#include "threadPool.h"
#include "stdio.h"

void* header(void *arg)
{
	while (1){
		printf("this is in the thread\n");
		sleep(1);
	}
}

int main(int argc, const char *argv[])
{
	pool_init(4);

	pool_add_worker(header, NULL);


	return 0;
}
