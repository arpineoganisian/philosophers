#include "philo.h"

int init_philosophers(t_args *args)
{

}

int	main(int argc, char **argv)
{
	t_args args;

	if (parse(argc, argv, &args) == EXIT_FAILURE)
		return (EXIT_FAILURE);

    init_philosophers(&args);

	printf("hop hey la la ley\n");

	pthread_mutex_destroy(&g_lock);

	return (EXIT_SUCCESS);
//	struct timeval current_time;
//	gettimeofday(&current_time, NULL);
//	printf("%d\n", current_time.tv_usec);

	//number_of_philosophers
	//time_to_die
	//time_to_eat
	//time_to_sleep
	//[number_of_times_each_philosopher_must_eat]
}