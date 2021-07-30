#include "philo.h"

void    *observe_death(void *philo)
{
	t_philo **tmp;
	int     i;

	tmp = (t_philo **)philo;
	i = 0;
	while(1)
	{
		if (get_time() - tmp[i]->args->start_time
			> tmp[i]->start_of_dinner + tmp[i]->args->time_to_die)
		{
			if (tmp[i]->args->finished != tmp[i]->args->num_of_philo)
				dying(tmp[i]);
			tmp[i]->args->death = 1;
			return (NULL);
		}
		if (i == tmp[i]->args->num_of_philo - 1)
			i = 0;
		else
			i++;
	}
}

void    *observe_num_of_meals(void *philo)
{
	t_philo **tmp;
	int     i;

	tmp = (t_philo **)philo;
	i = 0;
	while(1)
	{
		if (tmp[i]->num_of_meals == 0)
			tmp[i]->args->finished++;
		if (tmp[i]->args->finished == tmp[i]->args->num_of_philo)
		{
			tmp[i]->args->death = 1;
			return (NULL);
		}
		if (i == tmp[i]->args->num_of_philo - 1)
			i = 0;
		else
			i++;
	}
}