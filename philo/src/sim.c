/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 20:06:32 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/22 20:20:45 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdint.h>
#include <stdlib.h>
#include <bits/pthreadtypes.h>
#include <pthread.h>

int	spawn_thread(t_sim *sim, int i)
{
	t_philo	*philo;

	philo = &sim->philos[i];
	if (pthread_create(&philo->thread, 0, philo_main, philo) == -1)
	{
		printf("Philosopher initialization failed\n");
		return (-1);
	}
}

void	sim_cleanup(t_sim *sim)
{
	int	i;

	i = -1;
	while (++i < sim->philo_count)
	{
		if (sim->philos[i].thread)
			pthread_join(sim->philos[i].thread, NULL);
	}
	i = -1;
	while (++i < sim->philo_count)
	{
		pthread_mutex_destroy(&sim->forks[i].lock);
	}
}

int	sim_init(t_sim *sim)
{
	int32_t	i;

	sim->philos = malloc(sim->philo_count * sizeof(t_philo));
	sim->forks = malloc(sim->philo_count * sizeof(t_fork));
	i = -1;
	memset(sim->philos, 0, sim->philo_count * sizeof(t_philo));
	memset(sim->forks, 0, sim->philo_count * sizeof(t_fork));
	while (++i < sim->philo_count)
	{
		pthread_mutex_init(&sim->forks[i].lock, 0);
		if (i == 0)
			sim->philos[i].left = &sim->forks[sim->philo_count - 1];
		else
			sim->philos[i].left = &sim->forks[i - 1];
		if (i == sim->philo_count - 1)
			sim->philos[i].right = &sim->forks[0];
		else
			sim->philos[i].right = &sim->forks[i + 1];
		if (spawn_thread(sim, i) == -1)
		{
			sim_cleanup(sim);
			return (-1);
		}
	}
	return (0);
}
