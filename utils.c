/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlalouli <hlalouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 13:52:56 by hlalouli          #+#    #+#             */
/*   Updated: 2022/04/02 20:06:49 by hlalouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philoso.h"

long	ft_atoi(char *str)
{
	int				i;
	long long int	n;
	int				signe;

	i = 0;
	n = 0;
	signe = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
		return (ERR);
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		n = n * 10 + str[i++] - '0';
	if (str[i] == '\0' && str[i - 1] == '-')
		return (ERR);
	if (str[i] && (str[i] <= '0' || str[i] >= '9'))
		return (ERR);
	return (n * signe);
}

int	check_error(char **av, int ac)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (ft_atoi(av[i]) == ERR || ft_atoi(av[i]) == 0)
			return (printf("Wrong params!\n"), 0);
	}
	return (1);
}

int	ph_sleep(t_philo *philo)
{
	if (*philo->var == 1)
		return (0);
	pthread_mutex_lock(philo->prt);
	printf("%lums %zu is sleeping\n", get_time_s(philo->time), philo->id);
	pthread_mutex_unlock(philo->prt);
	ft_sleep(philo->utils->t_sleep);
	if (*philo->var == 1)
		return (0);
	pthread_mutex_lock(philo->prt);
	printf("%lums %zu is thinking\n", get_time_s(philo->time), philo->id);
	pthread_mutex_unlock(philo->prt);
	return (1);
}

int	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat);
	philo->last_time_eat = ml_time();
	pthread_mutex_lock(philo->prt);
	printf("%lums %zu is eating\n", get_time_s(philo->time), philo->id);
	pthread_mutex_unlock(philo->prt);
	pthread_mutex_unlock(&philo->eat);
	ft_sleep(philo->utils->t_eat);
	philo->nbr_to_eats += 1;
	pthread_mutex_unlock(philo->fork[LEFT]);
	pthread_mutex_unlock(philo->fork[RIGHT]);
	if (*philo->var == 1)
		return (0);
	return (1);
}

void	*routine(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		ft_sleep(2);
	while (*philo->var == 0)
	{
		if (!take_forks(philo, philo->fork[LEFT], philo->fork[RIGHT]))
			break ;
		if (!eat(philo))
			break ;
		if (!ph_sleep(philo))
			break ;
	}
	pthread_mutex_destroy(&philo->eat);
	return (NULL);
}
