/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:07:21 by angerard          #+#    #+#             */
/*   Updated: 2024/09/16 12:31:30 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor_thread;

	if (!check_args(argc, argv))
		return (1);
	if (init_data(&data, argc, argv) == 1)
		return (1);
	if (create_philos_threads(&data) != 0)
		return (1);
	if (create_monitor_threads(&data, &monitor_thread) != 0)
		return (1);
	join_threads(&data, monitor_thread);
	free_data(&data);
	return (0);
}
