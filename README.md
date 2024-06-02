# Key-Logger
***DISCLAIMER: This project is for learning purposes only. I am strongly against anyone using this project for malicious intent.***

If you wish to run this program at home scroll to: How to run.

## How it works (chronologically)
  First, the function hideConsole() is called to immediatley close the console as it opens, I used this method because this was running on a console application, not a Windows application. Next, an enum is created for visual purposes to tell whether the loop that grabs and logs keys is enabled or disabled. Then a message box pops up to let the user know the key logger is on, for security purposes. Two text files are then opened one to email at the end of the program.**Note** this text file is erased and opened every time the program starts. The other is to keep a log of the keys from each run of the program.**Note** the file contents will never be erased because the file is being opened in append mode, hence ios::app.
  Now the loop is set to automatically start, with a for loop that runs through every possible ASCII character (1-255). Two bool variables are made to tell whether left shift and left control are currently pressed down. Which correlates to the if statement below. The shortcut to end the program is [left shift + left control]. If the first if statement is false the next if statement gets the key the user pressed and calls the function translateKey(int). This function takes the integer GetAsyncKeyState returns and translates it into a key. The picture below represents the keys translateKey(int) can return:

![keyboardLayout](https://github.com/Julian-Cto/Key-Logger/assets/166642280/c4cfac10-3687-4ce1-a73c-096df6f945ec)

In the same line logKey(string) is called to write the translated key into the email and history text file.

Once the loop ends a marker for the end of input for that session is written to both files. A second message box is displayed to indicate key logging is off. The next six lines of code prepare the subject in the email by calling GetCompterName to retrieve the name of the computer the program is running on. Finally, an email object is made to prepare the email and then sent with the text file attached.
 
## How to run
**note this tutorial is for Visual Studios, if you wish to use a different compiler you need to integrate the windows.h files**

The instructions to run this code are below:

This program uses two external libraries windows.h and curl.h. Windows.h is already integrated into Visual Studios and I’ve attached the curl.h files in the repo and I integrated the files into the Email.h file. 
**note this program runs best in x64 debug** to run in different modes use [this](https://www.youtube.com/watch?v=q_mXVZ6VJs4&t=790s) tutorial. (I used method #1 9:50)

We will be editing the following files: **Email.cpp** and **keyLogger.cpp**

### Email.cpp

On line 50 and 51, Optional you can change “anyname” to the name you’d like the file to send as in the email. It can be different than the name of the file you are sending.

### keyLogger.cpp

On line 25, Optional “ANYNAME” is the name of the window that pops up to indicate the key logger is on.

On line 27, Required "emailfilename” replace this with the name of the text file you’d like to email at the end.

On line 28, Required "Histroyfilename” replace this with the name of the text file you’d like to keep the history on.
 
On line 53, Optional (same as line 25)

On line 63, Required "From" replace this with the name you’d like to send the email under, "TOname@domain.com" replace this with the email you’d like to send to, subject pre-set if you’d like to replace it you can edit it in the parameter as so: “any Subject”, "Body" replace with the desired text you’d like in the body.

On line 64, Required "smtp://smtp.domain.com:587" replace with your domain ex. "smtp://smtp.gmail.com:587" you could also replace 587 with your desired port if needed, “username” and “password” follow [this](https://support.google.com/mail/answer/185833?hl=en) tutorial for Gmail, "filename.txt" replace with the text file you’d like to attach which should be the same file on line 27.
