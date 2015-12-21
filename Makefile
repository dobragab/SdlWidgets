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
CXXFLAGS = -std=c++11 -O3 $(WARNINGS) $(SDL_CONFIG) -pthread
LDFLAGS = $(SDL_LIBS) -lm -lz

HEADERS := $(wildcard $(SRCDIR)/*.h) $(wildcard $(SRCDIR)/*.hpp) $(wildcard $(SRCDIR)/*.hh) $(wildcard $(SRCDIR)/*.hxx)

SOURCES_C   := $(wildcard $(SRCDIR)/*.c)
SOURCES_CPP := $(wildcard $(SRCDIR)/*.cpp)
SOURCES_CC  := $(wildcard $(SRCDIR)/*.cc)
SOURCES_CXX := $(wildcard $(SRCDIR)/*.cxx)

SOURCES = $(SOURCES_C) $(SOURCES_CPP) $(SOURCES_CC) $(SOURCES_CXX)

OBJECTS_C   := $(SOURCES_C:$(SRCDIR)/%.c=$(OBJDIR)/%.c.o)
OBJECTS_CPP := $(SOURCES_CPP:$(SRCDIR)/%.cpp=$(OBJDIR)/%.cpp.o)
OBJECTS_CC  := $(SOURCES_CC:$(SRCDIR)/%.cc=$(OBJDIR)/%.cc.o)
OBJECTS_CXX := $(SOURCES_CXX:$(SRCDIR)/%.cxx=$(OBJDIR)/%.cxx.o)

OBJECTS = $(OBJECTS_C) $(OBJECTS_CPP) $(OBJECTS_CC) $(OBJECTS_CXX)
OBJECTS += $(OBJDIR)/SDL_gfx/SDL_gfxBlitFunc.cpp.o $(OBJDIR)/SDL_gfx/SDL_gfxPrimitives.cpp.o

.PHONY: clean all dirs Linux LinuxDebug

all: dirs SDL_gfx $(BINDIR)/$(BINARY)

Linux: all

LinuxDebug: all
LinuxDebug: CFLAGS += -DDEBUG -g -O0
LinuxDebug: CXXFLAGS += -DDEBUG -g -O0
LinuxDebug: LDFLAGS += -g

SDL_gfx: $(OBJDIR)/SDL_gfx/SDL_gfxBlitFunc.cpp.o $(OBJDIR)/SDL_gfx/SDL_gfxPrimitives.cpp.o

$(OBJDIR)/SDL_gfx/SDL_gfxBlitFunc.cpp.o: $(SRCDIR)/SDL_gfx/SDL_gfxBlitFunc.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/SDL_gfx/SDL_gfxPrimitives.cpp.o: $(SRCDIR)/SDL_gfx/SDL_gfxPrimitives.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJDIR)/*.o
	@$(RM) $(OBJDIR)/SDL_gfx/*.o
	@$(RM) $(BINDIR)/$(BINARY)
	@echo Cleaned successfully.

dirs:
	@$(MAKEDIR) $(BINDIR)
	@$(MAKEDIR) $(OBJDIR)
	@$(MAKEDIR) $(OBJDIR)/SDL_gfx


$(BINDIR)/$(BINARY): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@

$(OBJDIR)/%.c.o : $(SRCDIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.cpp.o : $(SRCDIR)/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.cc.o : $(SRCDIR)/%.cc $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.cxx.o : $(SRCDIR)/%.cxx $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@
