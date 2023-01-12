/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 19:51:54 by mafissie          #+#    #+#             */
/*   Updated: 2022/09/29 00:24:15 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philolib.h"

void	init_philo(t_content *content)
{
	int			i;
	int			nbr;
	t_content	*tmp;

	tmp = content;
	nbr = content->nbr_phil;
	i = 0;
	while (i <= content->nbr_phil)
	{
		content->phil[i].count_eat = 0;
		content->phil[i].cont = tmp;
		content->phil[i].timeout_sleep = 0;
		content->phil[i].index = i;
		content->phil[i].nbr_philo = nbr;
		content->phil[i].is_eat = nbr;
		i++;
	}
}

void	init_content(t_content *content, int ac, char **args)

{
	content->nbr_phil = ft_atoi(args[1]);
	if (content->nbr_phil > 250)
		ft_error("Nbr of phil is too large !", content);
	content->t_death = ft_atoi(args[2]);
	content->t_eat = ft_atoi(args[3]);
	content->t_sleep = ft_atoi(args[4]);
	if (!content->nbr_phil || !content->t_death || !content->t_eat
		|| !content->t_sleep)
		ft_error("Bad args is 0 !", NULL);
	content->death = 0;
	if (ac == 6)
	{
		content->b_all_eat = ft_atoi(args[5]);
		if (!content->b_all_eat)
			ft_error("Bad args is 0 !", NULL);
	}
	else
		content->b_all_eat = 0;
}

void	init_data(t_content *content, int ac, char **args)
{
	init_content(content, ac, args);
	init_philo(content);
}

void	init_mutex(t_content *content)
{
	int	i;

	i = 0;
	pthread_mutex_init(&content->m_print, NULL);
	pthread_mutex_init(&content->m_time_check, NULL);
	pthread_mutex_init(&content->m_all_eat, NULL);
	while (i <= content->nbr_phil)
	{
		pthread_mutex_init(&content->phil[i].fork, NULL);
		pthread_mutex_init(&content->phil[i].m_is_eat, NULL);
		i++;
	}
}
