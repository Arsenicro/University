#ifndef _sockwrap_h
#define _sockwrap_h

#include <arpa/inet.h>
#include <cassert>
#include <cstring>
#include <errno.h>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/stat.h> 
#include <unistd.h>
#include <dirent.h>

#define ERROR(str) { fprintf(stderr, "%s: %s\n", str, strerror(errno)); exit(1); }
#define index_html "index.html"
#define BUFFSIZE 10000
#define max_clients 30
#define TIMEOUT 1
using namespace std;

//Funkcje z wykładu
int Socket(int family, int type, int protocol);
void Bind(int fd, const struct sockaddr_in *sa, socklen_t salen);
void Connect(int fd, const struct sockaddr_in *sa, socklen_t salen);
int Accept(int fd, struct sockaddr_in *sa, socklen_t *salenptr);
void Listen(int fd, int backlog);
ssize_t Recv(int fd, char *ptr, size_t nbytes, int flags);
void Send(int fd, char *ptr, int nbytes, int flags);
void Close(int fd);
int Select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
int ReadBufferedByte (int fd, char* c, struct timeval* tv);
int ReadLine (int fd, char* buff, int len);

//Moje funkcje

//utils.cpp
void checkinput(int argc, string cat, const char* port);
void dirlist(vector <string> &dir, string cat);
bool checkdomain(vector <string> dir, string domain);
void disconnect(int (*client_socket)[2], int index);
void new_connect(int (*client_socket)[2], int sockfd);
int new_socket(char * port);

//read.cpp
bool read_all(int conn_sockfd, struct query &q);

//answer.cpp
void answer(int conn_sockfd, struct query &q, vector <string> dir);
void answer_200(int conn_sockfd, struct query q, string query);
void answer_301(int conn_sockfd, struct query q);
void answer_403(int conn_sockfd);
void answer_404(int conn_sockfd);
void answer_501(int conn_sockfd);

struct {
	string ext;
	string type;
} extensions [] = {
	{"txt","text/html" },
	{"html","text/html" },
	{"css", "text/css" }, 
	{"jpg", "image/jpg" }, 
	{"jpeg","image/jpeg"},
	{"png", "image/png" },  
	{"pdf","application/pdf"},
	{"", "application/octet-stream"}};

struct query{
	char *port;
	string file;
	string host;
	string cat;
	bool hostreceived;
	bool connection;
	bool connectionreceived;
	bool get;
	bool portcorrect;
	bool timeout;

};

#endif
