#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

vector<vector<string> > temp_data;
vector<string> toupdate;

void readfile(string fname) {
    vector<string> row;
    string line, word;

    fstream file(fname, ios::in);
    if (file.is_open()) {
        while (getline(file, line)) {
            row.clear();
            stringstream str(line);
            while (getline(str, word, ',')) row.push_back(word);
            temp_data.push_back(row);
        }
    } else {
        cout << "Could not open the file\n";
    }
}

void writefile(vector<vector<string> > par, string fname) {
    fstream fout(fname, ios::out);
    for (auto x : par) {
        for (auto y : x) {
            fout << y;
            if (y != x.back()) fout << ",";
        }
        fout << "\n";
    }
}

void writefileappend(vector<string> par, string fname) {
    fstream fout(fname, ios::out | ios::app);
    for (auto x : par) {
        fout << x;
        if (x != par.back()) fout << ",";
    }
    fout << "\n";
}

void printdata(vector<vector<string> > par) {
    int c = 1;
    for (auto x : par) {
        cout << c << ". ";
        for (auto y : x) {
            cout << y;
            if (y != x.back()) cout << " | ";
        }
        c++;
        cout << "\n";
    }
}

void printdata_notpassword(vector<vector<string> > par) {
    int c = 1;
    for (auto x : par) {
        cout << c << ". ";
        cout << x[0] << " | " << x[1] << " | " << x[3] << '\n';
        c++;
    }
}

class User {
private:
    string password;

public:
    string name;
    string id;
    vector<string> isbns_issued;
    void display_menu();
    void login();
    void see_all_books(string id);
    void see_issued_books(string id);
    void logout();
    void issue_book(string id, string bookname, string type_user);
    void return_book(string id, string isbncode);
    void check_available(string id, string bookname);
    int calc_fine(string id, string type_user);
    void clear_fine_amount(string id, string type_user);
    void User_add(string id);
    void User_update(string id);
    void User_delete(string id);
    void User_search(string id);
    void add_to_history(string id, string bookname, string isbn, time_t issue_time, time_t return_time);
    bool has_unpaid_fines(string id, string type_user);
};

class Book {
public:
    string title;
    string author;
    string isbn;
    string publication;
    int is_issued;
    void Book_request(string id, string bookname, string type_user);
    void Show_duedate(string isbn_no);
    void Book_add(string id);
    void Book_update(string id);
    void Book_delete(string id);
    void Book_search(string id);
};

class Student : public User {
public:
    int Fine_amount;
    void display_student_menu(string id);
};

class Professor : public User {
public:
    int Fine_amount;
    void display_prof_menu(string id);
};

class Librarian : public User {
public:
    void display_lib_menu(string id);
    void see_all_users(string id);
    void see_all_books(string id);
    void add_user(string id);
    void view_borrowing_history(string id);
    void update_user(string id);
    void delete_user(string id);
    void add_book(string id);
    void update_book(string id);
    void delete_book(string id);
    // void see_issued_to_user(string id, string uid);
    // void see_issued_book(string id, string isbn);
};

void Student::display_student_menu(string id) {
    cout << "---------------------------------------------------------------------\n";
    cout << "\nWelcome "<<id<<",You have been logged in as Student\n";
    cout << "Press 1 to see all the books\n";
    cout << "Press 2 to view books issued by you\n";
    cout << "Press 3 to check if a book is available for issue or not\n";
    cout << "Press 4 to view the fine\n";
    cout << "Press 5 to issue a book\n";
    cout << "Press 6 to return a book\n";
    cout << "Press 7 to clear your fine\n";
    cout << "Press 8 to logout\n";
    cout << "---------------------------------------------------------------------\n";
    char c;
    cin >> c;
    string book_name, isbncode;
    Student s;
    Book b;
    switch (c) {
        case '1':
            s.see_all_books(id);
            s.display_student_menu(id);
            break;
        case '2':
            s.see_issued_books(id);
            s.display_student_menu(id);
            break;
        case '3':
            cout << "Enter the name of the book you want to check: ";
            cin.ignore();
            getline(cin, book_name);
            s.check_available(id, book_name);
            s.display_student_menu(id);
            break;
        case '4':
            s.calc_fine(id, "1");
            s.display_student_menu(id);
            break;
        case '5':
            cout << "Enter the name of the book you want to issue: ";
            cin.ignore();
            getline(cin, book_name);
            b.Book_request(id, book_name, "1");
            s.display_student_menu(id);
            break;
        case '6':
            cout << "Enter the isbn code of the book you want to return: ";
            cin >> isbncode;
            s.return_book(id, isbncode);
            s.display_student_menu(id);
            break;
        case '7':
            s.clear_fine_amount(id, "1");
            s.display_student_menu(id);
            break;
        case '8':
            logout();
            break;
    }
}

