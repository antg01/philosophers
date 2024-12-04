/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:25:07 by angerard          #+#    #+#             */
/*   Updated: 2024/12/04 15:26:09 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	get_time(void)
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

void	ft_usleep(size_t time)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < time)
	{
		usleep(200);
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
