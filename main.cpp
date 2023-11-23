#include <iostream>
#include "opencv2/opencv.hpp"
#include <string.h>
#include "db.h"
//#include "mysql-connector-cpp/jdbc/cppconn/connection.h"
//#include "mysql_connection.h"
//#include "mysql.h"

//#include "mysql-connector-cpp/jdbc/cppconn/statement.h"
//#include "mysql-connector-cpp/jdbc/cppconn/prepared_statement.h"
//#include "mysql-connector-cpp/jdbc/cppconn/resultset.h"
//#include "mysql-connector-cpp/jdbc/cppconn/driver.h"

#include "cppconn/driver.h"
#include "cppconn/connection.h"
#include "cppconn/statement.h"
#include "cppconn/prepared_statement.h"
#include "cppconn/resultset.h"

using namespace dbPixels;
/*
    std::string a = "";

    std::cin >> a;

    cv:: Mat image;
    cv::imread(a);
    // Read image
    cv::Mat im = cv::imread("image.jpg");

    // Select ROI
    cv::Rect2d r = selectROI("image", im, false, false, true);

    // Crop image
    cv::Mat imCrop = im(r);

    // Display Cropped Image
    imshow("Image", imCrop);
    cv::waitKey(0);

    return 0;
*/
/*
    string str = "1, 106, 107, 106, 106, 107, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 107, 107, 106, 108, 102,  93,  82, 183, 200, 198, 196, 197, 197, 197, 196, 196, 195, 195, 195, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 195, 197, 198, 198, 197, 195, 195, 195, 195, 196, 198, 198, 197, 196, 197, 198, 197, 197, 194, 195,  98,  73, 104, 110, 109, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 107, 107, 108, 108, 109, 106, 106, 106, 0";

    string number = "";

    int array[1000]{};
    int i = 0;
    for (char c : str) {
        if (c == ',') {
            if (c == ' ') continue;
            array[i] = stoi(number);
            ++i;
            number.clear();
            continue;
        }
        number += c;
    }

    cout << ++i;

    return 0;
*/

/*
int SizeImage() {
    string number = "";

    int array[1000]{};
    int i = 0;
    for (char c : str) {
        if (c == ',') {
            if (c == ' ') continue;
            array[i] = stoi(number);
            ++i;
            number.clear();
            continue;
        }
        number += c;
    }

    cout << ++i;

    return 0;
}
*/

/*
    cv::namedWindow("original", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("example", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("example1", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("example2", cv::WINDOW_AUTOSIZE);

    std::vector<cv::Mat> mrgs(3);

    cv::Mat imgSim = cv::imread("imgSim.jpg");

    std::vector<cv::Mat> chanell;

    cv::split(imgSim, chanell);

    cv::Mat one(chanell[0].size(), CV_8UC1, cv::Scalar(0));




    cv::Mat imgR = cv::Mat(imgSim.size(), CV_8UC3);
    mrgs[0] = chanell[0];
    mrgs[1] = one;
    mrgs[2] = one;
    cv::merge(mrgs, imgR);
    cv::imshow("example", imgR);


    cv::Mat imgG = cv::Mat(imgSim.size(), CV_8UC3);
    mrgs[0] = one;
    mrgs[1] = chanell[1];
    mrgs[2] = one;
    cv::merge(mrgs, imgG);
    cv::imshow("example1", imgG);

    cv::Mat imgB = cv::Mat(imgSim.size(), CV_8UC3);
    mrgs[0] = one;
    mrgs[1] = one;
    mrgs[2] = chanell[2];
    cv::merge(mrgs, imgB);
    cv::imshow("example2", imgB);

    cv::imshow("original", imgSim);

    cv::waitKey(0);

    std::cout << chanell.size();

    return 0;
*/

//вспомогательные переменные пикселей
int rmin = 0;
int rmax = 255;

int gmin = 0;
int gmax = 255;

int bmin = 0;
int bmax = 255;

int rgbMax = 255;

//Изображение в котором хотим найти обьект
cv::Mat image = cv::imread("wheel.jpg"); //"C:/Users/patem/source/repos/Project2/Project2/"

