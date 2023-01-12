/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 22:23:56 by mafissie          #+#    #+#             */
/*   Updated: 2022/10/02 18:26:52 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./philolib.h" 

int	fork_and_eat(t_thread *philo, t_content *tmp, int i)
{
	pthread_mutex_lock(&tmp->phil[i].fork);
	print_thread(tmp, philo->index, 0);
	pthread_mutex_lock(&tmp->phil[philo->index].fork);
	print_thread(tmp, philo->index, 0);
	print_thread(tmp, philo->index, 1);
	pthread_mutex_lock(&tmp->m_time_check);
	philo->timeout_sleep = take_time(tmp);
	pthread_mutex_unlock(&tmp->m_time_check);
	usleep(tmp->t_eat * 1000);
	pthread_mutex_lock(&tmp->m_all_eat);
	philo->count_eat++;
	pthread_mutex_unlock(&tmp->m_all_eat);
	pthread_mutex_lock(&tmp->m_print);
	if (tmp->death)
	{
		pthread_mutex_unlock(&tmp->phil[i].fork);
		pthread_mutex_unlock(&tmp->phil[philo->index].fork);
		pthread_mutex_unlock(&tmp->m_print);
		return (1);
	}
	pthread_mutex_unlock(&tmp->m_print);
	pthread_mutex_unlock(&tmp->phil[i].fork);
	pthread_mutex_unlock(&tmp->phil[philo->index].fork);
	pthread_mutex_lock(&tmp->m_all_eat);
	return (0);
}

void	ft_philo_data(t_thread **philo, t_content **tmp, int *j, int *i)
{
	*j = 1;
	if (((*philo)->index) % 2)
		usleep(3000);
	print_thread(*tmp, (*philo)->index, 3);
	if ((*philo)->index == (*philo)->nbr_philo)
		*i = (*philo)->nbr_philo - 1;
	else
		*i = (*philo)->index + 1;
	pthread_mutex_lock(&(*tmp)->m_all_eat);
	if ((*tmp)->b_all_eat > 0)
		*j = (*tmp)->b_all_eat;
	pthread_mutex_unlock(&(*tmp)->m_all_eat);
}

void	sleep_philo(t_content *tmp, t_thread *philo)
{
	print_thread(tmp, philo->index, 2);
	usleep(tmp->t_sleep * 1000);
}

void	*ft_philosophers(void *content)
{
	t_thread	*philo;
	t_content	*tmp;
	int			i;
	int			j;

	philo = NULL;
	tmp = NULL;
	philo = (t_thread *)content;
	tmp = (t_content *)philo->cont;
	ft_philo_data(&philo, &tmp, &j, &i);
	while (j)
	{
		if (fork_and_eat(philo, tmp, i))
			return (NULL);
		if (tmp->b_all_eat > 0)
			j--;
		if (j == 0)
		{
			pthread_mutex_unlock(&tmp->m_all_eat);
			return (NULL);
		}
		pthread_mutex_unlock(&tmp->m_all_eat);
		sleep_philo(tmp, philo);
	}
	return (NULL);
}

void	launch_philosophers(t_content *content)
{
	int			i;
	t_content	*tmp;

	tmp = content;
	i = 0;
	while (i < tmp->nbr_phil)
	{
		pthread_create(&tmp->phil[i].p_thread, NULL, &ft_philosophers, \
				&tmp->phil[i]);
		i++;
	}
	pthread_create(&tmp->death_thread, NULL, check_death, tmp);
	i = 0;
	while (i < tmp->nbr_phil)
	{
		pthread_join(tmp->phil[i].p_thread, NULL);
		i++;
	}
	pthread_join(tmp->death_thread, NULL);
}