void Professor::display_prof_menu(string id) {
    cout << "---------------------------------------------------------------------\n";
    cout << "\nYou have been logged in as Professor\n";
    cout << "Press 1 to see all the books\n";
    cout << "Press 2 to view books issued by you\n";
    cout << "Press 3 to check if a book is available for issue or not\n";
    cout << "Press 4 to view the fine\n";
    cout << "Press 5 to issue a book\n";
    cout << "Press 6 to return a book\n";
    cout << "Press 7 to clear your fine\n";
    cout << "Press 8 to logout\n";
    cout << "---------------------------------------------------------------------\n";
    char c;
    cin >> c;
    string book_name, isbncode;
    Professor s;
    Book b;
    switch (c) {
        case '1':
            s.see_all_books(id);
            s.display_prof_menu(id);
            break;
        case '2':
            s.see_issued_books(id);
            s.display_prof_menu(id);
            break;
        case '3':
            cout << "Enter the name of the book you want to check: ";
            cin.ignore();
            getline(cin, book_name);
            s.check_available(id, book_name);
            s.display_prof_menu(id);
            break;
        case '4':
            s.calc_fine(id, "2");
            s.display_prof_menu(id);
            break;
        case '5':
            cout << "Enter the name of the book you want to issue: ";
            cin.ignore();
            getline(cin, book_name);
            b.Book_request(id, book_name, "2");
            s.display_prof_menu(id);
            break;
        case '6':
            cout << "Enter the isbn code of the book you want to return: ";
            cin >> isbncode;
            s.return_book(id, isbncode);
            s.display_prof_menu(id);
            break;
        case '7':
            s.clear_fine_amount(id, "2");
            s.display_prof_menu(id);
            break;
        case '8':
            logout();
            break;
    }
}

void User::display_menu() {
    char c;
    cout << "---------------------------------------------------------------------\n";
    cout << "\n\nWelcome to the library management system!\n\n";
    cout << "1. Press 1 to log in: \n";
    cout << "2. Press 2 to exit\n";
    cout << "---------------------------------------------------------------------\n";
    cin >> c;
    if (c == '1') {
        User u;
        u.login();
    } else {
        cout << "Thanks for using the system!";
        exit(1);
    }
}


void User::login() {
    string id, password;
    cout << "Enter your id: ";
    cin >> id;
    cout << "Enter the password: ";
    cin >> password;
    vector<string> words_in_a_row;
    string line_in_csv, word;
    fstream file("all_users_data.csv", ios::in);
    int count = 0;
    if (file.is_open()) {
        while (getline(file, line_in_csv)) {
            words_in_a_row.clear();
            stringstream str(line_in_csv);
            while (getline(str, word, ',')) words_in_a_row.push_back(word);
            if (words_in_a_row[1] == id) {
                count = 1;
                if (words_in_a_row[2] == password) {
                    count++;
                    break;
                } else {
                    while (password != words_in_a_row[2]) {
                        cout << "You entered the wrong password. Press 1 to reenter the password and 2 to exit\n";
                        char c;
                        cin >> c;
                        if (c == '1') {
                            cout << "Enter the password: ";
                            cin >> password;
                            if (password == words_in_a_row[2]) count++;
                        } else if (c == '2') {
                            cout << "Exiting...";
                            return;
                        } else {
                            cout << "Please enter a valid input.\n";
                        }
                    }
                    if (count == 2) break;
                }
            }
            if (count == 2) break;
        }
        if (count == 0) {
            cout << "User not found\n";
            User u;
            u.display_menu();
        }
        if (count == 2) {
            Student s;
            Professor p;
            Librarian l;

            if (words_in_a_row[3] == "1") {
                s.display_student_menu(words_in_a_row[1]);
            } else if (words_in_a_row[3] == "2") {
                p.display_prof_menu(words_in_a_row[1]);
            } else {
                l.display_lib_menu(words_in_a_row[1]);
            }
        }
    }
}

