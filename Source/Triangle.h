//  plane.h
//  Rejtrejs
//
//  Created by Amaru on 2012-09-18.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _TRIANGLE_H
#define _TRIANGLE_H

#include "Vec.h"
#include "Material.h"
#include "Objects.h"

struct Triangle: Objects  
{
    Vec p0, normal;
	Vec orig, dir, v1, v2, v3, v4, temp, temp2;
    
    Triangle(const Vec &v_1, const Vec &v_2, const Vec &v_3, const Vec &v_4, const Material &mat0)
    {
        v1=v_1;
        v2=v_2;
        v3=v_3;
        v4=v_4;
        mat = mat0;
        temp=(v2-v1);
        temp2=(v2-v3);
        normal = (temp2.cross(temp)).Normalize();
        
    }
    
	~Triangle() {}
    
	bool intersectedBy(const Ray& ray, double &val)
    {
        //std::cout <<val<<std::endl;
        //std::cout <<normal<<std::endl;
       // Vec nnormal = normal.Normalize();
        Vec nRayDir = ray.dir;
        nRayDir.Normalize();
        double dist[2];
        
        
        Vec point, i1, i2, i3, endMovement;
        double dot11, dot12, dot13, dot22, dot23, invDen, u, v;
        dist[0] = (-((ray.orig-v1)*normal)/(nRayDir*normal));
        //std::cout <<distance<<std::endl;
        if (dist[0] >= 0000.1 && dist[0]<val)
        {
            endMovement=nRayDir*dist[0];
            point = ray.orig + endMovement;
            //std::cout <<point<<std::endl;
            i1 = v2 - v1;
            i2 = v3 - v1;
            i3 = point - v1;
            
            dot11 = i1 * i1;
            dot12 = i1 * i2;
            dot13 = i1 * i3;
            dot22 = i2 * i2;
            dot23 = i2 * i3;
            
            // Barycentric coordinates
            invDen = 1 / (dot11 * dot22 - dot12 * dot12);
            u = (dot22 * dot13 - dot12 * dot23) * invDen;
            v = (dot11 * dot23 - dot12 * dot13) * invDen;
            //std::cout <<u<<" "<<v<<std::endl;
            // 1.0 + 1e-10 fixes a precision problem
            // on some processors
            if (u >= 0.0 && v >= 0.0 && u+v < 1.0 + 1e-10)
            {    
               
                val = endMovement.length(); 
                //std::cout <<val<<std::endl;
                return true;
            }    
        }
        
        dist[1] = (-((ray.orig-v3)*normal)/(nRayDir*normal));
        
        if (dist[1] >= 0000.1 && dist[1]<val)
        {
            endMovement=nRayDir*dist[1];
            point = ray.orig + endMovement;
            
            i1 = v1 - v3;
            i2 = v4 - v3;
            i3 = point - v3;
            
            dot11 = i1 * i1;
            dot12 = i1 * i2;
            dot13 = i1 * i3;
            dot22 = i2 * i2;
            dot23 = i2 * i3;
            
            // Barycentric coordinates
            invDen = 1 / (dot11 * dot22 - dot12 * dot12);
            u = (dot22 * dot13 - dot12 * dot23) * invDen;
            v = (dot11 * dot23 - dot12 * dot13) * invDen;
            
            // 1.0 + 1e-10 fixes a precision problem
            // on some processors
            if (u >= 0.0 && v >= 0.0 && u+v < 1 + 1e-10)
            {    
                //std::cout <<"hej"<<std::endl;
                val = endMovement.length();  
                //std::cout <<val<<std::endl;
                return true;
            }   
        }
        
        return false;
    }
    Vec GetNormal(Vec &position)
    {
        return normal;
    }
    
};

#endif