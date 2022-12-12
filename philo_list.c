/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/17 12:43:02 by jbax          #+#    #+#                 */
/*   Updated: 2022/12/12 15:11:20 by jbax          ########   odam.nl         */
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
		ph->x_eat = -3;
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
	plist->time_mutex = malloc(sizeof(pthread_mutex_t));
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
	if (pthread_mutex_init(plist->time_mutex, 0))
		return (0);
	return (plist);
}
/*   1
    / \
   f   f
  / .   \
 4 .     2
  \ .   /
   f   f
    \ /
     3
*/

int	philo_del(t_philo_list **plist)
{
	t_philo_list	*temp;

	if (!*plist)
		return (1);
	temp = *plist;
	if ((*plist)->next)
	{
		(*plist) = (*plist)->next;
		if (temp->back)
			(*plist)->back = temp->back;
		else
			(*plist)->back = 0;
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
