#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/home/sriteja/Competitive Programming/Debugging/print.cpp"
#else
#define print(...) ((void)0)  // print to cerr
#define printl(...) ((void)0)
#define cerr if(0) cerr
#endif

int cnt;
vector<vector<int>> adj; 
vector<bool> visited; 
vector<vector<int>> dfstree, backedge;
map<pair<int,int>,vector<pair<int,int>>> auxillary;
map<pair<int,int>,bool> vis_aux;
vector<int> preorder;

void dfs(int cur, int par=-1)
{
  visited[cur] = true;
  cerr << cur << " ";
  for(auto x:adj[cur]) {
    if(visited[x] == false) {
      dfstree[cur].push_back(x);
      dfstree[x].push_back(cur);
      dfs(x,cur);
    }
    else if(x!=par  && x < cur) {
      backedge[cur].push_back(x);
      backedge[x].push_back(cur);
    }
  }
}

void PreOrderCalc(int cur, int par=-1, int count=0)
{
  preorder[cur]=count++;
  for(auto x:dfstree[cur]) {
    if(x!=par) {
      PreOrderCalc(x,cur,count);
    }
  }
}

int dfs_c(int cur, int par=-1)
{
  int minpre = preorder[cur];
  for (auto v:dfstree[cur]){
    if (v != par){
      int minpre_v = dfs_c(v,cur);
      for (auto u:backedge[v]){
        if (u != cur){
          minpre_v = min(minpre_v,preorder[u]);
        }
      }
      minpre = min(minpre,minpre_v);
      if (minpre_v < preorder[cur]) {
        auxillary[{min(cur,v), max(cur,v)}].push_back({min(cur,par), max(cur,par)});
        auxillary[{min(cur,par), max(cur,par)}].push_back({min(cur,v), max(cur,v)});
        cerr << "{" << min(cur,v) << "," << max(cur,v) << "} ";
        cerr << "{" << min(cur,par) << "," << max(cur,par) << "}" << endl;
      }
    }
  }
  return minpre;
}

void dfs_a(int cur, int par=-1){
  for (auto v:backedge[cur]){
    if (v != par && preorder[v] < preorder[cur]){
      auxillary[{min(cur,v), max(cur,v)}].push_back({min(cur,par), max(cur,par)});
      auxillary[{min(cur,par), max(cur,par)}].push_back({min(cur,v), max(cur,v)});
      cerr << "par: " << par << " " << "cur: " << cur << " " << "v: " << v << endl;
      cerr << "{" << min(cur,v) << "," << max(cur,v) << "} ";
      cerr << "{" << min(cur,par) << "," << max(cur,par) << "}" << endl;
    }
  }
  for(auto x:dfstree[cur]) {
    if (x != par){
      dfs_a(x,cur);
    }
  }
}

void dfs_conn(pair<int,int> p){
  vis_aux[p] = true;
  cout << p.first << "--" << p.second << " ";
  for (auto x:auxillary[p]){
    if (vis_aux[x] == false){
      dfs_conn(x);
    }
  }
  
}

int main(){
#ifdef LOCAL
  freopen("/home/sriteja/Competitive Programming/Debugging/IO/output_01.txt","w",stderr);
#endif
  ios_base::sync_with_stdio(false); cin.tie(0);

  int n,m; cin>>n>>m;
  adj = vector<vector<int>>(n);
  visited = vector<bool>(n,false);
  dfstree = vector<vector<int>>(n);
  backedge = vector<vector<int>>(n);
  preorder=vector<int>(n);
  
  for(int i=0;i<m;i++){
    int u,v; cin>>u>>v;
    u--; v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
    auxillary[{min(u,v), max(u,v)}] = {};
  } 
    

  print(n);
  print(m);
  cerr << "dfs:";
  dfs(0);
  cerr << endl;
  cerr << endl;
  
  cerr << "Backedges: " << endl;
  for(int i=0;i<n;i++) {
    cerr << i << ": ";
    for(auto x:backedge[i]) cerr << x << " ";
    cerr << endl;
  }
  cerr << endl;
  
  cerr << "Dfs Tree: " << endl;
  for(int i=0;i<n;i++) {
    cerr << i << ": ";
    for(auto x:dfstree[i]) cerr << x << " ";
    cerr << endl;
  }
  cerr << endl;
  
  visited.assign(n,false);
  cerr << "Preorder: " << endl;
  PreOrderCalc(0);
  for(int i=0;i<n;i++) cerr << preorder[i] << " ";
  cerr << endl;
  
  cerr << "Auxillary Edges: " << endl;
  cerr << "dfs a: " << endl;
  dfs_a(0);
  cerr << "dfs c: " << endl;
  dfs_c(0);
  cerr << endl;
  
  for (auto p:auxillary){
    if (vis_aux[p.first] == true) continue;
    vis_aux[p.first] = true;
    dfs_conn(p.first);
    cout <<endl;
  }
  

  return 0;
}
/*
4 4
1 2
2 3
3 4
2 4
*/

/*
{1,2} {2,3} {1,3} {3,4} {2,4} 
4--2 3--4 3--1 2--3 1--2

{0,1} {1,5} {5,6} {0,6} 
6--0 5--6 1--5 0--1 

{5,7} {7,8} {5,8} 
8--5 7--8 5--7

8--9
{8,9} 

{10,11}
10--11
*/