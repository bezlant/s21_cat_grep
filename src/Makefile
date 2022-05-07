CC:=gcc
CFLAGS:=-Wall -Werror -Wextra -std=c11

CAT_PATH:=./cat
GREP_PATH:=./grep
CAT:=s21_cat
GREP:=s21_grep

LDFLAGS:=-lm
ASAN:=-fsanitize=address -g

SRCS_CAT:=$(shell find $(CAT_PATH) -name "*.c")
OBJS_CAT:=$(SRCS_CAT:%.c=%.o)
SRCS_CAT_H:=$(shell find $(CAT_PATH) -name "*.h")

SRCS_GREP:=$(shell find $(GREP_PATH) -name "*.c")
OBJS_GREP:=$(SRCS_GREP:%.c=%.o)
SRCS_GREP_H:=$(shell find $(GREP_PATH) -name "*.h")

all: $(CAT) $(GREP)

$(CAT): $(OBJS_CAT) $(SRCS_CAT_H)
	$(CC) $(OBJS_CAT) $(CFLAGS) -o $@ $(LDFLAGS)
	
$(CAT_PATH)/%.o: %.c $(SRCS_CAT_H)
	$(CC) $(CFLAGS) $(ASAN) -c $< -o $@

$(GREP): $(OBJS_GREP) $(SRCS_GREP_H)
	$(CC) $(OBJS_GREP) $(CFLAGS) -o $@ $(LDFLAGS)

$(GREP_PATH)/%.o: %.c $(SRCS_GREP_H)
	$(CC) $(CFLAGS) $(ASAN) -c $< -o $@


clean:
	rm $(OBJS_CAT) $(CAT)
	rm $(OBJS_GREP) $(GREP)

rebuild: clean all

.PHONY: clean
