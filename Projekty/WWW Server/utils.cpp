//Kamil Matuszewski 272331.

#include "sockwrap.h"

/*
	Sprawdza czy input jest poprawny. Jesli nie to przerywa wykonanie programu.
	argc - liczba podanych argumentow
	cat - nazwa katalogu (sprawzamy czy istnieje)
	port - port
*/
void checkinput(int argc, string cat, const char* port){
	if(argc!=3){
		printf("Usage: server <port> <server_root_path>\n");
		exit(1);		
	}
	
	DIR *direct = opendir(cat.c_str());
	if(direct==NULL) {
		printf("Wrong server root path\n");
		exit(1);	
	}
	closedir(direct);
	if(atoi(port)==0){
		printf("Wrong port\n");
		exit(1);
	}

}


/*
	Tworzy liste domen na podstawie katalogow w serwerze. Funkcja wzieta z internetu, przerobiona na potrzeby programu.
	dir - wektor domen
	cat - nazwa katalogu z serwerem
*/
void dirlist(vector <string> &dir, string cat){
	const char* PATH = cat.c_str();

   	DIR *direct = opendir(PATH);

   	struct dirent *entry = readdir(direct);

   	while (entry != NULL) {
       		if (entry->d_type == DT_DIR)
          		 dir.push_back(entry->d_name);

       		entry = readdir(direct);
  	}

  	closedir(direct);

	for(unsigned int i=0; i<dir.size(); i++)
		if(dir[i].compare(".")==0 || dir[i].compare("..")==0)
			dir.erase(dir.begin()+i);

}

/*
	Sprawdza poprawnosc domeny w zapytaniu. Zwraca true jesli obslugujemy taka domene (jest w katalogu z serwerem), false wpp
	dir - wekror dostepnych domen
	domain - domena z zapytania
*/

bool checkdomain(vector <string> dir, string domain){

	for(unsigned int i=0; i<dir.size(); i++)
		if(domain.compare(dir[i])==0)
			return true;

	return false;
}

/*
	rozlacza sie z klientem o danym indeksie
	client_socket - tablica klientow
	index - indeks klienta
*/

void disconnect(int (*client_socket)[2], int index){
	int sd=client_socket[index][0];
	struct sockaddr_in client_address;
	socklen_t len = sizeof(client_address);
	getpeername(sd, (struct sockaddr*)&client_address , &len);
        printf("\n\nHost disconnected, ip: %s port: %d, id:%d\n\n" , inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port), index);
	Close(sd);
       	client_socket[index][0]=0;
	client_socket[index][1]=0;
}

/*
	laczy sie z nowym klientem. Znajduje wolne miejsce w tablicy, lub wypisuje blad
	client_socket - tablica klientow
	sockfd - glowny socket
*/

void new_connect(int (*client_socket)[2], int sockfd){
		struct sockaddr_in client_address;
		socklen_t len = sizeof(client_address);
		int new_socket = Accept(sockfd, &client_address, &len);
		char ip_address[20];
		inet_ntop (AF_INET, &client_address.sin_addr, ip_address, sizeof(ip_address));
		printf("\n\nNew connection, ip: %s port:%d\n" ,ip_address, ntohs(client_address.sin_port));
		for (int i = 0; i < max_clients; i++) {
            		//Jesli pozycja jest pusta dodajemy tam socket
             		if( client_socket[i][0] == 0 ){
                    		client_socket[i][0] = new_socket;
                    		printf("Adding to list of sockets as %d\n\n" , i);
                    		break;
                	}
			//Jesli jestesmy w ostatnim przejsciu i nie udalo sie nam zapisac socketa, to zwracamy blad
			if(i==max_clients-1){
				printf("\n\nServer is busy!\n\n");
				ifstream f("errors/busy.html", ios::binary);
				long size = f.tellg();
				f.seekg( 0, std::ios::end );
				size = f.tellg() - size;
				char sbuf[30];
				sprintf(sbuf, "%ld", size);
				char buf[size+1];
				f.seekg (0, ios::beg);
				f.read (buf, size);		
				f.close();
				Send(new_socket,buf,size,0);
				Close(new_socket);
			}
            	}
}

/*
	laczy sie z socketem na dany port
	port - port
*/

int new_socket(char * port){
	
	int opt=1;
	int sockfd = Socket(AF_INET, SOCK_STREAM, 0);
	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0) ERROR ("setsockopt error");
	struct sockaddr_in server_address;
	bzero (&server_address, sizeof(server_address));
	server_address.sin_family      = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port        = htons(atoi(port));
	Bind (sockfd, &server_address, sizeof(server_address));
	Listen (sockfd, 64);    
	return sockfd;
}

