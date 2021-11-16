//piggy simulator!
//a quick introduction/review of C++ classes!
/*
#include<iostream>
#include<SFML/Graphics.hpp>
using namespace std;
//standalone function declarations/prototypes would go here too!

//class definition-------------------------------------------

class piggy {
private: //private variables can only be seen/used by members of the class
	int xpos;
	int ypos;
	bool isWalking;
	bool isAsleep;
	bool isoinkin;
	int number;
	sf::Texture texture;
	sf::Sprite sprite;
public: //can be seen and used by everything in your program
	piggy(); //default constructor: initalizes all the variables in your pig
	piggy(int num); //parameterized constructor
	void walk();
	void sleep();
	void draw();
	void oink();
};

//---------------------------------------------------------
sf::RenderWindow window(sf::VideoMode(1280, 720), "Idk");
int main() {

	sf::Event e;

	piggy p1; //instantiate a pig object
	while (window.isOpen()) { //game loop!
		//PIG
		p1.walk();
		p1.sleep();
		p1.draw();
		p1.oink();

		window.display();
	}
}


//class function definitions AND standalone function definitions go here



//===================================================================================================================================================
piggy::piggy() {
	xpos = rand() % 700 + 100;
	ypos = rand() % 700 + 100;
	isAsleep = false;
	isWalking = false;
	isoinkin = false;
	if (!texture.loadFromFile("oink.jpg")) {
		cout << "Couldn't load pig" << endl;
	}
	sprite.setTexture(texture);
		

	
}//i fluip

piggy::piggy(int num) {
	xpos = rand() % 700 + 100;
	ypos = rand() % 700 + 100;
	isAsleep = false;
	isWalking = false;
	isoinkin = false;
	number = num;
}
void piggy::walk() {
	//randomly move in one of 8 directions when isWalking is true
	if (!isAsleep) {
		if (isWalking == true) {
			xpos += rand() % 10 - 5;
			ypos += rand() % 10 - 5;
			int off = rand() % 100 + 1;

			if (off < 30) { //30% chance walking will turn off each turn
				isWalking = false;
			}
		}
	}
	//10% chance any turn that isWalking will turn ON
	int num = rand() % 100 + 1;
	if (num < 10) {
		isAsleep = false;
		isWalking = true;
		cout << "walking!" << endl;
		system("pause");

	}
}
void piggy::sleep() {
	//you do this one!

	int numb = rand() % 100 + 1;
	if (numb < 25) {
		isAsleep = true;
	}
	if (isAsleep) {
		cout << "Snooore snooore oink snooore" << endl;
	}
}


void piggy::draw() {
	//eventually this will hold drawing functions to make it graphical
	cout << "Hello I am pig # " << number << endl;
	cout << "My position is " << xpos << " , " << ypos << endl;
	cout << "I am ";
	if (isAsleep) cout << " asleep." << endl;
	else cout << " not asleep." << endl;
	window.draw(sprite);
}

void piggy::oink() {
	int numbe = rand() % 100 + 1;
	if (numbe < 10) {
		isoinkin = true;
	}
	if (isoinkin) {
		cout << " oink" << endl;
	}
}
*/