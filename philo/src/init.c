/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@lausanne42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:16:31 by monoguei          #+#    #+#             */
/*   Updated: 2024/11/27 17:11:25 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void create_pthread(t_param *param)
{
	pthread_t	*thread;
	int			i;

	thread = malloc(sizeof(pthread_t *) * param->nb_philo);

	i = 0;
	printf("philo numero : %i\n", param->nb_philo);
	while (i < param->nb_philo) // initialisation
	{
		param->philos[i].id_philo = i + 1;
		param->philos[i].param = param;
		param->philos[i].activity = 1;
		i++;
	}

	i = 0;
	while (i < param->nb_philo) // lancement
	{
		pthread_create(thread, NULL, activity, (void *)&param->philos[i]);
		i++;
	}

	i = 0;
	while (i < param->nb_philo) // attente
	{
		pthread_join(thread[i], NULL);
		i++;
	}
	
	

	// pthread_t	t2;
	// param->philos->id_philo = 1;
	// pthread_create(&t2, NULL, &activity, param);
	// pthread_join(t2, NULL);
}

int	dead_or_alive(t_param *param, t_philo *philo)
{
	if (param->t_die <= get_diff(&philo->last_meal))
	{
		philo->activity = 0;
		printf("\ttimestamp : %li\t\tphilo number %i\t\tis DEADDD\n", get_diff(&philo->t0_simulation), philo->id_philo);
		return (0); // dead
	}
	else
		return (1); // alive
}

void	*activity(void *arg)
{
    t_philo *philo;
    t_param *param;

    philo = (t_philo *)arg;
    param = philo->param;
    gettimeofday(&philo->last_meal, NULL); // Initialiser last_meal avec l'heure actuelle
    gettimeofday(&philo->t0_simulation, NULL);
	while (philo->activity != 0)
    {	
        if (dead_or_alive(param, philo) == 1)
        {
            if (philo->activity == 1)
                think(philo);
            else if (philo->activity == 2)
                eat(param, philo);
            else if (philo->activity == 3)
                sleeep(param, philo);
        }
        else
        {
            philo->activity = 0; // dead
        }
    }
    return (NULL);
}

