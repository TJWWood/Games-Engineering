#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "LevelSystem.h"
#include "maths.h"
#include "Ghost.h"
#include "System_Renderer.h"

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

EntityManager em;
Player* player = new Player();
Ghost* ghost = new Ghost();
void Reset()
{

}

void Load() 
{
	if (!spriteSheet.loadFromFile("res/sprites/si.png"))
	{
		cerr << "Failed to load spritesheet" << std::endl;
	}
	ls::loadLevelFile("res/levels/maze_2.txt");
	// Print the level to the console
	for (size_t y = 0; y < ls::getHeight(); ++y) {
		for (size_t x = 0; x < ls::getWidth(); ++x) {
			cout << ls::getTile({ x, y });
		}
		cout << endl;
	}
	em.list.push_back(shared_ptr<Entity>(player));
	em.list.push_back(shared_ptr<Entity>(ghost));
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

	for (auto &e : em.list) {
		e->update(dt);
	};
}

void Render(RenderWindow &window)
{

	//ls::render(window);
	for (auto &e : em.list) {
		e->render(window);
	};
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
		Renderer::render();
	}
	return 0;
}