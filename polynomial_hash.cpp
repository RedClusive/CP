struct P_hash {
    vector<int> mod;
    vector<int> p;
    vector<vector<int>> st;
    vector<vector<int>> h;
    int n;

    P_hash(const string& s) {
        mod = {999'988'901, 888'888'901};
        p = {37, 227};
        n = s.size();
        st.resize(2);
        h.resize(2);
        for (int l = 0; l < 2; ++l) {
            st[l].resize(n + 1, 1);
            h[l].resize(n + 1, 0);
            for (int i = 0; i < n; ++i) {
                st[l][i + 1] = 1ll * st[l][i] * p[l] % mod[l];
                h[l][i + 1] = (1ll * h[l][i] * p[l] % mod[l] + (s[i] - 'a' + 1)) % mod[l];
            }
        }
    }

    int get0(int l, int r) {
        return (h[0][r + 1] - 1ll * h[0][l] * st[0][r - l + 1] % mod[0] + mod[0]) % mod[0];
    }

    int get1(int l, int r) {
        return (h[1][r + 1] - 1ll * h[1][l] * st[1][r - l + 1] % mod[1] + mod[1]) % mod[1];
    }

    pii get(int l, int r) {
        return {(h[0][r + 1] - 1ll * h[0][l] * st[0][r - l + 1] % mod[0] + mod[0]) % mod[0],
                (h[1][r + 1] - 1ll * h[1][l] * st[1][r - l + 1] % mod[1] + mod[1]) % mod[1]};
    }
};
