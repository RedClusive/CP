template<class T>
struct segtree {

    int n;
    vector <T> t;

    segtree(int sz) {
        n = sz;
        t.resize(n << 1, 0);
    }

    T op(T a, T b) {
        return a + b;
    }

    T get(int l, int r) {  // sum on interval [l, r)
        T res = 0;
        l += n, r += n;
        while (l < r) {
            if (l & 1) res = op(res, t[l++]);
            if (r & 1) res = op(res, t[--r]);
            l >>= 1, r >>= 1;
        }
        return res;
    }

    void upd(int v, T x) {
        v += n;
        t[v] = x;
        while (v > 1) {
            v >>= 1;
            t[v] = op(t[v << 1], t[v << 1 | 1]);
        }
    }
};
