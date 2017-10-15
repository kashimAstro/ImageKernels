#include "ofMain.h"

#define NUM_FILTERS_KERNELS 11

class ImageKernels 
{
	public:
	ofImage img;
	vector<ofImage> filt;

  	double left_sobel_kernel[9]   = { 1,0,-1,2,0,-2,1,0,-1 };
	double right_sobel_kernel[9]  = {-1,0,1,-2,0,2,-1,0,1 };
	double top_sobel_kernel[9]    = { 1,2,1,0,0,0,-1,-2,-1 };
	double bottom_sobel_kernel[9] = {-1,-2,-1,0,0,0,1,2,1 };
	double identity_kernel[9]     = { -1,0.2,0,0,1,0,0.8,1,-1 };
	double custom_kernel[9]       = { 0.8,0,-1,0.2,1,0,0,1,0 };
	double outline_kernel[9]      = { -1,-1,-1,-1,8,-1,-1,-1,-1 };
	double emboss_kernel[9]       = { -2,-1,0,-1,1,1,0,1,2};
 	double sharpen_kernel[9]      = { -1,-1,-1,-1,9,-1,-1,-1,-1 };
	double sobel_emboss_kernel[9] = { -1,-2,-1,0,0,0,1,2,1 };
	double box_blur_kernel[9]     = {  1,1,1,1,1,1,1,1,1 };

 	double *filters[NUM_FILTERS_KERNELS+1] = {
		emboss_kernel, 
		sharpen_kernel, 
		sobel_emboss_kernel,
		box_blur_kernel, 
		outline_kernel,
		left_sobel_kernel,
		right_sobel_kernel,
		top_sobel_kernel,
		bottom_sobel_kernel, 
		identity_kernel, 
		custom_kernel
	};

	const double filter_params[2*(NUM_FILTERS_KERNELS+1)] = {
		1.0, 0.0,
		1.0, 0.0,
		1.0, 0.5,
		9.0, 0.0,
		0.8, 0.1,
		1.0, 0.9,
		0.9, 0.0,
		0.1, 1.0,
		1.0, 0.5,
		0.5, 0.5,
		1.0, 0.0,
		0.0, 1.0
	};

	void setup(int _w, int _h)
	{
 		img.allocate(_w,_h,OF_IMAGE_GRAYSCALE);
	}

	ofImage filter(ofImage im, double *K, int Ks, double divisor, double offset)
	{
		unsigned int ix, iy, l;
		int kx, ky;
		double cp[3];
    		for(ix=0; ix < im.getWidth(); ix++) {
			for(iy=0; iy < im.getHeight(); iy++) {
				cp[0] = cp[1] = cp[2] = 0.0;
				for(kx=-Ks; kx <= Ks; kx++) {
					for(ky=-Ks; ky <= Ks; ky++) {
						cp[0] += (K[(kx+Ks) + (ky+Ks)*(2*Ks+1)]/divisor) * ((double)im.getColor(ix+kx, iy+ky).r) + offset;
						cp[1] += (K[(kx+Ks) + (ky+Ks)*(2*Ks+1)]/divisor) * ((double)im.getColor(ix+kx, iy+ky).g) + offset;
						cp[2] += (K[(kx+Ks) + (ky+Ks)*(2*Ks+1)]/divisor) * ((double)im.getColor(ix+kx, iy+ky).b) + offset;
	  				}
				}
				for(l=0; l<3; l++)
					cp[l] = (cp[l]>255.0) ? 255.0 : ((cp[l]<0.0) ? 0.0 : cp[l]) ;
				img.setColor(ix, iy,ofColor(cp[0],cp[1],cp[2]));
      			}
    		}
		img.update();
		return img;
	}
};
