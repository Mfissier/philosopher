/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 21:48:59 by mafissie          #+#    #+#             */
/*   Updated: 2022/09/28 00:40:35 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philolib.h"

void	destroy_mutex(t_content *content)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&content->m_print);
	pthread_mutex_destroy(&content->m_time_check);
	pthread_mutex_destroy(&content->m_all_eat);
	while (i < content->nbr_phil)
	{
		pthread_mutex_destroy(&content->phil[i].fork);
		pthread_mutex_destroy(&content->phil[i].m_is_eat);
		i++;
	}
}
