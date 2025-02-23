/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@lausanne42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:27:34 by monoguei          #+#    #+#             */
/*   Updated: 2025/02/23 17:12:00 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	param_are_valid(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (atoi(av[i]) < 0)
			return (FALSE);
		else
			i++;
	}
	return (TRUE);
}

int	main(int ac, char **av)
{
	t_simulation	*simulation;

	if (ac == 6 || ac == 5)
	{
		simulation = create_simulation(av);
		if (simulation)
		{
			if (simulation->param->nb_philo == 1)
				printf(ONE_PHILO, THINKING, TAKING_FORK, av[2], PRINT_DEAD);
			else
				init_simulation(simulation);
			free_malloc(simulation);
		}
	}
	return (0);
}
