NAME        = libasm.a

SRC         = ft_strlen.s ft_strcpy.s ft_strcmp.s ft_write.s ft_read.s ft_strdup.s
SRC_BONUS   = ft_list_push_front.s ft_list_size.s ft_list_sort.s ft_list_remove_if.s ft_list_new.s
SRC_UTF32   = ft_atoi_base_utf32.s ft_base_strlen_check.s ft_find_char_index.s ft_is_base_dups.s

OBJ_DIR     = obj

OBJ         = $(addprefix $(OBJ_DIR)/srcs/, $(SRC:.s=.o))
OBJ_BONUS   = $(addprefix $(OBJ_DIR)/srcs_bonus/, $(SRC_BONUS:.s=.o))
OBJ_UTF32   = $(addprefix $(OBJ_DIR)/srcs_bonus/atoi_base_utf32/, $(SRC_UTF32:.s=.o))

NASM        = nasm
FLAGS       = -f elf64
FLAGS_BONUS = -f elf64 -i srcs_bonus/
FLAGS_UTF32 = -f elf64 -i srcs_bonus/ -i srcs_bonus/atoi_base_utf32/

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

bonus: $(OBJ) $(OBJ_BONUS) $(OBJ_UTF32)
	ar rcs $(NAME) $(OBJ) $(OBJ_BONUS) $(OBJ_UTF32)

$(OBJ_DIR)/srcs/%.o: srcs/%.s
	mkdir -p $(OBJ_DIR)/srcs
	$(NASM) $(FLAGS) $< -o $@

$(OBJ_DIR)/srcs_bonus/%.o: srcs_bonus/%.s
	mkdir -p $(OBJ_DIR)/srcs_bonus
	$(NASM) $(FLAGS_BONUS) $< -o $@

$(OBJ_DIR)/srcs_bonus/atoi_base_utf32/%.o: srcs_bonus/atoi_base_utf32/%.s
	mkdir -p $(OBJ_DIR)/srcs_bonus/atoi_base_utf32
	$(NASM) $(FLAGS_UTF32) $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f to_read.txt

re: fclean all

.PHONY: all clean fclean re bonus