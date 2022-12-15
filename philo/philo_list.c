/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/17 12:43:02 by jbax          #+#    #+#                 */
/*   Updated: 2022/12/15 14:14:17 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_all.h"

int	time_new(int argc, char **argv, t_philo_time *ph)
{
	int	error;

	error = 0;
	ph->n_philo = ft_atoi(argv[1]);
	ph->t_death = ft_atoi(argv[2]);
	ph->t_eat = ft_atoi(argv[3]);
	ph->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		ph->x_eat = ft_atoi(argv[5]);
	else
		ph->x_eat = -3;
	what_error(ph, &error, argc);
	if (error == 1)
		return (1);
	if (ph->n_philo == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(ph->t_death * 1000);
		printf("%i 1 died\n", ph->t_death);
		return (1);
	}
	return (0);
}

static int	malloc_philo(t_philo_list **plist)
{
	if (!plist)
		return (1);
	*plist = 0;
	*plist = malloc(sizeof(t_philo_list));
	if (!*plist)
		return (1);
	(*plist)->fork_left = 0;
	(*plist)->time_mutex = 0;
	(*plist)->fork_left = malloc(sizeof(pthread_mutex_t));
	(*plist)->time_mutex = malloc(sizeof(pthread_mutex_t));
	if (!(*plist)->fork_left || !(*plist)->time_mutex)
		return (1);
	return (0);
}

t_philo_list	*philo_new(t_philo_time *time, int id, int *synk)
{
	t_philo_list			*plist;
	static pthread_mutex_t	*death = 0;

	if (malloc_philo(&plist))
		return (0);
	if (!death)
	{
		death = malloc(sizeof(pthread_mutex_t));
		if (!death)
			return (0);
		if (pthread_mutex_init(death, 0))
			return (0);
	}
	plist->death = death;
	plist->philo_id = id;
	plist->next = 0;
	plist->back = 0;
	plist->time = time;
	plist->sync = synk;
	if (pthread_mutex_init(plist->fork_left, 0))
		return (0);
	if (pthread_mutex_init(plist->time_mutex, 0))
		return (0);
	return (plist);
}

int	philo_del(t_philo_list **plist)
{
	t_philo_list	*temp;

	if (!*plist)
		return (1);
	temp = *plist;
	if ((*plist)->next)
	{
		(*plist) = (*plist)->next;
		(*plist)->back = temp->back;
	}
	else if (!temp->back)
	{
		pthread_mutex_destroy(temp->death);
		free(temp->death);
		*plist = 0;
	}
	pthread_mutex_destroy(temp->fork_left);
	free(temp->fork_left);
	pthread_mutex_destroy(temp->time_mutex);
	free(temp->time_mutex);
	free(temp);
	temp = 0;
	return (0);
}

void	philo_addback(t_philo_list **plist, t_philo_list *new)
{
	t_philo_list	*temp;

	if (!*plist)
		*plist = new;
	else
	{
		temp = *plist;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
		new->back = temp;
		new->fork_right = temp->fork_left;
		(*plist)->fork_right = new->fork_left;
	}
}
