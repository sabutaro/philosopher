/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 12:22:58 by sperrin           #+#    #+#             */
/*   Updated: 2021/06/07 16:24:10 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

void	*philo_dead(void *void_philo)
{
	t_philo			*philo;
	unsigned long	curr_time;

	philo = void_philo;
	while (1)
	{
		if (philo->cnt_eat == philo->table->must_eat)
			break ;
		curr_time = get_time();
		if (curr_time - philo->last_eat > philo->table->time_to_die)
		{
			sem_wait(philo->table->s_dead);
			if (philo->table->dead == 0)
			{
				philo->table->dead = 1;
				sem_post(philo->table->s_forks);
				put_msg(philo, "died", curr_time);
				exit (1);
			}
			sem_post(philo->table->s_dead);
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
