# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/23 14:03:03 by alberrod          #+#    #+#              #
#    Updated: 2023/12/23 14:03:08 by alberrod         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC       = cc
HEADERS_DIR = .
CFLAGS   = -Wall -Wextra -Werror -I $(HEADERS_DIR)
NAME     = libftprintf.a
RM       = rm -rf

CFILES = get_next_line.c get_next_line_utils.c

OFILES = $(CFILES:.c=.o)

all: $(NAME)

$(NAME): $(OFILES)
	ar rcs $(NAME) $(OFILES)

clean:
	$(RM) $(OFILES)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

# test: 
# 	cc -Wall -Wextra -Werror -fsanitize=address test_ft_printf.c libftprintf.a -g && ./a.out

.PHONY: all clean fclean re
 
