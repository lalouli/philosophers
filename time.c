/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlalouli <hlalouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 16:44:45 by hlalouli          #+#    #+#             */
/*   Updated: 2022/04/03 11:51:18 by hlalouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philoso.h"

size_t	ml_time(void)
{
	struct timeval	tp;
	size_t			milliseconds;

	gettimeofday(&tp, NULL);
	milliseconds = tp.tv_sec * 1000;
	milliseconds += tp.tv_usec / 1000;
	return (milliseconds);
}

void	ft_sleep(size_t ms)
{
	size_t	curr;
	size_t	end;

	curr = ml_time();
	end = curr + ms;
	while (ml_time() < end)
		usleep(100);
}

unsigned long	get_time_s(struct timeval tm)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((unsigned long)(tv.tv_sec * 1000 + tv.tv_usec / 1000)
			- (tm.tv_sec * 1000 + tm.tv_usec / 1000));
}
