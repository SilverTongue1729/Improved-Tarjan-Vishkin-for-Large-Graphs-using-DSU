#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,abm,bmi,bmi2,lzcnt,popcnt,mmx,avx,avx2,tune=native")

#ifdef LOCAL
#include "/home/sriteja/Competitive Programming/Debugging/print.cpp"
#else
#define print(...) ((void)0)  // print to cerr
#define printl(...) ((void)0)
#define cerr \
  if (0) cerr
#endif

int cnt;
vector<set<int>> ans;
vector<vector<int>> adj;
vector<int> disc, low, parent;
// stack<pair<int, int>> st;
vector<pair<int, int>> st;
int st_top=-1;
vector<bool> vis;

void dfs(int u) {
  static int time = 0;
  disc[u] = low[u] = ++time;
  int children = 0;

  for (int v : adj[u]) {
    if (disc[v] == -1) {
      children++;
      parent[v] = u;
      st.push_back({u, v});
      st_top++;
      dfs(v);
      low[u] = min(low[u], low[v]);
      if ((disc[u] == 1 && children > 1) || (disc[u] > 1 && low[v] >= disc[u])) {
        set<int> s;
        if (st_top == -1) {
          printf("st_top is -1\n");
          exit(0);
        }
        while (st[st_top].first != u || st[st_top].second != v) {
          // cout << st[st_top].first << "--" << st[st_top].second << " ";
          s.insert(st[st_top].first);
          s.insert(st[st_top].second);
          vis[st[st_top].first] = vis[st[st_top].second] = true;
          // st.pop();
          st_top--;
        }
        // cout << st[st_top].first << "--" << st[st_top].second;
        s.insert(st[st_top].first);
        s.insert(st[st_top].second);
        vis[st[st_top].first] = vis[st[st_top].second] = true;
        // st.pop();
        st_top--;
        // cout << endl;
        cnt++;
        ans.push_back(s);
        s.clear();
      }
    } else if (v != parent[u]) {
      low[u] = min(low[u], disc[v]);
      if (disc[v] < disc[u]) {
        st.push_back({u, v});
      }
    }
  }
}

int main() {
#ifdef LOCAL
  freopen("/home/sriteja/Competitive Programming/Debugging/IO/output_01.txt", "w", stderr);
#endif
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  adj.reserve((int)1e7);
  // st.reserve((int)1e7);

  int n, m;
  cin >> n >> m;
  adj = vector<vector<int>>(n);
  vis = vector<bool>(n);

  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    // u--; v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  disc = low = parent = vector<int>(n, -1);

  set<int> s;
  for (int i = 0; i < n; i++) {
    if (disc[i] == -1) {
      dfs(i);
    }
    int j = 0;
    while (st.size() > 0) {
      j = 1;
      // cout << st[st_top].first << "--" << st[st_top].second << " ";
      s.insert(st[st_top].first);
      s.insert(st[st_top].second);
      vis[st[st_top].first] = vis[st[st_top].second] = true;
      // st.pop();
      st_top--;
    }
    if (j == 1) {
      // cout << endl;
      cnt++;
      ans.push_back(s);
      s.clear();
    }
  }

  for (int i=0;i<n;i++)
    if (!vis[i]) ans.push_back({i});

  cout << ans.size() << endl;
  for (auto s : ans) {
    cout << s.size() << " ";
    for (auto x : s) cout << x << " ";
    cout << endl;
  }

  return 0;
}
