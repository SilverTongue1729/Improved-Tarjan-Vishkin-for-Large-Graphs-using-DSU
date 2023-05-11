#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/home/sriteja/Competitive Programming/Debugging/print.cpp"
#else
#define print(...) ((void)0)
#define cerr if(0) cerr
#endif

int root;
vector<vector<int>> adj; 
vector<vector<int>> tree, backedge;
vector<bool> vis;
vector<int> pre, inv_pre, par, nd, low, high;
map<pair<int, int>, vector<pair<int, int>>> auxiliary;
map<pair<int, int>, bool> vis_aux;

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
  queue<int> q;
  vis[u] = true;
  q.push(u);
  while (!q.empty()){
    int cur = q.front();
    q.pop();
    for (auto v:adj[cur]){
      if (!vis[v]) {
        vis[v] = true;
        tree[cur].push_back(v);  // only par->child edges
        q.push(v);
      } else if (par[cur] != v)
        backedge[cur].push_back(v);
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

void aux_add(pair<int,int> u, pair<int,int> v) {
  auxiliary[{pre[u.first], pre[u.second]}].push_back({pre[v.first], pre[v.second]});
  auxiliary[{pre[v.first], pre[v.second]}].push_back({pre[u.first], pre[u.second]});
}

void build_aux(int cur=root){
  for (auto v : tree[cur]) {
    build_aux(v);
    if (pre[v] != 0 && (low[v] < pre[cur] || high[v] >= pre[cur] + nd[cur]))
      aux_add({par[cur], cur}, {cur, v});
  }
  for (auto v : backedge[cur]) {
    if (pre[cur] < pre[v])
      aux_add({cur, v}, {par[v], v});
    if (pre[cur] + nd[cur] <= pre[v])
      aux_add({par[cur], cur}, {par[v], v});
  }
}

void dfs_conn(pair<int,int> p){
  vis_aux[p] = true;
  cout << inv_pre[p.first] << "--" << inv_pre[p.second] << " ";
  for (auto& x:auxiliary[p])
    if (vis_aux[x] == false)
      dfs_conn(x);
}

int main(){
#ifdef LOCAL
  freopen("/home/sriteja/Competitive Programming/Debugging/IO/output_01.txt","w",stderr);
#endif
  ios_base::sync_with_stdio(false); cin.tie(0);

  int n,m; cin>>n>>m;
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
  par = vector<int>(n,-1);
  make_tree_bfs(root);
  // make_tree_dfs(root);
      
  inv_pre = pre = nd = vector<int>(n,-1);
  calc_pre_par_nd(root);
    
  low = high = vector<int>(n,-1);
  calc_low_high(root);
  
  build_aux(root);
    
  for (int i=0;i<n;i++){
    for (auto v:adj[i]){
      if (vis_aux[{pre[i], pre[v]}] == true || pre[i] > pre[v]) continue;
      vis_aux[{pre[i], pre[v]}] = true;
      dfs_conn({pre[i], pre[v]});
      cout << endl;
    }
  }
  
  return 0;
}
