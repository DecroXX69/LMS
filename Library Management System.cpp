#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Book {
public:
    std::string title;
    std::string author;
    bool available;

    Book(const std::string& title, const std::string& author) : title(title), author(author), available(true) {}
};

class Library {
private:
    std::vector<Book> books;

public:
    void addBook(const std::string& title, const std::string& author) {
        books.emplace_back(title, author);
    }

    void viewBooks() const {
        std::cout << "Books in the library:" << std::endl;
        for (const auto& book : books) {
            std::cout << "Title: " << book.title << ", Author: " << book.author;
            if (book.available)
                std::cout << " (Available)";
            else
                std::cout << " (Borrowed)";
            std::cout << std::endl;
        }
    }

    void viewBorrowedBooks() const {
        std::cout << "Borrowed books:" << std::endl;
        bool borrowedBooksExist = false;

        for (const auto& book : books) {
            if (!book.available) {
                borrowedBooksExist = true;
                std::cout << "Title: " << book.title << ", Author: " << book.author << std::endl;
            }
        }

        if (!borrowedBooksExist)
            std::cout << "No books are currently borrowed." << std::endl;
    }

    void borrowBook(const std::string& title) {
        auto it = std::find_if(books.begin(), books.end(), [&title](const Book& book) {
            return book.title == title && book.available;
        });

        if (it != books.end()) {
            it->available = false;
            std::cout << "You have successfully borrowed the book: " << it->title << std::endl;
        } else {
            std::cout << "Book not found or not available for borrowing." << std::endl;
        }
    }

    void returnBook(const std::string& title) {
        auto it = std::find_if(books.begin(), books.end(), [&title](const Book& book) {
            return book.title == title && !book.available;
        });

        if (it != books.end()) {
            it->available = true;
            std::cout << "You have successfully returned the book: " << it->title << std::endl;
        } else {
            std::cout << "Book not found or already returned." << std::endl;
        }
    }

    void searchByAuthor(const std::string& author) const {
        std::cout << "Books by author " << author << ":" << std::endl;
        bool authorBooksExist = false;

        for (const auto& book : books) {
            if (book.author == author) {
                authorBooksExist = true;
                std::cout << "Title: " << book.title << std::endl;
            }
        }

        if (!authorBooksExist)
            std::cout << "No books found for the author." << std::endl;
    }
};

int main() {
    Library library;

    library.addBook("The Great Gatsby", "F. Scott Fitzgerald");
    library.addBook("To Kill a Mockingbird", "Harper Lee");
    library.addBook("1984", "George Orwell");
    library.addBook("Brave New World", "Aldous Huxley");

    int choice = -1;
    std::string userInput;

    while (choice != 0) {
        std::cout << "\nLibrary Management System" << std::endl;
        std::cout << "1. View Books" << std::endl;
        std::cout << "2. Borrow a Book" << std::endl;
        std::cout << "3. Return a Book" << std::endl;
        std::cout << "4. View Borrowed Books" << std::endl;
        std::cout << "5. Search Books by Author" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                library.viewBooks();
                break;

            case 2:
                std::cout << "Enter the title of the book you want to borrow: ";
                std::cin.ignore();
                std::getline(std::cin, userInput);
                library.borrowBook(userInput);
                break;

            case 3:
                std::cout << "Enter the title of the book you want to return: ";
                std::cin.ignore();
                std::getline(std::cin, userInput);
                library.returnBook(userInput);
                break;

            case 4:
                library.viewBorrowedBooks();
                break;

            case 5:
                std::cout << "Enter the author's name: ";
                std::cin.ignore();
                std::getline(std::cin, userInput);
                library.searchByAuthor(userInput);
                break;

            case 0:
                std::cout << "Exiting the program. Goodbye!" << std::endl;
                break;

            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    }

    return 0;
}
