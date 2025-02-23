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
#define COLOR_YELLOW  "\033[93m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_GREY    "\033[30m"

#define TAKING_FORK COLOR_YELLOW "has taken a fork 🍴" 	  COLOR_RESET
#define EATING      COLOR_GREEN  "    is eating 🍝 "      COLOR_RESET
#define SLEEPING    COLOR_BLUE   "  is sleeping 💤 "      COLOR_RESET
#define THINKING    COLOR_GREY	 "  is thinking 🤔 "      COLOR_RESET
#define PRINT_DEAD	COLOR_RED    "         died 💀 "      COLOR_RESET

#define THINK 1
#define EAT 2
#define SLEEP 3
#define DEAD 0
#define ALIVE 1
#define OFF 0
#define ON 1
#define NO_PARAM -1
#define TRUE 1
#define FALSE 0
#define LOCKED 1
#define UNLOCKED 0

typedef	struct s_philo
{
	// pthread				*thread;
	int					id_philo;
	int					activity;
	pthread_mutex_t		left_fork;
	int					state_fork;//LOCKED / UNLOCKED
	struct timeval		last_meal;
	struct s_simulation	*simulation;// pour utiliser routine (limitation par le prototype)
	pthread_t			*thread;
	int					meals_eaten;
}						t_philo;

typedef struct s_simulation
{
	struct s_param		*param;
	struct timeval		t0_simulation;
	struct s_philo		*philosophers;
	int					status; // 0 OFF | 1 ON
	pthread_mutex_t		print_mutex;
}						t_simulation;

typedef struct s_param
{
	int					nb_philo;
	long				t_die;
	long				t_eat;
	long				t_sleep;
	long				times_each_philo_must_eat;
}						t_param;

void 	init_simulation(t_simulation *simulation);
void	*routine(void *arg);
int		dead_or_alive(t_simulation *simulation, t_philo *philo);
void	eat(t_simulation *simulation, t_philo *philo);
void	sleeep(t_simulation *simulation, t_philo *philo);
void	think(t_simulation *simulation, t_philo *philo);
long	get_diff(struct timeval *start);
void 	print_philosopher_state(long timestamp_in_ms, t_philo *philo, char *state_message);
int		free_malloc(t_simulation *simulation);
int 	param_are_valid(char **av);
t_simulation	*create_simulation(char **av);


#endif