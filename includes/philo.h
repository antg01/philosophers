/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:07:45 by angerard          #+#    #+#             */
/*   Updated: 2024/09/17 15:22:23 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* Includes */
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

/* Structures */
typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				meals_eaten;
	size_t			last_meal_time;
	pthread_t		thread;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				philos_nbr;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	int				simulation_over;
	pthread_mutex_t	simulation_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}					t_data;

/* Function prototypes */
// args_checker.c
int					check_args(int argc, char **argv);

// data_init.c
int					init_data(t_data *data, int argc, char **argv);
void				free_data(t_data *data);

// routine.c
void				*philos_routine(void *arg);

// monitoring.c
void				*monitor_philos(void *arg);

// threads.c
int					create_philos_threads(t_data *data);
int					create_monitor_threads(t_data *data,
						pthread_t *monitor_thread);
void				join_threads(t_data *data, pthread_t monitor_thread);

// utils.c
int					ft_atoi(const char *str);
int					ft_isdigit(int c);
void				ft_usleep(size_t time);
size_t				get_time(void);

#endif
