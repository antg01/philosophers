/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:41:21 by angerard          #+#    #+#             */
/*   Updated: 2024/09/23 13:07:49 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * Handles the eating action for a philosopher.
 * The philosopher locks both forks (left and right) before eating.
 * It updates the philo's last meal time and increments the meals eaten count.
 * After eating for the specified duration, the philosopher unlocks both forks.
 *
 * @param philo Pointer to the philosopher structure.
 * @param data Pointer to the simulation data structure.
 */
static void	philo_eat(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->forks[philo->left_fork]);
	printf("%zu %d has taken a fork\n", get_time(), philo->id);
	pthread_mutex_lock(&data->forks[philo->right_fork]);
	printf("%zu %d has taken a fork\n", get_time(), philo->id);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	printf("%zu %d is eating\n", get_time(), philo->id);
	ft_usleep(data->time_to_eat);
	pthread_mutex_unlock(&data->forks[philo->left_fork]);
	pthread_mutex_unlock(&data->forks[philo->right_fork]);
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
		philo_eat(philo, data);
		printf("%zu %d is sleeping\n", get_time(), philo->id);
		ft_usleep(data->time_to_sleep);
	}
	return (NULL);
}
