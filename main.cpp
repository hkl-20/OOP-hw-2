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

    // Story line initialization
    cout << "Enter the width and size of the dungeon you want to play in: \n";
    cout << "It is recommended if the grid is bigger than 8x8 for a better experience.\n\n";

    int width, height;
    cout << "Width: ";
    cin >>  width;
    cout << "\nHeight: ";
    cin >> height;
    cout << "\n";

    Point startPoint(0,0);
    Point exitPoint(0,0);

    char* dungeon = nullptr;

    // Dungeon creation based on height and width provided
    dungeon = CreateDungeon(width, height, startPoint, exitPoint);

    Traversal(dungeon, startPoint, exitPoint, width, height);

    return 0;
}

void TrapStatements()
{
    /*
    Just assign some statements for health detoriation and call them at a certain probability
    */
    int select = rand() % 3 + 1;
    if (select == 1){
        cout << "An arrow flew out of a nearby wall and hit you in your posterior. That will leave a scar!\n";
    }
    else if (select == 2)
    {
        cout << "You walked into some spikes that sprung out of the floor.\n";
    }
    else{
        cout << "You stepped into a bear trap and got yourself injured.\n";
    }
}

void FoodStatements()
{
    /* 
    Just assign some statements for getting food and call them at a certain probability
    */
    int select = rand() % 3 + 1;
    if (select == 1){
        cout << "You looked at the food and it was a well cooked chicken ... well at least it looked like one.\n";
    }
    else if (select == 2)
    {
        cout << "It is a rat as big as a rabbit. It will go down well with a bit of wasp juice.\n";
    }
    else{
        cout << "It is a bread roll in this dungeon? Maybe there is a secret bakery around here.\n";
    }
}

void HitStatements()
{
    /* 
    Assign some statements for when the user hits and call them at a certain probability
    */
    int select = rand() % 3 + 1;
    if (select == 1){
        cout << "Your roundhouse kick sent your enemy flying right into a gutter.\n";
    }
    else if (select == 2)
    {
        cout << "Your speed is unmatched and delivered a Stone Cold Stunner.\n";
    }
    else{
        cout << "It is a bread roll in this dungeon? Maybe there is a secret bakery around here.\n";
    }
}

void GetHitStatements()
{
    /*
    Assign some statements for when the user gets hit and call them at a certain probability
    */
    int select = rand() % 3 + 1;
    if (select == 1){
        cout << "The enemy avoided your attack and gave you a nasty scratch.\n";
    }
    else if (select == 2)
    {
        cout << "You were not prepared for a sudden lunging attack that hit you hard.\n";
    }
    else{
        cout << "The enemy threw a rock that hit you on the temple and shook you bad.\n";
    }
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
    for(int i = width; i < width*height - width; i += width){
        dungeon[i] = 'W';
    }
    for(int i = width*2 - 1; i < width*height - width; i += width){
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
  
    //cout << person << endl;
  
    if (dungeon[(person * width ) + 1] == ' '){
        dungeon[(person * width ) + 1] = 'P';
    }
    else{
        dungeon[width + 1] = 'P';
    }
    
    //Exit 

    int exit;
    exit = rand() % (height - 2);

    //cout << exit << endl;

    if (dungeon[((exit + 1) * width)  - 2] == ' '){
        dungeon[((exit + 1) * width)  - 2] = 'X';
    }
    else{
        dungeon[width*height - width - 2] = 'X';
    }

    for (int i = 0; i < height*width; i ++){
        cout << dungeon[i] << " "; 
        if ((i + 1) % width == 0){
            cout << endl;
        }
    }

    // Beginning of the game in story mode
    cout << "\nAfter being captured by a raid of some robbers on your caravan,\n";
    cout << "you find yourself alone in a dark dungeon. With nothing but your\n";
    cout << "wits, you choose to take a step...\n";

    cout << "\nIn which direction do you want to move? (U,D,L,R; Press X if you want to give up and die.)\n";

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
    //Combat function for when player arrives at E
    cout << "You come across " << enemies << " enemies. You will have to fight.\n";
    while(enemies != 0 || player.alive == false){
        int playerHit = rand() % 100;
        if (playerHit < 30){
            HitStatements();
            enemies --;
            cout << "You killed one enemy!\n";
        }
        if (enemies != 0){
            for (int x = 0; x < enemies; x++){
                int enemyHit = rand() % 100;
                if (enemyHit < 30){
                    GetHitStatements();
                    player.loseHealth();
                    cout << "You lose 1 health";
                }
            }
        }
    } 
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
