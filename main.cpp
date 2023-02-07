#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // for system()
#include <ctime>   // for time() in srand( time(NULL) );
#include <iomanip> // for setw()
#include <conio.h>
using namespace std;
bool gameRunning = true;
int count = 2;

class Board
{
private:
    int dimX_, dimY_;          // to indicate private data

public:
    vector<vector<char>> map_; // convention to put trailing underscore
    Board(int dimX = 15, int dimY = 5);
    void init(int dimX, int dimY);
    void display() const;
    void gameSetting();
    void healthDisplay();

    int getDimX() const;
    int getDimY() const;
};

Board::Board(int dimX, int dimY)
{
    init(dimX, dimY);
    void gameSetting();
}
void Board::init(int dimX, int dimY)
{
    dimX_ = dimX;
    dimY_ = dimY;
    char objects[] = {'<', '>', '^', 'v', ' ', ' ', 'H', ' ','P', 'R', ' ', ' '};
    int noOfObjects = 10; // number of objects in the objects array
    // create dynamic 2D array using vector
    map_.resize(dimY_); // create empty rows
    for (int i = 0; i < dimY_; ++i)
    {
        map_[i].resize(dimX_); // resize each row
    }
    // put random characters into the vector array
    for (int i = 0; i < dimY_; ++i) 
    {
        for (int j = 0; j < dimX_; ++j)
        {
            int objNo = rand() % noOfObjects;
            map_[i][j] = objects[objNo];
        }
    }
}
void Board::display() const
{
    // comment this out during testing
    // system("cls"); // OR system("clear"); for Linux / MacOS
    cout << " --__--__--__--__--__" << endl;
    cout << " = Alien vs Zombie! =" << endl;
    cout << " __--__--__--__--__--" << endl;
    // for each row
    for (int i = 0; i < dimY_; ++i)
    {
        // display upper border of the row
        cout << " ";
        for (int j = 0; j < dimX_; ++j)
        {
            cout << "+-";
        }
        cout << "+" << endl;
        // display row number
        cout << setw(2) << (dimY_ - i);
        // display cell content and border of each column
        for (int j = 0; j < dimX_; ++j)
        {
            cout << "|" << map_[i][j];
        }
        cout << "|" << endl;
    }
    // display lower border of the last row
    cout << " ";
    for (int j = 0; j < dimX_; ++j)
    {
        cout << "+-";
    }
    cout << "+" << endl;
    // display column number
    cout << " ";
    for (int j = 0; j < dimX_; ++j)
    {
        int digit = (j + 1) / 10;
        cout << " ";
        if (digit == 0)
            cout << " ";
        else
            cout << digit;
    }
    cout << endl;
    cout << " ";
    for (int j = 0; j < dimX_; ++j)
    {
        cout << " " << (j + 1) % 10;
    }
    cout << endl
         << endl;
}
int Board::getDimX() const
{
    // Board board;
    return dimX_;
}
int Board::getDimY() const
{
    // Board board;
    return dimY_;
}
class Alien
{
public:
    void spawn(Board &board)
    {
        int middleX = board.getDimX() / 2;
        int middleY = board.getDimY() / 2;
        board.map_[middleY][middleX] = 'A';
    }
};

