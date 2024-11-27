/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:25:07 by angerard          #+#    #+#             */
/*   Updated: 2024/11/26 18:16:20 by angerard         ###   ########.fr       */
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
size_t	get_time_timestamp(void)
{
	struct timeval	current_time;
	static size_t	start_time = 0;
	size_t			current_ms;

	if (gettimeofday(&current_time, NULL) == -1)
	{
		printf("Error in time external function!\n");
		return ((size_t) - 1);
	}
	current_ms = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	if (start_time == 0)
		start_time = current_ms;
	return (current_ms - start_time);
}

/**
 * Custom implementation of a sleep function that pauses execution for
 * a given amount of time in milliseconds. Uses frequent checks to
 * ensure minimal delay and accuracy, even for small sleep durations.
 *
 * @param time_in_ms The amount of time to sleep in milliseconds.
 */
void	ft_usleep(size_t time_in_ms)
{
	size_t	start_time;
	size_t	current_time;

	start_time = get_time_timestamp();
	if (start_time == (size_t) - 1)
		return ;
	while (1)
	{
		current_time = get_time_timestamp();
		if (current_time == (size_t) - 1)
			break ;
		if ((current_time - start_time) >= time_in_ms)
			break ;
		usleep(100);
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
		if (base < base2 || base * sign > INT_MAX || base * sign < INT_MIN)
			return (printf("Error: Integer overflow or underflow\n"), 0);
		str++;
	}
	return (base * sign);
}
