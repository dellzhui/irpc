.PHONY: all clean

CC = gcc
LIB_DST = libirpc_client.a
CLIENT_TEST_DST = irpc_client
TARGETS = $(LIB_DST) $(CLIENT_TEST_DST)

CURDIR = $(shell pwd)
BUILDIR = $(CURDIR)/out
SRCS_ROOT_DIR = $(CURDIR)/src
SRCS_DIR = $(shell find $(SRCS_ROOT_DIR) -type d)
OBJS_DIR = $(BUILDIR)/objs
LIBS_DIR = $(BUILDIR)/lib
DEPS_DIR = $(BUILDIR)/deps
EXEC_DIR = $(BUILDIR)/bin

SRCS_LIB = irpc.dsc.c \
			fasterjson.c

OBJS_LIB = $(addprefix $(OBJS_DIR)/,$(SRCS_LIB:.c=.o))

CLIENT_SRCS_BIN = irpc_client.c
CLIENT_OBJS_BIN = $(addprefix $(OBJS_DIR)/,$(CLIENT_SRCS_BIN:.c=.o))

CFLAGS = -fPIC  -Wall -g -Werror -I.
LDFLAGS =

vpath %.c $(SRCS_DIR)
$(shell if [ ! -d $(OBJS_DIR) ]; then mkdir -p $(OBJS_DIR); fi)
$(shell if [ ! -d $(LIBS_DIR) ]; then mkdir -p $(LIBS_DIR); fi)
$(shell if [ ! -d $(DEPS_DIR) ]; then mkdir -p $(DEPS_DIR); fi)
$(shell if [ ! -d $(EXEC_DIR) ]; then mkdir -p $(EXEC_DIR); fi)

default: $(TARGETS)

all: $(TARGETS)

run:
	@$(EXEC_DIR)/$(CLIENT_TEST_DST) -i 192.168.0.200 -c atom1 -p " a bb  ccc ddd "

$(LIB_DST): $(OBJS_LIB)
	@echo "building $@"
	@ar -rcu $(LIBS_DIR)/$(LIB_DST) $(OBJS_LIB)

$(CLIENT_TEST_DST): $(CLIENT_OBJS_BIN) $(LIB_DST)
	@echo "building $@"
	@$(CC) -o $(EXEC_DIR)/$(CLIENT_TEST_DST) $(CLIENT_OBJS_BIN) $(LDFLAGS) -L$(LIBS_DIR) -lirpc_client

ifneq ($(MAKECMDGOALS), clean)
sinclude $(addprefix $(DEPS_DIR)/,$(SRCS_LIB:.c=.d))
sinclude $(addprefix $(DEPS_DIR)/,$(CLIENT_SRCS_BIN:.c=.d))
endif

$(OBJS_DIR)/%.o: %.c
	@echo "compiling $(notdir $(filter %.c, $^))"
	@if [ "x$(notdir $(filter %.c, $^))" = "xirpc.dsc.c" ];then \
		$(CC) `echo $(CFLAGS) | sed 's/-Werror//g'` -c $< -o $@ 1>/dev/null 2>&1 ; \
	else \
		$(CC) $(CFLAGS) -c $< -o $@; \
	fi

$(DEPS_DIR)/%.d: %.c
	@set -e; \
	rm -f $@; \
	$(CC) -E -MM $(CFLAGS) $(filter %.c, $^) > $@.$$$$; \
	sed 's,\(.*\)\.o[ :]*,$(OBJS_DIR)/\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$


install: default

clean:
	@rm -rf $(TARGETS) $(OBJS_DIR) $(DEPS_DIR) $(BUILDIR) $(EXEC_DIR)
