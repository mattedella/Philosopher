/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:55:58 by mdella-r          #+#    #+#             */
/*   Updated: 2024/06/26 10:47:24 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_write(t_rules *rules, int id, char *str, long long time)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&rules->writing);
	if (!(rules->is_dead))
	{
		printf("%lld %d %s\n", get_time() - rules->start_time, id, str);
		i = 1;
	}
	pthread_mutex_unlock(&rules->writing);
	if (i == 1)
	{
		usleep(time * 1000);
		i = 0;
	}
}

void	check_death(t_rules *r, int i)
{
	pthread_mutex_lock(&r->writing);
	r->is_dead = 1;
	pthread_mutex_unlock(&r->writing);
	ft_write_death(r, i + 1, "died");
}

void	ft_write_death(t_rules *rules, int id, char *str)
{
	pthread_mutex_lock(&rules->writing);
	printf("%lld %d %s\n", get_time() - rules->start_time, id, str);
	pthread_mutex_unlock(&rules->writing);
}

void	ft_death(t_philosopher *p, t_rules *r)
{
	int	i;

	while (!(r->all_ate))
	{
		i = -1;
		while (++i < r->nb_philo && !(r->is_dead))
		{
			pthread_mutex_lock(&(r->meal_check));
			if (get_time() - p[i].t_last_meal >= r->time_death)
				check_death(r, i);
			pthread_mutex_unlock(&(r->meal_check));
			usleep(100);
		}
		if (r->is_dead)
			break ;
		i = 0;
		pthread_mutex_lock(&(r->ate_check));
		while (r->nb_eat != -1 && i < r->nb_philo && p[i].x_ate >= r->nb_eat)
			i++;
		pthread_mutex_unlock(&(r->ate_check));
		if (i == r->nb_philo)
			r->all_ate = 1;
	}
}
