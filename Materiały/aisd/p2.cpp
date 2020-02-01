#include<stdio.h>
#include<math.h>
#include <algorithm>
#include <iostream>
using namespace std;

long long int siedem(char a){
    if (a=='0') return 1;
    if (a=='1') return 7;
    if (a=='2') return 49;
    if (a=='3') return 343;
    if (a=='4') return 2401;
    if (a=='5') return 16807;
    if (a=='6') return 117649;
    if (a=='7') return 823543;
    if (a=='8') return 5764801;
    if (a=='9') return 40353607;
    return -1;
}

void gora(char **tab, long long int **tab2, int k, int wiersz){
    int wiersz2 = (wiersz)%3;
    wiersz=(wiersz-1)%3;

    for(int i=0;i<k;i++){
        long long int pot=siedem(tab[wiersz][i]);
        if (i < 2 && i > k-3) return;
        else if(i<2 && i<k-2) tab2[wiersz][i]=max(tab2[wiersz][i],pot+tab2[wiersz2][i+2]);
        else if(i>k-3) tab2[wiersz][i]=max(tab2[wiersz][i],pot+tab2[wiersz2][i-2]);
        else tab2[wiersz][i]=max(tab2[wiersz][i],pot+max(tab2[wiersz2][i-2],tab2[wiersz2][i+2]));

    }
}
void dol(char **tab, long long int **tab2, int k, int wiersz){

    int wiersz2 = (wiersz-2)%3;
    wiersz = wiersz%3;
    for(int i=0;i<k;i++){
        long long int pot=siedem(tab[wiersz][i]);
        if(i<1)tab2[wiersz][i]=pot+tab2[wiersz2][i+1];
        else if(i>k-2) tab2[wiersz][i]=pot+tab2[wiersz2][i-1];
        else tab2[wiersz][i]=pot+max(tab2[wiersz2][i-1],tab2[wiersz2][i+1]);

    }
}

long long int maksimum(long long int **tab2, int k, int w){
    long long int m=tab2[w][0];
    for(int i=1; i<k; i++){
        if(m<tab2[w][i]) m=tab2[w][i];
    }
    return m;
}

int main(){
	char **tab;
	long long int **tab2;
    int w, k;
    scanf("%d %d", &w, &k);
    getchar();
    tab=new char * [3];
	for (int i=0;i<3;i++)
		tab[i]=new char[k];
	tab2=new long long int * [3];
	for (int i=0;i<3;i++)
		tab2[i]=new long long int[k];

    fgets(tab[0], k+2, stdin);
    fgets(tab[1], k+2, stdin);
    fgets(tab[2], k+2, stdin);

	for(int i=0; i<k; i++){
        tab2[0][i] = siedem(tab[0][i]);
        tab2[1][i] = 0;
        tab2[2][i] = 0;
	}

	for(int i=2; i<w-1; i++){
        dol(tab,tab2,k,i);
        gora(tab,tab2,k,i);
        fgets(tab[(i+1)%3],k+2,stdin);
	}
	dol(tab,tab2,k,w-1);

cout << maksimum(tab2,k,(w-1)%3);



return 0;
}