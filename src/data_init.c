/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:15:27 by angerard          #+#    #+#             */
/*   Updated: 2024/09/17 16:02:40 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * Assigns the command line arguments to the simulation data structure.
 * Extracts the number of philos, time to die, time to eat, and time to sleep.
 * Optionally assigns the number of meals required if provided.
 * Ensures all values are positive and valid.
 *
 * @param data Pointer to the simulation data structure.
 * @param argc Number of command line arguments.
 * @param argv Array of command line arguments.
 * @return 0 on success, 1 if any argument is invalid or missing.
 */
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

/**
 * Allocates memory for the philosophers and forks arrays.
 * The number of philos and forks is based on the `philos_nbr` value.
 * Ensures that memory allocation is successful for both arrays.
 *
 * @param data Pointer to the simulation data structure.
 * @return 0 on success, 1 if memory allocation fails.
 */
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

/**
 * Initializes the philosopher structures and assigns forks.
 * Each philosopher is given an ID, a left fork, and a right fork.
 * Also initializes the mutex for each fork.
 *
 * @param data Pointer to the simulation data structure.
 * @return 0 on successful initialization.
 */
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

/**
 * Frees the dynamically allocated memory and destroys the mutexes.
 * Destroys the mutexes for the forks and the simulation mutex.
 * Frees the memory allocated for the forks and philosophers arrays.
 *
 * @param data Pointer to the simulation data structure.
 */
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
	pthread_mutex_destroy(&data->simulation_mutex);
}

/**
 * Initializes the simulation data by assigning command line arguments,
 * allocating necessary memory, and initializing the philosopher structures.
 * Calls `assign_args` to validate and assign arguments, `allocate_memory`
 * to allocate memory for philosophers and forks, and
 * `initialize_philosophers` to set up each philosopher.
 *
 * @param data Pointer to the simulation data structure.
 * @param argc Number of command line arguments.
 * @param argv Array of command line arguments.
 * @return 0 on successful initialization, 1 on failure.
 */
int	init_data(t_data *data, int argc, char **argv)
{
	if (assign_args(data, argc, argv) != 0)
		return (1);
	if (allocate_memory(data) != 0)
		return (1);
	return (initialize_philosophers(data));
}
