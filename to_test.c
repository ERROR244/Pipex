#include "mylib/mylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int	main(void)
{
	int fd = open("file2", O_WRONLY | O_CREAT | O_TRUNC);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}

	char *ptr;
	ptr = get_next_line(0);
	while ((ptr = get_next_line(0)) != NULL)
	{
        printf("%s-%zu-", ptr, ft_strlen(ptr));
		ft_putstr_fd(ptr, fd);
		free(ptr);
	}
	printf("%s", ptr);
	close(fd);
}