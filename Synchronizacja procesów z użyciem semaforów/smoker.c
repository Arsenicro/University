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

int main(int argc, char* argv[])
{	
	sem_t *semaphore_agent, *semaphore_tobacco, *semaphore_paper, *semaphore_matches;
	
	semaphore_agent=sem_open("/semaphore_agent",0);
	semaphore_tobacco=sem_open("/semaphore_tobacco",0);
	semaphore_paper=sem_open("/semaphore_paper",0);
	semaphore_matches=sem_open("/semaphore_matches",0);

	int number = atoi(argv[1]);
	
	while(1)
	{


		if(number==1) //smoker_tobacco
		{
		 sem_wait(semaphore_tobacco);
		 sleep(1);
		 printf("Palacz z tytoniem: Dostałem papier i zapałki! Wreszcie mogę zapalić!\n");
		}
		else if(number==2) //smoker_paper
		{
		 sem_wait(semaphore_paper);
		 sleep(1);
		 printf("Palacz z papierem: Dostałem tytoń i zapałki! Wreszcie mogę zapalić!\n");
		}
		else
		{
		 sem_wait(semaphore_matches); //smoker_matches
		 sleep(1);
		 printf("Palacz z zapałkami: Dostałem tytoń i papier! Wreszcie mogę zapalić!\n");
		}		
		
		sleep(1);
		printf("PYK PYK PYK\n");
		sleep(1);
		printf("PYK PYK PYK\n");
		sleep(1);
		printf("PYK PYK PYK\n");
		sleep(1);
		printf("Skończyłem! Zapaliłbym jeszcze jednego!\n");
		sleep(1);
		
		sem_post(semaphore_agent);
	}
	
	return 0;
}

