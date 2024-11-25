/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:19:55 by angerard          #+#    #+#             */
/*   Updated: 2024/09/25 13:32:30 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * Checks if the given string represents a positive integer.
 * It ensures the string does not start with a negative sign
 * and that all characters are digits.
 *
 * @param str The string to check.
 * @return 1 if the string is a positive integer, 0 otherwise.
 */
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

/**
 * Validates the number of philosophers for the simulation.
 * Ensures the number of philosophers is at least two and no more than 200.
 *
 * @param argv Array of command line arguments.
 * @return 1 if the number is valid, 0 otherwise with an error message.
 */
static int	check_philos_nbr(char **argv)
{
	int	philos_nbr;

	philos_nbr = ft_atoi(argv[1]);
	if (philos_nbr <= 1)
	{
		printf("Error: There must be at least two philosophers.\n");
		return (0);
	}
	if (philos_nbr > 200)
	{
		printf("Error: Max nbr of philosophers suggested is 200.\n");
		return (0);
	}
	return (1);
}

/**
 * Validates the command line arguments for the philosopher simulation.
 * Ensures the number of arguments is between 5 and 6, and that all
 * arguments are positive integers.
 *
 * @param argc Number of command line arguments.
 * @param argv Array of command line arguments.
 * @return 1 if all arguments are valid, 0 otherwise with an error message.
 */
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

/**
 * Checks the validity of command line arguments for the simulation.
 * First, it validates the arguments format and number using `validate_args`.
 * Then, it checks the number of philosophers using `check_philos_nbr`.
 *
 * @param argc Number of command line arguments.
 * @param argv Array of command line arguments.
 * @return 1 if all checks pass, 0 otherwise.
 */
int	check_args(int argc, char **argv)
{
	if (!validate_args(argc, argv))
		return (0);
	if (!check_philos_nbr(argv))
		return (0);
	return (1);
}
