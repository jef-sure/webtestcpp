CXXFLAGS = -std=c++11 -O0 -g -Wall -fmessage-length=0

TMPDIR = tmp
BINDIR = bin
SRCDIR = src
OBJS := $(subst .cpp,.o,$(subst $(SRCDIR),$(TMPDIR),$(shell find $(SRCDIR) -name '*.cpp')))


LIBS =

TARGET =	$(BINDIR)/webtestcpp

.SUFFIXES: .cpp .o

-include $(OBJS:.o=.d)

$(TMPDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)
	$(CXX) -MM $(CXXFLAGS) $< | sed 's/^\([^ \t]\+\):/$(TMPDIR)\/\1:/' > $(TMPDIR)/$*.d
	
$(TARGET):	$(OBJS)
	@echo $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean