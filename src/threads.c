/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:55:08 by angerard          #+#    #+#             */
/*   Updated: 2024/12/04 15:21:23 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_philo_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->death_lock);
	if (*(philo->is_dead) == 1)
	{
		pthread_mutex_unlock(philo->death_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->death_lock);
	return (0);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (is_philo_dead(philo) != 1)
	{
		pthread_mutex_lock(&(philo->eating_mutex));
		if (philo->is_full != 0)
		{
			pthread_mutex_unlock(&(philo->eating_mutex));
			continue ;
		}
		pthread_mutex_unlock(&(philo->eating_mutex));
		is_eating(philo);
		is_sleeping(philo);
		is_thinking(philo);
	}
	return (ptr);
}

int	create_threads(t_data *data)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	while (i < data->nbr_philos)
	{
		if (pthread_create(&(data->philos[i].thread), NULL, &philo_routine,
				&(data->philos[i])) != 0)
			return (printf("Error: Thread creation failed!\n"), 1);
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor_routine, data) != 0)
		return (printf("Error: Thread creation failed!\n"), 1);
	i = 0;
	while (i < data->nbr_philos)
	{
		if (pthread_join(data->philos[i++].thread, NULL) != 0)
			return (printf("Error: Thread join failed!\n"), 1);
	}
	if (pthread_join(monitor_thread, NULL) != 0)
		return (printf("Error: Thread join failed!\n"), 1);
	free(data->philos);
	free(data->forks);
	return (0);
}
