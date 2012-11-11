#include "rejtrejs.h"

int main() 
{    
	srand((unsigned)time(0));

    scene.setup();
    
	// Allokering minne fÀÜr bilden och g√∂r alla pixlar svarta.
    img = (unsigned char *)malloc(3*imageWidth*imageHeight);
    memset(img,0,sizeof(img));

    #pragma omp parallel for schedule(dynamic, 1) 
	for(int i = 0; i < imageWidth ; i++)
    {
		fprintf(stderr,"\rRendering image %dx%d (%d spp, AAx4) %5.2f%% with %d/%d threads.",
			imageWidth,imageHeight,SAMPLES*4,100.*i/(imageWidth-1),
			omp_get_num_threads(), omp_get_max_threads());
        for(int j = 0; j < imageHeight; j++)
        {
			double r = 0, g = 0, b = 0;

			for(double fragmentx = i; fragmentx < i + 1; fragmentx += 0.5)
			for(double fragmenty = j; fragmenty < j + 1; fragmenty += 0.5)
			{
				double x = (2 * ((fragmentx + 0.5) * invWidth) - 1) * angle * aspectratio;
				double y = (1 - 2 * ((fragmenty + 0.5) * invHeight)) * angle;
				Ray ray(Vec(0,0,150),Vec(x,y,-1));
				ray.dir.Normalize();


				// DEPTH OF FIELD
				Vec rngVec ( (double)rand()/RAND_MAX-(double)rand()/RAND_MAX, 
				(double)rand()/RAND_MAX-(double)rand()/RAND_MAX, 
				(double)rand()/RAND_MAX-(double)rand()/RAND_MAX );
				rngVec *= 0.4; // FOCUS
				rngVec += ray.orig;
				Vec dir = ray.orig+ray.dir*DoF - rngVec;
				dir.Normalize();
				ray.orig = rngVec;
				ray.dir = dir;
				

				for ( int s = 0; s < SAMPLES; s++ ) 
				{					
					pixel = Color();
					int iters = 0;

					pixel = traceRay(ray, iters, 1.0);

					if ( pixel.r > 1 ) pixel.r =  1; if ( pixel.g > 1 ) pixel.g = 1; if ( pixel.b > 1 ) pixel.b = 1;

					r += pixel.r / 4;
					g += pixel.g / 4;
					b += pixel.b / 4;		
				}

			}

			r /= SAMPLES;
			g /= SAMPLES;
			b /= SAMPLES;		

			unsigned char red	=	(unsigned char)(255*r);
            unsigned char green =   (unsigned char)(255*g);
            unsigned char blue  =	(unsigned char)(255*b);

            img[(i+j*imageWidth)*3+2] += red;
            img[(i+j*imageWidth)*3+1] += green;
            img[(i+j*imageWidth)*3+0] += blue;

        }
	}           

	savebmp("test.bmp", imageWidth, imageHeight);	
	free(img);
	system("test.bmp");

} 




