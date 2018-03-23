#include "traceroute.h"

/*
Kamil Matuszewski, 272331.
*/

/*
sockfd - gniazdo
addr - adres na który będziemy wysyłać

id - id pakietu który będziemy wysyłać i odbierać - będzie to id procesu 
treply - przetrzymuje trzy oderane pakiety
responsetime - średni czas odpowiedzi 
ireply - liczba odpowiedzi

Dla kolejnych ttl wysyłamy po trzy pakiety i na bierząco wypisujemy - sprawdzamy też, czy coś przypadkiem nie poszło nie tak - jeśli nastąpił błąd, w celu uniknięcia komplikacji kończymy program. Jeśli dodarliśmy do adresu docelowego - przerywamy.
*/
int traceroute(int sockfd, struct sockaddr_in *addr){
	
	int id = getpid();

	for(int i=1; i<31; i++){
		struct in_addr treply[3];
		int responsetime=0;
		int ireply=0;
		error(sendsocks(sockfd, i, id, *addr));
		int end = recall(sockfd, i, id, &ireply, &responsetime, treply);
		error(end);
		print(i, &ireply, &responsetime, treply);	
		
		if(end) break;	
	}		
	return 0;
}

/*
Tu mamy funkcję wypisującą.
ttl - ttl
ireply - liczba odpowiedzi
responsetime - średni czas odpowiedzi LUB -1 gdy któraś z odpowiedzi nie nadeszła
treply - tablica z adresami ip które nam odpowiedziały

Jeśli ttl<10 to wypisujemy kosmetyczną spację. Tworzymy stringi do przetrzymywania trzech ip, w zależności od tego czy są różne czy się powtarzają, wypisujemy tak, by nie wypisywać kilku tych samych. Jeśli nie otrzymaliśmy żadnej odpowiedzi zwracamy -1, w przeciwnym przypadku, jeśli czas odpowiedzi to -1, wypisujemy znaki zapytania (jak w treści nakazano), jeśli nie to wypisujemy średni czas.
*/
void print(int ttl, int *ireply, int *responsetime, struct in_addr *treply){

	if(ttl<10) printf(" "); 	
	printf(" %d.\t", ttl);		

	char ip1[20], ip2[20], ip3[20];
	inet_ntop(AF_INET, &(treply[0]),ip1,sizeof(ip1));
	inet_ntop(AF_INET, &(treply[1]),ip2,sizeof(ip2));
	inet_ntop(AF_INET, &(treply[2]),ip3,sizeof(ip3));
	
	if(*ireply == 0) printf("*");
	else{
		printf("%s", ip1);
		if(strcmp(ip1,ip2)!=0 && *ireply>1){
			printf(" %s", ip2);
		}
		if(strcmp(ip1,ip3)!=0 && strcmp(ip2,ip3)!=0 && *ireply>2) {
			printf(" %s", ip3);
		}

		if(*responsetime<0) printf("\t???");	
		else printf("\t%dms", *responsetime);
	}
	printf("\n");
}
