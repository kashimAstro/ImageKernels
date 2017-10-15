#include "ofMain.h"
#include "ImageKernels.h"

class ofApp : public ofBaseApp
{
	public:
	ofImage img;
        ofVideoGrabber video;
	ImageKernels kernel;
	int smat;

	void setup()
	{
		ofSetVerticalSync(false);
		smat = 60;
		int width = 320;
		int height = 240;
    		video.setDeviceID(0);
		video.setDesiredFrameRate(60);
		video.initGrabber(width, height);
		kernel.setup(smat,smat);
	}

	void update()
	{
		ofSetWindowTitle(ofToString(ofGetFrameRate()));

		video.update();
		if(video.isFrameNew())
		{
			img = video.getPixels();
			img.setImageType(OF_IMAGE_GRAYSCALE);
			img.resize(smat,smat);
		}
	}

	void draw()
	{
		for(int i = 0; i < NUM_FILTERS_KERNELS; i++) {
			ofImage im = kernel.filter(img, kernel.filters[i], 1, kernel.filter_params[2*i], kernel.filter_params[2*i+1]);
			im.draw(120*i,0,120,120);
		}
	}
};

int main()
{
	ofSetupOpenGL(1024,120, OF_WINDOW);
	ofRunApp( new ofApp());
}
