//bullet.cpp
#include "Bullet.h"
#include "Game.h"
using namespace sf;
using namespace std;

void Bullet::_Update(const float & dt)
{
	if (getPosition().y < -32 || getPosition().y > gameHeight + 32) {
		//off screen - do nothing
		return;
	}
	else {
		move(0, dt * 200.0f * (_mode ? 1.0f : -1.0f));
		const FloatRect boundingBox = getGlobalBounds();

		for (auto s : ships) {
			if (!_mode && s == player) {
				//player bulelts don't collide with player
				continue;
			}
			if (_mode && s != player) {
				//invader bullets don't collide with other invaders
				continue;
			}
			if (!s->is_exploded() &&
				s->getGlobalBounds().intersects(boundingBox)) {
				//Explode the ship
				s->Explode();
				//warp bullet off-screen
				setPosition(-100, -100);
				return;
			}
		}
	}
}
Bullet::Bullet(){};

void Bullet::Update(const float &dt)
{
	Bullet::_Update(&dt);
}

void Bullet::Render(sf::RenderWindow &window)
{
	Bullet bullets[256];
	for (Bullet b : bullets)
	{
		window.draw(b);
	}
}

void Bullet::Fire(const sf::Vector2f &pos, const bool mode)
{
}

void Ship::Explode() {
	setTextureRect(IntRect(128, 32, 32, 32));
	_exploded = true;
}



