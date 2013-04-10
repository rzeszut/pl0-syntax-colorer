C=gcc
CFLAGS=-c -Wall -g
LDFLAGS=

BINDIR=bin

SOURCES=$(wildcard src/*.c)
SOURCE_FILES=$(notdir $(SOURCES))
SRCDIR=$(dir $(SOURCES))
OBJECTS=$(addprefix $(BINDIR)/,$(SOURCE_FILES:.c=.o))

EXECUTABLE=main

vpath %.c $(SRCDIR)

all: $(EXECUTABLE)
	@echo "Done."

$(EXECUTABLE): $(BINDIR) $(OBJECTS)
	@echo "Creating executable $(EXECUTABLE)..."
	@$(C) $(OBJECTS) $(LDFLAGS) -o $(EXECUTABLE)

$(BINDIR)/%.o: %.c
	@echo "Compiling $<..."
	@$(C) $(CFLAGS) $< -o $@

$(BINDIR):
	@echo "Creating $(BINDIR)..."
	@mkdir -p $(BINDIR)

.PHONY: clean

clean:
	@echo "Removing all binaries..."
	@$(RM) $(BINDIR)/*.o $(EXECUTABLE)
	@$(RM) -rf $(BINDIR)
	@echo "Done."
