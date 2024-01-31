name = pipex

SRC = main.c
OBS = ${SRC:.c=.o}

cc = cc

all : $(name)

$(name) : $(OBS)
	@${cc} ${OBS} -o ${name}

%.o:	%.c
	@$(CC) $(CFLAGS) -c $^ -o $@

clean :
	@rm -f $(OBS)

fclean: clean
	@rm -f $(name)

re : fclean all

.SECONDARY : ${OBS}
.PHONY: all clean fclean re