SRC_FILES = main.c philosopher.c timeutils.c utils.c workers.c
OBJ_FILES = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRC_FILES))
DEP_FILES = $(patsubst %.c,$(BUILD_DIR)/%.d,$(SRC_FILES))

HDR_FLAGS = -I $(LIBFT)
LIB_FLAGS = -rpath $(LIBFT) -L $(LIBFT) -lft
BUILD_DIR = build

NAME = philo
CFLAGS = -Wall -Wextra -g -MMD $(HDR_FLAGS)

CC = clang
LIBFT = $(CURDIR)/../libft

all: $(NAME)

$(LIBFT)/libft.so: libft

libft:
	make -C $(LIBFT)

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ -c $< 

$(BUILD_DIR):
	mkdir -p $@

$(NAME): $(LIBFT)/libft.so $(OBJ_FILES)
	$(CC) $(CFLAGS) $(LIB_FLAGS) -o $(NAME) $(OBJ_FILES)

fsu: CFLAGS += -fsanitize=undefined
fsu: re

fst: CFLAGS += -fsanitize=thread
fst: re

clean reclean:
	rm -rf $(BUILD_DIR)

deepclean: clean
	make -C $(LIBFT) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFT) fclean

re: fclean all reclean

-include $(DEP_FILES)

.PHONY: all clean fclean re libft nofs deepclean
