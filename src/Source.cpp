#include <SFML/Graphics.hpp>                                                  // SFML is the graphics processor, look at the official website to learn how to install
#include <iostream>                                                           // Main stuff for CPP
#include <Windows.h>                                                          // This helps me use inputs
#include "CustomItems.h"                                                      // SFML practically only does text and shapes, but its very good at it, so here im going to draw a button thing.
#include <thread>                                                             // So we can open other windows without the program getting confused

using namespace sf;

                                                                              // MAIN KEYBINDS
                                                                              // LCTRL + ESC     | CLOSES PROGRAM
                                                                              // LCTRL + RCTRL   | STARTS CLICKING

int ClickAmount          = 10;                                                // 10 clicks per event!!! | 10 Comes out to about 46.2 clicks per second
INPUT click              = { 0 };                                             // This creates an event that will be used to push out a command to the OS
bool AutoClickingToggled = false;                                             // Make sure the user can do other stuff while the mouse is "clicking"
bool BtnDown             = false;                                             // I don't want it to be repeatadly sending outputs.
                                                                              // VK_[instertkeyhere] and 0x12 are both numbers, only difference is one is an ENUM, which is basically a variable that turns text into numbers
int closeKey1            = VK_LCONTROL;                                       // Key 1 would be something like ctrl
int closeKey2            = VK_ESCAPE;                                         // Key 2 would be something like esc

int autoClickKey1        = VK_LCONTROL;                                       // Key 1 would be something like ctrl
int autoClickKey2        = VK_RCONTROL;                                       // Key 2 would be something like ctrl

void AutoClick()
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
}

void initKeybinds(sf::RenderWindow& target)
{
    if (GetAsyncKeyState(closeKey1) && GetAsyncKeyState(closeKey2) || GetAsyncKeyState(closeKey2) && GetAsyncKeyState(closeKey1))           // Close window command
    {
        target.close();
    }
    if (GetAsyncKeyState(autoClickKey1) && GetAsyncKeyState(autoClickKey2) || GetAsyncKeyState(autoClickKey2) && GetAsyncKeyState(autoClickKey1))   // Toggle autoclicking command
    {
        AutoClickingToggled = !AutoClickingToggled;
    }
}

void changeCloseKey1()
{
    bool on = true;
    while (on)
    {
        for (int keyCode = 1; keyCode < 256; ++keyCode) {
            // Check if the key with keyCode is currently
            // pressed
            if (GetAsyncKeyState(keyCode) & 0x8000) {
                // Convert the key code to ASCII character
                char keyChar = static_cast<char>(keyCode);
                closeKey1 = keyChar;
                on = false;
                std::cout << "due to keypress " << keyChar << " " << keyCode << "\n";
                break;
            }
        }
        Sleep(100);
    }
}

void changeCloseKey2()
{
    bool on = true;
    while (on)
    {
        for (int keyCode = 1; keyCode < 256; ++keyCode) {
            // Check if the key with keyCode is currently
            // pressed
            if (GetAsyncKeyState(keyCode) & 0x8000) {
                // Convert the key code to ASCII character
                char keyChar = static_cast<char>(keyCode);
                closeKey2 = keyChar;
                on = false;
                std::cout << "due to keypress " << keyChar << " " << keyCode << "\n";
                break;
            }
        }
        Sleep(100);
    }
}

void changeAutoClickKey1()
{
   bool on = true;
    while (on)
    {
        for (int keyCode = 1; keyCode < 256; ++keyCode) {
            // Check if the key with keyCode is currently
            // pressed
            if (GetAsyncKeyState(keyCode) & 0x8000) {
                // Convert the key code to ASCII character
                char keyChar = static_cast<char>(keyCode);
                autoClickKey1 = keyChar;
                on = false;
                std::cout << "due to keypress " << keyChar << " " << keyCode << "\n";
                break;
            }
        }
        Sleep(100);
    }
}

void changeAutoClickKey2()
{
    bool on = true;
    while (on)
    {
        for (int keyCode = 1; keyCode < 256; ++keyCode) {
            // Check if the key with keyCode is currently
            // pressed
            if (GetAsyncKeyState(keyCode) & 0x8000) {
                // Convert the key code to ASCII character
                char keyChar = static_cast<char>(keyCode);
                autoClickKey2 = keyChar;
                on = false;
                std::cout << "due to keypress " << keyChar << " " << keyCode << "\n";
                break;
            }
        }
        Sleep(100);
    }
}

