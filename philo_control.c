/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burakkarlidag <burakkarlidag@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:35:25 by bkarlida          #+#    #+#             */
/*   Updated: 2023/07/23 17:30:36 by burakkarlid      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	arg_control(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[0] == '-')
			i++;		
		if (!(str[i] >= '0' && str[i] <= '9'))
		{
			printf("wrong_arguments\n");
			return(1);
		}
		i++;
	}
	return(0);
}

int   arg_error(char **av, int ac)
{
	int i;

	i = 1;
	if (ac > 6 || ac < 5)
	{
		printf("Error_arg_count\n");
		return(1);
	}
	while (i < ac)
	{
		if (av[1][0] == '0')
		{
			printf("number of philo not entered\n");
			return (1);
		}
		if (arg_control(av[i]))
			return(1);
		
		i++;
	}
	return(0);
}