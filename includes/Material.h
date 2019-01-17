#ifndef MATERIAL_H
#define MATERIAL_H
#include "RayHit.h"

struct hit_record ; 
class Material{

public:
	virtual ~Material() = 0 ; 
	virtual bool scatter(const Ray& ray , const hit_record &rec , glm::dvec3 &attenuation , Ray &scattered) const = 0; 


};





class Lambert:public Material {


public:
	Lambert(glm::dvec3 a) {albedo = a ; }
	virtual ~Lambert() ; 
	virtual bool scatter(const Ray& ray , const hit_record &rec , glm::dvec3 &attenuation , Ray &scattered) const; 



private : 
	glm::dvec3 albedo ;








};





class Metal : public Material {


public:
	Metal(glm::dvec3 a , double f) {albedo = a ; fuzz =(fuzz < 1) ?  f : 1. ;  }
	virtual ~Metal() ;
	virtual bool scatter(const Ray& ray , const hit_record &rec , glm::dvec3 &attenuation , Ray &scattered) const; 


private:
	glm::dvec3 albedo ; 
	double fuzz ; 

};






class Dielectric : public Material {

public:
	Dielectric(double f) ; 
	virtual ~Dielectric(); 
	virtual bool scatter(const Ray& ray , const hit_record &rec , glm::dvec3 &attenuation , Ray &scattered) const; 

private:
	double factor ; 

};















#endif 
