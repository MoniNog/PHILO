/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@lausanne42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:16:31 by monoguei          #+#    #+#             */
/*   Updated: 2024/11/22 12:36:21 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	*eat(void *param)
// {
// 	t_param *philo;

// 	philo = (t_param *)param;
// 	printf("Wouhaowww ! I'm thinking ! Wait don't disturb me !\n");
// 	usleep(philo->t_eat * 1000);

// 	printf("Miam miam, I'm exited, oups !! eating :)\n");
// 	usleep(philo->t_sleep * 1000);

// 	printf("And now dodo ! ZzzZZ... ZZZZzzzzZzzzZ...\n");
// 	return NULL;
// }

void create_pthread(t_param *param)
{
	pthread_t	t1;
	// pthread_t	t2;
	param->philos->id_philo = 1;
	param->philos->activity = 1;
	eat(param);
	pthread_create(&t1, NULL, &activity, param);
	// pthread_create(&t2, NULL, &activity, param);
	pthread_join(t1, NULL);
	// pthread_join(t2, NULL);
}

int	dead_or_alive(t_param *param)
{
	printf("time since last meal : %li\n", get_diff(&param->philos->last_meal));
	if (param->t_die <= get_diff(&param->philos->last_meal))
	{
		param->philos->activity = 0;
		return (0); // dead
	}
	else
		return (1); // alive
}

void	*activity(void *param)
{
	t_param	*philo;

	philo = (t_param *)param;
	while (philo->philos->activity != 0)
	{	
		if (dead_or_alive(philo) == 1)
		{
			if (philo->philos->activity == 1)
				think(philo);
			else if (philo->philos->activity == 2)
				eat(philo);
			else
				sleeep(philo);
		}
	}
	printf("philo is dead :(\n");
	return NULL;
}

