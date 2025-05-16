NAME = Soup

CC		= c++
CFLAGS	= -Wall -Wextra -Werror -std=c++20 -MMD -g -fsanitize=address,undefined,leak
OBJDIR	= obj

SRC = main.cpp  Worker.cpp Soup.cpp

OBJ = $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRC))
DEP = $(patsubst %.cpp,$(OBJDIR)/%.d,$(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEP)