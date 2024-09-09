SRC_FILES = $(wildcard *.c) # TODO: no fer servir això
OBJ_FILES = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRC_FILES))
DEP_FILES = $(patsubst %.c,$(BUILD_DIR)/%.d,$(SRC_FILES))

HDR_FLAGS = -I $(LIBFT)
LIB_FLAGS = -rpath $(LIBFT) -L $(LIBFT) -lft
BUILD_DIR = build

NAME = philo
CFLAGS = -Wall -Wextra -Werror -g -MMD -fsanitize=address $(HDR_FLAGS) -pthread

CC = clang
LIBFT = $(CURDIR)/../libft

all: $(NAME)

libft:
	make -C $(LIBFT)

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ -c $< 

$(BUILD_DIR):
	mkdir -p $@

$(NAME): libft $(OBJ_FILES) 
	$(CC) $(CFLAGS) $(LIB_FLAGS) -o $(NAME) $(OBJ_FILES)

clean reclean:
	rm -rf $(BUILD_DIR)

deepclean: clean
	make -C $(LIBFT) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFT) fclean

re: fclean all reclean

-include $(DEP_FILES)

.PHONY: all clean fclean re libft
