#ifndef COLOR_HPP
#define COLOR_HPP

class Color
{
public:

	Color(int red, int green, int blue, int alpha) : 
		_red(red),
		_green(green),
		_blue(blue),
		_alpha(alpha) 
	{}		

	const int getRed(){ return this->_red; }
	const int getGreen() { return this->_green; }
	const int getBlue() { return this->_blue; }
	const int getAlpha() { return this->_alpha; }

private :

	int _red;
	int _green;
	int _blue;
	int _alpha;

};

#endif