#include "Ship.h"
#include "Game.h"
#include "Bullet.h"
using namespace sf;
using namespace std;

Ship::Ship() {};
Ship::Ship(IntRect ir) : Sprite() {
	_sprite = ir;
	setTexture(spriteSheet);
	setTextureRect(_sprite);
};

void Ship::Update(const float &dt) {};

Ship::~Ship() = default;

Invader::Invader() : Ship() {};
bool Invader::direction;
float Invader::speed;
Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
	setOrigin(16, 16);
	setPosition(pos);
}

void Invader::Update(const float &dt) {
	Ship::Update(dt);
	move(dt * (direction ? 1.0f : -1.0f) * speed, 0);
	if (direction && getPosition().x > gameWidth - 16 || !direction && getPosition().x < 16)
	{
		direction = !direction;
		//for (int i = 0; i < ships.size(); ++i)
		//{
		//	ships[i]->move(0, 24);
		//}
	}
}

Player::Player() : Ship(IntRect(160, 32, 32, 32))
{
	setPosition({ gameHeight * 0.5f, gameHeight - 32.0f });
}

void Player::Update(const float &dt) {
	Ship::Update(dt);
	int direction = 0.0f;
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		direction--;
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		direction++;
	}

	move(direction * 400.0f * dt, 0);

	static vector<Bullet*> bullets;
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		bullets.push_back(new Bullet(getPosition(), false));
	}
	//for (const auto s : bullets) {
	//	s.Update(dt);
	//}

}

