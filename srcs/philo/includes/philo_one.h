/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 09:20:49 by sperrin           #+#    #+#             */
/*   Updated: 2021/06/04 09:20:51 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_table
{
	int				number_of_philosopher;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				must_eat;
	unsigned long	base_time;
	int				dead;
	pthread_mutex_t	*m_forks;
	pthread_mutex_t	m_output;
	pthread_mutex_t	m_eat;
	pthread_mutex_t	m_dead;
}					t_table;

typedef struct s_philo
{
	t_table			*table;
	int				fork1;
	int				fork2;
	int				num;
	int				cnt_eat;
	unsigned long	last_eat;
	pthread_t		tid;
}					t_philo;

int					put_msg(t_philo *philo, char *str,
						unsigned long current_time);
void				*start_dinner(void *void_philo);
void				*philo_dead(void *void_philo);
int					ft_atoi(const char *str);
unsigned long		get_time(void);
void				m_sleep(unsigned long itime);
int					error(char *argv);
int					check_is_number(char **argv);
int					ft_strcmp(char *s1, char *s2);
#endif
