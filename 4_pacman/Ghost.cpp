#include "Ghost.h"
using namespace sf;
using namespace std;

void Ghost::update(double dt) {
	int directionX = 0;
	int directionY = 0;
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		directionX--;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		directionX++;
	}
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		directionY--;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		directionY++;
	}
	move(sf::Vector2f(directionX * dt * _speed, 0.0f));
	move(sf::Vector2f(0.0f, directionY * dt * _speed));

	Entity::update(dt);
}

Ghost::Ghost()
	: _speed(200.0f), Entity(make_unique<CircleShape>(25.f)) {
	_shape->setFillColor(Color::Blue);
	_shape->setOrigin(Vector2f(25.f, 25.f));
}

void Ghost::render(sf::RenderWindow &window) const {
	window.draw(*_shape);
}