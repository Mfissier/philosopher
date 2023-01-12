/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philolib.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafissie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:23:09 by mafissie          #+#    #+#             */
/*   Updated: 2022/09/28 19:04:31 by mafissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOLIB_H
# define PHILOLIB_H

# include <stddef.h>
# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

struct	s_content;

typedef struct s_thread
{
	pthread_mutex_t		fork;
	long int			timeout_sleep;
	int					count_eat;
	int					index;
	int					nbr_philo;
	int					is_eat;
	struct timeval		p_timeout;
	pthread_mutex_t		m_is_eat;
	pthread_t			p_thread;
	struct s_content	*cont;
}				t_thread;

typedef struct s_content
{
	int				nbr_phil;
	int				t_eat;
	int				t_sleep;
	int				t_death;
	int				death;
	int				b_all_eat;
	pthread_mutex_t	m_all_eat;
	pthread_mutex_t	m_time_check;
	pthread_t		death_thread;
	struct timeval	timeout;
	pthread_mutex_t	m_print;
	t_thread		phil[250];
}				t_content;

//check_death.c
void			*check_death(void *point);

// destroy.c
void			destroy_mutex(t_content *content);

// error_handling.c
void			putserr(char *str);
void			ft_error(char *str, void *pcontent);
void			as_error_args(int ac, char **av);

// init.c
void			init_philo(t_content *content);
void			init_content(t_content *content, int ac, char **args);
void			init_data(t_content *content, int ac, char **args);
void			init_mutex(t_content *content);

// philosophers.c
int				fork_and_eat(t_thread *philo, t_content *tmp, int i);
void			ft_philo_data(t_thread **philo, t_content **tmp, \
				int *j, int *i);
void			sleep_philo(t_content *tmp, t_thread *philo);
void			*ft_philosophers(void *content);
void			launch_philosophers(t_content *content);

// utils.c
size_t			ft_strlen(const char *str);
int				ft_atoi(const char *nptr);
void			ft_digit(char *s);

//utils_thread.c
long long int	take_time(t_content *content);
long long int	take_time_philo(t_thread *philo);
void			print_thread(t_content *content, int index, int print);
#endif
