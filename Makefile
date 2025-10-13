#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekeller- <ekeller-@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/24 18:23:17 by acesar-m          #+#    #+#              #
#    Updated: 2025/10/13 12:48:33 by ekeller-         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		= cub3D

CC			= cc
CFLAGS		= -I include -I $(MLX_DIR) -I $(LIBFT_DIR) -g -Wall -Wextra -Werror 

SRC_DIR		= src
OBJ_DIR		= obj

SRC			= 	main.c \
				init.c \
				hooks.c \
				move.c \
				dda.c \
				render.c \
				texture.c \
				draw_background.c \
				minimap.c \
				error/error.c \
				gc/gc.c \
				parser/parser.c \
				parser/parse_config.c \
				parser/parse_map.c \
				parser/ft_strdup_cub.c \
				texture_helper.c

SRCS		= $(addprefix $(SRC_DIR)/, $(SRC))
OBJS		= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

LIBFT_DIR	= include/libft
LIBFT		= $(LIBFT_DIR)/libft.a

MLX_DIR		= minilibx
MLX			= $(MLX_DIR)/libmlx.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lm -lXext -lX11

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@$(MAKE) -C $(MLX_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus