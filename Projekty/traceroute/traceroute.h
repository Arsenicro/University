#ifndef traceroute_h
#define traceroute_h

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <stdbool.h>
#include <time.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include <netinet/ip_icmp.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define assert(expr)
#define error(sth) if(sth<0) return -1

//Funkcja główna
int traceroute(int sockfd, struct sockaddr_in *addr);

//Pobieranie pid procesu
pid_t getpid(void);

//Wysyłanie
int sendsocks(int sockfd, int ttl, int pid, struct sockaddr_in addr);
int sendsock(int sockfd, int ttl, int pid, struct sockaddr_in addr);

//Odbieranie
int recsingle(int sockfd, int ttl, int id, struct in_addr *addr);
int recall(int sockfd, int ttl, int id, int *ireply, int *responsetime, struct in_addr *treply);

//Funkcja z wykładu - suma kontrolna
u_int16_t compute_icmp_checksum (const void *buff, int length);

//Wypisywanie
void print(int ttl, int *ireply, int *responsetime, struct in_addr *treply);

#endif
