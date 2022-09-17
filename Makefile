# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arguilla <arguilla@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/13 19:04:24 by spoliart          #+#    #+#              #
#    Updated: 2022/05/07 14:06:59 by spoliart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# [ VARIABLES ] #

NAME	=	test
RM		=	/bin/rm -rf
MAKE	=	make

# [ COLORS ] #

_END	=	\e[0m
_RED	=	\e[31m
_GREEN	=	\e[32m
_YELLOW	=	\e[33m

# [ COMPILATION VARIABLES ]#

CXX		=	c++
CXXFLAGS=	-Wall -Wextra -Werror --std=c++98 -g

# [ VALGRIND VARIABLES ] #

VALGRIND	=	/usr/bin/valgrind
VFLAGS		=	--leak-check=full --show-leak-kinds=all --track-origins=yes

# [ DIRECTORIES ] #

O		=	objs/
I		=	-Icontainers

# [ SOURCES ] #

SRCS	=	main.cpp

# [ OBJECTS ] #

OBJS	=	$(SRCS:%.cpp=$O%.o)

# [ PATH ] #

VPATH	=	containers

# [ RULES ] #

all:		$(NAME)

$(NAME):	$(OBJS)
			@printf "\033[2K\r$(_GREEN) All files compiled into '$O'. $(_END)✅\n"
			@$(CXX) $(CXXFLAGS) $^ -o $@
			@printf "$(_GREEN) Binary '$(NAME)' created. $(_END)✅\n"

$O:
			@mkdir -p $@

$O%.o:		%.cpp	| $O
			@printf "\033[2K\r $(_YELLOW)Compiling $< $(_END)⌛"
			@$(CXX) $(CXXFLAGS) $I -c $< -o $@

clean:
			@$(RM) $O
			@printf "$(_RED) '$O' has been deleted. $(_END)🗑️\n"

fclean:		clean
			@$(RM) $(LOG) $(BIN) $(NAME)
			@printf "$(_RED) '$(LOG)', '$(BIN)' and '$(NAME)' has been deleted. $(_END)🗑️\n"

re:			fclean all

valgrind: 	all
			@$(VALGRIND) $(VFLAGS) ./$(NAME)

# [ DEBUG ] #

LOG = log/
BIN = bin/
FT_NAME = ft_containers
STD_NAME = std_containers

debug:
			@mkdir -p $(BIN)
			@$(CC) $(CFLAGS) -DNO_DISPLAY_ADDRESS -DSTD main.cpp -o $(BIN)$(STD_NAME)
			@$(CC) $(CFLAGS) -DNO_DISPLAY_ADDRESS main.cpp -o $(BIN)$(FT_NAME)
			@printf "$(_GREEN) '$(FT_NAME)' and '$(STD_NAME)' created into '$(BIN)'. $(_END)✅\n"
			@mkdir -p $(LOG)
			@$(BIN)$(STD_NAME) > $(LOG)$(STD_NAME).log
			@$(BIN)$(FT_NAME) > $(LOG)$(FT_NAME).log
			@echo
			@diff --color $(LOG)$(STD_NAME).log $(LOG)$(FT_NAME).log 2>&1 | tee $(LOG)diff.log
			@if [ -s $(LOG)diff.log ]; then\
				printf "\n$(_RED) Diff found, log file in log dir. $(_END)❌\n";\
			else\
				printf "$(_GREEN) Tests passed. (log file in log dir) $(_END)✅\n";\
			fi

# [ PHONY ] #

.PHONY:	all clean fclean re valgrind debug
