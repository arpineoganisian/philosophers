#include "philo.h"

void	philo_message(long time, int thread_num, char *text, int flag)
{
	if (flag == 0)
		printf(" %ld - %d %s\n", time, thread_num, text);
}

void	dying(t_philo *philo)
{
	if (!philo->args->death_printed)
	{
		printf("️%ld - %d is dead ☠ \n",
			   get_time() - philo->args->start_time, philo->id);
	}
	philo->args->death_printed = 1;
}

void	sleeping_and_thinking(t_philo *philo)
{
	long	time_left;

	time_left = philo->start_of_dinner + philo->args->time_to_die
		- (get_time() - philo->args->start_time);
	if (time_left > 0)
		philo_message(get_time() - philo->args->start_time,
			  philo->id, "is sleeping 💤", philo->args->death);
	if (time_left < philo->args->time_to_sleep)
		fixed_usleep(time_left);
	else
		fixed_usleep(philo->args->time_to_sleep);
	philo_message(get_time() - philo->args->start_time, philo->id,
		"is thinking 🗿", philo->args->death);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	philo_message(get_time() - philo->args->start_time,
		  philo->id, "has taken a left fork 🍴", philo->args->death);
	pthread_mutex_lock(philo->right_fork);
	philo_message(get_time() - philo->args->start_time, philo->id,
		  "has taken a right fork 🍽", philo->args->death);
	philo->start_of_dinner = get_time() - philo->args->start_time;
	philo_message(get_time() - philo->args->start_time, philo->id,
		  "is eating 🍝", philo->args->death);
	fixed_usleep(philo->args->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
