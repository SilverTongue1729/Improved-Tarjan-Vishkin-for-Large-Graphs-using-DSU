#include <bits/stdc++.h>
#include <sys/resource.h>
using namespace std;

#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,abm,bmi,bmi2,lzcnt,popcnt,mmx,avx,avx2,tune=native")

#ifdef LOCAL
#include "/home/sriteja/Competitive Programming/Debugging/print.cpp"
#else
#define print(...) ((void)0)  // print to cerr
#define printl(...) ((void)0)
#endif

int cnt;
vector<set<int>> ans;
vector<vector<int>> adj;
vector<int> disc, low, parent;
stack<pair<int, int>> st;
vector<bool> vis;

void dfs(int u) {
  static int time = 0;
  disc[u] = low[u] = ++time;
  int children = 0;

  for (int v : adj[u]) {
    if (disc[v] == -1) {
      children++;
      parent[v] = u;
      st.push({u, v});
      dfs(v);
      low[u] = min(low[u], low[v]);
      if ((disc[u] == 1 && children > 1) || (disc[u] > 1 && low[v] >= disc[u])) {
        set<int> s;
        while (st.top().first != u || st.top().second != v) {
          // cout << st.top().first << "--" << st.top().second << " ";
          s.insert(st.top().first);
          s.insert(st.top().second);
          vis[st.top().first] = vis[st.top().second] = true;
          st.pop();
        }
        // cout << st.top().first << "--" << st.top().second;
        s.insert(st.top().first);
        s.insert(st.top().second);
        vis[st.top().first] = vis[st.top().second] = true;
        st.pop();
        // cout << endl;
        cnt++;
        ans.push_back(s);
        s.clear();
      }
    } else if (v != parent[u]) {
      low[u] = min(low[u], disc[v]);
      if (disc[v] < disc[u]) {
        st.push({u, v});
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
  
  // only use it for dfs
  const rlim_t kStackSize = 1024 * 1024 * 1024;  // 1 GB stack size
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0) {
    if (rl.rlim_cur < kStackSize) {
      rl.rlim_cur = kStackSize;
      result = setrlimit(RLIMIT_STACK, &rl);
      if (result != 0) {
        std::cerr << "setrlimit returned result = " << result << std::endl;
      }
    }
  }
  

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
      // cout << st.top().first << "--" << st.top().second << " ";
      s.insert(st.top().first);
      s.insert(st.top().second);
      vis[st.top().first] = vis[st.top().second] = true;
      st.pop();
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
