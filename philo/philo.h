/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:33:23 by mdella-r          #+#    #+#             */
/*   Updated: 2024/06/26 11:17:19 by mdella-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

struct	s_rules;

typedef struct s_philosopher
{
	int					id;
	int					x_ate;
	int					left_fork_id;
	int					right_fork_id;
	long long			t_last_meal;
	struct s_rules		*rules;
	pthread_t			thread_id;
}						t_philosopher;

typedef struct s_rules
{
	int					nb_eat;
	int					is_dead;
	int					all_ate;
	int					nb_philo;
	long long			time_eat;
	long long			time_death;
	long long			time_sleep;
	long long			start_time;
	pthread_mutex_t		writing;
	pthread_mutex_t		ate_check;
	pthread_mutex_t		meal_check;
	pthread_mutex_t		forks[200];
	t_philosopher		philosophers[200];
}						t_rules;

int			init_mutex(t_rules *rules);
int			init_routine(t_rules *rules);
int			init_all(int argc, char **argv, t_rules *rules);
void		ft_death(t_philosopher *philo, t_rules *rules);
void		*routine(void *void_philo);
void		init_philo(t_rules *rules);
void		ft_eat(t_philosopher *philo);
void		destroy_mutex(t_rules *rules);
void		check_death(t_rules *r, int i);
void		ft_think(t_philosopher *philo);
void		ft_sleep(t_philosopher *philo);
void		ft_write(t_rules *rules, int id, char *str, long long time);
void		ft_write_death(t_rules *rules, int id, char *str);
long long	get_time(void);
long long	ft_atoll(char *str);
#endif