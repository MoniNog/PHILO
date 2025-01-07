#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[43m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_GREY    "\033[30m"

#define TAKING_FORK COLOR_YELLOW "has taken a fork 🍴 " COLOR_RESET
#define EATING      COLOR_GREEN  "is eating 🍝 "        COLOR_RESET
#define SLEEPING    COLOR_BLUE   "is sleeping 💤 "      COLOR_RESET
#define THINKING    COLOR_GREY	 "is thinking 🤔 "      COLOR_RESET
#define PRINT_DEAD	COLOR_RED    "died 💀 "             COLOR_RESET

#define THINK 1
#define EAT 2
#define SLEEP 3
#define DEAD 0

struct s_param;

typedef	struct s_philo
{
	int				id_philo;// numero du philo
	int				activity; // 1 think, 2 eat, 3 sleep, 0 die
	struct timeval	last_meal;
	struct timeval	t0_simulation; //to remove
	struct s_param	*param; //to remove
}				t_philo;

typedef struct s_simulation
{
	struct s_param	*param;
	struct timeval	t0_simulation;
	t_philo			*philosophers;
}					t_simulation;
// PAS OUBLIER DE SUPPR DOUBLONS

typedef struct s_param
{
	int		nb_philo;
	long	t_die;
	t_philo	*philos;// to remove
	long	t_eat;
	long	t_sleep;
	long	times_each_philo_must_eat;
}			t_param;

void 	initialize_simulation(t_param *param);
void	*routine(void *arg);
void	eat(t_param *param, t_philo *philo);
void	sleeep(t_param *param, t_philo *philo);
void	think(t_philo *philo);
long	get_diff(struct timeval *start);
void print_philosopher_state(long timestamp_in_ms, t_philo *philo, const char *state_message);


// pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;

// typedef struct s_thread;
// {
// 	pthread_t	thread;
// 	int			etat;
// 	pmutex_t	mutexl	
// }				t_thread;

#endif