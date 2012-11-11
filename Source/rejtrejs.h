#ifndef _REJTREJS_H
#define _REJTREJS_H

#define MAXDISTANCE 1000
#define MINDISTANCE 1
#define SAMPLES 50
#define DoF 200
#define MAXITERATIONS 1000
#define imageWidth 1280
#define imageHeight 720
#define probability 0.9

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <omp.h>
#include <ctime>

#include "Vec.h"
#include "Sphere.h"
#include "Ray.h"
#include "Material.h"
#include "Plane.h"
#include "Objects.h"
#include "Light.h"
#include "Triangle.h"
#include "Scene.h"
#include "Color.h"

using namespace std;

const double PI = 3.14159265358979323846;
const double refAir = 1;

const double alpha = 1 - probability;
Ray rej;
Vec pos;
Material mat;
Scene scene;
Color pixel;

int fov = 30; // Synf‚Ä∞lt i grader
double aspectratio = (double)imageWidth / (double)imageHeight;
double angle = tan(PI * 0.5 * fov/180);
double invWidth = 1 / (double)imageWidth, invHeight = 1 / (double)imageHeight;

unsigned char *img = NULL;
void savebmp(const char *filename, int w,int h);
Color traceRay(Ray& rej, int& depth, double coef);

double getShade(const Ray& light, double distance);
Vec getRefractedVector(const Vec& normal, const Vec& incident, double n1, double n2, bool insideMedium);
double getReflectance(const Vec& normal, const Vec& incident, double n1, double n2, bool insideMedium);

struct Rejtrejs {
    
};


#endif