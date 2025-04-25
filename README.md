# Library Book Sorting System

This repository contains two main files. The first is a C++ header file, which includes definitions and functions for nodes and an AVL self-balancing binary tree. These are specifically made for allowing a system which allows the user to use CRUD operations in reference to books, allowing creation, reading, updating, and deletion via title or author. The second file is a .cpp file which contains a menu that provide better readability and allows use of the system properly, as an example of how one would use this. It contains no book data by default, but the user can easily add it with the menu. 

## Prerequisites

The only requirements for this program is Visual Studio, XCode, or similar software which can run the C++ code that makes up the main repository. 

### Visual Studio Download Link
https://visualstudio.microsoft.com/

### XCode Download Link
https://developer.apple.com/xcode/

## How to Run the Program

The menu allows five choices, selected by typing the number associated with each. These consist of: Insert, Update, Delete, Search, and Exit. Insert allows the user to type in the book title and author name. Update allows a previously entered entry to be modified. Delete allows an existing entry to be removed from the system. Search allows the user to find any book that includes the keyword if it is contained in the title or author's name. Exit will close the program.

1. Download the "LibrarySortingSystem.cpp" and "LibraryAVLTree.h" files.
2. Open the program in your code editor of choice.
3. Run the program
4. Press '1', then type the book title and press 'Enter', followed by the author's name, and 'Enter' once more. The program will then state you have successfully entered a book into the system.
5. Enter another number for your choice, and follow menu instructions. The format is typically the same as for inserting a new entry. Note that entering an incorrect entry when searching, deleting, or updating will cause the operation to fail.
7. When you are ready to end the program, navigate to the menu and press '5' to exit.

### Build Information
Written by Lake Haverlock using Visual Studio 2022.
