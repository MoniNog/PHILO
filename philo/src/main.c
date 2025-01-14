/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@lausanne42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:27:34 by monoguei          #+#    #+#             */
/*   Updated: 2025/01/14 11:03:52 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/// @brief Check if malloc success
/// @param simulation 
/// @return 0 : malloc fail, memory free | 1 : malloc success
int	free_malloc(t_simulation *simulation)
{
	free(simulation->philosophers);
	free(simulation->param);
	free(simulation);
	return (0);
}

/// @brief malloc struct, atoi params and stock them
/// @param av param set in the command line (nb_philo, t_die, t_eat, t_sleep, (times_each_philo_must_eat))
/// @return simulation where are param with the values enter in the command line
t_simulation	*create_simulation(char **av)
{
	t_simulation *simulation;
	
	simulation = malloc(sizeof(t_simulation));
	if (!simulation)
		return NULL;
	simulation->param = malloc(sizeof(t_param));
	if (!simulation->param)
		return NULL;
	simulation->param->nb_philo = atoi(av[1]);
	simulation->param->t_die = atoi(av[2]);
	simulation->param->t_eat = atoi(av[3]);
	simulation->param->t_sleep = atoi(av[4]);
	simulation->philosophers = malloc(sizeof(t_philo) * simulation->param->nb_philo);
	if (!simulation->philosophers)
		return NULL;
	if (av[5] && atoi(av[5]) > 0)
		simulation->param->times_each_philo_must_eat = atoi(av[5]);
	else
		simulation->param->times_each_philo_must_eat = -1;
	return (simulation);
}

int main(int ac, char **av)
{
	t_simulation *simulation;

	if (ac == 6 || ac == 5)
	{
		simulation = create_simulation(av);
		if (!simulation)
			return 0;
		init_simulation(simulation);
	}
	free_malloc(simulation);
	return 0;
}
