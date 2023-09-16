/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msenecha <msenecha@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 13:58:50 by msenecha          #+#    #+#             */
/*   Updated: 2023/09/16 16:23:02 by msenecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					tt_die;
	int					tt_eat;
	int					tt_sleep;
	int					meals;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
}				t_philo;

typedef struct s_gen;
{
	int					dead_flag;
	int					nb_philos;
	pthread_mutex_t		*dead_lock;
	pthread_mutex_t		*eat_lock;
	pthread_mutex_t		*display_lock;
	t_philo				*philos;
}

int	check_nb(char *str);
int	ft_atoi(const char *str);




#endif
