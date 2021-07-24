#include "philo.h"

int	init_args(char **argv, t_args *args)
{
	args->num_of_philo = philo_atoi(argv[1]);
	args->time_to_die = philo_atoi(argv[2]);
	args->time_to_eat = philo_atoi(argv[3]);
	args->time_to_sleep = philo_atoi(argv[4]);
	if (argv[5])
		args->num_of_meals = philo_atoi(argv[5]);
	if (args->num_of_philo == -1 || args->time_to_die == -1
		|| args->time_to_eat == -1 || args->time_to_sleep  == -1
		|| ((argv[5]) && args->num_of_meals == -1))
		return (EXIT_FAILURE);
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