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

	printf("Read Seed Value: %d\n\n", atoi(seed));

	srand(atoi(seed));

	int r = (rand() % (13-9)+8);
	int randomArray[r];
	int rIndex = 0;

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
		chid = getpid();
		if(id != 0){
		//	chid = getpid();
			printf("[Parent] I am waiting for PID %d to finish\n", id);
			while((wpid = waitpid(-1, &p, 0)) > 0);
			int es = WEXITSTATUS(p);
			printf("[Parent] child %d finished with status code %d\n", id,es);
			rIndex++;
		}
		else{
			int time = randomArray[rIndex] % 3 + 1;
			int code = randomArray[rIndex] % 50 + 1;

			printf("\t[Child, PID: %d]: I am the child and I will wait for %d Seconds and exit with code %d\n", getpid(), time, code);
			sleep(time);
			printf("\t[Child, PID: %d]: now exiting...\n", getpid());
			exit(code);
		}
	}
}

