/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burakkarlidag <burakkarlidag@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:35:25 by bkarlida          #+#    #+#             */
/*   Updated: 2023/08/06 01:31:55 by burakkarlid      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philo(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->print_mutex);
	if (death_check(philo) == 1
		&& (philo->eat_count != philo->rules->must_eat_count))
		printf("[%llu] %d %s", get_time()
			- philo->rules->ft, philo->id + 1, str);
	pthread_mutex_unlock(philo->print_mutex);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_philo(philo, "has taken a fork\n");
	if (philo->rules->nb == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		philo->rules->death = 42;
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	print_philo(philo, "has taken a fork\n");
	pthread_mutex_lock(philo->eat_mutex);
	philo->lt = get_time();
	print_philo(philo, "is eating\n");
	philo->eat_count++;
	pthread_mutex_unlock(philo->eat_mutex);
	sleep_func(philo->rules->te);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

int	eat_control(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->rules->must_eat_count == -1)
		return (0);
	while (i < philo->rules->nb)
	{
		pthread_mutex_lock(philo[i].eat_mutex);
		if (philo[i].eat_count < philo->rules->must_eat_count)
		{
			pthread_mutex_unlock(philo[i].eat_mutex);
			return (0);
		}
		pthread_mutex_unlock(philo[i].eat_mutex);
		i++;
	}
	pthread_mutex_lock(&philo->rules->death_mutex);
	philo->rules->death = 42;
	pthread_mutex_unlock(&philo->rules->death_mutex);
	return (1);
}

int	death_control(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->rules->nb)
	{
		pthread_mutex_lock(philo[i].eat_mutex);
		if ((int)(get_time() - philo[i].lt)
			>= philo->rules->td)
		{
			pthread_mutex_lock(&philo->rules->death_mutex);
			philo->rules->death = 42;
			pthread_mutex_unlock(&philo->rules->death_mutex);
			pthread_mutex_unlock(philo[i].eat_mutex);
			printf("[%llu] %d %s", get_time()
				- philo->rules->ft, philo[i].id + 1, "dead\n");
			return (1);
		}
		pthread_mutex_unlock(philo[i].eat_mutex);
		i++;
	}
	return (0);
}