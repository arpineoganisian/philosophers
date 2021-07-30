#include "philo.h"

t_philo	**init_philosophers(t_args *args)
{
	t_philo	**philo;
	int		i;

	i = 0;
	philo = (t_philo **)malloc(sizeof(t_philo *) * args->num_of_philo);
	while (i < args->num_of_philo)
	{
		philo[i] = (t_philo *)malloc(sizeof(t_philo));
		philo[i]->thread_num = i + 1;
		philo[i]->args = args;
		philo[i]->left_fork = malloc(sizeof(pthread_mutex_t));
		philo[i]->num_of_meals = args->num_of_meals;
		if (i != 0)
			philo[i]->right_fork = philo[i - 1]->left_fork;
		if (i == args->num_of_philo - 1)
			philo[0]->right_fork = philo[i]->left_fork;
		i++;
	}
	return (philo);
}

void	terminate(t_args *args, t_philo **philo)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&args->fin);
	while (i < args->num_of_philo)
	{
		pthread_mutex_destroy(philo[i]->left_fork);
		free(philo[i]->left_fork);
		free(philo[i]);
		i++;
	}
	free(args);
	free(philo);
}

int	main(int argc, char **argv)
{
	t_args	*args;
	t_philo	**philo;

	args = (t_args *)malloc(sizeof(t_args));
	if (parse(argc, argv, args) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	philo = init_philosophers(args);
	pthread_mutex_init(&args->fin, NULL);
    if (args->num_of_philo == 1)
        pthread_create(&philo[0]->thread, NULL, start_one, (void *)philo[0]);
    else
        start_many(args, philo);
    pthread_create(&philo[0]->thread, NULL, thread, (void *)philo[0]);
    pthread_create(&philo[0]->thread, NULL, start_one, (void *)philo[0]);
	return (EXIT_SUCCESS);
}
