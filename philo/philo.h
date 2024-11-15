#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>

typedef	struct s_philos
{
	int		id_philo;// numero du philo
	int		activity; //1 think, 2 eat, 3 sleep, 0 die

}				t_philo;

typedef struct s_param
{
	int		nb_philo;
	t_philo	*philos;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		t_each_philo_eat;
}			t_param;




// typedef struct s_thread;
// {
// 	pthread_t	thread;
// 	int			etat;
// 	pmutex_t	mutexl	
// }				t_thread;

#endif