#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include "../../thpool.h"


void sleep_5_secs(){
	sleep(5);
	puts("SLEPT");
}


int main(int argc, char *argv[]){

	int num = 0;
	threadpool thpool;

	/* Test if we can get the current number of working threads */
	/*Test jobs equal to thread*/
	thpool = thpool_init(5);
	thpool_add_work(thpool, (void*)sleep_5_secs, NULL);
	thpool_add_work(thpool, (void*)sleep_5_secs, NULL);
	thpool_add_work(thpool, (void*)sleep_5_secs, NULL);
	thpool_add_work(thpool, (void*)sleep_5_secs, NULL);
	thpool_add_work(thpool, (void*)sleep_5_secs, NULL);
	sleep(1);
	num = thpool_num_threads_working(thpool);
	if (num != 5) {
		printf("Expected 5 threads working, got %d", num);
		return -1;
	};

	/* Wait until all jobs have finished */
	thpool_wait(thpool);
	/* Destroy the threadpool */
	thpool_destroy(thpool);

	/* Test jobs less than thread */
	thpool = thpool_init(5);
	thpool_add_work(thpool, (void*)sleep_5_secs, NULL);
	thpool_add_work(thpool, (void*)sleep_5_secs, NULL);
	sleep(1);
	num = thpool_num_threads_working(thpool);
	if (num != 2) {
		printf("Expected 2 threads working, got %d", num);
		return -1;
	};

	thpool_wait(thpool);
	thpool_destroy(thpool);


	/* Test jobs more than thread */
	thpool = thpool_init(5);
	thpool_add_work(thpool, (void*)sleep_5_secs, NULL);
	thpool_add_work(thpool, (void*)sleep_5_secs, NULL);
	thpool_add_work(thpool, (void*)sleep_5_secs, NULL);
	thpool_add_work(thpool, (void*)sleep_5_secs, NULL);
	thpool_add_work(thpool, (void*)sleep_5_secs, NULL);
	thpool_add_work(thpool, (void*)sleep_5_secs, NULL);
	thpool_add_work(thpool, (void*)sleep_5_secs, NULL);
	thpool_add_work(thpool, (void*)sleep_5_secs, NULL);
	thpool_add_work(thpool, (void*)sleep_5_secs, NULL);
	thpool_add_work(thpool, (void*)sleep_5_secs, NULL);
	sleep(1);
	num = thpool_num_threads_working(thpool);
	if (num != 5) {
		printf("Expected 5 threads working, got %d", num);
		return -1;
	};

	thpool_wait(thpool);
	thpool_destroy(thpool);
	return 0;
}
