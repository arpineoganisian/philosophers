#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

pthread_mutex_t g_lock;
struct timeval  g_current_time;

typedef struct	s_args
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meals;
}				t_args;

int     parse(int argc, char **argv, t_args *args);
int     philo_atoi(const char *str);
long    get_time(void);
#endif