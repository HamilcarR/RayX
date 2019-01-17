#include "../includes/Exporter.h"

using namespace std;
void save_image(int width , int height ,  RGB* image){


ofstream img ("img.ppm") ; 
	img << "P3" << endl; 
	img << width << " " << height << endl; 
	img << 255 << endl; 
	
	for (int i = 0 ; i < width ; i++){
		for (int j = 0 ; j < height ; j++){
			RGB color =  image[i*height + j] ; 
			int r = color.r;  
			int g =	color.g ; 
			int b = color.b ; 

			img << r << " " << g << " " << b << endl; 

		}
	
	}

}
