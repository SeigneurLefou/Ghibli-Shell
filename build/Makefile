CC := cc
SHELL := /bin/bash

ifdef DEBUG
	CFLAGS += -g 
else
	CFLAGS := -Wall -Wextra -Werror
endif

FILE_COUNT := $(words $(SRC))

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
	@$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDES) || (EXIT_CODE=$$? && /bin/echo -e "\e[?25h" && $$(exit $$EXIT_CODE))
	@printf '\e[2F'

anim: padding
	@/bin/echo -e -n "\e[?25l\e[0m\e[11F$(FRAME1)"
	@sleep 0.3
	@/bin/echo -e -n "\e[0m\e[11F$(FRAME2)"
	@sleep 0.3
	@/bin/echo -e -n "\e[0m\e[11F$(FRAME3)"
	@sleep 0.3
	@/bin/echo -e -n "\e[0m\e[11F$(FRAME4)"
	@sleep 0.3
	@/bin/echo -e -n "\e[0m\e[11F$(FRAME5)"
	@sleep 0.3
	@/bin/echo -e -n "\e[0m\e[11F$(FRAME6)"
	@sleep 0.3
	@/bin/echo -e -n "\e[0m\e[11F$(FRAME7)"
	@sleep 0.3
	@/bin/echo -e -n "\e[0m\e[11F$(FRAME8)"
	@sleep 0.3
	@/bin/echo -e -n "\e[0m\e[11F$(FRAME9)"
	@sleep 0.3
	@/bin/echo -e "\e[0m\e[11F$(FRAME10)\e[?25h"

all: padding $(NAME)

padding:
	@/bin/echo -e "\n\n\n\n\n\n\n\n\n\n "

clean:
	@echo Cleaning output
	@rm -rf $(OUTPUT_DIR)

fclean: clean
	@echo Cleaning binary
	@rm -f $(NAME)

re: fclean all

.PHONY: clean all re fclean
