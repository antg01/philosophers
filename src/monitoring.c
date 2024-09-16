/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:44:33 by angerard          #+#    #+#             */
/*   Updated: 2024/09/16 15:57:14 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*monitor_philos(void *arg)
{
	t_data	*data;
	int		philos_finished;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
        philos_finished = 0;
		while (i < data->philos_nbr)
		{
			if ((get_time() - data->philos[i].last_meal_time) > (size_t)data->time_to_die)
			{
				printf("%zu ms: Philosopher %d died\n", get_time(), data->philos[i].id);
				return (NULL);
			}
			if (data->meals_required != -1 && data->philos[i].meals_eaten >= data->meals_required)
                philos_finished++;
			i++;
		}
		if (philos_finished == data->philos_nbr)
        {
            printf("All philosophers have eaten %d meals\n", data->meals_required);
			return (NULL);
        }
		ft_usleep(200);
	}
}
