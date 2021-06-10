/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 12:21:51 by sperrin           #+#    #+#             */
/*   Updated: 2021/06/10 21:23:20 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

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
	sem_wait(philo->table->s_dead);
	if (philo->table->dead)
	{
		sem_post(philo->table->s_dead);
		return (1);
	}
	print_status(get_time(), id, msg, philo);
	sem_post(philo->table->s_dead);
	return (0);
}

int	eat_sleep(int id, t_philo *philo)
{	
	sem_wait(philo->table->s_permits);
	sem_wait(philo->table->s_forks);
	put_msg(id, "has taken a fork", philo);
	sem_wait(philo->table->s_forks);
	put_msg(id, "has taken a fork", philo);
	sem_post(philo->table->s_permits);
	put_msg(id, "is eating", philo);
	sem_wait(philo->table->s_eat);
	philo->cnt_eat++;
	philo->last_eat = get_time();
	sem_post(philo->table->s_eat);
	msleep(philo->table->time_to_eat);
	sem_post(philo->table->s_forks);
	sem_post(philo->table->s_forks);
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
		if (eat_sleep(philo->num, philo) == 1)
			break ;
		if (put_msg(philo->num, "is sleeping", philo) == 1)
			exit (1);
		msleep(philo->table->time_to_sleep);
		if (put_msg(philo->num, "is thinking", philo) == 1)
			exit(1);
	}
	pthread_join(tid, NULL);
	return (NULL);
}
