struct P_matrix {
    vector<vector<vector<int>>> h;
    vector<vector<vector<int>>> st;
    vector<int> mod;
    vector<int> px;
    vector<int> py;
    int n, m, kek;

    P_matrix(const vector<vector<char>>& a) {
        mod = {999'988'901, 888'888'901, 1'000'000'007, 1'000'000'003};
        px = {449, 37, 31, 227};
        py = {31, 1337, 227, 228, 4243};
        n = a.size();
        m = a[0].size();
        kek = 2;
        h.resize(kek);
        st.resize(kek);
        for (int k = 0; k < kek; ++k) {
            h[k].resize(n + 1, vector<int>(m + 1, 0));
            st[k].resize(n + 1, vector<int>(m + 1, 1));
            for (int j = 0; j < m; ++j) {
                st[k][0][j + 1] = 1ll * st[k][0][j] * py[k] % mod[k];
            }
            for (int i = 0; i < n; ++i) {
                st[k][i + 1][0] = 1ll * st[k][i][0] * px[k] % mod[k];
                for (int j = 0; j < m; ++j) {
                    st[k][i + 1][j + 1] = 1ll * st[k][i + 1][j] * py[k] % mod[k];
                    h[k][i + 1][j + 1] = add_to_pos(i, j, a[i][j], k);
                }
            }
        }
    }

    int add_to_pos(int i, int j, char c, int k) {
        int res = 0;
        res = (res + 1ll * h[k][i + 1][j] * py[k] % mod[k]) % mod[k];
        res = (res + 1ll * h[k][i][j + 1] * px[k] % mod[k]) % mod[k];
        res = (res - 1ll * h[k][i][j] * py[k] * px[k] % mod[k] + mod[k]) % mod[k];
        res = (res + (c - 'a' + 1)) % mod[k];
        return res;
    }

    int get(int u, int l, int d, int r, int k) {
        int res = 0;
        res = h[k][d + 1][r + 1];
        res = (res - 1ll * h[k][d + 1][l] * st[k][0][r - l + 1] % mod[k] + mod[k]) % mod[k];
        res = (res - 1ll * h[k][u][r + 1] * st[k][d - u + 1][0] % mod[k] + mod[k]) % mod[k];
        res = (res + 1ll * h[k][u][l] * st[k][d - u + 1][r - l + 1] % mod[k]) % mod[k];
        return res;
    }

    vector<int> get(int u, int l, int d, int r) {
        vector<int> tmp;
        for (int k = 0; k < kek; ++k) {
            tmp.push_back(get(u, l, d, r, k));
        }
        return tmp;
    }

    int get_changed(int i, int j, char c, int k) {
        int res = 0;
        res = (h[k][n][m] - 1ll * h[k][i + 1][j + 1] * st[k][n - i - 1][m - j - 1] % mod[k] + mod[k]) % mod[k];
        res = (res + 1ll * add_to_pos(i, j, c, k) * st[k][n - i - 1][m - j - 1] % mod[k]) % mod[k];
        return res;
    }

    vector<int> get_changed(int i, int j, char c) {
        vector<int> tmp;
        for (int k = 0; k < kek; ++k) {
            tmp.push_back(get_changed(i, j, c, k));
        }
        return tmp;
    }

    void outst(int k) {
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= m; ++j) {
                cout << st[k][i][j] << ' ';
            }
            cout << endl;
        }
    }
};
