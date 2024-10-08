/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:41:21 by angerard          #+#    #+#             */
/*   Updated: 2024/10/07 11:22:19 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * Handles the eating action for a philo, alternating fork acquisition order
 * based on the philo's ID. Odd-numbered philos pick up the left fork first,
 * while even-numbered philos pick up the right fork first. Once both forks are
 * acquired, the philo starts eating, updates the last meal time, and increments
 * meals eaten. After eating for the specified duration, both forks are released.
 *
 * @param philo Pointer to the philo structure.
 * @param data Pointer to the simulation data structure.
 */
static void	philo_eat(t_philo *philo, t_data *data)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(&data->forks[philo->left_fork]);
		printf("%zu %d has taken a fork\n", get_time(), philo->id);
		pthread_mutex_lock(&data->forks[philo->right_fork]);
		printf("%zu %d has taken a fork\n", get_time(), philo->id);
	}
	else
	{
		pthread_mutex_lock(&data->forks[philo->right_fork]);
		printf("%zu %d has taken a fork\n", get_time(), philo->id);
		pthread_mutex_lock(&data->forks[philo->left_fork]);
		printf("%zu %d has taken a fork\n", get_time(), philo->id);
	}
	pthread_mutex_lock(&data->philo_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&data->philo_mutex);
	printf("%zu %d is eating\n", get_time(), philo->id);
	ft_usleep(data->time_to_eat);
	pthread_mutex_unlock(&data->forks[philo->right_fork]);
	pthread_mutex_unlock(&data->forks[philo->left_fork]);
}

/**
 * The routine function executed by each philosopher thread.
 * The philosopher alternates between thinking, eating, and sleeping.
 * It checks if the simulation is over or if the philosopher has eaten
 * the required number of meals before proceeding with the actions.
 * Each action (think, eat, sleep) is accompanied by appropriate log messages.
 * The routine loops until the simulation ends or the meal count is met.
 *
 * @param arg Ptn to the philo struct (cast to void* for pthread compatibility).
 * @return NULL when the routine finishes.
 */
void	*philos_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		pthread_mutex_lock(&data->simulation_mutex);
		if (data->simulation_over)
		{
			pthread_mutex_unlock(&data->simulation_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->simulation_mutex);
		if (data->meals_required != -1
			&& philo->meals_eaten >= data->meals_required)
			break ;
		printf("%zu %d is thinking\n", get_time(), philo->id);
		ft_usleep(10);
		philo_eat(philo, data);
		printf("%zu %d is sleeping\n", get_time(), philo->id);
		ft_usleep(data->time_to_sleep);
		// ft_usleep(10);
	}
	return (NULL);
}
