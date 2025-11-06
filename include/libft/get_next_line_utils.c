/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:22:48 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/11/06 17:26:19 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_line(char *stored, char *buf)
{
	char	*temp;

	if (stored == NULL)
		stored = ft_strjoin("", buf);
	else
	{
		temp = stored;
		stored = ft_strjoin(stored, buf);
		free(temp);
	}
	return (stored);
}
