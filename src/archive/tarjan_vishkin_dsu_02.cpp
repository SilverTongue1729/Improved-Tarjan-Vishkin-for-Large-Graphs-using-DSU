#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/home/sriteja/Competitive Programming/Debugging/print.cpp"
#else
#define print(...) ((void)0)
#define cerr if(0) cerr
#endif

int n,m;
int root;
vector<vector<int>> adj; 
vector<vector<int>> tree, backedge;
vector<bool> vis;
vector<int> pre, inv_pre, par, nd, low, high;

void make_tree_dfs(int cur=root, int par=-1) {
  vis[cur] = true;
  for (auto x : adj[cur]) {
    if (vis[x] == false) {
      tree[cur].push_back(x);
      make_tree_dfs(x, cur);
    }
    else if (x != par && x < cur) {
      backedge[cur].push_back(x);
      backedge[x].push_back(cur);
    }
  }
}

void make_tree_bfs(int u = root) {
  vector<int> par(n,-1);
  queue<int> q;
  vis[u] = true;
  q.push(u);
  while (!q.empty()){
    int cur = q.front();
    q.pop();
    for (auto v:adj[cur]){
      if (!vis[v]) {
        vis[v] = true;
        par[v] = cur;
        tree[cur].push_back(v);  // only par->child edges
        q.push(v);
      } else if (par[cur] != v){
        backedge[cur].push_back(v);
      }
    }
  }
}

int calc_pre_par_nd(int cur = root) {
  static int count = 0;
  pre[cur] = count;
  inv_pre[count] = cur;
  count++;
  nd[cur] = 1;
  for (auto v : tree[cur]){
    nd[cur] += calc_pre_par_nd(v);
    par[v] = cur;
  }
  return nd[cur];
}

void calc_low_high(int cur = root) {
  low[cur] = pre[cur];
  high[cur] = pre[cur];
  for (auto v : tree[cur]) {
    calc_low_high(v);
    low[cur] = min(low[cur], low[v]);
    high[cur] = max(high[cur], high[v]);
  }
  for (auto v : backedge[cur]) {
    low[cur] = min(low[cur], pre[v]);
    high[cur] = max(high[cur], pre[v]);
  }
}

map<pair<int,int>,pair<int,int>> parent;
map<pair<int,int>,int> sz;

void make(pair<int,int> v) {
  parent[v] = v; 
  sz[v] = 1; 
}

pair<int,int> find(pair<int,int> v) {
  if(v == parent[v]) return v; 
  return parent[v] = find(parent[v]);
}

void Union(pair<int,int> a, pair<int,int> b) {
  a = find(a);
  b = find(b);
  if(a != b) {
    if(sz[a] < sz[b]) 
      swap(a,b);
    parent[b] = a;
    sz[a] += sz[b];
  }
}

void Union_aux(pair<int,int> a, pair<int,int> b) {
  Union({pre[a.first], pre[a.second]}, {pre[b.first], pre[b.second]});
}

void build_aux(int cur=root){
  for (auto v : tree[cur]) {
    build_aux(v);
    if (pre[v] != 0 && (low[v] < pre[cur] || high[v] >= pre[cur] + nd[cur]))
      Union_aux({par[cur], cur}, {cur, v});
  }
  for (auto v : backedge[cur]) {
    if (pre[cur] < pre[v])
      Union_aux({cur, v}, {par[v], v});
    if (pre[cur] + nd[cur] <= pre[v])
      Union_aux({par[cur], cur}, {par[v], v});
  }
}

int main(){
#ifdef LOCAL
  freopen("/home/sriteja/Competitive Programming/Debugging/IO/output_01.txt","w",stderr);
#endif
  ios_base::sync_with_stdio(false); cin.tie(0);
  
  cin>>n>>m;
  adj = vector<vector<int>>(n);
  
  for(int i=0;i<m;i++){
    int u,v; cin>>u>>v;
    u--; v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  } 

  root = 0;
  vis = vector<bool>(n);
  tree = backedge = vector<vector<int>>(n);
  make_tree_bfs(root);
  // make_tree_dfs(root);
      
  inv_pre = pre = par = nd = vector<int>(n,-1);
  calc_pre_par_nd(root);
    
  low = high = vector<int>(n,-1);
  calc_low_high(root);
  
  
  for (int i=0;i<n;i++)
    for (auto v:adj[i])
      if (pre[i] < pre[v]) 
        make({pre[i],pre[v]});
  
  build_aux(root);
  
  map<pair<int,int>,vector<pair<int,int>>> auxiliary;
  
  for (auto p:parent)
    auxiliary[find(p.first)].push_back(p.first);
  
  for (auto p:auxiliary){
    for (auto x:p.second)
      cout << inv_pre[x.first] << "--" << inv_pre[x.second] << " ";
    cout << endl;
  }
    
  return 0;
}
