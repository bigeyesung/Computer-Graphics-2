#include "RayTracer.h"
int windowX = 640;
int windowY = 480;
#include <iostream>
using namespace std;
float t_min=10000000.0f;
float tNear = -10000.0f; 
glm:: vec3 lightsource(-6.0f,4.0f,2.0f);

Object* closed_object;
/*
** std::vector is a data format similar with list in most of  script language, which allows users to change its size after claiming.
** The difference is that std::vector is based on array rather than list, so it is not so effective when you try to insert a new element, but faster while calling for values randomly or add elements by order.
*/
std::vector<Object*> objects;

void cleanup() {
	for(unsigned int i = 0; i < objects.size(); ++i){
		if(objects[i]){
			delete objects[i];
		}
	}
}

/*
** TODO: Function for testing intersection against all the objects in the scene
**
** If an object is hit then the IntersectionInfo object should contain
** the information about the intersection. Returns true if any object is hit, 
** false otherwise
** 
*/

bool CheckIntersection(const Ray &ray, IntersectInfo &info) {
	//return true;
    bool secondjudge = false;
    bool judge=false;
    for (int i=0;i<objects.size();++i)
     {
      if(objects[i] -> Intersect(ray, info) )  // circle intersect
       {    
     
            judge = true;
            if(info.time<t_min)
            t_min=info.time;
       }

       
     }

      for(int i=0;i<objects.size();++i){
        if(objects[i] -> Intersect(ray, info) && info.time==t_min){
            closed_object=objects[i];
            secondjudge = true;
        }
    }
     //if (secondjudge)
        //if(closed_object-> Intersect(ray, info)){
            //glm::vec3 m = glm::normalize(lightsource-info.hitPoint);
            //info.tem_color=info.tem_color+std::max(0.f, glm::dot(info.normal,m));
       //}

	//You need to add your own solution for this funtion, to replace the 'return true'.	
	//Runing the function Intersect() of each of the objects would be one of the options.
	//Each time when intersect happens, the payload of ray will need to be updated, but that's no business of this function.
	//To make it clear, keyword const prevents the function from changing parameter ray.


 return judge;
}







void light(const Ray &ray, IntersectInfo &info){




        //closed_object->material.ambient;
        /*glm::vec3 m = glm::normalize(lightsource-info.hitPoint);
        float cosTheta = glm::dot(m,info.normal);
        glm::vec3 vDiffuseColor = glm::vec3(0,cosTheta*kd*Ip,0);  //Idiff=Ip*kd*cosin
        float Idiff= sqrt(glm::dot(vDiffuseColor,vDiffuseColor));
        
        glm::vec3 v = glm::normalize(ray.origin-info.hitPoint);
        float coscoma = glm::dot(2.0f*info.normal*cosTheta-m,v);  
        float spec = glm::max(pow(coscoma, 10.0f),0.0f);           //Ispec= Ip*Ks*coscoma 10
        glm::vec3 lol = glm::vec3(0.0f, spec*Ip*ks, 0.0f);
        float Ispec = sqrt(glm::dot(lol,lol));


        float Iamb = 0.2f;                //Iamb
        totallight = glm::vec3(0.0f,0.0f,Idiff+Ispec+Iamb);*/




}


