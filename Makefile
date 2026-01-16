ifndef GBDK_HOME
	GBDK_HOME = gbdk
endif

LCC = $(GBDK_HOME)/bin/lcc

SRCDIR = src
OBJDIR = obj
BINDIR = bin

CSOURCES = $(wildcard $(SRCDIR)/*.c)
OBJS = $(CSOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(BINDIR)/gbc0.gb

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(LCC) -c -o $@ $<

$(BINDIR)/gbc0.gb: $(OBJS) | $(BINDIR)
	$(LCC) -Wm-yc -o $@ $(OBJS)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

run: $(BINDIR)/gbc0.gb
ifeq ($(shell uname),Darwin)
	./assets/sameboy/SameBoy.app/Contents/MacOS/SameBoy $(BINDIR)/gbc0.gb
else
	./assets/bgb/bgb.exe $(BINDIR)/gbc0.gb
endif

clean:
	rm -rf $(OBJDIR) $(BINDIR)
