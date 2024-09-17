/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:44:33 by angerard          #+#    #+#             */
/*   Updated: 2024/09/17 16:13:21 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * Checks the state of a philo to determine if they have died or finished eating.
 * If the philo has not eaten within the allowed time, the simulation is ended.
 * If a meal requirement is set and the philo has eaten the required number
 * of meals, the finished philosophers count is incremented.
 *
 * @param philo Pointer to the philosopher structure.
 * @param data Pointer to the simulation data structure.
 * @param philos_finished Ptn to the count of philos who have finished eating.
 */
void	check_philo_state(t_philo *philo, t_data *data, int *philos_finished)
{
	if (philo->last_meal_time && (get_time()
			- philo->last_meal_time) > (size_t)data->time_to_die)
	{
		printf("%zu %d died\n", get_time(), philo->id);
		pthread_mutex_lock(&data->simulation_mutex);
		data->simulation_over = 1;
		pthread_mutex_unlock(&data->simulation_mutex);
	}
	if (data->meals_required != -1
		&& philo->meals_eaten >= data->meals_required)
	{
		(*philos_finished)++;
	}
}

/**
 * Monitors the state of all philos to determine if any have died
 * or if all have finished eating. Iterates through each philo, checking if
 * they have exceeded the time to die or met the required meal count.
 * If all philos have finished the required number of meals, the simulation ends.
 *
 * @param data Pointer to the simulation data structure.
 */
void	check_philosophers(t_data *data)
{
	int	i;
	int	philos_finished;

	i = 0;
	philos_finished = 0;
	while (i < data->philos_nbr)
	{
		check_philo_state(&data->philos[i], data, &philos_finished);
		i++;
	}
	if (philos_finished == data->philos_nbr)
	{
		ft_usleep(1000);
		printf("All philosophers have eaten %d meals\n", data->meals_required);
		pthread_mutex_lock(&data->simulation_mutex);
		data->simulation_over = 1;
		pthread_mutex_unlock(&data->simulation_mutex);
	}
}

/**
 * The monitoring routine for the simulation, executed by a separate thread.
 * Continuously checks the state of all philos to detect if the simul should end.
 * It monitors for either a philo dying or all philo completing their meals.
 * The loop terminates when `simulation_over` is set to 1.
 *
 * @param arg Ptn to the data struct (cast to void* for pthread compatibility).
 * @return NULL when monitoring finishes.
 */
void	*monitor_philos(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		pthread_mutex_lock(&data->simulation_mutex);
		if (data->simulation_over)
		{
			pthread_mutex_unlock(&data->simulation_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->simulation_mutex);
		check_philosophers(data);
		ft_usleep(100);
	}
	return (NULL);
}
