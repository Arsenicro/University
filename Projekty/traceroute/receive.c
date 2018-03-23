#include "traceroute.h"

/*
Kamil Matuszewski, 272331.
*/

/*
Funkcja odbiera wszystkie pakiety. Zwraca 1, jeśli dotarliśmy do celu, 0 jeśli jesteśmy w pakiecie pośrednim, -1 jeśli nastąpił błąd
sockfd - gniazdo
ttl - ttl (lol)
id - id (lol)
ireply - liczba odpowiedzi
responsetime - średni czas odpowiedzi, -1 w przypadku braku odpowiedzi od któregoś pakietu
treply - tablica trzech odpowiedzi (wysyłamy trzy pakiety)

rec - przechowuje odpowiedź recsingle
ireply - liczba wysłanych pakietów
totaltime - łączny czas wysłania wszystkich trzech pakietów
t - czas-odnośnik do mierzenia reszty czasów
st - czas wysłania jednego pakietu
resp - czas wysłania jednego pakietu w ms

W pętli odbieramy pakiety, dopóki nie przekroczymy czasu/nie odbierzemy wszystkich trzech. Pod koniec odpowiednio modyfikujemy zmienne i zwracamy odpowiednią wartość (patrz wyżej).
Co do liczenia czasu - to ustawiamy sobie czas główny (t), od którego będziemy liczyć czas odebrania pakietu (st). Będziemy to robić pod koniec przejścia pętli (rec nie czeka więc liczy się błyskawicznie, pętla while będzie przechodzić dopóki nie odbierze pakietu, a wtedy czas będzie już policzony). Nie jest to idealne rozwiązanie, ale według mnie najczytelniejsze.
*/
int recall(int sockfd, int ttl, int id, int *ireply, int *responsetime, struct in_addr *treply){	
	
	int rec;
	int totaltime=0;	
	struct timespec t,st;
	clock_gettime(CLOCK_MONOTONIC, &t);
	int resp = 0;

	while(*ireply < 3 && resp<1000){			
		rec=recsingle(sockfd, ttl, id, treply+*ireply);

		if(rec<0) return -1;
		if(rec!=2) {
			(*ireply)++;	
			totaltime+=resp;			
		}		
		clock_gettime(CLOCK_MONOTONIC, &st);	
		resp = (st.tv_sec - t.tv_sec)*1000 + (st.tv_nsec - t.tv_nsec)/1000000;	
	}
	if(*ireply<3) *responsetime = -1;	 
	else *responsetime=totaltime/3;
	
	if(rec==1) return true;

	return false;
}


/*
Funkcja odbiera jeden pakiet. Zwraca 0 jeśli jesteśmy w pakiecie pośrednim, 1 jeśli w pakiecie docelowym, 2 jeśli pakiet nieaktualny/nie nasz/gniazdo puste, -1 jeśli nastąpił błąd
sockfd - gniazdo
ttl - ttl (lol)
id - id (lol)
addr - adres pod który zapiszemy obecny pakiet

Jeśli otrzymaliśmy błąd inny niż EAGIN lub EWOULDBLOCK to zwracamy -1. wpp odbieramy pakiet, i zwracamy odpowiednią wartość w zależności czy to pakiet pośredni, docelowy, czy brak pakietu.
*/
int recsingle(int sockfd, int ttl, int id, struct in_addr *addr)
{ 	
	u_int8_t buffer[IP_MAXPACKET+1];

	if(recv(sockfd, buffer, IP_MAXPACKET, MSG_DONTWAIT)<0 && (errno != EAGAIN || errno !=  EWOULDBLOCK)){
		fprintf(stderr, "recv error: %s\n", strerror(errno));
		return -1;
	}

	struct ip *ipp = (struct ip *)buffer;
	struct icmp *icmpp = (struct icmp *)((uint8_t *)ipp + (*ipp).ip_hl * 4);
	
	//Jeśli ICMP_TIME_EXCEEDED musimy przesunąć icmp o 64 bity = 8 bajtów https://www.frozentux.net/iptables-tutorial/chunkyhtml/x281.html
	if(icmpp->icmp_type == ICMP_TIME_EXCEEDED){
		struct ip *ipp1 = (struct ip *)((uint8_t *)icmpp + 8);
		struct icmp *icmpp1 = (struct icmp *)((uint8_t *)ipp1 + (*ipp1).ip_hl * 4);
		if(icmpp1->icmp_seq==ttl && icmpp1->icmp_id==id){
			*addr=ipp->ip_src;
			return 0;
		}
	}else if(icmpp->icmp_type == ICMP_ECHOREPLY && icmpp->icmp_seq==ttl && icmpp->icmp_id==id){		
		*addr=ipp->ip_src;
		return 1;
	}

	return 2;
}
