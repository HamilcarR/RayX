#include "../includes/Material.h" 
#include <iostream>
#include "../includes/RayHit.h" 


glm::dvec3 random_unit(){
	glm::dvec3 p(0. , 0. , 0.) ; 
	do {
		p = 2. * glm::dvec3 (drand48() , drand48() , drand48()) - glm::dvec3(1. , 1. , 1.) ; 	
	}
	while(glm::length(p)*glm::length(p) >= 1.) ; 
	return p ; 
	

}


Material::~Material(){



}



Lambert::~Lambert(){


}





Metal::~Metal(){


}

Dielectric::Dielectric(double f) {

	factor = f ; 

}

Dielectric::~Dielectric(){


}


bool Lambert::scatter(const Ray& ray , const hit_record &rec , glm::dvec3 &attenuation , Ray &scattered) const {
	glm::dvec3 target = rec.position + rec.normal + random_unit() ; 
	scattered = Ray(rec.position , target-rec.position) ; 
	attenuation = albedo ; 
	return true ; 
}

bool Metal::scatter(const Ray& ray , const hit_record &rec , glm::dvec3 &attenuation , Ray &scattered) const {
	glm::dvec3 reflected = glm::reflect(glm::normalize(ray.getDirection()) , rec.normal) ; 
	scattered = Ray(rec.position , reflected + fuzz*random_unit()); 
	attenuation = albedo ; 
	return (glm::dot(scattered.getDirection() , rec.normal) > 0 ) ; 

}



inline double schlick(double cosinus , double dx) {
	double R0 = (1-dx)/(1+dx); 
	R0*=R0 ; 
	return R0 + (1 - R0) * pow( ( 1 - cosinus) , 5) ; 


}


inline bool refract (glm::dvec3 incident , glm::dvec3 normal , double ref_idx , glm::dvec3 &refraction) {
	glm::dvec3 uv = glm::normalize(incident) ;
	double dt = glm::dot(uv , normal ) ; 
	double discr = 1. - ref_idx * ref_idx * (1 - dt*dt) ; 
	if(discr > 0) {
		refraction = ref_idx * ( uv - normal * dt ) - normal * sqrt(discr) ; 
		return true ; 

	}
	else
		return false;


}

glm::dvec3 reflect ( glm::dvec3& i , glm::dvec3& n ){
	return i - 2 * glm::dot(i , n )*n ; 

}

bool Dielectric::scatter(const Ray& ray , const hit_record &rec , glm::dvec3 &attenuation , Ray &scattered) const {
	glm::dvec3 out_normal ; 
	glm::dvec3 reflected = reflect (ray.getDirection() , rec.normal); 
	double ni_nt ; 
	attenuation = glm::dvec3(1.) ;
	glm::dvec3 refracted ;
	double reflect_prob ; 
	double cosine ; 
	if(glm::dot(ray.getDirection() , rec.normal) > 0) {
		out_normal = -rec.normal; 
		ni_nt = factor ; 
		cosine =  glm::dot(ray.getDirection(), rec.normal) /
			glm::length(ray.getDirection()) ; 
		cosine = sqrt(1 - factor * factor * (1 - cosine * cosine)) ; 
	}
	else{
		out_normal = rec.normal ; 
		ni_nt = 1./factor ; 
		cosine = -glm::dot(ray.getDirection() , rec.normal) /
			glm::length(ray.getDirection()); 

	}
	if(refract(ray.getDirection() , out_normal , ni_nt , refracted)){
		reflect_prob = schlick(cosine , ni_nt) ;

	}
	else{
		reflect_prob = 1.;

	}
	if(drand48() < reflect_prob){
		scattered = Ray(rec.position  , reflected) ;

	}
	else{
		scattered = Ray(rec.position   , refracted) ; 

	}
	return true ; 

}


/*
bool Dielectric::scatter(const Ray& ray , const hit_record &rec , glm::dvec3 &attenuation , Ray &scattered) const {
	
	glm::dvec3 out_normal ;
	glm::dvec3 reflected = reflect(glm::normalize(ray.getDirection()) , rec.normal) ; 
	attenuation = glm::dvec3 (1. , 1. , 0.) ; 
	double ni_nt ; 
	glm::dvec3 refracted (0.) ; 
	if(glm::dot(glm::normalize(ray.getDirection()), rec.normal) > 0 ) {
		out_normal = - rec.normal ; 
		ni_nt = factor ; 
	}
	else{
		out_normal = rec.normal ; 
		ni_nt = 1. / factor ; 
	}
	if(refract( glm::normalize(ray.getDirection()) , out_normal , ni_nt , refracted))
		scattered = Ray(rec.position , refracted) ; 
	else{
		scattered = Ray(rec.position , reflected) ; 
		return false ; 
	}


	
	return true ; 



}
*/


