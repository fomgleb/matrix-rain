NAME = matrix_rain

all: $(NAME) clean

$(NAME) inc/*.h src/*.c:
	clang -std=c11 -Wall -Wextra -Werror -Wpedantic -lncurses -g src/*.c -o $(NAME)

uninstall: clean
	rm -rf $(NAME)

clean:

reinstall: uninstall all

