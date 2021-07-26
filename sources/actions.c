#include "philo.h"

//◦ timestamp_in_ms X has taken a fork
//◦ timestamp_in_ms X is eating
//◦ timestamp_in_ms X is sleeping
//◦ timestamp_in_ms X is thinking
//◦ timestamp_in_ms X died

void    thinking(t_philo *philo)
{
	int time_to_sleep;

	time_to_sleep = philo->args->time_to_die - philo->args->time_to_sleep
					- philo->args->time_to_sleep;
	printf("🗿 %ld - %d is thinking\n", get_time(), philo->thread_num);
	if (time_to_sleep < 0)
		philo->death = 1;
	else
		usleep(time_to_sleep * 1000);

}

void    sleeping(t_philo *philo)
{
	printf("💤 %ld - %d is sleeping\n", get_time(), philo->thread_num);
	usleep(philo->args->time_to_sleep * 1000);
}

void    eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	printf("🍴 %ld - %d has taken a left fork\n", get_time(), philo->thread_num);
	pthread_mutex_lock(philo->right_fork);
	printf("🍽 %ld - %d has taken a right fork\n", get_time(), philo->thread_num);
    printf("🍝 %ld - %d is eating\n", get_time(), philo->thread_num);
	usleep(philo->args->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*start_treads(void *philo)
{
	t_philo	*tmp;

	tmp = (t_philo *)philo;
	while (!tmp->death)
	{
		eating(tmp);
		sleeping(tmp);
		thinking(tmp);
	}
	return (NULL);
}

void	start_all(t_args *args, t_philo **philo)
{
	int i;

	i = 0;
	while(i < args->num_of_philo)
	{
		pthread_mutex_init(philo[i]->left_fork, NULL);
		i++;
	}
	i = 0;
	while(i < args->num_of_philo)
	{
		pthread_create(&philo[i]->thread, NULL, start_treads, (void *)philo[i]);
		i++;
		usleep(40);
	}
}