CC:=gcc
CFLAGS:=-Wall -Werror -Wextra -std=c11
CAT_PATH:=./cat
GREP_PATH:=./grep
CAT:=s21_cat
GREP:=s21_grep
LDFLAGS:=-lm
CPPFLAGS:=-MMD -MP
ASAN:=-fsanitize=address -g

SRCS_CAT:=$(shell find $(CAT_PATH) -name "*.c")
OBJS_CAT:=$(SRCS_CAT:%.c=%.o)

SRCS_GREP:=$(shell find $(GREP_PATH) -name "*.c")
OBJS_GREP:=$(SRCS_GREP:%.c=%.o)

all: $(CAT) $(GREP)

$(CAT): $(OBJS_CAT)
	$(CC) $(OBJS_CAT) $(CFLAGS) -o $@ $(LDFLAGS)
	
$(CAT_PATH)/%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(ASAN) -c $< -o $@

$(GREP): $(OBJS_GREP)
	$(CC) $(OBJS_GREP) $(CFLAGS) -o $@ $(LDFLAGS)

$(GREP_PATH)/%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(ASAN) -c $< -o $@

.PHONY: clean

fclean:
	rm $(OBJS_GREP)
	rm $(GREP_PATH)/*.d
	rm $(GREP)
	rm $(OBJS_CAT)
	rm $(CAT_PATH)/*.d
	rm $(CAT)

clean:
	rm $(OBJS_GREP)
	rm $(GREP_PATH)/*.d
	rm $(OBJS_CAT)
	rm $(CAT_PATH)/*.d

rebuild: clean all

-include $(DEPS)
