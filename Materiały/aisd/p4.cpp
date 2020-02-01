#include<cmath>
#include<algorithm>
#include<vector>
#include<climits>
#include<unordered_map>
using namespace std;
#define Repeat(i,l,n) for(int i=l; i<(n); i++)
vector < pair<pair<int, int>,int> > carrots;
vector <pair<int,int> >tree;
unordered_map<int,int> Func;

int Pov, Col;

struct compare{
	bool operator()(const pair<pair<int,int>,int> &left,const pair<pair<int,int>,int> &right){ 
		return left.first.second < right.first.second || ((left.first.second == right.first.second) && left.first.first < right.first.first);
	}
};

void Map(int k){
	Repeat(i,0,k){
		if(Func[carrots[i].first.first]==0){
			Col++;
			Func[carrots[i].first.first]=Col;
		}
	}
}

void FindPov(){
	Pov=1;
	while(Pov<Col) Pov*=2;
}

void Insert(int x, int val, int id){
	int v=Pov+x;
	tree[v].first=val;
	tree[v].second=id;
	while(v!=1){
		v/=2;
		if(tree[2*v].first > tree[2*v+1].first){
			tree[v].first=tree[2*v].first;
			tree[v].second=tree[2*v].second;
		}else{
			tree[v].first=tree[2*v+1].first;
			tree[v].second=tree[2*v+1].second;
		}
	}
}

pair<int,int> Val(int a, int b){
	int v1 = Pov+a, v2 = Pov+b, answ=tree[v1].first, id=tree[v1].second;
	if(v1!=v2) 
		if(tree[v2].first>answ){
			answ=tree[v2].first;
			id=tree[v2].second;
		}
	while(v1/2!=v2/2){
		
		if(v1%2==0) 
			if(tree[v1+1].first>answ){
				answ=tree[v1+1].first;
				id=tree[v1+1].second;
		}
		if(v2%2==1) 
			if(tree[v2-1].first>answ){
				answ=tree[v2-1].first;
				id=tree[v2-1].second;
		}
		v1/=2;
		v2/=2;
	}
	return {answ,id};
}

int main(){
    int n, m, k;
	vector <int> prev;
	vector < pair<int,int> > answ;
	scanf("%d %d %d", &m, &n, &k);
    carrots.resize(k);
	prev.resize(k);
	Repeat(i,0,k){
        int a,b,c;
		scanf("%d %d %d", &a, &b, &c);
        carrots[i].first={a,b};
		carrots[i].second=c;
    }
	sort(carrots.begin(), carrots.end());
	Map(k);
	sort(carrots.begin(), carrots.end(), compare());
	FindPov();
	tree.resize(2*Pov+10, {0,-1});
	Repeat(i,0,carrots.size()) {
		int x=Func[carrots[i].first.first];
		pair<int,int> v=Val(1,x);
		Insert(x, v.first+carrots[i].second, i);
		prev[i]=v.second;
	}
	pair<int,int> v = Val(1,Col);
	int p=v.second;
	while(p!=-1){
		answ.push_back(carrots[p].first);
		p=prev[p];
	}
	
	printf("%d\n%d\n", v.first,answ.size());
	
	for(int i=answ.size()-1; i>=0; i--)
		printf("%d %d\n", answ[i].first, answ[i].second);
	
	
    return 0;
	}