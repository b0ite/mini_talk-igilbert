FLAGS = -Wall -Wextra -Werror

all : server client

server : server.c
	gcc $(FLAGS) -o server server.c

client : client.c
	gcc $(FLAGS) -o client client.c

fclean : clean
	rm -f server.o client.o

clean :
	rm -f server client

re : clean all

.PHONY : all clean re fclean