//массивы в которых мы храним каналы rgb изображения по отдельности
cv::Mat r_plane(image.size(), CV_8UC1);
cv::Mat g_plane(image.size(), CV_8UC1);
cv::Mat b_plane(image.size(), CV_8UC1);

//каналы которые мы будем менять
cv::Mat r_range(image.size(), CV_8UC1);
cv::Mat g_range(image.size(), CV_8UC1);
cv::Mat b_range(image.size(), CV_8UC1);

//сумарная картинка которая у нас получиться
cv::Mat rgb(image.size(), CV_8UC3);

//для R
void myTrackbarRmin(int pos, void*) {
    rmin = pos;
    cv::inRange(r_plane, cv::Scalar(rmin), cv::Scalar(rmax), r_range);
}
void myTrackbarRmax(int pos, void*) {
    rmax = pos;
    cv::inRange(r_plane, cv::Scalar(rmin), cv::Scalar(rmax), r_range);
}

//для G
void myTrackbarGmin(int pos, void*) {
    gmin = pos;
    cv::inRange(g_plane, cv::Scalar(gmin), cv::Scalar(gmax), g_range);
}
void myTrackbarGmax(int pos, void*) {
    gmin = pos;
    cv::inRange(g_plane, cv::Scalar(gmin), cv::Scalar(gmax), g_range);
}

//для B
void myTrackbarBmin(int pos, void*) {
    bmin = pos;
    cv::inRange(b_plane, cv::Scalar(bmin), cv::Scalar(bmax), b_range);
}
void myTrackbarBmax(int pos, void*) {
    bmin = pos;
    cv::inRange(b_plane, cv::Scalar(bmin), cv::Scalar(bmax), b_range);
}

