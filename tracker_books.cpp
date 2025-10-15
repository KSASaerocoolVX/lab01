#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;
int NUMBER_OF_BOOK=0;
const int MAX_BOOK=10000;
struct Books {
    char naming[102],author[102];
    int year_of_read;
    float mark_of_book;
};
Books books [MAX_BOOK];
int stiri(const char* year) {
    int res=0;
    for (int i=0;year[i]!='\0';i++) {
        if (year[i]>='0' and year[i]<='9') {
            res=res*10+year[i]-'0';
        }
        else if (year[i]==' ') {
            continue;
        }
        else {
            return -1;
        }
    }
    return res;
}
float stirf(const char* s) {
    double res = 0.0;
    float factor = 1.0;
    bool afterDecimal = false;
    for (int i = 0; s[i] != '\0'; i++) {
        if ((s[i] == '.' || s[i] == ',') && afterDecimal==false) {
            factor=1.0;
            afterDecimal = true;
            continue;
        }
        if (s[i] >= '0' && s[i] <= '9') {
            if (afterDecimal) {
                factor /= 10.0;
                res = res + (s[i] - '0') * factor;
            } else {
                res = res * 10.0 + (s[i] - '0');
                factor*=10;
            }
        }
        else if (s[i]==' ') {
            continue;
        }
        else {
            return -1;
        }
    }
    return res;
}
void load_massive_books(const char * nameofile) {
    int NUMBER_APPEND_OF__CORRUPTED_BOOKS =0;
    char naming[102],author[102], year_of_read[20], mark_of_book[10];
    ifstream fin(nameofile);
    if (!fin) {
        cout << "Error opening file " << nameofile << endl;
        return;
    }
    else {
        while (NUMBER_OF_BOOK<MAX_BOOK && fin.peek()!=EOF) {
            fin.getline(naming,102,'|');
            if (fin.gcount()>99) {
                NUMBER_APPEND_OF__CORRUPTED_BOOKS++;
                cout << "Corrupted data " << NUMBER_OF_BOOK+NUMBER_APPEND_OF__CORRUPTED_BOOKS << endl;
                fin.clear();
                fin.ignore(10000, '\n');
                continue;
            }


            fin.getline(author,102,'|');
            if (fin.gcount()>99) {
                NUMBER_APPEND_OF__CORRUPTED_BOOKS++;
                cout << "Corrupted data " << NUMBER_OF_BOOK+NUMBER_APPEND_OF__CORRUPTED_BOOKS << endl;
                fin.clear();
                fin.ignore(10000, '\n');
                continue;
            }

            fin.getline(year_of_read,20,'|');
            if (fin.gcount()==19 && fin.peek()!='|') {
                NUMBER_APPEND_OF__CORRUPTED_BOOKS++;
                cout << "Corrupted data " << NUMBER_OF_BOOK+NUMBER_APPEND_OF__CORRUPTED_BOOKS << endl;
                fin.clear();
                fin.ignore(10000, '\n');
                continue;
            }
            fin.getline(mark_of_book,10);
            if (fin.gcount()==9 && fin.peek()!='|') {
                NUMBER_APPEND_OF__CORRUPTED_BOOKS++;
                cout << "Corrupted data " << NUMBER_OF_BOOK+NUMBER_APPEND_OF__CORRUPTED_BOOKS << endl;
                fin.clear();
                fin.ignore(10000, '\n');
                continue;
            }
            if (stiri(year_of_read)==-1) {
                NUMBER_APPEND_OF__CORRUPTED_BOOKS++;
                cout << "Corrupted year " << NUMBER_OF_BOOK+NUMBER_APPEND_OF__CORRUPTED_BOOKS << endl;
                fin.clear();
                fin.ignore(10000, '\n');
                continue;
            }
            if (stirf(mark_of_book)==-1) {
                NUMBER_APPEND_OF__CORRUPTED_BOOKS++;
                cout << "Corrupted mark " << NUMBER_APPEND_OF__CORRUPTED_BOOKS+NUMBER_OF_BOOK << endl;
                fin.clear();
                fin.ignore(10000, '\n');
                continue;
            }
            strcpy(books[NUMBER_OF_BOOK].naming,naming);
            strcpy(books[NUMBER_OF_BOOK].author,author);
            books[NUMBER_OF_BOOK].year_of_read=stiri(year_of_read);
            books[NUMBER_OF_BOOK].mark_of_book=stirf(mark_of_book);
            NUMBER_OF_BOOK++;
        }
        if(NUMBER_OF_BOOK>10000) {
            cout << "No have any space" << endl;
            return;
        }
        fin.close();
    }
}
void savebookfile(const char * nameofilem,Books book) {
    ofstream fout(nameofilem,ios::app);
    if (!fout) {
        cout << "Can't open file " << nameofilem << endl;
        return;
    }
    fout<<book.naming<< "|" <<book.author <<"|"<< book.year_of_read << "|" << book.mark_of_book<<endl;
    fout.close();
}
void addBook() {
    if(NUMBER_OF_BOOK>10000) {
        cout << "No have any space" << endl;
        return;
    }
    Books book;
    cin.ignore(10000,'\n');
    cout << "Enter book naming: ";
    bool overflow=true;
    while (overflow) {
        cin.getline(book.naming,sizeof(book.naming));
        if (cin.gcount()>99) {
            cout << "Incorrect input" << endl;
            overflow=true;
            cin.clear();
            cin.ignore(10000,'\n');
        }
        else {
            overflow=false;
        }
    }
    cout << "Enter book author: ";
    overflow=true;
    while (overflow) {
        cin.getline(book.author,sizeof(book.author));
        if (cin.gcount()>99) {
            cout << "Incorrect input" << endl;
            overflow=true;
            cin.clear();
            cin.ignore(10000,'\n');
        }
        else {
            overflow=false;
        }
    }
    cout << "Enter year of read: ";
    cin>>book.year_of_read;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(10000,'\n');
        cout << "Please enter a valid year\n";
        cout << "Enter book year of read: ";
        cin>>book.year_of_read;
    }
    cout << "Enter book mark of read from 0 to 10: ";
    cin >> book.mark_of_book;
    while (cin.fail() || (book.mark_of_book>10 || book.mark_of_book<0)) {
        cin.clear();
        cin.ignore(10000,'\n');
        cout << "Please enter a valid mark of read\n";
        cout << "Enter book mark of read from 0 to 10: ";
        cin >> book.mark_of_book;
    }
    NUMBER_OF_BOOK++;
    savebookfile("books.txt", book);
    cout << "Book added successfully" << endl;
}

