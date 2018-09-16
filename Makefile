
SRC_PATH = src/

OTOOL_SRC_NAME = 	otool.c \
					exit.c \
					header.c \
					section.c \
					print_text_section.c \
					utils.c \

NM_SRC_NAME = nm.c \
				exit.c \

OBJ_PATH = .obj/

CPPFLAGS = -Iincludes -I ./libft/includes

LDFLAGS = -Llibft

LDLIBS = -lft

NM = ft_nm

OTOOL = ft_otool

CC = gcc

CFLAGS = -Wall -Wextra

NM_OBJ_NAME = $(NM_SRC_NAME:.c=.o)
OTOOL_OBJ_NAME = $(OTOOL_SRC_NAME:.c=.o)

NM_SRC = $(addprefix $(SRC_PATH), $(NM_SRC_NAME))
NM_OBJ = $(addprefix $(OBJ_PATH), $(NM_OBJ_NAME))

OTOOL_SRC = $(addprefix $(SRC_PATH), $(OTOOL_SRC_NAME))
OTOOL_OBJ = $(addprefix $(OBJ_PATH), $(OTOOL_OBJ_NAME))

.PHONY: all, clean, fclean, re

all: $(NM) $(OTOOL)

$(NM): $(NM_OBJ)
	make -C ./libft/
	$(CC) $^ -o $(NM) $(LDFLAGS) $(LDLIBS)

$(OTOOL): $(OTOOL_OBJ)
	make -C ./libft/
	$(CC) $^ -o $(OTOOL) $(LDFLAGS) $(LDLIBS)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) $(SRC_PATH) 2> /dev/null || true
	$(CC) -o $@  $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	rm -f $(NM_OBJ) $(OTOOL_OBJ)
	make clean -C ./libft/
	@rmdir $(OBJ_PATH) $(SRC_PATH) 2> /dev/null || true

fclean: clean
	make fclean -C ./libft/
	rm -f $(NM) $(OTOOL)

re: fclean all