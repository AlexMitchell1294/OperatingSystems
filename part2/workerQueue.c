#include "workerQueue.h"
#define max 10

char colors[4][7] = {"Blue", "Red", "Green", "Yellow"};

bool isEmpty(team* t){
	return t->count == 0;	
}

bool isFull(team* t){
	return t->count == 10;
}

void makeTeam(team* t, int colora){
	t->count = 0;
	t->front = 0;
	t->rear = -1;
	t->colorID = colora;
	strcpy(t->color, colors[colora]);
}

void insert(team* t, worker w){
	if(!isFull(t)){
		if(t->rear==max-1) t->rear = -1;

		t->workerQ[++t->rear] = w;
		t->count++;
	}
}

worker get(team* t){
	worker w = t->workerQ[t->front++];

	if (t->front == max){
		t->front = 0;
	}

	t->count--;
	return w;
}


