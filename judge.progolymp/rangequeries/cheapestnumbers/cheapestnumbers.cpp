#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,q,a[N];
vector<int> seg[4*N+5];
vector<int> pre[4*N+5];
//build merge sort tree
void build(int node,int l,int r){
    //if range length is 1 there's only one element to add and no children
    if (l==r){
        seg[node].push_back(a[l]);
        pre[node].push_back(a[l]);
        return;
    }int mid=(l+r)/2;
    build(node*2,l,mid);
    build(node*2+1,mid+1,r);
    int i=0,j=0;
    // use two pointers to merge the two vectors in O(r-l+1)
    while (i<seg[node*2].size() && j<seg[node*2+1].size()){
        if (seg[node*2][i]<seg[node*2+1][j]) seg[node].push_back(seg[node*2][i++]);
        else seg[node].push_back(seg[node*2+1][j++]);
    }
    while (i<seg[node*2].size()) seg[node].push_back(seg[node*2][i++]);
    while (j<seg[node*2+1].size()) seg[node].push_back(seg[node*2+1][j++]);

    pre[node].push_back(seg[node][0]);
    for(int i=1; i<seg[node].size(); i++) {
        pre[node].push_back(pre[node][i-1] + seg[node][i]);
    }

    return;
}
//query
pair<int, int> operator+(pair<int, int> lhs, pair<int, int> rhs) {
    return {lhs.first + rhs.first, lhs.second + rhs.second};
}

/*
int l = -1, r = n;
while (r - l > 1) {
    int m = (l + r) / 2;
    if (f(m)) {
        r = m; // 0 = f(l) < f(m) = 1
    } else {
        l = m; // 0 = f(m) < f(r) = 1
    }
}
*/

pair<int, int> query(int node,int l,int r,int lx,int rx,int x){ // sum of all elements leq `x`
    //if outside -> 0
    if (l>rx || r<lx) return {0, 0};
    //if inside do binary search
    if (l>=lx && r<=rx){
        int L=-1,R=seg[node].size()-1,mid;
        while (R - L > 1){
            mid=(L+R)/2;
            if (seg[node][mid]>x){
                R=mid;
            } else {
                L = mid;
            }
        }
        return {(L >= 0) ? pre[node][L] : 0, L+1};
    }
    int mid=(l+r)/2;
    return query(node*2,l,mid,lx,rx,x) + query(node*2+1,mid+1,r,lx,rx,x);
}
int main(){
    cin>>n>>q;
    for (int i=1;i<=n;i++) cin>>a[i];
    build(1,1,n);

    while (q--){
        int l,r,x;
        cin >> l >> r >> x;
        int L, R, mid;
        L = -1;
        R = 1e9;
        while (R - L > 1) {
            mid = L + (R - L) / 2;
            if (query(1, 1, n, l, r, mid).first > x) {
                R = mid;
            } else {
                L = mid;
            }
        }
        cout << query(1,1,n,l,r,L).second << endl;
    }
    return 0;
}
