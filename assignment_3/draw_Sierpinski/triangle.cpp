#include <SFML/Graphics.hpp>

class SierpinskiTriangle: public sf::Shape
{
public:
    explicit SierpinskiTriangle(const sf::Vectorsf& a, const sf::Vector2f& b,
                                const sf::Vector2f& c, unsigned int level=0):
                                a_{a}, b_{b}, c_{c}, level_{level} {
        if (level == 0) {
            SierpinskiTriangle ptra = nullptr;
            sierpinski_trian_a_ = ptra;
            SierpinskiTriangle ptrb = nullptr;
            sierpinski_trian_b_ = ptrb;
            SierpinskiTriangle ptrc = nullptr;
            sierpinski_trian_c_ = ptrc;
        }
        else {

        }
    }

private:
    unsigned int level_;
    SierpinskiTriangle* sierpinski_trian_a_;
    SierpinskiTriangle* sierpinski_trian_b_;
    SierpinskiTriangle* sierpinski_trian_c_;

	// vertices
	sf::Vector2f a_;
	sf::Vector2f b_;
	sf::Vector2f c_;

	// line segments
	sf::VertexArray ab_(sf::Lines, 2);
	sf::VertexArray ac_(sf::Lines, 2);
	sf::VertexArray bc_(sf::Lines, 2);
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
