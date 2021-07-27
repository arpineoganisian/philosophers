#include "philo.h"

void	dying(t_philo *philo)
{
	printf("☠️ %ld - %d is dead\n",
		   get_time() - philo->args->start_time, philo->thread_num);
}

void	thinking(t_philo *philo)
{
	long	time_left;

	time_left = philo->start_of_dinner + philo->args->time_to_die
		- (get_time() - philo->args->start_time - philo->args->time_to_sleep);
	if (time_left < 0)
	{
		philo->args->death = 1;
		dying(philo);
	}
	else
	{
		printf("🗿 %ld - %d is thinking\n",
			get_time() - philo->args->start_time, philo->thread_num);
		usleep(time_left * 1000);
	}
}

void	sleeping(t_philo *philo)
{
	long	time_left;

	time_left = philo->start_of_dinner + philo->args->time_to_die
		- (get_time() - philo->args->start_time);
	if (time_left > 0)
		printf("💤 %ld - %d is sleeping\n",
			get_time() - philo->args->start_time, philo->thread_num);
	if (time_left < philo->args->time_to_sleep)
	{
		philo->args->death = 1;
		dying(philo);
		usleep(time_left * 1000);
	}
	else
		usleep(philo->args->time_to_sleep * 1000);
}

void	eating(t_philo *philo)
{
	if (philo->start_of_dinner + philo->args->time_to_die
		== get_time() - philo->args->start_time)
	{
		philo->args->death = 1;
		dying(philo);
		return;
	}
	pthread_mutex_lock(philo->left_fork);
	printf("🍴 %ld - %d has taken a left fork\n",
		get_time() - philo->args->start_time, philo->thread_num);
	pthread_mutex_lock(philo->right_fork);
	printf("🍽 %ld - %d has taken a right fork\n",
		get_time() - philo->args->start_time, philo->thread_num);
	philo->start_of_dinner = get_time() - philo->args->start_time;
	printf("🍝 %ld - %d is eating\n",
		get_time() - philo->args->start_time, philo->thread_num);
	usleep(philo->args->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
