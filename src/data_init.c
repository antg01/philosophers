/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:15:27 by angerard          #+#    #+#             */
/*   Updated: 2024/12/04 15:09:30 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_philos(t_data *data, char *argv[], int index)
{
	while (++index < data->nbr_philos)
	{
		data->philos[index].id = index + 1;
		data->philos[index].left_fork = &(data->forks[index]);
		if (index == data->nbr_philos - 1)
			data->philos[index].right_fork = &(data->forks[0]);
		else
			data->philos[index].right_fork = &(data->forks[index + 1]);
		if (pthread_mutex_init(&(data->philos[index].eating_mutex), NULL) != 0)
		{
			printf("Error: Mutex initialization failed!\n");
			return (1);
		}
		data->philos[index].is_full = 0;
		data->philos[index].meals_required = &(data->max_meals);
		data->philos[index].print_mutex = &(data->print_mutex);
		data->philos[index].death_lock = &(data->death_lock);
		data->philos[index].is_dead = &(data->is_dead);
		data->philos[index].time_to_die = ft_atoi(argv[2]);
		data->philos[index].time_to_eat = ft_atoi(argv[3]);
		data->philos[index].time_to_sleep = ft_atoi(argv[4]);
		data->philos[index].last_meal_time = get_time();
	}
	return (0);
}

int	init_forks(t_data *data)
{
	int	index;

	index = 0;
	while (index < data->nbr_philos)
	{
		if (pthread_mutex_init(&(data->forks[index]), NULL) != 0)
		{
			printf("Error: Mutex initialization failed!\n");
			return (1);
		}
		index++;
	}
	return (0);
}

int	init_data(t_data *data, int argc, char *argv[])
{
	data->nbr_philos = ft_atoi(argv[1]);
	if (argc == 5)
		data->max_meals = -1;
	else
		data->max_meals = ft_atoi(argv[5]);
	data->is_dead = 0;
	if (pthread_mutex_init(&(data->print_mutex), NULL) != 0)
	{
		printf("Error: Mutex initialization failed!\n");
		return (1);
	}
	if (pthread_mutex_init(&(data->death_lock), NULL) != 0)
	{
		printf("Error: Mutex initialization failed!\n");
		return (1);
	}
	data->philos = malloc(sizeof(t_philo) * data->nbr_philos);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_philos);
	if (data->philos == NULL || data->forks == NULL)
		return (1);
	if (init_forks(data) == 1)
		return (1);
	if (init_philos(data, argv, -1) == 1)
		return (1);
	return (0);
}
