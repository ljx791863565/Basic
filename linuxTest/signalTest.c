#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

void sigusr(int signo)
{
	if (signo == SIGUSR1) {
		printf("this signal is SIGUSR1\n");
	} else if (signo == SIGUSR2) {
		printf("this signal is SIGUSR2\n");
	} else {
		printf("unkonwn siganl\n");
	}
}

int main(int argc, const char *argv[])
{
	if (signal(SIGUSR1, sigusr) == SIG_ERR) {
		perror("signal");
		return -1;
	}
	if (signal(SIGUSR2, sigusr) == SIG_ERR) {
		perror("signal");
		return -1;
	}

	while (1) {
		printf("working....\n");
		sleep(1);
	}
	return 0;
}
