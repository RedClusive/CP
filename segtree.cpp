template<typename T>
struct segtree {

    int n;
    vector <T> t;

    segtree(int sz) {
        n = sz;
        t.resize(n << 1, 0);
    }

    T op(const T& a, const T& b) {
        return a + b;
    }

    T get(int l, int r) { 
        T res = 0;
        l += n, r += n;
        while (l < r) {
            if (l & 1) res = op(res, t[l++]);
            if (r & 1) res = op(res, t[--r]);
            l >>= 1, r >>= 1;
        }
        return res;
    }

    void upd(int v, const T& x) {
        v += n;
        t[v] = x;
        while (v >>= 1) {
            t[v] = op(t[v << 1], t[v << 1 | 1]);
        }
    }
};
