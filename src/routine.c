/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:41:21 by angerard          #+#    #+#             */
/*   Updated: 2024/12/04 15:27:07 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	is_thinking(t_philo *philo)
{
	print_action(philo, "is thinking", NULL);
}

void	is_sleeping(t_philo *philo)
{
	print_action(philo, "is sleeping", DEFAULT);
	ft_usleep(philo->time_to_sleep);
	print_action(philo, "finished sleeping", DEFAULT);
}

void	pick_up_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "picked up the left fork", NULL);
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "picked up the right fork", NULL);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "picked up the right fork", NULL);
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "picked up the left fork", NULL);
	}
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	print_action(philo, "dropped the left fork", NULL);
	pthread_mutex_unlock(philo->right_fork);
	print_action(philo, "dropped the right fork", NULL);
}

void	is_eating(t_philo *philo)
{
	pick_up_forks(philo);
	pthread_mutex_lock(&(philo->eating_mutex));
	print_action(philo, "is eating", YELLOW);
	philo->last_meal_time = get_time();
	philo->meal_count++;
	if (*(philo->meals_required) != -1)
	{
		if (philo->meal_count == *(philo->meals_required))
		{
			philo->is_full = 1;
			pthread_mutex_unlock(&(philo->eating_mutex));
			ft_usleep(philo->time_to_eat);
			put_down_forks(philo);
			print_action(philo, "is full", DEFAULT);
			return ;
		}
	}
	pthread_mutex_unlock(&(philo->eating_mutex));
	ft_usleep(philo->time_to_eat);
	put_down_forks(philo);
	print_action(philo, "finished eating", DEFAULT);
}
