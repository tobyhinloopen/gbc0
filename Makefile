ifndef GBDK_HOME
	GBDK_HOME = gbdk
endif

LCC = $(GBDK_HOME)/bin/lcc

SRCDIR = src
BUILDDIR = build
RELEASEDIR = release

CSOURCES = $(wildcard $(SRCDIR)/*.c)
OBJS = $(CSOURCES:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)

all: $(RELEASEDIR)/gbc0.gb

$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	$(LCC) -c -o $@ $<

$(RELEASEDIR)/gbc0.gb: $(OBJS) | $(RELEASEDIR)
	rm -f $(RELEASEDIR)/*.sav $(RELEASEDIR)/*.ss*
	$(LCC) -o $@ $(OBJS)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(RELEASEDIR):
	mkdir -p $(RELEASEDIR)

clean:
	rm -rf $(BUILDDIR) $(RELEASEDIR)
