/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@lausanne42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:18:09 by monoguei          #+#    #+#             */
/*   Updated: 2024/11/22 12:36:28 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// return la diff en milliseconde depuis le temps entre en param
long	get_diff(struct timeval *start)
{
	struct timeval	now;
	long			diff;

	gettimeofday(&now, NULL);
	diff = (now.tv_sec - start->tv_sec) * 1000;
	diff += (now.tv_usec - start->tv_usec) / 1000;
	return (diff);
}

void	eat(t_param *param)
{
	printf("philo number %i\t\tis eating\n", param->philos->id_philo);
	usleep(param->t_eat * 1000);
	gettimeofday(&param->philos->last_meal, NULL);
	param->philos->activity = 3;
}

void	sleeep(t_param *param)
{
		printf("philo number %i\t\tis sleeping\n", param->philos->id_philo);
		usleep(param->t_sleep * 1000);
		param->philos->activity = 1; 
}

void	think(t_param *param)
{
	printf("philo number %i\t\tis thinking\n", param->philos->id_philo);
	usleep(10 * 1000);
	param->philos->activity = 2; 
}