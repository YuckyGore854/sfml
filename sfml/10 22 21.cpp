// Space Simulator in C++, using SFML
//Written by Dr. Mo, 2017. Updated 2021.
//note: like all simulations, this is an approximation of reality
//there are many inaccuricies in this simulation (see Kepler's laws for details)
/*
#include<iostream>
using namespace std;
#include "SFML/Graphics.hpp"

int main() {

    //game set up 
    const int SCREEN_WIDTH = 1200;
    const int SCREEN_HEIGHT = 700;
    sf::RenderWindow renderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Solar System Sim"); //create screen
    sf::Event event; //set up event queue
    int t = 0; //in-game timer
    sf::Clock clock; //set up the clock (needed for game timing)
    const float FPS = 60.0f; //FPS
    renderWindow.setFramerateLimit(FPS); //set FPS

    //load images
    sf::Texture img1;
    if (!img1.loadFromFile("space.jpg")) return 0;
    sf::Sprite background;
    background.setTexture(img1);
    std::cout << background.getScale().x << " " << background.getScale().y << std::endl;
    background.setScale(sf::Vector2f(4, 4.3));

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //LOOK HERE! Each planet needs an x,y position. Add two variables for each planet you want- one for its x position, another for y
    double earth_x = 0; //we'll reset these later
    double earth_y = 0;
    double mars_x = 0;
    double mars_y = 0;
    int sun_x = SCREEN_WIDTH / 2; //put sun in center
    int sun_y = SCREEN_HEIGHT / 2;
    //TODO: declare variables for Mars position


    //earth SFML graphics setup
    sf::CircleShape earth(8);
    earth.setFillColor(sf::Color(0, 0, 255)); //using RGB value for color here (hex also works)
    earth.setPosition(10, 20); //top left "corner" of circle (not center!)


    //sun SFML graphics setup
    sf::CircleShape sun(15);
    sun.setFillColor(sf::Color(255, 255, 0)); //using RGB value for color here (hex also works)
    sun.setPosition(sun_x, sun_y); //set to center of screen

    //mars SFML graphics setup
    sf::CircleShape mars(5);
    mars.setFillColor(sf::Color(0xb7, 0x41, 0x0e));
    mars.setPosition(30, 20);

    //month timer
    double year = 2016;
    string months[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October","November", "December" };
    int month = 5;



    ////////ASTRONOMY VARIABLES////////////////////////////////////////////////////////////////////////////////
    //variables for planets' orbits! You can find this information here:
    //https://nssdc.gsfc.nasa.gov/planetary/factsheet/

    //semi-major axis: the long way across
    double Earth_Semimajor_Axis = 149.6;
    double Mars_Semimajor_Axis = 227.9;
    //TODO: add Mars Semimajor axis here

    //eccentricity: how squished your ellipse is
    double Earth_Eccentricity = 0.017;
    //TODO: add Mars eccentricity here
    double Mars_Eccentricity = 0.094;

    //semiMinor axis is the shorter one
    //formula found here: https://en.wikipedia.org/wiki/Semi-major_and_semi-minor_axes
    double Earth_Semiminor_Axis = Earth_Semimajor_Axis * (sqrt((1 - Earth_Eccentricity) * (1 - Earth_Eccentricity)));
    //TODO:add Mars' semi-minor axis
    double Mars_Semiminor_Axis = Mars_Semimajor_Axis * (sqrt((1 - Mars_Eccentricity) * (1 - Mars_Eccentricity)));
    //period ratios: 
    double Period_Ratio_Earth = 1;
    double Period_Ratio_Mars = .5317; //found by dividing orbital period of Earth by orbital period of Mars
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////




    //################### HOLD ONTO YOUR BUTTS, ITS THE GAME LOOP###############################################################
    while (renderWindow.isOpen()) {//keep window open until user shuts it down

        while (renderWindow.pollEvent(event)) { //look for events-----------------------

            //this checks if the user has clicked the little "x" button in the top right corner
            if (event.type == sf::Event::EventType::Closed)
                renderWindow.close();

        }//end event loop---------------------------------------------------------------
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            renderWindow.clear();
        }
       

        //******************************physics engine!********************************************************

        //parametric equations for Earth's elliptical orbit
        //modified from: http://ceadserv1.nku.edu/longa/ClimateChange/vignettes/BigPicture/EarthOrbit.pdf
        t++; //tick the parameter
        earth_x = Earth_Semimajor_Axis * cos((t * 3.14 * Period_Ratio_Earth) / 180 - Earth_Eccentricity) + sun_x;
        earth_y = Earth_Semiminor_Axis * sin((t * 3.14 * Period_Ratio_Earth) / 180) + sun_y;
        earth.setPosition(earth_x, earth_y);
        mars_x = Mars_Semimajor_Axis * cos((t * 3.14 * Period_Ratio_Mars) / 180 - Mars_Eccentricity) + sun_x;
        mars_y = Mars_Semiminor_Axis * cos((t * 3.14 * Period_Ratio_Mars) / 180 + sun_y) + sun_y;
        mars.setPosition(mars_x,mars_y);

        //TODO: parametric equations for Mars orbit go here



        //time calculation
        //2pi = 365 days
        //cout << "days: " << t << endl;
        //update and roughtly print out date to console (this gets more distorted the longer you go)
        if (t % 30 == 0) {
            cout << months[month] << ", " << year << endl;
            month++;
        }
        if (month == 11) {
            month = 0;
            year++;
        }


        //optional distance calulation 
        //xdiff = (Earth_Semimajor_Axis*(cos((t*3.14*Period_Ratio_Earth) / 180 - Earth_Eccentricity)) + SCREEN_WIDTH / 2) - (Mars_Semimajor_Axis*(cos((t*3.14*.5317) / 180 - Mars_Eccentricity)) + SCREEN_WIDTH / 2);
        //ydiff = (Earth_Semimajor_Axis*(sqrt((1 - Earth_Eccentricity)*(1 - Earth_Eccentricity))*sin((t*3.14) / 180)) + SCREEN_HEIGHT / 2) - (Mars_Semimajor_Axis*(sqrt((1 - Mars_Eccentricity)*(1 - Mars_Eccentricity))*sin((t*3.14*Period_Ratio_Mars) / 180)) + SCREEN_HEIGHT / 2);
        //dist = sqrt(ydiff*ydiff + xdiff*xdiff);
        //cout << "distance between planets: " << dist << endl;

        //render section-----------------------------------------
        
        //renderWindow.draw(background); //loads background image: make sure this goes first or it will cover other stuff!
        renderWindow.draw(earth);
        renderWindow.draw(mars);
        renderWindow.draw(sun);
        //TODO: draw other planets
        renderWindow.display(); //flips memory drawings onto screen

    }//######################## end game loop ###################################################################################

    cout << "goodbye!" << endl;
} //end game
*/