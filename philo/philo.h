/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:04:46 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/23 20:55:09 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>

# define C_R   "\033[0m"
# define COLOR_RED     "\033[31m"
# define COLOR_GR      "\033[32m"
# define COLOR_YELLOW  "\033[93m"
# define COLOR_BLUE    "\033[34m"
# define COLOR_GREY    "\033[30m"

# define TAKING_FORK "has taken a fork 🍴"
# define EATING      "    is eating 🍝 "
# define SLEEPING    "  is sleeping 💤 "
# define THINKING    "  is thinking 🤔 "
# define PRINT_DEAD  "         died 💀 "

# define THINK 1
# define EAT 2
# define SLEEP 3
# define DEAD 0
# define ALIVE 1
# define OFF 0
# define ON 1
# define NO_PARAM -1
# define TRUE 1
# define FALSE 0
# define LOCKED 1
# define UNLOCKED 0

typedef struct s_philo
{
	int					id_philo;
	int					activity;
	pthread_mutex_t		left_fork;
	int					state_fork;
	struct timeval		last_meal;
	struct s_simulation	*simulation;
	pthread_t			*thread;
	int					meals_eaten;
}						t_philo;

typedef struct s_simulation
{
	struct s_param		*param;
	struct timeval		t0_simulation;
	struct s_philo		*philosophers;
	int					status;
	pthread_mutex_t		status_mutex;
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

//	MAIN
int				param_are_valid(char **av);
int				ft_atoi(const char *str);

//	INIT
int				free_malloc(t_simulation *simulation);
void			init_simulation(t_simulation *simulation);
t_simulation	*create_simulation(char **av);
//	ACTIVITY
void			eat(t_simulation *simulation, t_philo *philo);
void			sleeep(t_simulation *simulation, t_philo *philo);
void			think(t_simulation *simulation, t_philo *philo);
void			pr_s(long timestamp_in_ms, t_philo *philo,
					char *state_message);
//	ROUTINE
long			get_diff(struct timeval *start);
int				dead_or_alive(t_simulation *simulation, t_philo *philo);
void			*routine(void *arg);

#endif