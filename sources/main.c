#include "philo.h"

t_philo **init_philosophers(t_args *args)
{
	t_philo	**philo;
    int		i;

    i = 0;
    philo = (t_philo **)malloc(sizeof(t_philo *) * args->num_of_philo);
	while(i < args->num_of_philo)
	{
		philo[i] = (t_philo *)malloc(sizeof(t_philo));
		philo[i]->thread_num = i + 1;
		philo[i]->time_to_eat = args->time_to_eat;
		philo[i]->left_fork = malloc(sizeof(pthread_mutex_t));
		if (i != args->num_of_philo - 1)
			philo[i]->right_fork = philo[i + 1]->left_fork;
		else

		i++;
	}
    return (philo);
}

int	main(int argc, char **argv)
{
	t_args *args;
	t_philo **philo;

    args = (t_args *)malloc(sizeof (t_args));
	if (parse(argc, argv, args) == EXIT_FAILURE)
		return (EXIT_FAILURE);

    philo = init_philosophers(args);
	start_dinner(args, philo);

	pthread_mutex_destroy(&g_lock);
    free(args);
	return (EXIT_SUCCESS);

}