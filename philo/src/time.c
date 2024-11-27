/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@lausanne42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:18:09 by monoguei          #+#    #+#             */
/*   Updated: 2024/11/27 16:57:21 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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


