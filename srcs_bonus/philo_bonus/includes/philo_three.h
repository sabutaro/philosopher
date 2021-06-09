/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 12:07:48 by sperrin           #+#    #+#             */
/*   Updated: 2021/06/07 16:26:55 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <signal.h>
# include <pthread.h>
# include <semaphore.h>

typedef struct s_table
{
	int				number_of_philosopher;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				must_eat;
	unsigned long	base_time;
	int				dead;
	sem_t			*s_forks;
	sem_t			*s_output;
	sem_t			*s_eat;
	sem_t			*s_dead;
	sem_t			*s_last_eat;
}					t_table;

typedef struct s_philo
{
	t_table			*table;
	int				num;
	int				cnt_eat;
	unsigned long	last_eat;
	pid_t			pid;
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
void				process_monitor(t_philo *philos, int count);
#endif
