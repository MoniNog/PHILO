/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@lausanne42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:18:09 by monoguei          #+#    #+#             */
/*   Updated: 2025/01/07 11:07:37 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/// @brief calculate the diff between now and the start parameter 
/// @param start starting time (T0)
/// @return diff in millisecond since time T0 and now
long	get_diff(struct timeval *start)
{
	struct timeval	now;
	long			diff;

	gettimeofday(&now, NULL);
	diff = (now.tv_sec - start->tv_sec) * 1000;
	diff += (now.tv_usec - start->tv_usec) / 1000;
	return (diff);
}
