/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 12:22:58 by sperrin           #+#    #+#             */
/*   Updated: 2021/06/10 21:33:18 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	*philo_dead(void *void_philo)
{
	t_philo	*philo;

	philo = void_philo;
	while (1)
	{
		usleep(100);
		sem_wait(philo->table->s_eat);
		if (philo->cnt_eat == philo->table->must_eat)
			break ;
		if (get_time() - philo->last_eat > philo->table->time_to_die)
		{
			sem_wait(philo->table->s_dead);
			if (!philo->table->dead)
			{
				philo->table->dead = 1;
				print_status(get_time(), philo->num, "died", philo);
				exit(1);
			}
			sem_post(philo->table->s_dead);
			break ;
		}
		sem_post(philo->table->s_eat);
	}
	sem_post(philo->table->s_eat);
	return (NULL);
}

unsigned long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
