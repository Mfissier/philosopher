/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:26:32 by mafissie          #+#    #+#             */
/*   Updated: 2022/09/29 00:24:05 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philolib.h"

int	check_death_bis(t_content *content, t_thread *philo, int i)
{
	pthread_mutex_lock(&content->m_time_check);
	if ((take_time(content) - philo[i].timeout_sleep) > content->t_death)
	{
		pthread_mutex_unlock(&content->m_time_check);
		print_thread(content, i, 4);
		pthread_mutex_lock(&content->m_print);
		content->death = 1;
		pthread_mutex_unlock(&content->m_print);
		return (1);
	}
	pthread_mutex_unlock(&content->m_time_check);
	pthread_mutex_lock(&content->m_all_eat);
	return (0);
}

int	check_death_all(t_content **content, t_thread **philo, int *i, int *j)
{
	pthread_mutex_unlock(&(*content)->m_time_check);
	while (*i < (*content)->nbr_phil)
	{
		if (check_death_bis((*content), (*philo), *i))
			return (1);
		if ((*content)->b_all_eat > 0)
		{
			while (*j < (*content)->nbr_phil)
			{
				if ((*philo)->count_eat != (*content)->b_all_eat)
					break ;
				*j += 1;
			}
			if (*j == (*content)->nbr_phil)
			{
				pthread_mutex_unlock(&(*content)->m_all_eat);
				return (1);
			}
			*j = 0;
		}
		pthread_mutex_unlock(&(*content)->m_all_eat);
		*i += 1;
	}
	*i = 0;
	return (0);
}

void	*check_death(void *point)
{
	t_thread	*philo;
	t_content	*content;
	int			i;
	int			j;

	content = NULL;
	philo = NULL;
	i = 0;
	j = 0;
	content = (t_content *)point;
	philo = (t_thread *)content->phil;
	pthread_mutex_lock(&content->m_time_check);
	if (!content->death)
	{
		while (!content->death)
		{
			if (check_death_all(&content, &philo, &i, &j))
				return (NULL);
			pthread_mutex_lock(&content->m_time_check);
		}
	}
	pthread_mutex_unlock(&content->m_time_check);
	return (NULL);
}