bool trace(const Ray &ray, IntersectInfo &info){
    
    for (int k=0; k<objects.size();k++){
 if (objects[k]->Intersect(ray,info) && tNear < t_min) { 
            
            t_min = tNear; 
            //isect.index = index; 
            //isect.uv = uv; 
            return true;
        } 
        else return false;

  }
}
/*
** TODO: Recursive ray-casting function. It might be the most important Function in this demo cause it's the one decides the color of pixels.
**
** This function is called for each pixel, and each time a ray is reflected/used 
** for shadow testing. The Payload object can be used to record information about
** the ray trace such as the current color and the number of bounces performed.
** This function should return either the time of intersection with an object
** or minus one to indicate no intersection.
*/
//	The function CastRay() will have to deal with light(), shadow() and reflection(). The impement of them would also be important.
float CastRay(Ray &ray, Payload &payload) {
//
    IntersectInfo info;
    
	if (CheckIntersection(ray,info)) {
		/* TODO: Set payload color based on object materials, not direction */  //payload=light particle
        //info.time=t_min;
        //light(ray,info);
        //glm::vec3 m = glm::normalize(lightsource-info.hitPoint);
        float kd = 0.8f;
        float Ip = 0.7f;
        float ks = 0.5f;
        glm::vec3 Iamb= info.material->ambient;
        glm::vec3 n = glm::normalize(info.normal);
        glm::vec3 m = glm::normalize(lightsource-info.hitPoint); ///L
        float cosTheta = glm::dot(m,n) ;///L.N
        glm::vec3 Idiff = glm::max(cosTheta,0.0f)* info.material->diffuse;
        glm::vec3 E = glm::normalize(glm::vec3(-10.0f, 10.0f, 10.0f) - info.hitPoint);
        
        glm::vec3 v = (ray.origin-info.hitPoint);
        float cosalpha = glm::dot(2.0f*n*cosTheta-m,E);  
        float spec = glm::max(pow(cosalpha, 10.0f),0.0f);           
        
        glm::vec3 Ispec= spec*info.material->specular;
    
        glm::vec3 normalized_ray = glm::normalize(ray.direction);
        glm::vec3 totallight = Iamb+Ispec+Idiff;
    
        if(trace(ray,info)){
            glm::vec3 hitpoint = ray.origin+ray.direction* tNear;
            glm ::vec3 hitNormal;
            bool vis = !trace(ray,info);
            
           totallight=totallight+ 0.18f *100;
        }



        payload.color=payload.color+totallight;

        //payload.numBounces = payload.numBounces+1;
		// In this case, it's just because we want to show something and we do not want to show the same color for every pixel.
		// Usually payload.color will be decided by the bounces.
		return info.time;
	}
	else{
		payload.color = glm::vec3(0.0f);
		// The Ray from camera hits nothing so nothing will be seen. In this case, the pixel should be totally black.
		return -1.0f;	
	}	
  //
}

// Render Function

// This is the main render function, it draws pixels onto the display
// using GL_POINTS. It is called every time an update is required.

