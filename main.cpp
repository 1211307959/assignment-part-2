// ********************************************************* 
// Course: TCP1101 PROGRAMMING FUNDAMENTALS 
// Year: Trimester 1, 2022/23 (T2215) 
// Lab: T12L 
// Names: MUHAMMAD KASYFI KHUZAIRI BIN MOHD GHAZALI | YUVAN RAJ A/L RAJENDRAN | ARNALIN BINTI IBRAHIM 
// IDs: 1211307959 | 1171102249 | 1211306091 
// Emails: 1211307959@student.mmu.edu.my | 1171102249@student.mmu.edu.my | 1211306091@student.mmu.edu.my 
// Phones: 0166513686 | 01116412020 | 01136039588
// ********************************************************* 
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // for system()
#include <ctime>   // for time() in srand( time(NULL) );
#include <iomanip> // for setw()
#include <conio.h>
using namespace std;
bool gameRunning = true;
int Round = 0;
int count = 2;
int posX, posY;
class Zombie;
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
char **createGameBoard(Board &board)
{
    char **temp;
    temp = new char *[board.getDimY()];       
    for (int i = 0; i < board.getDimY(); i++) 
        temp[i] = new char[board.getDimX()];  
    return temp;                        
                                        
}
char getRandomObject()
{
    char objects[] = {'<', '>', '^', 'v', ' ', ' ', 'H', ' ','P', 'R', ' ', ' '};
    int noOfObjects = 10; // number of objects in the objects array
    
    int objNo = rand() % noOfObjects;
    return objects[objNo];
}

void Board::init(int dimX, int dimY)
{
    dimX_ = dimX;
    dimY_ = dimY;
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
            map_[i][j] = getRandomObject();
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
    char move;
    int aHp;
    int aAttack;
    void spawn(Board &board)
    {
        int posX = board.getDimX() / 2;
        int posY = board.getDimY() / 2;
        board.map_[posY][posX] = 'A';
    }
    Alien(int posX, int posY)
    {
        this->posX = posX;
        this->posY = posY;
    }
    void alienPlay(Board &board, Alien &alien, Zombie &zombie);
    void attribute();

private:
    int posX;
    int posY;
};

void examineNextPositions(char nextSpot, Alien &alien, Zombie &zombie)
{
    if (nextSpot == '^' || nextSpot == 'v' || nextSpot == '<' || nextSpot == '>')
    {
        alien.move = nextSpot;
        alien.aAttack += 20;
        cout << "Alein move changed to " << nextSpot << endl;
        cout << "Alein Attack +20 " <<  endl;
    }
    else if (nextSpot == 'h')
    {   
        if(alien.aHp <= 100){
            alien.aHp += 20;
        }
        cout << "Alein found a health pack " << endl;
        cout << "Alein's lifes increased by 20 " << endl
             << endl;
    }
    else if (nextSpot == 'p')
    {
        // int zombieNumber = damageClosestZombie(alien, zombies);
        // cout << "Zombie " << zombieNumber << " has recived damaged by 10"  << endl;
    }
    else if (nextSpot == ' ')
    {

        cout << "this spot is empty" << endl;
    }
}

void Alien::alienPlay(Board &board, Alien &alien, Zombie &zombie){
    while (true)
    {
        int nextX = alien.posX;
        int nextY = alien.posY;
        int GameBoardRows = board.getDimX();
        int GameBoardCols = board.getDimY();

        switch (move)
        {
        case '^':
            nextX = posX - 1;
            break;
        case 'v':
            nextX = posX + 1;
            break;
        case '<':
            nextY = posY - 1;
            break;
        case '>':
            nextY = posY + 1;
            break;
        }

        if (nextX == -1 || nextX >= GameBoardRows - 1 || nextY == -1 || nextY >= GameBoardCols - 1)
        {
            cout << "Alien hit a Game Board border and its turn ended." << endl;
            cout << nextX << endl;
            cout << GameBoardRows << endl;
            return;
        }
        else
        {
            char nextSpot = board.map_[nextX][nextY];
            if (nextSpot == 'r')
            {
                cout << "Alien hits a rock can't move" << endl;
                while (board.map_[nextX][nextY] == 'r')
                {
                    board.map_[nextX][nextY] = getRandomObject();
                }
                break;
            }
            else
            {

                examineNextPositions(nextSpot, alien, zombie);
                board.map_[nextX][nextY] = 'A';
                board.map_[posX][posY] = '.';
                posX = nextX;
                posY = nextY;
                system("pause");
                system("CLS");
                board.display();
            //     showGameBoard(GameBoard);
            //     showStatus(alien, zombies);
            }
        }
    }
}

