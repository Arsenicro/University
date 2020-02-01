#include<math.h>
#include<algorithm>
#include<iostream>
#include<vector>
#include<climits>
using namespace std;
#define Repeat(i,l,n) for(unsigned int i=l; i<(n); i++)
vector < pair<int,int> > points;
struct solv{
    double distance;
    pair<int,int> a;
    pair<int,int> b;
    pair<int,int> c;
};


bool pairCompare(const pair<int, int>& firstElem, const pair<int, int>& secondElem) {
  return firstElem.second < secondElem.second;
}

long long int power(long long int a){
    return a*a;
}

double dist(pair<long long int, long long int> a, pair<long long int, long long int> b){
    return sqrt(power(a.first-b.first) + power(a.second-b.second));
}

double triangle(pair<int,int> a,pair<int,int> b, pair<int,int> c){
    return dist(a,b)+dist(a,c)+dist(c,b);

}
solv minSolv(solv A, solv B){
    return (A.distance<B.distance) ? A : B;
}

solv brute(vector < pair<int,int> > foo){
    solv s;
    s.distance=INFINITY;
    Repeat(k,0,foo.size())
        Repeat(i,0,foo.size()){
           Repeat(j,0,foo.size()){
               if (j!=i && j!=k && i!=k){
                    solv s2;
                    s2.distance=triangle(foo[k], foo[i], foo[j]);
                    s2.a=foo[k];
                    s2.b=foo[i];
                    s2.c=foo[j];
                    s=minSolv(s,s2);
               }
            }
        }

    return s;
}

solv merg(vector < pair<int,int> > foo, double p){
    vector < pair<int,int> > aux;
    aux.clear();
    solv res;
    res.distance=INFINITY;
    unsigned int size = foo.size();
    Repeat(i,0,size){
        aux.clear();
        aux.push_back(foo[i]);
        unsigned int j=i+1;
        while(foo[j].second <= foo[i].second+p && j < size) {
            aux.push_back(foo[j]);
            j++;
        }

        if(aux.size()>=3){
            res=minSolv(res, brute(aux));
        }
    }
    return res;

}

solv minTriangle(int s, int e){
    solv low;
    unsigned int n=e-s;
    if(n<3) low.distance=INFINITY;
    else{
        unsigned int m=s+n/2;
        int xm=(points[m].first+points[m+1].first)/2;
        solv L=minTriangle(s,m);
        solv R=minTriangle(m,e);
        low=minSolv(L,R);
        double p=low.distance/2;
        vector < pair<int,int> > foo;
        foo.clear();
        int start=m;
        while(points[start].first>=(xm-p) && points[start].first<=(xm+p) && start>=s) {
            foo.push_back(points[start]);
            start--;
        }

        start=m+1;
        while(points[start].first>=(xm-p) && points[start].first<=(xm+p) && start<points.size() && start<e){
            foo.push_back(points[start]);
            start++;
        }
        sort(foo.begin(), foo.end(), pairCompare);

        low=minSolv(low, merg(foo,p));
    }
    return low;
}

int main(){
    unsigned int n;
    cin >> n;
    points.clear();
    Repeat(i,0,n){
        int a, b;
        cin >> a >> b;
        points.push_back(make_pair(a,b));
    }
    sort(points.begin(), points.end());
    solv s = minTriangle(0,n);
    vector < pair<int,int> > solve;
    solve.clear();
    solve.push_back(s.a);
    solve.push_back(s.b);
    solve.push_back(s.c);
    sort(solve.begin(),solve.end());
    Repeat(i,0,3) cout << solve[i].first << " " << solve[i].second << endl;

return 0;
}