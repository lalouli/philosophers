/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlalouli <hlalouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:55:15 by hlalouli          #+#    #+#             */
/*   Updated: 2022/04/01 12:18:02 by hlalouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philoso.h"

int	main(int ac, char **av)
{
	t_utils			ut;
	pthread_mutex_t	*forks;
	pthread_mutex_t	p;
	int				i;

	if (ac != 5 && ac != 6)
		return (printf("Wrong params!\n"), 0);
	if (ac == 5 || ac == 6)
	{
		if (!check_error(av, ac))
			return (0);
		else
			create_info_philo(&ut, av, ac);
	}
	i = 1;
	forks = create_fork(&ut);
	pthread_mutex_init(&p, NULL);
	if (!forks || !threads_eating(&ut, forks, &p))
		i = 0;
	destroy_forks(forks, &ut);
	pthread_mutex_destroy(&p);
	return (i);
}
