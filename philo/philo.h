#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

struct s_param;

typedef	struct s_philo
{
	int				id_philo;// numero du philo
	int				activity; // 1 think, 2 eat, 3 sleep, 0 die
	struct timeval	last_meal;
	struct timeval	t0_simulation;
	struct s_param	*param;
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
void	*activity(void *arg);
void	eat(t_param *param, t_philo *philo);
void	sleeep(t_param *param, t_philo *philo);
void	think(t_philo *philo);
long	get_diff(struct timeval *start);





// typedef struct s_thread;
// {
// 	pthread_t	thread;
// 	int			etat;
// 	pmutex_t	mutexl	
// }				t_thread;

#endif