void User::see_all_books(string id) {
    temp_data.clear();
    cout << "In the data below, 0 signifies that the book is not issued and 1 means that the book is issued.\n";
    readfile("all_books_data.csv");
    printdata(temp_data);
    temp_data.clear();
}

void User::issue_book(string id, string bookname, string type_user) {
    temp_data.clear();
    int fl = 0;
    if (type_user == "1") {
        int count = 0;
        temp_data.clear();
        readfile("issued_books_data.csv");
        for (int i = 0; i < temp_data.size(); i++) {
            if (temp_data[i][0] == id) {
                count++;
            }
        }
        temp_data.clear();
        if (count > 4) {
            cout << "You can't issue more than 5 books!\n\n";
        } else {
            readfile("all_books_data.csv");
            for (int i = 0; i < temp_data.size(); i++) {
                if (temp_data[i][0] == bookname && temp_data[i][4] == "0") {
                    fl = 1;
                    cout << "Book is available!\n";
                    temp_data[i][4] = "1";
                    toupdate.clear();
                    toupdate.push_back(id);
                    toupdate.push_back(bookname);
                    toupdate.push_back(temp_data[i][2]);
                    toupdate.push_back(to_string(time(0)));
                    writefileappend(toupdate, "issued_books_data.csv");
                    cout << "Book successfully issued\n";
                    break;
                }
            }
            if (fl == 0) cout << "Book not available\n";
            writefile(temp_data, "all_books_data.csv");
            temp_data.clear();
        }
    }
    if (type_user == "2") {
        readfile("all_books_data.csv");
        for (int i = 0; i < temp_data.size(); i++) {
            if (temp_data[i][0] == bookname && temp_data[i][4] == "0") {
                fl = 1;
                cout << "Book is available!\n";
                temp_data[i][4] = "1";
                toupdate.clear();
                toupdate.push_back(id);
                toupdate.push_back(bookname);
                toupdate.push_back(temp_data[i][3]);
                toupdate.push_back(to_string(time(0)));
                writefileappend(toupdate, "issued_books_data.csv");
                cout << "Book successfully issued\n";
                break;
            }
        }
        if (fl == 0) cout << "Book not available\n";
        writefile(temp_data, "all_books_data.csv");
        temp_data.clear();
    }
}

