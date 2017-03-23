/*
Kamil Matuszewski - problem palaczy tytoniu.
Problem palaczy tytoniu rozwiązany przy pomocy semaforów.
Program działa na procesach, i do użycia wymaga systemu linux.
Wersja: 22.01.2016
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

//Tobacco : 001
//Paper : 010
//Matches : 100

int main(int argc, char* argv[])
{
	int first_item, second_item;
	sem_t *semaphore_agent, *semaphore_tobacco, *semaphore_paper, *semaphore_matches;
	
	semaphore_agent=sem_open("/semaphore_agent",0);
	semaphore_tobacco=sem_open("/semaphore_tobacco",0); 
	semaphore_paper=sem_open("/semaphore_paper",0);		
	semaphore_matches=sem_open("/semaphore_matches",0);	
	

 	srand(time(0));
	
	while(1)
	{
	 sem_wait(semaphore_agent);
	 

	 first_item=(1<<(rand()%3));
	 
	 	do
	 	{
		second_item=(1<<(rand()%3));
		}
		while(first_item==second_item);
		
	 	int mask=(first_item|second_item);
	
	 	if(mask==6)
	 	{
		 printf("Agent: Kładę na stole papier i zapałki.\n");
		 sem_post(semaphore_tobacco);
		}
		else if(mask==5)
		{
		 printf("Agent: Kładę na stole tytoń i zapałki.\n");
		 sem_post(semaphore_paper);
		}
		else
		{
		 printf("Agent: Kładę na stole tytoń i papier.\n");
		 sem_post(semaphore_matches);
		}
	}

	return 0;
}

