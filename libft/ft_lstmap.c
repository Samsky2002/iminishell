/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakerkao <oakerkao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 17:03:53 by oakerkao          #+#    #+#             */
/*   Updated: 2023/09/02 09:59:14 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*p;
	t_list	*l;

	if (!lst)
		return (NULL);
	l = NULL;
	while (lst)
	{
		p = ft_lstnew(f(lst->content));
		ft_lstadd_back(&l, p);
		if (!(p->content))
		{
			ft_lstclear(&l, del);
		}
		lst = lst->next;
	}
	return (l);
}
