/*
 * sharpen.c
 * Takes in image as command line argument and outputs a
 * filter version of it as sharpened.jpg
 * the filter sharpens the image - works great with images of fruits
 *  
 */

#include "hw4.h"


int main(int argc, char ** argv) {

	IplImage *src;
	IplImage *final;
	CvMat *kern;
	printf("loading image %s.\n", argv[1]);
	src = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR);
	printf("allocating final image.\n");
	final = cvCreateImage(cvGetSize(src), src->depth, 3);
	printf("creating mask kernel matrix.\n");
	kern = cvCreateMat(3, 3, CV_32F);
	cvSet(kern, cvScalarAll(0), NULL);
	printf("initializng mask kernel matrix.\n");
	cvSet2D(kern, 0, 0, cvRealScalar(0));
	cvSet2D(kern, 0, 1, cvRealScalar(-1));
	cvSet2D(kern, 0, 2, cvRealScalar(0));
	cvSet2D(kern, 1, 0, cvRealScalar(-1));
	cvSet2D(kern, 1, 1, cvRealScalar(5));
	cvSet2D(kern, 1, 2, cvRealScalar(-1));
	cvSet2D(kern, 2, 0, cvRealScalar(0));
	cvSet2D(kern, 2, 1, cvRealScalar(-1));
	cvSet2D(kern, 2, 2, cvRealScalar(0));
	
	printf("Applying mask to source image.\n");
	cvFilter2D(src, final, kern, cvPoint(-1,-1));
	printf("saving filtered image to sharpened.jpg.\n");
	cvSaveImage("sharpened.jpg", final, NULL );

	return EXIT_SUCCESS;
}
