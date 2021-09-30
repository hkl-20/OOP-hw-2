#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

using namespace std;

//Structure to keep track of various locations
struct Point
{
    int x;
    int y;

    Point(int _x, int _y): x(_x), y(_y)
    {

    }
};
//Structure for the Player object
struct Player
{
    int food;
    int health;
    bool alive;
    int x;
    int y;
    Player()
    {
        food = 64;
        health = 10;
        alive = true;
    }
    void loseHealth()
    {
        if(health>0)
            health--;
        if(health==0)
            alive = false;
    }
    void gainHealth()
    {
        if(health<10)
            health++;
    }
};

typedef const int cint;         //Google typedef to see what this means
typedef const Point cPoint;

char* CreateDungeon(int, int, Point&, Point&);      //Creates the dungeon
void Traversal(char*, Point&, cPoint&, cint, cint); //Used for moving inside dungeon
void Combat(Player&, int);  //Used for simulating combat
void TrapStatements();  //3 statements that show at random when the player activates a trap
void FoodStatements();  //3 statements that show at random when the player finds food
void HitStatements();   //3 statements that show at random when the player hits enemy
void GetHitStatements();//3 statements that show at random when the player gets hit

int main ()
{
    srand(time(0));

    int width = 8;
    int height = 8;

    /*
    *   ADD YOUR CODE HERE IF REQUIRED
    */

    Point startPoint(0,0);
    Point exitPoint(0,0);

    char* dungeon = nullptr;

    dungeon = CreateDungeon(width, height, startPoint, exitPoint);

    Traversal(dungeon, startPoint, exitPoint, width, height);

    /*
    *   ADD YOUR CODE HERE IF REQUIRED
    */
    
    for (int i = 0; i < height*width; i ++){
        cout << dungeon[i] << " "; 
        if ((i + 1) % width == 0){
            cout << endl;
        }

    }


    return 0;
}

void TrapStatements()
{
    /*
    *   ADD YOUR CODE HERE AS REQUIRED
    */
}

void FoodStatements()
{
    /*
    *   ADD YOUR CODE HERE AS REQUIRED
    */
}

void HitStatements()
{
    /*
    *   ADD YOUR CODE HERE AS REQUIRED
    */
}

void GetHitStatements()
{
    /*
    *   ADD YOUR CODE HERE AS REQUIRED
    */
}

void Traversal(char* dungeon, Point& startPoint, cPoint& exitPoint, cint width, cint height)
{
    /*
    *   ADD YOUR CODE HERE AS REQUIRED. DEFINE NEW FUNCTIONS IF IT GETS LONG.
    */
    
    for(int i = 0; i < width; i++){
        dungeon[i] = 'W';
    }

    for(int i = height*width - width; i < height*width; i++){
        dungeon[i] = 'W';
    }

    for(int i = width; i < width*height - width; i = i + width){
        dungeon[i] = 'W';
    }

    for(int i = width*2 - 1; i < width*height - width; i = i + width){
        dungeon[i] = 'W';
    }
    
    int a, b;
    //Random Objects
    for (int i = width + 1; i < (height*width - width - 1); i++){
        if ((i) % width != 0 && (i + 1) % width != 0 ){

            a = (rand() % 100);

            if ( a <= 20 ){

                b = (rand() % 100);
                
                if ((b >= 0) && (b < 15) ){
                    dungeon[i] = 'E';
                }
                else if((b >= 15) && (b < 30) ){
                    dungeon[i] = 'H';
                }
                else if((b >= 30) && (b < 45) ){
                    dungeon[i] = 'T';
                }
                else if((b >= 45) && (b < 60) ){
                    dungeon[i] = 'F';
                }
                else{
                    dungeon[i] = 'W';
                }


            }
        }
    }

    //Person 
    
    int person;
    person = rand() % (height - 2);
  
    cout << person << endl;
  
    if (dungeon[(person * width ) + 1] == ' '){
        dungeon[(person * width ) + 1] = 'P';
        
    }
    else{
        dungeon[width + 1] = 'P';
    }
    
    //Exit 

    int exit;
    exit = rand() % (height - 2);

    cout << exit << endl;

    if (dungeon[((exit + 1) * width)  - 2] == ' '){
        dungeon[((exit + 1) * width)  - 2] = 'X';
    }
    else{
        dungeon[width*height - width - 2] = 'X';
    }

    //Game
// KINDA STUCK AT THIS PART
  //  char userinput;

  //  cout << "Press S to start" << endl;

  //  cin >> userinput;

  //  cout << startPoint.x << " " << startPoint.y << endl;

  //  while (userinput != 'x'){
  //      cout << "UP -> U, DOWN -> D, LEFT -> L, RIGHT -> R" << endl;
  //      cin >> userinput;
    //    if (userinput == 'U'){
   //         dungeon[]
   //     }
  //  }



    



   

   

}

void Combat(Player& player, int enemies)
{
    /*
    *   ADD YOUR CODE HERE AS REQUIRED
    */
}

char* CreateDungeon(int width, int height, Point& ref_startPoint, Point& ref_exitPoint)
{
    /*
    *   ADD YOUR CODE HERE AS REQUIRED. DEFINE NEW FUNCTIONS IF IT GETS LONG.
    */
    int size;
    size = width * height;
    
    char *dungeon;

    dungeon = new char [size];

    for (int i = 0; i < size; i++){
        dungeon[i] = ' ';
    }

    return dungeon;
   
}
