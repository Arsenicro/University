//Kamil Matuszewski 272331.

#include "sockwrap.h"

/*
	Sprawdza jaka odpowiedz wyslac
	conn_sockfd - socket klienta
	q - struktura z danymi o zapytaniu
	dir - wektor domen
*/

void answer(int conn_sockfd, struct query &q, vector <string> dir){
	
//Jeśli nie otrzymalismy hosta, connection, get badz port byl niepoprawny zwracamy 501
	if(!q.hostreceived || !q.connectionreceived || !q.get || !q.portcorrect) answer_501(conn_sockfd);
	else{
		
	//Jesli domena byla niepoprawna (nie nalezy do nas) zwracamy 403
		if(!checkdomain(dir, q.host)) answer_403(conn_sockfd);
		else{
			
		//query bedzie przechowywac	sciezke do pliku do ktorego sie odwolujemy - katalog serwera/domena(host)/plik
			string query=q.cat;
			query.append(q.host);
			query.append(q.file); 
			
		//Informacje o pliku. Jesli s=-1 to plik nie istnieje
			struct stat file_stat; 
			int s=stat(query.c_str(), &file_stat);
		//Zakaz odwolywania sie do linkow z ../ w srodku
			if(query.find("../")!=string::npos) answer_501(conn_sockfd);
			else{
			//ISDIR zwraca 1 jesli dany plik jest katalogiem, wtedy zwracamy 301
				if (s!=-1 && S_ISDIR(file_stat.st_mode)) answer_301(conn_sockfd, q);
			//ISREG zwraca 1 jesli dany plik jest jakims plikiem, zwtacamy 200
				else if (s!=-1 && S_ISREG(file_stat.st_mode)) answer_200(conn_sockfd,q,query);
			//Jesli plik nie istnieje zwracamy 404
				else if(s==-1) answer_404(conn_sockfd);
			//Jesli nie zachodzi zadne z powyzszych to zapytanie bylo niepoprawne - zwracamy 501
				else answer_501(conn_sockfd);
			}
		}
	}
}

/*
	Tworzy odpowiedz 501, wyswietla odpowiedni plik.
	conn_sockfd - socket klienta
*/

void answer_501(int conn_sockfd){
	string answ="HTTP/1.1 501 Forbidden\n\n";
	ifstream f("errors/501.html", ios::binary);
	long size = f.tellg();
	f.seekg( 0, std::ios::end );
	size = f.tellg() - size;
	char sbuf[30];
	sprintf(sbuf, "%ld", size);
	char buf[size+1];
	f.seekg (0, ios::beg);
	f.read (buf, size);		
	f.close();

	printf("%s", answ.c_str());
		
	Send(conn_sockfd,(char*)answ.c_str(),answ.size(),0);
	Send(conn_sockfd,buf,size,0);
}

/*
	Tworzy odpowiedz 404, wyswietla odpowiedni plik.
	conn_sockfd - socket klienta
*/

void answer_404(int conn_sockfd){
	string answ="HTTP/1.1 404 Not Found\n\n";
	ifstream f("errors/404.html", ios::binary);
	long size = f.tellg();
	f.seekg( 0, std::ios::end );
	size = f.tellg() - size;
	char sbuf[30];
	sprintf(sbuf, "%ld", size);
	char buf[size+1];
	f.seekg (0, ios::beg);
	f.read (buf, size);		
	f.close();

	printf("%s", answ.c_str());

	Send(conn_sockfd,(char*)answ.c_str(),answ.size(),0);
	Send(conn_sockfd,buf,size,0);
}

/*
	Tworzy odpowiedz 403, wyswietla odpowiedni plik.
	conn_sockfd - socket klienta
*/

void answer_403(int conn_sockfd){
	string answ="HTTP/1.1 403 Forbidden\n\n";
	ifstream f("errors/403.html", ios::binary);
	long size = f.tellg();
	f.seekg( 0, std::ios::end );
	size = f.tellg() - size;
	char sbuf[30];
	sprintf(sbuf, "%ld", size);
	char buf[size+1];
	f.seekg (0, ios::beg);
	f.read (buf, size);		
	f.close();

	printf("%s", answ.c_str());
		
	Send(conn_sockfd,(char*)answ.c_str(),answ.size(),0);
	Send(conn_sockfd,buf,size,0);
}

/*
	Tworzy odpowiedz 301, przekierowuje do strony index.html w tym katalogu
	conn_sockfd - socket klienta
	q - struktura z danymi o zapytaniu (w szczegolnosci gostem, portem i plikiem)
*/

void answer_301(int conn_sockfd, struct query q){
	string answ="HTTP/1.1 301 Moved Permanently\nLocation: ";
	answ.append("http://");
	answ.append(q.host);
	answ.append(":");
	answ.append(q.port);
	answ.append(q.file);
	if((q.file).compare((q.file).size()-1, 1, "/")!=0) answ.append("/");
	answ.append(index_html);
	answ.append("\n\n");
			
	printf("%s", answ.c_str());
	Send(conn_sockfd,(char*)answ.c_str(),answ.size(),0);
}

/*
	Tworzy odpowiedz 200. Wyswietla plik z zapytania
	conn_sockfd - socket klienta
	q - struktura z danymi o zapytaniu
	query - sciezka do pliku do ktorego sie odwolujemy
*/

void answer_200(int conn_sockfd, struct query q, string query){
	
	int ty=(q.file).find(".");
	string type=(q.file).substr(ty+1,(q.file).size()-ty+1);
	int j=0;
	while(j<7){
		if(type.compare(extensions[j].ext)==0) break;
		j++;
	}
	
	ifstream f(query, ios::binary);
	long size = f.tellg();
	f.seekg( 0, std::ios::end );
	size = f.tellg() - size;
	char sbuf[30];
	sprintf(sbuf, "%ld", size);
	char buf[size+1];
	f.seekg (0, ios::beg);
	f.read (buf, size);		
	f.close();

	string answ="HTTP/1.1 200 OK\nContent-Type: ";
	answ.append(extensions[j].type);
	answ.append("\nContent-Length: ");
	answ.append(sbuf);
	answ.append("\n\n");
	
	printf("%s", answ.c_str());
	
	Send(conn_sockfd,(char*)answ.c_str(),answ.size(),0);
	Send(conn_sockfd,buf,size,0);

}
