#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <windows.h>
#include <sys/stat.h>
#include <string>
#include <mysql.h>

using namespace cv;
using namespace std;


int main()
{
	int qstate;


	char imgPath[] = "C:/Users/samti/source/repos/FaceRecognition/FaceRecognition/x64/Debug/1.jpeg";
	ifstream fileImg(imgPath, ios::binary);
	fileImg.seekg(0, std::ios::end);
	int bufferLength = fileImg.tellg();
	fileImg.seekg(0, std::ios::beg);

	if (fileImg.fail())
	{
		cout << "Failed to read image" << endl;
		cin.get();
		return -1;
	}

	//Read image data into char array
	char* buffer = new char[bufferLength];
	fileImg.read(buffer, bufferLength);
	cout << buffer;

	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* result;
	setlocale(LC_ALL, "ru");
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "assasin007", "hightemperaturefaces", 3306, NULL, 0);

	




	double scale = 3.0;
	CascadeClassifier faceCascade;
	faceCascade.load("C:\\Users\\samti\\source\\repos\\FaceRecognition/FaceRecognition/haarcascade/haarcascade_frontalface_default.xml");

	VideoCapture cap(0);

	int temperature = 40;
	Scalar goodTemperature = *new Scalar(0, 255, 0);
	Scalar tempColor = goodTemperature;
	Scalar InterTemperature = *new Scalar(0, 153, 255);
	Scalar BadTemperature = *new Scalar(0, 0, 255);

	//char imgPath[] = "C:/Users/samti/source/repos/FaceRecognition/FaceRecognition/1.jpeg";
	//ifstream fileImg(imgPath, ios::binary);

	//std::ifstream file("1.jpeg");
	std::vector<char> data;

	fileImg >> std::noskipws;
	std::copy(std::istream_iterator<char>(fileImg), std::istream_iterator<char>(), std::back_inserter(data));

	//Mat matrixJprg = imdecode(Mat(data), 1);

	//namedWindow("Image from Char Array", WINDOW_AUTOSIZE);
	//if (!(matrixJprg.empty()))
	//{
	//	
	//	imshow("Image from Char Array", matrixJprg);
	//}

	while (true)
	{
		// //Импровизированный датчик температуры
		//while (true)
		//{
		//	temperature = 35 + rand() % 6;
		//	break;
		//}

		//if (temperature <= 36)
		//{
		//	tempColor = goodTemperature;
		//}
		//else if (temperature > 36 && temperature < 38)
		//{

		//	tempColor = InterTemperature;
		//}
		//else if (temperature > 38)
		//{
		//	tempColor = BadTemperature;
		//}


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
			putText(img, to_string(temperature), Point(cvRound(area.x * scale), cvRound(area.y * scale)), FONT_HERSHEY_SIMPLEX, 0.75, tempColor, 2);
		}

		cap.read(grayscale);
		imshow("Temperature", img);
		waitKey(1);

		if (temperature >= 36)
		{

			if (!conn)
			{
				// Если нет возможности установить соединение с сервером
				// базы данных выводим сообщение об ошибке
				fprintf(stderr, "Error: can't connect to database %s\n", mysql_error(conn));
			}
			else
			{
				// Если соединение успешно установлено выводим фразу - "Success!"
				fprintf(stdout, "Success!\n");
			}

			char querry[50] = "insert into face (facetemp) values (40)";
			//string insertQuerry = "insert into person (first_name) values ('TESTTEST2')";
			//const char* q = insertQuerry.c_str();
			qstate = mysql_query(conn, querry);

			if (!qstate)
			{
				cout << endl << "Row affected";
			}

			else
			{
				cout << "GG";
			}







			imwrite("1.jpeg", img);
		}
	}
	return 0;
}





/*


 Если t > то скрин и заливает в бд

		if (temperature >= 36)
		{
		}

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

