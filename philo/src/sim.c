/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 20:06:32 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/24 12:07:12 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>

void	sim_cleanup(t_sim *sim)
{
	int	i;

	i = -1;
	atomic_store(&sim->should_end, true);
	atomic_store(&sim->active, false);
	while (++i < sim->philo_count)
	{
		if (sim->philos[i].started)
			pthread_join(sim->philos[i].thread, NULL);
	}
	i = -1;
	while (++i < sim->philo_count)
	{
		if (sim->forks[i].initialized)
			pthread_mutex_destroy(&sim->forks[i].lock);
	}
	pthread_mutex_destroy(&sim->io_lock);
	free(sim->philos);
	free(sim->forks);
}

static void	assign_forks(t_sim *sim, int i)
{
	t_philo	*philo;
	int		left;
	int		right;

	philo = &sim->philos[i];
	left = i % sim->philo_count;
	right = (i + 1) % sim->philo_count;
	philo->left = &sim->forks[left];
	philo->right = &sim->forks[right];
	philo->pick_left_first = i % 2;
	if (i == sim->philo_count - 1)
		philo->pick_left_first = true;
}

static int	philo_init(t_sim *sim, int i)
{
	t_philo	*philo;

	philo = &sim->philos[i];
	philo->sim = sim;
	philo->id = i + 1;
	if (pthread_mutex_init(&sim->forks[i].lock, 0) != 0)
	{
		printf("Mutex init failed\n");
		return (-1);
	}
	sim->forks[i].initialized = 1;
	assign_forks(sim, i);
	if (pthread_create(&philo->thread, 0, philo_main, philo) != 0)
	{
		printf("Thread init failed\n");
		return (-1);
	}
	philo->started = true;
	return (0);
}

int	sim_init(t_sim *sim)
{
	int32_t	i;

	sim->philos = malloc((size_t)sim->philo_count * sizeof(t_philo));
	sim->forks = malloc((size_t)sim->philo_count * sizeof(t_fork));
	if (!sim->philos || !sim->forks || pthread_mutex_init(&sim->io_lock, 0))
	{
		printf("Initialization failed\n");
		free(sim->philos);
		free(sim->forks);
		return (-1);
	}
	i = -1;
	memset(sim->philos, 0, (size_t)sim->philo_count * sizeof(t_philo));
	memset(sim->forks, 0, (size_t)sim->philo_count * sizeof(t_fork));
	sim->start_time = time_now();
	while (++i < sim->philo_count)
		if (philo_init(sim, i) != 0)
			return (sim_cleanup(sim), -1);
	atomic_store(&sim->active, true);
	return (0);
}
