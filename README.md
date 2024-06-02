# Key-Logger
DISCLAIMER: This project is for learning purposes only. I am strongly against anyone using this project for malicious intent.

If you wish to run this program at home scroll down until you see: How to run.

#How it works (chronologically)
  First the function hideConsole() is called to immediatley close the console as it opens, I used this method because this was ran on a console application not a windows application. Next an enum is created for visual purposes to tell wether the loop that grabs and logs keys is enabled or disabled. Then a message box pops up to let the user know the key logger is on, for security purposes. Two text files are then opened one to email at the end of the program.*Note this text file is erased and opened everytime the program starts. The other is to keep a log of the keys from each run of the program.*Note the file contents will never be erased because the file is being opened in append mode, hence ios::app.
  Now the loop is set to automaically start, with a for loop that runs through every possible ASCII character (1-255). Two bool variavbles are made to tell wether left shift and left control are currently pressed down. Which correlates to the if statement below. The shortcut to end the program is [left shift + left control]. If the first if statement is false the next if statement gets the key the user pressed and calls the function translateKey(int). This fucntion takes the integer GetAsyncKeyState returns and translates it into a key.
  


#How to run
