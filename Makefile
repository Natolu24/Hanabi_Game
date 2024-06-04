CC = g++
CFLAGS = -Wall -Wextra
RM = rm -f

PROGNAME = hanabi
FOLDNAME = Projet_Tuteure_Hanabi
PROGS = hanabi application scenes gamesystem ai_players
SOURCES = $(PROGS:=.cpp)
LIBRARY = -lsfml-graphics -lsfml-window -lsfml-system
OBJ = $(PROGS:=.o)


all: $(PROGNAME)

$(PROGNAME): $(OBJ)
	$(CC) $(OBJ) -o $(PROGNAME) $(LIBRARY)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(PROGS) $(OBJ) *~ gmon.out core.*