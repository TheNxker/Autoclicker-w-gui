#include <SFML/Graphics.hpp>                                                  // SFML is the graphics processor, look at the official website to learn how to install
#include <iostream>                                                           // Main stuff for CPP
#include <Windows.h>                                                          // This helps me use inputs
#include "CustomItems.h"                                                      // SFML practically only does text and shapes, but its very good at it, so here im going to draw a button thing.

using namespace sf;

                                                                              // MAIN KEYBINDS
                                                                              // LCTRL + ESC     | CLOSES PROGRAM
                                                                              // LCTRL + RCTRL   | STARTS CLICKING

int ClickAmount          = 10;                                                // 10 clicks per event!!! | 10 Comes out to about 46.2 clicks per second
INPUT click              = { 0 };                                             // This creates an event that will be used to push out a command to the OS
bool AutoClickingToggled = false;                                             // Make sure the user can do other stuff while the mouse is "clicking"

int AutoClick()
{
    Sleep(50);                                                                // Allows up to 20 events per second.
    for (int i = 0; i <= ClickAmount; i++)                                    // This loops until we reach the desired amount of clicks during this event
    {
        click.type = INPUT_MOUSE;                                             // The input type is a mouse input.
        click.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;                              // Mouse input type is a mouse left button down
        SendInput(1, &click, sizeof(click));                                  // Send the input over to the OS
        ZeroMemory(&click, sizeof(click));                                    // Use this so there arent any input errors when we do a mouse up | removes all attributes that were previously set

        click.type = INPUT_MOUSE;                                             // The input type is a mouse input.
        click.mi.dwFlags = MOUSEEVENTF_LEFTUP;                                // Mouse input type is a mouse left button up
        SendInput(1, &click, sizeof(click));                                  // Send the input over to the OS
    }

    return 0;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 200), "Autoclicker");

    Font font;
    if (!font.loadFromFile("resource\\FacultyGlyphic-Regular.ttf"))
    {
        std::cerr << "Cant find the font file!!";
    }

    Text keybinds;                                                           // Keybinds text
    keybinds.setFont(font);
    keybinds.setString("Autoclick || LCTRL + RCTRL\n" 
                       "Exit            || LCTRL + ESC");                    // Probably gonna make a whole system for this
    keybinds.setCharacterSize(24);
    keybinds.setFillColor(Color::Black);
    keybinds.setOrigin(Vector2f(keybinds.getLocalBounds().getSize().x/2,     // Set the part of the text which gets moved to the center of the object.
        keybinds.getLocalBounds().getSize().y / 2));
    keybinds.setPosition(window.getSize().x / 2, window.getSize().y / 2);


    while (window.isOpen())
    {
        if (GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(VK_ESCAPE))    // Close window command
        {
            window.close();
        }
        if (GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(VK_RCONTROL))  // Toggle autoclicking command
        {
            AutoClickingToggled = !AutoClickingToggled;
        }
        if (AutoClickingToggled)
        {
            AutoClick();
        }

        sf::Event event;                                                     // Event handling service for SFML, try not to use their keyboard service, its subpar  compared to Windows.h

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();                                              // Does anyone know why we need to even program in an option for closing this? Serious malware potential my man.
            }
        }

        window.clear(Color::White);
                                                                             // VV Make sure to put everything you want to draw down here  VV
        window.draw(keybinds);
                                                                             // ^^ Also make sure to put everything out want to draw above ^^
        window.display();
    }
    return 0;
}