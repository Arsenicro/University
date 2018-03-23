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
	pid_t agent, smoker_tobacco, smoker_paper, smoker_matches;

	sem_unlink("/semaphore_agent");
	sem_unlink("/semaphore_tobacco");
	sem_unlink("/semaphore_paper");
	sem_unlink("/semaphore_matches");
	
	semaphore_agent=sem_open("/semaphore_agent", O_CREAT, (S_IRWXU | S_IRWXG | S_IRWXO), 1);
	semaphore_tobacco=sem_open("/semaphore_tobacco", O_CREAT, (S_IRWXU | S_IRWXG | S_IRWXO), 0);
	semaphore_paper=sem_open("/semaphore_paper", O_CREAT, (S_IRWXU | S_IRWXG | S_IRWXO), 0);
	semaphore_matches=sem_open("/semaphore_matches", O_CREAT, (S_IRWXU | S_IRWXG | S_IRWXO), 0);
	
	sem_close(semaphore_agent);
	sem_close(semaphore_tobacco);
	sem_close(semaphore_paper);
	sem_close(semaphore_matches);
	
	agent=fork();
	
	if(agent==0)
	{
	 char* argums[]={"agent", 0};
	 char* envir[]={ NULL };
	 execve("agent", argums, envir);
	}
	else
	{
	 smoker_tobacco=fork();
	 
		if(smoker_tobacco==0)
		{
	 	 char* argums[]={"smoker", "1", 0};
	 	 char* envir[]={ NULL };
		 execve("smoker", argums, envir);
		}
		else
		{
		 smoker_paper=fork();
		 
			if(smoker_paper==0)
			{
	 	 	 char* argums[]={"smoker", "2", 0};
	 	 	 char* envir[]={ NULL };
			 execve("smoker", argums, envir);
			}
			else
			{
			 smoker_matches=fork();
			 
				if(smoker_matches==0)
				{
	 	 		 char* argums[]={"smoker", "3", 0};
	 	 		 char* envir[]={ NULL };
				 execve("smoker", argums, envir);
				}
				else
				{
				 while(1);
				}
			}
		}
	}
	
	
	return 0;
}
