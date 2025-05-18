# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -g -Wall -Wextra -Werror -Iinclude

# Arquivos fonte
SRCS = src/main.c \
       src/familyTree.c \
       src/input.c \
       src/ui_utils.c \
       src/main_menu_screen.c \
       src/tree_manager_screen.c

# Arquivos objeto (gerados automaticamente)
OBJS = $(SRCS:.c=.o)

# Nome do executável
TARGET = ftree

# Regra principal
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Regra genérica para compilar .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza
.PHONY: clean
clean:
	rm -fv $(OBJS) $(TARGET)

# Para Windows (se estiver usando cmd/PowerShell)
.PHONY: clean-win
clean-win:
	del /f /q $(subst /,\,$(OBJS)) $(TARGET).exe