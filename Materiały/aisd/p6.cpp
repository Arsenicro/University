#include<cmath>
#include<algorithm>
#include<climits>
#include <time.h>  
#include <vector>
using namespace std;
#define Repeat(i,l,n) for(int i=l; i<(n); i++)
#define P 9999991

int myhash(int a, int m, int index){ return ((a*index)%P)%m; }
//int myrandom(){return rand()%P;}

int main(){
	
	int m,N,A=0;
	srand (time(NULL)); 
	scanf("%d", &N);
	m=N;
	int rozmiar[300000], taba[300000], grzadki[400008];
	pair<int,int> dane[N];
	Repeat(i,0,N){
		scanf(" %d", &dane[i].second);
	}

	Repeat(i,0,m){
		rozmiar[i]=0;
	}
	
	while(1){
		A++;
		Repeat(i,0,N){
			int h = myhash(A,m,dane[i].second);
			rozmiar[h]++;
		}
		long long int s=0;
		Repeat(i,0,m){
			if(rozmiar[i]==0) rozmiar[i]=1; 
			else rozmiar[i]*=2;
		}
		Repeat(i,0,m) s+=rozmiar[i];
		if(s<3*N) break; 
		Repeat(i,0,m) rozmiar[i]=0;
	}
	
	Repeat(i,0,N){
		int h = myhash(A,m,dane[i].second);
		dane[i].first=h;
	}
	sort(dane,dane+N);
	
	int c=0;
	Repeat(i,0,N){
		int a=0;
		if(rozmiar[i]==1){
			taba[i]=0;
			continue;
		} 
		bool w=false;
		while(!w){
			w=true;
			a++;
			Repeat(j,0,rozmiar[i]) grzadki[j]=0;
			while(dane[c].first<i && c<N) c++;
			int prevc=c;
			while(dane[c].first==i && c<N){
				long long int h2=dane[c].second;
				h2*=a;
				h2%=P;
				h2%=rozmiar[i];
				grzadki[h2]++;
				if(grzadki[h2]>1){
					w=false;
					break;
				}
				c++;
			}
			if(w) taba[i]=a;
			else c=prevc;
			
		}
	
	}
	
	printf("%d\n", m);
	Repeat(i,0,m) printf("%d ", rozmiar[i]);
	printf("\n%d\n", A);
	Repeat(i,0,m) printf("%d ", taba[i]);
	
	
	
	return 0;
}