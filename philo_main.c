/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_main.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/15 14:54:36 by jbax          #+#    #+#                 */
/*   Updated: 2022/12/12 15:13:03 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_all.h"

void	*philo_main(void *list)
{
	t_philo_list	*plist;
	struct timeval	ogtime;
	int				i;

	plist = (t_philo_list *)list;
	gettimeofday(&ogtime, 0);
	plist->ogtime = ogtime;
	i = 1;
	plist->last_meal = run_time(ogtime);
	if (!(plist->philo_id % 2))
		usleep(100);
	while (i != plist->time->x_eat + 1 && i)
	{
		pthread_mutex_lock(plist->fork_right);
		pthread_mutex_lock(plist->fork_left);
		if (to_late_for_dinner(ogtime, plist, "has taken a fork\n", 1))
			return (0);
		if (to_late_for_dinner(ogtime, plist, "has taken a fork\n", 1))
			return (0);
		if (to_late_for_dinner(ogtime, plist, "is eating\n", 1))
			return (0);
		plist->last_meal = run_time(ogtime);
		if (sleepy(ogtime, plist, plist->time->t_eat, 1))
			return (0);
		i++;
		pthread_mutex_unlock(plist->fork_right);
		pthread_mutex_unlock(plist->fork_left);
		if (to_late_for_dinner(ogtime, plist, "is sleeping\n", 0))
			return (0);
		if (sleepy(ogtime, plist, plist->time->t_sleep, 0))
			return (0);
		if (to_late_for_dinner(ogtime, plist, "is thinking\n", 0))
			return (0);
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

// void	leaks(void)
// {
// 	system("leaks -q philo");
// }
	// atexit(&leaks);

int	main(int argc, char **argv)
{
	t_philo_time	ph;
	t_philo_list	*plist;
	int				i;
	int				j;

	if (check_args(argc))
		return (0);
	time_new(argc, argv, &ph);
	i = 0;
	j = 0;
	plist = 0;
	while (i < ph.n_philo)
	{
		i++;
		philo_addback(&plist, philo_new(&ph, i, &j));
	}
	if (create_thread(plist))
		return (0);
	i = 1;
	while (i < ph.n_philo)
	{
		pthread_join(plist->thread_id, 0);
		if (plist->next)
			plist = plist->next;
		i++;
	}
	i = 0;
	while (plist->back)
		plist = plist->back;
	while (plist)
		philo_del(&plist);
	return (0);
}
