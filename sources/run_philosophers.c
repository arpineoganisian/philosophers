#include "philo.h"

void	*run_one_philo(void *philo)
{
	t_philo	*tmp;

	tmp = (t_philo *)philo;
	pthread_mutex_lock(tmp->left_fork);
	printf(" %ld - %d has taken a left fork 🍴 \n",
		   get_time() - tmp->args->start_time, tmp->id);
	fixed_usleep(tmp->args->time_to_die);
	pthread_mutex_unlock(tmp->left_fork);
	tmp->args->death = 1;
	dying(tmp);
	return (NULL);
}

void	*philosophers(void *philo)
{
	t_philo	*tmp;

	tmp = (t_philo *)philo;
	while (!tmp->args->death && !tmp->args->end)
	{
		eating(tmp);
		sleeping_and_thinking(tmp);
		if (tmp->args->fifth_arg)
		{
			tmp->n_of_meals--;
			if (tmp->n_of_meals == 0)
			{
				pthread_mutex_lock(tmp->args->fin);
				tmp->args->finished++;
				pthread_mutex_unlock(tmp->args->fin);
				return (NULL);
			}
		}
	}
	return (NULL);
}

void	run_many_phils(t_args *args, t_philo **philo)
{
	int	i;

	i = 0;
	pthread_create(&args->death_thread, NULL, monitoring_death, (void *)philo);
	pthread_create(&args->end_thread, NULL, monitoring_end, (void *)philo);
	while (i < args->n_of_phils)
	{
		if (i == 0 || i % 2 == 0)
			pthread_create(&philo[i]->thread, NULL, philosophers,
				   (void *)philo[i]);
		i++;
	}
	usleep(40);
	i = 0;
	while (i < args->n_of_phils)
	{
		if (i % 2 == 1)
			pthread_create(&philo[i]->thread, NULL, philosophers,
				   (void *)philo[i]);
		i++;
	}
}