void showallstats() {
    if (NUMBER_OF_BOOK == 0) {
        cout << "No books found" << endl;
        return;
    }

    float totalMark = 0;
    unsigned short bestbookindex = 0;
    for (int i = 0; i < NUMBER_OF_BOOK; i++) {
        totalMark += books[i].mark_of_book;
        if (books[i].mark_of_book > books[bestbookindex].mark_of_book) {
            bestbookindex = i;
        }
    }
    float average = totalMark / NUMBER_OF_BOOK;

    const int LABEL_WIDTH = 24;

    cout << "--------------------------------------------------------------------------\n";
    cout << "|                        READEN + AVERAGE                                |\n";
    cout << "--------------------------------------------------------------------------\n";

    cout << left;
    cout << setw(LABEL_WIDTH) << "| Total books:" << NUMBER_OF_BOOK << endl;
    cout << setw(LABEL_WIDTH) << "| Average mark:"
         << fixed << setprecision(2) << average << endl;

    cout << "--------------------------------------------------------------------------\n";
    cout << "|                             BEST BOOK                                  |\n";
    cout << "--------------------------------------------------------------------------\n";

    cout << setw(LABEL_WIDTH) << "| Title:" << books[bestbookindex].naming << endl;
    cout << setw(LABEL_WIDTH) << "| Author:" << books[bestbookindex].author << endl;
    cout << setw(LABEL_WIDTH) << "| Year read:" << books[bestbookindex].year_of_read << endl;
    cout << setw(LABEL_WIDTH) << "| Mark:"
         << fixed << setprecision(1) << books[bestbookindex].mark_of_book << endl;

    cout << "--------------------------------------------------------------------------\n";
}
void showbook() {
    if (NUMBER_OF_BOOK==0) {
        cout << "No books found." << endl;
        return;
    }
    const int LABEL_WIDTH = 24;
    cout << "\n--- All Books ---\n";
    cout << left << setw(LABEL_WIDTH) << "Title"
    << setw(LABEL_WIDTH) << "Author"
    << setw(LABEL_WIDTH) << "Year"
    << "Rating\n";
    cout << "--------------------------------------------------------------------------\n";
    for (int i = 0; i < NUMBER_OF_BOOK; i++) {
        cout << left << setw(LABEL_WIDTH) << books[i].naming
             << setw(LABEL_WIDTH) << books[i].author
             << setw(LABEL_WIDTH) << books[i].year_of_read
             << fixed << setprecision(1) << books[i].mark_of_book << endl;
    }
    cout << "--------------------------------------------------------------------------\n";
}

int main() {
    load_massive_books("books.txt");
    char state;
    cout<< "=== Tracking books ===\n" <<"Type 1 to add book\n" << "Type 2 to show statistic\n" << "Type 3 to show books\n" << "Type 4 to exit program" << endl;
    do{
        cin >>state;
        switch (state) {
            case '1':
                addBook();
                break;
            case '2':
                showallstats();
                break;
            case '3':
                showbook();
                break;
            case '4':
                exit(0);
            default:
                cout<<"Please enter a valid option"<<endl;
        }
    } while (state!='4');
    return 0;
}