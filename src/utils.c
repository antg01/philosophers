/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:25:07 by angerard          #+#    #+#             */
/*   Updated: 2024/09/17 10:14:22 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		printf("Error in time external function!\n");
		return (0);
	}
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(size_t time_in_ms)
{
	size_t	start;
	size_t	current_time;

	start = get_time();
	while ((current_time = get_time()) != (size_t)-1 && (current_time
			- start) < time_in_ms)
	{
		if (time_in_ms - (current_time - start) > 10)
		{
			usleep(1000);
		}
		else
		{
			usleep(100);
		}
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
