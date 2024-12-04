/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:07:21 by angerard          #+#    #+#             */
/*   Updated: 2024/12/04 15:32:42 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_action(t_philo *philo, char *msg, char *color)
{
	if (is_philo_dead(philo) == 1)
		return ;
	pthread_mutex_lock(philo->print_mutex);
	if (color != NULL)
		printf("%s", color);
	printf("%lu | Philosopher %d %s\n", get_time() % 1000000, philo->id, msg);
	printf(DEFAULT);
	pthread_mutex_unlock(philo->print_mutex);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (!check_args(argc, argv))
		return (1);
	if (init_data(&data, argc, argv) == 1)
		return (1);
	create_threads(&data);
	return (0);
}
