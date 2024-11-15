/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 12:16:08 by mdella-r          #+#    #+#             */
/*   Updated: 2024/07/16 14:56:40 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_philosopher *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&rules->forks[philo->left_fork_id]);
	ft_write(rules, philo->id, "has taken a fork", 0);
	if (rules->nb_philo == 1)
	{
		usleep(rules->time_death * 1000);
		pthread_mutex_unlock(&rules->forks[philo->left_fork_id]);
	}
	pthread_mutex_lock(&rules->forks[philo->right_fork_id]);
	ft_write(rules, philo->id, "has taken a fork", 0);
	ft_write(rules, philo->id, "is eating", rules->time_eat);
	pthread_mutex_lock(&rules->meal_check);
	philo->t_last_meal = get_time();
	pthread_mutex_unlock(&rules->meal_check);
	pthread_mutex_lock(&rules->ate_check);
	philo->x_ate++;
	pthread_mutex_unlock(&rules->ate_check);
	pthread_mutex_unlock(&rules->forks[philo->left_fork_id]);
	pthread_mutex_unlock(&rules->forks[philo->right_fork_id]);
}

void	ft_sleep(t_philosopher *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	ft_write(rules, philo->id, "is sleeping", rules->time_sleep);
}

void	ft_think(t_philosopher *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	ft_write(rules, philo->id, "is thinking", 0);
}

void	*routine(void *void_philo)
{
	t_philosopher	*philo;
	t_rules			*rules;

	philo = (t_philosopher *)void_philo;
	rules = philo->rules;
	if (philo->id % 2)
		usleep(15000);
	while (philo->x_ate != rules->nb_eat)
	{
		pthread_mutex_lock(&rules->writing);
		if (rules->is_dead == 1)
		{
			pthread_mutex_unlock(&rules->writing);
			break ;
		}
		pthread_mutex_unlock(&rules->writing);
		ft_eat(philo);
		if (philo->x_ate == rules->nb_eat)
			return (NULL);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}

int	init_routine(t_rules *rules)
{
	int				i;

	i = rules->nb_philo;
	while (--i >= 0)
	{
		if (pthread_create(&rules->philosophers[i].thread_id, NULL, routine,
				&rules->philosophers[i]))
			return (1);
		pthread_mutex_lock(&rules->meal_check);
		rules->philosophers[i].t_last_meal = get_time();
		pthread_mutex_unlock(&rules->meal_check);
	}
	ft_death(rules->philosophers, rules);
	i = -1;
	while (++i < rules->nb_philo)
		pthread_join(rules->philosophers[i].thread_id, NULL);
	i = -1;
	while (++i < rules->nb_philo)
		pthread_mutex_destroy(&rules->forks[i]);
	pthread_mutex_destroy(&rules->meal_check);
	pthread_mutex_destroy(&rules->writing);
	pthread_mutex_destroy(&rules->ate_check);
	return (0);
}
