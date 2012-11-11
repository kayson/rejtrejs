//
//  savebmp.h
//  Rejtrejs
//
//  Created by Amaru on 2012-09-07.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//


#ifndef _SPHERE_H
#define _SPHERE_H

#include "Vec.h"
#include "Ray.h"
#include "Material.h"
#include "Objects.h"

struct Sphere : Objects 
{
	Vec pos;
    Ray rej;
	double rad;
	
    
	Sphere(const Vec &pos0,const double &rad0, const Material &mat0) {
		pos = pos0;
		rad = rad0;
        mat = mat0;
	}
	~Sphere() {}
    
	bool intersectedBy(const Ray& ray, double &val)
    {
		Vec d = ray.orig-pos;
        
		double A = ray.dir*ray.dir;
		double B = d*ray.dir;
		double C = (d*d)-(rad*rad);
        
		double disc = B*B-A*C;
        
        double t[2];
        if(disc<0) return false; //miss

		t[0]=d*ray.dir*-1+sqrt(disc); //hittar skarningspunkter
        t[1]=d*ray.dir*-1-sqrt(disc); 
        
		bool returnval = false;
        if ((t[0] > 0.1) && (t[0] < val)) 
		{
			val = t[0];
			returnval = true;
		} 
		if ((t[1] > 0.1) && (t[1] < val)) 
		{
			val = t[1];
			returnval = true;
		}
		return returnval;
	}
    
    
    Vec GetNormal(Vec& position)
    {
        
        Vec n = (position - pos);
        n.Normalize();
        return n;
    }

	Vec GetRandomPoint()
	{
		Vec rngVec ( (double)rand()/RAND_MAX-(double)rand()/RAND_MAX, 
				-(double)rand()/RAND_MAX, 
				(double)rand()/RAND_MAX-(double)rand()/RAND_MAX );

		rngVec.Normalize();
		
		return pos+rngVec*rad;
	}
    
    
};


#endif