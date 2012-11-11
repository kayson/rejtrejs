//
//  Material.h
//  Rejtrejs
//
//  Created by Amaru on 2012-09-10.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "Vec.h"
#include "Color.h"

struct Material {
	Color color;
    
    double diffuse;
	double refractionIndex;
	double specValue;
	double specPower;
	double reflection;
	bool refraction;
    bool light;
    
	
	Material() {
		color = Color();
	}
    
	Material(const double &r0, const double &g0, const double &b0) {
		color = Color(r0,g0,b0);
		diffuse = 0;
		specValue = 1;
		specPower = 1;
		reflection = 0;
		refraction = false;
		light = false;
	}
    
    Color getColor()
    {
        return color;
    }
    
    void setDiffuse(double d){
        diffuse = d;
    }
    
    double getDiffuse(){return diffuse;}
    
    
    void setReflection(double reflect){
        reflection = reflect;
    }
	double getReflection(){return reflection;}



	void setRefraction(bool refract){
        refraction = refract;
    }
	void setRefractionIndex(double refraction){
        refractionIndex = refraction;
    }
    bool getRefraction(){return refraction;}
	double getRefractionIndex(){return refractionIndex;}
    
    
    void setLight(bool islight)
    {
        light = islight;
    }
	bool isLight(){return light;}
    

	void setSpecValue(double specVal){
        specValue = specVal;
    }
    double getSpecValue(){return specValue;}

	void setSpecPower(double specPow){
        specPower = specPow;
    }
    double getSpecPower(){return specPower;}
    

	~Material() {}
};

#endif