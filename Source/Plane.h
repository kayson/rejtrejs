//  plane.h
//  Rejtrejs
//
//  Created by Amaru on 2012-09-18.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _PLANE_H
#define _PLANE_H

#include "Vec.h"
#include "Material.h"
#include "Objects.h"

struct Plane : Objects
{
    Vec p0, normal;
	Vec orig, dir;
    
    Plane(const Vec &n,const Vec &point, const Material &mat0)
    {
        normal=n;
        p0=point;
        mat=mat0;
    }
    
	~Plane() {}
    
	bool intersectedBy(const Ray& ray, double &val)
    {
        
        double t[2];
        
        t[0]=(ray.dir * normal);
        
        if (t[0] != 0)
        {
			t[1]=((p0-ray.orig) * normal)/t[0];
        }
        else return false;
        
        if((t[1]<0.000001) || (t[1] > val))
        {
            return false;
        }    
        val = t[1];
        return true;
        
	}
    
    Vec	GetNormal(Vec& position) 
    { 
        //std::cout << normal <<std::endl;
        return normal;
    }
    
    
};

#endif