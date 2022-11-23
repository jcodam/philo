/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/17 12:43:02 by jbax          #+#    #+#                 */
/*   Updated: 2022/11/23 16:53:13 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_all.h"

int	time_new(int argc, char **argv, t_philo_time *ph)
{
	ph->n_philo = ft_atoi(argv[1]);
	ph->t_death = ft_atoi(argv[2]);
	ph->t_eat = ft_atoi(argv[3]);
	ph->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		ph->x_eat = ft_atoi(argv[5]);
	else
		ph->x_eat = -1;
	return (0);
}

t_philo_list	*philo_new(t_philo_time *time, int id, int *synk)
{
	t_philo_list			*plist;
	static pthread_mutex_t	*death = 0;

	plist = malloc(sizeof(t_philo_list));
	if (!plist)
		return (0);
	plist->fork_left = malloc(sizeof(pthread_mutex_t));
	if (!death)
	{
		death = malloc(sizeof(pthread_mutex_t));
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
	return (plist);
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
		temp->fork_right = new->fork_left;
		new->fork_right = (*plist)->fork_left;
	}
}
