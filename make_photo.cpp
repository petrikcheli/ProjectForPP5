#include "make_photo.h"

make_photo::make_photo() {
    cv::namedWindow("choice_ROI", cv::WINDOW_NORMAL);
    cv::VideoCapture cap;
    std::string file_name_video = "first_video.mp4";
    std::string file_name_video2 = "video_test.mp4";
    cap.open(file_name_video);

    cv::Mat frame;

    cap>>frame;
    // Read image

    // Select ROI
    cv::Rect2d r = selectROI("choice_ROI", frame, false, false, true);
    std::cout << r.x << std::endl <<  r.y << std::endl;
    r.x = r.x-1;
    r.y = r.y-1;
    cv::Mat roi = frame(r);

    cv::namedWindow("roi", cv::WINDOW_NORMAL);
    cv::imshow("roi", roi);
    cv::waitKey(0);
    std::string extention_photo_object = ".jpg";
    int i = 0;
    for(;;){
        cap>>frame;
        if(frame.empty()) break;
        cv::rectangle(frame, r, cv::Scalar(0, 255, 0));
        //cv::rectangle(frame, roi, cv::Scalar(94.0,206,165))
        cv::imshow("choice_ROI", frame);
        char c = cv::waitKey(13);
        if(c == 32){
            i++;
            cv::imwrite("img/image"+std::to_string(i)+extention_photo_object,
                        frame(r),
                        {cv::IMWRITE_JPEG_QUALITY, 95});
        } else if (c == 27){
            break;
        }
    }
}