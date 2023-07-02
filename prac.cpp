#include <iostream>
#include <cstdlib>
#include <fstream>


using namespace std;

typedef struct node
{
    string username, password;
    int ascore, sscore, mscore, dscore;
    float allscore;
    struct node *next;
} LIST;

class Player
{
private:
    LIST *L;
public:
    void init();
    void login(string nm, string pw);
    void registration(string n, string p);
    void menu();
    int leaderBoard();
    int addition(int x);
    int subtraction(int x);
    int multiplication(int x);
    int division(int x);
    void aDisplay();
    void sDisplay();
    void mDisplay();
    void dDisplay();
    void allDisplay();
    float avg(int a,int b, int c, int d)
    {
        return (a+b+c+d)/3.0;
    }
    void save()
    {
        ofstream fp("game.txt");

        if (!fp)
        {
            cout << "Error: Unable to create the players_data.txt file.\n";
            return;
        }

        LIST *p = L;
        while (p != NULL)
        {
            fp << p->username << " " << p->password << " " << p->ascore << " "
                    << p->sscore << " " << p->mscore << " " << p->dscore << " "
                    << p->allscore << "\n";
            p = p->next;
        }
        fp.close();
        cout << "save";
        system("pause");
    }
    void load()
{
    ifstream fp("game.txt");
    if (!fp)
    {
        cout << "Error opening file." << endl;
        return;
    }

    string username, password;
    int ascore, sscore, mscore, dscore;
    float allscore;

    while (fp >> username >> password >> ascore >> sscore >> mscore >> dscore >> allscore)
{
    LIST *temp = new LIST;
    temp->username = username;
    temp->password = password;
    temp->ascore = ascore;
    temp->sscore = sscore;
    temp->mscore = mscore;
    temp->dscore = dscore;
    temp->allscore = allscore;
    temp->next=nullptr;

    if (L == NULL)
    {
        L = temp;
        temp->next = NULL;
    }
    else
    {
        temp->next = L;
        L = temp;
    }
}

    fp.close();
    cout << "load";
    system("pause");
}

};

void Player::init()
{
    L = NULL;
}

void Player::login(string nm, string pw)
{
    LIST *temp = L;
    while (temp != NULL)
    {
        if (temp->username == nm && temp->password == pw)
        {
            cout << "while loop" << endl;
            L = temp;
            return;
        }
        temp = temp->next;
    }
    cout << "\t\t\t  Login failed!" << endl;
    system("pause");
}

void Player::registration(string usrnm, string pass)
{
    LIST *p, *q, *temp;
    p = q = L;
    temp = new LIST;
    temp->username = usrnm;
    temp->password = pass;
    temp->ascore = 0;
    temp->sscore = 0;
    temp->mscore = 0;
    temp->dscore = 0;
    temp->allscore = 0;

    while (p != NULL && p->username < usrnm)
    {
        q = p;
        p = p->next;
    }

    if (p == L)
    {
        L = temp;
    }
    else
    {
        q->next = temp;
        temp->next = p;
    }
}

void Player::menu()
{
    int c;
    int score, items = 10;
    float fg;
    while (true)
    {
        system("cls");
        cout << "\t\t\t    1. Addition" << endl;
        cout << "\t\t\t    2. Subtraction" << endl;
        cout << "\t\t\t    3. Multiplication" << endl;
        cout << "\t\t\t    4. Division" << endl;
        cout << "\t\t\t    5. Leaderboards" << endl;
        cout << "\t\t\t    6. Return" << endl;
        cin >> c;

        switch (c)
        {
        case 1:
            system("cls");
            score = addition(items);
            cout << "\t\t\t   ===================================================\n";
            cout << "\t\t\t   You got " << score << " correct answers out of " << items << " questions.\n";
            fg = (float)score / items * 100;
            cout << "\t\t\t   You got " << fg << "% for addition.\n";
            system("pause");
            break;
        case 2:
            system("cls");
            score = subtraction(items);
            cout << "\t\t\t   ===================================================\n";
            cout << "\t\t\t   You got " << score << " correct answers out of " << items << " questions.\n";
            fg = (float)score / items * 100;
            cout << "\t\t\t   You got " << fg << "% for addition.\n";
            save();
            system("pause");
            break;
        case 3:
            system("cls");
            score = multiplication(items);
            cout << "\t\t\t   ===================================================\n";
            cout << "\t\t\t   You got " << score << " correct answers out of " << items << " questions.\n";
            fg = (float)score / items * 100;
            cout << "\t\t\t   You got " << fg << "% for addition.\n";
            save();
            system("pause");
            break;
        case 4:
            system("cls");
            score = division(items);
            cout << "\t\t\t   ===================================================\n";
            cout << "\t\t\t   You got " << score << " correct answers out of " << items << " questions.\n";
            fg = (float)score / items * 100;
            cout << "\t\t\t   You got " << fg << "% for addition.\n";
            save();
            system("pause");
            break;
        case 5:
            system("cls");
            leaderBoard();
            break;
        case 6:
            return;
        default:
            cout << "Invalid Input.";
            break;
        }
    }
}

