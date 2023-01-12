/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 23:42:14 by mafissie          #+#    #+#             */
/*   Updated: 2022/09/28 19:06:37 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philolib.h"

long long int	take_time(t_content *content)
{
	struct timeval		save_t;
	long int			i;
	long int			y;

	gettimeofday(&save_t, NULL);
	i = (save_t.tv_sec - content->timeout.tv_sec) * 1000;
	y = (save_t.tv_usec - content->timeout.tv_usec) / 1000;
	return (i + y);
}

long long int	take_time_philo(t_thread *philo)
{
	struct timeval		save_t;
	long int			i;
	long int			y;

	save_t.tv_sec = 0;
	save_t.tv_usec = 0;
	gettimeofday(&save_t, NULL);
	i = (save_t.tv_sec - philo->p_timeout.tv_sec) * 1000;
	y = (save_t.tv_usec - philo->p_timeout.tv_usec) / 1000;
	return (i + y);
}

void	print_thread(t_content *content, int index, int print)
{
	t_content	*tmp;

	tmp = NULL;
	tmp = content;
	pthread_mutex_lock(&tmp->m_print);
	if (!tmp->death)
	{
		if (print == 0)
			printf("%lld %d has taken a fork\n", take_time(tmp), index + 1);
		else if (print == 1)
			printf("%lld %d is eating\n", take_time(tmp), index + 1);
		else if (print == 2)
			printf("%lld %d is sleeping\n", take_time(tmp), index + 1);
		else if (print == 3)
			printf("%lld %d is thinking\n", take_time(tmp), index + 1);
		else if (print == 4)
			printf("%lld %d died\n", take_time(tmp), index + 1);
	}
	pthread_mutex_unlock(&tmp->m_print);
}
