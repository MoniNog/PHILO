/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:27:34 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/23 15:14:35 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	free_malloc(t_simulation *simulation)
{
	int	i;

	i = 0;
	while (i < simulation->param->nb_philo)
	{
		pthread_mutex_destroy(&simulation->philosophers[i].left_fork);
		free(simulation->philosophers[i].thread);
		i++;
	}
	free(simulation->philosophers);
	free(simulation->param);
	pthread_mutex_destroy(&simulation->print_mutex);
	pthread_mutex_destroy(&simulation->status_mutex);
	free(simulation);
	return (0);
}

int isdigit_str(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (FALSE);
		str++;
	}
	return (TRUE);
}

int	param_are_valid(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!isdigit_str(av[i]) || atoi(av[i]) < 0)
			return (FALSE);
		else
			i++;
	}
	return (TRUE);
}

int	main(int ac, char **av)
{
	t_simulation	*simulation;

	if ((ac == 6 && atoi(av[5]) != 0) || ac == 5 )
	{
		simulation = create_simulation(av);
		if (simulation)
		{
			if (simulation->param->nb_philo == 1)
			{
				printf("\t0\tPhilo n°1\t%s\n", THINKING);
				printf("\t0\tPhilo n°1\t%s\n", TAKING_FORK);
				printf("\t%s\tPhilo n°1\t%s\n", av[2], PRINT_DEAD);
			}
			else
				init_simulation(simulation);
			free_malloc(simulation);
		}
	}
	return (0);
}
