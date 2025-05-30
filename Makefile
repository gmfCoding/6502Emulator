SRCSF = $(TEST) \
		6502.c

ifndef $(TEST)
TEST=main.c
endif

ifndef $(OS)
OS := $(shell uname)
endif

$(info Compiling for OS:$(OS))

NAME = prog

DIRSRC = src
DIROBJ = obj/$(CONF)
DIRINC = inc

# All relative to Makefile's folder
SRCS = $(patsubst %.c,$(DIRSRC)/%.c, $(SRCSF))
OBJS = $(SRCS:$(DIRSRC)/%.c=$(DIROBJ)/%.o)
LIBS = $(patsubst %.a,$(DIRLIB)/%.a, $(LIBSF)) 
DEPS = $(OBJS:.o=.d)

LIB-I = $(patsubst %,-I%,$(dir $(LIBS))) -I$(DIRLIB)
LIB-l = $(subst lib,-l,$(basename $(notdir $(LIBSF))))
LIB-L = $(patsubst %,-L$(DIRLIB)/%, $(dir $(LIBSF)))

CC = cc

WFLAGS =  -Wall -Wextra -Werror $(EFLAGS)
CPPFLAGS =-I$(DIRINC) $(LIB-I) -MM -MMD -MP
CFLAGS = $(OPFLAG) $(DFLAGS) $(WFLAGS)
LDFLAGS = $(OPFLAG) $(DFLAGS) $(LIB-L) $(LIB-l) -lz -lm -lpthread

OPTS = $(OPT)
SAN = address 

CONF = debug
CONF_TARGET = .target

ifneq (,$(findstring debug,$(CONF)))
OPTS = fsan,debug
endif

ifneq (,$(findstring dsym,$(CONF)))
OPTS = debug
endif

ifneq (,$(findstring none,$(OPTS)))
OPFLAG = -O0
endif
ifneq (,$(findstring debug,$(OPTS)))
	OPFLAG = -O0
	DFLAGS += -g3
endif
ifneq (,$(findstring fdeb,$(OPTS)))
	OPFLAG = -O1 -march=native
	DFLAGS += -g3
endif
ifneq (,$(findstring fsan,$(OPTS)))
# -fno-sanitize-ignorelist -fsanitize-ignorelist=ignorelist.txt
# Compile with selected sanitizer:
# And when using other sanitizers such as memory or undefined, it may be useful to not prematurely stop,
# Use UBSAN_OPTIONS=halt_on_error=0 (need -fs..-recover=..) or equivelent
# Also might be nice to redirect stderr to a file
# USE 
	DFLAGS += -fsanitize=$(SAN) -fsanitize-recover=$(SAN) 
endif
ifneq (,$(findstring gmon,$(OPTS)))
	PGFLAGS += -pg
endif

# RULES
all: $(NAME)

# marker for the last built architecture
BUILT_MARKER := $(CONF).built

$(BUILT_MARKER):
	@-rm -f *.built
	@touch $(BUILT_MARKER)

# OBJ TO PROJECT
$(NAME): $(LIBS) $(OBJS) $(BUILT_MARKER)
	-@printf "${BLUE}"
	$(CC) $(PGFLAGS) $(OBJS) $(LDFLAGS) -o $@
	-@printf "${NC}"

# SOURCE TO OBJ
$(OBJS): $(DIROBJ)%.o : $(DIRSRC)%.c | $(DIROBJ)
	-@mkdir -p $(dir $@)
	-@printf "${GREEN}"
	-$(CC) $(PGFLAGS) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<
	-@printf "${NC}"

# CLEANING
fclean: clean
	-@printf "${BRED}Cleaning executable!\n${RED}"
	-rm -f $(NAME)
	-@printf "${NC}"

clean:
	-@printf "${BYELLOW}Cleaning objects!\n${RED}"
	-rm -rf $(DIROBJ)
	-@printf "${NC}"

re: fclean all

# Dependencies
-include $(DEPS)

# Folders
$(DIROBJ):
	-@printf "${CYAN}"
	-mkdir -p $(DIROBJ)
	-@printf "${NC}"

.PHONY: all re fclean clean libclean

# COLORS
export BGREEN = \033[1;32m
export GREEN = \033[0;32m
export BRED = \033[1;31m
export RED = \033[0;31m
export BYELLOW = \033[1;33m
export YELLOW = \033[0;33m
export BBLUE = \033[1;34m
export BLUE = \033[0;34m
export BCYAN = \033[1;36m
export CYAN = \033[0;36m
export NC = \033[0m