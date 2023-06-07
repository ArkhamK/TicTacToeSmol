//Necessities Inclusion
#include <SFML/Graphics.hpp>;
#include <iostream>; 
#include "Button.h"

using namespace sf;

//Variables
Sprite grid, squares[9];
Texture grid_t, blank_t, circle_t, cross_t, resetb_t;
Button* resetb;
Event event;
Font font;
Text playerindicator;
bool boardfull = 0, gameover = 0;
int currentplayer = 1, occupied[9] = { 0 };

//Functions
void EventHandler(RenderWindow *window);
void playermove(Vector2f mousePos, Vector2u windowPos);
void ResetBoard();
bool checkwin(int box);
bool checkdraw();


int main() {

	//Assets Loading 
	grid_t.loadFromFile("Assets/Grid.png");
	blank_t.loadFromFile("Assets/Blank.png");
	circle_t.loadFromFile("Assets/Circle.png");
	cross_t.loadFromFile("Assets/Cross.png");
	resetb_t.loadFromFile("Assets/Reset.png");
	font.loadFromFile("Assets/Minecraft.ttf");

	//Texture Mapping 
	grid.setTexture(grid_t);
	for (int i = 0; i < 9; i++)
	{
		squares[i].setTexture(blank_t);
	}

	//Window Initialization 
	RenderWindow window(VideoMode(600,600), "Tic Tac Toe by 20-CS-19", Style::Close);
	window.setFramerateLimit(60);
	

	//Board Formatting
	grid.setOrigin(50.0f, 50.0f);
	grid.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	grid.setScale(400.0f/grid.getGlobalBounds().width, 400.0f/grid.getGlobalBounds().height);
	for (int i = 0; i < 9; i++)
	{
		squares[i].setScale(120.0f / squares[i].getGlobalBounds().width,
							120.0f / squares[i].getGlobalBounds().height);
	}
	


	//Player Indicator
	playerindicator = Text("Player 1's Turn", font, 60u);
	playerindicator.setOrigin(playerindicator.getGlobalBounds().width / 2,
					       	  playerindicator.getGlobalBounds().height / 2);
	playerindicator.setPosition((float)window.getSize().x / 2, 30.0f);
	playerindicator.setFillColor(Color(Uint8(181), Uint8(0), Uint8(0)));

	//Blank spacing 
	float xoffset = grid.getGlobalBounds().width / 2;
	float yoffset = grid.getGlobalBounds().height / 2;
	float xorigin = (float)(window.getSize().x / 2 - xoffset + 4);
	float yorigin = (float)(window.getSize().y / 2 - yoffset + 4);


	squares[0].setPosition(xorigin + 136.0f * 0, yorigin + 136.0f * 0);
	squares[1].setPosition(xorigin + 136.0f * 1, yorigin + 136.0f * 0);
	squares[2].setPosition(xorigin + 136.0f * 2, yorigin + 136.0f * 0);

	squares[3].setPosition(xorigin + 136.0f * 0, yorigin + 136.0f * 1);
	squares[4].setPosition(xorigin + 136.0f * 1, yorigin + 136.0f * 1);
	squares[5].setPosition(xorigin + 136.0f * 2, yorigin + 136.0f * 1);

	squares[6].setPosition(xorigin + 136.0f * 0, yorigin + 136.0f * 2);
	squares[7].setPosition(xorigin + 136.0f * 1, yorigin + 136.0f * 2);
	squares[8].setPosition(xorigin + 136.0f * 2, yorigin + 136.0f * 2);

	//Button Initialization 
	resetb = new Button(&resetb_t);
	resetb->setScale(120.0f, 60.0f);
	resetb->setPosition(Vector2f(window.getSize().x / 2, 550.0f), true);
	

	//Main Loop
	while (window.isOpen()) {

		//Button updates
		resetb->update(Mouse::getPosition(window));

		EventHandler(&window);

		window.clear();
		window.draw(grid);

		for (int i = 0; i < 9; i++)
		{
			window.draw(squares[i]);
		}

		window.draw(playerindicator);

		resetb->render(window);

		window.display();
	}
	return 0;
}

//Function Initialization
void EventHandler(RenderWindow *window) {
	while (window -> pollEvent(event)) {

		//Event Manager
		switch (event.type){
		case Event::Closed:
			window->close();
			break;

		case Event::MouseButtonPressed:
			if (event.mouseButton.button==Mouse::Left)
			{
				playermove(window->mapPixelToCoords(Mouse::getPosition(*window)), window->getSize());

				if (resetb->isPressed())
				{
					ResetBoard();
				}
			}
			break;
		}
	}
}

//Clicking and Positioning 
void playermove(Vector2f mousePos, Vector2u windowPos) {
	if (!gameover){

		if (!boardfull)
		{
			for (int i = 0; i < 9; i++)
			{
				if (squares[i].getGlobalBounds().contains(mousePos))
				{
					if (!occupied[i])
					{
						squares[i].setTexture(currentplayer == 1 ? cross_t : circle_t);
						occupied[i] = currentplayer;
						playerindicator.setString(currentplayer == 1 ? "Player 2's Turn" : "Player 1's Turn");
						playerindicator.setOrigin(playerindicator.getGlobalBounds().width / 2,
							playerindicator.getGlobalBounds().height / 2);

						if (checkwin(i))
						{

							gameover = true;
							playerindicator.setString(currentplayer == 1 ? "Player 1 Wins" : "Player 2 Wins");
							playerindicator.setOrigin(playerindicator.getGlobalBounds().width / 2,
												   	  playerindicator.getGlobalBounds().height / 2);
							playerindicator.setPosition((float)windowPos.x / 2, 30.0f);

						}
						else if (checkdraw())
						{

							gameover = true;
							std::cout << "Draw";
							playerindicator.setString("Draw");
							playerindicator.setOrigin(playerindicator.getGlobalBounds().width / 2,
													  playerindicator.getGlobalBounds().height / 2);
							playerindicator.setPosition((float)windowPos.x / 2, 30.0f);

							}
						else {
							currentplayer = currentplayer == 1 ? 2 : 1;
						}
					}
					break;
				}
			}
		}
	}
}
//Reset Clear
void ResetBoard() {
	
	gameover = false;
	currentplayer = currentplayer == 1 ? 2 : 1;
	playerindicator.setString(currentplayer == 1 ? "Player 1's Turn" : "Player 2's Turn");
	playerindicator.setOrigin(playerindicator.getGlobalBounds().width / 2,
		playerindicator.getGlobalBounds().height / 2);

	for (int i = 0; i < 9; i++)
	{
		squares[i].setTexture(blank_t);
		occupied[i] = 0;
	}
}

//Win or Draw
bool checkwin(int box) {
	int row = (box / 3) * 3;
	int column = box % 3;

	if (occupied[row] == currentplayer && occupied[row + 1] == currentplayer && occupied[row + 2] == currentplayer)
	{
		return true;
	}

	if (occupied[column] == currentplayer && occupied[column + 3] == currentplayer && occupied[column + 6] == currentplayer)
	{
		return true;
	}

	if (occupied[0] == currentplayer && occupied[4] == currentplayer && occupied[8] == currentplayer)
	{
		return true;
	}

	if (occupied[2] == currentplayer && occupied[4] == currentplayer && occupied[6] == currentplayer)
	{
		return true;
	}
	return false;
}

bool checkdraw() {
	for (int i = 0; i < 9; i++)
	{
		if (occupied[i] == 0) return false;
	}
	return true;
}