/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@lausanne42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 18:10:50 by monoguei          #+#    #+#             */
/*   Updated: 2024/11/24 18:49:13 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	eat(t_param *param, t_philo *philo)
{
	printf("philo number %i\t\tis eating\n", philo->id_philo);
	gettimeofday(&philo->last_meal, NULL);
	usleep(param->t_eat * 1000);
	philo->activity = 3;
}

void	sleeep(t_param *param, t_philo *philo)
{
	printf("philo number %i\t\tis sleeping\n", philo->id_philo);
	usleep(param->t_sleep * 1000);
	philo->activity = 1; 
}

void	think(t_philo *philo)
{
	printf("philo number %i\t\tis thinking\n", philo->id_philo);
	usleep(10 * 1000);
	philo->activity = 2; 
}