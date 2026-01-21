ifndef GBDK_HOME
	GBDK_HOME = gbdk
endif

LCC = $(GBDK_HOME)/bin/lcc

SRCDIR = src
OBJDIR = obj
BINDIR = bin

CSOURCES = $(wildcard $(SRCDIR)/*.c)
OBJS = $(CSOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TEST_OBJS = $(filter-out $(OBJDIR)/main.o,$(OBJS)) $(OBJDIR)/main_test.o

HEADERS = $(wildcard $(SRCDIR)/*.h)

all: $(BINDIR)/gbc0.gb

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS) | $(OBJDIR)
	$(LCC) -c -o $@ $<

$(OBJDIR)/main_test.o: $(SRCDIR)/main.c $(HEADERS) | $(OBJDIR)
	$(LCC) -c -DTEST_ONLY -o $@ $<

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

$(BINDIR)/gbc0_test.gb: $(TEST_OBJS) | $(BINDIR)
	$(LCC) -Wm-yc -o $@ $(TEST_OBJS)

test: $(BINDIR)/gbc0_test.gb
	rm -f $(BINDIR)/gbc0_test.png
	assets/sameboy/sameboy_tester --cgb --start --length 5 $(BINDIR)/gbc0_test.gb
	ffmpeg -y -i $(BINDIR)/gbc0_test.bmp $(BINDIR)/gbc0_test.png 2>/dev/null
	rm $(BINDIR)/gbc0_test.bmp

.PHONY: all run clean test
