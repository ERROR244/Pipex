name = pipex

SRC = main.c pipex_utils0.c pipex_utils1.c

OBS = ${SRC:.c=.o}

cc = gcc -fsanitize=address -g -O2
Mylib = ./Mylib/Mylib

all : $(name)

$(Mylib) :
	@make -C Mylib

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