#include <iostream>
#include <vector>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
using namespace cv;
using namespace std;


int main()
{
	double scale = 3.0;
	CascadeClassifier faceCascade;
	faceCascade.load("C:\\Users\\samti\\source\\repos\\FaceRecognition/FaceRecognition/haarcascade/haarcascade_frontalface_default.xml");

	int temperature = 36;
	VideoCapture cap(0);


	while (true)
	{
		
		Mat img;
		cap >> img;
		Mat grayscale;
		cvtColor(img, grayscale, COLOR_BGR2GRAY);
		resize(grayscale, grayscale, Size(grayscale.size().width / scale, grayscale.size().height / scale));

		vector<Rect> faces;
		faceCascade.detectMultiScale(grayscale, faces, 1.1, 3, 0, Size(30, 30));

		for (Rect area : faces)
		{
			Scalar drawColor = Scalar(255, 0, 0);
			rectangle(img, Point(cvRound(area.x * scale), cvRound(area.y * scale)),
				Point(cvRound((area.x + area.width - 1) * scale), cvRound((area.y + area.height - 1) * scale)), drawColor);
		}


		cap.read(grayscale);
		imshow("Temperature", img);
		waitKey(1);

		// Если t > то скрин и заливает в бд
		if (temperature >= 36)
		{
			imwrite("1.jpeg", img);
		}
	}
	

	return 0;
}










/*




	int counter = 0;
	for (int i = 0; i <= 10; i++)
	{
		++counter;
		Sleep(2000);
	}
	string jpeg_name = to_string(counter) + ".jpeg";


		for (int i = 0; i <= 10; i++)
	{
		++counter;
	}
	string jpeg_name = to_string(counter) + ".jpeg";






	******************************************************

	// Рабочий!!! вариант
	
		double scale = 3.0;
	CascadeClassifier faceCascade;
	faceCascade.load("C:\\Users\\samti\\source\\repos\\FaceRecognition/FaceRecognition/haarcascade/haarcascade_frontalface_default.xml");

	int temperature = 36;
	VideoCapture cap(0);


	while (true)
	{
		
		Mat img;
		cap >> img;
		Mat grayscale;
		cvtColor(img, grayscale, COLOR_BGR2GRAY);
		resize(grayscale, grayscale, Size(grayscale.size().width / scale, grayscale.size().height / scale));

		vector<Rect> faces;
		faceCascade.detectMultiScale(grayscale, faces, 1.1, 3, 0, Size(30, 30));

		for (Rect area : faces)
		{
			Scalar drawColor = Scalar(255, 0, 0);
			rectangle(img, Point(cvRound(area.x * scale), cvRound(area.y * scale)),
				Point(cvRound((area.x + area.width - 1) * scale), cvRound((area.y + area.height - 1) * scale)), drawColor);
		}



		cap.read(grayscale);
		imshow("Temperature", img);
		waitKey(1);
		if (temperature >= 36)
		{
			//Delay   //  25   -> "25"
			imwrite("1.jpeg", img);
		}
	}
	

	return 0;
	
	
	
	
	//


		******************************************************




	int main()
{
	// Load Face cascade (.xml file)
	CascadeClassifier face_cascade;
	face_cascade.load("haarcascade_frontalface_alt2.xml");

	Mat img;
	VideoCapture cap(0);
	while (true)
	{
		cap >> img;

		//cvtColor(img, img, CV_BGR2GRAY);

		// Detect faces
		std::vector<Rect> faces;
		face_cascade.detectMultiScale(img, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));


		// Draw circles on the detected faces
		for (int i = 0; i < faces.size(); i++)
		{
			Point center(faces[i].x + faces[i].width * 0.5, faces[i].y + faces[i].height * 0.5);
			ellipse(img, center, Size(faces[i].width * 0.5, faces[i].height * 0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
		}

		imshow("Detected Face", img);
		waitKey(1);
	}
	return 0;
}
*/

