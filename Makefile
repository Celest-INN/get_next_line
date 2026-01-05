NAME = get_next_line.a

SRC = get_next_line.c get_next_line_utils.c

OBJ = ${SRC:.c=.o}

FLAG = -Wall -Wextra -Werror

RM = rm -f

all: ${NAME}

%.o: %.c
	cc ${FLAG} -c -o $@ $<

${NAME}: ${OBJ}
	ar rcs $(NAME) $(OBJ)

clean:
	${RM} ${OBJ}

fclean: clean
		${RM} ${NAME}

re: fclean all