int main() {

    //Создаем соединение с базой данных
    db dateBase = dbPixels::db();

    sql::Connection* conn = dateBase.get_connection();
    sql::Statement* stmt = dateBase.get_statement();
    sql::PreparedStatement* pstmt = dateBase.get_preparementStatement();
    //разбиваем картинки по каналам
    std::vector<cv::Mat> channel(3);
    cv::split(image, channel);
    r_plane = channel[2];
    b_plane = channel[0];
    g_plane = channel[1];
    double frame_min = 0;
    double frame_max = 0;

    cv::minMaxLoc(r_plane, &frame_min, &frame_max);
    rmin = frame_min;
    rmax = frame_max;

    cv::minMaxLoc(g_plane, &frame_min, &frame_max);
    gmin = frame_min;
    rmax = frame_max;

    cv::minMaxLoc(b_plane, &frame_min, &frame_max);
    bmin = frame_min;
    bmax = frame_max;

    cv::namedWindow("original", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("R", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("G", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("B", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("R range", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("G range", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("B range", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("rgb and", cv::WINDOW_AUTOSIZE);

    cv::createTrackbar("Rmin", "R range", &rmin, rgbMax, myTrackbarRmin);
    cv::createTrackbar("Rmax", "R range", &rmax, rgbMax, myTrackbarRmax);
    cv::createTrackbar("Gmin", "G range", &gmin, rgbMax, myTrackbarGmin);
    cv::createTrackbar("Gmax", "G range", &gmax, rgbMax, myTrackbarGmax);
    cv::createTrackbar("Bmin", "B range", &bmin, rgbMax, myTrackbarBmin);
    cv::createTrackbar("Bmax", "B range", &bmax, rgbMax, myTrackbarBmax);


    while (true) {
        // показываем картинку
        cv::imshow("original", image);

        // показываем слои
        cv::imshow("R", r_plane);
        cv::imshow("G", g_plane);
        cv::imshow("B", b_plane);

        // показываем результат порогового преобразования
        cv::imshow("R range", r_range);
        cv::imshow("G range", g_range);
        cv::imshow("B range", b_range);

        // складываем
        std::vector<cv::Mat> result_vector(3);
        result_vector[2] = r_range;
        result_vector[1] = g_range;
        result_vector[0] = b_range;
        cv::merge(result_vector, rgb);

        // показываем результат
        cv::imshow("rgb and", rgb);
        char c = cv::waitKey(33);
        if (c == 27) { // если нажата ESC - выходим
            break;
        }
    }
    std::cout<<"Results: " << std::endl;
    std::cout << "RED Min: " << rmin << " RED Max: " << rmax << std::endl;
    std::cout << "GREEN Min: " << gmin << " GREEN Max: " << gmax << std::endl;
    std::cout << "BLUE Min: " << bmin << " BLUE Max: " << bmax << std::endl;

    int result_size_cout = 0;

    //находим количество подходящих пикселей
    for (int i = 0; i < rgb.rows; ++i) {
        for (int j = 0; j < rgb.cols; ++j) {
            if (rgb.at<cv::Vec3b>(i, j) == cv::Vec3b(255, 255, 255))++result_size_cout;//cv::Vec3i{255, 255, 255})
        }
    }

    std::cout << result_size_cout << std::endl;

    //массив для хранения только разных подходящих пикселей
    cv::Vec2i *arr_not_repeat_vec = new cv::Vec2i[result_size_cout];
    bool arr_bool_I[100000]{};
    bool arr_bool_J[100000]{};
    int i_arr = 0;

    //находим координаты подъодящих пикселей
    for (int i = 0; i < rgb.rows; ++i) {
        for (int j = 0; j < rgb.cols; ++j) {
            if (rgb.at<cv::Vec3b>(i, j) == cv::Vec3b(255, 255, 255)) {
                if(arr_bool_I[i] == false || arr_bool_J[j] == false){
                    arr_not_repeat_vec[i_arr] = cv::Vec2i(i, j);
                    arr_bool_I[i] = true;
                    arr_bool_J[j] = true;
                    i_arr++;
                }
            }
        }
    }

    cv::Vec3b *array_suitable_pixels = new cv::Vec3b[i_arr];


    for (int i = 0; i < i_arr; i++) {
        array_suitable_pixels[i] = image.at<cv::Vec3b>(arr_not_repeat_vec[i][0],
                                                       arr_not_repeat_vec[i][1]);
        int r = array_suitable_pixels[i][0];
        int g = array_suitable_pixels[i][1];
        int b = array_suitable_pixels[i][2];
        pstmt = conn->prepareStatement("INSERT INTO pixels.rbg (r, g, b) VALUES ( ?, ?, ?)");
        pstmt->setInt(1, r);
        pstmt->setInt(2, g);
        pstmt->setInt(3, b);
        pstmt->execute();
        std::cout << arr_not_repeat_vec[i] << " : " << image.at<cv::Vec3b>(arr_not_repeat_vec[i][0],
                                                                           arr_not_repeat_vec[i][1]) << std::endl;
    }

    //std::string name_photo_object = "photo";
    std::string extention_photo_object = ".jpg";

    cv::Mat first_photo_object = cv::imread("image/wheel0.jpg");

    /*
    pstmt = conn->prepareStatement("INSERT INTO pixels.rbg (r, g, b) VALUES ( r=?, g=?, b=?)");

    int count_photo_object = 10;
    for (int k = 0; k < count_photo_object; k++) {
        std::string photo_img = "image/wheel" + std::to_string(k) + extention_photo_object;
        cv::Mat photo = cv::imread(photo_img);
        for (int i = 0; i < first_photo_object.rows; i++) {
            for (int j = 0; j < first_photo_object.cols; j++) {
                if (first_photo_object.at<cv::Vec3b>(i, j) == array_suitable_pixels[k]) {
                    //записываем результат в базу данных
                    //first_photo_object.at<cv::Vec3b>(i, j)[0]
                    //stmt->execute("INSERT INTO pixels.rbg (r, g, b) VALUES ('+temp_r+', '+temp_g+', '+temp_b+')");
                    pstmt->setInt(1, int(first_photo_object.at<cv::Vec3b>(i, j)[0]));
                    pstmt->setInt(2, int(first_photo_object.at<cv::Vec3b>(i, j)[1]));
                    pstmt->setInt(3, int(first_photo_object.at<cv::Vec3b>(i, j)[2]));
                    pstmt->execute();

                }
            }
        }
    }
    */


    std::cout << i_arr << std::endl;
    std::cout << image.type() << std::endl;

    //delete conn;
    //delete stmt;

    return 0;
}