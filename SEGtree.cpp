#include<bits/stdc++.h>
using namespace std;
class SEGtree{
    vector<int> seg, lazy;
public:
    SEGtree(int  n){
        seg.resize(4*n+1,0);
        lazy.resize(4*n+1,0);
    }
    void build(int  ind, int  lo, int  hi, vector<int > &a){
        if(lo==hi){
            seg[ind] = a[lo];
            return;
        }
        int  mid = (lo+hi)>>1;
        build(ind*2+1,lo,mid,a);
        build(ind*2+2,mid+1,hi,a);
        seg[ind] = seg[ind*2+1]+seg[ind*2+2];
    }
    void propagate(int  ind, int  lo, int  hi){
        if(lazy[ind]!=0){
            seg[ind]+=lazy[ind];
            if(lo!=hi){
                lazy[ind*2+1] += lazy[ind];
                lazy[ind*2+2] += lazy[ind];
            }
            lazy[ind]=0;
        }
    }
    void pointupdate(int ind,int lo,int hi,int i ,int val){
        if(lo==hi){
            seg[ind]=val;
            return;
        }
        int mid = (lo+hi)/2;
        if(i<=mid) pointupdate(ind*2+1,lo,mid,i,val);
        else pointupdate(ind*2+2,mid+1,hi,i,val);
        seg[ind] = seg[ind*2+1]+seg[ind*2+2];
    }
    void rangeupdate(int  ind, int  i, int  j, int  val, int  lo, int  hi){
        propagate(ind,lo,hi);
        if(lo>j||hi<i) return;
        if(i<=lo&&hi<=j) {
            lazy[ind] += val;
            propagate(ind,lo,hi);
            return;
        }
        int  mid = (lo+hi) /2;
        rangeupdate(ind*2+1, i, j, val, lo, mid);
        rangeupdate(ind*2+2, i, j, val, mid+1, hi);
        seg[ind] = seg[ind*2+1]+seg[ind*2+2];
    }
    int quering(int  ind, int  i, int  j, int  lo, int  hi){
        propagate(ind,lo,hi);
        if(lo>j||hi<i) return 0;
        if(i<=lo&&hi<=j) {
            return seg[ind];
        }
        int  mid = (lo+hi) / 2;
        int  left = quering(ind*2+1, i, j, lo, mid);
        int  right = quering(ind*2+2, i, j, mid+1, hi);
        return left+right;
    }
};