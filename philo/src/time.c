/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 02:42:53 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/23 13:19:18 by smamalig         ###   ########.fr       */
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

void	time_sleep(t_sim *sim, int32_t time_ms)
{
	int64_t	now;
	int64_t	elapsed;
	int64_t	tick;
	int64_t	target;

	now = time_now();
	elapsed = now - sim->start_time;
	tick = elapsed / time_ms;
	target = sim->start_time + (tick + 1) * time_ms;
	if (target - now < 1)
		target += time_ms;
	while (now < target)
	{
		usleep(100);
		now = time_now();
	}
}

int	await_active(t_philo *philo)
{
	while (1)
	{
		if (philo->sim->active)
			break ;
		if (philo->sim->should_end)
			return (-1);
		usleep(100);
	}
	philo->last_meal = time_now();
	return (0);
}