void User::return_book(string id, string isbncode) {
    temp_data.clear();
    int fl = 0;
    string bookname;
    time_t issue_time = 0;
    time_t return_time = time(0);
    int overdue_days = 0;
    int fine_amount = 0;
    string type_user = "";

    readfile("all_users_data.csv");
    for (int i = 0; i < temp_data.size(); i++) {
        if (temp_data[i][1] == id) {
            type_user = temp_data[i][3];
            break;
        }
    }
    temp_data.clear();

    int max_days = (type_user == "1") ? 15 : 30;

    readfile("issued_books_data.csv");
    for (int i = 0; i < temp_data.size(); i++) {
        if (temp_data[i][2] == isbncode && temp_data[i][0] == id) {
            fl = 1;
            bookname = temp_data[i][1];
            issue_time = stoi(temp_data[i][3]);

            int days_borrowed = (return_time - issue_time) / 86400;

            if (days_borrowed > max_days) {
                overdue_days = days_borrowed - max_days;
                if (type_user == "1") { // Student
                    fine_amount = overdue_days * 10;
                } else { // Professor
                    fine_amount = overdue_days * 0;
                }

                cout << "Book is overdue by " << overdue_days << " days.\n";
                cout << "Fine amount: Rs. " << fine_amount << "\n";

            } else {
                cout << "Book returned on time. No fine.\n";
            }

            // Add to history before removing from current list
            add_to_history(id, bookname, isbncode, issue_time, return_time);

            // Remove from issued_books_data.csv
            temp_data.erase(temp_data.begin() + i);
            writefile(temp_data, "issued_books_data.csv");

            temp_data.clear();
            readfile("all_books_data.csv");

            for (int j = 0; j < temp_data.size(); j++) {
                if (temp_data[j][2] == isbncode) {
                    temp_data[j][4] = "0"; // Mark as available
                }
            }

            writefile(temp_data, "all_books_data.csv");
            break;
        }
    }

    if (fl == 0) {
        cout << "Book with ISBN " << isbncode << " not found in your borrowing list.\n";
    }
}

void User::see_issued_books(string id) {
    int count = 0;
    temp_data.clear();
    readfile("issued_books_data.csv");
    for (int i = 0; i < temp_data.size(); i++) {
        if (temp_data[i][0] == id) {
            cout << count << ". ";
            count++;
            for (int k = 0; k < temp_data[i].size() - 1; k++)
                cout << temp_data[i][k] << " | ";
            time_t stamp = stoi(temp_data[i][3]);
            tm *dateformat = localtime(&stamp);
            cout << dateformat->tm_mday << "/" << 1 + dateformat->tm_mon << "/" << 1900 + dateformat->tm_year << "\n";
        }
    }
    if (count == 0) cout << "You haven't issued any books as of now\n\n";
    temp_data.clear();
}

void User::check_available(string id, string bookname) {
    temp_data.clear();
    int fl = 0;
    readfile("all_books_data.csv");
    int count = 1;
    for (int i = 0; i < temp_data.size(); i++) {
        if (temp_data[i][0] == bookname && temp_data[i][4] == "0") {
            fl = 1;
            cout << count << ". ";
            count++;
            cout << "Book is available!\n";
            for (auto j : temp_data[i])
                cout << j << " | ";
            cout << "\n";
            break;
        }
    }
    if (fl == 0) cout << "Book not available\n";
    temp_data.clear();
}

void User::add_to_history(string id, string bookname, string isbn, time_t issue_time, time_t return_time) {
    vector<string> history_record;
    history_record.push_back(id);
    history_record.push_back(bookname);
    history_record.push_back(isbn);
    history_record.push_back(to_string(issue_time));
    history_record.push_back(to_string(return_time));

    // Calculate if it was returned late
    string type_user = "";
    temp_data.clear();
    readfile("all_users_data.csv");
    for (int i = 0; i < temp_data.size(); i++) {
        if (temp_data[i][1] == id) {
            type_user = temp_data[i][3];
            break;
        }
    }
    temp_data.clear();

    int max_days = (type_user == "1") ? 30 : 60; // 30 days for students, 60 for professors
    int days_borrowed = (return_time - issue_time) / 86400;

    if (days_borrowed > max_days) {
        int overdue_days = days_borrowed - max_days;
        int fine_amount = (type_user == "1") ? overdue_days * 2 : overdue_days * 5;
        history_record.push_back(to_string(overdue_days));
        history_record.push_back(to_string(fine_amount));
    } else {
        history_record.push_back("0"); 
        history_record.push_back("0"); 
    }

    writefileappend(history_record, "borrowing_history.csv");
    cout << "Added to borrowing history.\n";
}

bool User::has_unpaid_fines(string id, string type_user) {
    int fine = calc_fine(id, type_user);
    return (fine > 0);
}





