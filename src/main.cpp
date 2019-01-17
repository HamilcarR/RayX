#include <fstream>
#include <iostream>
#include <cstdlib>
#include <limits>
#include "../includes/Exporter.h" 
#include "../includes/Structs.h"
#include "../includes/RayHit.h" 
#include "../includes/Sphere.h" 
#include <cfloat>



#define row 1000
#define column 1000



using namespace std;
// change stack size with ulimit -s > 8 MB ? 
const int LIMIT = 5000 ; 



glm::dvec3 color(Ray ray , Object *world, int limit){
	hit_record rec ; 
	if(world->hit(ray , 0.1e-10 ,std::numeric_limits<double>::max() , rec) ){
		Ray scatter ; 
		glm::dvec3 attenuation ; 
		if(limit != 0 && rec.material->scatter(ray , rec , attenuation , scatter) ){
			return attenuation * color(scatter , world , limit-1) ; 

		}
		else
			return glm::dvec3(0, 0, 0) ; 
	}
	else{
		glm::dvec3 unit_direction = glm::normalize(ray.getDirection()) ; 
		double t = 0.5f*(unit_direction.y + 1.f) ; 
		return (1.f - t) * glm::dvec3(1.f , 1.f , 1.f) + t*glm::dvec3(0.2f , 0.7f , 1.f) ; 
		//return glm::dvec3 ( 0.f , 0.f , 0.f ) ; 
	}


}



int main(int argv , char** argc){



	glm::dvec3 llc(-2.f , -2.f , -2.f); 
	glm::dvec3 h(4.f , 0.f , 0.f) ; 
	glm::dvec3 v(0.f , 4.f , 0.f) ; 
	glm::dvec3 o(0.f , 0.2f , -0.1f) ; 


	Object *list[5]= {  new Sphere(glm::dvec3(0 , 0.3f , -1.2f) , 0.2f , new Metal(glm::dvec3(0.5 , 0.8 , 0.2) , 0.1)),
			     new Sphere(glm::dvec3(0 , 100.5f , -1) , 100.f , new Lambert(glm::dvec3(0.8 , 0.6 , 0.2))),
			     new Sphere(glm::dvec3(0.3f , 0.4f , -0.9f) , 0.1f , new Metal(glm::dvec3(0.1 , 0.1 , 0.1), 0.)),	
 			     new Sphere(glm::dvec3(-0.3f , 0.4f , -0.9f) , 0.1f , new Metal(glm::dvec3(0.9 , 0.5 , 0.5) , 0.7 )) , 
			     new Sphere(glm::dvec3(0.f , 0.4f , -0.8f) , 0.12f , new Dielectric(2.5)) 
	
	
	}; 
	Object *world = new Object_list(list , 5) ; 

	int AA = 30 ; 	


	RGB image[row*column] ; 
	for(int i = 0 ; i < row ; i++)
		for(int j = 0 ; j < column ; j++){
			glm::dvec3 col(0.f , 0.f , 0.f) ;  
			for(int s = 0 ; s < AA ; s++){
				double x = double(j +drand48()) / double (column) ; 
				double y = double(i +drand48()) / double (row) ; 
				Ray ray(o , llc+x*h+y*v);
				col += color(ray , world , LIMIT) ;
			}
				col /= double(AA) ; 
				RGB color ; 
				color.r = int(255 * sqrt(col.r)) ; 
				color.g = int(255 * sqrt(col.g)) ; 
				color.b = int(255 * sqrt(col.b)) ; 
			
			image[i*column+j] = color ;

		}
	save_image(row , column , image);
	delete world ; 
	return EXIT_SUCCESS ; 
}
