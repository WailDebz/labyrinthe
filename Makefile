# ============================================================================
# Makefile — Donjon & Labyrinthe Interactif
# ============================================================================

CXX       = g++
CXXFLAGS  = -std=c++17 -Wall -Wextra -g
TARGET    = labyrinthe

# Sources
SRCS = main.cpp \
       src/classes/mur.cpp \
       src/classes/passage.cpp \
       src/classes/tresor.cpp \
       src/classes/monstre.cpp \
       src/classes/piege.cpp \
       src/classes/CaseFactory.cpp \
       src/classes/donjon.cpp \
       src/classes/player.cpp

# Objets
OBJS = $(SRCS:.cpp=.o)

# Règle par défaut
all: $(TARGET)

# Liaison
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilation
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage
clean:
	del /Q $(subst /,\,$(OBJS)) $(TARGET).exe 2>nul || true

# Exécution
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
