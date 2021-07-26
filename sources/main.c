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
		philo[i]->args = args;
		philo[i]->left_fork = malloc(sizeof(pthread_mutex_t));
		if (i != 0)
			philo[i]->right_fork = philo[i-1]->left_fork;
		if (i == args->num_of_philo - 1)
			philo[0]->right_fork = philo[i]->left_fork;
		philo[i]->death = 0;
		i++;
	}
    return (philo);
}

//void	init_all_data(t_args *args)
//{
//}

void join_threads(t_args *args, t_philo **philo)
{
	int 	i;

	i = 0;
	while (i < args->num_of_philo)
	{
		pthread_join(philo[i]->thread, NULL) ;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_args	*args;
	t_philo	**philo;

    args = (t_args *)malloc(sizeof(t_args));
	if (parse(argc, argv, args) == EXIT_FAILURE)
		return (EXIT_FAILURE);
//	init_all_data(args);
    philo = init_philosophers(args);
    start_all(args, philo);
	join_threads(args, philo);
	return (EXIT_SUCCESS);
}