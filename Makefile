NAME = minishell

OUTPUT_DIR = output

SRC_DIR = src

OUT_DIRS := $(OUTPUT_DIR)/src

SRC = src/main.c

LDFLAGS := -lreadline

INCLUDES = list,include,libft

include libft/Makefile
include list/Makefile
include vec/Makefile

include build/Makefile
