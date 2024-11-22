#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

typedef	struct s_philos
{
	int				id_philo;// numero du philo
	int				activity; // 1 think, 2 eat, 3 sleep, 0 die
	struct timeval	last_meal;
}				t_philo;

typedef struct s_param
{
	int		nb_philo;
	t_philo	*philos;
	long	t_die;
	long	t_eat;
	long	t_sleep;
	long	times_each_philo_must_eat;
}			t_param;

void 	create_pthread(t_param *param);
void	*activity(void *param);
void	eat(t_param *param);
void	sleeep(t_param *param);
void	think(t_param *param);
long	get_diff(struct timeval *start);





// typedef struct s_thread;
// {
// 	pthread_t	thread;
// 	int			etat;
// 	pmutex_t	mutexl	
// }				t_thread;

#endif