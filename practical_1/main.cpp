#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {
	Keyboard::A,   // Player1 UP
	Keyboard::Z,   // Player1 Down
	Keyboard::Up,  // Player2 UP
	Keyboard::Down // Player2 Down
};
const Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;

CircleShape ball;
RectangleShape paddles[2];
int score[2];

Vector2f ballVelocity;
bool server = false;
Font font;
Text text;


void Reset()
{
	paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
	paddles[1].setPosition(gameWidth - 30 + paddleSize.x / 2, gameHeight / 2);
	// reset Ball Position
	ball.setPosition(gameWidth / 2, gameHeight / 2);

	ballVelocity = { (server ? 100.0f : -100.0f), 60.0f };
	text.setString(score[0] + " : " + score[1]);
	text.setPosition((gameWidth * 0.5f) - (text.getLocalBounds().width * 0.5f), 0);
}

void Load() {
	// Set size and origin of paddles
	for (auto &p : paddles) {
		p.setSize(paddleSize - Vector2f(3, 3));
		p.setOrigin(paddleSize / 2.f);
	}
	// Set size and origin of ball
	ball.setRadius(ballRadius - 3);
	ball.setOrigin(ballRadius / 2, ballRadius / 2);
	// reset paddle position
	Reset();

	ballVelocity = { (server ? 100.0f : -100.0f), 60.0f };
	font.loadFromFile("res/fonts/RobotoMono-Bold.ttf");
	text.setString("Score here");
	text.setFont(font);
	text.setCharacterSize(24);
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

	float direction = 0.0f;

	if (Keyboard::isKeyPressed(controls[0]))
	{
		direction--;
	}
	if (Keyboard::isKeyPressed(controls[1]))
	{
		direction++;
	}
	
	paddles[0].move(0, direction * paddleSpeed * dt);
	direction = 0.0f;
	if (Keyboard::isKeyPressed(controls[2]))
	{
		direction--;
	}
	if (Keyboard::isKeyPressed(controls[3]))
	{
		direction++;
	}
	paddles[1].move(0, direction * paddleSpeed * dt);

	
	ball.move(ballVelocity * dt);

	const float bx = ball.getPosition().x;
	const float by = ball.getPosition().y;

	if (by > gameHeight)
	{
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, -10);
	}
	else if (by < 0)
	{
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, 10);
	}
	//right wall
	else if (bx > gameWidth)
	{
		score[1]++;
		Reset();
	}
	//left wall
	else if (bx < 0)
	{
		score[0]++;
		Reset();
	}
	//not behind it && below top edge && above bottom edge - LEFT
	else if (bx < paddleSize.x && by > paddles[0].getPosition().y - (paddleSize.y * 0.5) && by < paddles[0].getPosition().y + (paddleSize.y * 0.5))
	{
		ballVelocity.x *= -1.1f;
		ballVelocity.y *= 1.1f;
		ball.move(0, 10);
	}
	//TODO RIGHT


	//TODO Paddles stay in play area
}

void Render(RenderWindow &window)
{
	window.draw(paddles[0]);
	window.draw(paddles[1]);
	window.draw(ball);
	window.draw(text);
}

int main(){
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG!");
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