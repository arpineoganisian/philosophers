#include "philo.h"

int	philo_atoi(const char *str)
{
    int		i;
    long	res;

    i = 0;
    res = 0;
    while (str[i])
    {
        if (str[i] >= '0' && str[i] <= '9')
            res = res * 10 + (str[i] - '0');
        else
            return (-1);
        i++;
        if (i > 11)
            return (-1);
    }
    if (res > 2147483647 || res == 0)
        return (-1);
    return (res);
}

int	init_args(char **argv, t_args *args)
{
    args->n_of_phils = philo_atoi(argv[1]);
    args->time_to_die = philo_atoi(argv[2]);
    args->time_to_eat = philo_atoi(argv[3]);
    args->time_to_sleep = philo_atoi(argv[4]);
    if (argv[5])
    {
		args->n_of_meals = philo_atoi(argv[5]);
		args->fifth_arg = 1;
	}
    else
    	args->fifth_arg = 0;
    if (args->n_of_phils == -1 || args->time_to_die == -1
    || args->time_to_eat == -1 || args->time_to_sleep == -1
    || ((argv[5]) && args->n_of_meals == -1))
        return (EXIT_FAILURE);
    args->start_time = get_time();
    args->death = 0;
    args->finished = 0;
    args->death_printed = 0;
    args->fin = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(args->fin, NULL);
    return (EXIT_SUCCESS);
}

int	parse(int argc, char **argv, t_args *args)
{
    if (argc < 5 || argc > 6)
    {
        printf("Wrong number of arguments\n");
        return (EXIT_FAILURE);
    }
    if (init_args(argv, args) == EXIT_FAILURE)
    {
        printf("Wrong value of argument\n");
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}
