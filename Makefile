# This software is distributed under the GNU General Public License Version 3
# Copyright (C) Aparajita Haldar

COMPILER = g++
CFLAGS   = -g -MMD -MP -Wall -Wextra -Wunused-parameter -Wfloat-equal -fPIC
LDFLAGS  = -L.
SGDL     = SGDL
LIBS     = -l$(SGDL) -lGTL
LIBSGDL	 = lib$(SGDL).so
INCLUDE  = -I.
MAIN	 = main
OBJDIR   = .
SOURCES  = util.cpp cgraph.cpp ctree.cpp ebdgraph.cpp
HEADERS  = $(SOURCES:.cpp=.h)
OBJECTS  = $(SOURCES:.cpp=.o)
INSTALL  = install
PREFIX   = ../local
RM       = rm -f

$(SGDL): $(OBJECTS)
	$(COMPILER) $(CFALGS) -shared $(OBJECTS) -o $(LIBSGDL)

$(MAIN): $(OBJECTS) $(LIBS) $(LIBSGDL)
	$(COMPILER) -o $@ $(MAIN).cpp $(CFLAGS) $(LDFLAGS) $(LIBS)

all: $(SGDL) $(MAIN)

$(INSTALL): $(SGDL) $(HEADERS)
	$(INSTALL) -d $(PREFIX)/lib $(PREFIX)/include/$(SGDL)
	$(INSTALL) -t $(PREFIX)/lib $(LIBSGDL)
	$(INSTALL) -t $(PREFIX)/include/$(SGDL) $(HEADERS)

un$(INSTALL):
	$(RM) -r $(PREFIX)/lib/$(LIBSGDL) $(PREFIX)/include/$(SGDL)

%.o: %.cpp %.h
	$(COMPILER) $(CFLAGS) $(INCLUDE) -o $@ -c $<

clean:
	$(RM) $(OBJECTS) $(DEPENDS) $(MAIN) $(LIBSGDL) *~ *.d main.o

-include $(DEPENDS)
