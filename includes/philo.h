#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_args
{
	int				n_of_phils;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_of_meals;

	short			fifth_arg;

	short			end;
	short			death;
	pthread_t		end_thread;
	pthread_t		death_thread;

	int				finished;
	pthread_mutex_t	*fin;

	short 			death_printed;

    long			start_time;

}				t_args;

typedef struct s_philo
{
    t_args          *args;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    int             id;
    pthread_t		thread;
	int             n_of_meals;
	long            start_of_dinner;

}				t_philo;

int		parse(int argc, char **argv, t_args *args);
long	get_time(void);
void	fixed_usleep(long sleep_time);
void	*run_one_philo(void *philo);
void	run_many_phils(t_args *args, t_philo **philo);
void	*monitoring_death(void *philo);
void	*monitoring_end(void *philo);
void    *philosophers(void *philo);
void    dying(t_philo *philo);
void    sleeping_and_thinking(t_philo *philo);
void    eating(t_philo *philo);
#endif