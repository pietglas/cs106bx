#include <SFML/Graphics.hpp>
#include <complex>
#include <iostream>

class Mandelbrot 
{
public:
	Mandelbrot(double framewidth, double framelength, size_t max_iterations): 
			   framewidth_{framewidth}, framelength_{framelength}, 
			   max_iterations_{max_iterations}
	{}

	static std::complex<double> MandelbrotSequence(std::complex<double> z, 
									size_t max_iterations = 200) {
		if (max_iterations == 0)
			return z;
		else 
			return std::pow(Mandelbrot::MandelbrotSequence(z, --max_iterations), 2) + z;
	}

	static bool InMandelbrot(std::complex<double> z, size_t max_iterations = 200) {
		bool in_mandelbrot;
		std::complex<double> z_iterated = Mandelbrot::MandelbrotSequence(z, max_iterations);
		if (std::abs(z_iterated) <= 2)
			in_mandelbrot = true;
		else
			in_mandelbrot = false;

		return in_mandelbrot;
	}

	void set_mandelbrot() {
		unsigned int vecsize = framewidth_ * framelength_;
		unsigned int cols = framewidth_;
		//unsigned int rows = framelength_;
		mandelbrot_set_.reserve(vecsize);
		for (int i = 0; i != vecsize; i++) {
			// determine matrix-indices wrt chosen axes
			int row = 1 + (i / cols);
			int col = i % row;

			// take the complex number corresponding to the pixel
			double real_part = (framewidth_/2 - col) / (framewidth_ / 2);
			double complex_part = (2 * (framelength_/3) - row) / (framewidth_ / 3);
			std::complex<double> z(real_part, complex_part);
			bool in_mandelbrot = Mandelbrot::InMandelbrot(z, max_iterations_);
			if (in_mandelbrot)
				std::cout << "In mandelbrot! " << std::endl;
			mandelbrot_set_.push_back(in_mandelbrot);
		}
	}

	void set_pixels() {
		pixels_.setPrimitiveType(sf::Points);
		pixels_.resize(mandelbrot_set_.size());
		unsigned int cols = framewidth_;
		//unsigned int rows = framelength_;
		for (int i = 0; i != pixels_.getVertexCount(); i++) {
			// determine matrix-indices wrt chosen axes
			int row = 1 + (i / cols);
			int col = i % row;

			pixels_[i].position = sf::Vector2f(col - 1, row - 1);
			if (mandelbrot_set_.at(i))
				pixels_[i].color = sf::Color::Black;
			else
				pixels_[i].color = sf::Color::White;
		}
	}

	sf::VertexArray get_pixels() const {return pixels_;}

private:
	double framewidth_;
	double framelength_;
	size_t max_iterations_ = 200;
	std::vector<bool> mandelbrot_set_;
	sf::VertexArray pixels_;
};

int main() {
	double framelength = 401;
	double framewidth = 603;
	size_t screenlength = framelength;
	size_t screenwidth = framewidth;
	size_t max_iterations = 200;
	sf::RenderWindow window(sf::VideoMode(screenwidth, screenlength), "mandelbrot");

	Mandelbrot mandelbrot{framewidth, framelength, max_iterations};

	mandelbrot.set_mandelbrot();
	mandelbrot.set_pixels();

	while (window.isOpen()) {

		// handle events
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// draw
		window.clear(sf::Color::White);
		window.draw(mandelbrot.get_pixels());
		window.display();
	}

	return 0;

}



