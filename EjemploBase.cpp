
#include <iostream>
#include <cstdlib>
#include <opencv2/core/core.hpp> // Contiene las definiciones base de matrices y estructuras
#include <opencv2/highgui/highgui.hpp> // Interfaz gráfica de usuario
#include <opencv2/imgproc/imgproc.hpp> // Procesamiento de imágenes
#include <opencv2/imgcodecs/imgcodecs.hpp> // Códecs para leer los distintos formatos de imágenes (JPG, PNG, etc.)

using namespace std;
using namespace cv;

int main(int argc, char *argv[]){

    Mat imagen = imread("SIMON_BOLIVAR_ORIGINAL.png");
    Mat imagen2 = imread("SIMON_BOLIVAR.png");
    Mat resta;
    Mat original = imagen.clone();

    namedWindow("Imagen", WINDOW_AUTOSIZE);
    imshow("Imagen", imagen);

    namedWindow("Imagen 2", WINDOW_AUTOSIZE);
    imshow("Imagen 2", imagen2);
    
    cvtColor(imagen, imagen, COLOR_BGR2GRAY);
    cvtColor(imagen2, imagen2, COLOR_BGR2GRAY);

    absdiff(imagen, imagen2, resta);

    for (int i = 0; i < resta.rows; i++){
        for (int j = 0; j < resta.cols; j++){
            int pixel = resta.at<uchar>(i,j);
            if(pixel > 0){
                int max = 0;
                for(int x=j; x < resta.cols; x++){
                    if(resta.at<uchar>(i,x) > 0){
                        max = x;
                    }
                }
                for(int z=j; z < max; z++){
                    resta.at<uchar>(i,z) = 255;
                    Vec3b pixel_ = original.at<Vec3b>(i,z);
                    Vec3b pixelNegativo = Vec3b(255-pixel_[0], 255-pixel_[1], 255-pixel_[2]);
                    original.at<Vec3b>(i,z) = pixelNegativo;
                }
            }

        }

    }
    namedWindow("Resultado", WINDOW_AUTOSIZE);
    imshow("Resultado", original);
    
    waitKey();
    destroyAllWindows();
}

