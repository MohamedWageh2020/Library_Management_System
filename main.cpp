#include <iostream>
#include <algorithm>
using namespace std;


const int MAX_NUMBERS_OF_BOOKS=101; // Define a constant for the maximum number of books
const int MAX_NUMBERS_OF_USERS=101; // Define a constant for the maximum number of users


struct Book{                  // Declare a struct named 'Book' to represent book information
    int book_id;             // Book ID
    string book_name;       // Book name
    int book_quantity;     // Quantity of the book available
    int total_borrowed;     // Total number of times the book has been borrowed
    bool book_exist;        // Flag indicating if the book exists
    int len;                 // Length of the array storing borrowers' names
    string namse_who_borrowed[MAX_NUMBERS_OF_USERS];  // Array to store names of users who borrowed the book

    Book(){  // Constructor for the 'Book' struct
        book_id=0;  // Initialize book ID
        len=0;      // Initialize length
        book_quantity=0;    // Initialize book quantity
        book_exist=0;       // Initialize book existence flag
        total_borrowed=0;   // Initialize total borrowed count
    }
};

struct User{           // Declare a struct named 'User' to represent user information
    string username;     // User's username
    int user_national_id;  // User's national ID
    bool user_exist=0;       // Flag indicating if the user exists
    int borrowed_books[MAX_NUMBERS_OF_BOOKS]; // Array to store borrowed book IDs
    int len;    // Length of the array storing borrowed book IDs

    User(){          // Constructor for the 'User' struct
        username="";     // Initialize username
        len=0;           // Initialize length
        user_national_id=-1;      // Initialize national ID
        user_exist=0;     // Initialize user existence flag
    }
};

bool compare_name(Book &a,Book &b){   // Comparison function for sorting by book name
    return a.book_name<b.book_name;
}

bool compare_id(Book &a,Book &b){   // Comparison function for sorting by book ID
    return a.book_id<b.book_id;
}

struct Library_System{    // Define a struct named 'Library_System'

    Book array_of_books[MAX_NUMBERS_OF_BOOKS];   // Array to store books
    User array_of_users[MAX_NUMBERS_OF_USERS];   // Array to store users

    Library_System(){      // Constructor for 'Library_System'
        for(int i=1;i<MAX_NUMBERS_OF_USERS;i++){
            array_of_books[i]=Book();  // Initialize book array
            array_of_users[i]=User();  // Initialize user array
        }
    }

    void run(){        // Function to run the library system
        int option;   // Infinite loop for menu
        while(true){  // Get user choice from menu
        option=menu();
        switch (option)
        {
        case 1:
            Add_book();
            break;
        case 2:
            Search_books_by_prefix();
            break;
        case 3:
            Print_who_borrowed_book_by_name();
            break;
        case 4:
            Print_library_by_id();
            break;
        case 5:
            Print_library_by_name();
            break;
        case 6:
            Add_user();
            break;
        case 7:
            User_borrow_book();
            break;
        case 8:
            User_return_book();
            break;
        case 9:
            Print_users();
            break;
        case 10:
            return ;
            break;
        default:
            break;
        }
        }
    }

    int menu(){    // Function to display menu and get user choice
        int op;
        cout<<"Library Menu;\n";
        cout<<"1) Add book\n";
        cout<<"2) Search books by prefix\n";
        cout<<"3) Print who borrowed book by name\n";
        cout<<"4) Print library by id\n";
        cout<<"5) Print library by name\n";
        cout<<"6) Add user\n";
        cout<<"7) User borrow book\n";
        cout<<"8) User return book\n";
        cout<<"9) Print users\n";
        cout<<"10)Exit\n";
        cout<<"Enter your menu choice [1-10]: ";
        cin>>op;
        return op;
    }

     int find_book_ID(string name){     // Function to find book ID by name
        for(int i=1;i<MAX_NUMBERS_OF_BOOKS;i++){
            if(array_of_books[i].book_name==name){
                return i;   // Return the book's ID if found
            }
        }
        return -1;   // Return -1 if book name is not found
    } 

     int find_user_ID(string name){   // Function to find user ID by username
        for(int i=1;i<MAX_NUMBERS_OF_USERS;i++){
            if(array_of_users[i].username==name){
                return i;  // Return the user's ID if found
            }
        }
        return -1;    // Return -1 if username is not found
    } 

    void Add_book(){
        int id,quantity;
        string name;
        cout<<"Enter book info: id & name & total quantity: ";
        cin>>id>>name>>quantity;

        if(id>=1 && id<MAX_NUMBERS_OF_BOOKS){
        array_of_books[id].book_id=id;  // Set book ID
        array_of_books[id].book_name=name;  // Set book name
        array_of_books[id].book_quantity=quantity;   // Set book quantity
        array_of_books[id].book_exist=1;    // Mark book as existing
        }

        else{
            cout<<"Invalid id please try agian\n";  // Print error message
        }
    }

