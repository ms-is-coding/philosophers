/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 20:14:22 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/23 05:03:30 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

static void	philo_eat_meal(t_philo *philo, t_fork *first, t_fork *second)
{
	pthread_mutex_lock(&first->lock);
	pthread_mutex_lock(&second->lock);
	pthread_mutex_lock(&philo->sim->main_lock);
	if (philo->sim->active)
	{
		printf("%li %i has taken a fork\n", timestamp(philo->sim), philo->id);
		printf("%li %i has taken a fork\n", timestamp(philo->sim), philo->id);
		printf("%li %i is eating\n", timestamp(philo->sim), philo->id);
	}
	pthread_mutex_unlock(&philo->sim->main_lock);
	philo->last_meal = time_now();
	time_sleep(philo->sim, philo->sim->eat_time);
	philo->meal_count++;
	if (philo->sim->meal_count > 0
		&& philo->meal_count == philo->sim->meal_count)
	{
		pthread_mutex_lock(&philo->sim->main_lock);
		if (++philo->sim->saturated == philo->sim->philo_count)
			philo->sim->active = false;
		pthread_mutex_unlock(&philo->sim->main_lock);
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
		if (philo->sim->active)
			printf("%li %i has taken a fork\n", timestamp(philo->sim),
				philo->id);
		time_sleep(philo->sim, philo->sim->death_time * 2);
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
	pthread_mutex_lock(&philo->sim->main_lock);
	if (philo->sim->active)
		printf("%li %i is sleeping\n", timestamp(philo->sim), philo->id);
	pthread_mutex_unlock(&philo->sim->main_lock);
	time_sleep(philo->sim, philo->sim->sleep_time);
}

static void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->main_lock);
	if (philo->sim->active)
		printf("%li %i is thinking\n", timestamp(philo->sim), philo->id);
	pthread_mutex_unlock(&philo->sim->main_lock);
}

void	*philo_main(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (await_active(philo) == -1)
		return (NULL);
	while (philo->sim->active)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
