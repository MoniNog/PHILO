/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@lausanne42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:16:31 by monoguei          #+#    #+#             */
/*   Updated: 2024/11/24 18:59:14 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void create_pthread(t_param *param)
{
	pthread_t	t1;
	// pthread_t	t2;
	param->philos->id_philo = 1;
	param->philos->activity = 1;
	pthread_create(&t1, NULL, &activity, param->philos);
	// pthread_create(&t2, NULL, &activity, param);
	pthread_join(t1, NULL);
	// pthread_join(t2, NULL);
}

int	dead_or_alive(t_param *param, t_philo *philo)
{
	printf("time since last meal : %li\n", get_diff(&philo->last_meal));
	if (param->t_die <= get_diff(&philo->last_meal))
	{
		philo->activity = 0;
		return (0); // dead
	}
	else
		return (1); // alive
}

void	*activity(void *phil_id)
{
	t_philo	*philo;
	t_param *param;
	
	param = NULL;
	philo = (t_philo *)phil_id;
	while (philo->activity != 0)
	{	
		if (dead_or_alive(param, philo) == 1)
		{
			if (philo->activity == 1)
				think(philo);
			else if (philo->activity == 2)
				eat(param, philo);
			else
				sleeep(param, philo);
		}
	}
	printf("philo is dead :(\n");
	return NULL;
}

