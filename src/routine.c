/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:41:21 by angerard          #+#    #+#             */
/*   Updated: 2024/09/17 09:52:43 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*philos_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
        if (data->meals_required != -1 && philo->meals_eaten >= data->meals_required)
            break;
		// philo think
		printf("%zu %d is thinking\n", get_time(), philo->id);

        // takes fork
		pthread_mutex_lock(&data->forks[philo->left_fork]);
		printf("%zu %d has taken a fork\n", get_time(), philo->id);
		pthread_mutex_lock(&data->forks[philo->right_fork]);
		printf("%zu %d has taken a fork\n", get_time(), philo->id);

		// philo eats
		philo->last_meal_time = get_time();
		philo->meals_eaten++;
		// printf("%zu ms %d is eating his %dnd meal\n", get_time(), philo->id, philo->meals_eaten);
		printf("%zu %d is eating\n", get_time(), philo->id);
        // Simulate time passing by
		ft_usleep(data->time_to_eat);

		// unlock mutex
		pthread_mutex_unlock(&data->forks[philo->left_fork]);
		pthread_mutex_unlock(&data->forks[philo->right_fork]);

		// philo sleeps
		printf("%zu %d is sleeping\n", get_time(), philo->id);
		ft_usleep(data->time_to_sleep);
	}
	return (NULL);
}
