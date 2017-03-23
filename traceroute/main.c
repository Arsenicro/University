#include "traceroute.h"

/*
Kamil Matuszewski, 272331.

Program traceroute napisany na zajęcia z sieci komputerowych (semestr letni 2016). Szczegóły zadania w pliku p1 pdf.
*/

/*
Na początku sprawdzamy czy podano ip. Jeśli nie to tworzymy gniazdo - sprawdzamy czy nam się udało, jeśli nie, kończymy. Jeśli wszystko się powiodło, konwertujemy ip na chara. Funkcja inet_pton zwraca 0 jeśli nie udało się jej przekonwertować - sprawdzamy także to. Wywołujemy funkcję traceroute, która jest główną funkcją naszego programu.
*/

int main(int argc, char *argv[]){

	if(argc!=2) {
		printf("Podaj tylko IP!\n");
		return 0;	
	}
	
	int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

	if (sockfd < 0) {
		fprintf(stderr, "socket error: %s\n", strerror(errno)); 
		return EXIT_FAILURE;
	}

	struct sockaddr_in addr;
	
	//Konwertowanie IP  	
	
	addr.sin_port = htons (7);
  	addr.sin_family = AF_INET;
  	if(inet_pton(AF_INET, argv[1], &(addr.sin_addr))==0){
		printf("Złe IP!\n");
		return EXIT_FAILURE;
	}
	
	if(traceroute(sockfd, &addr)<0) return EXIT_FAILURE;	

	return 0;
}
