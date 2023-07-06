#include <windows.h>
#include <iostream>

#include "family.h"
#include "food.h"
#include "snake.h"

family myFamily;
food myFood;
snake mySnake(1, 1);

// void cls(HANDLE);

int main()
{
    myFamily.clear();

    myFood.set_position(5, 5);

    while (1)
    {
        // Clear every char in Family
        myFamily.clear();

        // Collect user input for frame
        mySnake.get_input(myFamily);
        try
        {
            // Attempt to move Snake, looking for Kill error
            mySnake.move(myFamily);
        }
        catch (const char *er)
        {
            // If we receive error, clear screen and end game
            myFamily.clear();
            std::cerr << er << std::endl;
            system("pause");
            return -1;
        }

        // Draw chars in Family for new frame
        mySnake.draw(myFamily);
        myFamily.draw(myFood.get_y(), myFood.get_x(),
                      myFood.get_symbol());

        // If Snake Head collects Food this frame,
        // grow Snake and place food in random location
        if (mySnake.check_food(myFood))
        {
            myFood.reposition(myFamily);
        }

        myFamily.print();

        // Wait 1 frame
        Sleep(1000 / 30);

        // Clear screen
        system("cls");
        // HANDLE hStdout;
        // hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        // cls(hStdout);
    }

    return 0;
}

/*
void cls(HANDLE hconsole)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    SMALL_RECT scrollRect;
    COORD scrollTarget;
    CHAR_INFO fill;

    // Get the number of character cells in the current buffer
    if (!GetConsoleScreenBufferInfo(hconsole, &csbi))
    {
        return;
    }

    // Scroll the rectangle of the entire buffer
    scrollRect.Left = 0;
    scrollRect.Top = 0;
    scrollRect.Right = csbi.dwSize.X;
    scrollRect.Bottom = csbi.dwSize.Y;

    // Scroll it upwards off the top of the buffer with a
    // magnitude of the entire height
    scrollTarget.X = 0;
    scrollTarget.Y = (SHORT)(0 - csbi.dwSize.Y);

    // Fill the empty space with the buffer's default
    // text attributes
    fill.Char.UnicodeChar = TEXT(' ');
    fill.Attributes = csbi.wAttributes;

    // Do the scroll
    ScrollConsoleScreenBuffer(hconsole, &scrollRect, NULL,
                              scrollTarget, &fill);

    // Move the cursor to the top left corner too
    csbi.dwCursorPosition.X = 0;
    csbi.dwCursorPosition.Y = 0;

    SetConsoleCursorPosition(hconsole, csbi.dwCursorPosition);
}
*/