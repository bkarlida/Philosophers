/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkarlida <bkarlida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 00:55:35 by bkarlida          #+#    #+#             */
/*   Updated: 2023/07/27 23:36:56 by bkarlida         ###   ########.fr       */
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

long long	get_time(void)
{
	struct timeval	tv;
	long long		time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}



void	sleep_func(long long time, t_rules *rules)
{
	long long	i;
	//(void)rules;
	i = get_time();
	while (!(rules->dead))
	{
		if (get_time() - i >= time)
			break ;
		usleep(300);
	}
}

// void	eat_control(t_rules *rules)
// {
// 	int	i;
// 	int	flag;

// 	i = 0;
// 	flag = 0;
// 	while (i < rules->nb)
// 	{
// 		if (rules->philos[i].eat_count == rules->must_eat)
// 			flag++;
// 		if (flag == rules->nb)
// 		{
// 			rules->togg = 1;
// 		}
// 		i++;
// 	}
// }

void	print_philo(t_philo *phl, t_rules *rules, char *str)
{
	pthread_mutex_lock(&(rules->death_mutex));
	if (!(rules->dead))
	{
		pthread_mutex_unlock(&rules->death_mutex);
		pthread_mutex_lock(&(rules->print_mutex));
		printf("[%lli] ", get_time() - rules->ft);
		printf("%i ", phl->id + 1);
		printf("%s", str);
		pthread_mutex_unlock(&rules->print_mutex);
	}
	pthread_mutex_unlock(&rules->death_mutex);
}
