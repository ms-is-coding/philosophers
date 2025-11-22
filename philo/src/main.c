/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:41:27 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/22 20:06:14 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int32_t	philo_atoi(const char *nptr, int32_t min, int32_t max,
					const char *name)
{
	int64_t	n;

	n = 0;
	if (!nptr)
		return (-1);
	while (*nptr)
	{
		if (*nptr < '0' || *nptr > '9')
		{
			printf("Invalid value for %s\n", name);
			return (-1);
		}
		if (n > max)
		{
			printf("Value for %s too big. Max %i\n", name, max);
			return (-1);
		}
		n = n * 10 + *nptr++ - '0';
	}
	if (n < min || n > max)
	{
		printf("Value for %s too small. Min %i\n", name, min);
		return (-1);
	}
	return ((int32_t)n);
}

#define USAGE "<philo_count> <death_time> <eat_time> <sleep_time> [meal_count]"

int	main(int argc, char **argv)
{
	t_sim	sim;

	memset(&sim, 0, sizeof(sim));
	if (argc < 5 || argc > 6)
	{
		printf("%s: " USAGE "\n", argv[0]);
		return (1);
	}
	sim.philo_count = philo_atoi(argv[1], 1, 200, "philo_count");
	sim.death_time = philo_atoi(argv[2], 1, 100000, "death_time");
	sim.eat_time = philo_atoi(argv[3], 1, 100000, "eat_time");
	sim.sleep_time = philo_atoi(argv[4], 1, 100000, "sleep_time");
	sim.meal_count = philo_atoi(argv[5], 1, 1000, "meal_count");
	if (sim.philo_count == -1 || sim.death_time == -1
		|| sim.eat_time == -1 || sim.sleep_time == -1)
		return (1);
	launch_sim(sim);
}
