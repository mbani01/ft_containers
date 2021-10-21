# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbani <mbani@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/20 11:19:43 by mbani             #+#    #+#              #
#    Updated: 2021/10/20 11:36:34 by mbani            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.cpp
NAME = ft
NAME1 = std
FLAG = -Wall -Wextra -Werror

all : $(NAME)

$(NAME): $(SRC)
	@clang++ -std=c++98 $(FLAG) $(SRC) -D NS=0 -o $(NAME1)
	@clang++ -std=c++98 $(FLAG) $(SRC) -D NS=1 -o $(NAME)
clean:
	@rm -rf $(NAME) $(NAME1)
fclean: clean
re : fclean all
.PHONY: all clean fclean re