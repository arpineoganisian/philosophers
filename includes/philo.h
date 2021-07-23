#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

pthread_mutex_t	g_lock;

typedef struct	s_philo
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meals;
	struct timeval	current_time;
}				t_philo;

int	parse(int argc, char **argv, t_philo *philo);
int	num_atoi(const char *str);

#endif