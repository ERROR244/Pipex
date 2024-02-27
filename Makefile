name = pipex
bonus = pipex_bonus

SRC = 	main.c pipex_utils0.c wrapper_functions.c libft/ft_isalpha.c libft/ft_split.c libft/ft_putstr_fd.c\
		libft/ft_strjoin.c libft/ft_strjoin1.c libft/ft_strdup.c libft/ft_strlen.c\
		libft/ft_putchar_fd.c libft/get_next_line_utils.c libft/ft_strnstr.c\
		libft/get_next_line.c libft/ft_toupper.c libft/ft_strncmp.c\
		libft/ft_printf.c\
		libft/print_ch.c\
		libft/print_i_d.c\
		libft/print_p.c\
		libft/print_str.c\
		libft/print_u.c\
		libft/ft_itoa.c\
		libft/print_x.c


SRCB = 	Bonus/main_bonus.c Bonus/pipex_utils0_bonus.c Bonus/pipex_utils1_bonus.c Bonus/pipex_utils2_bonus.c Bonus/wrapper_functions_bonus.c libft/ft_isalpha.c libft/ft_split.c\
		libft/ft_putstr_fd.c libft/ft_strjoin.c libft/ft_strjoin1.c libft/ft_strdup.c libft/ft_strlen.c libft/ft_strncmp.c\
		libft/ft_putchar_fd.c libft/get_next_line_utils.c libft/ft_strnstr.c\
		libft/get_next_line.c libft/ft_toupper.c\
		libft/ft_printf.c\
		libft/print_ch.c\
		libft/print_i_d.c\
		libft/print_p.c\
		libft/print_str.c\
		libft/print_u.c\
		libft/ft_itoa.c\
		libft/print_x.c



OBS = ${SRC:.c=.o}
OBSB = ${SRCB:.c=.o}

CC = cc #-fsanitize=address
CFLAGS = -Wall -Wextra -Werror

all : $(bonus) #$(name)

$(name) : $(OBS)
	touch in
	touch out
	${CC} $(CFLAGS) ${OBS} -o ${name}

bonus	:	$(bonus)

$(bonus)	:	$(OBSB)
	touch in
	touch out
	${CC} $(CFLAGS) ${OBSB} -o ${bonus}

%.o:	%.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean :
	@rm -f $(OBS)
	@rm -f $(OBSB)

fclean: clean
	@rm -f $(name)
	rm -f out
	rm -f in
	@rm -f $(bonus)

re : fclean all
reb : fclean bonus

.SECONDARY : ${OBS} ${OBSB}
.PHONY: all clean fclean re