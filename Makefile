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

CFLAGS = -g -Wall -Wextra -Werror -Iheaders/ 

LIBFT = libft/libft.a

LIB = mlx/libmlx_Linux.a -lX11 -lXext -lm

MLX = mlx/

FLAG = -lXext -lX11 -lm -lz

SRC = main.c \
		rt/color_opers.c rt/input.c rt/rft_init_scene.c \
		rt/image_creat.c rt/palle.c rt/utils.c \
		parsing/read_rt.c \
		parsing/check_rt.c \
		parsing/parsing.c \
		parsing/init.c \
		parsing/init_help.c \
		parsing/parse_utils.c \
		parsing/parse_data.c \
		parsing/parse_obj.c \
rt/stuff_printer.c \
vectors/miscellaneous_2.c \
vectors/miscellaneous.c \
vectors/vector3_ops_2.c \
vectors/vector3_ops.c \
vectors/vectors_new.c

OBJ = $(SRC:.c=.o)

debug: $(OBJ)
	@echo "⌛ compiling...⌛"
	$(CC) $(CFLAGS) $(OBJ) $(LIB) $(LIBFT) -o $(NAME)
	@echo "🎉 mini_rt compiled! 🎉"
	@rm -f $(OBJ)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "⌛ compiling...⌛"
	$(MAKE) -s -C libft/
	$(MAKE) -s -C $(MLX)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) $(LIBFT) -o $(NAME)
	@echo "🎉 mini_rt compiled! 🎉"
	@rm -f $(OBJ)


	
clean:	
	@echo "🧽 cleaning... 🧽"
	@rm -f $(OBJ)
	@make clean -s -C libft/


fclean: clean
	@echo "🚮♻️ spring cleaning, rm $(NAME)... ♻️ 🚮" 
	rm -rf $(NAME)

re: fclean all

.SILENT:

