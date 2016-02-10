#include "Object.h"
#include <GL/gl.h>

Material::Material():
    ambient(1.0f),
    diffuse(1.0f),
    specular(1.0f),
    glossiness(10.0f),
    reflection(0.8f)
   
  {}

Object::Object(const glm::mat4 &transform, const Material &material):
    transform(transform),
    material(material)
  {}

/* TODO: Implement */
bool Sphere::Intersect(const Ray &ray, IntersectInfo &info) const { 
        //float t0, t1; // solutions for t if the ray intersects 
//#if 0 
        
        // geometric solution
     glm::vec3 L = ballheart-ray.origin; 
     float tca = glm::dot(L,ray.direction);
     float a =glm::dot(ray.direction,ray.direction);
     float b =2*glm::dot(ray.direction,-L); 
     float c =glm::dot(L,L)-pow(radius,2);
     float different = pow(b,2)-4*a*c;
     float d =(-b-sqrt(different)/(2*a));
     //glm::vec3 unit = glm::normalize (ray.direction);
     //float distance = glm::dot(ray.direction,L);
      if (different <0) return false; 

      else if (different==0)// one intersection point
        {
         
         
         //glm::vec3 unit = glm::normalize (ray.direction);
         //float distance = glm::dot(unit,L);
         info.hitPoint =ray.origin+d*ray.direction;

         glm::vec3 tem = glm::normalize(info.hitPoint-ballheart);
         float denom = glm::dot(tem,ray.direction);
         info.normal = (denom <0)? -tem : tem;
         info.time=glm::length(ray.origin-info.hitPoint);
         info.material= &material;
         return true;
        }
      else // 2 interaction point not yet to "write"
        {

         info.hitPoint = ray.origin+d*ray.direction;
         glm::vec3 tem = glm::normalize(info.hitPoint-ballheart);
         float denom = glm::dot(tem,ray.direction);
         info.normal = (denom <0)? -tem : tem;
         info.time=glm::length(ray.origin-info.hitPoint);
         info.material= &material;
         return true;

        }

    }
// Function glm::dot(x,y) will return the dot product of parameters. (It's the inner product of vectors)




/* TODO: Implement */
bool Plane::Intersect(const Ray &ray, IntersectInfo &info) const { 

float denom = glm::dot(planenormal,ray.direction);
if (denom==0)
    return false;
else
    {
      float t1 = glm::dot((planepoint-ray.origin),planenormal);
      float t2 = glm::dot(ray.direction,planenormal);
      float t  = t1/t2;
      //glm::vec3 s = planepoint-ray.origin;
      //float y=glm::dot(s,planenormal)/denom;
       if(t<=info.time){
         info.hitPoint=ray.origin+t*ray.direction;
         info.normal = planenormal;
         info.normal=(denom <0)? planenormal : -planenormal;
         info.time=glm::length(ray.origin-info.hitPoint);
         info.material= &material;
         return true;
       }
       else
        return false;
    }

/*if(denom>1e-6 ){
   glm::vec3 polo=planepoint-ray.origin;
   float t = glm::dot(polo,planenormal);
   return (t>=0);
  }



    return false; */
}

/* TODO: Implement */
bool Triangle::Intersect(const Ray &ray, IntersectInfo &info) const {

glm::vec3 edge1 = point2-point1;
glm::vec3 edge2 = point3-point1;
glm::vec3 edge3 = point3-point2; 

glm::vec3 trinormal = glm::normalize(glm::cross(edge1,edge2));
glm::vec3 pvec = glm::cross(ray.origin,edge2); 
float det = glm::dot(edge1,pvec); 
float invDet = 1 / det; 
float d = glm::dot(trinormal,point2);
 glm::vec3 tvec = ray.origin - point1; 
 glm::vec3 qvec = glm::cross(tvec,edge1); 

float t = glm::dot(edge2,qvec) * invDet; 
glm::vec3 P = ray.origin + t * ray.direction; 

float denom = glm::dot(trinormal,ray.direction);
if (denom==0)
  return false;
   else{

     // edge1

    glm::vec3 vp0 = P-point1; 
    glm::vec3 C = glm::cross(edge1,vp0); 
    if (glm::dot(trinormal,C) < 0) return false; // P is on the wrong side 
 
    // edge2
   
    glm:: vec3 vp1 = P - point2; 
    C = glm::cross(edge2,vp1); 
    if (glm::dot(trinormal,C) < 0)  return false; // P is on the wrong side 
 
    // edge3
    
    glm::vec3 vp2 = P - point3; 
    C = glm::cross(edge3,vp2); 
    if (glm::dot(trinormal,C) < 0)  return false; // P is on the wrong side; 
 


    info.hitPoint=P;
    info.normal=(denom <0)? trinormal: -trinormal;
    info.time=glm::length(ray.origin-info.hitPoint);
    info.material= &material;
    return true;






   }











 return true; }
