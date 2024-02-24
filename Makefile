name = pipex

SRC = 	main.c pipex_utils0.c pipex_utils1.c pipex_utils2.c libft/ft_isalpha.c libft/ft_split.c libft/ft_putstr_fd.c\
		libft/ft_strjoin.c libft/ft_strjoin1.c libft/ft_strdup.c libft/ft_strlen.c libft/ft_strncmp.c\
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

CC = cc -fsanitize=address -g -O2
CFLAGS = -Wall -Wextra -Werror

all : $(name)

$(name) : $(OBS)
	${CC} $(CFLAGS) ${OBS} -o ${name}

%.o:	%.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean :
	rm -f $(OBS)

fclean: clean
	rm -f $(name)

re : fclean all

.SECONDARY : ${OBS}
.PHONY: all clean fclean re