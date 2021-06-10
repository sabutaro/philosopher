/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 12:08:15 by sperrin           #+#    #+#             */
/*   Updated: 2021/06/10 21:14:31 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	init_philo_and_time(int argc, char **argv, t_table *table)
{
	table->number_of_philosopher = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->must_eat = ft_atoi(argv[5]);
	else
		table->must_eat = -1;
	if (table->number_of_philosopher <= 1 || table->number_of_philosopher > 200)
		return (0);
	if (table->time_to_die < 60 || table->time_to_eat < 60
		|| table->time_to_sleep < 60)
		return (0);
	return (1);
}

static int	init_table(t_table *table)
{	
	sem_unlink("/fork");
	sem_unlink("/eat");
	sem_unlink("/dead");
	sem_unlink("/permits");
	table->s_forks = sem_open("/fork", O_CREAT | O_EXCL,
			S_IRWXU, table->number_of_philosopher);
	table->s_eat = sem_open("/eat", O_CREAT | O_EXCL, S_IRWXU, 1);
	table->s_dead = sem_open("/dead", O_CREAT | O_EXCL, S_IRWXU, 1);
	table->s_permits = sem_open("/permits", O_CREAT | O_EXCL, S_IRWXU, 1);
	table->base_time = get_time();
	table->dead = 0;
	return (0);
}

static void	init_philo(t_philo *philo, t_table *table, pid_t *philosopher)
{
	int		i;

	i = 0;
	while (i < table->number_of_philosopher)
	{
		philo[i].num = i + 1;
		philo[i].cnt_eat = 0;
		philo[i].table = table;
		philo[i].last_eat = get_time();
		philosopher[i] = fork();
		if (philosopher[i] < 0)
			exit(1);
		if (philosopher[i] == 0)
		{
			start_dinner(&philo[i]);
			return ;
		}
		i++;
	}
	process_monitor(philosopher, philo);
}

void	clean_all(t_table *table, t_philo *philo, pid_t *philosopher)
{
	sem_unlink("/fork");
	sem_unlink("/eat");
	sem_unlink("/dead");
	sem_unlink("/permits");
	sem_close(table->s_forks);
	sem_close(table->s_eat);
	sem_close(table->s_dead);
	sem_close(table->s_permits);
	free(philo);
	free(philosopher);
}

int	main(int argc, char **argv)
{
	t_table	table;
	t_philo	*philo;
	pid_t	*philosopher;

	if (argc < 5 || argc > 6)
		return (error("Error: Wrong numbers of arguments\n"));
	if (!check_is_number(argv))
		return (error("Error: Bad arguments\n"));
	if (!init_philo_and_time(argc, argv, &table))
		return (error("Error: Problem with the arguments\n"));
	if (init_table(&table))
		return (error("Error: malloc failed\n"));
	philo = (t_philo *)malloc((sizeof(t_philo) * table.number_of_philosopher));
	philosopher = malloc(sizeof(pid_t) * table.number_of_philosopher);
	if (!philo)
		return (1);
	init_philo(philo, &table, philosopher);
	clean_all(&table, philo, philosopher);
	return (0);
}
