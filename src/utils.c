/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:25:07 by angerard          #+#    #+#             */
/*   Updated: 2024/09/23 13:09:19 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * Retrieves the current time in milliseconds.
 * Uses the `gettimeofday` function to obtain the current time in seconds and ms.
 * Converts the time to milliseconds and returns it.
 * If `gettimeofday` fails, an error message is printed,
 * and the function returns -1.
 *
 * @return The current time in milliseconds, or (size_t) -1 on failure.
 */
size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		printf("Error in time external function!\n");
		return ((size_t) - 1);
	}
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/**
 * Custom implementation of a sleep function that pauses the execution for
 *  a given time in milliseconds. Continuously checks the current time
 * to avoid busy waiting and optimizes by using `usleep` for small delays.
 *
 * @param time_in_ms The amount of time to sleep in milliseconds.
 */
void	ft_usleep(size_t time_in_ms)
{
	size_t	start;
	size_t	current_time;

	start = get_time();
	current_time = get_time();
	if (start == (size_t)-1)
		return ;
	while (current_time != (size_t)-1 && (current_time - start) < time_in_ms)
	{
		if (time_in_ms - (current_time - start) > 10)
		{
			usleep(1000);
		}
		else
		{
			usleep(100);
		}
		current_time = get_time();
	}
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

static int	ft_isspace(const char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long int	base;
	long int	base2;
	int			sign;

	base = 0;
	base2 = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		base2 = base;
		base = 10 * base + (*str - '0');
		if (base < base2)
			return (~sign >> 1);
		str++;
	}
	return (base * sign);
}
