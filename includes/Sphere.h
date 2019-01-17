#ifndef SPHERE_H
#define SPHERE_H
#include "RayHit.h"
#include "Material.h"
class Sphere : public Object{

public:
	Sphere() ; 
	Sphere(glm::dvec3 center , double radius , Material* material) ; 
	~Sphere() ; 
	virtual bool hit(const Ray &ray , double t_min , double t_max , hit_record& rec) const ; 
	


private:

	glm::dvec3 center ; 
	double radius ; 
	Material* material; 

};










#endif 
