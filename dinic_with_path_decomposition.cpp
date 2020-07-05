#include <bits/stdc++.h>

#define F first
#define S second
#define pb push_back
#define ll long long
#define ld long double
#define endl '\n'
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pld pair<ld, ld>
#define ull unsigned long long

using namespace std;

const ll INF = 1e9 + 7;
const int N = 501;
const int M = 1e9 + 7;

mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());

int n, m, s, t, d[N], ptr[N];

struct edge {
    int a, b, cap, flow, id;
};

vector<edge> e;
vector<int> g[N];

void add_edge(int a, int b, int cap, int id) {
    edge e1 = {a, b, cap, 0, id};
    edge e2 = {b, a, 0, 0, id};
    g[a].pb(e.size());
    e.pb(e1);
    g[b].pb(e.size());
    e.pb(e2);
}

bool bfs() {
    memset(d, -1, n * sizeof d[0]);
    d[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto id : g[v]) {
            int to = e[id].b;
            if (d[to] == -1 && e[id].flow < e[id].cap) {
                d[to] = d[v] + 1;
                q.push(to);
            }
        }
    }
    return d[t] != -1;
}

int dfs(int v, int flow) {
    if (!flow) return 0;
    if (v == t) return flow;
    for (; ptr[v] < g[v].size(); ++ptr[v]) {
        int id = g[v][ptr[v]], to = e[id].b;
        if (d[to] != d[v] + 1) continue;
        int pushed = dfs(to, min(flow, e[id].cap - e[id].flow));
        if (pushed) {
            e[id].flow += pushed;
            e[id ^ 1].flow -= pushed;
            return pushed;
        }
    }
    return 0;
}

int dinic(int start = INF) {
    int flow = 0;
    int it = 0;
    while (true) {
        if (!bfs()) break;
        memset(ptr, 0, n * sizeof ptr[0]);
        while (int pushed = dfs(s, start)) {
            flow += pushed;
            if (flow == start) return flow;
        }
    }
    return flow;
}

bool was[N];

int decomp(int v, vector<pii>& p) {
    for (auto id : g[v]) {
        if (e[id].flow > 0) {
            if (e[id].b == t) {
                p.pb({e[id].id, id});
                return e[id].flow;
            }
            int ok = decomp(e[id].b, p);
            if (ok) {
                p.pb({e[id].id, id});
                return min(ok, e[id].flow);
            }
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#else
    // freopen("a.in", "r", stdin);
    // freopen("a.out", "w", stdout);
#endif
    cin >> n >> m;
    s = 0;
    t = n - 1;
    for (int i = 0; i < m; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        x--, y--;
        add_edge(x, y, z, i + 1);
    }
    dinic();
    vector<pair<int, vector<pii>>> res;
    while (true) {
        vector<pii> p;
        int cur = decomp(s, p);
        cerr << cur << endl;
        if (!cur) break;
        for (auto i : p) {
            e[i.S].flow -= cur;
        }
        reverse(p.begin(), p.end());
        res.pb({cur, p});
    }
    cout << res.size() << endl;
    for (auto& kek: res) {
        cout << kek.F << ' ';
        cout << kek.S.size() << ' ';
        for (auto i : kek.S) {
            cout << i.F << ' ';
        }
        cout << endl;
    }
    return 0;
}
