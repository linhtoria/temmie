#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

#include "defs.h"
#include "affects.h"

int end_x;
int x_ofs = 0;
int y_ofs = 0;
int term_x = 0;
int term_y= 0;

WINDOW *term;

void init_screen() {
	term = initscr(); /* Initialize terminal */

	start_color(); /* Initialize colors */
	init_pair(PC_WHITE,COLOR_WHITE,COLOR_BLACK);
	init_pair(PC_RED,COLOR_RED,COLOR_BLACK);
	init_pair(PC_GREEN,COLOR_GREEN,COLOR_BLACK);
	init_pair(PC_YELLOW,COLOR_YELLOW,COLOR_BLACK);
	init_pair(PC_BLUE,COLOR_BLUE,COLOR_BLACK);
	init_pair(PC_MAGENTA,COLOR_MAGENTA,COLOR_BLACK);
	init_pair(PC_CYAN,COLOR_CYAN,COLOR_BLACK);
	SET_COLOR(COL_BKG);

	cbreak(); /* Disable line buffering and erase/kill characters */
	noecho(); /* Don't echo characters */
	nodelay(term,TRUE); /* Don't block while waiting for input */

	nonl(); /* Don't translate return into newline, only CR */
	intrflush(term,FALSE); /* Do not flush input at ^C */
	keypad(term,TRUE); /* Enable keypad */

	wrefresh(term);
}

void presentation() {
	borders(COL_BLUE);
	SET_COLOR(COL_GREEN);

	mvwprintw(term,8+y_ofs,25+x_ofs, "  --*----**  TEMMIE  **---*--");
	mvwprintw(term,11+y_ofs,27+x_ofs, "   a game by Linh Nguyen");
	SET_COLOR(COL_WHITE);
	mvwprintw(term,22+y_ofs,29+x_ofs, "Press any key to start");
	SET_COLOR(COL_BKG);

	while (wgetch(term) == ERR);

	wclear(term);
}

// Returns true if terminal is 80x25
int right_size() {
	getmaxyx(term, term_y, term_x);

	x_ofs = (term_x - 80) / 2;
	y_ofs = (term_y - 25) / 2;

	return ((term_x >= 80) && (term_y >= 25));
}

int main() {	
    srand(time(NULL));
	init_screen();			/* Start curses mode */
    
	if (!right_size()) {
		endwin();
		fprintf(stderr,"Temmie must be run in an 80x25 terminal!\n");
		return -1;
	}

    presentation();
    endwin();

    return 0;

}
