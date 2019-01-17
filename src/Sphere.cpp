#include "../includes/Sphere.h"
#include <iostream>
#include <assert.h>

Sphere::Sphere(){


}



Sphere::Sphere(glm::dvec3 c , double r , Material* M) {
	material = M ; 
	center = c ; 
	radius = r ; 

}


Sphere::~Sphere(){
	delete material ; 

}


bool Sphere::hit(const Ray &ray , double t_min , double t_max , hit_record& rec) const{
	glm::dvec3 oc  = ray.getOrigin() - center ; 
	double a = glm::dot( ray.getDirection() , ray.getDirection()); 
	double b = glm::dot (oc , ray.getDirection()); 
	double c = glm::dot(oc , oc ) - radius*radius ; 
	double discriminant = b*b - a*c;
	assert(a != 0) ; 	
	if (discriminant > 0) {
		double temp = (-b-sqrt(discriminant))/a;
		if(temp< t_max && temp > t_min){
			rec.t = temp ; 
			rec.position = ray.getPointPosition(temp) ;
			rec.normal = (rec.position-center)/radius ;
			rec.material = material; 
			return true ; 

		}
		temp = (-b + sqrt(discriminant)) / a ; 
		if(temp < t_max && temp > t_min){
			rec.t = temp ; 
			rec.position = ray.getPointPosition(temp) ;
			rec.normal = (rec.position-center)/radius ; 
			rec.material = material ; 
			return true ; 


		}
	
	}
	
	return false;

}
