#include <stdio.h>
#include <time.h>

int countEnter = 0;
int countExit = 0;

time_t start_t, end_t;




__attribute__((no_instrument_function))
void __cyg_profile_func_enter(void *this_fn, void *call_site){

	printf("Function entered: %d\n", countEnter);

	countEnter++;
	time(&start_t);



}

__attribute__((no_instrument_function))
void __cyg_profile_func_exit(void *this_fn, void *call_site){

	printf("Function exited: %d\n", countExit);
	countExit++;
	time(&end_t);

	double diffTime = difftime(end_t,start_t);
	printf("Execution Time is: %f\n", diffTime);

}

