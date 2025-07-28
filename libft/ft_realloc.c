/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:32:02 by a-khairi          #+#    #+#             */
/*   Updated: 2025/07/23 23:13:14 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	void	*str;

	if (!ptr)
	{
		str = malloc(new_size);
		gr_t(str, 0);
		if (!str)
			return (NULL);
		return (str);
	}
	if (new_size == 0)
	{
		return (NULL);
	}
	new_ptr = malloc(new_size);
	gr_t(new_ptr, 0);
	if (!new_ptr)
		return (NULL);
	if (old_size > new_size)
		old_size = new_size;
	ft_memcpy(new_ptr, ptr, old_size);
	return (new_ptr);
}
