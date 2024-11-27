/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@lausanne42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:27:34 by monoguei          #+#    #+#             */
/*   Updated: 2024/11/27 15:53:53 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_param	*parsing(char **av)
{// check atoi nb positif uniquement
	t_param	*param;

	param = malloc(sizeof(t_param));
	param->nb_philo = atoi(av[1]);
	param->t_die = atoi(av[2]);
	param->t_eat = atoi(av[3]);
	param->t_sleep = atoi(av[4]);
	param->philos = malloc(sizeof(t_philo) * param->nb_philo);
	if (av[5])
		param->times_each_philo_must_eat = atoi(av[5]);
	else
		param->times_each_philo_must_eat = -1;
	return (param);
}

int main(int ac, char **av)
{
	t_param *param; 

	if (ac == 6 || ac == 5)
	{
		param = parsing(av);
		create_pthread(param);
	}
	return 0;
}