int m=(int)1e9+7;
int apowerb(int a,int b){
    int ans=1,t=a;
    while(b){
        if(b&1) ans=(ans*1LL*t)%m;
        t=(t*1LL*t)%m;
        b>>=1;
    }
    return ans;
}