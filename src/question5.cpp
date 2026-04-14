#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <algorithm>
#include "question_model.cpp"

using vector2 = std::vector<std::vector<float>>;
using Pixel = uchar;

class Question5 : public Question {

    public:

    using Question::Question;

    void high_frequency_emphasis(float k1, float k2) {

        int width = image.cols;
        int height = image.rows;

        cv::Mat floatImg;
        image.convertTo(floatImg, CV_32F);

        cv::Mat planes[] = {floatImg, cv::Mat::zeros(image.size(), CV_32F)};
        cv::Mat complexImg;

        cv::merge(planes, 2, complexImg);

        cv::dft(complexImg, complexImg);

        for (int w = 0;w < width;w ++) {
        for (int h = 0;h < height;h ++) {
            cv::Vec2f value = complexImg.at<cv::Vec2f>(h, w);

            float transformation_value = k1 + k2 * high_pass(h, w);

            value *= transformation_value;

            complexImg.at<cv::Vec2f>(h, w) = value;
        }}

        cv::Mat spatial_domain_image;
        cv::dft(complexImg, spatial_domain_image, cv::DFT_INVERSE | cv::DFT_SCALE | cv::DFT_REAL_OUTPUT);

        cv::Mat resulting_bmp_image;
        spatial_domain_image.convertTo(resulting_bmp_image, CV_8UC1);

        image = resulting_bmp_image;
    }

    int high_pass(int y, int x) {
        if (y*y + x*x >= 100) {
            return 1;
        }
        return 0;
    }
};

int main(int argc, char* argv[]) {

    if (argc != 4) {
        std::cout << argc << '\n';
        std::cout << "You need to pass excatly one input image path, k1 and k2 as an argument!";
        return -1;
    }

    std::string filepath = argv[1];
    Question5 q(filepath);

    float k1 = std::stof(argv[2]), k2 = std::stof(argv[3]);

    q.high_frequency_emphasis(k1, k2);
    q.save("question5_high_freq_emphasis");
}
