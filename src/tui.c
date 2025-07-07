#include "tui.h"
#include "generator.h"
#include <locale.h>
#include <ncurses.h>

#define NUM_OPTIONS 12
const char *options[NUM_OPTIONS] = {
    "C",
    "C++",
    "Python",
    "Go",
    "Rust",
    "Java",
    "JavaScript (Node.js)",
    "TypeScript",
    "Shell",
    "HTML/CSS/JS (web)",
    "Lua",
    "Haskell"
};

// Use a rainbow of colors (loop if not enough)
const short option_colors[NUM_OPTIONS] = {
    COLOR_RED, COLOR_YELLOW, COLOR_GREEN, COLOR_CYAN,
    COLOR_BLUE, COLOR_MAGENTA, COLOR_RED, COLOR_YELLOW,
    COLOR_GREEN, COLOR_CYAN, COLOR_BLUE, COLOR_MAGENTA
};

void start_tui() {
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    char project_name[256];

    if (has_colors()) {
        start_color();
        use_default_colors();

        for (int i = 0; i < NUM_OPTIONS; i++) {
            init_pair(10 + i, option_colors[i], -1);
        }
        init_pair(1, COLOR_GREEN, -1);  // selected dot (yes)
        init_pair(2, COLOR_RED, -1);    // unselected dot (no)
        init_pair(3, COLOR_GREEN, -1);  // title/prompt
    }

    int highlight = 0;
    int choice;

    // --- Display menu once and update highlight ---
    while (1) {
        attron(COLOR_PAIR(3));
        mvprintw(0, 0, "Select a language/framework (press 'q' or ESC to quit):");
        attroff(COLOR_PAIR(3));

        for (int i = 0; i < NUM_OPTIONS; i++) {
            if (i == highlight) {
                attron(COLOR_PAIR(1));
                mvprintw(i + 2, 2, "●");
                attroff(COLOR_PAIR(1));
            } else {
                attron(COLOR_PAIR(2));
                mvprintw(i + 2, 2, "○");
                attroff(COLOR_PAIR(2));
            }

            attron(COLOR_PAIR(10 + i));
            mvprintw(i + 2, 4, "%-25s", options[i]);  // pad to clear leftover chars
            attroff(COLOR_PAIR(10 + i));
        }
        refresh();

        choice = getch();

        if (choice == 'q' || choice == 27) {
            endwin();
            return;
        } else if (choice == KEY_UP || choice == 'k') {
            highlight = (highlight - 1 + NUM_OPTIONS) % NUM_OPTIONS;
        } else if (choice == KEY_DOWN || choice == 'j') {
            highlight = (highlight + 1) % NUM_OPTIONS;
        } else if (choice == '\n' || choice == '\r') {
            break;
        }
    }

    // --- Prompt project name, show below menu ---
    attron(COLOR_PAIR(3));
    mvprintw(NUM_OPTIONS + 4, 0, "Enter project name:                     ");
    attroff(COLOR_PAIR(3));
    move(NUM_OPTIONS + 5, 0);
    echo();
    getnstr(project_name, 255);
    noecho();

    // --- Show generating message below ---
    attron(COLOR_PAIR(3));
    mvprintw(NUM_OPTIONS + 7, 0, "Generating project '%s' in language: %s", project_name, options[highlight]);
    attroff(COLOR_PAIR(3));
    refresh();

    endwin();  // Exit curses before heavy work

    generate_project_by_language(highlight, project_name);

    // Re-init curses and show done message below previous content
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    attron(COLOR_PAIR(3));
    mvprintw(NUM_OPTIONS + 9, 0, "Done. Exiting...");
    attroff(COLOR_PAIR(3));
    refresh();

    move(NUM_OPTIONS + 10, 0);
    curs_set(0);

    endwin();
}
