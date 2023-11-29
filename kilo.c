#include <unistd.h>
#include <ctype.h>
#include <stdio.h>

#define CTRL_KEY(k)	((k) & 0x1F)

extern void enableRawMode();

int main() {

	enableRawMode();

	char c = '\0';
	while( 1 ) {

		read(STDIN_FILENO, &c, 1);
		if( iscntrl(c) ) {
			printf("%d\r\n", c);
		} else {
			printf("%x ('%c')\r\n", c, c);
		}
		
		if ( c == CTRL_KEY('q' )) {
			printf("Bye bye!\r\n");
			break;
		}
	}

	return 0;
}
