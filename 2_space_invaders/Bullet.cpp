//bullet.cpp
#include "Bullet.h"
#include "Game.h"
using namespace sf;
using namespace std;

void Bullet::_Update(const float & dt)
{
	move(0, dt * 200.0f * (_mode ? 1.0f : -1.0f));
}
Bullet::Bullet(){};

void Bullet::Update(const float & dt)
{
}

void Bullet::Render(sf::RenderWindow &window)
{
	Bullet bullets[256];
	for (Bullet b : bullets)
	{
		window.draw(b);
	}
}

void Bullet::Fire(const sf::Vector2f & pos, const bool mode)
{

}





