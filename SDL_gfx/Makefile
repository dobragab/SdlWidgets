TARGETDIR= .
TARGET   = libSDL_gfx.a

SRCDIR   = .
OBJDIR   = obj

RM       = rm -f
MAKEDIR  = mkdir -p
AR       = ar rcs

WARNINGS = 
SDL_CONFIG = `sdl2-config --cflags`

CXX = g++
CXXFLAGS = -std=c++11 -O3 $(WARNINGS) $(SDL_CONFIG) -pthread

HEADERS := $(wildcard $(SRCDIR)/*.h)
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.cpp.o)

.PHONY: clean all

all: dirs $(TARGETDIR)/$(TARGET)

clean:
	@$(RM) $(OBJDIR)/*.o
	@$(RM) $(TARGETDIR)/$(TARGET)
	@echo Cleaned successfully.

dirs:
	@$(MAKEDIR) $(TARGETDIR)
	@$(MAKEDIR) $(OBJDIR)

$(TARGETDIR)/$(TARGET): $(OBJECTS)
	$(AR) $(TARGETDIR)/$(TARGET) $(OBJECTS) 

$(OBJDIR)/%.cpp.o : $(SRCDIR)/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@
