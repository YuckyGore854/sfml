#include<iostream>
#include "SFML/Graphics.hpp"
using namespace std;
enum DIRECTIONS { LEFT, RIGHT, UP, DOWN }; //left is 0, right is 1, up is 2, down is 3
int main() {
    //game set up (you'll need these lines in every game)
    sf::RenderWindow screen(sf::VideoMode(840, 1200), "breakout"); //set up screen
    sf::Event event; //set up event queue
    sf::Clock clock; //set up the clock (needed for game timing)
    const float FPS = 60.0f; //FPS
    screen.setFramerateLimit(FPS); //set FPS
   
    //load in images
    sf::Texture brick;
    brick.loadFromFile("brick3036.png");
    sf::Sprite wall;
    wall.setTexture(brick);
    const int arrayY = 30;
    const int arrayX = 60;
    //player setup
    int xpos = 200;
    int ypos = 180;
    int vx = 0;
    int vy = 0;
    int radius = 10;

    sf::Sprite playerSprite;
    sf::Texture pacMan;
    pacMan.loadFromFile("pacman.png");
    playerSprite.setTexture(pacMan, true);
    playerSprite.setPosition(xpos, ypos);
    int playerTicker = 0;
    int playerRow = 0;
    int playerColumn = 0;
    sf::IntRect playerSubrect;
    playerSubrect.width = 20;
    playerSubrect.height = 20;
    

    sf::CircleShape player(radius);
    player.setFillColor(sf::Color(250, 250, 0)); //using RGB value for color here (hex also works)
    player.setPosition(xpos, ypos); //top left "corner" of circle (not center!)
    bool keys[] = { false, false, false, false };

    sf::CircleShape dot(5);
    dot.setFillColor(sf::Color::Color(255, 255, 255, 255));

    int map2[31][28] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 1, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 1,
        1,-1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 1,-1, 1, 1,-1, 1, 1, 1, 1, 1,-1, 1, 1, 1, 1,-1, 1,
        1,-1, 1, 0, 0, 1,-1, 1, 0, 0, 0, 1,-1, 1, 1,-1, 1, 0, 0, 0, 1,-1, 1,-1,-1, 1,-1, 1,
        1,-1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 1,-1, 1, 1,-1, 1, 1, 1, 1, 1,-1, 1, 1, 1, 1,-1, 1,
        1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 1,
        1,-1, 1, 1, 1, 1,-1, 1, 1,-1, 1, 1, 1, 1, 1, 1, 1, 1,-1, 1, 1,-1, 1, 1, 1, 1,-1, 1,
        1,-1, 1, 1, 1, 1,-1, 1, 1,-1, 1, 1, 1, 1, 1, 1, 1, 1,-1, 1, 1,-1, 1, 1, 1, 1,-1, 1,
        1,-1,-1,-1,-1,-1,-1, 1, 1,-1,-1,-1,-1, 1, 1,-1,-1,-1,-1, 1, 1,-1,-1,-1,-1,-1,-1, 1,
        1, 1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 1,-1, 1, 1,-1, 1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 1,-1, 1, 1, 1, 1, 1,-1, 1, 1,-1, 1, 1, 1, 1, 1,-1, 1,-1,-1,-1,-1,-1,
        0, 0, 0, 0, 0, 1,-1, 1, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 1, 1,-1, 1,-1,-1,-1,-1,-1,
        0, 0, 0, 0, 0, 1,-1, 1, 1,-1, 1, 1, 2, 2, 2, 2, 1, 1,-1, 1, 1,-1, 1,-1,-1,-1,-1,-1,
        1, 1, 1, 1, 1, 1,-1, 1, 1,-1, 1,-1,-1,-1,-1,-1,-1, 1,-1, 1, 1,-1, 1, 1, 1, 1, 1, 1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        1, 1, 1, 1, 1, 1,-1, 1, 1,-1, 1,-1,-1,-1,-1,-1,-1, 1,-1, 1, 1,-1, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 1,-1, 1, 1,-1, 1, 1, 1, 1, 1, 1, 1, 1,-1, 1, 1,-1, 1,-1,-1,-1,-1,-1,
        0, 0, 0, 0, 0, 1,-1, 1, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 1, 1,-1, 1,-1,-1,-1,-1,-1,
        0, 0, 0, 0, 0, 1,-1, 1, 1,-1, 1, 1, 1, 1, 1, 1, 1, 1,-1, 1, 1,-1, 1,-1,-1,-1,-1,-1,
        1, 1, 1, 1, 1, 1,-1, 1, 1,-1, 1, 1, 1, 1, 1, 1, 1, 1,-1, 1, 1,-1, 1, 1, 1, 1, 1, 1,
        1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 1, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 1,
        1,-1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 1,-1, 1, 1,-1, 1, 1, 1, 1, 1,-1, 1, 1, 1, 1,-1, 1,
        1,-1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 1,-1, 1, 1,-1, 1, 1, 1, 1, 1,-1, 1, 1, 1, 1,-1, 1,
        1,-1,-1,-1, 1, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 1, 1,-1,-1,-1, 1,
        1, 1, 1,-1, 1, 1,-1, 1, 1,-1, 1, 1, 1, 1, 1, 1, 1, 1,-1, 1, 1,-1, 1, 1,-1, 1, 1, 1,
        1, 1, 1,-1, 1, 1,-1, 1, 1,-1, 1, 1, 1, 1, 1, 1, 1, 1,-1, 1, 1,-1, 1, 1,-1, 1, 1, 1,
        1,-1,-1,-1,-1,-1,-1, 1, 1,-1,-1,-1,-1, 1, 1,-1,-1,-1,-1, 1, 1,-1,-1,-1,-1,-1,-1, 1,
        1,-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,-1, 1, 1,-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,-1, 1,
        1,-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,-1, 1, 1,-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,-1, 1,
        1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    
    };
