# LMS-Library-Management-System
A library of books contains many books. Each book is stored in a text file in a given directory, which contains the library. Each book has a title, an author, a release date, and a Language. These can be read from the Project Gutenberg file header, see for example the novel Mobi Dick by Herman Hesse:
https://www.gutenberg.org/files/2701/2701-0.txt .<br />
The file header is given for reference.<br />
A book can contain many types of content, e.g. a novel, a play, etc. A novel can contain many chapters. Each chapter has a title followed by many paragraphs. Each paragraph contains many sentences, and each sentence is a sequence of words. A play has a optional prologue followed by many acts. Each act has many scenes, and each scene is a sequence of dialogues. Additionally, a play also has a list of characters or personae, where each dialogue is spoken by a character.
## The Software
This Library management system (LMS) manages all the books in a given directory. The program will start with a directory as input, and will manage the books in that directory. The LMS will maintain the type of each book in the library, in a file called “index.txt”. It should automatically detect all files in the directory and be able to detect the newly added books.<br />
The LMS has the following functionalities:
1. List all books along with their filename, title, and author name.
2. Search for a book by its title or author name, and show the matching books as a list. 
3. Display a book from any of the above two lists.

The LMS also performs the following analytic tasks:
1. If the type of the selected book is novel, given an input word, the LMS will be able to show the top 5 chapters, where this word appears most of the times.
2. If the type of the selected book is play, then given an input character, the LMS will be able to show a list of all other characters which appear in at least one scene with the input character.
