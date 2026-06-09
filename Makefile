NAME = libftprintf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIE

SRCS = ft_printf.c handle_format.c print_char.c print_str.c \
	 print_int.c print_uint.c print_hex.c print_ptr.c \
	 parse_flags.c print_utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
	@echo "################ Hai compilato printf, daje! ################"

clean:
	rm -f $(OBJS)
	@echo "################ Pulito quaaaasi tutto! Olé! ################"
fclean: clean
	rm -f $(NAME)
	@echo "################ Pulito tutto, meglio de AMA ################"
re: fclean all
	@echo "################ Prima pulito, poi rifatto!  ################"
	
bonus: all

.PHONY: all clean fclean re bonus
