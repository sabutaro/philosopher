/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 12:07:48 by sperrin           #+#    #+#             */
/*   Updated: 2021/06/14 15:48:39 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

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
	sem_t			*s_eat;
	sem_t			*s_dead;
	sem_t			*s_permits;
}					t_table;

typedef struct s_philo
{
	t_table			*table;
	int				num;
	int				cnt_eat;
	unsigned long	last_eat;
}					t_philo;

void				*start_dinner(void *void_philo);
void				*philo_dead(void *void_philo);
int					ft_atoi(const char *str);
unsigned long		get_time(void);
int					error(char *argv);
int					put_msg(int id, char *msg, t_philo *philo);
int					check_is_number(char **argv);
int					ft_strcmp(char *s1, char *s2);
void				process_monitor(pid_t *philosopher, t_philo *philo);
void				print_status(unsigned long get_time, int id,
						char *msg, t_philo *philo);
void				msleep(unsigned long end);
#endif
