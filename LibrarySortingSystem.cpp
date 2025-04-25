#include <iostream>
#include <iomanip>
#include <string>
#include "LibraryAVLTree.h"

using namespace std;

//Displays a menu for user choices
void displayMenu()
{
    cout << "\n Library System Menu: \n";
    cout << "1. Insert a book \n";
    cout << "2. Update a book \n";
    cout << "3. Delete a book \n";
    cout << "4. Search for a book \n";
    cout << "5. Exit \n";
    cout << "Enter your choice: ";
}

int main()
{
    //Creates the AVL tree
    AVLTree<Book> library;
    int choice;

    //Displays the menu on startup and after each function has finished
    do
    {
        displayMenu();
        cin >> choice;

        //Clears leftover newline from input buffer
        cin.ignore();

        string title, author, newTitle, newAuthor;

        //Runs the different user choices
        switch (choice)
        {
        //Allows user to insert a new book
        case 1:
            cout << "Enter book title: ";
            getline(cin, title);

            cout << "Enter author name: ";
            getline(cin, author);

            library.insert(Book(title, author));
            cout << "Book inserted successfully! \n";
            break;

        //Allows user to update an existing book
        //If the book does not exist, fails to update.
        case 2:
            cout << "Enter the title of the book to update: ";
            getline(cin, title);

            cout << "Enter the author of the book to update: ";
            getline(cin, author);

            if (!library.exists(Book(title, author))) {
                cout << "Book not found. Update canceled. \n";
                break;
            }

            cout << "Enter the new title: ";
            getline(cin, newTitle);

            cout << "Enter the new author: ";
            getline(cin, newAuthor);

            library.update(Book(title, author), Book(newTitle, newAuthor));
            break;

        //Allows user to delete an existing book
        case 3:
            cout << "Enter book title to delete: ";
            getline(cin, title);

            cout << "Enter author name: ";
            getline(cin, author);

            library.remove(Book(title, author));
            break;

        //Allows user to search for an existing book
        case 4:
            cout << "Enter a title or author keyword to search: ";
            getline(cin, title);

            library.search(title);
            break;

        //Exits the program
        case 5:
            cout << "Exiting the program. Goodbye! \n";
            break;

        //Returns to menu if invalid input entered
        default:
            cout << "Invalid choice, please try again. \n";
        }
    } while (choice != 5);

    return 0;
}