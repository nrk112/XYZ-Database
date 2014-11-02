
XYZ Data Base Assignment
========================
You are going to make a corporate database
(sort of) program for the XYZ Company. The XYZ Company keeps all of its information in text files, but the employees often have a hard time finding the information that they need. 
They need a program that will index all of their text files so that when they need to find all occurrences of a given word. The program will tell the employees the text of the lines where the word is found and also the text file names and the line numbers where that word is mentioned.
The program will be implemented with a transducer. The program accepts only four commands CLEAR, ADD_FILE, FIND_WORD and QUIT. Optionally for extra credit you can implement the QUERY command.
For example here are three of the text files that contain corporate information (actually poems by Robert Frost):

FIRE_AND_ICE.TXT
Some say the world will end in fire,
Some say in ice.
From what I've tasted of desire
I hold with those who favour fire.
But if it had to perish twice,
I think I know enough of hate
To say that for destruction ice
Is also great
And would suffice.

THE_ROAD_NOT_TAKEN.TXT
Two roads diverged in a yellow wood,
And sorry I could not travel both
And be one traveler, long I stood
And looked down one as far as I could
To where it bent in the undergrowth;
Then took the other, as just as fair,
And having perhaps the better claim,
Because it was grassy and wanted wear;
Though as for that the passing there
Had worn them really about the same,
And both that morning equally lay
In leaves no step had trodden black.
Oh, I kept the first for another day!
Yet knowing how way leads on to way,
I doubted if I should ever come back.
I shall be telling this with a sigh
Somewhere ages and ages hence:
Two roads diverged in a wood, and I-
I took the one less traveled by,
And that has made all the difference.

NOTHING_GOLD_CAN_STAY.TXT
Nature's first green is gold,
Her hardest hue to hold.
Her early leaf's a flower;
But only so an hour.
Then leaf subsides to leaf.
So Eden sank to grief,
So dawn goes down to day.
Nothing gold can stay.


The information in these text files would be added to the corporate data base with the following three commands:
ADD_FILE FIRE_AND_ICE.TXT
ADD_FILE THE_ROAD_NOT_TAKEN.TXT
ADD_FILE NOTHING_GOLD_CAN_STAY.TXT

When the FIND_WORD word command is given the system will report the lines of text which contain that line and also the source of that line of text.
For example, the command:
FIND_WORD is
Will cause the following to be displayed on the screen:

Is also great
FIRE_AND_ICE.TXT [8]

Nature's first green is gold,
NOTHING_GOLD_CAN_STAY.TXT [1]

And the command:
FIND_WORD day
Will cause the following to be displayed on the screen:

Oh, I kept the first for another day!
THE_ROAD_NOT_TAKEN.TXT [13]

So dawn goes down to day.
NOTHING_GOLD_CAN_STAY.TXT [7]

If a word occurs more than one time in the same line it will only be displayed once.
The FIND_WORD command is not case sensitive. The system will be implemented by keeping a linked list of "Lines". Each "Line" will include a string of the actual text of the line and string of the filename where it originated and the integer line number within the file of origin. The index will be managed by a BST (Binary Search Tree) of "Words" each "Word" will consist of a string with the word in it and a pointer to the "Line" where the word was found. 
Only alphabetic characters A - Z and a - z and the apostrophe will be included in words. Any other character (including blanks, punctuation, numbers, carriage returns and line feeds) will not be added to the index and will serve as the separators between the indexed words. 
The database will be persistent. This means that when you run the program it automatically starts up with the data base that was in the system the last time it ran. All input can be assumed to be correct. 
The QUERY command is optional (MAJOR EXTRA CREDIT!) and will work using STL sets and an S - Expression tree. More details on this subject will be given in class.
QUERY recognizes expressions which include parentheses, various operators, and keywords.

For example the following command:
QUERY ( ( ( (north) & (pole) ) | ( (santa) & (clause) ) ) & (christmas) )
Would display (like the FIND_WORD command) every line that included the word "christmas" and the words "north" and "pole". It would also display all the lines that include the word "christmas" and the words "santa" and "clause".

==========================================================================
Homework assignment 3 for COP3530 Data Structures &amp; Algorithm Analysis
