# Quelldateien
SOURCES := main.c graphic.c engine.c config.c gfx.c ui.c
# zugehörige Include Dateien
INCLUDES := graphic.h engine.h config.h gfx.h ui.h
PRECOMPILEDHEADERS := $(INCLUDES:.h=.h.gch)
# aus Quelldateien resultierende Objektdateien
OBJS := $(SOURCES:.c=.o)
# benötigte externe Bibliotheken
LIBS := -lSDL2 -lm
# zu erzeugendes Programm
BINARY := animation

# Compilerflags, Debugging-Symbole, keine Optimierung, alle Warnings
CFLAGS := -g3 -O0 -Wall -Wundef -fmessage-length=0


# das gewünschte Programm aus den Einzelteilen zusammenfügen
$(BINARY): $(OBJS)
	$(CC) $(CFLAGS) -o $(BINARY) $(OBJS) $(LDFLAGS) $(LIBS)

# erzeuge die Objektdateien aus den Quelldateien
# der Einfachheit halber, kompiliere bei jeder Änderung in den Headerfiles
.c.o: $(INCLUDES)
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

# gewünschtes Ziel, wenn make ohne Kommandozeilenparameter aufgerufen wird
all: $(BINARY)

# Aufräumarbeiten:
clean:
	-rm -f $(BINARY)
	-rm -f $(OBJS)
	-rm -f $(PRECOMPILEDHEADERS)

# installiere die LibSDL2 auf Debian-basierten Linux-Systemen
setup:
	sudo sh -c "apt-get update; apt-get install libsdl2-dev"

.phony: all clean setup
