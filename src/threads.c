/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:55:08 by angerard          #+#    #+#             */
/*   Updated: 2024/09/25 13:33:02 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * Creates threads for each philosopher in the simulation.
 * Each philo is assigned to a thread, executing the `philos_routine` function.
 * If a thread creation fails, an error message is printed with the
 * corresponding philo's ID.
 *
 * @param data Pointer to the simulation data structure.
 * @return 0 on success
 */
int	create_philos_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_nbr)
	{
		data->philos[i].data = data;
		if (pthread_create(&data->philos[i].thread, NULL, philos_routine,
				&data->philos[i]) != 0)
		{
			printf("Error: Failed to create thread for philosopher %d\n",
				data->philos[i].id);
		}
		i++;
	}
	return (0);
}

/**
 * Creates a separate thread to monitor the philosophers' states.
 * The monitor thread executes the `monitor_philos` function
 * to oversee the simulation. If the monitor thread creation fails,
 * an error message is printed.
 *
 * @param data Pointer to the simulation data structure.
 * @param monitor_thread Pointer to the pthread_t var for the monitor thread.
 * @return 0 on success, 1 if the thread creation fails.
 */
int	create_monitor_threads(t_data *data, pthread_t *monitor_thread)
{
	if (pthread_create(monitor_thread, NULL, monitor_philos, data) != 0)
	{
		printf("Error: Failed to create monitor thread\n");
		return (1);
	}
	return (0);
}

/**
 * Joins all the threads created for the simulation, including the monitor
 * thread and philo threads. Ensures that the main program waits for
 * the monitor thread and all philo threads to finish execution.
 *
 * @param data Pointer to the simulation data structure.
 * @param monitor_thread The pthread_t variable for the monitor thread.
 */

void	join_threads(t_data *data, pthread_t monitor_thread)
{
	int	i;

	i = 0;
	pthread_join(monitor_thread, NULL);
	while (i < data->philos_nbr)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}
