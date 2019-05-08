/*#include "pch.h"
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int, char**)
{
	VideoCapture cap(0); // open the default camera
	if (!cap.isOpened())  // check if we succeeded
		return -1;

	Mat edges;
	namedWindow("edges", 1);
	for (;;)
	{
		Mat frame;
		cap >> frame; // get a new frame from camera
		cvtColor(frame, edges, COLOR_BGR2GRAY);
		GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
		Canny(edges, edges, 0, 30, 3);
		imshow("edges", edges);
		if (waitKey(30) >= 0) break;
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}
*/


#include "pch.h"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

int main()
{
	VideoCapture capture(0);
	if (!capture.isOpened())
		throw "Error when reading file";
	namedWindow("window", 1);
	for (;;)
	{
		Mat image;
		capture >> image;
		if (image.empty())
			break;

		// Load Face cascade (.xml file)
		CascadeClassifier face_cascade;
		face_cascade.load("C:/Users/dadded1/Pictures/machinelearning/carDetection.xml");
		if (!face_cascade.load("C:/Users/dadded1/Pictures/machinelearning/carDetection.xml"))
		{
			cerr << "Error Loading XML file" << endl;
			return 0;
		}

		// Detect faces
		std::vector<Rect> faces;
		face_cascade.detectMultiScale(image, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

		// Draw circles on the detected faces
		for (int i = 0; i < faces.size(); i++)
		{
			Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
			ellipse(image, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
		}

		imshow("Detected Face", image);
		if (waitKey(30) >= 0) break;
	}

	return 0;
}