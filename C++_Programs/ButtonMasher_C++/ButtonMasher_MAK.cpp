//**************************************************************
// ButtonMasher_MAK.cpp
//
// Purpose: Test your button mashing speed in this game by pressing spacebar as fast as you can. Your presses per second will be displayed upon completion.
//
// Note: This code will NOT RUN unless if you have a Mac and have installed ncurses. To install ncurses, install Homebrew by
// using the command "/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)""
// and use the command "brew install ncurses" to install ncurses. To run this program go to terminal, cd into the directory that the program is in,
// and write "g++ ButtonMasher_MAK.cpp -o ButtonMasher_MAK -lncurses" and press enter. This compiles the program. Then write "./ButtonMasher_MAK"
//
// R1: 24-Jan-2024 Muhammad Khurram – Written for Advanced Computer Studies.
//**************************************************************

#include <iostream>
#include <ctime>
#include <ncurses.h>
#include <thread>
#include <chrono>

int main() {
    initscr(); 
    noecho(); 
    nodelay(stdscr, false); 
    curs_set(FALSE); 

    printw("Welcome to my button masher! The button in question is the spacebar. Press it as fast as you can in the time allotted and see how fast you can go!\n\nPress Enter to start the game...\n");
    refresh();
    while (getch() != '\n');

    nodelay(stdscr, true);

    int count = 0;
    time_t start = time(0);
    double seconds_since_start = 0.0;


    for (int i = 3; i > 0; --i) 
    {
        printw("Game starts in: %d\n", i);
        refresh();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        clear();
    }

    printw("Go!!\n");
    refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    start = time(0);

    while(seconds_since_start < 5.0) 
    {
        char ch = getch();
        if (ch == ' ') {
            ++count;
        }
        seconds_since_start = difftime(time(0), start);
        clear();
        printw("Time left: %d\n", 5 - (int)seconds_since_start);
    }


    printw("Game Over!\n");
    printw("You pressed the spacebar %d times in 5 seconds.\n", count);
    printw("That's %f presses per second.\n", count / 5.0);
    refresh();
    std::this_thread::sleep_for(std::chrono::seconds(5));

    endwin(); 

    return 0;
}