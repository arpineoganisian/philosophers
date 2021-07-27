#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_args
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meals;
	short			death;
	short			fifth;
	int				finished;
	long			start_time;
	short			print;
}				t_args;

typedef struct s_philo
{
	int				thread_num;
	pthread_t		thread;
	t_args			*args;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long			start_of_dinner;
}				t_philo;

int		parse(int argc, char **argv, t_args *args);
long	get_time(void);
void	fixed_usleep(long sleep_time);
void	*start_one(void *philo);
void	start_many(t_args *args, t_philo **philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);
void	dying(t_philo *philo);
#endif