#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <unistd.h>

#include "defs.h"
#include "blit.h"

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
	blit_borders(COL_BLUE);
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

int pause() {
	int overwritten[16];
	int ch,i;

	for (i = 0; i < 16; i++)
		overwritten[i] = (int) mvwinch(term, 10, 31 + i);

	SET_COLOR(COL_RED);
	mvwprintw(term, 10, 31," ** PAUSED ** ");
	SET_COLOR(COL_BKG);

	wmove(term,0,0);

	while ((ch = wgetch(term)) == ERR);

	for (i = 0; i < 16;i++)
		mvwaddch(term, 10, 31 + i, (chtype) overwritten[i]);

	if ((ch == KEY_ESC) || (ch == 'Q')) 
        return -1;

	return 0;
}

int move_temmie() {
    int c = 0;
    static int last_c = -1;
    static int tem_x = 37;
    static int tem_speed = 0;

    c = wgetch(term);
	if (c != last_c) {	
			switch(c) {

			case ERR:
				/* No key pressed */
				break;
			case KEY_LEFT:
				tem_speed--;
				break;
			case KEY_RIGHT:
				tem_speed++;
				break;
			case KEY_DOWN:
				tem_speed=0;
				break;
            case 'p':
            case 'P':
                if (pause() < 0) {
                    c = 'Q';
                }
                break;
            case KEY_ESC:
                c = 'Q';
            }
    }

    last_c = c;

    wmove(term, 0, 0);
    wrefresh(term);

    return c != 'Q';

}

void m_wait(long delay) {
    usleep(delay);
}

int main() {	
    srand(time(NULL));
	init_screen();			/* Start curses mode */
    
	if (!right_size()) {
		endwin();
		fprintf(stderr,"NO!!!!! less than 80x25 terminals r... NOT CUTE!\n");
		return -1;
	}

    presentation();

    while (move_temmie()) {
        m_wait(DELAY);
        blit_borders(COL_GREEN);
    }
    
    endwin();

    return 0;
}
