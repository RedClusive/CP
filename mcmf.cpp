int n, m, s, t, d[N], ptr[N], pr[N], used[N], cpr[N];

struct edge {
    int a, b, cap, flow, cost, id;
};

vector<edge> e;
vector<int> g[N];

void clear_dist() {
    for (int i = 0; i < n; ++i) {
        cpr[i] = pr[i];
    }
    fill(d, d + n, INF);
    fill(pr, pr + n, -1);
    fill(used, used + n, 0);
}

void add_edge(int a, int b, int cap, int cost, int id) {
    edge e1 = {a, b, cap, 0, cost, id};
    edge e2 = {b, a, 0, 0, -cost, id};
    g[a].pb(e.size());
    e.pb(e1);
    g[b].pb(e.size());
    e.pb(e2);
}

bool spfa() {
    clear_dist();
    d[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        used[v] = false;
        for (auto id : g[v]) {
            int to = e[id].b;
            if (e[id].flow < e[id].cap && d[v] + e[id].cost < d[to]) {
                d[to] = d[v] + e[id].cost;
                pr[to] = id;
                if (!used[to]) {
                    q.push(to);
                    used[to] = true;
                }
            }
        }
    }
    return d[t] < INF;
}

int mcmf(ll& cost, int k = INF) {
    int flow = 0;
    while (flow < k) {
        if (!spfa()) break;
        int add = k - flow;
        for (int v = t; v != s; v = e[pr[v]].a) {
            int id = pr[v];
            add = min(add, e[id].cap - e[id].flow);
        }
        for (int v = t; v != s; v = e[pr[v]].a) {
            int id = pr[v];
            e[id].flow += add;
            e[id^1].flow -= add;
            cost += 1ll * add * e[id].cost;
        }
        flow += add;
    }
    return flow;
}
