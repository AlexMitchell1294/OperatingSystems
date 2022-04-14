//#ifdef PACKAGEQUEUE_H_INCLUDED
//#define PACKAGEQUEUE_H_INCLUDED
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct package{
	int id;
	int steps[4];
	int stepsLeft;
}package;

typedef struct packages{
	package pq[50];//0 indicates no job 1-4 indicates their respective job
	int count;
	int front;
	int rear;
}packages;

bool contains(int[], int, int);
bool isEmptyp(packages* p);
void initPackageQueue(packages* p);
package getNextPackage(packages* p);
char *getSteps(package p);
//#endif