void Alien::attribute(){
    aHp = 100;
    aAttack = 0;
    cout << "-> Alien :  Life "<< aHp ;
    cout <<", " <<"Attack " << aAttack << endl ;
}

class Zombie
{
public:
    int posX;
    int posY;
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
            } while ((x == mid_x && y == mid_y) || (x == posX && y == posY));
            board.map_[y][x] = id[i];
        }
    }
    void attribute();
    void zombieTurn(Alien &alien, char **GameBoard,Board board,Zombie zombie);
    

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
bool verifyZombieMove(int newX, int newY, char **GameBoard, Board board, Zombie zombie)
{
    for (int i = 0; i < count; i++)
    {
        if (newX >= 0 && newX < board.getDimX() && newY >= 0 && newY < board.getDimY() && GameBoard[newX][newY] != 'A' && GameBoard[newX][newY] != zombie.id[i])
        {
            return true;
        }
    }
    return false;
}

void Zombie::zombieTurn(Alien &alien, char **GameBoard, Board board, Zombie zombie)
{
    for (int i = 0; i < count; i++)
    {
    int newX = posX;
    int newY = posY;
    char moves[4] = {'v', '^', '<', '>'};
    int moveIndex;
    string moveorientation;
    do
    {
        moveIndex = rand() % 4;
        char move = moves[moveIndex];
        if (move == 'v')
        { 
            newX = posX + 1;
            moveorientation = "Down";
        }
        else if (move == '^')
        {
            newX = posX - 1;
            moveorientation = "Up";
        }
        else if (move == '>')
        { 
            newY = posY + 1;
            moveorientation = "Right";
        }
        else if (move == '<')
        {
            newY = posY - 1;
            moveorientation = "Left";
        }
    } while (!(verifyZombieMove(newX, newY, GameBoard, board, zombie)));

    cout << "Zombie moves " << moveorientation << endl;
    GameBoard[posX][posY] = ' ';
    posX = newX;
    posY = newY;
    GameBoard[posX][posY] = id[i];
    }
}

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
        Alien alien(posX, posY);
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
    Alien alien(posX, posY);
    alien.attribute();
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
void getCommand(Alien &alien, Board &board)
{
    bool running = true;

    string input, quitInput;
    cout << "command >";
    cin >> input;
    if (input == "w")
    {
      alien.move = '^';
    }
    else if (input == "s")
    {
        alien.move = 'v';
    }
    else if (input == "a")
    {
        alien.move = '<';
    }
    else if (input == "d")
    {
        alien.move = '>';
    }
    else if (input == "arrow")
    {
    }
    else if (input == "help")
    {
        getHelp();
        return;
    }
    else if (input == "save")
    {
    }
    else if (input == "load")
    {
    }
    else if (input == "quit")
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
    int count = 2;
    Board board;
    Alien alien(posX, posY);
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

void resetObjects(Board &board)
{
    // int GameBoardRows = board.getDimX();
    // int GameBoardCols = board.getDimY();    
    
    for (int i = 0; i < board.getDimX(); i++)
    {
        for (int j = 0; j < board.getDimY(); j++)
        {
            if (board.map_[i][j] == '.')
            {
                board.map_[i][j] = getRandomObject();
            }
        }
    }
}

int main()
{
    srand(time(NULL));
    Board board;
    Alien alien(posX, posY);
    Zombie zombie;
    char **GameBoard;
    GameBoard = createGameBoard(board);
    mainPage();

    while (gameRunning)
    {
        getCommand(alien, board);
        alien.alienPlay(board, alien, zombie);
        cout << "Alien turn ended" << endl;
        system("pause");
        cout << "Reset trail" << endl;
        system("pause");
        zombie.zombieTurn(alien, GameBoard, board, zombie);
        board.healthDisplay();
        Round++;
        if (Round > 5)
        {
            gameRunning = false;
        }
    }

    return 0;
}