int Player::leaderBoard()
{
    int ch;
    while (true)
    {
        system("cls");
        cout << "\t\t\t    1. Addition Leaderboard" << endl;
        cout << "\t\t\t    2. Subtraction Leaderboard" << endl;
        cout << "\t\t\t    3. Multiplication Leaderboard" << endl;
        cout << "\t\t\t    4. Division Leaderboard" << endl;
        cout << "\t\t\t    5. Overall Leaderboards" << endl;
        cout << "\t\t\t    6. Return" << endl;
        cin >> ch;

        switch (ch)
        {
        case 1:
            system("cls");
            aDisplay();
            break;
        case 2:
            system("cls");
            sDisplay();
            break;
        case 3:
            system("cls");
            mDisplay();
            break;
        case 4:
            system("cls");
            dDisplay();
            break;
        case 5:
            system("cls");
            allDisplay();
            break;
        case 6:
            return 0;
        default:
            cout << "Invalid Input.";
            break;
        }
    }
}

int Player::addition(int x)
{
    int i, a, b, c, cor = 0;
    int score = 0;

    cout << "\t\t\t    Arithmetic Addition Game!" << endl
         << endl;
    for (i = 0; i < 10; i++)
    {
        a = rand() % 20 + 1;
        b = rand() % 20 + 1;
        cout << "\t\t\t   " << i + 1 << ".) What is " << a << " + " << b << "? ";
        cin >> c;

        if (c == a + b)
        {
            cout << "\t\t\t   Very Good!" << endl;
            cor++;
        }
        else
        {
            cout << "\t\t\t   The answer is " << a + b << "." << endl;
        }
    }
    score = cor;
    if (L != NULL) // Store the score in the current user's node
    {
        L->ascore = score;
    }
    return score;
}

int Player::subtraction(int x)
{
    int i, a, b, c, cor = 0;
    int score = 0;

    cout << "\t\t\t    Arithmetic Addition Game!" << endl
         << endl;
    for (i = 0; i < 10; i++)
    {
        a = rand() % 10 + 1;
        b = rand() % a + 1;
        cout << "\t\t\t   " << i + 1 << ".) What is " << a << " - " << b << "? ";
        cin >> c;

        if (c == a - b)
        {
            cout << "\t\t\t   Very Good!" << endl;
            cor++;
        }
        else
        {
            cout << "\t\t\t   The answer is " << a - b << "." << endl;
        }
    }
    score = cor;
    if (L != NULL) // Store the score in the current user's node
    {
        L->sscore = score;
    }
    return score;
}

int Player::multiplication(int x)
{
    int i, a, b, c, cor = 0;
    int score = 0;

    cout << "\t\t\t    Arithmetic Addition Game!" << endl
         << endl;
    for (i = 0; i < 10; i++)
    {
        a = rand() % 10 + 1;
        b = rand() % 10 + 1;
        cout << "\t\t\t   " << i + 1 << ".) What is " << a << " * " << b << "? ";
        cin >> c;

        if (c == a * b)
        {
            cout << "\t\t\t   Very Good!" << endl;
            cor++;
        }
        else
        {
            cout << "\t\t\t   The answer is " << a * b << "." << endl;
        }
    }
    score = cor;
    if (L != NULL) // Store the score in the current user's node
    {
        L->mscore = score;
    }
    return score;
}

int Player::division(int x)
{
    int i, a, b, c, cor = 0;
    int score = 0;

    cout << "\t\t\t    Arithmetic Addition Game!" << endl
         << endl;
    for (i = 0; i < 10; i++)
    {
        b = rand() % 10 + 1;
        a = b * (rand() % 10 + 1);
        cout << "\t\t\t   " << i + 1 << ".) What is " << a << " / " << b << "? ";
        cin >> c;

        if (c == a + b)
        {
            cout << "\t\t\t   Very Good!" << endl;
            cor++;
        }
        else
        {
            cout << "\t\t\t   The answer is " << a + b << "." << endl;
        }
    }
    score = cor;
    if (L != NULL) // Store the score in the current user's node
    {
        L->dscore = score;
    }
    return score;
}

