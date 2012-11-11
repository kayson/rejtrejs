#ifndef _COLOR_H
#define _COLOR_H

struct Color 
{
	double r, g, b;

    Color ()
    {
		r = 0;
		g = 0;
		b = 0;
    }

	Color(double x0, double y0, double z0) {
		r = x0;
		g = y0;
		b = z0;
	}

	Color& operator+=(const Color& col) {
		r+=col.r;
		g+=col.g;
		b+=col.b;
		return *this;
	}

    ~Color(){}
   

};

std::ostream& operator<<(std::ostream& o, const Color& obj) 
{
    return o << "[" << obj.r << "," << obj.g << "," << obj.b << "]";
};


#endif




