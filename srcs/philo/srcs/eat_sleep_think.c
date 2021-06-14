/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:30:37 by sperrin           #+#    #+#             */
/*   Updated: 2021/06/14 18:36:56 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_status(unsigned long get_time, int id, char *msg, t_philo *philo)
{
	printf("%lums %d %s\n", get_time - philo->table->base_time, id, msg);
}

void	msleep(unsigned long end)
{
	unsigned long	start;

	start = get_time();
	while (get_time() - start < end)
		usleep(100);
}

int	put_msg(int id, char *msg, t_philo *philo)
{
	pthread_mutex_lock(&philo->table->m_dead);
	if (philo->table->dead)
	{
		pthread_mutex_unlock(&philo->table->m_dead);
		return (1);
	}
	print_status(get_time(), id, msg, philo);
	pthread_mutex_unlock(&philo->table->m_dead);
	return (0);
}

int	eat(int id, t_philo *philo)
{	
	t_table			*table;

	table = philo->table;
	pthread_mutex_lock(&table->m_forks[philo->fork1]);
	put_msg(id, "has taken a fork", philo);
	pthread_mutex_lock(&table->m_forks[philo->fork2]);
	put_msg(id, "has taken a fork", philo);
	put_msg(id, "is eating", philo);
	pthread_mutex_lock(&philo->table->m_eat);
	philo->cnt_eat++;
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->table->m_eat);
	usleep(philo->table->time_to_eat * 1000);
	pthread_mutex_unlock(&table->m_forks[philo->fork1]);
	pthread_mutex_unlock(&table->m_forks[philo->fork2]);
	if (philo->table->must_eat != -1
		&& philo->cnt_eat == philo->table->must_eat)
		return (1);
	return (0);
}

void	*start_dinner(void *philo_ptr)
{
	t_philo			*philo;
	pthread_t		tid;
	int				i;

	i = 0;
	philo = philo_ptr;
	if (philo->num % 2 == 0)
		msleep(philo->table->time_to_eat);
	pthread_create(&tid, NULL, philo_dead, philo);
	while (1)
	{
		if (eat(philo->num, philo) == 1)
			break ;
		if (put_msg(philo->num, "is sleeping", philo) == 1)
			break ;
		usleep(philo->table->time_to_sleep * 1000);
		if (put_msg(philo->num, "is thinking", philo) == 1)
			break ;
	}
	pthread_join(tid, NULL);
	return (NULL);
}
