/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlalouli <hlalouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 21:36:37 by hlalouli          #+#    #+#             */
/*   Updated: 2022/03/26 23:07:54 by hlalouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philoso.h"

int	check_nb_eating(t_philo *philos, unsigned int nb_philos, long nbr_to_eats)
{
	size_t	i;

	i = 0;
	while (i < nb_philos)
	{
		if (philos[i].nbr_to_eats < nbr_to_eats)
			return (0);
		i++;
	}
	return (1);
}

int	is_dead(t_philo *philo)
{
	if (*philo->var == 1)
		return (1);
	pthread_mutex_lock(&philo->eat);
	if ((int)(ml_time() - philo->last_time_eat) >= philo->utils->t_die)
	{
		pthread_mutex_unlock(&philo->eat);
		if (*philo->var == 0)
		{
			*philo->var = 1;
			pthread_mutex_lock(philo->prt);
			printf("%lums %zu died\n", get_time_s(philo->time), philo->id);
			pthread_mutex_unlock(philo->prt);
		}
		return (1);
	}
	pthread_mutex_unlock(&philo->eat);
	return (0);
}

int	check_death(t_philo *philos, unsigned int nb_philos)
{
	size_t	i;

	i = 0;
	while (i < nb_philos)
	{
		if (is_dead(&philos[i]))
			return (1);
		i++;
	}
	return (0);
}

void	unlock_forks(pthread_mutex_t *forks, unsigned int nb_philos)
{
	size_t	i;

	i = 0;
	while (i < nb_philos)
	{
		pthread_mutex_unlock(&forks[i]);
		i++;
	}
}
