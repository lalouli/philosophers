/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlalouli <hlalouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 21:11:10 by hlalouli          #+#    #+#             */
/*   Updated: 2022/03/26 23:23:38 by hlalouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philoso.h"

pthread_mutex_t	*create_fork(t_utils *utils)
{
	pthread_mutex_t	*frk;
	int				i;

	i = 0;
	frk = malloc(sizeof(pthread_mutex_t) * utils->nb_philo);
	if (!frk)
		return (0);
	while (i < utils->nb_philo)
	{
		pthread_mutex_init(&frk[i], NULL);
		i++;
	}
	return (frk);
}

void	get_forks(t_philo *philo, size_t i, pthread_mutex_t *forks,
				unsigned int nb_philo)
{
	if (i == 0)
	{
		philo->fork[LEFT] = &forks[nb_philo - 1];
		philo->fork[RIGHT] = &forks[0];
	}
	else
	{
		philo->fork[LEFT] = &forks[i - 1];
		philo->fork[RIGHT] = &forks[i];
	}
}

int	take_forks(t_philo *philo, pthread_mutex_t *fleft, pthread_mutex_t *fright)
{
	if (*philo->var == 1)
		return (0);
	pthread_mutex_lock(fleft);
	if (*philo->var == 1)
		return (0);
	pthread_mutex_lock(philo->prt);
	printf("%lu ms %zu take a fork\n", get_time_s(philo->time), philo->id);
	pthread_mutex_unlock(philo->prt);
	pthread_mutex_lock(fright);
	if (*philo->var == 1)
		return (0);
	pthread_mutex_lock(philo->prt);
	printf("%lu ms %zu take a fork\n", get_time_s(philo->time), philo->id);
	pthread_mutex_unlock(philo->prt);
	return (1);
}

void	destroy_forks(pthread_mutex_t *forks, t_utils *utils)
{
	int	i;

	i = 0;
	while (i < utils->nb_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}
