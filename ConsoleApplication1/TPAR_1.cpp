

#include <iostream>
#include <cstring>
#include <vector>
#include <iostream>
#include <aruco/aruco.h>
#include "aruco\aruco.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp>

using namespace cv;
using namespace aruco;
using namespace std;

int cameraID;

VideoCapture   cap;
cv::Mat myImage;
int main()
{
    printf("Welcome to arucoMinimal, using OpenCV version %s (%d.%d.%d)\n",
        CV_VERSION,
        CV_MAJOR_VERSION, CV_MINOR_VERSION, CV_SUBMINOR_VERSION);

    printf("Hot keys: \n"
        "\tESC - quit the program\n");
 
    // Creating the OpenCV capture
    cout << "Entrez l'identifiant de la camera" << endl;
    cin >> cameraID;
    cap.open(cameraID);
    if (!cap.isOpened()) {
        cerr << "Erreur lors de l'initialisation de la capture de la camera !" << endl;
        cerr << "Fermeture..." << endl;
        exit(EXIT_FAILURE);
    }

    MarkerDetector myDetector;

    while (true) {
        cap >> myImage;  
        if (myImage.empty()) {
            cerr << "Erreur lors de la capture de l'image !" << endl;
            break;
        }
    
	
        vector<aruco::Marker> markers = myDetector.detect(myImage);
        if (!markers.empty()) {
            for (auto& m : markers) {
                cout << m << endl;
                m.draw(myImage, Scalar(0, 0, 255), 1,2);  
            }
        }
        else {
            cout << "No markers detected." << endl;
        }

        imshow("Detected ArUco Markers", myImage);

        char key = (char)waitKey(1);
        if (key == 27) {
            break;  
        }
    }
}

