name = pipex

SRC = main.c mylib/ft_split.c mylib/ft_strjoin.c mylib/ft_strdup.c mylib/ft_strnstr.c mylib/ft_strlen.c mylib/ft_printf.c mylib/print_ch.c mylib/print_i_d.c mylib/print_p.c mylib/print_str.c mylib/print_u.c mylib/print_x.c


OBS = ${SRC:.c=.o}

cc = cc #-fsanitize=address -g -O2
Mylib = ./Mylib/Mylib

all : $(name)

$(Mylib) :
	@Make -C Mylib

$(name) : $(Mylib) $(OBS)
	${cc} $(Mylib) ${OBS} -o ${name}

%.o:	%.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean :
	@rm -f $(OBS)
	@make clean -C Mylib

fclean: clean
	@rm -f $(name)
	@make fclean -C Mylib

re : fclean all

.SECONDARY : ${OBS}
.PHONY: all clean fclean re