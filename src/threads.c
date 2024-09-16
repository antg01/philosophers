/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:55:08 by angerard          #+#    #+#             */
/*   Updated: 2024/09/16 12:31:14 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

int	create_monitor_threads(t_data *data, pthread_t *monitor_thread)
{
	if (pthread_create(monitor_thread, NULL, monitor_philos, data) != 0)
	{
		printf("Error: Failed to create monitor thread\n");
		return (1);
	}
	return (0);
}

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
