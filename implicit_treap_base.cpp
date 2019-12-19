mt19937 gen{random_device{}()};

struct treap {

    struct node {
        int val, y, sz;
        node *l, *r;

        node() : sz(1), y(gen()), l(nullptr), r(nullptr) {
        }

        node(int k) : val(k), sz(1), y(gen()), l(nullptr), r(nullptr) {
        }
    };

    typedef node* pnode;

    int size(pnode v) {
        return (v ? v->sz : 0);
    }

    void upd_sz(pnode v) {
        if (v) v->sz = size(v->l) + size(v->r) + 1;
    }

    void split(pnode v, pnode& l, pnode& r, int key) {
        if (!v) {
            l = r = nullptr;
            return;
        }
        int cur = (v->l != nullptr ? v->l->sz : 0);
        if (cur < key) {
            split(v->r, v->r, r, key - cur - 1);
            l = v;
        } else {
            split(v->l, l, v->l, key);
            r = v;
        }
        upd_sz(v);
    }

    void merge(pnode& v, pnode l, pnode r) {
        if (!l) {
            v = r;
            return;
        }
        if (!r) {
            v = l;
            return;
        }
        if (l->y > r->y) {
            merge(l->r, l->r, r);
            v = l;
        } else {
            merge(r->l, l, r->l);
            v = r;
        }
        upd_sz(v);
    }

    /*
    I am the bone of my treap
    pointers is my body, random is my blood
    I have created over a thousand nodes
    Unknown to memory leaks, nor known to destructor
    Have withstood time limits to answer many queries
    Yet those split and merge will never hold anything
    So as I pray, Unlimited Node Works!    
    */

    pnode root;

    treap() : root(nullptr) {
    }

    void insert(int pos, int val) {
        if (!root) {
            root = new node(val);
            return;
        }
        pnode l, r, nw = new node(val);
        split(root, l, r, pos - 1);
        merge(l, l, nw);
        merge(root, l, r);
    }

    void kek(int l, int r) {
        pnode a, b, c;
        split(root, b, c, r);
        split(b, a, b, l - 1);
        merge(b, b, a);
        merge(root, b, c);
    }

    void out() {
        out(root);
    }

    void out(pnode v) {
        if (v->l) out(v->l);
        cout << v->val << ' ';
        if (v->r) out(v->r);
    }
};
