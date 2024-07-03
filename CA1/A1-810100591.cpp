#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

typedef struct PAGES
{
    string date;
    vector<string> diary;
    int positive_words;
    int num_of_chars;
} PAGES;

int char_counter(string new_word, PAGES *the_page);
void PW_counter(string new_word, PAGES *the_page);
void input(string *new_word, PAGES *new_day);
void output(PAGES *day);
void show_tabloid(PAGES *day);
PAGES *search_day(string the_date, vector<PAGES> *note_book, int num_pages);
PAGES *search_longest_day(int num_pages, vector<PAGES> *note_book);
PAGES *search_best_day(int num_pages, vector<PAGES> *note_book);

int main()
{
    string new_word;
    PAGES new_page;
    vector<PAGES> note_book;
    int num_of_pages = 0;
    new_page.positive_words = 0;
    new_page.num_of_chars = 0;
    while (cin >> new_word)
    {
        if (new_word == "start_day")
        {
            cin >> new_page.date;
            note_book.push_back(new_page);
            num_of_pages++;
        }
        else if (new_word == "show_day")
        {
            string date;
            cin >> date;
            PAGES *day = search_day(date, &note_book, num_of_pages);
            output(day);
        }
        else if (new_word == "show_the_longest_day")
        {
            PAGES *day = search_longest_day(num_of_pages, &note_book);
            show_tabloid(day);
        }
        else if (new_word == "show_the_best_day")
        {
            PAGES *day = search_best_day(num_of_pages, &note_book);
            show_tabloid(day);
        }
        else
        {
            input(&new_word, &(note_book[num_of_pages - 1]));
            char_counter(new_word, &(note_book[num_of_pages - 1]));
            PW_counter(new_word, &(note_book[num_of_pages - 1]));
        }
    }
    return 0;
}

int char_counter(string new_word, PAGES *the_page)
{
    //اگر صفحه ناموجود بود خطا برمیگردانیم.
    if (the_page == NULL)
    {
        return 1;
    }
    //تعداد کاراکتر ها را به روز میکنیم.
    (the_page->num_of_chars) += new_word.length();
    return 0;
}

void PW_counter(string new_word, PAGES *the_page)
{
    fstream file;
    string w1, w2;
    file.open("positive-words.txt", ios::in);
    while (true)
    {
        file >> w1;
        w2 = w1;
        if (file.eof())
        {
            break;
        }
        w1.append(" ");
        w2.append("\n");
        int found1 = -1, found2;
        found2 = new_word.find(w2);
        if (found2 != string::npos)
        {
            the_page->positive_words += 1;
        }
        for (int i = 0; i < ((new_word.length()) / 3); i++)
        {
            found1 = new_word.find(w1, found1 + 1);
            if (found1 == string::npos)
            {
                break;
            }
            else
            {
                if (found1 == 0 || new_word[found1 - 1] == ' ')
                {
                    the_page->positive_words += 1;
                }
            }
        }
    }
    file.close();
}

void input(string *new_word, PAGES *new_day)
{
    string temp;
    getline(cin, temp);
    temp.append("\n");
    (*new_word).append(temp);
    (new_day->diary).push_back(*new_word);
}

void output(PAGES *day)
{
    //خاطرات یک روز را چاپ میکنند.
    for (int i = 0; i < (day->diary).size(); i++)
    {
        cout << (day->diary[i]);
    }
}

void show_tabloid(PAGES *day)
{
    cout << (day->date) << '\n';
    if ((day->num_of_chars) <= 20)
    {
        output(day);
    }
    else
    {
        int counter = 20;
        for (int i = 0; i < (day->diary).size(); i++)
        {
            if ((day->diary[i].length()) >= counter)
            {
                cout << (day->diary[i]).substr(0, counter) << "...\n";
                break;
            }
            else
            {
                counter = (counter - ((day->diary[i].length())));
                cout << (day->diary[i]);
            }
        }
    }
}

PAGES *search_day(string the_date, vector<PAGES> *note_book, int num_pages)
{
    for (int i = 0; i < num_pages; i++)
    {
        if ((*note_book)[i].date == the_date)
        {
            //شی مورد نظر را از لیستل از شی ها میابیم و بر میگردانیم.
            return &((*note_book)[i]);
        }
    }
    //اگر شی وجود نداشت null برمیگردانیم.
    return NULL;
}

PAGES *search_longest_day(int num_pages, vector<PAGES> *note_book)
{
    //اگر لیست خالی بود null برمیگردانیم.
    if (num_pages == 0)
    {
        return NULL;
    }
    PAGES *longest = &((*note_book)[0]);
    //بلندترین روز را می یابیم و بر میگردانیم.
    for (int i = 0; i < num_pages; i++)
    {
        if ((*note_book)[i].num_of_chars >= longest->num_of_chars)
        {
            longest = &((*note_book)[i]);
        }
        else if ((*note_book)[i].num_of_chars = longest->num_of_chars)
        {
            for (int j = 9; j > -1; j++)
            {
                if ((int)(((*note_book)[i].date)[j]) < ((int)(longest->date[j])))
                {
                    longest = &((*note_book)[i]);
                    break;
                }
            }
        }
    }
    return longest;
}

PAGES *search_best_day(int num_pages, vector<PAGES> *note_book)
{
    if (num_pages == 0)
    {
        return NULL;
    }
    PAGES *best = &((*note_book)[0]);
    for (int i = 0; i < num_pages; i++)
    {
        if ((*note_book)[i].positive_words >= best->positive_words)
        {
            best = &((*note_book)[i]);
        }
        else if ((*note_book)[i].positive_words = best->positive_words)
        {
            for (int j = 9; j > -1; j++)
            {
                if ((int)(((*note_book)[i].date)[j]) < ((int)(best->date[j])))
                {
                    best = &((*note_book)[i]);
                    break;
                }
            }
        }
    }
    return best;
}