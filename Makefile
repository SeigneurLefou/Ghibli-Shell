NAME = minishell

OUTPUT_DIR = output

SRC_DIR = src

OUT_DIRS := $(OUTPUT_DIR)/src

SRC = src/main.c

LDFLAGS := -lreadline

include list/Makefile
include build/Makefile
