/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burakkarlidag <burakkarlidag@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 02:23:11 by burakkarlid       #+#    #+#             */
/*   Updated: 2023/08/06 01:57:00 by burakkarlid      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*philo_division(t_rules *rules)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo) * rules->nb);
	rules->forks = malloc(sizeof(pthread_mutex_t)
			* rules->nb);
	while (i < rules->nb)
	{
		philo[i].id = i;
		philo[i].eat_count = 0;
		philo[i].rules = rules;
		philo[i].right_fork = &rules->forks[i];
		philo[i].left_fork = &rules->forks[(i + 1) % (rules->nb)];
		pthread_mutex_init(&rules->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&rules->death_mutex, NULL);
	philo->rules->death = 1;
	return (philo);
}

int	death_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->death_mutex);
	if (philo->rules->death == 1)
	{
		pthread_mutex_unlock(&philo->rules->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->rules->death_mutex);
	return (0);
}

void	*routine(void *philo)
{
	t_philo	*temp;

	temp = philo;
	if (temp->id % 2 == 1)
		usleep(1000);
	while (1)
	{
		if (death_check(temp) == 0)
			break ;
		eating(temp);
		mutex_sleep(temp);
		print_philo(temp, "is thinking\n");
	}
	return (NULL);
}

void	thread_create(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->rules->nb)
	{
		philo[i].lt = get_time();
		pthread_create(&philo[i].thread_id, NULL, routine, &philo[i]);
		usleep(150);
		i++;
	}
	while (1)
	{
		if (eat_control(philo) == 1)
			break ;
		if (death_control(philo) == 1)
			break ;
		usleep(200);
	}
}

int		arg_division(t_rules *rules, int ac, char **av)
{
	int		k;

	k = 1;
	if (arg_control(av) == 1 || ac < 5 || ac > 6)
	{
		write(2, "Wrong Argument\n", 15);
		return (0);
	}
	while (av[k])
	{
		if (ft_atoi(av[k]) == -1)
			return (0);
		k++;
	}
	rules = get_arg(ac, av, rules);
	return (1);
}

int	main(int ac, char **av)
{
	t_rules	*rules;
	t_philo	*philo;

	rules = malloc(sizeof(t_rules));
	if (arg_division(rules, ac, av) == 0)
		return (0);
	rules->ft = get_time();
	philo = philo_division(rules);
	mutex_init(philo, rules);
	thread_create(philo);
	thread_join(philo);
	mutex_destroy(philo);
}
