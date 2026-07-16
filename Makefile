CXX       = g++
CXXFLAGS  = -std=c++17 -O2
LIBS      = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SRC       = src/main.cpp
BUILD_DIR = build
BIN       = $(BUILD_DIR)/Snake

.PHONY: all run clean

all: $(BIN)

$(BIN): $(SRC)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(BIN) $(LIBS)

# Esegue il gioco dalla root del progetto, cosi' i path relativi
# verso assets/ e data/ restano validi.
run: all
	./$(BIN)

clean:
	rm -rf $(BUILD_DIR)
