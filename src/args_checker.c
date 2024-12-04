/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:19:55 by angerard          #+#    #+#             */
/*   Updated: 2024/12/04 16:23:01 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	is_positive_int(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	check_philos_nbr(char **argv)
{
	int	philos_nbr;

	philos_nbr = ft_atoi(argv[1]);
	if (philos_nbr <= 1)
	{
		printf("Error: There must be at least two philos.\n");
		return (0);
	}
	if (philos_nbr > 200)
	{
		printf("Error: Max nbr of philos suggested is 200.\n");
		return (0);
	}
	return (1);
}

static int	validate_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("Error: Wrong number of arguments.\n");
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		if (!is_positive_int(argv[i]))
		{
			printf("Error: Argument %d is not a valid positive integer.\n", i);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	check_time_values(char **argv)
{
	int	time_value;
	int	i;

	i = 2;
	while (i <= 4)
	{
		time_value = ft_atoi(argv[i]);
		if (time_value < 60)
		{
			printf("Error: Arg %d must be at least 60ms.\n", i);
			return (0);
		}
		if (time_value > INT_MAX)
		{
			printf("Error: Arg %d exceeds the max int value.\n", i);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_args(int argc, char **argv)
{
	if (!validate_args(argc, argv))
		return (0);
	if (!check_philos_nbr(argv))
		return (0);
	if (!check_time_values(argv))
		return (0);
	return (1);
}
