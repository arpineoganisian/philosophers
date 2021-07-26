#include "philo.h"

void    dying(t_philo *philo)
{
	printf("☠️ %ld - %d is dead\n",
		   get_time() - philo->args->start_time, philo->thread_num);
}

void    thinking(t_philo *philo)
{
	int time_for_thinking;

	time_for_thinking = philo->args->time_to_die - philo->args->time_to_eat
					- philo->args->time_to_sleep;
	printf("🗿 %ld - %d is thinking\n",
		get_time() - philo->args->start_time, philo->thread_num);
	if (time_for_thinking < 0)
	{
		philo->args->death = 1;
		dying(philo);
	}
	else
		usleep(time_for_thinking * 1000);
}

void	sleeping(t_philo *philo)
{
	int	time_for_sleeping;

	time_for_sleeping = philo->args->time_to_die - philo->args->time_to_eat;
	printf("💤 %ld - %d is sleeping\n",
		get_time() - philo->args->start_time, philo->thread_num);
	if (time_for_sleeping < 0)
	{
		philo->args->death = 1;
		dying(philo);
	}
	else
		usleep(philo->args->time_to_sleep * 1000);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	printf("🍴 %ld - %d has taken a left fork\n",
		get_time() - philo->args->start_time, philo->thread_num);
	pthread_mutex_lock(philo->right_fork);
	printf("🍽 %ld - %d has taken a right fork\n",
		get_time() - philo->args->start_time, philo->thread_num);
	printf("🍝 %ld - %d is eating\n",
		get_time() - philo->args->start_time, philo->thread_num);
	usleep(philo->args->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*start_treads(void *philo)
{
	t_philo	*tmp;
	int 	i;

	i = 0;
	tmp = (t_philo *)philo;
	while (i < tmp->args->num_of_meals)
	{
		eating(tmp);
		sleeping(tmp);
		thinking(tmp);
		i++;
	}
	return (NULL);
}

void	start_all(t_args *args, t_philo **philo)
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
