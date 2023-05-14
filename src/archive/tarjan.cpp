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
vector<int> disc, low, parent;
stack<pair<int,int>> st;

void dfs(int u){
  static int time = 0;
  disc[u] = low[u] = ++time;
  int children = 0;
  
  for(int v:adj[u]){
    if(disc[v]==-1){
      children++;
      parent[v] = u;
      st.push({u,v});
      dfs(v);
      low[u] = min(low[u],low[v]);
      if ((disc[u]==1 && children>1) || (disc[u]>1 && low[v]>=disc[u])){
        while (st.top().first != u || st.top().second != v) {
          cout << st.top().first << "--" << st.top().second << " ";
          st.pop();
        }
        cout << st.top().first << "--" << st.top().second;
        st.pop();
        cout << endl;
        cnt++;
      }
    }
    else if(v!=parent[u]){
      low[u] = min(low[u],disc[v]);
      if(disc[v]<disc[u]){
        st.push({u,v});
      }
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
  print(n);
  print(m);
  
  for(int i=0;i<m;i++){
    int u,v; cin>>u>>v;
    // u--; v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }  
  
  disc = low = parent = vector<int>(n,-1);
    
  for(int i=0;i<n;i++){
    if(disc[i]==-1){
      dfs(i);
    }
    set<int> s;
    int j=0;
    while (st.size() > 0) {
      j = 1;
      cout << st.top().first << "--" << st.top().second << " ";
      st.pop();
    }
    if (j == 1) {
      cout << endl;
      cnt++;
    }
  }

  return 0;
}
