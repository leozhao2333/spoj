#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int N=10005;
int dep[N],top[N],size[N],son[N],fa[N],id[N],idx,val[N];
int n;
vector<int>g[N];
struct edge
{
	int u,v,val;
	void read(){scanf("%d%d%d",&u,&v,&val);}
}e[N];
void dfs1(int u,int f,int d)
{
	dep[u]=d;
	size[u]=1;
	son[u]=0;
	fa[u]=f;
	for (int i=0;i<g[u].size();i++)
	{
		int v=g[u][i];
		if (v==f)continue;
		dfs1(v,u,d+1);
		size[u]+=size[v];
		if (size[son[u]]<size[v])
		 son[u]=v;
	}
}
void dfs2(int u,int tp)
{
	top[u]=tp;
	id[u]=++idx;
	if (son[u])dfs2(son[u],tp);
	for (int i=0;i<g[u].size();i++)
	{
		int v=g[u][i];
		if (v==fa[u]||v==son[u])continue;
		dfs2(v,v);
	}
}
#define lson(x)((x<<1)+1)
#define rson(x)((x<<1)+2)
const int INF=0x3f3f3f3f;
struct node
{
	int l,r,val;
}node[N*4];
void pushup(int x){node[x].val=max(node[lson(x)].val,node[rson(x)].val);}
void build(int l,int r,int x=0)
{
	node[x].l=l;node[x].r=r;
	if (l==r)
	{
		node[x].val=val[l];
		return;
	}
	int mid=(l+r)/2;
	build(l,mid,lson(x));
	build(mid+1,r,rson(x));
	pushup(x);
}
void add(int v,int val,int x=0)
{
	if (node[x].l==node[x].r)
	{
		node[x].val=val;
		return;
	}
	int mid=(node[x].l+node[x].r)/2;
	if (v<=mid)add(v,val,lson(x));
	if (v>mid)add(v,val,rson(x));
	pushup(x);
}
int query(int l,int r,int x=0)
{
	if (node[x].l>=l&&node[x].r<=r)
	return node[x].val;
	int mid=(node[x].l+node[x].r)/2;
	int ans=0;
	if (l<=mid)ans=max(ans,query(l,r,lson(x)));
	if (r>mid)ans=max(ans,query(l,r,rson(x)));
	return ans;
}
int gao(int u,int v)
{
	int tp1=top[u],tp2=top[v];
	int ans=0;
	while(tp1!=tp2)
	{
		if (dep[tp1]<dep[tp2])
		{
			swap(tp1,tp2);
			swap(u,v);
		}
		ans=max(query(id[tp1],id[u]),ans);
		u=fa[tp1];
		tp1=top[u];
	}
	if (u==v)return ans;
	if (dep[u]>dep[v])swap(u,v);
	ans=max(query(id[son[u]],id[v]),ans);
	return ans;
}
int T;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		idx=0;
		for (int i=1;i<=n;i++)g[i].clear();
		for (int i=1;i<n;i++)
		{
			e[i].read();
			g[e[i].u].push_back(e[i].v);
			g[e[i].v].push_back(e[i].u);
		}
		dfs1(1,0,1);
		dfs2(1,1);
		char Q[10];
		for (int i=1;i<n;i++)
		{
			if(dep[e[i].u]<dep[e[i].v])swap(e[i].u,e[i].v);
			val[id[e[i].u]]=e[i].val;
		}
		build(1,idx);
		int a,b;
		while(scanf("%s",Q))
		{
			if (Q[0]=='D')break;
			scanf("%d%d",&a,&b);
			if (Q[0]=='Q')printf("%d\n",gao(a,b));
			if (Q[0]=='C')add(id[e[a].u],b);
		}
	}
}
