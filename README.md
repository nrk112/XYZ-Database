
XYZ Data Base Assignment
========================
You are going to make a corporate database
(sort of) program for the XYZ Company. The XYZ Company keeps all of its information in text files, but the employees often have a hard time finding the information that they need. 
They need a program that will index all of their text files so that when they need to find all occurrences of a given word. The program will tell the employees the text of the lines where the word is found and also the text file names and the line numbers where that word is mentioned.
The program will be implemented with a transducer. The program accepts only four commands CLEAR, ADD_FILE, FIND_WORD and QUIT. Optionally for extra credit you can implement the QUERY command.<br />
For example here are three of the text files that contain corporate information (actually poems by Robert Frost):

<h2>FIRE_AND_ICE.TXT</h2><br />
Some say the world will end in fire,<br />
Some say in ice.<br />
From what I've tasted of desire<br />
I hold with those who favour fire.<br />
But if it had to perish twice,<br />
I think I know enough of hate<br />
To say that for destruction ice<br />
Is also great<br />
And would suffice.<br />

<h2>THE_ROAD_NOT_TAKEN.TXT</h2><br />
Two roads diverged in a yellow wood,<br />
And sorry I could not travel both<br />
And be one traveler, long I stood<br />
And looked down one as far as I could<br />
To where it bent in the undergrowth;<br />
Then took the other, as just as fair,<br />
And having perhaps the better claim,<br />
Because it was grassy and wanted wear;<br />
Though as for that the passing there<br />
Had worn them really about the same,<br />
And both that morning equally lay<br />
In leaves no step had trodden black.<br />
Oh, I kept the first for another day!<br />
Yet knowing how way leads on to way,<br />
I doubted if I should ever come back.<br />
I shall be telling this with a sigh<br />
Somewhere ages and ages hence:<br />
Two roads diverged in a wood, and I-<br />
I took the one less traveled by,<br />
And that has made all the difference.<br />

<h2>NOTHING_GOLD_CAN_STAY.TXT</h2><br />
Nature's first green is gold,<br />
Her hardest hue to hold.<br />
Her early leaf's a flower;<br />
But only so an hour.<br />
Then leaf subsides to leaf.<br />
So Eden sank to grief,<br />
So dawn goes down to day.<br />
Nothing gold can stay.<br />

The information in these text files would be added to the corporate data base with the following three commands:<br />
ADD_FILE FIRE_AND_ICE.TXT<br />
ADD_FILE THE_ROAD_NOT_TAKEN.TXT<br />
ADD_FILE NOTHING_GOLD_CAN_STAY.TXT<br />

When the FIND_WORD word command is given the system will report the lines of text which contain that line and also the source of that line of text.
For example, the command:<br />
FIND_WORD is<br />
Will cause the following to be displayed on the screen:<br />

Is also great<br />
FIRE_AND_ICE.TXT [8]<br />

Nature's first green is gold,<br />
NOTHING_GOLD_CAN_STAY.TXT [1]<br />

And the command:<br />
FIND_WORD day<br />
Will cause the following to be displayed on the screen:<br />

Oh, I kept the first for another day!<br />
THE_ROAD_NOT_TAKEN.TXT [13]<br />

So dawn goes down to day.<br />
NOTHING_GOLD_CAN_STAY.TXT [7]<br />

If a word occurs more than one time in the same line it will only be displayed once.<br />
The FIND_WORD command is not case sensitive. The system will be implemented by keeping a linked list of "Lines". Each "Line" will include a string of the actual text of the line and string of the filename where it originated and the integer line number within the file of origin. The index will be managed by a BST (Binary Search Tree) of "Words" each "Word" will consist of a string with the word in it and a pointer to the "Line" where the word was found. 
Only alphabetic characters A - Z and a - z and the apostrophe will be included in words. Any other character (including blanks, punctuation, numbers, carriage returns and line feeds) will not be added to the index and will serve as the separators between the indexed words. 
The database will be persistent. This means that when you run the program it automatically starts up with the data base that was in the system the last time it ran. All input can be assumed to be correct. <br />
The QUERY command is optional (MAJOR EXTRA CREDIT!) and will work using STL sets and an S - Expression tree. More details on this subject will be given in class.<br />
QUERY recognizes expressions which include parentheses, various operators, and keywords.

For example the following command:<br />
QUERY ( ( ( (north) & (pole) ) | ( (santa) & (clause) ) ) & (christmas) )<br />
Would display (like the FIND_WORD command) every line that included the word "christmas" and the words "north" and "pole". It would also display all the lines that include the word "christmas" and the words "santa" and "clause".

==========================================================================
Homework assignment 3 for COP3530 Data Structures &amp; Algorithm Analysis
