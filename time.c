/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:07:09 by atrilles          #+#    #+#             */
/*   Updated: 2022/07/20 16:07:17 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	calc_time(void)
{
	struct timeval	st;

	gettimeofday(&st, NULL);
	return (st.tv_sec * 1000 + st.tv_usec / 1000);
}

long	get_delta(struct timeval t1, struct timeval t2)
{
	return ((t2.tv_sec - t1.tv_sec) * 1000 + (t2.tv_usec - t1.tv_usec) / 1000);
}

void	u_sleep(long time)
{
	struct timeval	start;
	struct timeval	actuel;

	gettimeofday(&start, NULL);
	gettimeofday(&actuel, NULL);
	while (get_delta(start, actuel) < time)
	{
		gettimeofday(&actuel, NULL);
		usleep(10);
	}
	return ;
}
