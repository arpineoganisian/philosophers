#include "philo.h"

void	*start_one(void *philo)
{
	t_philo	*tmp;

	tmp = (t_philo *)philo;
	pthread_mutex_lock(tmp->left_fork);
	printf(" %ld - %d has taken a left fork 🍴 \n",
		   get_time() - tmp->args->start_time, tmp->thread_num);
	fixed_usleep(tmp->args->time_to_die);
	pthread_mutex_unlock(tmp->left_fork);
	tmp->args->death = 1;
	dying(tmp);
	return (NULL);
}

void	*treads(void *philo)
{
	t_philo	*tmp;

	tmp = (t_philo *)philo;
	while (!tmp->args->death
		&& (tmp->args->fifth || tmp->args->finished != tmp->args->num_of_philo))
	{
		eating(tmp);
		sleeping(tmp);
		thinking(tmp);
		pthread_mutex_lock(&tmp->args->fin);
		tmp->num_of_meals--;
		pthread_mutex_unlock(&tmp->args->fin);
	}
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
		if (i == 0 || i % 2 == 0)
			pthread_create(&philo[i]->thread, NULL, treads, (void *)philo[i]);
		i++;
	}
	i = 0;
	usleep(40);
	while (i < args->num_of_philo)
	{
		if (i % 2 == 1)
			pthread_create(&philo[i]->thread, NULL, treads, (void *)philo[i]);
		i++;
	}
}
