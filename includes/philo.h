/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:10:03 by angerard          #+#    #+#             */
/*   Updated: 2024/12/04 15:24:15 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define DEFAULT "\001\033[0;39m\002"
# define RED "\001\033[1;91m\002"
# define GREEN "\001\033[1;92m\002"
# define YELLOW "\001\033[1;93m\002"

typedef struct s_philo
{
	int				id;
	int				*is_dead;
	int				is_full;
	int				*meals_required;
	int				meal_count;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*death_lock;
	pthread_mutex_t	eating_mutex;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			last_meal_time;
	pthread_t		thread;
}					t_philo;

typedef struct s_data
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_lock;
	int				nbr_philos;
	int				max_meals;
	int				is_dead;
}					t_data;

// actions.c
int					check_args(int argc, char **argv);
int					init_philos(t_data *data, char *argv[], int index);
int					init_forks(t_data *data);
int					init_data(t_data *data, int argc, char *argv[]);
int					is_philo_dead(t_philo *philo);
void				*philo_routine(void *ptr);
int					create_threads(t_data *data);
void				is_thinking(t_philo *philo);
void				is_sleeping(t_philo *philo);
void				pick_up_forks(t_philo *philo);
void				put_down_forks(t_philo *philo);
void				is_eating(t_philo *philo);
int					check_philo_status(t_data *data, int index,
						int *full_count);
int					check_philo_death(t_data *data, int index);
void				*monitor_routine(void *ptr);
void				print_action(t_philo *philo, char *message, char *color);
size_t				get_time(void);
void				ft_usleep(size_t duration);
int					ft_isdigit(int c);
int					ft_atoi(const char *str);

#endif
