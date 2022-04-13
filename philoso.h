/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoso.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlalouli <hlalouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 14:00:48 by hlalouli          #+#    #+#             */
/*   Updated: 2022/03/26 23:18:25 by hlalouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSO_H
# define PHILOSO_H
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define ERR 4000000000

# define LEFT 0
# define RIGHT 1

typedef struct s_utils
{
	int				nb_philo;
	int				t_eat;
	int				t_sleep;
	int				t_die;
	int				nbr_of_eats;
	int				is_dead;
	pthread_mutex_t	pen;
}	t_utils;

typedef struct s_philo
{
	size_t			id;
	long			nbr_to_eats;
	int				*var;
	pthread_mutex_t	*fork[2];
	pthread_mutex_t	*prt;
	pthread_mutex_t	eat;
	size_t			last_time_eat;
	t_utils			*utils;
	struct timeval	time;
	pthread_t		th;
}	t_philo;

long			ft_atoi(char	*str);
int				check_error(char **av, int ac);
void			create_info_philo(t_utils *utils, char **av, int ac);
pthread_mutex_t	*create_fork(t_utils *utils);
void			insert_end(t_philo **head, char **av, int ac);
void			get_forks(t_philo *philo, size_t i, pthread_mutex_t *forks,
					unsigned int nb_philo);
int				take_forks(t_philo *philo, pthread_mutex_t *fleft,
					pthread_mutex_t *fright);
void			n_philos(t_philo *philos, t_utils *utils,
					pthread_mutex_t *forks, pthread_mutex_t *print);
size_t			ml_time(void);
void			ft_sleep(size_t ms);
void			destroy_forks(pthread_mutex_t *forks, t_utils *utils);
unsigned long	get_time_s(struct timeval tm);
int				threads_eating(t_utils *utls, pthread_mutex_t *frks,
					pthread_mutex_t *prt);
int				eat(t_philo *philo);
int				ph_sleep(t_philo *philo);
void			*routine(void *arg);
int				check_nb_eating(t_philo *philos, unsigned int nb_philos,
					long nbr_to_eats);
int				is_dead(t_philo *philo);
int				check_death(t_philo *philos, unsigned int nb_philos);
void			unlock_forks(pthread_mutex_t *forks, unsigned int nb_philos);

#endif