/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:07:21 by angerard          #+#    #+#             */
/*   Updated: 2024/09/25 13:32:08 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
