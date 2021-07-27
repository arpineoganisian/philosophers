#include "philo.h"

long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void	fixed_usleep(long milliseconds)
{
	long	period;

	period = get_time() + milliseconds;
	while (period > get_time())
		usleep(1);
}