void editKeybinds()
{
    sf::RenderWindow keyWindow(sf::VideoMode(400,200), "Change Keybinds...");
                                                                              // Change first keybind

    Button nextBind("Next bind");
    keyWindow.setActive();
    bool changingBinds = true;
    int currentBind = 1;
    bool BindBtnDown = false;
    std::thread changeBind;
    while (keyWindow.isOpen())
    {
        Event e;
        while(keyWindow.pollEvent(e))
        {
            if (e.type == Event::Closed)
            {
                keyWindow.close();
            }
        }
        nextBind.Update(keyWindow);
        

                                                                              // Ty Geeks for Geeks <3
        if (nextBind.isPressed() && !BindBtnDown)
        {
            BindBtnDown = true;
        }
        else if (!nextBind.isPressed() && BindBtnDown)
        {
            BindBtnDown = false;
            switch (currentBind)
            {
            case 1:
                changeBind = std::thread(changeCloseKey1);
                changeBind.join();
                currentBind ++;
                break;
            case 2:
                changeBind = std::thread(changeCloseKey2);
                changeBind.join();
                currentBind ++;
                break;
            case 3:
                changeBind = std::thread(changeAutoClickKey1);
                changeBind.join();
                currentBind ++;
                break;
            case 4:
                changeBind = std::thread(changeAutoClickKey2);
                changeBind.join();
                changingBinds = false;
                currentBind = 1;
                keyWindow.close();
                break;
            }
        }
        keyWindow.clear(Color::White);
        nextBind.Render(keyWindow);
        keyWindow.display();
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 200), "Autoclicker");

    Font font;
    if (!font.loadFromFile("resource/FacultyGlyphic-Regular.ttf"))
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


    // std::vector<Button*> edit;
    // edit.push_back(new Button("Edit Keybinds"));
    Button btn1("Edit");                                                     // Wasted 2 hours of my life making this function, and maybe even more to come.. WHY TF DOESNT SFML HAVE BUTTONS!!!
    btn1.setPosition(Vector2f((window.getSize().x / 2) , (window.getSize().y / 2)+35.f));
 
    while (window.isOpen())
    {
        initKeybinds(window);
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

        btn1.Update(window);
        if (btn1.isPressed() && BtnDown == false)
        {
            BtnDown = true;
        }
        else if (BtnDown == true && !btn1.isPressed())
        {
            std::thread thing(editKeybinds);
            thing.join();
            BtnDown = false;
        }

        window.clear(Color::White);
                                                                             // VV Make sure to put everything you want to draw down here  VV
        window.draw(keybinds);
        btn1.Render(window);
                                                                             // ^^ Also make sure to put everything out want to draw above ^^
        window.display();
    }
    return 0;
}



Button::Button(std::string words)
{
	this->coloridle = sf::Color(200,200,200,255);
	this->colorhover = sf::Color(100,100,100,255);
	this->colorpress = sf::Color(0,0,0,0);
	this->font.loadFromFile("resource/FacultyGlyphic-Regular.ttf");
	this->text.setFont(font);
	this->text.setFillColor(colorpress);
	this->text.setCharacterSize(16);
	this->text.setString(words);
	this->buttonstate = IDLE;
	this->shape.setSize(sf::Vector2f(100.f,50.f));
	this->text.setFillColor(sf::Color::Black);
	this->text.setOrigin(sf::Vector2f(this->text.getLocalBounds().getSize().x/2, this->text.getLocalBounds().getSize().y/2));
	this->text.setPosition(sf::Vector2f(this->shape.getSize().x / 2, this->shape.getSize().y / 2));
}

Button::~Button()
{
}

const bool Button::isPressed()
{
    if (this->buttonstate == PRESSED)
    {
        return true;
    }
    else
    {
        return false;
    }
}

const bool Button::isHover()
{
	if (this->buttonstate == HOVER)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Button::Update(const sf::RenderWindow& window)
{
	sf::Vector2f mousePosView = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	if (this->shape.getGlobalBounds().contains(mousePosView))
	{
		this->shape.setFillColor(this->colorhover);
		this->buttonstate = HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->shape.setFillColor(this->colorpress);
			this->buttonstate = PRESSED;
		}
	}
	else
	{
		this->shape.setFillColor(this->coloridle);
		this->buttonstate = IDLE;
	}
}

void Button::Render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}

void Button::setPosition(sf::Vector2f pos)
{
	this->shape.setPosition(pos);
	this->text.move(pos);
}

void Button::setOrigin(sf::Vector2f origin)
{
	this->shape.setOrigin(origin);
}