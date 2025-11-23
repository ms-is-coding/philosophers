/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 20:14:22 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/23 14:13:28 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdatomic.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>

static void	philo_eat_meal(t_philo *philo, t_fork *first, t_fork *second)
{
	pthread_mutex_lock(&first->lock);
	philo_print(philo, "has taken a fork");
	pthread_mutex_lock(&second->lock);
	philo_print(philo, "has taken a fork");
	philo_print(philo, "is eating");
	atomic_store(&philo->last_meal, time_now());
	time_sleep(philo->sim, philo->sim->eat_time);
	atomic_fetch_add(&philo->meal_count, 1);
	if (philo->sim->meal_count > 0
		&& atomic_load(&philo->meal_count) == philo->sim->meal_count)
	{
		if (atomic_fetch_add(&philo->sim->saturated, 1) + 1
			== philo->sim->philo_count)
			atomic_store(&philo->sim->active, false);
	}
	pthread_mutex_unlock(&second->lock);
	pthread_mutex_unlock(&first->lock);
}

static void	philo_eat(t_philo *philo)
{
	t_fork	*first;
	t_fork	*second;

	if (philo->sim->philo_count == 1)
	{
		philo_print(philo, "has taken a fork");
		time_sleep(philo->sim, philo->sim->death_time + 10);
		return ;
	}
	first = philo->right;
	second = philo->left;
	if (philo->pick_left_first)
	{
		first = philo->left;
		second = philo->right;
		time_sleep(philo->sim, 1);
	}
	philo_eat_meal(philo, first, second);
}

static void	philo_sleep(t_philo *philo)
{
	philo_print(philo, "is sleeping");
	time_sleep(philo->sim, philo->sim->sleep_time);
}

static void	philo_think(t_philo *philo)
{
	philo_print(philo, "is thinking");
}

void	*philo_main(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (await_active(philo) == -1)
		return (NULL);
	while (atomic_load(&philo->sim->active))
	{
		if (atomic_load(&philo->sim->active))
			philo_eat(philo);
		if (atomic_load(&philo->sim->active))
			philo_sleep(philo);
		if (atomic_load(&philo->sim->active))
			philo_think(philo);
	}
	return (NULL);
}
