/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 12:22:53 by sperrin           #+#    #+#             */
/*   Updated: 2021/06/07 17:40:12 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

int	kill_processus(t_philo *philo, int count, int status)
{
	int	i;

	if ((WIFEXITED(status) && WEXITSTATUS(status) == 1)
		|| count == philo->table->number_of_philosopher)
	{
		i = 0;
		while (i < philo->table->number_of_philosopher)
		{
			kill(philo[i].pid, SIGKILL);
			i++;
		}
		return (1);
	}
	return (0);
}

void	process_monitor(t_philo *philo, int count)
{
	int	status;
	int	i;

	while (1)
	{
		i = 0;
		while (i < philo->table->number_of_philosopher)
		{
			status = -1;
			waitpid(philo[i].pid, &status, WNOHANG);
			if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
				count++;
			if ((WIFEXITED(status) && WEXITSTATUS(status) == 1)
				|| count == philo->table->number_of_philosopher)
				break ;
			i++;
		}
		if (kill_processus(philo, count, status))
			break ;
	}
}
