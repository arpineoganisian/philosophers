#include "philo.h"

void    *eating(void *philo)
{
	t_philo	*tmp;

	tmp = (t_philo *)philo;
    printf("%ld - %d is eating\n", get_time(), tmp->thread_num);
	usleep(tmp->time_to_eat * 1000);
	return (NULL);
}

void	start_dinner(t_args *args, t_philo **philo)
{
	int i;

	i = 0;
	while(i < args->num_of_philo)
	{
		pthread_create(&philo[i]->thread, NULL, eating, (void *)philo[i]);
		i++;
	}
}