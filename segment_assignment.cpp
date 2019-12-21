template<typename T>
struct segtree {
    int n;
    vector<T> t;
    vector<T> lazy;
    vector<bool> need;
    segtree(int sz) {
        n = 1;
        while (n < sz) n *= 2;
        t.resize(2 * n, 0);
        lazy.resize(2 * n, 0);
        need.resize(2 * n, 0);
    }
    T op(T a, T b) {
        return a + b;
    }
    void push(int v, int l, int r) {
        if (need[v] && v < n) {
            int mid = (l + r) >> 1;
            t[v * 2] = lazy[v] * (mid - l);
            t[v * 2 + 1] = lazy[v] * (r - mid);
            lazy[v * 2] = lazy[v];
            lazy[v * 2 + 1] = lazy[v];
            need[v * 2] = need[v];
            need[v * 2 + 1] = need[v];
            lazy[v] = 0;
            need[v] = 0;
        }
    }
    void upd(int v, int cl, int cr, int l, int r, T x) {
        if (r <= cl || cr <= l) return;
        if (l <= cl && cr <= r) {
            lazy[v] = x;
            need[v] = 1;
            t[v] = x * (cr - cl);
            return;
        }
        push(v, cl, cr);
        int mid = (cl + cr) / 2;
        upd(v * 2, cl, mid, l, r, x);
        upd(v * 2 + 1, mid, cr, l, r, x);
        t[v] = op(t[v * 2], t[v * 2 + 1]);
    }
    void upd(int l, int r, T x) {
        upd(1, 0, n, l, r, x);
    }
    T get(int v, int cl, int cr, int l, int r) {
        if (r <= cl || cr <= l) return 0;
        if (l <= cl && cr <= r) {
            return t[v];
        }
        push(v, cl, cr);
        int mid = (cl + cr) / 2;
        return op(get(v * 2, cl, mid, l, r), get(v * 2 + 1, mid, cr, l, r));
    }
    T get(int l, int r) {
        return get(1, 0, n, l, r);
    }
};
