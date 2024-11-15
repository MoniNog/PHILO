/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@lausanne42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:27:34 by monoguei          #+#    #+#             */
/*   Updated: 2024/11/15 12:19:00 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parsing(t_param **param, char **av)
{
		*param = malloc(sizeof(t_param));
	
		
	(*param)->nb_philo = atoi(av[1]);
	(*param)->t_die = atoi(av[2]);
	(*param)->t_eat = atoi(av[3]);
	(*param)->t_sleep = atoi(av[4]);
	(*param)->t_each_philo_eat = atoi(av[5]);

	(*param)->philos = malloc(sizeof(t_philo) * (*param)->nb_philo);
}

int main(int ac, char **av)
{
	t_param	*param;

	param = NULL;
	if (ac == 6)
		parsing(&param, av);
	
    printf("nb philo : %i\n", param->nb_philo);
	printf("time to die : %i\n", param->t_die);
	printf("time to eat : %i\n", param->t_eat);
	printf("time to sleep : %i\n", param->t_sleep);
	printf("times each philo eats : %i\n", param->t_each_philo_eat);
	return 0;
}