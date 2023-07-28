/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkarlida <bkarlida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:47:57 by bkarlida          #+#    #+#             */
/*   Updated: 2023/07/27 18:25:24 by bkarlida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main (int ac, char **av)
{
	t_rules	*rules;
	t_philo	*phl;

	rules = malloc(sizeof(t_rules));
	phl = malloc(sizeof(t_philo));
	if (arg_error(av, ac))
		return (0);
	if (arg_division(rules, av))
		return(0);
	if (philo_divison(rules))
		return(0);
	if (thread_create(rules, phl))
		return(0);
	//free(rules);
	//free(phl);
}