// This function transforms each pixel into the space of the virtual
// scene and casts a ray from the camera in that direction using CastRay
// And for rendering,
// 1)Clear the screen so we can draw a new frame
// 2)Cast a ray into the scene for each pixel on the screen and use the returned color to render the pixel
// 3)Flush the pipeline so that the instructions we gave are performed.

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Clear OpenGL Window

	//	Three parameters of lookat(vec3 eye, vec3 center, vec3 up).	
	glm::mat4 viewMatrix = glm::lookAt(glm::vec3(-10.0f,10.0f,10.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
	glm::mat4 projMatrix = glm::perspective(45.0f, (float)windowX / (float)windowY, 1.0f, 10000.0f);

	glBegin(GL_POINTS);	//Using GL_POINTS mode. In this mode, every vertex specified is a point.
	//	Reference https://en.wikibooks.org/wiki/OpenGL_Programming/GLStart/Tut3 if interested.
  
	for(int x = 0; x < windowX; ++x)
		for(int y = 0; y < windowY; ++y){//Cover the entire display zone pixel by pixel, but without showing.
			float pixelX =  2*((x+0.5f)/windowX)-1;	//Actually, (pixelX, pixelY) are the relative position of the point(x, y).
			float pixelY = -2*((y+0.5f)/windowY)+1;	//The displayzone will be decribed as a 2.0f x 2.0f platform and coordinate origin is the center of the display zone.

			//	Decide the direction of each of the ray.
			glm::vec4 worldNear = glm::inverse(viewMatrix) * glm::inverse(projMatrix) * glm::vec4(pixelX, pixelY, -1, 1);
			glm::vec4 worldFar  = glm::inverse(viewMatrix) * glm::inverse(projMatrix) * glm::vec4(pixelX, pixelY,  1, 1);
			glm::vec3 worldNearPos = glm::vec3(worldNear.x, worldNear.y, worldNear.z) / worldNear.w;
			glm::vec3 worldFarPos  = glm::vec3(worldFar.x, worldFar.y, worldFar.z) / worldFar.w;

			Payload payload;
			Ray ray(worldNearPos, glm::normalize(glm::vec3(worldFarPos - worldNearPos))); //Ray(const glm::vec3 &origin, const glm::vec3 &direction)

			if(CastRay(ray,payload) > 0.0f){
				glColor3f(payload.color.x,payload.color.y,payload.color.z);
			} 
			else {
				glColor3f(0,0,0);
			}

			glVertex3f(pixelX,pixelY,0.0f);
		}
  
	glEnd();
	glFlush();
}

int main(int argc, char **argv) {

  	//initialise OpenGL
	glutInit(&argc, argv);
	//Define the window size with the size specifed at the top of this file
	glutInitWindowSize(windowX, windowY);

	//Create the window for drawing
	glutCreateWindow("RayTracer");
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);	
    glutDisplayFunc(Render);
	//Set the function demoDisplay (defined above) as the function that
	//is called when the window must display.
	

    //	TODO: Add Objects to scene
	//	This part is related to function CheckIntersection().
	//	Being added into scene means that the object will take part in the intersection checking, so try to make these two connected to each other.

    
    Plane* plane1 = new Plane(glm::vec3(0,0,1),glm::vec3(1,1,0));//////////////xy
    objects.push_back(plane1);
    objects[0]->material.ambient=glm::vec3(0.3f,0.3f,0.3f);
    objects[0]->material.diffuse=glm::vec3(0.0f,0.5f,0.6f);
    objects[0]->material.specular=glm::vec3(0.0f,0.5f,0.3f);
    objects[0]->material.glossiness= 2.0f;
    objects[0]->material.reflection= 0.5f;

    Plane* plane2 = new Plane(glm::vec3(0,1,0),glm::vec3(1,0,1));//////////////xy
    objects.push_back(plane2);
    objects[1]->material.ambient=glm::vec3(0.3f,0.3f,0.3f);
    objects[1]->material.diffuse=glm::vec3(0.0f,0.5f,0.6f);
    objects[1]->material.specular=glm::vec3(0.0f,0.5f,0.3f);
    objects[1]->material.glossiness= 2.0f;
    objects[1]->material.reflection= 0.5f;
   
    Plane* plane3 = new Plane(glm::vec3(1,0,0),glm::vec3(0,1,1));//////////////xy
    objects.push_back(plane3);
    objects[2]->material.ambient=glm::vec3(0.3f,0.3f,0.3f);
    objects[2]->material.diffuse=glm::vec3(0.0f,0.5f,0.6f);
    objects[2]->material.specular=glm::vec3(0.0f,0.5f,0.3f);
    objects[2]->material.glossiness= 2.0f;
    objects[2]->material.reflection= 0.5f;
   
    Sphere* sphere1 = new Sphere(glm::vec3(0.0,0.0,0.0),2.0);  //ballheart and radius
    objects.push_back(sphere1);
    objects[3]->material.ambient =glm::vec3(1.0f,0.0f,0.0f);
    objects[3]->material.diffuse =glm::vec3(0.0f,0.0f,0.0f);
    objects[3]->material.specular=glm::vec3(1.0f,1.0f,1.0f);
    objects[3]->material.glossiness =2.0f;
    objects[3]->material.reflection =3.0f;


    Triangle* triangle1 = new Triangle(glm::vec3(-1.0f,3.0f,9.0f),glm::vec3(-1.0f,0.0f,9.0f),glm::vec3(-1.0f,0.0f,6.0f));  //ballheart and radius
    objects.push_back(triangle1);
    objects[4]->material.ambient =glm::vec3(1.0f,0.0f,0.0f);
    objects[4]->material.diffuse =glm::vec3(0.0f,0.0f,0.0f);
    objects[4]->material.specular=glm::vec3(1.0f,1.0f,1.0f);
    objects[4]->material.glossiness =2.0f;
    objects[4]->material.reflection =3.0f;

	atexit(cleanup);
	glutMainLoop();
}
