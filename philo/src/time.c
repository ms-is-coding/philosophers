/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 02:42:53 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/23 16:46:08 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdint.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

int64_t	time_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int64_t	timestamp(t_sim *sim)
{
	return (time_now() - sim->start_time);
}

void	time_sleep(int32_t time_ms)
{
	int64_t	now;
	int64_t	start;

	now = time_now();
	start = now;
	while (now - start < time_ms)
	{
		usleep(100);
		now = time_now();
	}
}

int	await_active(t_philo *philo)
{
	while (1)
	{
		if (atomic_load(&philo->sim->active))
			break ;
		if (atomic_load(&philo->sim->should_end))
			return (-1);
		usleep(10);
	}
	atomic_store(&philo->last_meal, time_now());
	return (0);
}
