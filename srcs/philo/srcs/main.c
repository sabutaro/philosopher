/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:30:16 by sperrin           #+#    #+#             */
/*   Updated: 2021/06/14 15:43:47 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
	if (table->number_of_philosopher > 200)
		return (0);
	if (table->time_to_die < 60 || table->time_to_eat < 60
		|| table->time_to_sleep < 60)
		return (0);
	return (1);
}

static int	init_table(t_table *table)
{
	int		i;

	table->m_forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* table->number_of_philosopher);
	if (!table->m_forks)
		return (1);
	i = 0;
	while (i < table->number_of_philosopher)
	{
		pthread_mutex_init(&table->m_forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&table->m_eat, NULL);
	pthread_mutex_init(&table->m_dead, NULL);
	table->base_time = get_time();
	table->dead = 0;
	return (0);
}

static void	init_dinner(t_philo *philos, t_table *table)
{
	int		i;

	i = 0;
	while (i < table->number_of_philosopher)
	{
		philos[i].num = i + 1;
		philos[i].fork1 = ((i + 1) + (table->number_of_philosopher - 2))
			% table->number_of_philosopher;
		philos[i].fork2 = i;
		philos[i].cnt_eat = 0;
		philos[i].table = table;
		philos[i].is_eating = 0;
		philos[i].last_eat = get_time();
		pthread_create(&philos[i].tid, NULL, start_dinner, &philos[i]);
		i++;
	}
}

void	clean_all(t_table *table, t_philo *philos)
{
	int		i;

	i = 0;
	while (i < table->number_of_philosopher)
	{
		pthread_mutex_destroy(&table->m_forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->m_eat);
	pthread_mutex_destroy(&table->m_dead);
	free(table->m_forks);
	free(philos);
}

int	main(int argc, char **argv)
{
	t_table	table;
	t_philo	*philos;
	int		i;

	if (argc < 5 || argc > 6)
		return (error("Error: Wrong numbers of arguments\n"));
	if (!check_is_number(argv))
		return (error("Error: Bad arguments\n"));
	if (!init_philo_and_time(argc, argv, &table))
		return (error("Error: Problem with the arguments\n"));
	if (init_table(&table))
		return (error("Error: malloc failed\n"));
	philos = (t_philo *)malloc((sizeof(t_philo) * table.number_of_philosopher));
	if (!philos)
		return (1);
	init_dinner(philos, &table);
	i = 0;
	while (i < table.number_of_philosopher)
	{
		pthread_join(philos[i].tid, NULL);
		i++;
	}
	clean_all(&table, philos);
	return (0);
}
