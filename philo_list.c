/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/17 12:43:02 by jbax          #+#    #+#                 */
/*   Updated: 2022/11/18 16:52:06 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_all.h"

t_philo_list	*philo_new(t_philo_time *time, int id, int *synk)
{
	t_philo_list	*plist;
	pthread_mutex_t	fork;

	plist = malloc(sizeof(t_philo_list));
	if (!plist)
		return (0);
	plist->philo_id = id;
	plist->next = 0;
	plist->back = 0;
	plist->time = time;
	plist->sync = synk;
	if (pthread_mutex_init(&fork, 0))
		return (0);
	plist->fork_left = &fork;
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
	}

}
