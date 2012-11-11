//
//  Ray.h
//  Rejtrejs
//
//  Created by Amaru on 2012-09-10.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _RAY_H
#define _RAY_H

#include "Vec.h"

struct Ray 
{
	Vec orig, dir;
    
	Ray() {
		orig = Vec();
		dir = Vec();
	}
    
	Ray(const Vec &orig0, const Vec &dir0) {
		orig = orig0;
		dir = dir0;
	}

	~Ray() {}
    
};

#endif