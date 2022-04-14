object = stage shipping

all: $(object)

stage: stage.c 
	gcc -g -o stage stage.c -pthread

shipping: shipping.c workerQueue.c workerQueue.h packageQueue.h packageQueue.c
	gcc -g -o shipping shipping.c workerQueue.c workerQueue.h packageQueue.h packageQueue.c -pthread

.PHONY: clean

.PHONY: s

s:
	./shipping

clean:
	-rm $(object)