void Librarian::view_borrowing_history(string id) {
    cout << "---------------------------------------------------------------------\n";
    cout << "Borrowing History Report\n";
    cout << "---------------------------------------------------------------------\n";
    
    // Option to view all history or filter by user
    cout << "1. View all borrowing history\n";
    cout << "2. View history for a specific user\n";
    cout << "Enter your choice: ";
    
    char choice;
    cin >> choice;
    
    temp_data.clear();
    readfile("borrowing_history.csv");
    
    if (choice == '1') {
        // Show all history
        cout << "\nComplete Borrowing History:\n";
        cout << "--------------------------------------------------------------\n";
        cout << "User ID | Book Name | ISBN | Issue Date | Return Date | Overdue Days | Fine\n";
        cout << "--------------------------------------------------------------\n";
        
        for (int i = 0; i < temp_data.size(); i++) {
            cout << temp_data[i][0] << " | "; // User ID
            cout << temp_data[i][1] << " | "; // Book Name
            cout << temp_data[i][2] << " | "; // ISBN
            
            // Format dates
            time_t issue_stamp = stoi(temp_data[i][3]);
            tm *issue_date = localtime(&issue_stamp);
            cout << issue_date->tm_mday << "/" << 1 + issue_date->tm_mon << "/" << 1900 + issue_date->tm_year << " | ";
            
            time_t return_stamp = stoi(temp_data[i][4]);
            tm *return_date = localtime(&return_stamp);
            cout << return_date->tm_mday << "/" << 1 + return_date->tm_mon << "/" << 1900 + return_date->tm_year << " | ";
            
            cout << temp_data[i][5] << " days | "; // Overdue days
            cout << "Rs. " << temp_data[i][6] << endl; // Fine amount
        }
    } else if (choice == '2') {
        // Filter by user ID
        string user_id;
        cout << "Enter user ID: ";
        cin >> user_id;
        
        cout << "\nBorrowing History for User " << user_id << ":\n";
        cout << "--------------------------------------------------------------\n";
        cout << "Book Name | ISBN | Issue Date | Return Date | Overdue Days | Fine\n";
        cout << "--------------------------------------------------------------\n";
        
        bool found = false;
        for (int i = 0; i < temp_data.size(); i++) {
            if (temp_data[i][0] == user_id) {
                found = true;
                cout << temp_data[i][1] << " | "; // Book Name
                cout << temp_data[i][2] << " | "; // ISBN
                
                // Format dates
                time_t issue_stamp = stoi(temp_data[i][3]);
                tm *issue_date = localtime(&issue_stamp);
                cout << issue_date->tm_mday << "/" << 1 + issue_date->tm_mon << "/" << 1900 + issue_date->tm_year << " | ";
                
                time_t return_stamp = stoi(temp_data[i][4]);
                tm *return_date = localtime(&return_stamp);
                cout << return_date->tm_mday << "/" << 1 + return_date->tm_mon << "/" << 1900 + return_date->tm_year << " | ";
                
                cout << temp_data[i][5] << " days | "; 
                cout << "Rs. " << temp_data[i][6] << endl; 
            }
        }
        
        if (!found) {
            cout << "No borrowing history found for user " << user_id << endl;
        }
    } else {
        cout << "Invalid choice.\n";
    }
    
    temp_data.clear();
}


int User::calc_fine(string id, string type_user) {
    int fine = 0;
    
    temp_data.clear();
    readfile("issued_books_data.csv");
    for (int i = 0; i < temp_data.size(); i++) {
        if (temp_data[i][0] == id) {
            int curtime = time(0);
            int isstime = stoi(temp_data[i][3]);
            int max_days = (type_user == "1") ? 15 : 30;
            int days_borrowed = (curtime - isstime) / 86400;
            
            if (days_borrowed > max_days) {
                int overdue_days = days_borrowed - max_days;
                int daily_fine = (type_user == "1") ? 10 : 0;
                fine += overdue_days * daily_fine;
            }
        }
    }
    temp_data.clear();
    
    // Now check unpaid historical fines
    readfile("unpaid_fines.csv");
    for (int i = 0; i < temp_data.size(); i++) {
        if (temp_data[i][0] == id) {
            fine += stoi(temp_data[i][1]); // Add unpaid fine amount
        }
    }
    temp_data.clear();
    
    return fine;
}

