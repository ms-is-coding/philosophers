# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/02 11:03:00 by smamalig          #+#    #+#              #
#    Updated: 2025/11/27 12:15:03 by smamalig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= philo

SRC_DIR			:= src
LIB_DIR			:= lib
BUILD_DIR		:= build

CC				:= cc
CFLAGS			:= -Wall -Wextra -MMD -MP -std=gnu2x
CFLAGS_DEBUG	:= -Og -g3 -Wshadow -Wpadded -Wconversion -Wstrict-prototypes \
					-Wmissing-declarations -Wstrict-prototypes -Wundef \
					-Wmissing-prototypes -Wold-style-definition -Winline \
					-Wsign-conversion -Wcast-align -Wcast-qual -Wwrite-strings \
					-Wuninitialized -Wdouble-promotion -Wfloat-equal -Wvla \
					-Wnull-dereference -Wformat=2 -fstack-protector-strong
CFLAGS_RELEASE	:= -O2 -DNDEBUG -march=native -D__is_42sh
CFLAGS_SANITIZE	:= -fsanitize=undefined,thread


ifeq ($(MODE), release)
	CFLAGS += $(CFLAGS_RELEASE)
else ifeq ($(MODE), debug)
	CFLAGS += $(CFLAGS_DEBUG)
else ifeq ($(MODE), sanitize)
	CFLAGS += $(CFLAGS_DEBUG) $(CFLAGS_SANITIZE)
else
	MODE = default
	CFLAGS += -Werror
endif

ROOT_DIR	:= $(BUILD_DIR)/$(MODE)
OBJ_DIR		:= $(ROOT_DIR)/obj

SRC_FILES		:= sim.c philo.c main.c time.c

SRCS			:= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS			:= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
DEPS			:= $(OBJS:.o=.d)

INCLUDES		:= -Iinclude


.PHONY: all
all: $(NAME)
	@$(MAKE) postbuild --no-print-directory


.PHONY: default
default: all


.PHONY: release
release:
	@$(MAKE) MODE=release --no-print-directory


.PHONY: debug
debug:
	@$(MAKE) MODE=debug --no-print-directory


.PHONY: sanitize
sanitize:
	@$(MAKE) MODE=sanitize --no-print-directory


.PHONY: bonus
bonus: release


.PHONY: postbuild
postbuild:
	cp -f $(ROOT_DIR)/$(NAME) $(NAME)


$(NAME): $(ROOT_DIR)/$(NAME)


$(ROOT_DIR)/$(NAME): $(OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(OBJS) -o $(ROOT_DIR)/$(NAME)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)


.PHONY: fclean
fclean:
	rm -rf $(BUILD_DIR)
	rm -f $(NAME)


.PHONY: re
re: fclean
	@$(MAKE) all --no-print-directory


-include $(DEPS)


.PHONY: norm
norm:
	echo $(SRCS) | xargs -n1 -P$(shell nproc) norminette


.PHONY: tidy
tidy:
	echo $(SRCS) | xargs -n1 -P$(shell nproc) clang-tidy -p .
