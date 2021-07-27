#include "philo.h"

void	dying(t_philo *philo)
{
//	if (philo->args->print == 0)
		printf("☠️ %ld - %d is dead\n",
			get_time() - philo->args->start_time, philo->thread_num);
//	philo->args->print = 1;
}

void	thinking(t_philo *philo)
{
	long	time_left;

	time_left = (philo->start_of_dinner + philo->args->time_to_die)
		- (get_time() - philo->args->start_time + philo->args->time_to_sleep
		+ philo->args->time_to_eat);
	if (time_left <= 0)
	{
		philo->args->death = 1;
		dying(philo);
	}
	else
	{
		printf("🗿 %ld - %d is thinking\n",
			get_time() - philo->args->start_time, philo->thread_num);
		fixed_usleep(time_left);
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
		fixed_usleep(time_left);
		philo->args->death = 1;
		dying(philo);
	}
	else
		fixed_usleep(philo->args->time_to_sleep);
}

void	eating(t_philo *philo)
{
	if (philo->start_of_dinner + philo->args->time_to_die
		== get_time() - philo->args->start_time)
	{
		philo->args->death = 1;
		dying(philo);
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
	fixed_usleep(philo->args->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
