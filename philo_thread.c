/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkarlida <bkarlida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 02:23:11 by burakkarlid       #+#    #+#             */
/*   Updated: 2023/07/27 23:48:06 by bkarlida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		eating(t_philo *phl, t_rules *rules)
{
	pthread_mutex_lock(phl->right);
	print_philo(phl, rules, "has taken a fork\n");
	if (rules->nb == 1)
	{
		pthread_mutex_unlock(phl->right);
		return (1);
	}
	pthread_mutex_lock(phl->left);
	print_philo(phl, rules, "has taken a fork\n");
	print_philo(phl, rules, "is eating\n");
	pthread_mutex_lock(rules->meal_mutex);
	phl->lt = get_time();
	pthread_mutex_unlock(rules->meal_mutex);
	pthread_mutex_lock(rules->eat_count_mutex);
	phl->eat_count++;
	pthread_mutex_unlock(rules->eat_count_mutex);
	sleep_func(rules->ne, rules);
	pthread_mutex_unlock(phl->right);
	pthread_mutex_unlock(phl->left);
	return (0);
}

void	*routine(void *a)
{
	t_philo	*phl;
	t_rules	*rules;
	
	phl = (t_philo *)a;
	rules = phl->rules;
	if (phl->id % 2 == 1)
		usleep(100);
	while (!(rules->dead))
	{
		if (eating(phl, rules))
			break;
		pthread_mutex_lock(&rules->death_mutex);
		if (rules->dead)
		{
			pthread_mutex_unlock(&rules->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&rules->death_mutex);
		if (rules->must_eat != -1 && phl->eat_count >= rules->must_eat)
		{
			rules->togg = 4;
			pthread_mutex_unlock(&rules->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&rules->death_mutex);
		print_philo(phl, rules, "is sleeping\n");
		sleep_func(rules->ns, rules);
		print_philo(phl, rules, "is thinking\n");
	}
	return (NULL);
}

int		dead_control(t_rules *rules, t_philo *phl)
{
	int	i;

	i = -1;
	while (++i < rules->nb)
	{
		pthread_mutex_lock(&rules->meal_mutex[i]);
		if (((get_time() - rules->philos[i].lt) > rules->nd))
		{
			pthread_mutex_unlock(&rules->meal_mutex[i]);
			print_philo(phl, rules, " is died\n");
			pthread_mutex_lock(&rules->death_mutex);
			rules->dead = 1;
			pthread_mutex_unlock(&rules->death_mutex);
			return (1);
		}
		pthread_mutex_unlock(&rules->meal_mutex[i]);
		usleep(100);
	}
	return (0);
}

int		thread_create(t_rules *rules, t_philo *phl)
{
	int i;

	i = 0;
	rules->ft = get_time();
	while (i < rules->nb)
	{
		if (pthread_create(&rules->philos[i].thread_id, NULL, &routine, &rules->philos[i]))
			return (1);
		pthread_mutex_lock(&rules->meal_mutex[i]);
		rules->philos[i].lt = get_time();
		pthread_mutex_unlock(&rules->meal_mutex[i]);
		usleep(100);
		i++;
	}
	while (1)
	{
		if (dead_control(rules, phl) == 1 || rules->togg == 4)
			break ;
	}
	i = 0;
	while (i < rules->nb)
	{
		if (pthread_join(rules->philos[i].thread_id, NULL))
			return (1);
		i++;
	}
	return (0);
}
