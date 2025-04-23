#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

struct AP {
    long long a = 0, d = 0;
    AP() {}
    AP(long long _a, long long _d) : a(_a), d(_d) {}

    long long sum(int n) const {
        return n * (2 * a + (n - 1) * d) / 2;
    }

    AP shift(int n) const {
        return AP(a + (n - 1) * d, d);
    }

    AP operator+(const AP &o) const {
        return AP(a + o.a, d + o.d);
    }
};

long long t[N << 2];
AP lazy[N << 2];
int n, q;

void build(int node, int l, int r) {
    t[node] = 0;
    lazy[node] = AP();
    if (l == r) return;
    int mid = (l + r) / 2;
    build(node * 2, l, mid);
    build(node * 2 + 1, mid + 1, r);
}

void propagate(int node, int l, int r) {
    if (lazy[node].a == 0 && lazy[node].d == 0) return;
    int len = r - l + 1;
    t[node] += lazy[node].sum(len);
    if (l != r) {
        int mid = (l + r) / 2;
        lazy[node * 2] = lazy[node * 2] + lazy[node];
        lazy[node * 2 + 1] = lazy[node * 2 + 1] + lazy[node].shift(mid - l + 2);
    }
    lazy[node] = AP();
}

void update(int node, int l, int r, int i, int j, AP val) {
    propagate(node, l, r);
    if (r < i || l > j) return;
    if (i <= l && r <= j) {
        lazy[node] = lazy[node] + val.shift(l - i + 1);
        propagate(node, l, r);
        return;
    }
    int mid = (l + r) / 2;
    update(node * 2, l, mid, i, j, val);
    update(node * 2 + 1, mid + 1, r, i, j, val);
    t[node] = t[node * 2] + t[node * 2 + 1];
}

long long query(int node, int l, int r, int i, int j) {
    propagate(node, l, r);
    if (r < i || l > j) return 0;
    if (i <= l && r <= j) return t[node];
    int mid = (l + r) / 2;
    return query(node * 2, l, mid, i, j) + query(node * 2 + 1, mid + 1, r, i, j);
}