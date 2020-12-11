#include <ncurses.h>
#include "ncursesViewController.h"

ncursesViewController::ncursesViewController() {
    initscr();
    noecho();
    ESCDELAY = 250;
    keypad(stdscr, TRUE);
}

void ncursesViewController::moveCursorToFinalPosn() {
    move(finalCursorPosn.y, finalCursorPosn.x);
    refresh();
}

const Posn ncursesViewController::getScrSize() const {
    int h, w;
    getmaxyx(stdscr, h, w);
    return Posn{w, h};
}

const int ncursesViewController::getScrWidth() const {
    int h, w;
    getmaxyx(stdscr, h, w);
    return w;
}

const int ncursesViewController::getScrHeight() const {
    int h, w;
    getmaxyx(stdscr, h, w);
    return h;
}

void ncursesViewController::print(char c, const Posn p) {
    move(p.y, p.x);
    addch(c);
    refresh();
}

int ncursesViewController::get() {
    return getch();
}

ncursesViewController::~ncursesViewController() {
    endwin();
}
