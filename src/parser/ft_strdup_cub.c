/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_cub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller- <ekeller-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:26:50 by ekeller-          #+#    #+#             */
/*   Updated: 2025/10/13 11:27:01 by ekeller-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3d.h"

char	*ft_strdup_cub(const char *str)
{
	size_t	len;
	char	*copy;

	len = ft_strlen(str) + 1;
	copy = ft_malloc((len) * sizeof(char));
	if (copy == NULL)
		return (NULL);
	ft_strlcpy(copy, str, len);
	return (copy);
}