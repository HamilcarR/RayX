#ifndef RAYHIT_H
#define RAYHIT_H

#include "Structs.h"
#include "Material.h" 

class Material ; 
struct hit_record{
	double t; 
	glm::dvec3 position ; 
	glm::dvec3 normal ; 
	Material *material ; 


};




class Object {
public :
	virtual ~Object() = 0 ; 
	virtual bool hit(const Ray &ray , double t_min , double t_max ,hit_record &rec) const  = 0 ;  


};



class Object_list : public Object{

public :
	Object_list();
	~Object_list();
	Object_list(Object ** l , int n ); 
	virtual bool hit (const Ray &ray , double t_min , double t_max , hit_record &rec) const   ; 
		
	int size ; 
	Object ** list ; 



};

















#endif