    void Search_books_by_prefix(){
        string prefix;
        bool flag=1,not_exist=1;

        cout<<"enter book name prefix: ";
        cin>>prefix;
        
        for(int i=1;i<MAX_NUMBERS_OF_BOOKS;i++){
            flag=1;
            if(array_of_books[i].book_exist==1){
                for(int j=0;j<(int)prefix.size();j++){
                    if(prefix[j]!=array_of_books[i].book_name[j]){
                        flag=0;
                        break;
                    }
                }
                if(flag==1){
                    cout<<array_of_books[i].book_name<<"\n"; // Print matching book name
                    not_exist=0;
                }
            }
        }
        if(not_exist==1){
            cout<<"No books with such prefix\n";  // Print if no books match the prefix
        }
    }

    void  Print_who_borrowed_book_by_name(){
        string book_name;
        int book_idx;
        cout<<"Enter book name: ";
        cin>>book_name;
        book_idx=find_book_ID(book_name);

        if(book_idx==-1){
            cout<<"Invalid book name\n";
            return;
        }

        for(int j=1;j<=array_of_books[book_idx].len;j++){
            cout<<array_of_books[book_idx].namse_who_borrowed[j]<<"\n";
            }
            
        return;
    }

    void Print_library_by_id(){
        sort(array_of_books,array_of_books+MAX_NUMBERS_OF_BOOKS-1,compare_id);
        for(int i=1;i<MAX_NUMBERS_OF_BOOKS;i++){
            if(array_of_books[i].book_exist==1){
                cout<<"id= "<<array_of_books[i].book_id<<"  name= "<<array_of_books[i].book_name<<"  total_quantity = "<<array_of_books[i].book_quantity<<"  totak_borrowed = "<<array_of_books[i].total_borrowed<<"\n";
            }
        }
    }

    void Print_library_by_name(){
        sort(array_of_books,array_of_books+MAX_NUMBERS_OF_BOOKS-1,compare_name);
        for(int i=1;i<MAX_NUMBERS_OF_BOOKS;i++){
            if(array_of_books[i].book_exist==1){
                cout<<"id= "<<array_of_books[i].book_id<<"  name= "<<array_of_books[i].book_name<<"  total_quantity = "<<array_of_books[i].book_quantity<<"  totak_borrowed = "<<array_of_books[i].total_borrowed<<"\n";
            }
        }
    }

    void Add_user(){
        string username;
        int national_id;
        cout<<"Enter user name & national id: ";
        cin>>username>>national_id;

        if(national_id>=1 && national_id<MAX_NUMBERS_OF_USERS){
            array_of_users[national_id].user_national_id=national_id;
            array_of_users[national_id].username=username;
            array_of_users[national_id].user_exist=1;
        }
        else{
            cout<<"Invalid national_id please try agian\n";
        }
    }

    void User_borrow_book(){
        string username,book_name;
        int book_idx,user_idx;
        cout<<"Enter user name and book name: ";
        cin>>username>>book_name;
        book_idx=find_book_ID(book_name);
        if(book_idx==-1){
            cout<<"Invalid book name\n";
            return;
        }

        if(array_of_books[book_idx].book_quantity==0){
            cout<<"No borrowed copies\n";
            return;
        } 
        
        user_idx=find_user_ID(username);
         if(user_idx==-1){
            cout<<"Invalid username\n";
            return;
        }
        array_of_users[user_idx].len++;
        array_of_users[user_idx].borrowed_books[array_of_users[user_idx].len]=array_of_books[book_idx].book_id;
        array_of_books[book_idx].book_quantity--;
        array_of_books[book_idx].total_borrowed++;
        array_of_books[book_idx].len++;
        array_of_books[book_idx].namse_who_borrowed[array_of_books[book_idx].len]=username;
        return;
    }

    void User_return_book(){
        string username,book_name;
        int book_idx,user_idx;
        cout<<"Enter user name and book name: ";
        cin>>username>>book_name;
        book_idx=find_book_ID(book_name);
        if(book_idx==-1){
            cout<<"Invalid book name\n";
        }
        else{
            user_idx=find_user_ID(username);
            array_of_users[user_idx].len--;
            array_of_books[book_idx].book_quantity++;
            array_of_books[book_idx].total_borrowed--;
        }
        return;
    }

    void Print_users(){
        for(int i=1;i<MAX_NUMBERS_OF_USERS;i++){
            if(array_of_users[i].user_exist==1){
                cout<<"User "<<array_of_users[i].username<<" id "<<array_of_users[i].user_national_id<<" borrowed books ids: ";
                for(int j=1;j<=array_of_users[i].len;j++){
                    cout<<array_of_users[i].borrowed_books[j]<<" ";
                }
                cout<<"\n";
            }
        }
        return;
    }
};



int main(void){
    Library_System library=Library_System();
    library.run();
    return 0;
}