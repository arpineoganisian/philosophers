#include "philo.h"

void	start_one(t_args *args, t_philo **philo)
{
	(void)args;
	(void)philo;
}

void	*start_treads(void *philo)
{
	t_philo	*tmp;
	int		i;

	i = 0;
	tmp = (t_philo *)philo;
	while (tmp->args->fifth || i < tmp->args->num_of_meals)
	{
		eating(tmp);
		sleeping(tmp);
		thinking(tmp);
		i++;
	}
	tmp->args->finished++;
	return (NULL);
}

void	start_many(t_args *args, t_philo **philo)
{
	int	i;

	i = 0;
	while (i < args->num_of_philo)
	{
		pthread_mutex_init(philo[i]->left_fork, NULL);
		i++;
	}
	i = 0;
	while (i < args->num_of_philo)
	{
		pthread_create(&philo[i]->thread, NULL, start_treads, (void *)philo[i]);
		i++;
		usleep(40);
	}
}
