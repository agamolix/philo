/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:06:50 by atrilles          #+#    #+#             */
/*   Updated: 2022/07/20 16:07:00 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_case(t_philo *philo, int i, int nb)
{
	if (nb != 1 && !philo->data->death && !philo->data->forks[i].state
		&& !philo->data->forks[(i + 1) % nb].state)
	{
		eat(philo);
		sleep_and_think(philo);
	}
	return;
}

void check_death_or_alleaten(t_data *data)
{
	int i;
	int nb = data->nb;
	int ttd = data->time_to_die;

	while (1)
	{
		if (!data->death && data->have_all_eaten == nb)
		{
			pthread_mutex_lock(&data->mutex_print);
			printf("%ld Philosophers have eaten all their meals\n", calc_time() - data->start);
			pthread_mutex_unlock(&data->mutex_print);
			return;
		}
		i = 0;
		while (i < nb)
		{
			if (!data->philos[i].finish && calc_time() >= data->philos[i].start_eat + ttd)
			{
				death(&data->philos[i]);
				return;
			}
			i++;
		}
	}	
}

void	*job(void *arg)
{
	t_philo	*philo;
	philo = (t_philo *)arg;

	int i = philo->id - 1;
	int nb = philo->nb;
	int option = philo->option;
	int times = philo->times;

	while (1)
	{
		if (philo->data->death || philo->finish)
			return 0;
		if (!philo->finish && !philo->data->death)
			check_case(philo, i, nb);
		if (!philo->data->death && option == 1 && philo->meals == times)
		{
			philo->data->have_all_eaten++;
			philo->finish = 1;
			return 0;
		}
		usleep(10);
	}
	return 0;
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (argc > 6 || argc < 5)
	{
		printf("Bad arguments: wrong nb of args\n");
		return (1);
	}
	if (init(&data, argc, argv))
		return (1);
	if (create_threads(&data))
		return (1);

	check_death_or_alleaten(&data);

	i = 0;
	while(i < data.nb)
	{
		pthread_join(data.philos[i].tid, NULL);
		i++;
	}

	i = 0;
	while (i < data.nb)
	{
		pthread_mutex_destroy(&data.forks[i].mutex_fork);
		i++;
	}
	pthread_mutex_destroy(&data.mutex_death);
	pthread_mutex_destroy(&data.mutex_print);
	free(data.forks);
	free(data.philos);
	return (0);
}
