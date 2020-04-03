#include <SFML/Graphics.hpp>
#include <memory>


class SierpinskiTriangle
{
public:
    SierpinskiTriangle(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, 
    				   sf::RenderWindow* window, unsigned int level=0):
                       a_{a}, b_{b}, c_{c}, window_{window}, level_{level}
        {
        triangle_[0].position = a;
		triangle_[1].position = b;
		triangle_[2].position = c;
		triangle_[3].position = a;

		triangle_[0].color = sf::Color::Black;
		triangle_[1].color = sf::Color::Black;
		triangle_[2].color = sf::Color::Black;
		triangle_[3].color = sf::Color::Black;

        if (level == 0) {
            sierpinski_trian_a_ = nullptr;
            sierpinski_trian_b_ = nullptr;
            sierpinski_trian_c_ = nullptr;
        }
        else {
        	// calculate coords for the new triangles
        	sf::Vector2f betw_ab((a.x + b.x) / 2, a.y);
        	sf::Vector2f betw_bc(((betw_ab).x + b.x) / 2, (b.y + c.y) / 2);
        	sf::Vector2f betw_ca((a.x + (betw_ab).x) / 2, (b.y + c.y) / 2);
        	
        	// define triangles
        	SierpinskiTriangle trian_a{a, betw_ab, betw_ca, window, level - 1};
        	SierpinskiTriangle trian_b{betw_ab, b, betw_bc, window, level - 1};
        	SierpinskiTriangle trian_c{betw_ca, betw_bc, c, window, level - 1};
        	
        	// set pointers for the recursion
        	sierpinski_trian_a_ = std::make_shared<SierpinskiTriangle>(trian_a);
        	sierpinski_trian_b_ = std::make_shared<SierpinskiTriangle>(trian_b);
        	sierpinski_trian_c_ = std::make_shared<SierpinskiTriangle>(trian_c);
        }
    }

    void Draw() {
    	if (level_ == 0) {
    		(*window_).draw(triangle_);
    	}
    	else {
    		(*window_).draw(triangle_);
    		(*sierpinski_trian_a_).Draw();
    		(*sierpinski_trian_b_).Draw();
    		(*sierpinski_trian_c_).Draw();
    	}
    }

private:
    // level defines how deep the recursion goes
    unsigned int level_;
    // recursive layer
    std::shared_ptr<SierpinskiTriangle> sierpinski_trian_a_;
    std::shared_ptr<SierpinskiTriangle> sierpinski_trian_b_;
    std::shared_ptr<SierpinskiTriangle> sierpinski_trian_c_;

    // get a pointer to the window
    sf::RenderWindow* window_;

    sf::Vector2f a_ = sf::Vector2f(0.f, 0.f);
	sf::Vector2f b_ = sf::Vector2f(0.f, 0.f);
	sf::Vector2f c_ = sf::Vector2f(0.f, 0.f);

	// triangle
	sf::VertexArray triangle_ = sf::VertexArray(sf::LineStrip, 4);
};



int main () {
	sf::RenderWindow window(sf::VideoMode(400, 400), "draw a line1");

	sf::Vector2f a(10.f, 10.f);
	sf::Vector2f b(390.f, 10.f);
	sf::Vector2f c(200.f, 390.f);
	sf::RenderWindow* window_ptr = &window;
	SierpinskiTriangle sierpinski{a, b, c, window_ptr, 10};

	while (window.isOpen()) {

		// handle events
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// draw
		window.clear(sf::Color::White);
		sierpinski.Draw();
		//window.draw(triangle);
		window.display();
	}

	return 0;
}
