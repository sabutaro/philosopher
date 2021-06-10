/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 12:22:53 by sperrin           #+#    #+#             */
/*   Updated: 2021/06/10 16:43:15 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static pid_t	wait_philosophers(t_philo *philo)
{
	pid_t	pid;
	int		i;
	int		status;
	int		count;

	count = 0;
	i = -1;
	while (++i < philo->table->number_of_philosopher)
	{
		status = 0;
		pid = waitpid(-1, &status, 0);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 1)
				return (pid);
			else if (WEXITSTATUS(status) == 0)
			{
				if (++count == philo->table->number_of_philosopher)
					break ;
			}
		}
	}
	return (-1);
}

void	process_monitor(pid_t *philosophers, t_philo *philo)
{
	pid_t	pid;
	int		i;

	pid = wait_philosophers(philo);
	if (pid != -1)
	{
		i = 0;
		while (i < philo->table->number_of_philosopher)
		{
			kill(philosophers[i], SIGKILL);
			i++;
		}
	}
}
