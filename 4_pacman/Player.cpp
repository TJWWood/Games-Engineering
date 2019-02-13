#include "Player.h"
using namespace sf;
using namespace std;

void Player::update(double dt) {
	//Move in four directions based on keys
	int directionX = 0;
	int directionY = 0;
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		directionX--;
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		directionX++;
	}
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		directionY--;
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		directionY++;
	}
	move(sf::Vector2f(directionX * dt * _speed, 0.0f));
	move(sf::Vector2f(0.0f, directionY * dt * _speed));
	Entity::update(dt);
}

Player::Player()
	: _speed(200.0f), Entity(make_unique<CircleShape>(25.f)) {
	_shape->setFillColor(Color::Yellow);
	_shape->setOrigin(Vector2f(25.f, 25.f));
}

void Player::render(sf::RenderWindow &window) const {
	window.draw(*_shape);
}