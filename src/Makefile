CC := cc
SHELL := /bin/bash

ifdef SANIT
	DEBUG=1
endif
ifdef DEBUG
	CFLAGS += -g -Wall -Wextra
else
	CFLAGS := -g #Wall -Wextra -Werror
endif
ifdef SANIT
	CFLAGS += -fsanitize=address -MMD -MP
endif

FILE_COUNT := $(words $(SRC))

LOAD_BAR_SIZE := 30

OBJ = $(SRC:%.c=$(OUTPUT_DIR)/%.o)

file_processed = 0
current_file_processed = 0
size = 0

$(NAME): $(OUT_DIRS) $(OBJ)
ifndef DEBUG
	@/bin/echo -e "\e[?25l\e[3F" 
	@export frame=$$(($(file_processed) + 1));                                                                                                     \
	while [ $$(($$frame % 10 + 1 )) -ne 5 ];                                                                                                       \
		do                                                                                                                                         \
		frame=$$(( $$frame + 1 ));                                                                                                                 \
		/bin/echo -e "\e[13F";                                                                                                                     \
		export frames=$(BUILD_FRAMES); /bin/echo -e "\e[0m$${frames[$$(( $$frame / 3 % 10 ))]}";                                                   \
		sleep 0.05;                                                                                                                                \
	done

	@export frame=0;                                                                                                                               \
	while [ $$frame -le 6 ];                                                                                                                       \
		do                                                                                                                                         \
		/bin/echo -e "\e[13F";                                                                                                                     \
		export frames=$(END_BUILD_FRAMES); /bin/echo -e "\e[0m$${frames[$$frame]}";                                                                \
		frame=$$(( $$frame + 1 ));                                                                                                                 \
		sleep 0.05;                                                                                                                                \
	done
	@/bin/echo -e "\n\n"
endif

	@/bin/echo -e "\e[33m\e[2KLittle Totoro is linking your binary. Please wait...\e[0m"
	@$(CC) $(OBJ) $(CFLAGS) $(LDFLAGS) -o $@
	@/bin/echo -e "\e[92m\e[?25hDone!\e[0m"

$(OUT_DIRS):
	@/bin/echo -e "\e[33mLittle Totoro is seeding your build directories.\e[0m"
	@mkdir -p $(OUT_DIRS)

$(OUTPUT_DIR)/%.o: %.c | $(OUTPUT_DIR)/%.o_progress
ifndef DEBUG
	@if [ $(current_file_processed) -eq 0 ]; then echo -e "\n\n\n\n\n\n\n\n\n\n\n\n\n\n "; fi
	$(eval current_file_processed=1)
	@/bin/echo -e "\e[?25l\e[15F"
	@export frames=$(BUILD_FRAMES); /bin/echo -e "\e[0m$${frames[$(shell expr $(file_processed) / 3 % 10)]}"
	@/bin/echo -e "\e[33mCurrently growing: $@\e[0m\e[0K"

	@printf '[';
	$(eval size=$(shell expr $(file_processed) "*" $(LOAD_BAR_SIZE) / $(FILE_COUNT) ))
	@printf %$(size)s | tr " " "=";
	@printf "%$(shell expr $(LOAD_BAR_SIZE) - $(size))s";
	@printf "] $(shell expr $(size) "*" 100 / $(LOAD_BAR_SIZE))%%\n"
else
	@/bin/echo -e "\e[33mCurrently growing: $@\e[0m\e[0K"
endif
	@err=$$($(CC) $(CFLAGS) -I$(INCLUDES) -fdiagnostics-color -o $@ -c $< 2>&1);                                                                   \
	EXIT_CODE=$$?;                                                                                                                                 \
	if [ $$EXIT_CODE -ne 0 ]; then                                                                                                                 \
		/bin/echo -e "\e[?25h\x1b[31;1m\nGrowth failed! But we are not left with nothing! Here is what Little Totoro noticed:\n\x1b[0;22m";        \
		printf "$$err\n\n" 2>/dev/stderr;                                                                                                          \
		$$(exit $$EXIT_CODE);                                                                                                                      \
	elif [ -n "$$err" ]; then                                                                                                                      \
		/bin/echo -e "\e[?25h\x1b[35;1m\nOops! Something went wrong durring the growth! Let see what Totoro noticed:\n\x1b[0;22m";                 \
		printf "$$err\n\n" 2>/dev/stderr;                                                                                                          \
	fi

all: $(NAME)

clean:
	@echo -e "\e[33mCleaning output... Please wait for the Catbus...\e[0m"

ifndef DEBUG
	@export size=80;                                                                                                                               \
	for ((cam_x = 80 ; cam_x >= -80 ; cam_x--)); do                                                                                                \
		if [ $$(($$cam_x / 15 % 2)) -eq 0 ];                                                                                                       \
			then export frame="$(CLEAN_FRAME1)";                                                                                                   \
		else                                                                                                                                       \
			export frame="$(CLEAN_FRAME2)";                                                                                                        \
		fi;                                                                                                                                        \
		/bin/echo -e -n "$$frame" |                                                                                                                \
		while read line ;                                                                                                                          \
		do                                                                                                                                         \
			if [ $$cam_x -gt 0 ];                                                                                                                  \
				then printf "%$${cam_x}s";                                                                                                         \
			fi;                                                                                                                                    \
			if [ $$cam_x -lt 0 ]; then                                                                                                             \
				echo -e "$${line:$$(( 0 - $$cam_x )):$$(( $$size - $$cam_x ))}\e[0K";                                                              \
			else                                                                                                                                   \
				echo -e "$${line:0:$$(( $$size - $$cam_x ))}\e[0K";                                                                                \
			fi;                                                                                                                                    \
		done;                                                                                                                                      \
		/bin/echo -e "\e[?25l\e[14F";                                                                                                              \
		sleep 0.01;                                                                                                                                \
	done
endif
	@rm -rf $(OUTPUT_DIR)
	@echo -e "\e[32mCatbus cleaned the objects. Thank you Catbus!\e[0m"

fclean: clean
	@echo -e "\e[32mCatbus cleaned the binary too!\e[0m"
	@rm -f $(NAME)

re: fclean all

.PHONY: clean all re fclean

define PROGRESS_MACRO
$1_progress:
	$$(eval file_processed=$$(shell expr $$(file_processed) + 1))

endef

$(foreach obj, $(OBJ), $(eval $(call PROGRESS_MACRO, $(obj))))
