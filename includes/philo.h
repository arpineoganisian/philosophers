#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

pthread_mutex_t g_lock;

typedef struct	s_args
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meals;
}				t_args;

typedef struct	s_philo
{
    int         	thread_num;
    pthread_t   	thread;
    int 			time_to_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t *right_fork;

}				t_philo;

int     parse(int argc, char **argv, t_args *args);
long    get_time(void);
void	start_dinner(t_args *args, t_philo **philo);
#endif