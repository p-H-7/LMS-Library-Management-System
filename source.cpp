#include <iostream>
#include <cstring>
#include <dirent.h>
#include <sys/types.h>
#include <fstream>
#include <vector>
#include <regex>
using namespace std;

int SearchForSub(string, string);

class book
{
    string fileName;
    string filePath;
    string name;
    string author;
    string type;

public:
    book() {}

    book(string str, const char *path)
    {
        type = "Novel";
        filePath = (string)path + "/" + str;
        fileName = str;
        //cout<<fileName<<endl;
        fstream new_file;
        new_file.open(filePath, ios::in);
        if (!new_file)
            cout << "No such file" << endl;

        else
        {
            string word;
            while (!new_file.eof())
            {
                new_file >> word;
                if (word == "Title:")
                    getline(new_file, name);

                if (word == "Author:")
                    getline(new_file, author);

                if (word == "ACT")
                {
                    type = "Play";
                    break;
                }
            }
        }
        new_file.close();
    }

    void printBook()
    {
        cout << fileName << endl
             << "Name:" << name << endl
             << "Author:" << author << endl
             << "Type: " << type << endl;
    }

    void printToFile(fstream &File)
    {
        File << "Name: " << name << " Type: " << type << endl;
    }

    string getName()
    {
        return name;
    }

    string getFilePath()
    {
        return filePath;
    }

    string getType()
    {
        return type;
    }

    int SearchForTitle(string titEx)
    {
        return SearchForSub(titEx, name);
    }

    int SearchForAuthor(string str)
    {
        return SearchForSub(str, author);
    }
};

class TopFive
{
    unsigned int count;
    string chapter;

public:
    TopFive()
    {
        chapter = "empty";
    }

    bool operator<(const TopFive &s) const
    {
        return (count < s.count);
    }

    void setChapter(string ch)
    {
        chapter = ch;
    }

    string getChapter()
    {
        return chapter;
    }

    void initCount()
    {
        count = 0;
    }

    void IncCount()
    {
        count++;
    }

    unsigned int getCount()
    {
        return count;
    }
};

class LMS
{
    //book *list;
    vector<book> list;
    //int listSize;

public:
    LMS() {}

    void add(book &text)
    {
        //static int i = 0;
        //list[i] = text;
        list.push_back(text);
        //i++;
        //listSize = i;
        //cout<<i<<endl;
    }

    void printList()
    {
        int j = 0;
        cout << "List Size: " << list.size() << endl;
        while (j < list.size())
        {
            list.at(j).printBook();
            j++;
        }
    }

    int getSize()
    {
        return list.size();
    }

    void IndexFile();

    void SearchForBook();

    void DisplayBook();

    void AnalyticTasks();
};

//void list_dir(const char *, LMS);
//void lmsInterface(LMS &, const char*);
//void NewBook(LMS &, const char*);

void list_dir(const char *path, LMS &temp)
{
    struct dirent *entry;
    DIR *dir = opendir(path);
    if (dir == NULL)
    {
        return;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".DS_Store") == 0)
            continue;
        else
        {
            //printf("%s\n",entry->d_name);
            book ex(entry->d_name, path);
            temp.add(ex);
        }
    }
    closedir(dir);
    //return path;
}

void NewBook(LMS &lmsEx, const char *path)
{
    LMS temp;

    list_dir(path, temp);

    if (temp.getSize() > lmsEx.getSize())
    {
        cout << "New Book Added" << endl;
        lmsEx = temp;
    }

    else
        cout << "NO new Book" << endl;
}

void lmsInterface(LMS &demo, const char *path)
{
    demo.IndexFile();
    //demo.printList();
    // demo.SearchForBook();
    //demo.DisplayBook();

    int ch;
    do
    {
        //clrscr();
        cout << "\n\n\nMAIN MENU";
        cout << "\n\nEnter 1 to GET THE LIST OF BOOKS IN THE DIRECTORY";
        cout << "\n\nEnter 2 to SEARCH FOR A BOOK";
        cout << "\n\nEnter 3 to check if a NEW BOOK has been added";
        cout << "\n\nEnter 4 to DISPLAY A BOOK FROM THE ABOVE LISTS";
        cout << "\n\nEnter 5 to perform ANALYTICS TASK";
        cout << "\n\nEnter 6 to exit";
        cout << "\n\nPlease Select Your Option (1-6) ";
        cin >> ch;
        cout << "\n\n\n";
        switch (ch)
        {
        case 1:
            demo.printList();
            break;
        case 2:
            demo.SearchForBook();
            break;
        case 3:
            NewBook(demo, path);
            demo.IndexFile();
            break;
        case 4:
            demo.DisplayBook();
            break;
        case 5:
            demo.AnalyticTasks();
            break;
        case 6:
            exit(0);
        default:
            cout << "\a";
        }
    } while (ch != 6);
}

