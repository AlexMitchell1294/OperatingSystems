#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	char seed[10];
	char ch;
	FILE  *fp;
	char filename[9] = "seed.txt";

	fp = fopen(filename, "r");

	int i = 0;
	while((ch = fgetc(fp)) != EOF){
		seed[i] = ch;
		i++;
	}

	printf("Read Seed Value: %s", seed);

	srand(atoi(seed));

	int r = (rand() % (12-6)+5);
	int randomArray[r];
	int des = r;

	for(i=0; i<r;i++){
		randomArray[i] = rand();
	}

	int id;
	int p = 0;
	pid_t wpid;
	pid_t chid;

	printf("Random Child Count: %d\n", r);
	for(i=0; i < r; i++){
		id = fork();
		if(id != 0){
			printf("[Parent, PID: %d] I am waiting for PID %d to finish\n", getpid(), id);
			while((wpid = waitpid(-1, &p, 0)) > 0);
			int es = WEXITSTATUS(p);
			printf("[Parent, PID: %d] child %d finished with status code %d. It's now my turn to exit\n",getpid(),	 id,es);

			exit(es+1);
		}
		else{
			printf("\t[Child, PID: %d]: I was called desendent count=%d. I'll have %d descendant(s).\n", getpid(), des, des-1);
			if(des<=0){
				exit(0);
			}
			else{
				des = des-1;
			}
		}
	}
}

