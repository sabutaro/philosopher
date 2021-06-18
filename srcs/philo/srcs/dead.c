/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 12:22:58 by sperrin           #+#    #+#             */
/*   Updated: 2021/06/18 12:57:12 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*philo_dead(void *void_philo)
{
	t_philo	*philo;

	philo = void_philo;
	while (1)
	{
		usleep(1000);
		pthread_mutex_lock(&philo->table->m_eat);
		if (philo->cnt_eat == philo->table->must_eat)
			break ;
		if (get_time() - philo->last_eat > philo->table->time_to_die)
		{
			pthread_mutex_lock(&philo->table->m_dead);
			if (!philo->table->dead)
			{
				philo->table->dead = 1;
				pthread_mutex_unlock(&philo->table->m_forks[philo->fork1]);
				print_status(get_time(), philo->num, "died", philo);
			}
			pthread_mutex_unlock(&philo->table->m_dead);
			break ;
		}
		pthread_mutex_unlock(&philo->table->m_eat);
	}
	pthread_mutex_unlock(&philo->table->m_eat);
	return (NULL);
}

unsigned long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
