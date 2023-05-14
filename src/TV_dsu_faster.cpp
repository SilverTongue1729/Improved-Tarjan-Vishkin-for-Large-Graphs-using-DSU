#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,abm,bmi,bmi2,lzcnt,popcnt,mmx,avx,avx2,tune=native")

#ifdef LOCAL
#include "/home/sriteja/Competitive Programming/Debugging/print.cpp"
#else
#define print(...) ((void)0)
#define cerr \
  if (0) cerr
#endif

int n, m;
int root;
vector<vector<int>> adj;
vector<vector<int>> tree, backedge;
vector<bool> vis;
vector<int> pre, inv_pre, par, nd, low, high;

void make_tree_dfs(int cur = root, int par = -1) {
  vis[cur] = true;
  for (auto x : adj[cur]) {
    if (vis[x] == false) {
      tree[cur].push_back(x);
      make_tree_dfs(x, cur);
    } else if (x != par && x < cur) {
      backedge[cur].push_back(x);
      backedge[x].push_back(cur);
    }
  }
}

int make_tree_bfs(int u = root) {
  vector<int> par(n, -1);
  queue<int> q;
  vis[u] = true;
  q.push(u);
  int n = 1;
  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    for (auto v : adj[cur]) {
      if (!vis[v]) {
        vis[v] = true;
        par[v] = cur;
        tree[cur].push_back(v);  // only par->child edges
        q.push(v);
        n++;
      } else if (par[cur] != v) {
        backedge[cur].push_back(v);
      }
    }
  }
  return n;
}

int calc_pre_par_nd(int cur = root) {
  static int count = 0;
  pre[cur] = count;
  inv_pre[count] = cur;
  count++;
  nd[cur] = 1;
  for (auto v : tree[cur]) {
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

map<pair<int, int>, pair<int, int>> parent;
map<pair<int, int>, int> sz;

void make(pair<int, int> v) {
  parent[v] = v;
  sz[v] = 1;
}

pair<int, int> find(pair<int, int> v) {
  if (v == parent[v]) return v;
  return parent[v] = find(parent[v]);
}

void Union(pair<int, int> a, pair<int, int> b) {
  a = find(a);
  b = find(b);
  if (a != b) {
    if (sz[a] < sz[b])
      swap(a, b);
    parent[b] = a;
    sz[a] += sz[b];
  }
}

void Union_aux(pair<int, int> a, pair<int, int> b) {
  Union({pre[a.first], pre[a.second]}, {pre[b.first], pre[b.second]});
}

void build_aux(int cur = root) {
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

int main() {
#ifdef LOCAL
  freopen("/home/sriteja/Competitive Programming/Debugging/IO/output_01.txt", "w", stderr);
#endif
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;
  adj = vector<vector<int>>(n);

  vis = vector<bool>(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    // u--; v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
    vis[u] = vis[v] = true;
  }

  vector<vector<int>> ans;
  for (int i = 0; i < n; i++)
    if (!vis[i]) {
      ans.push_back({i});
      print(i);
    }

  vis.assign(n, false);

  tree = backedge = vector<vector<int>>(n);
  inv_pre = pre = par = nd = vector<int>(n, -1);
  low = high = vector<int>(n, -1);

  vector<int> roots;
  for (int i = 0; i < n; i++) {
    if (!vis[i]) {
      root = i;
      roots.push_back(i);
      make_tree_dfs(i);
      // make_tree_bfs(i);
      calc_pre_par_nd(i);
      calc_low_high(i);
    }
  }
  // print(roots);

  for (int i = 0; i < n; i++)
    for (auto v : adj[i])
      if (pre[i] < pre[v])
        make({pre[i], pre[v]});

  for (auto root : roots) {
    build_aux(root);
  }

  map<pair<int, int>, int> mp;

  vis.assign(n, false);

  int cnt = ans.size();

  for (auto p : parent) {
    if (mp.find(find(p.first)) == mp.end()) {
      mp[p.second] = cnt;
      // mp.insert({p.second,cnt});
      cnt++;
      ans.push_back({p.first.first, p.first.second});

    } else {
      ans[mp[p.second]].push_back(p.first.first);
      ans[mp[p.second]].push_back(p.first.second);
    }
  }
  
  cout << ans.size() << endl;
  for (auto s : ans) {
    // if (s.size() > 2) cout << s.size()/2 << " ";
    // else cout << s.size() << " ";
    unordered_set<int> st;
    vector<int> temp;
    for (auto x : s) {
      if (st.find(inv_pre[x]) != st.end()) continue;
      st.insert(inv_pre[x]);
      // cout << inv_pre[x] << " ";
      temp.push_back(inv_pre[x]);
    }
    cout << temp.size() << " ";
    for (auto x : temp) cout << x << " ";
    cout << endl;
  }

  return 0;
}
