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

const ll INF = 1e18 + 7;
const int N = 1e7 + 7;
const int M = 1e9 + 7;

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());

struct vertex {
    int next[2];
    bool leaf;
    int p;
    int up;
    char pch;
    int link;
    int go[2];
    int was;
};

vertex t[N + 1];
int sz;

void init() {
    t[0].p = t[0].link = t[0].up = -1;
    memset(t[0].next, -1, sizeof t[0].next);
    memset(t[0].go, -1, sizeof t[0].go);
    sz = 1;
}

void add_string(const string& s) {
    int v = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        int c = s[i] - '0';
        if (t[v].next[c] == -1) {
            memset(t[sz].next, -1, sizeof t[sz].next);
            memset(t[sz].go, -1, sizeof t[sz].go);
            t[sz].p = v;
            t[sz].pch = c;
            t[sz].link = -1;
            t[sz].up = -1;
            t[v].next[c] = sz++;
        }
        v = t[v].next[c];
    }
    t[v].leaf = true;
}

int go(int v, char c);

int get_link(int v) {
    if (t[v].link == -1) {
        if (v == 0 || t[v].p == 0) {
            t[v].link = 0;
        } else {
            t[v].link = go(get_link(t[v].p), t[v].pch);
        }
    }
    return t[v].link;
}

int go(int v, char c) {
    if (t[v].go[c] == -1) {
        if (t[v].next[c] != -1) {
            t[v].go[c] = t[v].next[c];
        } else {
            t[v].go[c] = v == 0 ? 0 : go(get_link(v), c);
        }
    }
    return t[v].go[c];
}

int up(int v) {
    if (t[v].up == -1) {
        int kek = get_link(v);
        if (t[kek].leaf || kek == 0) {
            t[v].up = kek;
        } else {
            t[v].up = up(kek);
        }
    }
    return t[v].up;
}

void dfs(int v) {
    t[v].was = 1;
    for (char c = 0; c <= 1; ++c) {
        int to = go(v, c);
        if (t[to].was == 1) {
            cout << "TAK";
            exit(0);
        }
        if (t[to].was == 2 || t[to].leaf || t[up(to)].leaf) continue;
        dfs(to);
    }
    t[v].was = 2;
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
    init();
    int n;
    cin >> n;
    if (n == 0) {
        cout << "TAK";
        return 0;
    }
    string s;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        add_string(s);
    }
    dfs(0);
    cout << "NIE";
    return 0;
}
