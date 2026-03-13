# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lchamard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/12 08:35:55 by lchamard          #+#    #+#              #
#    Updated: 2026/03/12 08:35:57 by lchamard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS = pipex_bonus
CC = cc
BUILD = build/
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -Iincludes

# DIRECTORY
DS = src/
STR = $(DS)libft/str_utils/
CONV = $(DS)libft/conv_utils/
MEM = $(DS)libft/mem_utils/
COMP = $(DS)libft/comp_utils/
PUT = $(DS)libft/put_utils/
LST = $(DS)libft/lst_utils/
BUILD = build/
PF = $(DS)printf/
GNL = $(DS)gnl/
CMD = $(DS)pipex/cmd_utils/
PIP = $(DS)pipex/

SRC = $(COMP)ft_isascii.c\
	$(COMP)ft_isdigit.c\
	$(COMP)ft_isalpha.c\
	$(COMP)ft_isprint.c\
	$(COMP)ft_isalnum.c\
	$(COMP)ft_isvalid.c\
	$(COMP)ft_isdouble.c\
	$(CONV)ft_toupper.c\
	$(CONV)ft_tolower.c\
	$(CONV)ft_atoi.c\
	$(CONV)ft_antoi.c\
	$(CONV)ft_itoa.c\
	$(CONV)ft_atol.c\
	$(CONV)ft_antol.c\
	$(MEM)ft_memcpy.c\
	$(MEM)ft_memmove.c\
	$(MEM)ft_memchr.c\
	$(MEM)ft_double_free.c\
	$(MEM)ft_bzero.c\
	$(MEM)ft_memcmp.c\
	$(MEM)ft_memset.c\
	$(MEM)ft_calloc.c\
	$(MEM)ft_setalloc.c\
	$(PUT)ft_putchar_fd.c\
	$(PUT)ft_putstr_fd.c\
	$(PUT)ft_putstrstr_fd.c\
	$(PUT)ft_putendl_fd.c\
	$(PUT)ft_putnbr_fd.c\
	$(PUT)ft_putnbr_endl.c\
	$(PUT)ft_putvoids_fd.c\
	$(PUT)ft_putunsigned_nbr_fd.c\
	$(PUT)ft_putnbrbase_fd.c\
	$(STR)ft_strnstr.c\
	$(STR)ft_strlen.c\
	$(STR)ft_strdup.c\
	$(STR)ft_strncmp.c\
	$(STR)ft_strcmp.c\
	$(STR)ft_strrchr.c\
	$(STR)ft_substr.c\
	$(STR)ft_strjoin.c\
	$(STR)ft_strnjoin.c\
	$(STR)ft_sstrjoin.c\
	$(STR)ft_strmapi.c\
	$(STR)ft_striteri.c\
	$(STR)ft_strtrim.c\
	$(STR)ft_strlcpy.c\
	$(STR)ft_strcpy.c\
	$(STR)ft_strchr.c\
	$(STR)ft_strichr.c\
	$(STR)ft_strlcat.c\
	$(STR)ft_strcat.c\
	$(STR)ft_split.c\
	$(LST)ft_lstadd_back.c\
	$(LST)ft_lstadd_front.c\
	$(LST)ft_lstlast.c\
	$(LST)ft_lstsize.c\
	$(LST)ft_lstnew.c\
	$(LST)ft_lstdelone.c\
	$(LST)ft_lstiter.c\
	$(LST)ft_lstclear.c\
	$(LST)ft_lstmap.c\
	$(LST)ft_lstshow.c\
	$(LST)ft_lstfind.c\
	$(LST)ft_lstisdouble.c\
	$(PF)ft_printf.c\
	$(GNL)get_next_line.c\
	$(CMD)ft_cmdadd_back.c\
	$(CMD)ft_cmdadd_front.c\
	$(CMD)ft_cmdlast.c\
	$(CMD)ft_cmdfirst.c\
	$(CMD)ft_cmdsize.c\
	$(CMD)ft_cmdnew.c\
	$(CMD)ft_cmdclear.c\
	$(CMD)ft_cmdshow.c\
	$(PIP)exec_cmd.c\
	$(PIP)execution_loop.c\
	$(PIP)exit_processus.c\
	$(PIP)here_doc.c\
	$(PIP)initialiser.c

OBJ = $(SRC:%.c=$(BUILD)%.o)

$(NAME) : $(OBJ) $(DS)main.c
	@$(CC) $(CFLAGS) $(INCLUDES) $(DS)main.c $(OBJ) -o $(NAME)
	@echo -e "BINARY : $(NAME)"

$(BONUS) : $(OBJ) $(DS)main_bonus.c
	@$(CC) $(CFLAGS) $(INCLUDES) $(DS)main_bonus.c $(OBJ) -o $(BONUS)
	@echo -e "BINARY : $(BONUS)"

$(BUILD)%.o : %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo -e "CC $<\n\t> $@"

all : $(NAME) 

bonus : $(BONUS)

re : fclean all bonus

clean :
	@rm -Rf $(BUILD)
	@rm -Rf libft/$(BUILD)
	@echo -e "DELETE : $(BUILD)"

fclean : clean
	@rm -f $(NAME)
	@echo -e "DELETE : $(NAME)"
	@rm -f $(BONUS)
	@echo -e "DELETE : $(BONUS)"

.PHONY: all bonus clean fclean re