Color traceRay(Ray& rej, int& iterations, double coef){
	iterations++;
    if (coef < 0.0000001 || iterations >= MAXITERATIONS) return Color();
    double distanceToIntersect = MAXDISTANCE;
    double distance = MAXDISTANCE;
	Color temppixel;
    Color lightcolor;
    Color color;
	double shade;
    double diffusecolor;
    Vec lightVec;
    Objects* nearestObject;

    // Find if ray intersects and object in the scene
    for(unsigned int i=0;i<scene.sceneObj.size();i++) 
    {  
        Objects* currentObject = scene.sceneObj[i];
        bool hit = currentObject->intersectedBy(rej,distance);
        
			// Hit a object 
            if( hit && distance<distanceToIntersect)
            {
                distanceToIntersect = distance;
                color = currentObject->mat.getColor();
                nearestObject = currentObject;
        
                if(currentObject->mat.isLight())
                {
					return color;
                }
            }
    }  
 
    if(distanceToIntersect >= MAXDISTANCE || distanceToIntersect < MINDISTANCE ) return Color();

    // get intersection point
    Vec intersectionPoint = rej.orig + rej.dir*distanceToIntersect;
    // get normal at the intersectionpoint
    Vec n = nearestObject->GetNormal(intersectionPoint);

	double reflection = nearestObject->mat.getReflection();
	bool refraction = nearestObject->mat.getRefraction();		
	// Branching
	if(refraction || reflection > 0)
	{
		double refractCoef = 0;
		double reflectCoef = 0;
		if( refraction )
		{
			// Refracted branch
			bool insideMedium;
			if (n * rej.dir > 0)
			{
				n *= (-1.0);
				insideMedium = true;
			}
			else insideMedium = false;
			double refInd = nearestObject->mat.getRefractionIndex();
			Vec refDir = getRefractedVector(n,rej.dir,refAir,refInd,insideMedium);
			Ray refRay(intersectionPoint,refDir);
			reflection = getReflectance(n,rej.dir,refAir,refInd,insideMedium);
			if ( reflection < 0 || reflection > 1 ) cout << "reflectance fel : " << reflection << "\n";
			refractCoef = coef - (coef * reflection);
			coef -= refractCoef;

			temppixel += traceRay(refRay, iterations, refractCoef);
		}
		// Perfect reflected branch
		reflectCoef = coef * reflection;
		coef -= reflectCoef;

		const double cosI = -1.0 * (rej.dir * n);
		Vec refDir = rej.dir + n * cosI * 2.0;
		Ray newRay(intersectionPoint, refDir);
		temppixel += traceRay(newRay, iterations, reflectCoef);
	}
	else
	{
		double rng = (double)rand()/RAND_MAX;
		if ( rng < alpha )
		{
			Vec rngVec ( (double)rand()/RAND_MAX-(double)rand()/RAND_MAX, 
				(double)rand()/RAND_MAX-(double)rand()/RAND_MAX, 
				(double)rand()/RAND_MAX-(double)rand()/RAND_MAX );

			Vec newDir = rngVec.cross(n);
			newDir.Normalize();

			double eps1 = (double)rand()/RAND_MAX*2*PI;
			double eps2 = sqrt((double)rand()/RAND_MAX);

			double x = cos(eps1)*eps2;
			double y = sin(eps1)*eps2;
			double z = sqrt(1-eps2*eps2);
			Vec ssx = newDir * x + n.cross(newDir) * y + n * z;
			ssx.Normalize();

			Vec H = newDir - rej.dir;
			H.Normalize();

			double blinnTerm = max(H * n, 0.0);
			double specVal = nearestObject->mat.getSpecValue();
			double specPow = nearestObject->mat.getSpecPower();
			blinnTerm = specVal * pow(blinnTerm , specPow) * coef;

			coef -= blinnTerm;
				
			Ray newRay(intersectionPoint, ssx);
			temppixel += traceRay(newRay, iterations, blinnTerm / alpha);
		}
		else // ABSORBED
		{
			//return temppixel;
		}
	}


	// Leaf
    for(unsigned int l=0; l<scene.sceneObj.size(); l++) 
    {     
        if(scene.sceneObj.at(l)->mat.isLight())
        {
            Sphere *light = (Sphere*)scene.sceneObj.at(l);    
            lightVec = light->GetRandomPoint() - intersectionPoint;
            if (n*lightVec <= 0)
                continue;
                
            double distanceToLight = lightVec.length();
				
			Ray lightRay;
			lightRay.dir = lightVec.Normalize();
			lightRay.orig = intersectionPoint;			
				
			shade = getShade(lightRay, distanceToLight);
			lightcolor = light->mat.getColor();
			diffusecolor = nearestObject->mat.getDiffuse(); 
                    
			double lambert = max(lightRay.dir*n, 0.0);
            Vec H = lightRay.dir - rej.dir;
			H.Normalize();

			double blinnTerm = max(H * n, 0.0);
			double specVal = nearestObject->mat.getSpecValue();
			double specPow = nearestObject->mat.getSpecPower();
			blinnTerm = specVal * pow(blinnTerm , specPow) * coef;

			temppixel.r += color.r * lambert  * shade * blinnTerm * diffusecolor * lightcolor.r;
			temppixel.g += color.g * lambert * shade * blinnTerm * diffusecolor * lightcolor.g;
			temppixel.b += color.b * lambert * shade * blinnTerm * diffusecolor * lightcolor.b;    

        }//Avslut if-sats lights
    }//Avslut Object forloop 

	return temppixel;
}// Avslut trace ray


