NAME =  pipex

DIR_LIBFT = libft

CC = gcc

CFLAGS = -I./libft -g

SOURCES = pipex.c \
		  pipex_utils.c \
		  pipex_cleaning.c \
		  pipex_execution.c \

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	@make -C $(DIR_LIBFT)
	@echo "Building $(NAME)..."
	@$(CC) $(OBJECTS) -L$(DIR_LIBFT) -lft -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(DIR_LIBFT) fclean

re:	fclean all

# Cible pour tester le temps d'exécution de pipex
test_time:
	@echo "Démarrage du test..."
	@t1=$$(date +%s); \
	./pipex Makefile "sleep 2" "sleep 1" outf 2>/dev/null; \
	code=$$?; \
	t2=$$(date +%s); \
	echo "Code de sortie: $$code"; \
	echo "Temps d'exécution: $$((t2 - t1)) secondes"
