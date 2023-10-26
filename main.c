/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msenecha <msenecha@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 13:58:30 by msenecha          #+#    #+#             */
/*   Updated: 2023/10/26 16:23:08 by msenecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

void	destroy_everything(t_gen *ptr, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&ptr->display_lock);
	pthread_mutex_destroy(&ptr->eat_lock);
	pthread_mutex_destroy(&ptr->dead_lock);
	while (i < ptr->philo[0].nb_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}


// Fonction de creation des threads apres l'initialisation
// Initialise d'abord le thread de monitoring qui va surveiller si un philo est mort
// ou si tous les philos ont bien mage tous leur repas
// Ensuite, on initialise les threads pour chaque philo
// Derniere etape = pthread_join pour faire attendre le programme jusqu'a ce que
// tous les threads finissent leur routine
void	create_threads(t_gen *ptr, pthread_mutex_t *forks)
{
	int			i;
	pthread_t	monitor;
	t_philo		*philo;

	i = 0;
	philo = ptr->philo;
	if (pthread_create(&monitor, NULL, &monitoring, philo) != 0)
		destroy_everything(ptr, forks);
	while (i < ptr->philo[0].nb_philos)
	{
		if (pthread_create(&ptr->philo[i].thread, NULL, &routine,
				&ptr->philo[i]) != 0)
			destroy_everything(ptr, forks);
		i++;
	}
	if (pthread_join(monitor, NULL) != 0)
		destroy_everything(ptr, forks);
	i = 0;
	while (i < ptr->philo[0].nb_philos)
	{
		if (pthread_join(ptr->philo[i].thread, NULL) != 0)
			destroy_everything(ptr, forks);
		i++;
	}
}

int	check_param(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (write(1, "Error : Wrong number of arguments\n", 35), 1);
	if (ft_atoi(argv[1]) > 200)
		return (write(1, "Error : Number of philosophers should not be \
				more than 200.\n", 61), 1);
	while (i < (argc))
	{
		if (ft_atoi(argv[i]) <= 0)
			return (write(1, "Error : Arguments values are not valid\n",
					39), 1);
		if (check_nb(argv[i]) == 1)
			return (write(1, "Error : Arguments values are not valid\n",
					39), 1);
		i++;
	}
	if ((argv[5]) && (ft_atoi(argv[5]) < 0 || check_nb(argv[5]) == 1))
		return (write(1, "Error : Number of meals is invalid\n", 36), 1);
	return (0);
}


// Initialisation en tableau pour les fourchettes : tableau de mutex, autant de fourchettes que de philos
// Initialisation en tableau de structure pour les philos
// Si un seul philo, tu le fais attendre le time_to_die, il creve, tu l'affiches et basta
int	main(int argc, char **argv)
{
	t_gen			*ptr;
	t_philo			*philo;
	pthread_mutex_t	*forks;

	if (check_param(argc, argv) == 1)
		return (1);
	ptr = malloc(sizeof(t_gen));
	philo = malloc(ft_atoi(argv[1]) * sizeof(t_philo));
	forks = malloc(ft_atoi(argv[1]) * sizeof(pthread_mutex_t));
	init(argv, ptr, philo, forks);
	if (ft_atoi(argv[1]) == 1)
	{
		ft_usleep(ft_atoi(argv[2]));
		printf("%04d : Philo 1 died\n", ft_atoi(argv[2]));
	}
	else
		create_threads(ptr, forks);
	destroy_everything(ptr, forks);
	free (ptr);
	free (forks);
	free (philo);
	return (0);
}
