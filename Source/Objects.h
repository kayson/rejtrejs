//
//  Object.h
//  Rejtrejs
//
//  Created by Amaru on 2012-09-27.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//
#ifndef _OBJECT_H
#define _OBJECT_H

#include "Ray.h"
#include "Material.h"

struct Objects 
{
    Material mat;
    
    Objects ()
    {
        //std::cout << "Object created!";
    }
    
    ~Objects(void)
    {
        //std::cout << "Object destroy!";
    }
    
    void setupMaterial(double r, double g, double b){
        Material(r, g ,b);
    }    
    
    virtual Vec GetNormal(Vec& position) = 0;
    
    virtual bool intersectedBy(const Ray& ray, double &val) = 0;

};

#endif




