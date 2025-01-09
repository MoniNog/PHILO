/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@lausanne42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:27:34 by monoguei          #+#    #+#             */
/*   Updated: 2025/01/09 16:30:31 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/// @brief atoi params and stock them in the struct t_param
/// @param av param set in the command line (nb_philo, t_die, t_eat, t_sleep, (times_each_philo_must_eat))
/// @return struct t_param where are stock the params.
t_param	*initialization_struct(t_simulation *simulation, char **av)
{// check atoi nb positif uniquement
	simulation->param = malloc(sizeof(t_param));
	if (!simulation->param)
	{
		free(simulation);
		return NULL;
	}
	simulation->param->nb_philo = atoi(av[1]);
	simulation->param->t_die = atoi(av[2]);
	simulation->param->t_eat = atoi(av[3]);
	simulation->param->t_sleep = atoi(av[4]);
	simulation->philosophers = malloc(sizeof(t_philo) * simulation->param->nb_philo);
	if (!simulation->philosophers)
	{
		free(simulation->param);
		free(simulation);
		return NULL;
	}
	if (av[5])
		simulation->param->times_each_philo_must_eat = atoi(av[5]);
	else
		simulation->param->times_each_philo_must_eat = -1;
	return (simulation->param);
}

int main(int ac, char **av)
{
	t_simulation *simulation;

	if (ac == 6 || ac == 5)
	{
		simulation = malloc(sizeof(t_simulation));
		if (!simulation)
			return 0;
		simulation->param = initialization_struct(simulation, av);
		init_simulation(simulation, simulation->param, simulation->philosophers);
	}
	return 0;
}
