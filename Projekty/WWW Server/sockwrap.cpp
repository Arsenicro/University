//Kamil Matuszewski 272331
//Funkcje wziete z wykladu

#include "sockwrap.h"

int Socket(int family, int type, int protocol)
{
	int n;
	if ( (n = socket(family, type, protocol)) < 0)
		ERROR ("socket error");
	return n;
}

void Bind(int fd, const struct sockaddr_in *sa, socklen_t salen)
{
	if (bind(fd, (struct sockaddr*)sa, salen) < 0)
		ERROR ("bind error");
}

void Connect(int fd, const struct sockaddr_in *sa, socklen_t salen)
{
	if (connect(fd, (struct sockaddr*)sa, salen) < 0)
		ERROR ("connect error");
}
	
int Accept(int fd, struct sockaddr_in *sa, socklen_t *salenptr)
{
	int n;
    if ( (n = accept(fd, (struct sockaddr*)sa, salenptr)) < 0) 
		ERROR ("accept error");
    return n;
}

void Listen(int fd, int backlog)
{
    if (listen(fd, backlog) < 0)
		ERROR ("listen error");
}

ssize_t Recv(int fd, char *ptr, size_t nbytes, int flags) 
{
	int n;
	if ( (n = recv(fd, ptr, nbytes, flags)) < 0)
		ERROR ("recv error");
	ptr[n] = 0;
	return n;
}

void Send(int fd, char *ptr, int nbytes, int flags) 
{
// to niekoniecznie jest blad!
	int n=send(fd, ptr, nbytes, flags);
	if (n < 0){	
		ERROR ("send error");	
	}
}

void Close(int fd)
{
	if (close(fd) < 0)
		ERROR ("close error");
}

int Select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout)
{
    int n;
    if ((n = select(nfds,readfds,writefds,exceptfds,timeout)) < 0  && (errno!=EINTR))  
        ERROR ("select error");
    return n;   
}