double getShade(const Ray& lightRay, double distance)
{
	double distanceToLight = distance;
	double shade = 1.0;
	for(unsigned int i=0;i<scene.sceneObj.size();i++) 
	{  	
		if(scene.sceneObj.at(i)->mat.isLight()==false)
			{    
				Objects* currentObject = scene.sceneObj[i];

				bool hit = currentObject->intersectedBy(lightRay,distance);
				// Hit a shadow object 
				if(hit && distance < distanceToLight && currentObject->mat.getRefraction() == 0)
				{
					shade -=  min(shade,((distanceToLight-distance)/distanceToLight));
					return shade;
				}

			}
	}  
	return shade;
}

Vec getRefractedVector(const Vec& normal, const Vec& incident, double n1, double n2, bool insideMedium)
{
	double n = n1 / n2;
	if( insideMedium ) n = 1.0 / n;
	const double cosI = -1.0*(normal * incident);
	const double sinT2 = n * n * ( 1.0	- cosI * cosI );
	if ( sinT2 > 1.0 ) return Vec();
	const double cosT = sqrt(1.0 - sinT2);
	return incident * n  + normal * (n * cosI - cosT);
}

double getReflectance(const	Vec& normal, const Vec& incident, double n1, double n2, bool insideMedium)
{	
	if( insideMedium ) 
	{
		double tmp = n2;
		n2 = n1;
		n1 = tmp;
	}
	double n = n1 / n2;


	const double cosI = -1.0*( normal * incident );
	const double sinT2 = n * n * ( 1.0 - cosI * cosI );
	if(sinT2 > 1.0) return 1.0;
	const double cosT = sqrt(1.0 - sinT2);
	const double r0rth = (n1 * cosI - n2 * cosT) / (n1 * cosI + n2 * cosT);
	const double rPar = (n2 * cosI - n1 * cosT) / (n2 * cosI + n1 * cosT);
	return (r0rth * r0rth + rPar * rPar) / 2.0;
}


void savebmp( const char *filename, int w, int h )
{
    int i;
    FILE *f;
    int filesize = 54 + 3*w*h;
    
    unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
    unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
    unsigned char bmppad[3] = {0,0,0};
    
    bmpfileheader[ 2] = (unsigned char)(filesize    );
    bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
    bmpfileheader[ 4] = (unsigned char)(filesize>>16);
    bmpfileheader[ 5] = (unsigned char)(filesize>>24);
    
    bmpinfoheader[ 4] = (unsigned char)(       w    );
    bmpinfoheader[ 5] = (unsigned char)(       w>> 8);
    bmpinfoheader[ 6] = (unsigned char)(       w>>16);
    bmpinfoheader[ 7] = (unsigned char)(       w>>24);
    bmpinfoheader[ 8] = (unsigned char)(       h    );
    bmpinfoheader[ 9] = (unsigned char)(       h>> 8);
    bmpinfoheader[10] = (unsigned char)(       h>>16);
    bmpinfoheader[11] = (unsigned char)(       h>>24);

    f = fopen(filename,"wb");
    fwrite(bmpfileheader,1,14,f);
    fwrite(bmpinfoheader,1,40,f);

    for(i=0; i<h; i++)
    {
        fwrite(img+(w*(h-i-1)*3),3,w,f);
        fwrite(bmppad,1,(4-(w*3)%4)%4,f);
    }
    fclose(f);
}



