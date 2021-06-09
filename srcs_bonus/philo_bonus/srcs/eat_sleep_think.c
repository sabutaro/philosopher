/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 12:21:51 by sperrin           #+#    #+#             */
/*   Updated: 2021/06/07 17:33:18 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

static void	take_forks_and_eat(t_philo *philo, t_table *table)
{
	sem_wait(table->s_forks);
	put_msg(philo, "has taken a fork", get_time());
	sem_wait(table->s_forks);
	put_msg(philo, "has taken a fork", get_time());
	put_msg(philo, "is eating", get_time());
	sem_wait(table->s_eat);
	philo->last_eat = get_time();
	++philo->cnt_eat;
	sem_post(table->s_eat);
	m_sleep(philo->table->time_to_eat);
	sem_post(table->s_forks);
	sem_post(table->s_forks);
}

static int	eat(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	take_forks_and_eat(philo, table);
	if (philo->table->must_eat != -1
		&& philo->cnt_eat == philo->table->must_eat)
		return (1);
	return (0);
}

void	m_sleep(unsigned long end)
{
	unsigned long	start;

	start = get_time();
	while (get_time() - start < end)
		usleep(100);
}

int	put_msg(t_philo *philo, char *str, unsigned long curr_time)
{
	sem_wait(philo->table->s_output);
	if ((ft_strcmp("died", str) != 0) && (philo->table->dead == 1
			|| curr_time - philo->last_eat > philo->table->time_to_die))
	{	
		sem_post(philo->table->s_output);
		return (1);
	}
	printf("%lums %d %s\n", curr_time - philo->table->base_time,
		philo->num, str);
	sem_post(philo->table->s_output);
	return (0);
}

void	*start_dinner(void *philo_ptr)
{
	t_philo			*philo;
	pthread_t		tid;

	philo = (t_philo *)philo_ptr;
	if (philo->num % 2 == 0)
		m_sleep(philo->table->time_to_eat);
	pthread_create(&tid, NULL, philo_dead, philo);
	while (1)
	{
		if (eat(philo))
			break ;
		if (put_msg(philo, "is sleeping", get_time()))
			break ;
		m_sleep(philo->table->time_to_sleep);
		if (put_msg(philo, "is thinking", get_time()))
			break ;
	}
	pthread_join(tid, NULL);
	return (NULL);
}
