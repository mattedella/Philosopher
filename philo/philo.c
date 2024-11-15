/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:43:20 by mdella-r          #+#    #+#             */
/*   Updated: 2024/07/11 10:53:25 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_rules *rules)
{
	int	i;

	i = rules->nb_philo;
	while (--i >= 0)
	{
		rules->philosophers[i].id = i + 1;
		rules->philosophers[i].x_ate = 0;
		rules->philosophers[i].left_fork_id = i;
		rules->philosophers[i].right_fork_id = (i + 1) % rules->nb_philo;
		rules->philosophers[i].rules = rules;
		rules->philosophers[i].t_last_meal = 0;
	}
}

int	init_mutex(t_rules *rules)
{
	int	i;

	i = rules->nb_philo;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&rules->forks[i], NULL))
			return (1);
	}
	if (pthread_mutex_init(&rules->meal_check, NULL))
		return (1);
	if (pthread_mutex_init(&rules->writing, NULL))
		return (1);
	if (pthread_mutex_init(&rules->ate_check, NULL))
		return (1);
	return (0);
}

int	init_all(int argc, char **argv, t_rules *r)
{
	r->nb_philo = ft_atoll(argv[1]);
	r->time_death = ft_atoll(argv[2]);
	r->time_eat = ft_atoll(argv[3]);
	r->time_sleep = ft_atoll(argv[4]);
	r->is_dead = 0;
	r->all_ate = 0;
	if (r->time_eat <= 0 || r->time_sleep <= 0 || r->time_death <= 0
		|| r->nb_philo < 1 || r->nb_philo > 200)
		return (1);
	if (argc == 6)
	{
		r->nb_eat = ft_atoll(argv[5]);
		if (r->nb_eat <= 0)
			return (1);
	}
	else
		r->nb_eat = -1;
	if (init_mutex(r) == 1)
		return (1);
	r->start_time = get_time();
	init_philo(r);
	return (0);
}

int	main(int argc, char **argv)
{
	t_rules	rules;

	if (argc < 5 || argc > 6)
	{
		printf("Invalid number of arguments\n");
		return (1);
	}
	if (init_all(argc, argv, &rules) == 1)
	{
		printf("Init failed\n");
		return (1);
	}
	if (init_routine(&rules) == 1)
	{
		printf("Init routine failed\n");
		return (1);
	}
	return (0);
}
