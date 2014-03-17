/*
* etch.c 
* filter that creates a Black and Whte version of the original
* saves modified image as etched.jpg
*/
#include "hw4.h"


int main(int argc, char ** argv) {
	int numberOfSubImages, // the number of subImages created
			numColumns, // the number of horizontal images in the result
			numRows, // the number of vertical images in the result
			i; // just an iterator
	IplImage *src, // the source image
			 *final; //the modified image created from source
	IplImage **subImages; // subimages created from main image
	CvScalar *scolors; // the average color of the sub images of the source image
	CvSize srcSize, subImgSize;
	CvScalar white, black, offwhite;
	for(i = 0; i < 3; i++)
	{
		white.val[i] = 255;
		black.val[i] = 0;
		offwhite.val[i] = 230;
	}

	// Load the source image
	src = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR);
	// get the number of rows and columns
	srcSize = cvGetSize(src);
	numColumns = srcSize.width / 2;
	numRows = srcSize.height / 2;
	numberOfSubImages = numColumns * numRows;

	printf("Computing sub images\n");
	// create the sub images
	subImages = getSubImages(src, numColumns, numRows);

	// compute the average colors of the sub images
	printf("Computing sub image colors\n");
	scolors = getAvgColors(subImages, numColumns * numRows);

	printf("Making blocks\n");
#pragma omp parallel for
	for (i = 0; i < numberOfSubImages; i++) {
		if((scolors[i].val[0] > 150) && (scolors[i].val[1] > 150) && (scolors[i].val[2] > 150))
		{
			cvSet(subImages[i], white, NULL);
		}else if((scolors[i].val[0] > 120) && (scolors[i].val[1] > 120) && (scolors[i].val[2] > 120))
		{
			cvSet(subImages[i], offwhite, NULL);
		}else
		{
			cvSet(subImages[i], black, NULL);
		}
	}
	printf("Blocks constructed\n");
	// stitch the result
	final = stitchImages(subImages, numColumns, numRows);
	printf( "Images stitched\n");

	printf("saving modified image to etched.jpg\n");
	cvSaveImage("etched.jpg", final, NULL );

	return EXIT_SUCCESS;
}