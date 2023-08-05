/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burakkarlidag <burakkarlidag@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:22:12 by bkarlida          #+#    #+#             */
/*   Updated: 2023/08/06 01:57:47 by burakkarlid      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_rules
{
	int					nb;
	int					td;
	int					te;
	int					ts;
	int					must_eat_count;
	long long			ft;
	pthread_mutex_t		*forks;
	pthread_mutex_t		death_mutex;
	pthread_mutex_t		*all_eat_mutex;
	pthread_mutex_t		*all_print_mutex;
	pthread_mutex_t		*all_sleep_mutex;
	int					death;
}	t_rules;

typedef struct s_philo
{
	long long			lt;
	int					id;
	int					eat_count;
	pthread_mutex_t		*eat_mutex;
	pthread_mutex_t		*sleep_mutex;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*print_mutex;
	pthread_t			thread_id;
	t_rules				*rules;

}	t_philo;

int				ft_atoi(const char *str);
int				arg_control(char **av);
int				death_check(t_philo *philo);
unsigned long	get_time(void);
t_rules			*get_arg(int ac, char **av, t_rules *rules);
t_philo			*philo_division(t_rules *rules);
void			get_forks(t_rules *rules, t_philo *philo);
void			*routine(void *philo);
void			thread_create(t_philo *philo);
void			print_philo(t_philo *philo, char *str);
void			eating(t_philo *philo);
void			sleep_func(int until);
void			mutex_sleep(t_philo *philo);
int				eat_control(t_philo *philo);
int				death_control(t_philo *philo);
void			mutex_destroy(t_philo *philo);
void			mutex_init(t_philo *philo, t_rules *rules);
void			thread_join(t_philo *philo);
#endif