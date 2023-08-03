# \ = is used to Splitting Long Lines 3.1.1

# ;\ = indicates a multiline command and keeps the instance of the terminal for
# the next command

# % = the same as * 'wildcard'
# $@ = means what is before the : in the target
# $^ = means what is after the : in the target
# $< = the first prerequisite (usually a source file)
# -I.  = adds include directory of header files.
# -f = force the removal even if the files have been already deleted.

# -c = Compile or assemble the source files, but do not link.
# cp = copy.
# The linking stage simply is not done. The ultimate output is
# in the form of an object file for each source file.
# By default, the object file name for a source file is made by replacing
# the suffix .c, .i, .s, etc., with .o. Unrecognized input files,
# not requiring compilation or assembly, are ignored.
# -s = silent
# @echo = stampa quello che viene dopo

NAME = mini_rt

CC = gcc 

CFLAGS = -Wall -Wextra -Werror -pthread -Iheaders/

LIBFT = libft/libft.a

LIB = mlx/libmlx_Linux.a -lX11 -lXext -lm

MLX = mlx/

INCLUDE = include/

FLAG =  -lXext -lX11 -lm -lz

SRC = 	main.c \
		rt/color_opers.c rt/input.c rt/rft_init_scene.c \
		rt/vectors.c rt/image_creat.c rt/lol.c rt/palle.c rt/utils.c


OBJ = $(SRC:.c=.o)

SCENE = ./scene/mandatory.rt

all: $(NAME)

$(NAME): $(OBJ)
	@echo "⌛ compiling...⌛"
	$(MAKE) -s -C libft/
	$(MAKE) -s -C $(MLX)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) $(LIBFT) -o $(NAME)
	@echo "🎉 mini_rt compiled! 🎉"

clean:	
	@echo "🧽 cleaning... 🧽"
	@rm -f $(OBJ) $(OBJ_BONUS)
	@make clean -s -C libft/


fclean: clean
	@echo "🚮♻️ spring cleaning, rm $(NAME)... ♻️ 🚮" 
	make clean -C $(MLX)
	rm -rf $(NAME)

re: fclean all

run:
	./$(NAME) $(SCENE)

valgrind:
	valgrind --leak-check=full ./$(NAME)

.SILENT:
