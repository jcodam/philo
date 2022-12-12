/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_util.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/24 16:25:57 by jbax          #+#    #+#                 */
/*   Updated: 2022/12/12 17:23:32 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_all.h"

int	run_time(struct timeval begin)
{
	struct timeval	new;
	int				i;
	int				t;

	gettimeofday(&new, 0);
	t = new.tv_sec - begin.tv_sec;
	i = ((new.tv_usec + (t * 1000000)) - begin.tv_usec) / 1000;
	return (i);
}

int	unlock_fork(t_philo_list *plist)
{
	pthread_mutex_unlock(plist->fork_right);
	pthread_mutex_unlock(plist->fork_left);
	return (0);
}

int	to_late_for_dinner(struct timeval og, t_philo_list *plist,
		char *str, int f_switch)
{
	pthread_mutex_lock(plist->death);
	if (*plist->sync == -1)
	{
		pthread_mutex_unlock(plist->death);
		if (f_switch)
		{
			unlock_fork(plist);
		}
		return (1);
	}
	if (run_time(og) >= plist->last_meal + plist->time->t_death)
	{
		*plist->sync = -1;
		pthread_mutex_unlock(plist->death);
		printf("%d %d died\n", run_time(og), plist->philo_id);
		if (f_switch)
		{
			unlock_fork(plist);
		}
		return (1);
	}
	if (str)
		printf("%d %d %s", run_time(og), plist->philo_id, str);
	pthread_mutex_unlock(plist->death);
	return (0);
}

int	sleepy(struct timeval og, t_philo_list *plist, int time, int f_switch)
{
	struct timeval	base;
	int				i;
	int				j;

	i = 1;
	gettimeofday(&base, 0);
	while (i)
	{
		if (to_late_for_dinner(og, plist, 0, f_switch))
			return (1);
		usleep(200);
		j = run_time(base);
		if (j >= time)
			i = 0;
	}
	return (0);
}

int	create_thread(t_philo_list *plist)
{
	int	i;
	int	n;

	i = 0;
	n = plist->time->n_philo;
	while (plist && i < n)
	{
		if (pthread_create(&plist->thread_id,
				0, philo_main, plist))
		{
			put_s("create error\n");
			return (1);
		}
		plist = plist->next;
		i++;
	}
	return (0);
}
