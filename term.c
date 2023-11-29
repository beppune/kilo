#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <errno.h>
#include <stdio.h>

struct termios saved_termios;

void die(const char *s) {
	perror(s);
	exit(1);
}

void disableRawMode() {
	if( tcsetattr(STDIN_FILENO, TCSAFLUSH, &saved_termios) == -1 )
		die("tcsetattr");
}

void enableRawMode() {
	if( tcgetattr(STDIN_FILENO, &saved_termios) == -1 )
		die("tcgetattr");

	atexit(disableRawMode);

	struct termios raw = saved_termios;

	if( tcgetattr(STDIN_FILENO, &raw) == -1 )
		die("tcgetattr");

	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= ~(CS8);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw.c_cc[VMIN] = 1;
	raw.c_cc[VTIME] = 1;

	if( tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1 )
		die("tcsetattr");

}

char editorReadKey() {
	int nread;
	char c;
	while( (nread = read(STDIN_FILENO, &c, 1)) != 1 ) {
		if( nread == -1 && errno != EAGAIN ) die("read");
	}
	return c;
}


