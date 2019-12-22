struct P_matrix {
    vector<vector<int>> h;
    vector<vector<int>> st;
    int mod;
    int px;
    int py;
    int n, m;

    P_matrix(const vector<vector<char>>& a, int b = 999'988'901, int c = 227, int d = 37) {
        mod = b;
        px = c;
        py = d;
        n = a.size();
        m = a[0].size();
        h.resize(n + 1, vector<int>(m + 1, 0));
        st.resize(n + 1, vector<int>(m + 1, 1));
        for (int j = 0; j < m; ++j) {
            st[0][j + 1] = 1ll * st[0][j] * py % mod;
        }
        for (int i = 0; i < n; ++i) {
            st[i + 1][0] = 1ll * st[i][0] * px % mod;
            for (int j = 0; j < m; ++j) {
                st[i + 1][j + 1] = 1ll * st[i + 1][j] * py % mod;
                h[i + 1][j + 1] = add_to_pos(i, j, a[i][j]);
            }
        }
    }

    int add_to_pos(int i, int j, char c) {
        int res = 0;
        res = (res + 1ll * h[i + 1][j] * py % mod) % mod;
        res = (res + 1ll * h[i][j + 1] * px % mod) % mod;
        res = (res - 1ll * h[i][j] * py * px % mod + mod) % mod;
        res = (res + (c - 'a' + 1)) % mod;
        return res;
    }

    int get(int u, int l, int d, int r) {
        int res = 0;
        res = h[d + 1][r + 1];
        res = (res - 1ll * h[d + 1][l] * st[0][r - l + 1] % mod + mod) % mod;
        res = (res - 1ll * h[u][r + 1] * st[d - u + 1][0] % mod + mod) % mod;
        res = (res + 1ll * h[u][l] * st[d - u + 1][r - l + 1] % mod) % mod;
        return res;
    }

    int get() {
        return h[n][m];
    }

    int get_changed(int i, int j, char c) {
        int res = 0;
        res = (h[n][m] - 1ll * h[i + 1][j + 1] * st[n - i - 1][m - j - 1] % mod + mod) % mod;
        res = (res + 1ll * add_to_pos(i, j, c) * st[n - i - 1][m - j - 1] % mod) % mod;
        return res;
    }

    void outst() {
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= m; ++j) {
                cout << st[i][j] << ' ';
            }
            cout << endl;
        }
    }
};
