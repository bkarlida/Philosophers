/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_division.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burakkarlidag <burakkarlidag@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 02:45:53 by burakkarlid       #+#    #+#             */
/*   Updated: 2023/08/06 01:46:35 by burakkarlid      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	arg_control(char **av)
{
	int	i;
	int	k;

	k = 1;
	while (av[k])
	{
		i = 0;
		while (av[k][i])
		{
			if (av[k][i] >= '0' && av[k][i] <= '9')
				i++;
			else
				return (1);
		}
		k++;
	}
	return (0);
}

t_rules	*get_arg(int ac, char **av, t_rules *rules)
{
	rules->nb = ft_atoi(av[1]);
	rules->td = ft_atoi(av[2]);
	rules->te = ft_atoi(av[3]);
	rules->ts = ft_atoi(av[4]);
	if (ac == 6)
		rules->must_eat_count = ft_atoi(av[5]);
	else
		rules->must_eat_count = -1;
	return (rules);
}

unsigned long	get_time(void)
{
	unsigned long	time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	mutex_init(t_philo *philo, t_rules *rules)
{
	int	i;

	i = 0;
	rules->all_sleep_mutex = malloc(sizeof(pthread_mutex_t)
			* rules->nb);
	rules->all_eat_mutex = malloc(sizeof(pthread_mutex_t)
			* rules->nb);
	rules->all_print_mutex = malloc(sizeof(pthread_mutex_t)
			* rules->nb);
	while (i < rules->nb)
	{
		philo[i].sleep_mutex = &rules->all_sleep_mutex[i];
		philo[i].eat_mutex = &rules->all_eat_mutex[i];
		philo[i].print_mutex = &rules->all_print_mutex[i];
		pthread_mutex_init(&rules->all_sleep_mutex[i], NULL);
		pthread_mutex_init(&rules->all_eat_mutex[i], NULL);
		pthread_mutex_init(&rules->all_print_mutex[i], NULL);
		i++;
	}
}


