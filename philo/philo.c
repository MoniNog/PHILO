/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@lausanne42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:27:34 by monoguei          #+#    #+#             */
/*   Updated: 2024/11/22 11:56:03 by monoguei         ###   ########.fr       */
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
	if (av[5])
		(*param)->times_each_philo_must_eat = atoi(av[5]);

	(*param)->philos = malloc(sizeof(t_philo) * (*param)->nb_philo);
}

int main(int ac, char **av)
{
	// t_param	*param;
	(void)ac;
	(void)av;
	t_param *param; 

	if (ac == 6 || ac == 5)
		parsing(&param, av);
    printf("nb philo : %i\n", param->nb_philo);
	printf("time to die : %li\n", param->t_die);
	printf("time to eat : %li\n", param->t_eat);
	printf("time to sleep : %li\n", param->t_sleep);
	if (ac == 6)
		printf("times each philo eats : %li\n", param->times_each_philo_must_eat);
	create_pthread(param);
	return 0;
}