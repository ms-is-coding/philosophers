/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:41:00 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/23 05:02:09 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdint.h>
# include <pthread.h>
# include <stdbool.h>

typedef struct s_fork
{
	pthread_mutex_t	lock;
	bool			initialized;
	char			padding[7];
}	t_fork;

typedef struct s_philo
{
	int64_t			last_meal;
	struct s_sim	*sim;
	t_fork			*left;
	t_fork			*right;
	pthread_t		thread;
	int32_t			meal_count;
	int32_t			id;
	bool			started;
	bool			pick_left_first;
	char			padding[6];
}	t_philo;

typedef struct s_sim
{
	t_philo			*philos;
	t_fork			*forks;
	int64_t			start_time;
	pthread_mutex_t	main_lock;
	int32_t			philo_count;
	int32_t			death_time;
	int32_t			eat_time;
	int32_t			sleep_time;
	int32_t			meal_count;
	int32_t			saturated;
	bool			active;
	bool			should_end;
	char			padding[6];
}	t_sim;

void	*philo_main(void *arg);
int		sim_init(t_sim *sim);
void	sim_cleanup(t_sim *sim);
int64_t	timestamp(t_sim *sim);
int64_t	time_now(void);
void	time_sleep(t_sim *sim, int32_t millis);
int		await_active(t_philo *philo);

#endif // PHILO_H
