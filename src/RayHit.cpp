#include "../includes/RayHit.h"
#include <iostream>






Object::~Object(){



}




Object_list::Object_list(){



}

Object_list::Object_list(Object** l , int n ){
	list = new Object*[n] ;
	size = n ; 
	for(int i = 0 ; i < size ; i++)
		list[i] = l[i] ; 

}

Object_list::~Object_list(){

	for(int i = 0 ; i < size ; i++){
		delete list[i];
	}
	delete list ; 
}





bool Object_list::hit(const Ray &ray , double t_min , double t_max , hit_record& rec) const {
	hit_record temp_rec  ; 
	bool hit_anything = false; 
	double closest = t_max ; 
	for(int i = 0 ; i < size ; i++){
		
		if(list[i]->hit(ray , t_min , closest , temp_rec)){

			hit_anything = true; 
			closest = temp_rec.t ; 
			rec = temp_rec ; 
		}
	}
	return hit_anything ; 
	



}
