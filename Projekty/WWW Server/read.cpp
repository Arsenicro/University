//Kamil Matuszewski 272331.

#include "sockwrap.h"

/*
  read_all wczytuje zapytanie i je przetwarza. Zwraca 0 jesli nic nie wczytal, 1 jesli udalo sie cos wczytac.
  Bedzie wczytywac dane, szukac odpowiedniej linijki i wyrzucac niepotrzebne.
  conn_sockfd - socket klienta
  q - struktura z danymi o zapytaniu
	
*/

bool read_all(int conn_sockfd, struct query &q){

	int n;
//recv_buffer przechowuje wczytane zapytanie
	char recv_buffer[BUFFSIZE+1];
//marker bedzie przechowywac znacznik, po ktorym rozpoznamy interesujaca nas linijke
	int marker;
//enter znajdzie koniec obecnej linijki
	int enter;
	string s;					
	n=read( conn_sockfd ,recv_buffer, BUFFSIZE);
	if(n==0) return 0;
		
//Zamieniamy wczytana linijke na stringa, by moc latwiej ja przeanalizowac
	recv_buffer[n] = 0;	
	string all=recv_buffer;
	printf("%s\n", recv_buffer);
		
//Szukamy linijki z HTTP
	marker=all.find("HTTP");
	if(marker!=-1){		
		enter=all.find("\n");
		while(enter<marker){ all.erase(0,enter+1); enter=all.find("\n"); marker=all.find("HTTP");} 
		s=all.substr(0,all.find(" "));
	//Jesli to get to ustawiamy na true
		if(s.compare("GET")==0 || s.compare("get")==0 || s.compare("Get")==0) q.get=true;
		all.erase(0,all.find(" ")+1);
		q.file=all.substr(0,all.find(" "));
		all.erase(0,all.find("\n"));
	}
//Szukamy lnijki z host
	marker=all.find("ost");
	if(marker==-1) q.hostreceived=false;
	else{
		enter=all.find("\n");
		while(enter<marker){ all.erase(0,enter+1); enter=all.find("\n"); marker=all.find("ost");} 
		all.erase(0,all.find(" ")+1);
		s=all.substr(0,all.find("\n"));
		int hp=s.find(":");
		string port= s.substr(hp+1,s.size()-hp-1);
		q.host=s.substr(0,hp);
		all.erase(0,all.find("\n"));
		q.hostreceived=true;
	}
//Szukamy linijki z connection
	marker=all.find("onnection");
	if(marker==-1) q.connectionreceived=false;	
	else{		
		enter=all.find("\n");
		while(enter<marker){ all.erase(0,enter+1); enter=all.find("\n"); marker=all.find("onnection");}
		all.erase(0,all.find(" "));
		s=all.substr(0,all.find("\n"));
	//Jesli connection=close, q.connection ustawiamy na false
		if(!s.compare("close") || !s.compare("Close") || !s.compare("CLOSE")) q.connection=false;
		q.connectionreceived=true;
	}
	return 1;
}

