#pragma once
//#include <GL\glut.h>
#include "Ray.h"
#include <GL/glut.h> //OpenGL Utility Toolkits

class Material {
  public:
    Material();
    glm::vec3 ambient; //Reflectivity in r/g/b channels //surroundinh light
    glm::vec3 diffuse;  //spreading light
    glm::vec3 specular;	// mirror reflect
    float glossiness; //Specular intensity
    float reflection;
    
};

// The father class of all the objects displayed. Some features would be shared between objects, others will be overloaded.
class Object {
  
  public:
    Object(const glm::mat4 &transform = glm::mat4(1.0f), const Material &material = Material());
    //  The keyword const here will check the type of the parameters and make sure no changes are made
    //  to them in the function. It's not necessary but better for robustness

    virtual bool Intersect(const Ray &ray, IntersectInfo &info) const { return true; }
    glm::vec3 Position() const { return glm::vec3(transform[3][0], transform[3][1], transform[3][2]); }
    const Material *MaterialPtr() const { return &material; }

  //protected:  //  The difference between protected and private is that the protected members will still be available in subclasses.
    glm::mat4 transform;  // Usually a transformation matrix is used to decribe the position from the origin.
    Material material;
};

//  For all those objects added into the scene. Describing them in proper ways and the implement of function Intersect() is what needs to be done.
//  Actually, it's also possible to use some other objects, but those geometries are easy to describe and the intersects are easier to calculate.
//  Try something else if you like, for instance, a box?

/* TODO: Implement */
class Sphere : public Object {
public:
    glm::vec3 ballheart;
    float radius;
 
      Sphere(glm::vec3 center, float size,const glm::mat4 &transform = glm::mat4(1.0f), const Material &material = Material()):Object(){
      //this->material.ambient = amb;
      //this->material.diffuse = dif;
      ballheart = center;
      radius = size;
      }


    virtual bool Intersect(const Ray &ray, IntersectInfo &info) const;  //  To figure out if the Ray hit this object.


};


/* TODO: Implement */
class Plane : public Object {
  public:
    glm::vec3 planenormal;
    glm::vec3 planepoint;
      Plane(glm::vec3 normal, glm::vec3 point,const glm::mat4 &transform = glm::mat4(1.0f), const Material &material = Material()):Object(){
      //this->material.ambient = glm::vec3(1,0,0);  //?????
      planenormal = normal;
      planepoint = point;
      }

    virtual bool Intersect(const Ray &ray, IntersectInfo &info) const;
};

/* TODO: Implement */
class Triangle : public Object {
  public:
    glm::vec3 point1;
    glm::vec3 point2;
    glm::vec3 point3;
  Triangle(glm::vec3 p1, glm::vec3 p2,glm::vec3 p3,const glm::mat4 &transform = glm::mat4(1.0f), const Material &material = Material()):Object(){
      //this->material.ambient = glm::vec3(1,0,0);  //?????
      point1 = p1;
      point2 = p2;
      point3 = p3;
      }
    
    virtual bool Intersect(const Ray &ray, IntersectInfo &info) const;
};
