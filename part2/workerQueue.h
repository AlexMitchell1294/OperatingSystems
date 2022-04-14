#ifndef WORKERQUEUE_H_INCLUDED
#define WORKERQUEUE_H_INCLUDED
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void makeTeam();

typedef struct worker{
	char color[7];
	int colorID;
	int id;
	pthread_t p;
}worker;

typedef struct team{
	worker workers[10];
	worker workerQ[10];
	int colorID;// 0 for blue, 1 for red, 2 for green, 3 for yellow
	char color[7];
	int front;
	int count;
	int rear;
}team;



#endif


