//
//  Light.h
//  Rejtrejs
//
//  Created by Amaru on 2012-09-12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//
#ifndef _LIGHT_H
#define _LIGHT_H

#include "Vec.h"
#include "Material.h"

struct Light 
{
	Vec pos;
	Material color;
    
	Light(const Vec &pos0,const Material &mat0) {
		pos = pos0;
		color = mat0;
	}
	~Light() {}
    
};

#endif