#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
vector <pair<long long int, long long int> > twine;

int find1(int a, int b, long long int val){
    if(a>b) return -1;
    int h=(a+b)/2;
    if(twine[h].first>val) return find1(a, h-1, val);
    if(twine[h].first<val) return find1(h+1, b, val);
    return h;
}

int main(){

    long long int result=0;
    int number, k=0;

    scanf("%d", &number);

    for(int i=0; i<number; i++){
        long long int a,b;
        scanf("%lld %lld", &a, &b);
        twine.push_back(make_pair(a,b));
    }
    sort(twine.begin(), twine.end());

    while(k<number){

        if(twine[k].second%2!=0){
           twine[k].second-=1;
           result++;
        }
        if(twine[k].second==0) k++;
        else{
            twine[k].first*=2;
            twine[k].second/=2;
            int h=find1(k+1,twine.size()-1,twine[k].first);

            if(h!=-1){
                twine[h].second+=twine[k].second;
                k++;
            }
        }
    }
    printf("%d", result);
}