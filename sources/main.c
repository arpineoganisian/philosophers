#include "philo.h"

//int init_philosophers(t_args *args)
//{
//    (void)args;
//    return (0);
//}

int	main(int argc, char **argv)
{
	t_args *args;
    args = (t_args *)malloc(sizeof (t_args));

	if (parse(argc, argv, args) == EXIT_FAILURE)
		return (EXIT_FAILURE);

//    init_philosophers(args);

	pthread_mutex_destroy(&g_lock);
    free(args);
	return (EXIT_SUCCESS);

}