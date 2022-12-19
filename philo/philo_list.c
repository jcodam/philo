/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/17 12:43:02 by jbax          #+#    #+#                 */
/*   Updated: 2022/12/19 14:48:57 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_all.h"

static int	free_philo(t_philo_list **plist, int n_free, pthread_mutex_t *death)
{
	if (n_free > 7 && death)
		pthread_mutex_destroy(death);
	if (n_free > 6 && death)
		free(death);
	if (n_free > 5)
		pthread_mutex_destroy((*plist)->time_mutex);
	if (n_free > 4)
		pthread_mutex_destroy((*plist)->fork_left);
	if (n_free > 3)
		free((*plist)->time_mutex);
	if (n_free > 2)
		free((*plist)->fork_left);
	if (n_free > 1)
		free((*plist));
	return (1);
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
	if (!(*plist)->fork_left)
	{
		free_philo(plist, 2, 0);
		return (1);
	}
	(*plist)->time_mutex = malloc(sizeof(pthread_mutex_t));
	if (!(*plist)->time_mutex)
	{
		free_philo(plist, 3, 0);
		return (1);
	}
	if (pthread_mutex_init((*plist)->fork_left, 0))
		return (free_philo(plist, 4, 0));
	if (pthread_mutex_init((*plist)->time_mutex, 0))
		return (free_philo(plist, 5, 0));
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
			free_philo(&plist, 6, 0);
		if (!death)
			return (0);
		if (pthread_mutex_init(death, 0))
		{
			free_philo(&plist, 7, death);
			return (0);
		}
	}
	plist->death = death;
	plist->philo_id = id;
	plist->next = 0;
	plist->back = 0;
	plist->time = time;
	plist->sync = synk;
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

	if (!new)
	{
		put_s("memory allocation failed\n");
		while (*plist)
			philo_del(plist);
	}
	else if (!*plist)
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