int main()
{
    char *dir;
    cout << "Input directory path" << endl;
    cin >> dir;

    LMS lEx;
    //const char* path;
    list_dir(dir, lEx);
    lmsInterface(lEx, dir);
    return 0;
}

int SearchForSub(string small, string big)
{
    int M = small.length();
    int N = big.length();

    for (int i = 0; i <= N - M; i++)
    {
        int j;

        for (j = 0; j < M; j++)
            if (big[i + j] != small[j])
                break;

        if (j == M)
            return 1;
    }

    return -1;
}

void LMS::IndexFile()
{
    fstream new_file;
    new_file.open("/Users/haasitapinnepu/Desktop/index.txt", ios::out);
    if (!new_file)
        cout << "No such file" << endl;

    else
    {
        int j = 0;
        while (j < list.size())
        {
            list.at(j).printToFile(new_file);
            j++;
        }
    }
    new_file.close();
}

void LMS::SearchForBook()
{
    vector<string> MatchingBooks;
    MatchingBooks.clear();
    cout << "!!Search for a book!!" << endl;
    cout << "Enter the parameter to be used:(Title / Author)" << endl;
    string flag;
    cin >> flag;
    string trash;
    getline(cin, trash);

    if (flag == "Title" || flag == "title")
    {
        cout << "Enter the title" << endl;
        string titEx;
        getline(cin, titEx);

        int j = 0;
        while (j < list.size())
        {
            int res = list.at(j).SearchForTitle(titEx);
            if (res != -1)
                MatchingBooks.push_back(list.at(j).getName());
            j++;
        }
        if (MatchingBooks.size() == 0)
            cout << "Not Found" << endl;
    }

    else if (flag == "Author" || flag == "author")
    {
        cout << "Enter the Name" << endl;
        string aname;
        getline(cin, aname);

        int j = 0;
        while (j < list.size())
        {
            int res = list.at(j).SearchForAuthor(aname);
            if (res != -1)
                MatchingBooks.push_back(list.at(j).getName());
            j++;
        }
        if (MatchingBooks.size() == 0)
            cout << "Not Found" << endl;
    }

    else
        cout << "Invalid Parameter" << endl;

    if (MatchingBooks.size() != 0)
    {
        cout << "The matching Books from the search are:" << endl;

        for (int i = 0; i < MatchingBooks.size(); i++)
        {
            cout << MatchingBooks[i] << endl;
        }
    }
}

void LMS::DisplayBook()
{
    string trash;
    getline(cin, trash);
    cout << "Enter the name of the book to be displayed:" << endl;
    string titEx;
    getline(cin, titEx);

    int j = 0;
    string filePath = "empty";
    //string type;
    while (j < list.size())
    {
        int res = list[j].SearchForTitle(titEx);
        if (res != -1)
        {
            filePath = list[j].getFilePath();
            //type = list[j].getType();
        }
        j++;
    }

    if (filePath == "empty")
        cout << "Invalid Book Name" << endl;

    else
    {
        fstream new_file;
        new_file.open(filePath, ios::in);
        if (!new_file)
            cout << "No such file" << endl;

        else
        {
            string line;
            while (!new_file.eof())
            {
                getline(new_file, line);
                int res = SearchForSub("START OF THIS PROJECT GUTENBERG EBOOK", line);

                if (res != -1)
                    break;
            }

            int line_count = 0;

            while (line_count < 56)
            {
                getline(new_file, line);
                cout << line << endl;
                line_count++;
            }
        }
        new_file.close();
    }
}

int CheckDup(vector<string> &vic, string str)
{
    if (vic.empty())
        return 1;

    else
    {
        for (int i = 0; i < vic.size(); i++)
        {
            if (vic.at(i) == str)
                return 0;
        }

        return 1;
    }
}

