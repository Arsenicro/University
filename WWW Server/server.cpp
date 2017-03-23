//Kamil Matuszewski 272331.
//Funkcje InitBuffer, ReadBufferedByte, ReadLine, fragment main oraz cały plik socwarp.cpp wziety z wykładu. Nie odpowiadam za ich poprawnosc

/*
Prosty server WWW napisany na zajęcia z sieci komputerowych (semestr letni 2016). Szczegóły zadania w pliku p4.pdf
*/

#include "sockwrap.h"


/*
argv[1] - port
argv[2] - katalog serwera
*/
int main(int argc, char** argv){

//cat - nazwa katalogu z serwerem w stringu. Nazwa katalogu musi konczyc sie na "/", wiec jesli sie nie konczy, dopisujemy. 

    	int client_socket[30][2];
	char* port;

	string cat=argv[2]; 
	if(cat.compare(cat.size()-1,1,"/")!=0) cat.append("/");
	port=argv[1];

//sprawdzamy poprawnosc wejscia
	checkinput(argc,cat,port);

//Zerowanie tablicy klientow
	for (int i=0; i<max_clients; i++){ client_socket[i][0]=0; client_socket[i][1]=0; }
	
//Laczymy sie z socketem	
	int sockfd = new_socket(port); 
   
//Tworzymy liste dostepnych domen na podstawie katalogow w katalogu z serwerem   
	vector <string> dir;
	dirlist(dir,cat);
	
	printf("Hello!\n");

	while (1) {

	//Czyszczenie zbioru socketow i dodawanie do niego socketa glownego
		int sd;
		fd_set readfds;
		FD_ZERO(&readfds);
		FD_SET(sockfd, &readfds);
      		int max_sd = sockfd;
		
		struct timeval time;
		
	//Dodawanie pozostalych socketow (jesli sa one niepuste)
		for (int i=0; i<max_clients; i++){
			sd = client_socket[i][0];
			if(sd > 0)
                		FD_SET( sd , &readfds);
			if(sd > max_sd)
               			max_sd = sd;
		}
	//Ustawianie timeout czasu czekania
		struct timeval tv; tv.tv_sec = TIMEOUT; tv.tv_usec = 0;
		if(Select( max_sd + 1 , &readfds , NULL , NULL , &tv)==0)
			for(int i=0; i<max_clients; i++)
				if(client_socket[i][0]>0)
					disconnect(client_socket, i);	
				
							
	//Jesli cos sie dzieje z glownym socketem, to mamy nowe polaczenie
		if (FD_ISSET(sockfd, &readfds))
			new_connect(client_socket, sockfd);
		
	//Dla kazdego z klientow sprawdzamy, czy cos sie z nim dzieje
		for (int i = 0; i < max_clients; i++){
			sd = client_socket[i][0];
			if (FD_ISSET( sd , &readfds)){
				
			/*
				Inicjacja zmiennych - struktura q przechowuje wszystkie dane o wczytanym zapytaniu. Ma pola:
				port - port z ktorym sie laczymy
				file - plik ktorego dotyczy zapytanie
				host - host do ktorego sie odwolujemy
				cat - nazwa katalogu z serwerem
				connection - mowi czy utrzymujemy polaczenie
				hostreceived - czy w zapytaniu otrzymalismy host
				connectionreceived - czy w zapytaniu otrzymalismy connection
				get - czy metoda to get
				portcorrect - czy port jest poprawny, tj zgodny z tym na ktorym nasluchujemy oraz czy jest liczba.
			*/
			
				query q;	
				q.port=argv[1];
				q.cat=cat;
				q.connection=true;
				q.hostreceived=false;
				q.connectionreceived=false;
				q.get=false;
				q.portcorrect=true;
				q.timeout=false;
				
			//Ustawiamy timeout uzycia socketa				
				gettimeofday(&time,NULL);
				client_socket[i][1]=time.tv_sec;
				
			//read_all zwraca 0 jesli nic nie przeczytalismy
				if(!read_all(sd, q))
					disconnect(client_socket, i);		
			//Jesli wczytalismy zapytanie, obslugujemy	
				else{ 
					printf("\n");
					answer(sd, q, dir);
				}
			//Jesli klient zakonczyl polaczenie, wylogowujemy
				if(q.connection==false)
					disconnect(client_socket, i);
			}
		//Zamykanie socketow z przekroczonym timeoutem
			gettimeofday(&time,NULL);
			if(client_socket[i][0]>0 && client_socket[i][1]!=0)
				if(time.tv_sec-client_socket[i][1]>= TIMEOUT)
					disconnect(client_socket, i);
		}


	}
		
}
