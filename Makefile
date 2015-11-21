BINARY = SdlWidget

SRCDIR   = src
OBJDIR   = obj
BINDIR   = .

RM       = rm -f
MAKEDIR  = mkdir -p

WARNINGS = -Wall -Wdeprecated -pedantic -Wfloat-equal -Wunreachable-code -Wnon-virtual-dtor

SDL_CONFIG = `sdl2-config --cflags`

SDL_LIBS = `sdl2-config --libs` -lSDL2_gfx -lSDL2_ttf -lSDL2_image -lSDL2_mixer


CC = gcc
CFLAGS = -std=c99 -O3 $(WARNINGS) $(SDL_CONFIG)

CXX = g++
CXXFLAGS = -std=c++11 -O3 $(WARNINGS) $(SDL_CONFIG)
LDFLAGS = $(SDL_LIBS) -lm -lz


SOURCES := $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/*.cc) $(wildcard $(SRCDIR)/*.cxx)
INCLUDES := $(wildcard $(SRCDIR)/*.h) $(wildcard $(SRCDIR)/*.hpp) $(wildcard $(SRCDIR)/*.hh) $(wildcard $(SRCDIR)/*.hxx)

OBJECTS_C := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
OBJECTS_CPP := $(OBJECTS_C:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
OBJECTS_CC := $(OBJECTS_CPP:$(SRCDIR)/%.cc=$(OBJDIR)/%.o)
OBJECTS := $(OBJECTS_CC:$(SRCDIR)/%.cxx=$(OBJDIR)/%.o)


.PHONY: clean all dirs Linux LinuxDebug

all: dirs $(BINDIR)/$(BINARY)

Linux: all

LinuxDebug: all
LinuxDebug: CFLAGS += -DDEBUG -g -O0
LinuxDebug: CXXFLAGS += -DDEBUG -g -O0
LinuxDebug: LDFLAGS += -g

clean:
	$(RM) $(OBJDIR)/*.o
	$(RM) $(BINDIR)/$(BINARY)

dirs:
	$(MAKEDIR) $(BINDIR)
	$(MAKEDIR) $(OBJDIR)


$(BINDIR)/$(BINARY): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o : $(SRCDIR)/%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o : $(SRCDIR)/%.cxx
	$(CXX) $(CXXFLAGS) -c $< -o $@
