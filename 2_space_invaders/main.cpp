#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ship.h"

using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {
	Keyboard::A,   // Player1 UP
	Keyboard::Z,   // Player1 Down
	Keyboard::Up,  // Player2 UP
	Keyboard::Down // Player2 Down
};

const int gameWidth = 800;
const int gameHeight = 600;
sf::Texture spriteSheet;
sf::Sprite invader;

std::vector<Ship *> ships;


void Reset()
{

}

void Load() 
{
	if (!spriteSheet.loadFromFile("res/sprites/si.png"))
	{
		cerr << "Failed to load spritesheet" << std::endl;
	}

	//invader.setTexture(spriteSheet);
	//invader.setTextureRect(sf::IntRect(0, 0, 32, 32));

	//Invader* inv = new Invader(sf::IntRect(0, 0, 32, 32), { 100,100 });
	//ships.push_back(inv);
	Player* player = new Player();
	ships.push_back(player);

	int invaders_rows = 20;
	int invaders_columns = 5;
	for (int r = 0; r < invaders_rows; ++r) {
		auto rect = IntRect(0, 0, 32, 32);
		for (int c = 0; c < invaders_columns; ++c) {
			Vector2f position = sf::Vector2f(r * invaders_rows, c * invaders_columns);
			auto inv = new Invader(rect, position);
			ships.push_back(inv);
		}
	}
}

void Update(RenderWindow &window)
{
	static Clock clock;
	float dt = clock.restart().asSeconds();

	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			window.close();
			return;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		window.close();
	}

	for (auto &s : ships) {
		s->Update(dt);
	};


}

void Render(RenderWindow &window)
{
	for (const auto s : ships)
	{
		window.draw(*s);
	}
}

int main(){
	RenderWindow window(VideoMode(gameWidth, gameHeight), "SPACE INVADERS");
	Load();
	
	while (window.isOpen())
	{
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}