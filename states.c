/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:07:47 by atrilles          #+#    #+#             */
/*   Updated: 2022/07/20 16:07:57 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	int	i;
	int	nb;
	
	i = philo->id - 1;
	nb = philo->nb;
	pthread_mutex_lock(&philo->data->forks[i].mutex_fork);
	pthread_mutex_lock(&philo->data->forks[(i + 1) % nb].mutex_fork);
	philo->data->forks[i].state = 1;
	pthread_mutex_lock(&philo->data->mutex_print);
	if (!philo->data->death)
		printf("%ld %d has taken a fork\n", calc_time() - philo->start,
			philo->id);
	pthread_mutex_unlock(&philo->data->mutex_print);
	philo->data->forks[(i + 1) % nb].state = 1;
	philo->start_eat = calc_time();
	pthread_mutex_lock(&philo->data->mutex_print);
	if (!philo->data->death)
	{
		printf("%ld %d has taken a fork\n", calc_time() - philo->start,
			philo->id);
		printf("%ld %d is eating\n", calc_time() - philo->start, philo->id);
	}
	pthread_mutex_unlock(&philo->data->mutex_print);
	philo->meals++;
	u_sleep(philo->time_to_eat);
}

void	sleep_and_think(t_philo *philo)
{
	int	i;
	int	nb;

	i = philo->id - 1;
	nb = philo->nb;
	philo->data->forks[i].state = 0;
	philo->data->forks[(i + 1) % nb].state = 0;
	pthread_mutex_lock(&philo->data->mutex_print);
	if (!philo->data->death)
		printf("%ld %d is sleeping\n", calc_time() - philo->start, philo->id);
	pthread_mutex_unlock(&philo->data->mutex_print);
	pthread_mutex_unlock(&philo->data->forks[i].mutex_fork);
	pthread_mutex_unlock(&philo->data->forks[(i + 1) % nb].mutex_fork);
	u_sleep(philo->time_to_sleep);
//	philo->state = 0;
	pthread_mutex_lock(&philo->data->mutex_print);
	if (!philo->data->death)
		printf("%ld %d is thinking\n", calc_time() - philo->start, philo->id);
	pthread_mutex_unlock(&philo->data->mutex_print);
}

void	death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_death);
	philo->data->death++;
	pthread_mutex_lock(&philo->data->mutex_print);
	if (philo->data->death == 1)
		printf("%ld %d died\n", calc_time() - philo->start, philo->id);
	pthread_mutex_unlock(&philo->data->mutex_print);
	pthread_mutex_unlock(&philo->data->mutex_death);
}

