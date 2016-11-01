#include "defn.h"

void print(BookInfo book);
int stringValue(char *str, int size);


bool TestForPrime(int val)
{
    int limit, factor = 2;

    limit = (long)(sqrtf((float)val) + 0.5f);
    while( (factor <= limit) && (val % factor))
        factor++;
    return (factor>limit);
}

BST* add(BST **root, BST *newNode)
{
    if(!strcmp((*root)->book.title, ""))
    {
        *root = newNode;
        return *root;
    }
    else if(strcmp((*root)->book.title, newNode->book.title) < 0)
    {
        if((*root)->right)
            add(&((*root)->right), newNode);
        else
        {
            (*root)->right = newNode;
            return (*root)->right;
        }
    }
    else
    {
        if((*root)->left)
            add(&((*root)->left), newNode);
        else
        {
            (*root)->left = newNode;
            return (*root)->left;       
        }
        
    }
}


void findBook(HashTableEntry *hashTable, char *bookTitle, int prime)
{   
    HashTableEntry *curEntry = &(hashTable[stringValue(bookTitle, prime)]);
    while(curEntry && curEntry->book)
    {
        if(!strcmp(curEntry->book->book.title, bookTitle))
        {
            print(curEntry->book->book);
            return;
        }
        else
            curEntry = curEntry->next;
    }
    cout << "Book not carried\n";
}

void findPrice(HashTableEntry *hashTable, char *bookTitle, int prime)
{
    HashTableEntry *curEntry = &(hashTable[stringValue(bookTitle, prime)]);
    while(curEntry && curEntry->book)
    {
        if(!strcmp(curEntry->book->book.title, bookTitle))
        {
            printFormats(curEntry->book->book);
        }
        else
            curEntry = curEntry->next;
    }
    cout << "Book not carried\n";
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

//print all book information
void print(BookInfo book)
{
    cout << "" << book.title << "\n";
    cout << "" << book.author << "\n";
    cout << "" << book.publisher << "\n";

    for(int i = 0; i < NO_FORMATS; i++)
    {   
        if(strcmp(book.formats[i].format, ""))
        {
            cout << "" << book.formats[i].format << "\n";
            cout << "" << book.formats[i].price << "\n";
            cout << "" << book.formats[i].quantity << "\n";
        }
    }
}

void printFormats(BookInfo book)
{
    cout << "" << book.title << "\n";

    for(int i = 0; i < NO_FORMATS; i++)
    {
        if(strcmp(book.formats[i].format, ""))
        {
            cout << "" << book.formats[i].format << "\n";
            cout << "" << book.formats[i].price << "\n";
            cout << "" << book.formats[i].quantity << "\n";
        }
    }
}

void printAll(Genre *genres, int num)
{
    for(int i = 0; i < num; i++)
    {
        print((genres[i].root->book));
    }
}


void printNode(BST *node)
{
    if(node->left)
        printNode(node->left);
    cout << node->book.title << "\n";
    if(node->right)
        printNode(node->right);
}


bool printNodeLowHi(BST *node, char *low, char *hi)
{
    bool found = false;
    if(node->left)
        found = found || printNodeLowHi(node->left, low, hi);
    if((strcmp(node->book.title, low) >= 0) && (strcmp(node->book.title, hi) <= 0))
    {
        cout << node->book.title<<"\n";
        found = true;
    }
    if(node->right)
        found = found || printNodeLowHi(node->right, low, hi);
    return found;
}


void findGenre(Genre *genres, int numGenres, char *genreStr)
{   
    cout << "Finding Genre\n";
    for(int i = 0; i < numGenres; i++)
    {
        if(!strcmp(genres[i].genre, genreStr))
        {
            printNode(genres[i].root);
            return;
        }
    }
    cout << "Genre not found\n";
}

void findGenreLH(Genre *genres, int numGenres, char *genreStr, char *low, char *hi)
{
    cout << "Finding genre low hi \n";
    cout << low << " " << hi << "\n";
    for(int i = 0; i < numGenres; i++)
    {
        if(!strcmp(genres[i].genre, genreStr))
        {
            if(!printNodeLowHi(genres[i].root, low, hi))
                cout << "No books found for given range.\n";
            return;
        }
    }
    cout << "Genre not found\n";
}


void addHash(HashTableEntry *hashtable, BST *book)
{
    if(hashtable)
        if(hashtable->book)
            addHash(hashtable->next, book);
        else
        {
            hashtable->book = book;
            strncpy(hashtable->title, book->book.title, TITLE_LEN);
        }
    else
    {
        hashtable = new HashTableEntry;
        hashtable->book = book;
        strncpy(hashtable->title, book->book.title, TITLE_LEN);
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
        
        BST *newNode = new BST;
        
        newNode->book = *book;

        addHash(&hashTable[stringValue(book->title, prime)], add(&(genres[currentGenre].root), newNode));
    }
    
    int queries = 0;

    cin >> queries;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    for(int i = 0; i < queries; i++)
    {
        char query[200];
        char queryType[10];
        char findType[10];
        char queryTerm[100] = {0};
        char queryTermLow[10];
        char queryTermHi[10];
        cin.getline(query, 200);
        stringstream s(query);
        s >> queryType;
        if(!strcmp(queryType, "find"))
        {
            s >> findType;
            if(!strcmp(findType, "book"))
            {
                s.ignore(numeric_limits<streamsize>::max(), '\"');
                s.getline(queryTerm, 100, '\"');
                findBook(hashTable, queryTerm, prime);
            }
            else if(!strcmp(findType, "genre"))
            {
                s.ignore(numeric_limits<streamsize>::max(), '\"');
                s.getline(queryTerm, 100, '\"');
                findGenre(genres, numGenres, queryTerm);
            }
        }
        else if(!strcmp(queryType, "range"))
        {
            s.ignore(numeric_limits<streamsize>::max(), '\"');
            s.getline(queryTerm, 20, '\"');
            s.ignore(numeric_limits<streamsize>::max(), '\"');
            s.getline(queryTermLow, 10, '\"');
            s.ignore(numeric_limits<streamsize>::max(), '\"');
            s.getline(queryTermHi, 10, '\"');

            findGenreLH(genres, numGenres, queryTerm, queryTermLow, queryTermHi);
        }
        else if(!strcmp(queryType, "price"))
        {
            s.ignore(numeric_limits<streamsize>::max(), '\"');
            s.getline(queryTerm, 20, '\"');
            findPrice(hashTable, queryTerm, prime);
        }
    }
}