void User::logout() {
    cout << "Logging out...\n";
    User u;
    u.display_menu();
}

void User::clear_fine_amount(string id, string type_user) {
    int a = calc_fine(id, type_user);
    if (a == 0) {
        cout << "You have no pending dues\n";
    } else {
        cout << "Your fine of Rupees " << a << " is being cleared.\n";
        // Clear the fines from unpaid_fines.csv
        temp_data.clear();
        readfile("unpaid_fines.csv");
        for (int i = 0; i < temp_data.size(); i++) {
            if (temp_data[i][0] == id) {
                temp_data.erase(temp_data.begin() + i);
                break;
            }
        }
        writefile(temp_data, "unpaid_fines.csv");
        temp_data.clear();
    }
}

void User::User_add(string id) {
    Librarian l;
    l.add_user(id);
}

void User::User_delete(string id) {
    Librarian l;
    l.delete_user(id);
}

void User::User_update(string id) {
    Librarian l;
    l.update_user(id);
}

void User::User_search(string id) {
    // Implementation for searching a user
}


void Book::Show_duedate(string isbn) {
    temp_data.clear();
    string uid;
    time_t stamp;
    readfile("issued_books_data.csv");
    int fl = 0;
    for (int i = 0; i < temp_data.size(); i++) {
        if (temp_data[i][2] == isbn) {
            fl = 1;
            uid = temp_data[i][0];
            stamp = stoi(temp_data[i][3]);
            break;
        }
    }
    temp_data.clear();
    int days = 30;
    readfile("all_users_data.csv");
    for (int i = 0; i < temp_data.size(); i++) {
        if (temp_data[i][1] == uid) {
            if (temp_data[i][3] == "1")
                days = 30;
            else
                days = 60;
            break;
        }
    }
    stamp += days * 86400;
    tm *due_time = localtime(&stamp);  
    if (fl == 0) cout << "Book was not issued!\n";
    else {
        cout << "Due date of the book is : ";
        cout << due_time->tm_mday << "/" << 1 + due_time->tm_mon << "/" << 1900 + due_time->tm_year << "\n";
    }
}

void Book::Book_request(string id, string bookname, string type_user) {
    User u;
    
    if (u.has_unpaid_fines(id, type_user)) {
        cout << "You have unpaid fines. Please clear your fines before borrowing new books.\n";
        int fine_amount = u.calc_fine(id, type_user);
        cout << "Your current fine amount: Rs. " << fine_amount << "\n";
        cout << "Would you like to clear your fines now? (y/n): ";
        char choice;
        cin >> choice;
        
        if (choice == 'y' || choice == 'Y') {
            u.clear_fine_amount(id, type_user);
            u.issue_book(id, bookname, type_user);
        } else {
            cout << "Book request denied due to unpaid fines.\n";
        }
    } else {
        u.issue_book(id, bookname, type_user);
    }
}

void Book::Book_add(string id) {
    Librarian l;
    l.add_book(id);
}

void Book::Book_delete(string id) {
    Librarian l;
    l.delete_book(id);
}

void Book::Book_update(string id) {
    Librarian l;
    l.update_book(id);
}