void LMS::AnalyticTasks()
{
    string trash;
    getline(cin, trash);
    cout << "Enter the name of the selected book: " << endl;
    string Selected;
    getline(cin, Selected);

    string selType = "empty";
    string SelFilePath;

    int j = 0;
    while (j < list.size())
    {
        int res = list[j].SearchForTitle(Selected);
        if (res != -1)
        {
            selType = list[j].getType();
            SelFilePath = list[j].getFilePath();
        }
        j++;
    }

    if (selType == "empty")
        cout << "Invalid Book name" << endl;

    else if (selType == "Novel")
    {
        cout << "Give the input word" << endl;
        string myInput;
        cin >> myInput;

        //cout<<"Before vector"<<endl;
        vector<TopFive> top(200);
        //cout<<"After vector"<<endl;

        fstream new_file;
        new_file.open(SelFilePath, ios::in);
        if (!new_file)
            cout << "No such file" << endl;

        else
        {
            int k = -1;
            string line;
            while (!new_file.eof())
            {
                getline(new_file, line);
                //cout<<"Before Chapter"<<endl;
                int res = SearchForSub("CHAPTER", line);
                //cout<<"After Chapter"<<endl;

                if (res != -1)
                {
                    //cout<<"Found Chapter"<<endl;
                    k++;
                    top[k].setChapter(line);
                    top[k].initCount();
                    getline(new_file, line);
                }

                int n = SearchForSub(myInput, line);

                if (n != -1)
                {
                    top[k].IncCount();
                }
            }
            //cout << k << endl;
            //cout << top.size() << endl;
            sort(top.begin(), top.end());

            if (top.size() == 0)
                cout << "Error in finding chapter" << endl;

            else if (top.size() != 0)
            {
                cout << "The top 5 chapters with the most occurences of the given word are: " << endl;

                int chapCount = 0;
                for (int f = 0; f < top.size() && chapCount < 5; f++)
                {

                    if (top[f].getChapter() != "empty")
                    {
                        cout << top[f].getChapter() << endl;
                        chapCount++;
                    }
                }
            }
        }
        new_file.close();
    }

    else if (selType == "Play")
    {
        cout << "Give the Input Character(All CAPS)" << endl;
        string myCharacter;
        cin >> myCharacter;

        myCharacter = myCharacter;
        vector<string> list;

        fstream new_file;
        new_file.open(SelFilePath, ios::in);
        if (!new_file)
            cout << "No such file" << endl;

        else
        {
            //int k = -1;
            string line;
            vector<string> buffer;
            int flag = 0;
            while (!new_file.eof())
            {

                getline(new_file, line);
                int res = SearchForSub("SCENE", line);

                if (res != -1)
                {
                    //cout << "Enter scene" << endl;
                    buffer.clear();
                    flag = 0;
                    getline(new_file, line);
                }

                if (regex_match(line, regex("([A-Z])*.")))
                {
                    //cout << "Enter char" << endl;
                    if (SearchForSub(myCharacter, line) == -1)
                    {
                        //cout << "Enter buffer" << endl;
                        if (CheckDup(buffer, line))
                        {
                            //cout<<"Enter push buffer"<<endl;
                            buffer.push_back(line);
                            //cout<<buffer.size()<<endl;
                        }
                    }

                    if (SearchForSub(myCharacter, line) != -1)
                    {
                        flag = 1;
                    }
                }

                if (flag == 1)
                {
                    //cout << "Enter clause" << endl;
                    int i = 0;
                    //cout<<buffer.size()<<endl;
                    while (i < buffer.size())
                    {
                        //cout<<"Enter for"<<endl;
                        if (CheckDup(list, buffer.at(i)))
                        {
                            //cout << "Enter list" << endl;
                            list.push_back(buffer.at(i));
                        }
                        i++;
                    }
                    buffer.clear();
                }
            }
        }
        new_file.close();

        if (list.size() == 0)
            cout << "List error" << endl;

        else if (list.size() != 0)
        {
            cout << "The characters appearing in atleast one scene along with given character are:" << endl;
            for (int i = 0; i < list.size(); i++)
            {
                cout << list[i] << endl;
            }
        }
    }

    else
        cout << "Not Applicable" << endl;
}