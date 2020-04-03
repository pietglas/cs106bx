#include <SFML/Graphics.hpp>

class SierpinskiTriangle: public sf::Shape
{
public:


private:
	// vertices
	sf::Vector2f A;
	sf::Vector2f B;
	sf::Vector2f C;

	// line segments
	sf::VertexArray AB(sf::Lines, 2);
	sf::VertexArray AC(sf::Lines, 2);
	sf::VertexArray BC(sf::Lines, 2);
};

int main () {
	sf::RenderWindow window(sf::VideoMode(400, 400), "draw a line1");

	// create an array of 3 vertices that define a line1 primitive
	sf::VertexArray line1(sf::Lines, 2);
	sf::VertexArray line2(sf::Lines, 2);
	sf::VertexArray line3(sf::Lines, 2);

	// define the position of the line1's points
	line1[0].position = sf::Vector2f(10.f, 10.f);
	line1[1].position = sf::Vector2f(390.f, 10.f);

	line2[0].position = sf::Vector2f(10.f, 10.f);
	line2[1].position = sf::Vector2f(200.f, 390.f);

	line3[0].position = sf::Vector2f(390.f, 10.f);
	line3[1].position = sf::Vector2f(200.f, 390.f);


	// define the color of the line1's points
	line1[0].color = sf::Color::Black;
	line1[1].color = sf::Color::Black;

	line2[0].color = sf::Color::Black;
	line2[1].color = sf::Color::Black;

	line3[0].color = sf::Color::Black;
	line3[1].color = sf::Color::Black;

	while (window.isOpen()) {
		
		// handle events
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) 
				window.close();
		}

		// draw
		window.clear(sf::Color::White);
		window.draw(line1);
		window.draw(line2);
		window.draw(line3);
		window.display();
	}

	return 0;
}