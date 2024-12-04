/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:44:33 by angerard          #+#    #+#             */
/*   Updated: 2024/12/04 15:27:18 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_philo_status(t_data *data, int i, int *full_count)
{
	if (data->max_meals == -1)
	{
		data->philos[i].is_full = 0;
		return (0);
	}
	if (data->philos[i].is_full == 1)
	{
		*full_count = *full_count + 1;
		data->philos[i].is_full = -1;
	}
	if (*full_count >= data->nbr_philos)
	{
		print_action(&(data->philos[i]), "all are full!", GREEN);
		pthread_mutex_lock(&(data->death_lock));
		data->is_dead = 1;
		pthread_mutex_unlock(&(data->death_lock));
		return (1);
	}
	return (0);
}

int	check_philo_death(t_data *data, int i)
{
	if (data->philos[i].is_full == 0 && get_time()
		- data->philos[i].last_meal_time > data->philos[i].time_to_die)
	{
		print_action(&(data->philos[i]), "died!", RED);
		pthread_mutex_lock(&(data->death_lock));
		data->is_dead = 1;
		pthread_mutex_unlock(&(data->death_lock));
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *ptr)
{
	t_data	*data;
	int		i;
	int		full_count;

	data = (t_data *)ptr;
	full_count = 0;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&(data->philos[i].eating_mutex));
		if (check_philo_death(data, i) == 1 || check_philo_status(data, i,
				&full_count) == 1)
		{
			pthread_mutex_unlock(&(data->philos[i].eating_mutex));
			return (NULL);
		}
		pthread_mutex_unlock(&(data->philos[i].eating_mutex));
		i++;
		if (i == data->nbr_philos)
			i = 0;
	}
	return (ptr);
}
