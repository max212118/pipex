NAME =  pipex

DIR_LIBFT = libft

CC = gcc

CFLAGS = -Werror -Wextra -Wall -I./libft -g

SOURCES = pipex.c \
		  pipex_utils.c

OBJECTS = $(SOURCES:.c=.o)

all: makelibft $(NAME)

makelibft:
	@echo "Building libft..."
	$(MAKE) -C $(DIR_LIBFT)

$(NAME): $(OBJECTS)
	@echo "Building $(NAME)..."
	$(CC) $(OBJECTS) -L$(DIR_LIBFT) -lft -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(DIR_LIBFT) fclean

re:	fclean all
