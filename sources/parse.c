#include "philo.h"

int	init_args(char **argv, t_philo *philo)
{
	philo->num_of_philo = num_atoi(argv[1]);
	philo->time_to_die = num_atoi(argv[2]);
	philo->time_to_eat = num_atoi(argv[3]);
	philo->time_to_sleep = num_atoi(argv[4]);
	if (argv[5])
		philo->num_of_meals = num_atoi(argv[5]);
	if (philo->num_of_philo == -1 || philo->time_to_die == -1
		|| philo->time_to_eat == -1 || philo->time_to_sleep  == -1
		|| ((argv[5]) && philo->num_of_meals == -1))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);

}

int	parse(int argc, char **argv, t_philo *philo)
{
	if (argc < 5 || argc > 6)
	{
		printf("Wrong number of arguments\n");
		return (EXIT_FAILURE);
	}
	if (init_args(argv, philo) == EXIT_FAILURE)
	{
		printf("Wrong value of argument\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}