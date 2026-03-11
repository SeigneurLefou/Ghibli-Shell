CC := cc
SHELL := /bin/bash

ifdef DEBUG
	CFLAGS += -g 
else
	CFLAGS := -Wall -Wextra -Werror
endif

FILE_COUNT := $(shell printf '%s' '$(subst ','"'"',$(SRC))' | wc -w)

LOAD_BAR_SIZE := 30

OBJ = $(SRC:%.c=$(OUTPUT_DIR)/%.o)

$(NAME): $(OUT_DIRS) $(OBJ)
	@/bin/echo -e "\n\n\e[33m\e[2KLinking binary\e[0m"
	@$(CC) $(OBJ) $(CFLAGS) $(LDFLAGS) -o $@
	@/bin/echo -e "\e[92m\e[?25hDone!"

$(OUT_DIRS):
	@echo Creating build directories
	@mkdir -p $(OUT_DIRS)

$(OUTPUT_DIR)/%.o: %.c
	@/bin/echo -e "\e[?25l\e[33mCurrently building: $@\e[0m\e[0K"
	$(eval file_processed=$(shell echo $$(($(file_processed)+1))))
	@printf '['; \
	SIZE=$$(( $(file_processed) * $(LOAD_BAR_SIZE) / $(FILE_COUNT) )); \
	printf %$$((SIZE))s | tr " " "="; \
	printf %$$(($(LOAD_BAR_SIZE) - SIZE))s | tr " " " "; \
	printf "] $$((SIZE * 100 / $(LOAD_BAR_SIZE)))%%\n"
	@$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDES)
	@printf '\e[2F'

all: $(NAME)

clean:
	@echo Cleaning output
	@rm -rf $(OUTPUT_DIR)

fclean: clean
	@echo Cleaning binary
	@rm -f $(NAME)

re: fclean all

.PHONY: clean all re fclean
