/**
 * problem: Dado un grafo con pesos en 
 * los nodos, si se comienza por un nodo
 * y existe un nodo con menor peso como 
 * vecino, se unen los nodos por la arista
 * y se suman sus pesos, debes responder
 * el peso final de un nodo, para cada nodo
 * como inicial.
**/

#include<bits/stdc++.h>
using namespace std;
#define int long long
#define f first
#define s second
#define db(x) cerr << #x << ": " << (x) << '\n';
#define pb push_back
#define lb lower_bound
#define up upper_bound
#define all(x) x.begin() , x.end()
#define rall(x) x.rbegin() , x.rend()
#define enl '\n'
typedef pair<int,int> ii;
typedef long double ld;
typedef unsigned long long ull;
/// Constraints:
const int maxn = 200010;
const int mod = 1000000007;
const int mod2 = 998244353;

int n, L[maxn], R[maxn], sts[maxn*4], lazy[maxn*4], val[maxn], ans[maxn], cntt, par[maxn], inv[maxn];
ii stm[maxn*4];
vector<int> g[maxn];
 
void lazyp(int nod,int l,int r){
    sts[nod] = lazy[nod] * ( r - l + 1 );
    stm[nod] = { lazy[nod] , l };
    if( l != r ){
        lazy[2*nod] = lazy[nod];
        lazy[2*nod+1] = lazy[nod];
    }
    lazy[nod] = -1;
}
 
void update(int nod,int l,int r,int x,int y,int val){
    if( lazy[nod] != -1 ) lazyp(nod,l,r);
    if( l > y || r < x ) return;
    if( l >= x && r <= y ){
        lazy[nod] = val;
        lazyp(nod,l,r);
        return;
    }
    int mi = ( l + r ) >> 1;
        update(2*nod,l,mi,x,y,val);
        update(2*nod+1,mi+1,r,x,y,val);
    sts[nod] = sts[2*nod] + sts[2*nod+1];
    stm[nod] = max( stm[2*nod] , stm[2*nod+1] );
}
 
int query_sum(int nod,int l,int r,int x,int y){
    if( lazy[nod] != -1 ) lazyp(nod,l,r);
    if( l > y || r < x ) return 0;
    if( l >= x && r <= y ) return sts[nod];
    int mi = ( l + r ) >> 1;
    return query_sum(2*nod,l,mi,x,y) + query_sum(2*nod+1,mi+1,r,x,y);
}
 
ii query_max(int nod,int l,int r,int x,int y){
    if( lazy[nod] != -1 ) lazyp(nod,l,r);
    if( l > y || r < x ) return {0, 0};
    if( l >= x && r <= y ) return stm[nod];
    int mi = ( l + r ) >> 1;
    return max( query_max(2*nod,l,mi,x,y) , query_max(2*nod+1,mi+1,r,x,y) );
}
 
void dfs(int u,int p){
    L[u] = R[u] = ++cntt;
    for( auto v : g[u] ){
        if( v != p ){
            par[v] = u;
            dfs(v,u);
            R[u] = max( R[u] , R[v] );
        }
    }
}

/**
 * idea: 
 * sea F(l, r) la respuesta para los nodos 
 * descubiertos entre los tiempos l y r de
 * un euler tour cualquiera.
 * 
 * resolvemos cualquiera nodo no resuelto 
 * con mayor valor en el rango:
 * 
 *  1. si existe un nodo vecino con menor 
 *  valor como vecino, entonces la nueva suma
 *  es mayor que cualquier valor del subarbol,
 *  por tanto la respuesta es todo el subarbol.
 * 
 *  2.  
 * 
 * 
 *  1 4
 *  2 3
 *  1 1 3
 *  1 2 2
 *  2 4 4
 *  3 3 4
 *  1 1 1 2
 *  1 3 3 3
 *  3 4 4 4
 *  2 2 2 4
 *  1 1 1 1 1
 *  2 2 2 2 2
 *  3 3 3 3 3
 *  4 4 4 4 4
 */

 

void DandC(int l, int r, int extra){
    ii mx = query_max(1,1,n,l,r);
    if( mx.f == 0 ) return;
 
    int u = inv[mx.s];
 
    bool it = 0;
    for( auto v : g[u] )
        if( val[u] > val[v] )
            it = 1;
 
    int slr = query_sum(1,1,n,l,r);
    int su =  query_sum(1,1,n,L[u],R[u]);

    ans[u] = it ? extra + slr : val[u];
 
    for( auto v : g[u] ){
        if( v != par[u] ){
            int sv = query_sum(1,1,n,L[v],R[v]);
            DandC(L[v], R[v], sv > val[u] ? extra + slr - sv : 0);
        }
    }
 
    int new_val = slr - su > val[u] ? extra + su : 0;
    update(1,1,n,L[u],R[u],0);
    DandC(l, r, new_val);
}
 
int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cout.setf(ios::fixed); cout.precision(0);
    srand(time(NULL));
 
    //freopen("a.in","r",stdin);
    //freopen("a.out","w",stdout);
 
    for(int i=0; i<maxn*4; i++)
        lazy[i] = -1;
 
    cin >> n;
 
    for(int i=1; i<n; i++){
        int u, v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
 
    dfs(1,1);
 
    for(int i=1; i<=n; i++){
        cin >> val[i];
        update(1,1,n,L[i],L[i],val[i]);
        inv[L[i]] = i;
    }
 
    DandC(1, n, 0);
 
    for(int i=1; i<=n; i++)
        cout << ans[i] << " \n"[i==n];
 
    return 0;
}

