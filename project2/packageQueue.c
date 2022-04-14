#include "packageQueue.h"

bool isEmptyp(packages* p){
	return p->count == 0;
}

void initPackageQueue(packages* p){
	p->count = 40;
	p->front = 0;
	p->rear = -1;
	int r;
	int array[4] = {0,0,0,0};
	for(int i = 0; i<40;i++){
		for(int j = 0; j<4; j++){		
			r = rand()%4;	
			array[r] = r+1;//p->pq[i].steps[r] = r+1;
		}
		for(int j=0;j<4;j++){
			r = rand()%4;
			if(!contains(p->pq[i].steps, 4, r+1))
				p->pq[i].steps[rand()%4] = r+1;
			
		}
		p->pq[i].id = i;
	}
}

package getNextPackage(packages* p){
	package pack = p->pq[p->front++];

	p->count--;
	return pack;
}

char *getSteps(package p){
	char *str;
	char *c;
	int array[4] = {0,0,0,0};
	str = (char*)malloc(8*sizeof(char));
	c = (char*)malloc(2*sizeof(char));
	for(int i = 0; i <4; i++){
		memset(c,0,sizeof(c));
		if(p.steps[i] != 0){
			if(p.steps[i] != array[p.steps[i]] || p.steps[i] == 0){
				//array[p.steps[i]] = p.steps[i];
				*c = p.steps[i]+'0';
				strcat(c, " ");
				strcat(str, c);
			}
		}
	}
	free(c);

	return str;
}

bool contains(int arr[], int size, int val){
	int flag = false;
	for (int i = 0; i<size; i++){
		if (arr[i] == val){
			flag = true;
			break;
		}
	}
	return flag;
}
