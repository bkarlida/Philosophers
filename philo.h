/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkarlida <bkarlida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:22:12 by bkarlida          #+#    #+#             */
/*   Updated: 2023/07/27 21:31:53 by bkarlida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id; 
	int				eat_count;
	long long 		lt;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_t		thread_id;
	struct philo_lst	*rules;
}					t_philo;

typedef struct philo_lst
{
    int nb;
    int nd;
    int ne;
    int ns;
    int must_eat;
    int togg;
    int dead;
	long long ft;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	*meal_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*eat_count_mutex;
    pthread_mutex_t	forks[202];
	t_philo			philos[202];
} t_rules;

int			arg_division(t_rules *phl, char **av);
int     	arg_error(char **av, int ac);
int			ft_atoi(const char *str);
int			philo_divison(t_rules *phl);
int			thread_create(t_rules *rules, t_philo *phl);
long long	get_time(void);
void	sleep_func(long long time, t_rules *rules);
void	print_philo(t_philo *phl, t_rules *rules, char *str);
//void	eat_control(t_rules *rules);
#endif