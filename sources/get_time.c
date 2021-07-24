#include "philo.h"

long get_time(void)
{
	gettimeofday(&g_current_time, NULL);
	return g_current_time.tv_usec;
}