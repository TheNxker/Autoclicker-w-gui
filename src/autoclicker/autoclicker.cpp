// autoclicker.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream> // Main stuff for CPP
#include <Windows.h> // This helps me use inputs

// MAIN KEYBINDS
// LCTRL + ESC     | CLOSES PROGRAM
// LCTRL + RCTRL   | STARTS CLICKING

int ClickAmount = 10;                                                    // 10 clicks per event!!! | 10 Comes out to about 46.2 clicks per second

int main()
{
    while (true)
    {
        Sleep(50);                                                       // Allows up to 20 events per second.

        if (GetAsyncKeyState(VK_LCONTROL) & GetAsyncKeyState(VK_ESCAPE))
        {
            return 0;
        }
        if (GetAsyncKeyState(VK_LCONTROL) & GetAsyncKeyState(VK_RCONTROL))
        {
            INPUT click = { 0 };                                         // This creates an event that will be used to push out a command to the OS
            for (int i = 0; i <= ClickAmount; i++)                       // This loops until we reach the desired amount of clicks during this event
            {
                click.type = INPUT_MOUSE;                                // The input type is a mouse input.
                click.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;                 // Mouse input type is a mouse left button down
                SendInput(1, &click, sizeof(click));                     // Send the input over to the OS
                ZeroMemory(&click, sizeof(click));                       // Use this so there arent any input errors when we do a mouse up | removes all attributes that were previously set

                click.type = INPUT_MOUSE;                                // The input type is a mouse input.
                click.mi.dwFlags = MOUSEEVENTF_LEFTUP;                   // Mouse input type is a mouse left button up
                SendInput(1, &click, sizeof(click));                     // Send the input over to the OS
            }
        }
    }
}