/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlalouli <hlalouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:47:11 by hlalouli          #+#    #+#             */
/*   Updated: 2022/04/02 20:03:03 by hlalouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philoso.h"

void	create_info_philo(t_utils *utils, char **av, int ac)
{
	utils->nb_philo = ft_atoi(av[1]);
	utils->t_die = ft_atoi(av[2]);
	utils->t_eat = ft_atoi(av[3]);
	utils->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		utils->nbr_of_eats = ft_atoi(av[5]);
}

void	n_philos(t_philo *philos, t_utils *utils, pthread_mutex_t *forks,
			pthread_mutex_t *print)
{
	int	i;

	i = 0;
	while (i < utils->nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].nbr_to_eats = 0;
		philos[i].utils = utils;
		philos[i].prt = print;
		pthread_mutex_init(&philos[i].eat, NULL);
		get_forks(&philos[i], i, forks, utils->nb_philo);
		i++;
	}
}			

int	watch_threads(t_utils *utils, t_philo *philos, unsigned int nb_philos,
			pthread_mutex_t *forks)
{
	size_t	i;

	i = 0;
	while (*philos->var == 0)
	{
		ft_sleep(4);
		check_death(philos, nb_philos);
		if (*philos->var == 0 && utils->nbr_of_eats > 0
			&& check_nb_eating(philos, nb_philos, utils->nbr_of_eats))
		{
			*philos->var = 1;
			ft_sleep(5);
			printf("Everyone ate well\n");
		}
	}
	while (i < nb_philos)
	{
		if (i == 0 && *philos->var == 1)
			unlock_forks(forks, nb_philos);
		if (pthread_join(philos[i].th, NULL))
			return (0);
		i++;
	}
	free(philos);
	return (1);
}

int	threads_eating(t_utils *utls, pthread_mutex_t *frks, pthread_mutex_t *prt)
{
	t_philo			*philos;
	int				i;
	int				var;
	struct timeval	time;

	i = 0;
	var = 0;
	philos = malloc(sizeof(t_philo) * utls->nb_philo);
	if (!philos)
		return (0);
	n_philos(philos, utls, frks, prt);
	gettimeofday(&time, NULL);
	while (i < utls->nb_philo)
	{
		philos[i].var = &var;
		philos[i].time = time;
		philos[i].last_time_eat = ml_time();
		if (pthread_create(&philos[i].th, NULL, &routine, &philos[i]))
			return (0);
		i++;
	}
	return (watch_threads(utls, philos, utls->nb_philo, frks));
}
