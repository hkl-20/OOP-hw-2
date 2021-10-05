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
    else{ //Need to fix this 
        cout << "You made an excellent jab that knocked the lights out of your enemy.\n";
    }
}

void GetHitStatements()
{
    /*
    Statements for when the user gets hit by enemies and then each of them are called at a certain probability
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
    Player player;
    
    // the next 4 loops are creating the boundary for the dungeon
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
            
            // object placements with a 20% probability
            if ( a <= 20 ){
                b = (rand() % 100);

                // enemy attack placement with a 15% probability
                if ((b >= 0) && (b < 15) ){
                    dungeon[i] = 'E';
                }

                // health boost placement with a 15% probability
                else if((b >= 15) && (b < 30) ){
                    dungeon[i] = 'H';
                }

                // trap placement with a 15% probability
                else if((b >= 30) && (b < 45) ){
                    dungeon[i] = 'T';
                }

                // food placement with a 15% probability
                else if((b >= 45) && (b < 60) ){
                    dungeon[i] = 'F';
                }

                // wall placement with a 40% probability
                else{
                    dungeon[i] = 'W';
                }
            }
        }
    }

    //Person 
    int person;
    int size = width * height;

    person = rand() % (height - 2);

    // placement of a person in the dungeon
    if (dungeon[(person * width ) + 1] == ' '){
        dungeon[(person * width ) + 1] = 'P';
    }
    else{
        dungeon[width + 1] = 'P';
    }
    
    //Exit 
    int exit;
    exit = rand() % (height - 2);

    // position for the escape in dungeon
    if (dungeon[((exit + 1) * width)  - 2] == ' '){
        dungeon[((exit + 1) * width)  - 2] = 'X';
    }
    else{
        dungeon[size - width - 2] = 'X';
    }

    // Visual Dungeon Creation
    /*
    for (int i = 0; i < size; i ++){
        cout << dungeon[i] << " "; 
        if ((i + 1) % width == 0){
            cout << endl;
        }
    }
    */

    // Getting the position of the player
    for(int x = 1; x < size; x++){
        if (dungeon[x] == 'P'){
            player.x = (x % width);
            player.y = (x / width);
        }
    }

    // Beginning of the game in story mode
    cout << "\nAfter being captured by a raid of some robbers on your caravan,\n";
    cout << "you find yourself alone in a dark dungeon. With nothing but your\n";
    cout << "wits, you choose to take a step...\n";

    // when player is in the dungeon, has food and is alive
    while (player.alive == true && player.food != 0)
    {
        char nextDirection;
        int nextX, nextY;
        cout << "\nIn which direction do you want to move? (U,D,L,R; Press X if you want to give up and die.)\n";
        cin >> nextDirection;

        // condition for when player wants to exit
        if (nextDirection == 'x' || nextDirection == 'X'){
            player.alive = false;
        }

        // condition for when player wants to move up
        else if (nextDirection == 'u' || nextDirection == 'U'){
            nextY = player.y - 1;

            // getting the current position of 'P' 
            int currentPlace = ((player.y) * width) + player.x;
            char currentTemp = dungeon[currentPlace];

            // getting the next potential position of 'P'
            int nextPlace = ((nextY) * width) + player.x;
            char nextTemp = dungeon[nextPlace];

            // placing 'P' if the next position is empty
            if (nextTemp == ' '){
                dungeon[currentPlace] = ' ';
                dungeon[nextPlace] = 'P';
                player.y = nextY;
                cout << "There is nothing here\n";
            }

            // condition for when player gets food
            else if (nextTemp == 'F'){
                int bonusFood = rand() % 5 + 4;

                //addition to the current food amount for the player
                player.food += bonusFood;
                dungeon[currentPlace] = ' ';
                dungeon[nextPlace] = 'P';
                player.y = nextY;

                // fun statements to accompany
                FoodStatements();
            }

            // condition for when player encounters a trap
            else if (nextTemp == 'T'){

                //loss of health due to the trap
                player.loseHealth();
                dungeon[currentPlace] = ' ';
                dungeon[nextPlace] = 'P';
                player.y = nextY;

                // fun statements to accompany
                TrapStatements();
            }

            // condition for when a player gets a health boost
            else if (nextTemp == 'H'){

                //player gets a health boost
                player.gainHealth();
                dungeon[currentPlace] = ' ';
                dungeon[nextPlace] = 'P';
                player.y = nextY;
                cout << "Your current health is: " << player.health << endl;
            }

            // condition for when a wall is encountered
            else if (nextTemp == 'W'){
                cout << "There appears to be a wall here\n";
            }

            // condition for when enemies are encountered
            else if (nextTemp == 'E'){
                int enemies = rand() % 3 + 2;
                dungeon[currentPlace] = ' ';
                dungeon[nextPlace] = 'P';
                player.y = nextY;

                // combat function is called to deal with enemies
                Combat(player, enemies);
            }

            // condition for when player exits the dungeon 
            else if (nextTemp == 'X'){
                break;  
            }
            
            // current player update
            player.food --;
            cout << "You have food for " << player.food << " more turns\n";
            cout << "You have " << player.health << " health left\n";
        }

        // condition for when player wants to move right
        else if (nextDirection == 'r' || nextDirection == 'R'){
            nextX = player.x + 1;

            // getting the current position of 'P'
            int currentPlace = ((player.y) * width) + player.x;
            char currentTemp = dungeon[currentPlace];

            // getting the next potential position of 'P'
            int nextPlace = ((player.y) * width) + nextX;
            char nextTemp = dungeon[nextPlace];
            
            // placing 'P' if the next position is empty
            if (nextTemp == ' '){
                dungeon[currentPlace] = ' ';
                dungeon[nextPlace] = 'P';
                player.x = nextX;
                cout << "There is nothing here\n";
            }

            // condition for when player gets food
            else if (nextTemp == 'F'){
                int bonusFood = rand() % 5 + 4;
                
                //addition to the current food amount for the player
                player.food += bonusFood;
                dungeon[currentPlace] = ' ';
                dungeon[nextPlace] = 'P';
                player.x = nextX;
                
                // fun statements to accompany
                FoodStatements();
            }

            // condition for when player encounters a trap
            else if (nextTemp == 'T'){
                
                //loss of health due to the trap
                player.loseHealth();
                dungeon[currentPlace] = ' ';
                dungeon[nextPlace] = 'P';
                player.x = nextX;

                // fun statements to accompany
                TrapStatements();

            }

            // condition for when a player gets a health boost
            else if (nextTemp == 'H'){

                //player gets a health boost
                player.gainHealth();
                dungeon[currentPlace] = ' ';
                dungeon[nextPlace] = 'P';
                player.x = nextX;
                cout << "Your current health is: " << player.health << endl;
            }

            // condition for when a wall is encountered
            else if (nextTemp == 'W'){
                cout << "There appears to be a wall here\n";
            }

            // condition for when enemies are encountered
            else if (nextTemp == 'E'){
                int enemies = rand() % 3 + 2;
                dungeon[currentPlace] = ' ';
                dungeon[nextPlace] = 'P';
                player.x = nextX;

                // combat function is called to deal with enemies
                Combat(player, enemies);
            }

            // condition for when player exits the dungeon
            else if (nextTemp == 'X'){
                break;  
            }

            // current player update
            player.food --;
            cout << "You have food for " << player.food << " more turns\n";
            cout << "You have " << player.health << " health left\n";
        }

        // condition for when player wants to move left
        else if (nextDirection == 'l' || nextDirection == 'L'){
            nextX = player.x - 1;

            // getting the current position of 'P'
            int currentPlace = ((player.y) * width) + player.x;
            char currentTemp = dungeon[currentPlace];

            // getting the next potential position of 'P'
            int nextPlace = ((player.y) * width) + nextX;
            char nextTemp = dungeon[nextPlace];

            // placing 'P' if the next position is empty
            if (nextTemp == ' '){
                dungeon[currentPlace] = ' ';
                dungeon[nextPlace] = 'P';
                player.x = nextX;
                cout << "There is nothing here\n";
            }

            // condition for when player gets food
            else if (nextTemp == 'F'){
                int bonusFood = rand() % 5 + 4;

                //addition to the current food amount for the player
                player.food += bonusFood;
                dungeon[currentPlace] = ' ';
                dungeon[nextPlace] = 'P';
                player.x = nextX;
                
                // fun statements to accompany
                FoodStatements();
            }

            // condition for when player encounters a trap
            else if (nextTemp == 'T'){

                // loss of health due to the trap
                player.loseHealth();
                dungeon[currentPlace] = ' ';
                dungeon[nextPlace] = 'P';
                player.x = nextX;

                // fun statements to accompany
                TrapStatements();

            }
            
            // condition for when a player gets a health boost
            else if (nextTemp == 'H'){

                //player gets a health boost
                player.gainHealth();
                dungeon[currentPlace] = ' ';
                dungeon[nextPlace] = 'P';
                player.x = nextX;
                cout << "Your current health is: " << player.health << endl;
            }

            // condition for when a wall is encountered
            else if (nextTemp == 'W'){
                cout << "There appears to be a wall here\n";
            }
            
            // condition for when enemies are encountered
            else if (nextTemp == 'E'){
                int enemies = rand() % 3 + 2;
                dungeon[currentPlace] = ' ';
                dungeon[nextPlace] = 'P';
                player.x = nextX;

                // combat function is called to deal with enemies
                Combat(player, enemies); 
            }

            // condition for when player exits the dungeon 
            else if (nextTemp == 'X'){
                break;  
            }

            // current player update
            player.food --;
            cout << "You have food for " << player.food << " more turns\n";
            cout << "You have " << player.health << " health left\n";  
        }

        // condition for when player wants to move down
        else if (nextDirection == 'd' || nextDirection == 'D'){
            nextY = player.y + 1;

            // getting the current position of 'P'
            int currentPlace = ((player.y) * width) + player.x;
            char currentTemp = dungeon[currentPlace];

            // getting the next potential position of 'P'
            int nextPlace = ((nextY) * width) + player.x;
            char nextTemp = dungeon[nextPlace];

            // placing 'P' if the next position is empty
            if (nextTemp == ' '){
                dungeon[currentPlace] = ' ';
                dungeon[nextPlace] = 'P';
                player.y = nextY;
                cout << "There is nothing here\n";
            }

            // condition for when player gets food
            else if (nextTemp == 'F'){
                int bonusFood = rand() % 5 + 4;
                
                //addition to the current food amount for the player
                player.food += bonusFood;
                dungeon[currentPlace] = ' ';
                dungeon[nextPlace] = 'P';
                player.y = nextY;
                
                // fun statements to accompany
                FoodStatements();
            }
            
            // condition for when player encounters a trap
            else if (nextTemp == 'T'){

                //loss of health due to the trap
                player.loseHealth();
                dungeon[currentPlace] = ' ';
                dungeon[nextPlace] = 'P';
                player.y = nextY;

                // fun statements to accompany
                TrapStatements();
            }

            // condition for when a player gets a health boost 
            else if (nextTemp == 'H'){

                //player gets a health boost
                player.gainHealth();
                dungeon[currentPlace] = ' ';
                dungeon[nextPlace] = 'P';
                player.y = nextY;
                cout << "Your current health is: " << player.health << endl;
            }

            // condition for when a wall is encountered
            else if (nextTemp == 'W'){
                cout << "There appears to be a wall here\n";
            }
            
            // condition for when enemies are encountered
            else if (nextTemp == 'E'){
                int enemies = rand() % 3 + 2;
                dungeon[currentPlace] = ' ';
                dungeon[nextPlace] = 'P';
                player.y = nextY;

                // combat function is called to deal with enemies
                Combat(player, enemies);
            }

            // condition for when player exits the dungeon
            else if (nextTemp == 'X'){
                break;  
            }

            // current player update
            player.food --;
            cout << "You have food for " << player.food << " more turns\n";
            cout << "You have " << player.health << " health left\n";
        }
    }

    if (player.alive == false){
        cout << "You have died.";
    }
    else if (player.food == 0){
        cout << "You have no more food, you have died";
    }
    else{
        cout << "Congratulations, You have made it out of the dungeon.";
    }

}

void Combat(Player& player, int enemies)
{   cout << enemies << endl;

    //Combat function for when player arrives at E
    cout << "You come across " << enemies << " enemies. You will have to fight.\n";

    while(enemies != 0 && player.alive == true){
        int playerHit = rand() % 100;

        // Condition for player to hit enemy
        if (playerHit < 30){
            HitStatements();
            enemies --;
            cout << "You killed one enemy!\n";
        }

        // Condition for enemies to hit player
        if (enemies != 0){
            for (int x = 0; x < enemies; x++){
                int enemyHit = rand() % 100;
                if (enemyHit < 10){
                    GetHitStatements();
                    player.loseHealth();
                    cout << "You lose 1 health\n";
                }
            }
        }
    } 
}

char* CreateDungeon(int width, int height, Point& ref_startPoint, Point& ref_exitPoint)
{
    /*
    *   Creating a single sized array as a dungeon for the game
    */
    int size;
    size = width * height;
    
    char *dungeon;

    // the dungeon array
    dungeon = new char [size];

    // populating the dungeon
    for (int i = 0; i < size; i++){
        dungeon[i] = ' ';
    }
    return dungeon;
}