void Librarian::display_lib_menu(string id) {
    cout << "---------------------------------------------------------------------\n";
    cout << "\nWelcome " << id << "! You are logged in as librarian.\n\n";
    cout << "Press 1 to add a user\n";
    cout << "Press 2 to update a user\n";
    cout << "Press 3 to delete a user\n";
    cout << "Press 4 to add a book\n";
    cout << "Press 5 to update a book\n";
    cout << "Press 6 to delete a book\n";
    cout << "Press 7 to view all users\n";
    cout << "Press 8 to view all books\n";
    cout << "Press 9 to view borrowing history\n"; 
    cout << "Press l to logout\n";
    cout << "---------------------------------------------------------------------\n";
    char c;
    cin >> c;
    Librarian l;
    Book b;
    User u;
    string isbn, uid;
    switch (c) {
        case '1':
            u.User_add(id);
            l.display_lib_menu(id);
            break;
        case '2':
            u.User_update(id);
            l.display_lib_menu(id);
            break;
        case '3':
            u.User_delete(id);
            l.display_lib_menu(id);
            break;
        case '4':
            b.Book_add(id);
            l.display_lib_menu(id);
            break;
        case '5':
            b.Book_update(id);
            l.display_lib_menu(id);
            break;
        case '6':
            b.Book_delete(id);
            l.display_lib_menu(id);
            break;
        case '7':
            l.see_all_users(id);
            l.display_lib_menu(id);
            break;
        case '8':
            l.see_all_books(id);
            l.display_lib_menu(id);
            break;
        case '9':
            l.view_borrowing_history(id);
            l.display_lib_menu(id);
            break;
        case 'l':
            logout();
            l.display_lib_menu(id);
            break;
    }
}

void Librarian::see_all_users(string id) {
    temp_data.clear();
    readfile("all_users_data.csv");
    cout << "Below are all the users. 1 at the end signifies a student, 2 means a professor and 3 means a librarian \n\n";
    cout << "The data is given in the form of student, username, type of user.\n\n";
    printdata_notpassword(temp_data);
    temp_data.clear();
}

void Librarian::see_all_books(string id) {
    temp_data.clear();
    readfile("all_books_data.csv");
    cout << "Below are all the books. 1 at the end signifies a student, 2 means a professor and 3 means a librarian \n\n";
    cout << "The data is given in the form of book name, author, publisher, isbn number, and is_issued (1 if book is issued).\n\n";
    printdata(temp_data);
    temp_data.clear();
}

void Librarian::add_user(string id) {
    cout << "Please enter the details of the new user : \n";
    string _name, _id, _password, _type;
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, _name);
    cout << "Enter id : ";
    cin >> _id;
    cout << "Enter password : ";
    cin >> _password;
    cout << "Enter type of the user : 1 if student, 2 if professor, 3 if librarian : ";
    cin >> _type;
    fstream fout("all_users_data.csv", ios::out | ios::app);
    fout << _name << "," << _id << "," << _password << "," << _type << '\n';
    cout << "New user has been added.\n";
}

void Librarian::add_book(string id) {
    cout << "Please enter the details of the new book : \n";
    string title, author, isbn, publisher;
    cout << "Enter title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter author : ";
    cin >> author;
    cout << "Enter isbn : ";
    cin >> isbn;
    cout << "Enter name of publisher : ";
    cin >> publisher;
    fstream fout("all_books_data.csv", ios::out | ios::app);
    fout << title << "," << author << "," << isbn << "," << publisher << ",0" << '\n';
    cout << "New book has been added.\n";
}

void Librarian::delete_book(string id) {
    string isbnno;
    cout << "Enter the isbn number of the book : ";
    cin >> isbnno;
    temp_data.clear();
    int found = 0;
    readfile("all_books_data.csv");
    for (int i = 0; i < temp_data.size(); i++) {
        if (temp_data[i][2] == isbnno) {
            found = 1;
            temp_data.erase(temp_data.begin() + i);
            break;
        }
    }
    writefile(temp_data, "all_books_data.csv");
    temp_data.clear();
    readfile("issued_books_data.csv");
    for (int i = 0; i < temp_data.size(); i++) {
        if (temp_data[i][2] == isbnno) {
            temp_data.erase(temp_data.begin() + i);
            break;
        }
    }
    writefile(temp_data, "issued_books_data.csv");
    temp_data.clear();
    if (found == 0) cout << "Book not found.\n";
}

