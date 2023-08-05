/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burakkarlidag <burakkarlidag@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 00:55:35 by bkarlida          #+#    #+#             */
/*   Updated: 2023/08/06 01:57:08 by burakkarlid      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	ft_atoi(const char *str)
{
	size_t			i;
	long int		result;
	int				sign;

	i = 0;
	result = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			sign *= -1;
		i++;
	}
	while (str[i] && str[i] >= 48 && str[i] <= 57)
	{
		result = result * 10 + (str[i] - 48);
		if (result * sign < -2147483648)
			return (2);
		else if (result * sign > 2147483647)
			return (-1);
		i++;
	}
	return (result * sign);
}

void	sleep_func(int until)
{
	unsigned long	localtime;

	localtime = get_time();
	while ((get_time() - localtime) < (unsigned long)until)
		usleep(200);
}

void	mutex_destroy(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->rules->nb)
	{
		pthread_mutex_destroy(&philo->rules->forks[i]);
		pthread_mutex_destroy(&philo->rules->all_sleep_mutex[i]);
		pthread_mutex_destroy(&philo->rules->all_eat_mutex[i]);
		pthread_mutex_destroy(&philo->print_mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&philo->rules->death_mutex);
	free(philo->rules->all_eat_mutex);
	free(philo->rules->all_sleep_mutex);
	free(philo->rules->forks);
	free(philo);
}

void	thread_join(t_philo *philo)
{
	int	k;

	k = 0;
	while (k < philo->rules->nb)
	{
		pthread_join(philo[k].thread_id, NULL);
		k++;
	}
}


void	mutex_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->sleep_mutex);
	print_philo(philo, "is sleeping\n");
	pthread_mutex_unlock(philo->sleep_mutex);
	sleep_func(philo->rules->ts);
}