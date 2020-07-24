
/*
 * assert的四种测试形式
 * 静止的和活动的，满足条件和不满足条件的
 * 只有活动的不满足条件的测试才会终止
 */

#define NDEBUG
#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static int val = 0;
static void field_abort(int sig)
{
	if (val == 1) {
		puts("SUCCESS testing <assert.h>");
		exit(EXIT_SUCCESS);
	}else {
		puts("FALLURE testing <assert.h>");
		exit(EXIT_FAILURE);
	}
}

static void dummy()
{
	int i = 0;
	assert(i == 0);		//静止的满足条件的测试
	assert(i == 1);		//静止的不满足条件的测试
}

#undef NDEBUG 
#include <assert.h>

int main()
{
	assert(signal(SIGABRT, &field_abort) != SIG_ERR);
	dummy();
	assert(val == 0);	//活动的满足条件的测试
	++val;
	fputs("Sample assertion failure messafe --\n", stderr);
	assert(val == 0);	//活动的不满足条件的测试
	puts("FAILURE testing <assert.h>");
	return (EXIT_FAILURE);

}
