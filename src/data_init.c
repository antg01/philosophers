/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:15:27 by angerard          #+#    #+#             */
/*   Updated: 2024/09/16 10:17:20 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	assign_args(t_data *data, int argc, char **argv)
{
	data->philos_nbr = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->philos_nbr <= 0 || data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0)
	{
		printf("Error: arguments missing.\n");
		return (1);
	}
	if (argc == 6)
	{
		data->meals_required = ft_atoi(argv[5]);
		if (data->meals_required < 0)
		{
			printf("Error: Invalid meal count.\n");
			return (1);
		}
	}
	else
		data->meals_required = -1;
	return (0);
}

int	allocate_memory(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->philos_nbr);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philos_nbr);
	if (!data->philos || !data->forks)
	{
		printf("Error: Memory allocation failed.\n");
		return (1);
	}
	return (0);
}

int	initialize_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_nbr)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->philos_nbr;
		data->philos[i].meals_eaten = 0;
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (0);
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	if (data->forks)
	{
		while (i < data->philos_nbr)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	if (data->philos)
		free(data->philos);
}

int	init_data(t_data *data, int argc, char **argv)
{
	if (assign_args(data, argc, argv) != 0)
		return (1);
	if (allocate_memory(data) != 0)
		return (1);
	return (initialize_philosophers(data));
}
