all:
	gcc chess.c eventHandler.c gameLogic.c gtk.c AI.c knightMiniGame.c UI.c -o Chess $(shell pkg-config gtk+-3.0 --cflags --libs)

