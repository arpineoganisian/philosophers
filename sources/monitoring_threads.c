#include "philo.h"

void	*monitoring_death(void *philo)
{
    t_philo **tmp;
    int     i;

    tmp = (t_philo **)philo;
    i = 0;
    while (!tmp[i]->args->death && !tmp[i]->args->end)
    {
        if (get_time() - tmp[i]->args->start_time
        > tmp[i]->start_of_dinner + tmp[i]->args->time_to_die)
        {
            tmp[i]->args->death = 1;
            if (!tmp[i]->args->fifth_arg || (tmp[i]->args->fifth_arg && tmp[i]->n_of_meals != 0))
           		dying(tmp[i]);
            return (NULL);
        }
        if (i == tmp[i]->args->n_of_phils - 1)
            i = 0;
        else
            i++;
    }
    return (NULL);
}

void	*monitoring_end(void *philo)
{
    t_philo **tmp;
    int     i;

    tmp = (t_philo **)philo;
    i = 0;

    if (tmp[i]->args->fifth_arg)
    {
    	while (!tmp[i]->args->end)
		{
			if (tmp[i]->args->finished == tmp[i]->args->n_of_phils)
			{
				tmp[i]->args->end = 1;
				return (NULL);
			}
			if (i == tmp[i]->args->n_of_phils - 1)
				i = 0;
			else
				i++;
		}
	}
    return (NULL);
}

