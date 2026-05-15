#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdio>

using namespace std;

class Book {
private:
    int bookId;
    string title;
    string author;
    bool issued;

public:
    Book(int id = 0, string t = "", string a = "", bool i = false) {
        bookId = id;
        title = t;
        author = a;
        issued = i;
    }

    void inputBookDetails() {
        cout << "Enter Book ID: ";
        cin >> bookId;

        cin.ignore();

        cout << "Enter Book Title: ";
        getline(cin, title);

        cout << "Enter Author Name: ";
        getline(cin, author);

        issued = false;
    }

    void displayBookDetails() const {
        cout << left << setw(10) << bookId
             << setw(30) << title
             << setw(25) << author
             << setw(15) << (issued ? "Issued" : "Available") << endl;
    }

    int getBookId() const {
        return bookId;
    }

    string getTitle() const {
        return title;
    }

    string getAuthor() const {
        return author;
    }

    bool isIssued() const {
        return issued;
    }

    void issueBook() {
        if (issued) {
            cout << "Book Already Issued!" << endl;
        }
        else {
            issued = true;
            cout << "Book Issued Successfully!" << endl;
        }
    }

    void returnBook() {
        if (!issued) {
            cout << "Book Was Not Issued!" << endl;
        }
        else {
            issued = false;
            cout << "Book Returned Successfully!" << endl;
        }
    }

    void writeToFile(ofstream &outFile) {
        outFile << bookId << endl;
        outFile << title << endl;
        outFile << author << endl;
        outFile << issued << endl;
    }

    void readFromFile(ifstream &inFile) {
        inFile >> bookId;
        inFile.ignore();

        getline(inFile, title);
        getline(inFile, author);

        inFile >> issued;
        inFile.ignore();
    }
};

void addBook() {
    Book b;

    ofstream outFile("library.txt", ios::app);

    if (!outFile) {
        cout << "File Error!" << endl;
        return;
    }

    b.inputBookDetails();
    b.writeToFile(outFile);

    outFile.close();

    cout << "\nBook Added Successfully!\n";
}

void displayBooks() {
    ifstream inFile("library.txt");

    if (!inFile) {
        cout << "No Records Found!" << endl;
        return;
    }

    Book b;

    cout << "\n================ LIBRARY RECORDS ================\n";

    cout << left << setw(10) << "BOOK ID"
         << setw(30) << "TITLE"
         << setw(25) << "AUTHOR"
         << setw(15) << "STATUS" << endl;

    cout << "--------------------------------------------------------------------------\n";

    while (inFile.peek() != EOF) {
        b.readFromFile(inFile);
        b.displayBookDetails();
    }

    inFile.close();
}

void searchBook() {
    string keyword;
    bool found = false;

    cin.ignore();

    cout << "Enter Book Title or Author: ";
    getline(cin, keyword);

    ifstream inFile("library.txt");

    if (!inFile) {
        cout << "File Error!" << endl;
        return;
    }

    Book b;

    while (inFile.peek() != EOF) {
        b.readFromFile(inFile);

        if (b.getTitle() == keyword || b.getAuthor() == keyword) {
            cout << "\nBook Found:\n";

            cout << left << setw(10) << "BOOK ID"
                 << setw(30) << "TITLE"
                 << setw(25) << "AUTHOR"
                 << setw(15) << "STATUS" << endl;

            cout << "--------------------------------------------------------------------------\n";

            b.displayBookDetails();
            found = true;
        }
    }

    if (!found) {
        cout << "Book Not Found!" << endl;
    }

    inFile.close();
}

void issueBook() {
    int id;
    bool found = false;

    cout << "Enter Book ID to Issue: ";
    cin >> id;

    ifstream inFile("library.txt");
    ofstream tempFile("temp.txt");

    if (!inFile || !tempFile) {
        cout << "File Error!" << endl;
        return;
    }

    Book b;

    while (inFile.peek() != EOF) {
        b.readFromFile(inFile);

        if (b.getBookId() == id) {
            b.issueBook();
            found = true;
        }

        b.writeToFile(tempFile);
    }

    inFile.close();
    tempFile.close();

    remove("library.txt");
    rename("temp.txt", "library.txt");

    if (!found) {
        cout << "Book Not Found!" << endl;
    }
}

void returnBook() {
    int id;
    bool found = false;

    cout << "Enter Book ID to Return: ";
    cin >> id;

    ifstream inFile("library.txt");
    ofstream tempFile("temp.txt");

    if (!inFile || !tempFile) {
        cout << "File Error!" << endl;
        return;
    }

    Book b;

    while (inFile.peek() != EOF) {
        b.readFromFile(inFile);

        if (b.getBookId() == id) {
            b.returnBook();
            found = true;
        }

        b.writeToFile(tempFile);
    }

    inFile.close();
    tempFile.close();

    remove("library.txt");
    rename("temp.txt", "library.txt");

    if (!found) {
        cout << "Book Not Found!" << endl;
    }
}

int main() {
    int choice;

    while (true) {
        cout << "\n=========== LIBRARY MANAGEMENT SYSTEM ===========\n";

        cout << "1. Add Book" << endl;
        cout << "2. Display Books" << endl;
        cout << "3. Search Book" << endl;
        cout << "4. Issue Book" << endl;
        cout << "5. Return Book" << endl;
        cout << "6. Exit" << endl << endl;

        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addBook();
            break;

        case 2:
            displayBooks();
            break;

        case 3:
            searchBook();
            break;

        case 4:
            issueBook();
            break;

        case 5:
            returnBook();
            break;

        case 6:
            cout << "Exiting Application..." << endl;
            return 0;

        default:
            cout << "Invalid Choice! Please Try Again." << endl;
        }
    }

    return 0;
}
