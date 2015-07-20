# This software is distributed under the GNU General Public License Version 3
# Copyright (C) Aparajita Haldar

COMPILER = g++
CFLAGS   = -g -MMD -MP -Wall -Wextra -Winit-self -Wno-unused-parameter -Wfloat-equal
LDFLAGS  =
LIBS     = -lGTL
INCLUDE  = -I.
TARGET   = main
OBJDIR   = .
SOURCES  = $(wildcard *.cpp)
OBJECTS  = $(addprefix $(OBJDIR)/, $(SOURCES:.cpp=.o))

all: clean $(TARGET)

$(TARGET): $(OBJECTS) $(LIBS)
	$(COMPILER) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LIBS)

$(OBJDIR)/%.o: %.cpp %.h
	$(COMPILER) $(CFLAGS) $(INCLUDE) -o $@ -c $<

clean:
	rm -f $(OBJECTS) $(DEPENDS) $(TARGET) *~ *.d

-include $(DEPENDS)
