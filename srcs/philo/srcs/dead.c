/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:30:23 by sperrin           #+#    #+#             */
/*   Updated: 2021/06/07 16:24:39 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

void	*philo_dead(void *void_philo)
{
	t_philo			*philo;

	philo = void_philo;
	while (1)
	{
		if (philo->cnt_eat == philo->table->must_eat)
			break ;
		if (get_time() - philo->last_eat > philo->table->time_to_die)
		{
			pthread_mutex_lock(&philo->table->m_dead);
			if (philo->table->dead == 0)
			{
				philo->table->dead = 1;
				pthread_mutex_unlock(&philo->table->m_forks[philo->fork1]);
				put_msg(philo, "died", get_time());
			}
			pthread_mutex_unlock(&philo->table->m_dead);
			break ;
		}
		m_sleep(1);
	}
	return (NULL);
}

unsigned long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
