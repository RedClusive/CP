template<typename T>
struct segtree {
    int n;
    vector<T> t;
    vector<T> lazy;
    vector<bool> need;
    
    segtree(int sz) {
        n = 1;
        while (n < sz) n <<= 1;
        t.resize(n << 1, 0);
        lazy.resize(n << 1, 0);
        need.resize(n << 1, 0);
    }

    T op(const T& a, const T& b) {
        return a + b;
    }

    void push(int v, int l, int r) {
        if (need[v] && v < n) {
            int mid = (l + r) >> 1, lc = v << 1, rc = v << 1 | 1;
            t[lc] = lazy[v] * (mid - l);
            t[rc] = lazy[v] * (r - mid);
            lazy[lc] = lazy[v];
            lazy[rc] = lazy[v];
            need[lc] = need[v];
            need[rc] = need[v];
            lazy[v] = 0;
            need[v] = 0;
        }
    }
    void upd(int v, int cl, int cr, int l, int r, const T& x) {
        if (r <= cl || cr <= l) return;
        if (l <= cl && cr <= r) {
            lazy[v] = x;
            need[v] = 1;
            t[v] = x * (cr - cl);
            return;
        }
        push(v, cl, cr);
        int mid = (cl + cr) >> 1;
        upd(v << 1, cl, mid, l, r, x);
        upd(v << 1 | 1, mid, cr, l, r, x);
        t[v] = op(t[v << 1], t[v << 1 | 1]);
    }
    void upd(int l, int r, const T& x) {
        upd(1, 0, n, l, r, x);
    }
    T get(int v, int cl, int cr, int l, int r) {
        if (r <= cl || cr <= l) return 0;
        if (l <= cl && cr <= r) {
            return t[v];
        }
        push(v, cl, cr);
        int mid = (cl + cr) >> 1;
        return op(get(v << 1, cl, mid, l, r), get(v << 1 | 1, mid, cr, l, r));
    }
    T get(int l, int r) {
        return get(1, 0, n, l, r);
    }
};
