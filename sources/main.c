#include "philo.h"

t_philo	**init_philosophers(t_args *args)
{
    t_philo	**philo;
    int		i;

    i = 0;
    philo = (t_philo **)malloc(sizeof(t_philo *) * args->n_of_phils);
    while (i < args->n_of_phils)
    {
        philo[i] = (t_philo *)malloc(sizeof(t_philo));
        philo[i]->id = i + 1;
        philo[i]->args = args;
        philo[i]->left_fork = malloc(sizeof(pthread_mutex_t));
        philo[i]->n_of_meals = args->n_of_meals;
        if (i != 0)
            philo[i]->right_fork = philo[i - 1]->left_fork;
        if (i == args->n_of_phils - 1)
            philo[0]->right_fork = philo[i]->left_fork;
        pthread_mutex_init(philo[i]->left_fork, NULL);
        i++;
    }
    return (philo);
}

void terminate(t_args *args, t_philo **philo)
{
    int	i;

    i = 0;
    pthread_mutex_destroy(args->fin);
	free(args->fin);
    while (i < args->n_of_phils)
    {
        pthread_mutex_destroy(philo[i]->left_fork);
        free(philo[i]->left_fork);
        free(philo[i]);
        i++;
    }
    free(args);
    free(philo);
}

void wait_threads(t_args *args, t_philo **philo)
{
    int 	i;

    i = 0;
    while (i < args->n_of_phils)
    {
        pthread_join(philo[i]->thread, NULL);
        i++;
    }
}

int main(int argc, char **argv) {
    t_args	*args;
    t_philo	**philo;

    args = (t_args *)malloc(sizeof(t_args));
    if (parse(argc, argv, args) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    philo = init_philosophers(args);
    if (args->n_of_phils == 1)
        pthread_create(&philo[0]->thread, NULL, run_one_philo, (void *)philo[0]);
    else
    	run_many_phils(args, philo);
    wait_threads(args, philo);
    terminate(args, philo);
    return (EXIT_SUCCESS);
}