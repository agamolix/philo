/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:04:12 by atrilles          #+#    #+#             */
/*   Updated: 2022/07/20 16:06:37 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, int argc, char **argv)
{
	data->start = calc_time();
	data->nb = my_atoi(argv[1]);
	data->time_to_eat = my_atoi(argv[3]);
	data->time_to_sleep = my_atoi(argv[4]);
	data->time_to_die = my_atoi(argv[2]);
	if (argc == 6)
	{
		data->option = 1;
		data->number_of_times_each_philosopher_must_eat = my_atoi(argv[5]);
	}
	else
		data->option = 0;
	data->death = 0;
	data->have_all_eaten = 0;
	data->forks = malloc(sizeof(t_fork) * (data->nb + 1));
	data->philos = malloc(sizeof(t_philo) * (data->nb + 1));
	pthread_mutex_init(&data->mutex_death, NULL);
	pthread_mutex_init(&data->mutex_print, NULL);
	return (0);
}

int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb)
	{
		data->forks[i].state = 0;
		pthread_mutex_init(&data->forks[i].mutex_fork, NULL);
		data->philos[i].id = i + 1;
		data->philos[i].nb = data->nb;
//		data->philos[i].state = 0;
		data->philos[i].start_eat = data->start;
		data->philos[i].data = data;
		data->philos[i].meals = 0;
		data->philos[i].time_to_die = data->time_to_die;
		data->philos[i].time_to_eat = data->time_to_eat;
		data->philos[i].time_to_sleep = data->time_to_sleep;
		data->philos[i].option = data->option;
		data->philos[i].times = data->number_of_times_each_philosopher_must_eat;
		data->philos[i].start = data->start;
		data->philos[i].finish = 0;
		i++;
	}
	return (0);
}

int	init(t_data *data, int argc, char **argv)
{
	init_data(data, argc, argv);
	init_philo(data);
	if (data->nb < 1 || (data->option && data->number_of_times_each_philosopher_must_eat < 0) 
	|| data->time_to_eat < 0 || data->time_to_sleep < 0 || data->time_to_die < 0)
	{
		if (data->nb < 1)
			printf("Bad arguments: nb of philo < 1\n");
		else if (data->number_of_times_each_philosopher_must_eat < 0)
			printf("Bad arguments: nb of meals < 0\n");
		else if (data->time_to_eat < 0)
			printf("Bad arguments: time to eat < 0\n");
		else if (data->time_to_sleep < 0)
			printf("Bad arguments: time to sleep < 0\n");
		else if (data->time_to_die < 0)
			printf("Bad arguments: time to die < 0\n");
		return (1);
	}
	return (0);
}

int	create_threads(t_data *data)
{
	int			i;

	i = 0;
	while (i < data->nb)
	{
		if (pthread_create(&data->philos[i].tid, NULL, &job, &data->philos[i]))
		{
			printf("Thread create error");
			return (1);
		}
		i++;
	}
	return (0);
}

