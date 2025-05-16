NAME = Soup

CC		= c++
CFLAGS	= -Wall -Wextra -Werror -std=c++20 -MMD -g -fsanitize=address,undefined,leak
OBJDIR	= obj
SRCDIR	= src
INCLUDE	= -Iinclude

SRC		= main.cpp Worker.cpp Soup.cpp

SRCS	= $(addprefix $(SRCDIR)/, $(SRC))
OBJ		= $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))
DEP		= $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.d,$(SRCS))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEP)