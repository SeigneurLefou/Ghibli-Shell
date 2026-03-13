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

file_processed = 0
current_file_processed = 0
size = 0

$(NAME): $(OUT_DIRS) $(OBJ)
	@/bin/echo -e "\e[33m\e[2KLinking binary\e[0m"
	@$(CC) $(OBJ) $(CFLAGS) $(LDFLAGS) -o $@
	@/bin/echo -e "\e[92m\e[?25hDone!"

$(OUT_DIRS):
	@echo Creating build directories
	@mkdir -p $(OUT_DIRS)

$(OUTPUT_DIR)/%.o: %.c | $(OUTPUT_DIR)/%.o_progress
	@if [ $(current_file_processed) -eq 0 ]; then echo -e "\n\n\n\n\n\n\n\n\n\n\n\n\n\n "; fi
	$(eval current_file_processed=1)
	@/bin/echo -e "\e[?25l\e[15F"
	@/bin/echo -e "\e[0m$(FRAME$(shell echo $(shell expr $(file_processed) / 3 % 10 + 1)))"
	@/bin/echo -e "\e[33mCurrently building: $@\e[0m\e[0K"

	@printf '[';
	$(eval size=$(shell expr $(file_processed) "*" $(LOAD_BAR_SIZE) / $(FILE_COUNT) ))
	@printf %$(size)s | tr " " "=";
	@printf "%$(shell expr $(LOAD_BAR_SIZE) - $(size))s";
	@printf "] $(shell expr $(size) "*" 100 / $(LOAD_BAR_SIZE))%%\n"
	@$(CC) $(CFLAGS) -I$(INCLUDES) -o $@ -c $< || (EXIT_CODE=$? && /bin/echo -e "\e[?25h" && $$(exit $(EXIT_CODE)))

all: $(NAME)

clean:
	@echo Cleaning output
	@rm -rf $(OUTPUT_DIR)

fclean: clean
	@echo Cleaning binary
	@rm -f $(NAME)

re: fclean all

.PHONY: clean all re fclean

define PROGRESS_MACRO
$1_progress:
	$$(eval file_processed=$$(shell expr $$(file_processed) + 1))

endef

$(foreach obj, $(OBJ), $(eval $(call PROGRESS_MACRO, $(obj))))
