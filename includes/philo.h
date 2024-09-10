/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:07:45 by angerard          #+#    #+#             */
/*   Updated: 2024/09/10 15:41:26 by angerard         ###   ########.fr       */
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
# include <sys/time.h>
# include <unistd.h>

/* Structures */
typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				left_fork;
	int				right_fork;
}					t_philo;

typedef struct s_data
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printing;
	pthread_mutex_t	dead_check;
	int				nbr_philos;
	int				nbr_times_to_eat;
	int				dead;
}					t_data;

/* Function prototypes */
// args_checker.c
int					check_args(int argc, char **argv);

// utils.c
int					ft_atoi(const char *str);
int					ft_isdigit(int c);
void				ft_usleep(size_t time);

#endif
