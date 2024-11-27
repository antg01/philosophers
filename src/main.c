/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:07:21 by angerard          #+#    #+#             */
/*   Updated: 2024/11/26 17:25:25 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * Terminates the philosopher simulation, ensuring a proper cleanup of threads
 * and resources before exiting the program. This function waits for all
 * philosopher threads to finish execution using pthread_join, displays a log
 * message indicating the philosopher who died, and then frees all allocated
 * resources. Finally, the program exits with a status of 1.
 *
 * @param data Pointer to the simulation data structure containing simulation
 * information and resources.
 * @param philo Pointer to the philosopher structure that triggered the
 * termination (e.g., the philosopher who died).
 */
void	terminate_simulation(t_data *data, t_philo *philo)
{
	int	i;

	if (data->philos)
	{
		i = 0;
		while (i < data->philos_nbr)
		{
			if (data->philos[i].thread)
				pthread_join(data->philos[i].thread, NULL);
			i++;
		}
	}
	printf("%zu %d died\n", get_time_timestamp(), philo->id);
}

/**
 * Main function to initialize and manage the philosopher simulation.
 * Handles argument validation, data initialization, thread creation,
 * and synchronization for the simulation. It ensures the proper
 * cleanup of resources before exiting.
 *
 * @param argc Number of command line arguments.
 * @param argv Array of command line arguments.
 * @return 1 on failure, 0 on success.
 */
int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor_thread;

	if (!check_args(argc, argv))
		return (1);
	if (init_data(&data, argc, argv) == 1)
		return (1);
	data.simulation_over = 0;
	pthread_mutex_init(&data.simulation_mutex, NULL);
	if (create_philos_threads(&data) != 0)
		return (1);
	if (create_monitor_threads(&data, &monitor_thread) != 0)
		return (1);
	join_threads(&data, monitor_thread);
	free_data(&data);
	return (0);
}
