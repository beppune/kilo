#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define CTRL_KEY(k)	((k) & 0x1F)

extern void enableRawMode();

extern char editorReadKey();

void editorProcessKeypress() {
	char c = editorReadKey();

	switch(c) {
		case CTRL_KEY('q'):
			printf("Kilo: bye bye!\r\n");
			exit(0);
	}
}

void editorRefreshScreen() {
	write(STDOUT_FILENO, "\x1b[2J", 4);
	write(STDOUT_FILENO, "\x1b[H", 3);
}

int main() {

	enableRawMode();
	editorRefreshScreen();


	while( 1 ) {
		editorProcessKeypress();
	}

	return 0;
}
