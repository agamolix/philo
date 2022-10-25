/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <atrilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 17:40:41 by atrilles          #+#    #+#             */
/*   Updated: 2022/07/20 15:50:03 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include "philo.h"
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				nb;
//	int				state;
	int				meals;
	int				finish;
	long int		start_eat;
	long int		start_sleep;
	long int		start_think;
	struct s_data	*data;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				times;
	int				option;
	long int		start;
	pthread_t		tid;
}	t_philo;

typedef struct s_fork
{
	int				state;
	pthread_mutex_t	mutex_fork;
}	t_fork;

typedef struct s_data
{
	int				nb;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				number_of_times_each_philosopher_must_eat;
	int				option;
	int				death;
	long int		start;
	int				have_all_eaten;
	pthread_t		death_tid;
	pthread_mutex_t	mutex_death;
	t_philo			*philos;
	t_fork			*forks;
	pthread_mutex_t	mutex_print;
}	t_data;

typedef struct s_mutex
{
	int				data;
	pthread_mutex_t	mutex;
}	t_mutex;


//-----main-----
void		check_case(t_philo *philo, int i, int nb);
int			main(int argc, char **argv);
void		*job(void *arg);
void		*death_job(void *arg);

//-----functions-----
char		*remove_space(char *str);
int			convert(char *str, int len_nb, int sign);
int			calc_len_nb(char *str);
int			my_atoi(const char *nptr);

//-----time-----
long int	calc_time(void);
long		get_delta(struct timeval t1, struct timeval t2);
void		u_sleep(long int time);
//-----states-----
void		eat(t_philo *philo);
void		sleep_and_think(t_philo *philo);
void		death(t_philo *philo);
void		eaten_all(t_philo *philo);

//-----init-----
int			init_data(t_data *data, int argc, char **argv);
int			init_philo(t_data *data);
int			init(t_data *data, int argc, char **argv);
int			create_threads(t_data *data);

#endif