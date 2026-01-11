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
	rm -f $(BINDIR)/*.sav $(BINDIR)/*.ss*
	$(LCC) -Wm-yc -o $@ $(OBJS)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

run: $(BINDIR)/gbc0.gb
	rm -rf /mnt/c/gbc
	mkdir -p /mnt/c/gbc
	cp $(BINDIR)/gbc0.gb /mnt/c/gbc/gbc0.gb
	/mnt/c/Program\ Files/mGBA/mGBA.exe "C:\\gbc\\gbc0.gb"

clean:
	rm -rf $(OBJDIR) $(BINDIR)
