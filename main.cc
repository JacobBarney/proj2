#include "defn.h"

bool TestForPrime(int val)
{
    int limit, factor = 2;

    limit = (long)(sqrtf((float)val) + 0.5f);
    while( (factor <= limit) && (val % factor))
        factor++;
    return (factor>limit);
}

BST* add(BST *root, BookInfo* book)
{
    if(!strcmp(root->book.title, ""))
    {
        root->book = *book;
        return root;
    }
    else if(root->book.title < book->title)
    {
        if(root->right)
            add(root->right, book);
        else
        {
            root->right = new BST;
            root->right->book = *book;
        }
    }
    else
    {
        if(root->left)
            add(root->left,book);
        else
        {
            root->left = new BST;
            root->left->book = *book;
        }
    }
}

int stringValue(char *str, int size)
{
    int sum = 0;
    for(int i = 0; i < TITLE_LEN; i++)
    {
        sum+= int(str[i]);
    }

    return sum % size;
}


void print(BookInfo *book)
{
    cout << "" << book->title << "\n";
    cout << "" << book->author << "\n";
    cout << "" << book->publisher << "\n";

    for(int i = 0; i < NO_FORMATS; i++)
    {
        cout << "" << book->formats[i].format << "\n";
        cout << "" << book->formats[i].price << "\n";
        cout << "" << book->formats[i].quantity << "\n";
    }
}

void printAll(Genre *genres, int num)
{
    for(int i = 0; i < num; i++)
    {
        print(&(genres[i].root->book));
    }
}

int main()
{
    int numGenres = 0;
    int numBooks = 0;

    cin >> numGenres;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    Genre *genres = new Genre[numGenres];
    
    for(int i = 0; i < numGenres; i++)
    {
        cin.getline(genres[i].genre, GENRE_LEN);
        genres[i].root = new BST;
    }
    
    cin >> numBooks;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for(int i = 0; i < numGenres; i++)
    {
        cout << "genre " << i << ": " << genres[i].genre << "\n";
    }
    
    int prime = (numBooks*2) + 1;

    while(!TestForPrime(prime))
    {
        prime++;
    }

    HashTableEntry *hashTable = new HashTableEntry[prime];

    BookInfo *books = new BookInfo[numBooks];
    
    for(int i = 0; i < numBooks; i++)
    {
        char tempGenre[GENRE_LEN];
        int currentGenre = 0;
        
        cin.getline(tempGenre, GENRE_LEN);
        
        for(int j = 0; j < numGenres; j++)
        {
            if(!strcmp(genres[j].genre, tempGenre))
            {
                currentGenre = j;
                break;
            }
        }

        BookInfo *book = new BookInfo;

        cin.getline(book->title, TITLE_LEN);

        cin.getline(book->author, AUTHOR_LEN);

        cin.getline(book->publisher, PUBLISHER_LEN);

        int numFormats = 0;

        cin >> numFormats;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for(int j = 0; j < numFormats; j++)
        {
            cin.getline(book->formats[j].format, FORMAT_LEN);
            
            cin >> book->formats[j].price;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> book->formats[j].quantity;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        hashTable[stringValue(book->title, prime)].book = add(genres[currentGenre].root, book);

        strncpy(hashTable[stringValue(book->title, prime)].title, book->title, TITLE_LEN);
    }
    
}
