#ifndef _VEC_H
#define _VEC_H

struct Vec {
	double x,y,z;
    
	Vec() {
		x = 0.0;
		y = 0.0;
		z = 0.0;
	}
    
	Vec(double x0, double y0, double z0) {
		x = x0;
		y = y0;
		z = z0;
	}
    
    Vec(double v0) {
		x = y = z = v0;
	}
    
	Vec operator+(const Vec& vec3) const {
		return Vec(x+vec3.x,y+vec3.y,z+vec3.z);	
	}
    
	Vec operator-(const Vec& vec3) const {
		return Vec(x-vec3.x,y-vec3.y,z-vec3.z);	
	}
    
	Vec& operator+=(const Vec& vec3) {
		x+=vec3.x;
		y+=vec3.y;
		z+=vec3.z;
		return *this;
	}
    
	Vec& operator-=(const Vec& vec3) {
		x-=vec3.x;
		y-=vec3.y;
		z-=vec3.z;
		return *this;
	}
    
	// Skal‰rprodukt
	double operator*(const Vec &vec3) const {
		return x*vec3.x + y*vec3.y + z*vec3.z;
	}
    
	Vec operator*(double s) const {
		return Vec((s*x), (s*y), (s*z));
	}
    
    
	Vec& operator*=(double s) {
		x*=s;
		y*=s;
		z*=s;
		return *this;
	}
    
	Vec& operator/=(double s) {
		return *this *= 1.0/s;
	}
	
	Vec operator/(double s) const {
		double invS = 1.0/s;
		return Vec(x*invS, y*invS, z*invS);
	}
    
    double length(void)
    {
        return sqrt(x*x+y*y+z*z);
        
    }
    
	// Normalisera vektor
	Vec& Normalize() {
		double len = sqrt( x*x + y*y + z*z );
        
		x /= len;
		y /= len;
		z /= len;
		return *this;
	}
    
    Vec cross(Vec b)
    {
        return Vec(y*b.z-z*b.y,-1*(x*b.z-z*b.x),x*b.y-y*b.x);
    }

	~Vec() {}
    
};

std::ostream& operator<<(std::ostream& o, const Vec& obj) 
{
    return o << "[" << obj.x << " " << obj.y << " " << obj.z << "]";
};

#endif