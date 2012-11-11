//
//  Scene.h
//  Rejtrejs
//
//  Created by Amaru on 2012-10-03.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//
#ifndef _SCENE_H
#define _SCENE_H


#include "Vec.h"
#include "Sphere.h"
#include "Plane.h"
#include "Objects.h"
#include <vector>


struct Scene 
{

    std::vector<Objects*> sceneObj;
    
    Scene ()
    {
        
    }
    
    ~Scene()
    {
        for(unsigned int i=0; i<sceneObj.size(); i++)
        {
            delete sceneObj.at(i);
        }    
    }
        
    void setup()
    {
        //Spheres
        Sphere *sphere = new Sphere(Vec(-10,-15,-30), 7, Material(0,1,0));
        sphere->mat.setDiffuse(0.8);
        sphere->mat.setReflection(0.3);
		sphere->mat.setSpecPower(3);
        sceneObj.push_back(sphere);
        
        Sphere *sphere2 = new Sphere(Vec(0,-10,-30), 5, Material(0,0,1));
        sphere2->mat.setDiffuse(0.8);
        sphere2->mat.setReflection(0.3);
		sphere2->mat.setSpecPower(3);
        sceneObj.push_back(sphere2);
        
        Sphere *sphere3 = new Sphere(Vec(0,-18,-10), 8, Material(1,0,0));
		sphere3->mat.setRefractionIndex(1.65);
		sphere3->mat.setRefraction(true);
		sphere3->mat.setSpecPower(3);	
        sceneObj.push_back(sphere3);
        
        //Planes
        Plane *top = new Plane(Vec(0,-1,0), Vec(0,30,0), Material(1,1,1));
        top->mat.setDiffuse(0.8);
		top->mat.setSpecPower(5);
        sceneObj.push_back(top);
        
        Plane *ground = new Plane(Vec(0,1,0), Vec(0,-30,0), Material(1,1,1));
        ground->mat.setDiffuse(0.8);
		ground->mat.setSpecValue(1);
		ground->mat.setSpecPower(5);
        sceneObj.push_back(ground);
        
        Plane *back = new Plane(Vec(0,0,1), Vec(0,0,-60), Material(1,1,1));
        back->mat.setDiffuse(0.8);
		back->mat.setSpecPower(5);
        sceneObj.push_back(back);
        
        Plane *right = new Plane(Vec(1,0,0), Vec(-30,0,0), Material(1,0,0));
        right->mat.setDiffuse(0.8);
		right->mat.setSpecPower(5);
        sceneObj.push_back(right);
        
        Plane *left = new Plane(Vec(-1,0,0), Vec(30,0,0), Material(0,1,0));
        left->mat.setDiffuse(0.8);
		left->mat.setSpecPower(5);
        sceneObj.push_back(left);

        //Add light
        Sphere *light = new Sphere(Vec(0,30,-10), 15, Material(1,1,1));
        light->mat.setLight(true);
        sceneObj.push_back(light);
        
       /* Sphere *light2 = new Sphere(Vec(0,30,0), 5, Material(1,1,1));
        light2->mat.setLight(true);
		light2->mat.setRefraction(0);
		light2->mat.setReflection(0);
		light2->mat.setSpecValue(1);
		light2->mat.setSpecPower(90);
        sceneObj.push_back(light2);*/

		/*Sphere *light3 = new Sphere(Vec(5,25,-30), 1, Material(1,1,1));
        light3->mat.setLight(true);
		light3->mat.setRefraction(0);
		light3->mat.setReflection(0);
		light3->mat.setSpecValue(1);
		light3->mat.setSpecPower(90);
        sceneObj.push_back(light3);

		Sphere *light4 = new Sphere(Vec(0,25,-35), 1, Material(1,1,1));
        light4->mat.setLight(true);
		light4->mat.setRefraction(0);
		light4->mat.setReflection(0);
		light4->mat.setSpecValue(1);
		light4->mat.setSpecPower(90);
        sceneObj.push_back(light4);

		Sphere *light5 = new Sphere(Vec(0,25,-25), 1, Material(1,1,1));
        light5->mat.setLight(true);
		light5->mat.setRefraction(0);
		light5->mat.setReflection(0);
		light5->mat.setSpecValue(1);
		light5->mat.setSpecPower(90);
        sceneObj.push_back(light5);*/

        
        //botten
        Vec v1(5, -29.9, -25); //vänster
        Vec v2(12.5, -29.9, -32.5); //bak
        Vec v3(12.5,-29.9, -17.5); //närmast skärmen
        Vec v4(20, -29.9, -25); //höger
        
        //Övre
        Vec v5(5, -10, -25);//vänster
        Vec v6(12.5, -10, -32.5);//bak
        Vec v7(12.5, -10, -17.5);//närmast skärmen
        Vec v8(20, -10, -25);//höger
        
        Triangle *traingle = new Triangle(v5, v1, v3, v7, Material(0,0,1));
        traingle->mat.setDiffuse(1);
		traingle->mat.setReflection(0.3);
		traingle->mat.setSpecPower(2);
        sceneObj.push_back(traingle);
        
        Triangle *traingle2 = new Triangle(v7, v3, v4, v8, Material(0,0,1));
        traingle2->mat.setDiffuse(1);
		traingle2->mat.setReflection(0.3);
		traingle2->mat.setSpecPower(2);
        sceneObj.push_back(traingle2);    
        
        Triangle *traingle5 = new Triangle(v5, v7, v8, v6, Material(1,0,0));
        traingle5->mat.setDiffuse(1);
		traingle5->mat.setReflection(0.3);
		traingle5->mat.setSpecPower(2);
        sceneObj.push_back(traingle5);
        
    }
    
};


#endif