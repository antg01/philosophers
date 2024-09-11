/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:07:45 by angerard          #+#    #+#             */
/*   Updated: 2024/09/11 09:40:01 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* Constants */
# define EXIT_FAILURE 1

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
	pthread_t		thread;
}					t_philo;

typedef struct s_data
{
	int				philos_nbr;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}					t_data;

/* Function prototypes */
// args_checker.c
int					check_args(int argc, char **argv);

// data_init.c
int					init_data(t_data *data, int argc, char **argv);

// utils.c
int					ft_atoi(const char *str);
int					ft_isdigit(int c);
void				ft_usleep(size_t time);

#endif
