#ifndef STRUCTS_H
#define STRUCTS_H
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

struct RGB{
	unsigned char r ; 
	unsigned char g ; 
	unsigned char b ; 


};






class Ray{
public:
	Ray() { origin = glm::dvec3(0 , 0 , 0) ; direction = glm::dvec3(0 , 0 , 0 ) ; } 
	Ray(glm::dvec3 o , glm::dvec3 d) { origin = o ; direction = d ; } 
	virtual ~Ray(){} ; 
	glm::dvec3 getOrigin()const {return origin ; } 
	glm::dvec3 getDirection()const {return direction ; }
	void setOrigin(glm::dvec3 o){origin = o; }
	void setDirection(glm::dvec3 d){direction = d ; }
	glm::dvec3 getPointPosition(double t)const {return origin+direction*t ; }




private:
	glm::dvec3 origin ; 
	glm::dvec3 direction ; 



};

#endif
