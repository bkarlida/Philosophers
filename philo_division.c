/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_division.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkarlida <bkarlida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 02:45:53 by burakkarlid       #+#    #+#             */
/*   Updated: 2023/07/27 23:34:21 by bkarlida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		philo_divison(t_rules *phl)
{
	int i;

	i = -1;
	while (++i < phl->nb)
	{
		phl->philos[i].id = i;
		phl->philos[i].rules = phl;
		phl->philos[i].right = &phl->forks[i];
		phl->philos[i].left = &phl->forks[(i + 1) % (phl->nb)];
	}
	return (0);	
}

int		forks_division(t_rules *rules)
{
	int i;

	i = 0;
	while (i < rules->nb)
	{
		pthread_mutex_init(&(rules->forks[i]), NULL);
		pthread_mutex_init(&rules->meal_mutex[i], NULL);
		pthread_mutex_init(&rules->eat_count_mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(&rules->print_mutex, NULL);
	pthread_mutex_init(&rules->death_mutex, NULL);
	return (0);
}

int		min_max_control(t_rules *phl)
{
	if (phl->nb == 2 || phl->nb == -1)
	{
		printf("min_max_error\n");
		return(1);
	}
	if (phl->nd == 2 || phl->nd == -1)
	{
		printf("min_max_error\n");
		return(1);
	}
	if (phl->ne == 2 || phl->ne == -1)
	{
		printf("min_max_error\n");
		return(1);
	}
	if (phl->ns == 2 || phl->ns == -1)
	{
		printf("min_max_error\n");
		return(1);
	}
	return(0);
}

int   arg_division(t_rules *rules, char **av)
{
	rules->nb = ft_atoi(av[1]);
	rules->nd = ft_atoi(av[2]);
	rules->ne = ft_atoi(av[3]);
	rules->ns = ft_atoi(av[4]);
	//if (min_max_control(rules))// eksik var yap 
	//	return (1);	
	if (av[5])
	{
		rules->must_eat = ft_atoi(av[5]);
		if (rules->must_eat <= 0)
			return (1);
	}
	else
		rules->must_eat = -1;
	
	if (rules->nb > 250)
		return(1);
	rules->dead = 0;
	rules->togg = -1;
    rules->eat_count_mutex = malloc(sizeof(pthread_mutex_t));
    rules->meal_mutex = malloc(sizeof(pthread_mutex_t));
	if (forks_division(rules))
		return(1);
	return(0);
}

