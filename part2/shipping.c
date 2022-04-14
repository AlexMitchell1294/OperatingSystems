#include "workerQueue.h"
#include "packageQueue.h"
#include <semaphore.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

sem_t mutex;

/*
sem_t blue;
sem_t red;
sem_t green;
sem_t yellow;*/

sem_t *colors;

team* blue;
team* red;
team* green;
team* yellow;

int spotLocations[4] = {0,0,0,0};
packages *allP;
char *buffer;

int lottery;
int currentPos;
int queueLen;

void *work(void *args){
	worker *w = (worker*) args;
	sem_wait(&colors[w->colorID]);
	package p;
	sem_wait(&mutex);
	p = getNextPackage(allP);
	sem_post(&mutex);
	int a = 0;
 	int flag = 0;
	
	/*while(1){
		sem_wait(&mutex);
		//printf("%s %d Try: %d\n", w->color, w->id, a);
		lottery = rand() % 4;
		if(lottery == w->colorID){

			p = getNextPackage(allP);
			sem_post(&mutex);
			break;
		}
		else{
			a +=1;
			sem_post(&mutex);
			usleep(1000*10);
		}
	}*/

	printf("%s %d grabbed a Package: \n", w->color, w->id);
	printf("\tPackage: %d\n\tSteps: %s\n", p.id, getSteps(p));
	sleep(1);
	int yours;
//	printf("mutex down 1\n");
	sem_wait(&mutex);
	yours = currentPos + queueLen;
	queueLen += 1;
	sem_post(&mutex);
	while(1){
		sem_wait(&mutex);
		flag = 0;
		for(int i = 0; i<4; i++){
			if(p.steps[i] != 0){
				if (spotLocations[p.steps[i]-1] == 0){
					spotLocations[p.steps[i]-1] = w->colorID+1;
					flag+=1;
				}
			}
			else{
				flag+=1;
			}
		}
		//printf("%d\n", flag);
		if(flag == 4) break;
		else{
			for(int i = 0; i<4; i ++){
				if (spotLocations[i] == w->colorID+1) spotLocations[i] = 0;
			}
		}
		//printf("\ttarr: %d %d %d %d\n", spotLocations[0], spotLocations[1], spotLocations[2], spotLocations[3]);
	
		sem_post(&mutex);
		/*if(p.step[1] != 0)
			 if (spotLocations[p.steps[1]-1] == 0) spotLocations[p.steps[1]-1] = w->colorID+1;

		if(p.step[2] != 0)
			 if (spotLocations[p.steps[2]-1] == 0) spotLocations[p.steps[2]-1] = w->colorID+1;

		if(p.step[3] != 0)
			 if (spotLocations[p.steps[3]-1] == 0) spotLocations[p.steps[3]-1] = w->colorID+1;
		*/
	}
	sem_post(&mutex);
/*
	for(int i = 0; i<4; i++){
		//sem_wait(&mutex);
		while(p.steps[i] != 0){
			sem_wait(&mutex);
//			printf("mutex down 2\n");
			if (spotLocations[p.steps[i]-1] == 0 ){//&& currentPos == yours){
				//printf("%d %d %d %d\n", p.steps[0], p.steps[1], p.steps[2], p.steps[3]);
				//printf("%d\n", w->colorID +1);
				spotLocations[p.steps[i]-1] = w->colorID + 1;
				sem_post(&mutex);
//				printf("mutex up 1\n");
				break;
			}
			else if (p.steps[i] == 0){
				sem_post(&mutex);
			}
			else{
				//if(flag == 0){
					sem_post(&mutex);
					//printf("mutex up 2\n");
					//flag=1;
					usleep(1000*10);
					break;
				//}	
			}
		}
//		sem_post(&mutex);
	}*/
	sem_wait(&mutex);
	currentPos += 1;
	queueLen -= 1;
	sem_post(&mutex);

	printf("%s %d claimed %s\n", w->color, w->id, getSteps(p));

	for(int i = 0; i<4; i++){
		sem_wait(&mutex);
		while(p.steps[i] != 0){
			//print
					//release
			sem_post(&mutex);
			//sleep
			sleep(1);
			//pickup
			sem_wait(&mutex);
			//leave station
			spotLocations[p.steps[i]-1] = 0;
			printf("%s %d released %d\n", w->color, w->id, p.steps[i]);
			//print
			//release
			break;
		}
		sem_post(&mutex);
	}

	
	printf("%s %d Placed a package unto truck\n", w->color, w->id);

	sem_post(&colors[w->colorID]);
}


int main(){

	char seed[10];
	char ch;
	FILE *fp;
	char filename[9] = "seed.txt";
	fp = fopen(filename, "r");

	int k = 0;
	while((ch = fgetc(fp)) != EOF){
		seed[k] = ch;
		k++;
	}
	srand(atoi(seed));
	printf("Random Seed: %s\n", seed);
	
//	spotLocations[4] = {0,0,0,0};
	spotLocations[0] = 0;
	currentPos = 0;
	queueLen = 0;
	sem_init(&mutex, 0, 1);

	colors = (sem_t*)malloc(sizeof(sem_t)*4);
	/*sem_t blue;
	sem_t red;
	sem_t green;
	sem_t yellow;

	colors[0] = blue;
	colors[1] = red;
	colors[2] = green;
	colors[3] = yellow;*/

	sem_init(&colors[0], 0, 1);
	sem_init(&colors[1], 0, 1);
	sem_init(&colors[2], 0, 1);
	sem_init(&colors[3], 0, 1);
	blue = (team*)malloc(sizeof(team));
	red = (team*)malloc(sizeof(team));
	green = (team*)malloc(sizeof(team));
	yellow = (team*)malloc(sizeof(team));
	allP = (packages*)malloc(sizeof(packages));
	buffer = (char*)malloc(20*sizeof(char));

	makeTeam(blue, 0);
	makeTeam(red, 1);
	makeTeam(green, 2);
	makeTeam(yellow, 3);
	initPackageQueue(allP);
/*
	for(int i = 0; i<50; i++){	
		buffer = getSteps(p->pq[i]);
		printf("%s\n", buffer);
	}*/

	for(int i = 0; i < 10; i++){
		blue->workers[i] = (worker){.colorID=0, .id=i, .color="Blue"};
		red->workers[i] = (worker){.colorID=1, .id=i, .color="Red"};
		green->workers[i] = (worker){.colorID=2, .id=i, .color="Green"};
		yellow->workers[i] = (worker){.colorID=3, .id=i, .color="Yellow"};
		pthread_create(&blue->workers[i].p, NULL, work, &blue->workers[i]);
		pthread_create(&red->workers[i].p, NULL, work, &red->workers[i]);
		pthread_create(&green->workers[i].p, NULL, work, &green->workers[i]);
		pthread_create(&yellow->workers[i].p, NULL, work, &yellow->workers[i]);
	}
	int sd;

	/*while(1){
		sleep(1);
		sem_getvalue(&mutex, &sd);
		printf("\t%d\t%d\t%d\tarr: %d %d %d %d\n", sd, currentPos, queueLen, spotLocations[0], spotLocations[1], spotLocations[2], spotLocations[3]);
	}*/
	pthread_exit(NULL);
}
