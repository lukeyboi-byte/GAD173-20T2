#include <SFML/Graphics.hpp>
#include <conio.h>
#include <iostream>

int windowX = 1000; //Initial window width
int windowY = 600; //Initial window hieght
int speed = 10; //How fast we move



int main()
{
	//Shape stuff
	sf::Vector2f rectSize = sf::Vector2f(100.f, 50.f); //Size of our rectangle in pixels
	sf::Vector2f rectPos = sf::Vector2f((windowX / 2) - (rectSize.x / 2), (windowY / 2) - (rectSize.y / 2)); //centre
	sf::Color rectColour = sf::Color(255, 255, 0, 255); //0-255 for all 4 r,g,b,a

	//Window stuff
	sf::RenderWindow window(sf::VideoMode(windowX, windowY), "Breakout Clone");
	window.setFramerateLimit(60); //Stop the game going at lightspeed

	sf::RectangleShape paddle(rectSize); //our paddle object
	paddle.setFillColor(rectColour); //Sety colour
	paddle.setPosition(rectPos); //Set position

	//Ball stuff
	sf::CircleShape ball(10.f); // Create ball
	ball.setFillColor(sf::Color::Magenta);
	sf::Vector2f velocity = sf::Vector2f(0.f, 0.f); //setup velocity
	velocity.x = rand() % 10; //initial x will be random
	velocity.y = -5;
	//move starting position of the ball up by the height of the paddle
	ball.setPosition(sf::Vector2f(rectPos.x, rectPos.y - rectSize.y));

	//borders stuff
	sf::RectangleShape top;
	sf::RectangleShape bottom;
	sf::RectangleShape left;
	sf::RectangleShape right;
	top.setSize(sf::Vector2f(windowX, 1));
	top.setPosition(0, 0);
	top.setFillColor(sf::Color::Black);
	bottom.setSize(sf::Vector2f(windowX, 1));
	bottom.setPosition(sf::Vector2f(0, windowY - 1));
	bottom.setFillColor(sf::Color::Black);
	left.setSize(sf::Vector2f(1, windowY));
	left.setPosition(sf::Vector2f(0, 0));
	left.setFillColor(sf::Color::Black);
	right.setSize(sf::Vector2f(1, windowY));
	right.setPosition(sf::Vector2f(windowX - 1, 0));
	right.setFillColor(sf::Color::Black);


	//Code to run whilst window is open
	while (window.isOpen())
	{
		//check if left is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			//Move left
			rectPos.x -= speed;
			//if our position is outside the window, come back
			if (rectPos.x <= 0)
			{
				rectPos.x = 0;
			}
			//update the position of our paddle!
			paddle.setPosition(rectPos);
		}
		//check if right is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			//Move right
			rectPos.x += speed;
			//if our position is outside the window, come back
			if (rectPos.x >= windowX - rectSize.x)
			{
				rectPos.x = windowX - rectSize.x;
			}
			paddle.setPosition(rectPos);
		}

		if (top.getGlobalBounds().intersects(ball.getGlobalBounds()))
		{
			//did we hit the top?
			velocity.y = -velocity.y;
		}

		if (bottom.getGlobalBounds().intersects(ball.getGlobalBounds()))
		{
			//did we hit the bottom?
			velocity.y = -velocity.y;
		}

		if (left.getGlobalBounds().intersects(ball.getGlobalBounds()) || right.getGlobalBounds().intersects(ball.getGlobalBounds()))
		{
			//left or right
			velocity.x = -velocity.x;
		}

		if (paddle.getGlobalBounds().intersects(ball.getGlobalBounds()))
		{
			//did the ball hit the paddle?
			velocity.y = -velocity.y;
		}

		ball.move(velocity); //move ball around

		//Pollevent is our window updating event
		sf::Event event;
		while (window.pollEvent(event))
		{
			//if window closes
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//Clear our window, and redraw everything
		window.clear();
		window.draw(paddle);
		window.draw(ball);
		window.display();
		
	}

	return 0;
}