class Zombie
{
public:
    char id[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    void spawn(Board &board, int count)
    {
        int mid_x = board.getDimX() / 2;
        int mid_y = board.getDimY() / 2;
        int x, y;
        for (int i = 0; i < count; i++)
        {
            do
            {
                x = rand() % board.getDimX();
                y = rand() % board.getDimY();
            } while (x == mid_x && y == mid_y);
            board.map_[y][x] = id[i];
        }
    }
    void attribute();

private:
    int zHp;
    int zAttack;
    int range;
};

void Zombie::attribute(){

    for (int i = 0; i < count; i++)
    {
    zHp = (rand() % 4 + 1) * 50 + 50;
    zAttack = (rand() % 5 + 1) * 5; // 5 - 25
    range = rand() % 3 + 1; // 1 - 3

    cout << "   Zombie " << id[i] << " : Life "<< zHp ;
    cout << ", " <<"Attack " <<  zAttack << ',';
    cout << " Range  "<< range << endl;
    }
    cout << endl;
};

void Board::gameSetting()
{
    int newX = 0;
    int newY = 0;
    count = 0;
    bool odd = false;

    while (odd == false){
    cout << "Enter new value for Row => ";
    cin >> newX;
    cout << "Enter new value for Column => ";
    cin >> newY;
    cout << "Enter number of zombies => ";
    cin >> count;
    if (newX % 2 == 0 || newY % 2 == 0)
    {
        cout << endl;
        cout << "Invalid input." << endl;
        cout << "Make sure both row and column are in odd number." << endl
             << endl;
    }
    else
    {

        init( newX, newY);
        Alien alien;
        alien.spawn(*this);
        Zombie zombie;
        zombie.spawn(*this, count);
        cout << endl;
        cout << "Game settings updated!" << endl
             << endl;
        odd = true;
    }}
}

void Board::healthDisplay()
{
    int a_life = 100;
    int a_attack = 0;
    cout << "-> Alien :  Life "<< a_life ;
    cout <<", " <<"Attack " << a_attack<< endl ;

    Zombie zombie;
    zombie.attribute();
   
}

    void getHelp()
    {
        cout << "1. w - move up" << endl;
        cout << "2. s - move down" << endl;
        cout << "3. a - move left" << endl;
        cout << "4. d - move right" << endl;
        cout << "5. arrow - change the direction of the arrow" << endl;
        cout << "6. help - display user command" << endl;
        cout << "7. save - save the game" << endl;
        cout << "8. load - load the game" << endl;
        cout << "9. quit - quit the game" << endl
             << endl;
        system("pause");
    }
    void getCommand()
    {
        string input, quitInput;
        cout << "command >";
        cin >> input;
        if (input == "w")
        {
        }
        if (input == "s")
        {
        }
        if (input == "a")
        {
        }
        if (input == "d")
        {
        }
        if (input == "arrow")
        {
        }
        if (input == "help")
        {
            getHelp();
            return;
        }
        if (input == "save")
        {
        }
        if (input == "load")
        {
        }
        if (input == "quit")
        {
            cout << "Are you sure?(y/n)  => ";
            cin >> quitInput;
            if (quitInput == "Y" || quitInput == "y")
            {
                cout << endl;
                cout << "Goodbye!";
                gameRunning = false;
            }
            if (quitInput == "N" || quitInput == "n")
            {
                cout << endl;
                system("pause");
            }
        }
        else{
        cout << "Please enter valid command." << endl;
        cout << "press 'help' to display user command." << endl;
    }
}
void test1_1()
{
        Board board;
        Alien alien;
        Zombie zombie;
        alien.spawn(board);
        zombie.spawn(board, count);
        board.display();
        board.healthDisplay();
}

void mainPage()
{
    Board board;
    // Board.display();
    cout << "Default game settings" << endl;
    cout << "_____________________" << endl
         << endl;

    cout << "Row = " << board.getDimX() << endl;
    cout << "Column = " << board.getDimY() << endl;
    cout << "Zombie = 2" << endl << endl;

    string choice;
    bool onlyChoice = false;
    
    while(onlyChoice == false){
        // Make your choice to start a game
        cout << "Would you like to change the game setting?(y/n)  => ";
        cin >> choice;
        if (choice == "Y"|| choice == "y")
        {
            board.gameSetting();
            board.display();
            board.healthDisplay();
            onlyChoice = true;
        } else if (choice == "N"||choice == "n") {
            cout << "Default setting Mantained" << endl << endl;
            //system("pause");
            test1_1();
            onlyChoice = true;
        }
    }    
}
int main() {
    srand(1); // use this for fixed map during testing
    //srand(time(NULL)); // try this for random map
    //test1_1(); 
    mainPage();
    while (gameRunning)
    {
        getCommand();
    }
    return 0;
    //char choice;
}
