#include "traceroute.h"

/*
Kamil Matuszewski, 272331.
*/

/*
Pętla wysyłająca kilka pakietów na raz. Zwraca 0 jeśli wszystko poszło dobrze, -1 jeśli nastąpił jakiś błąd
sockfd - gniazdo
ttl - ttl
pid - id pakietu, w naszym przypadku to id procesu
addr - adres na który chcemy wysyłać pakiet
*/
int sendsocks(int sockfd, int ttl, int pid, struct sockaddr_in addr){
	for(int i=0; i<3; i++){
		if(sendsock(sockfd, ttl, pid, addr)<0) return -1;
	}
	return 0;
}

/*
Wysyła jeden pakiet. Zwraca 0 jeśli wszystko poszło dobrze, -1 jeśli nastąpił błąd
sockfd - gniazdo
ttl - ttl
pid - id procesu, id pakietu
addr - adres na który chcemy wysyłać pakiet

Ustawiamy wszystkie wartości, ustawiamy ttl poleceniem setsockopt, a następnie wysyłamy.
*/
int sendsock(int sockfd, int ttl, int pid, struct sockaddr_in addr){
	struct icmp packet;
	packet.icmp_type = ICMP_ECHO;
	packet.icmp_code = 0;
	packet.icmp_id = pid;
	packet.icmp_seq = ttl;
	packet.icmp_cksum = 0;
	packet.icmp_cksum = compute_icmp_checksum((u_int16_t*)&packet, sizeof(packet));

	setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl));
	
	if (sendto(sockfd, &packet, sizeof(packet), 0, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		fprintf(stderr, "sendto error: %s\n", strerror(errno));
		return -1;		
	}
	return 0;
}
/*
Funkcja z wykładu, nie ogarniam
*/
u_int16_t compute_icmp_checksum (const void *buff, int length){
	
	u_int32_t sum;
	const u_int16_t* ptr = buff;
	assert (length % 2 == 0);
	for (sum = 0; length > 0; length -= 2)
		sum += *ptr++;

	sum = (sum >> 16) + (sum & 0xffff);
	return (u_int16_t)(~(sum + (sum >> 16)));
}