void Player::aDisplay()//should be sorted
{
    LIST *p;
    p = L;
    int i = 1;
    cout << "\t\t\t   ==========================\n";
    cout << "\t\t\t   Addition Leaderboard\n";
    cout << "\t\t\t   ==========================\n\n";
    cout << "\t\t\t    Usernames\t\tScores\n\n";

    // Iterate through the list and display scores
    while (p != NULL)
    {
        cout << "\t\t\t   " << i++ << ".) " << p->username << " \t\t  " << p->ascore << endl;
        p = p->next;
        break;
    }
    system("pause");
}


void Player::sDisplay()//should be sorted
{
    LIST *p = L;

    cout << "\t\t\t   ==========================\n";
    cout << "\t\t\t   Subtraction Leaderboard\n";
    cout << "\t\t\t   ==========================\n\n";
    cout << "\t\t\t    Usernames\t\tScores\n\n";
    int i = 0;

    // Iterate through the list and display scores
    while (p != NULL)
    {
        cout << "\t\t\t   " << i+1 << ".) " << p->username << " \t\t  " << p->sscore << endl;
        i++;
        p=p->next;
    }
    system("pause");
}

void Player::mDisplay()// should be sorted
{
    LIST *p = L;

    cout << "\t\t\t   ==========================\n";
    cout << "\t\t\t   Multiplication Leaderboard\n";
    cout << "\t\t\t   ==========================\n\n";
    cout << "\t\t\t    Usernames\t\tScores\n\n";

    int i = 0;

    // Iterate through the list and display scores
    while (p != NULL)
    {
        cout << "\t\t\t   " << i+1 << ".) " << p->username << " \t\t  " << p->mscore << endl;
        i++;
        p=p->next;
    }
    system("pause");
}

void Player::dDisplay()//should be sorted
{
    LIST *p = L;

    cout << "\t\t\t   ==========================\n";
    cout << "\t\t\t   Division Leaderboard\n";
    cout << "\t\t\t   ==========================\n\n";
    cout << "\t\t\t    Usernames\t\tScores\n\n";

    int i = 0;

    // Iterate through the list and display scores
    while (p != NULL)
    {
        cout << "\t\t\t   " << i+1 << ".) " << p->username << " \t\t  " << p->dscore << endl;
        i++;
        p=p->next;
    }
    system("pause");
}

void Player::allDisplay()//should save the top 10
{
    LIST *p = L;
    float ave;
    cout << "\t\t\t   ==========================\n";
    cout << "\t\t\t   Overall Leaderboard\n";
    cout << "\t\t\t   ==========================\n\n";
    cout << "\t\t\t    Usernames\t\tScores\n\n";

    int i = 0;

    // Iterate through the list and display scores
    while (p != NULL)
    {
        ave=avg(p->ascore,p->sscore,p->mscore,p->dscore);
        cout << "\t\t\t   " << i+1 << ".) " << p->username << " \t\t  " << p->allscore << "/40" << endl;
        i++;
        p=p->next;
    }
    system("pause");
}

int main()
{
    Player player;
    int choice;
    player.init();
    player.load();
    while (true)
    {
        system("cls");
        cout << "\t\t\t______________________________________________\n\n";
        cout << "\t\t\t       Welcome to Arithmetic Practice Game" << endl;
        cout << "\t\t\t______________________________________________\n\n";
        cout << "\t\t\t      1. LogIn" << endl;
        cout << "\t\t\t      2. Register" << endl;
        cout << "\t\t\t      3. Exit" << endl;
        cout << "\t\t\t      Input choice : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            system("cls");
            string n, p;
            cout << "\t\t\t     LOGIN FORM" << endl
                 << endl;
            cout << "\t\t\t   Username : ";
            cin >> n;
            cout << "\t\t\t   Password : ";
            cin >> p;
            player.login(n, p);
            player.menu();
            break;
        }
        case 2:
        {
            system("cls");
            string n, p;
            cout << "\t\t\t     REGISTRATION FORM" << endl
                 << endl;
            cout << "\t\t\t   Username : ";
            cin >> n;
            cout << "\t\t\t   Password : ";
            cin >> p;
            player.registration(n, p);
            break;
        }
        case 3:
        {
            player.save();
            exit(0);
        }
        default:
        {
            cout << "Incorrect input.";
            system("pause");
            break;
        }
        }
    }
}

