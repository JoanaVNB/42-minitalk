FILESVR = server.c

FILECLT = client.c

CFLAGS = -Wall -Wextra -Werror

SFLAGS = -D_POSIX_C_SOURCE=199309L

NAMESVR = server

NAMECLT = client

MSG1 = @echo "Compiled ✔︎"
MSG2 = @echo "Cleaned ✔︎"

all: $(NAMESVR) $(NAMECLT)

$(NAMESVR): $(FILESVR)
	gcc $(CFLAGS) $(FILESVR) $(SFLAGS) -o $(NAMESVR)
	${MSG1}

$(NAMECLT): $(FILECLT)
	gcc $(CFLAGS) $(FILECLT) -o $(NAMECLT)
	${MSG1}
	
clean:
	rm $(NAMESVR) $(NAMECLT)

fclean: clean

run:
	./server

valgrind:
	valgrind --leak-check=full ./server

re: clean all
