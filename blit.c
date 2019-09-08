#include <curses.h>
#include "defs.h"
#include "util.h"

extern int x_ofs;
extern int y_ofs;
extern int term_x;
extern int term_y;
extern WINDOW *term;

void blit_borders(int color) {
    int i;
    SET_COLOR(color);

    if (y_ofs-1 >= 0) {
		for (i=x_ofs;i<80+x_ofs;i++)
			mvwaddch(term,y_ofs-1,i,(chtype)'-');
	}

	if (y_ofs+25 < term_y) {
		for (i=x_ofs;i<80+x_ofs;i++)
			mvwaddch(term,y_ofs+25,i,(chtype)'-');
	}

	if (x_ofs-1 >= 0) {
		for (i=y_ofs;i<25+y_ofs;i++)
			mvwaddch(term,i,x_ofs-1,(chtype)'|');
	}

	if (x_ofs+80 < term_x) {
		for (i=y_ofs;i<25+y_ofs;i++)
			mvwaddch(term,i,x_ofs+80,(chtype)'|');
	}

	if ((x_ofs-1 >= 0) && (y_ofs-1 >= 0))
		mvwaddch(term,y_ofs-1,x_ofs-1,(chtype)'+');
	if ((x_ofs-1 >= 0) && (y_ofs+25 < term_y))
		mvwaddch(term,y_ofs+25,x_ofs-1,(chtype)'+');
	if ((x_ofs+80 < term_x) && (y_ofs-1 >= 0))
		mvwaddch(term,y_ofs-1,x_ofs+80,(chtype)'+');
	if ((x_ofs+80 < term_x) && (y_ofs+25 < term_y))
		mvwaddch(term,y_ofs+25,x_ofs+80,(chtype)'+');

	SET_COLOR(COL_BKG);
}

void blit_temmie(int x, int y) {
/* Player Temmie 
 
             .''..           ...                  
            .:'','...,:'   .''.;'                 
            ,,;d:.....''',,..ccc,                 
           .,...             .,,,.                
          ';     .:d;           .;'               
         .;.   .:ONMKo.          ';.              
         ;;   ,xkxXMMWKdlo;      .;'              
       .d0c  ,0Ndc0WNWKloOd.     .ol,cc'          
       .d0c  ,0Ndc0WNWKloOd.     .ol,cc'         
       .xXN0,.lNWKO000O0WWO. .;'cNMMWN0:.         
         .'l: .cKWMMMMMMWNx. '; .cll::lokc        
           ,;  'ldkkkkkkdl'  .''cl;;d0X0d'        
           .;,'.l0kxkkkkO0o. .dxOWWWWk,.          
            .'.'OMN0XWMMNKKx:dXxkWNNMX;           
               'x0k;,ONNx,oKNNkd0OoOMWc           
               .x0x' cOOc. .'ldxc.;0MO.           
                ;o;. 'lc.    ,l:..;ll'  
*/

    if (is_y_range(y)) {
        SET_COLOR(COL_WHITE);
        mvwprintw(term, y, x + 6,  " .''..           ...");
    }

    if (is_y_range(y + 1)) {
        mvwprintw(term, y + 1, x + 5,  " .:'','...,:'   .''.;'");
    }

    if (is_y_range(y + 2)) {
        mvwprintw(term, y + 2, x + 5,  ",,;d:.....''',,..ccc, ");
    }

    if (is_y_range(y + 3)) {
        mvwprintw(term, y + 3, x + 4,  " .,...             .,,,.");
    } 

    if (is_y_range(y + 4)) {
        mvwprintw(term, y + 4, x + 3,  " ';     .:d;           .;'");
    }

    if (is_y_range(y + 5)) {
        mvwprintw(term, y + 5, x + 2,  " .;.   .:ONMKo.          ';.");
    }

    if (is_y_range(y + 6)) {
        mvwprintw(term, y + 6, x + 2,  " ;;   ,xkxXMMWKdlo;      .;'");
    }

    if (is_y_range(y + 7)) {
        mvwprintw(term, y + 7, x,  " .d0c  ,0Ndc0WNWKloOd.     .ol,cc'");
    }

    if (is_y_range(y + 8)) {
        mvwprintw(term, y + 8, x,  " .d0c  ,0Ndc0WNWKloOd.     .ol,cc'");
    }

    if (is_y_range(y + 9)) {
        mvwprintw(term, y + 9, x,  " .xXN0,.lNWKO000O0WWO. .;'cNMMWN0:.");
    }

    if (is_y_range(y + 10)) {
        mvwprintw(term, y + 10, x + 2,  " .'l: .cKWMMMMMMWNx. '; .cll::lokc");
    }

    if (is_y_range(y + 11)) {
        mvwprintw(term, y + 11, x + 4,  " ,;  'ldkkkkkkdl'  .''cl;;d0X0d'");
    }

    if (is_y_range(y + 12)) {
        mvwprintw(term, y + 12, x + 4,  " .;,'.l0kxkkkkO0o. .dxOWWWWk,.");
    }

    if (is_y_range(y + 13)) {
        mvwprintw(term, y + 13, x + 5,  " .'.'OMN0XWMMNKKx:dXxkWNNMX;");
    }

    if (is_y_range(y + 14)) {
        mvwprintw(term, y + 14, x + 8,  " 'x0k;,ONNx,oKNNkd0OoOMWc");
    }

    if (is_y_range(y + 15)) {
        mvwprintw(term, y + 15, x + 8,  " .x0x' cOOc. .'ldxc.;0MO.");
    }

    if (is_y_range(y + 16)) {
        mvwprintw(term, y + 16, x + 9,  " ;o;. 'lc.    ,l:..;ll'");
    }

    SET_COLOR(COL_BKG);
}

void clear_temmie(int x, int y)
{
	SET_COLOR(COL_BKG);
    int tem_x_offset[] = {6, 5, 5, 4, 3, 2, 2, 0, 0, 0, 2, 4, 4, 5, 8, 8, 9};
    for (int i = 0; i <= 16; i++) {
        mvwprintw(term, y + i, x + tem_x_offset[i], "         "); 
    }
}
