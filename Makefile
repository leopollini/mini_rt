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

NAME		= mini_rt

CC			= gcc 

CFLAGS		= -pthread -Iheaders/ # -Wall -Wextra -Werror

LIB			= mlx/libmlx_Linux.a -lX11 -lXext -lm libft/libft.a

MLX			= mlx/

INCLUDE		= include/

FLAG		=  -lXext -lX11 -lm -lz

FLAG =  -lXext -lX11 -lm -lz

SRC = 	main.c \
		rt/color_opers.c rt/input.c rt/rft_init_scene.c \
		rt/vectors.c rt/image_creat.c rt/lol.c rt/palle.c rt/utils.c


OBJ = $(SRC:.c=.o)

SCENE = ./scene/mandatory.rt

all: $(NAME)

$(NAME): $(OBJ)
	@echo "⌛ compiling...⌛"
	make -s -C libft/
	make -s -C $(MLX)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(NAME)
	@echo "🎉 mini_rt compiled! 🎉"
	rm -f $(OBJ)

bonus: all

debug: $(OBJ)
	@echo "⌛ compiling...⌛"
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(NAME)
	@echo "🎉 mini_rt compiled! 🎉"
	rm -f $(OBJ)

clean:	
	@echo "🧽 cleaning... 🧽"
	@rm -f $(OBJ) $(OBJ_BONUS)
	@make fclean -s -C libft/


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