//################### HOLD ONTO YOUR BUTTS, ITS THE GAME LOOP###############################################################
    while (screen.isOpen()) {//keep window open until user shuts it down

        while (screen.pollEvent(event)) { //look for events-----------------------

            //this checks if the user has clicked the little "x" button in the top right corner
            if (event.type == sf::Event::EventType::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                screen.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                keys[LEFT] = true;
            }
            else keys[LEFT] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                keys[RIGHT] = true;
            }
            else keys[RIGHT] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                keys[UP] = true;
            }
            else keys[UP] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                keys[DOWN] = true;
            }
            else keys[DOWN] = false;

        }//end event loop---------------------------------------------------------------

        //move Mr. Pac
        if (keys[LEFT]) {
            vx = -2;
            playerRow = 1;
        }

        else if (keys[RIGHT] == true) {
            vx = 2;
            playerRow = 0;
        }

        if (keys[UP]) {
            vy = -2;
            playerRow = 2;
        }

        else if (keys[DOWN]) {
            vy = 2;
            playerRow = 3;
        }
        playerSubrect.top = playerRow * 20;
        //right collision
        if (vx > 0 && 
            //top right corner
            ((map2[(ypos) / 36][(xpos + (radius*2 + 3)) / 30] == 1) ||
            //bottom right corner
            (map2[(ypos + radius*2 + 2) / 36 ]
                [(xpos + radius * 2 + 3) / 30] == 1))) {
            vx = 0;
        }
        //left collision
        
        if (vx < 0 &&
            //top left
            ((map2[ypos / 36][(xpos - 3) / 30] == 1) ||
                //bottom left
                (map2[(ypos + radius * 2 + 3) / 36][(xpos - 3) / 30] == 1))) {
            vx = 0;
        }
        
        //up collision
        if (vy < 0 && 
            //top left
            ((map2[(ypos - 5) / 36][(xpos) / 30] == 1) ||
            //top right
            (map2[(ypos - 5) / 36][(xpos + radius * 2) / 30] == 1))) {
            vy = 0;
        }
         
        //down collision
        if (vy > 0 && (
            (map2[(ypos + (radius*2+5)) / 36][(xpos) / 30] == 1)||
            (map2[(ypos+radius*2+5)/36][(xpos+radius*2)/30] == 1))){
        
            vy = 0;
        }
    
        if (map2[(ypos + radius) / 36][(xpos + radius) / 30] == -1 || map2[(ypos + radius * 2) / 36][(xpos + radius * 2) / 30] == -1); {
            map2[(ypos) / 36][(xpos) / 30] = 0;
        }
        
        xpos += vx;
        ypos += vy;
        player.setPosition(xpos, ypos);
        playerSprite.setPosition(xpos, ypos);
             //render section-----------------------------------------
        screen.clear(); //wipes screen, without this things smear
        for (int rows = 0; rows < 31; rows++) {
            for (int cols = 0; cols < 28; cols++) {
                if (map2[rows][cols] == 1) {
                    wall.setPosition(cols * 30, rows * 36);
                    screen.draw(wall);
                }
                if (map2[rows][cols] == -1) {
                    dot.setPosition(cols * 30 +10, rows * 36 + 10);
                    screen.draw(dot);
                }
            }
        }
        playerTicker++;
        if (playerTicker == 5) {
            std::cout << playerTicker << std::endl;
            playerColumn++;
            if (playerColumn > 2) {
                playerColumn = 0;
            }
            playerSubrect.left = playerColumn * 20;
            playerSprite.setTextureRect(playerSubrect);
            playerTicker = 0;
        }
        
        //screen.draw(player); //draw player
        screen.draw(playerSprite);
        screen.display(); //flips memory drawings onto screen
    

    }//######################## end game loop ###################################################################################

    cout << "goodbye!" << endl;
} //end of main