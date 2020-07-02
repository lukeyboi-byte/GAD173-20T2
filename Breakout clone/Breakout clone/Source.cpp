#include "BreakoutMain.h"
#include <conio.h>


int main()
{
	Game myGame;
	if (!myGame.Start())
	{
		//somthing failed
		return EXIT_FAILURE;
	}
	return myGame.Update();
}

Brick brick;
//vector is like a combination of an array and list
std::vector<Brick> Bricks(31, Brick(brick));

bool Game::Start() //Setup our game
{
	//load sound buffers!
	paddleSB.loadFromFile("SFX/paddlebounce.wav");
	wallSB.loadFromFile("SFX/wallbounce.wav");
	brickSB.loadFromFile("SFX/blockbounce.wav");

	font.loadFromFile("arial.ttf");
	scoreText.setFont(font);
	livesText.setFont(font);
	scoreText.setPosition(0, windowHeight - 50);
	livesText.setPosition(windowWidth - 100, windowHeight - 50);
	scoreText.setCharacterSize(24);
	livesText.setCharacterSize(24);
	scoreText.setFillColor(sf::Color::White);
	livesText.setFillColor(sf::Color::White);

	//setup window
	sf::VideoMode vmode(windowWidth, windowHeight);
	window.create(vmode, "Breakout Clone!");
	window.setFramerateLimit(60);

	//setup bricks
	srand(time(NULL));
	for (int i = 0; i < 31; i++)
	{
		Bricks[i].bShape.setSize(sf::Vector2f(100, 50));
		//bottom row
		if (i <= 10)
		{
			Bricks[i].bShape.setFillColor(sf::Color(rand() % 35 + 180, 0, 0, 255));
			Bricks[i].bShape.setPosition(100 * i, 0);
		}
		//top row
		else if (i > 20)
		{
			Bricks[i].bShape.setFillColor(sf::Color(0, rand() % 35 + 180, 0, 255));
			Bricks[i].bShape.setPosition(100 * (i - 21), 100);
		}
		//middle row
		else if (i > 10)
		{
			Bricks[i].bShape.setFillColor(sf::Color(0, 0, rand() % 35 + 180, 255));
			Bricks[i].bShape.setPosition(100 * (i - 11), 50);
		}

	}

	//setup borders
	top.setSize(sf::Vector2f(windowWidth, 1));
	top.setPosition(0, 0);
	top.setFillColor(sf::Color::Black);
	bottom.setSize(sf::Vector2f(windowWidth, 1));
	bottom.setPosition(sf::Vector2f(0, windowHeight - 1));
	bottom.setFillColor(sf::Color::Black);
	left.setSize(sf::Vector2f(1, windowHeight));
	left.setPosition(sf::Vector2f(0, 0));
	left.setFillColor(sf::Color::Black);
	right.setSize(sf::Vector2f(1, windowHeight));
	right.setPosition(sf::Vector2f(windowWidth - 1, 0));
	right.setFillColor(sf::Color::Black);

	return true;
}

int Game::Update()
{
	//setup paddle
	Paddle paddle;
	paddle.pShape.setSize(sf::Vector2f(120.f, 15.f));
	paddle.pShape.setFillColor(sf::Color::Blue);
	paddle.pShape.setPosition(windowHeight - (windowHeight / 5), windowWidth / 2);
	//setup ball
	Ball ball;
	ball.ballShape.setRadius(ball.ballRadius);
	ball.ballShape.setPosition(paddle.pShape.getPosition().x, paddle.pShape.getPosition().y - 75);
	ball.ballShape.setFillColor(sf::Color::Magenta);
	ball.ballVelocity.x = rand() % 10;
	ball.ballVelocity.y = -5;

	//Code to run whilst window is open
	while (window.isOpen())
	{
		//Using mouse to control paddle position!
		if (sf::Mouse::getPosition(window).x > paddle.pShape.getSize().x / 2 && sf::Mouse::getPosition(window).x < window.getSize().x - paddle.pShape.getSize().x / 2)
		{
			paddle.pShape.setPosition(sf::Mouse::getPosition(window).x - paddle.pShape.getSize().x / 2, paddle.pShape.getPosition().y);
		}

		//move ball
		ball.ballShape.move(ball.ballVelocity);

		if (top.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
		{
			ball.Bounce(0, top, ball.ballShape);
			sound.setBuffer(wallSB);
			sound.play();
		}

		if (bottom.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
		{
			ball.Bounce(0, bottom, ball.ballShape);
			lives -= 1;
			if (lives == 0)
			{
				//Game over
				return 1;
			}
		}

		if (left.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()) || right.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
		{
			ball.Bounce(1, left, ball.ballShape);
			sound.setBuffer(wallSB);
			sound.play();
		}

		if (paddle.pShape.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
		{
			ball.Bounce(0, paddle.pShape, ball.ballShape);
			sound.setBuffer(paddleSB);
			sound.play();
		}
		//colission with bricks
		for (int i = 0; i < Bricks.size(); i++)
		{
			if(Bricks[i].bShape.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
			{
				ball.Bounce(0, Bricks[i].bShape, ball.ballShape);
				Bricks[i].bShape.setPosition(1200, 0);
				score += 1;
				ball.ballVelocity = ball.ballVelocity * 1.03f;
				if (score == 30)
				{
					return 1;
				}
				sound.setBuffer(brickSB);
				sound.play();
			}
		}

		//Pollevent is our window updating event
		sf::Event event;
		while (window.pollEvent(event))
		{
			//if window closes
			if (event.type == sf::Event::Closed)
				window.close();
		}

		scoreText.setString("Score: " + std::to_string(score));
		livesText.setString("Lives: " + std::to_string(lives));
		//Clear our window, and redraw everything
		window.clear();
		for (int i = 0; i < Bricks.size(); i++)
		{
			window.draw(Bricks[i].bShape);
		}
		window.draw(scoreText);
		window.draw(livesText);
		window.draw(paddle.pShape);
		window.draw(ball.ballShape);
		window.display();
		
	}

	return 0;
}