void Librarian::delete_user(string id) {
    string uid;
    cout << "Enter the user id of the user : ";
    cin >> uid;
    temp_data.clear();
    int found = 0;
    readfile("all_users_data.csv");
    for (int i = 0; i < temp_data.size(); i++) {
        if (temp_data[i][1] == uid) {
            found = 1;
            temp_data.erase(temp_data.begin() + i);
            break;
        }
    }
    writefile(temp_data, "all_users_data.csv");
    temp_data.clear();
    vector<string> isbns;
    readfile("issued_books_data.csv");
    for (int i = 0; i < temp_data.size(); i++) {
        if (temp_data[i][0] == uid) {
            isbns.push_back(temp_data[i][2]);
            temp_data.erase(temp_data.begin() + i);
            break;
        }
    }
    writefile(temp_data, "issued_books_data.csv");
    temp_data.clear();

    readfile("all_books_data.csv");
    for (int i = 0; i < temp_data.size(); i++) {
        for (int j = 0; j < isbns.size(); j++) {
            if (isbns[j] == temp_data[i][2]) {
                temp_data[i][4] = "0";
            }
        }
    }
    writefile(temp_data, "all_books_data.csv");
    if (found == 0) cout << "User not found.\n";
}

void Librarian::update_user(string id) {
    string upid;
    cout << "Enter the id of the user you want to update : ";
    cin >> upid;
    cout << "Enter the serial number of the field you want to update : \n";
    cout << "1. Password\n";
    cout << "2. Name of the User\n";
    char c;
    cin >> c;
    temp_data.clear();
    int fl = 0;
    readfile("all_users_data.csv");
    for (int i = 0; i < temp_data.size(); i++) {
        if (temp_data[i][1] == upid) {
            fl = 1;
            string new_field;
            cout << "Enter the new value of the field : ";
            cin.ignore();
            getline(cin, new_field);
            if (c == '1') {
                temp_data[i][2] = new_field;
            } else if (c == '2') {
                temp_data[i][0] = new_field;
            } else {
                cout << "Invalid input!\n\n";
            }
            break;
        }
    }
    cout << "User updated\n";
    writefile(temp_data, "all_users_data.csv");
    temp_data.clear();
    if (fl == 0) cout << "User was not found.\n\n";
}

void Librarian::update_book(string id) {
    string isbn_no;
    cout << "Enter the ISBN number of the book you want to update: ";
    cin >> isbn_no;
    cout << "Enter the serial number of the field you want to update: \n";
    cout << "1. Name of the Book\n";
    cout << "2. Name of the Author\n";
    cout << "3. Name of the Publisher\n";
    char c;
    cin >> c;
    temp_data.clear();
    int fl = 0;
    string new_field;
    readfile("all_books_data.csv");
    for (int i = 0; i < temp_data.size(); i++) {
        if (temp_data[i][2] == isbn_no) { 
            fl = 1;
            cout << "Enter the new value of the field: ";
            cin.ignore();
            getline(cin, new_field);
            if (c == '1') {
                temp_data[i][0] = new_field; 
            } else if (c == '2') {
                temp_data[i][1] = new_field; 
            } else if (c == '3') {
                temp_data[i][3] = new_field; 
            } else {
                cout << "Invalid input!\n\n";
            }
            break;
        }
    }
    if (fl == 1) {
        cout << "Book updated\n";
        writefile(temp_data, "all_books_data.csv");
    } else {
        cout << "Book was not found.\n\n";
    }
    temp_data.clear();
}

int main(){
    ifstream history_file("borrowing_history.csv");
    if (!history_file) {
        ofstream create_history("borrowing_history.csv");
        create_history << "user_id,book_name,isbn,issue_time,return_time,overdue_days,fine_amount\n";
        create_history.close();
    }
    history_file.close();
    
    ifstream fines_file("unpaid_fines.csv");
    if (!fines_file) {
        ofstream create_fines("unpaid_fines.csv");
        create_fines << "user_id,fine_amount\n";
        create_fines.close();
    }
    fines_file.close();
    
    User temp;
    temp.display_menu();
    return 0;
}