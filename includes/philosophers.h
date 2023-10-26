/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msenecha <msenecha@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 13:58:50 by msenecha          #+#    #+#             */
/*   Updated: 2023/10/26 16:33:34 by msenecha         ###   ########.fr       */
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

# define MAX_PHILO 200

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					dead; // je crois que je l'utilise meme plus en fait, a verifier
	int					nb_philos;
	int					eating;
	int					eaten;
	size_t				start_time;
	size_t				last_meal;
	size_t				tt_die;
	size_t				tt_eat;
	size_t				tt_sleep;
	int					meals;
	pthread_mutex_t		*display_lock;
	pthread_mutex_t		*dead_lock;
	pthread_mutex_t		*eat_lock;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
	struct s_gen		*flag; // utile pour mettre le dead_flag general a 1 si un philo meurt : philo[i].flag->dead_flag (le dead_flag de struct generale qui condition la routine)
}				t_philo;

typedef struct s_gen
{
	int					dead_flag;
	int					nb_philosophers;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		eat_lock;
	pthread_mutex_t		display_lock;
	t_philo				*philo;
}				t_gen;

int		check_nb(char *str);
int		ft_atoi(const char *str);
void	init(char **argv, t_gen *ptr, t_philo *philo, pthread_mutex_t *forks);
size_t	get_current_time(void);
void	*monitoring(void *ptr);
void	*routine(void *ptr);
void	print_actions(char *str, int id, t_philo *philo);
int		ft_usleep(size_t milliseconds);
void	clear_threads(void *ptr);
void	destroy_everything(t_gen *ptr, pthread_mutex_t *forks);
int		check_if_dead(t_philo *philo, size_t tt_die);
int		dead_loop(t_philo *ptr);

#endif
