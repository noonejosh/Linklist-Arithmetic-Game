#include <iostream>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <vector>

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
        LIST *p = L;
        if (fp.is_open())
        {
            while (p != NULL)
            {
                fp << p->username << " " << p->password << " " << p->ascore << " "
                        << p->sscore << " " << p->mscore << " " << p->dscore << " "
                        << p->allscore << "\n";
                p = p->next;
            }
            fp.close();
        }
        else
        {
            cout << "File error." << endl;
        }
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

        LIST *temp = L;
        while (temp != NULL && fp >> username >> password >> ascore >> sscore >> mscore >> dscore >> allscore)
        {
            registration(username,password);
            temp->ascore=ascore;
            temp->sscore=sscore;
            temp->mscore=mscore;
            temp->dscore=dscore;
            temp->allscore=allscore;
        }

        fp.close();
        cout << "load";
        cout << temp << endl;
        system("pause");
    }

};

void Player::init()
{
    L = NULL;
}

void Player::login(string nm, string pw)
{
    LIST *temp; // Initialize p to the head of the linked list
    cout << L << endl;
    cout << temp << endl;
    temp=L;
    while (temp != NULL)
    {
        if (temp->username == nm && temp->password == pw)
        {
            temp=L; // Update L to point to the current player node
            cout << L << endl;
            cout << temp << endl;
            return;
            system("pause");
        }
        temp = temp->next;
    }

    if(temp==NULL)
    {
        cout << "\t\t\t  Login failed!" << endl;
        system("pause");
    }
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
    temp->next=nullptr;

    while (p != NULL && p->username < usrnm)
    {
        q = p;
        p = p->next;
    }

    if (p == L)
    {
        temp->next = L;
        L = temp;
    }
    else
    {
        temp->next = p;
        q->next = temp;
    }
}


