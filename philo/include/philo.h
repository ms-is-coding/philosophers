/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:41:00 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/22 20:15:52 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <bits/pthreadtypes.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

typedef struct s_fork
{
	pthread_mutex_t	lock;
	int				taken;
}	t_fork;

typedef struct s_philo
{
	pthread_t	thread;
	t_fork		*left;
	t_fork		*right;
}	t_philo;

typedef struct s_sim
{
	int32_t	philo_count;
	int32_t	death_time;
	int32_t	eat_time;
	int32_t	sleep_time;
	int32_t	meal_count;
	char	reserved[4];
	t_philo	*philos;
	t_fork	*forks;
}	t_sim;

void	*philo_main(void *arg);
int		sim_init(t_sim *sim);

#endif // PHILO_H
