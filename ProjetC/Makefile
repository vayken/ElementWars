CC=g++
 
 
# Les différents répertoires contenant respectivement les fichiers : Sources *.c, Headers *.h, Objets *.o, l'exécutable
SRCDIR=./src
HEADDIR=./include
SFMLINCLUDE=./SFML/include
SFMLLIB=./SFML/lib
BINDIR=./bin
LIBDIR=./obj
 
 
# Les différentes options de compilations
CFLAGS= -I$(HEADDIR) -I$(SFMLINCLUDE) -Wall -O2 -g -std=c++11 
# Les différents bibliothèques 
GLLIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -L$(SFMLLIB)
 
# L'exécutable
BIN=elementWars 
 
# Où trouver les différents sources *.cpp qu'il faudra compiler pour créer les objets correspondants
SRC= $(wildcard $(SRCDIR)/*.cpp)
OBJ= $(SRC:$(SRCDIR)/%.cpp=$(LIBDIR)/%.o)
 
all: $(BIN)
 
#Création de l'exécutable
elementWars: $(OBJ)
	$(CC) -o $(BINDIR)/$@ $^ $(CFLAGS) $(GLLIBS)
 
# Création des différents *.o à partir des *.cpp
$(LIBDIR)/%.o: $(SRCDIR)/%.cpp $(HEADDIR)/%.h
	$(CC) -o $@ -c $< $(CFLAGS)
 
# Nettoyage des objets => Tout sera recompiler !
clean:
	rm $(LIBDIR)/*.o
 
# Nettoyage complet => clean + effacement du l'exécutable
Clean: clean
	rm $(BINDIR)/*