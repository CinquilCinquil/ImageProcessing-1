#include <opencv2/opencv.hpp>
#include <iostream>

// programa de teste gerado por ia
int main() {
    cv::Mat image = cv::imread("images/linux.png");

    if (image.empty()) {
        std::cerr << "Error: Could not open or find the image!" << std::endl;
        return -1;
    }

    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

    cv::imshow("Original", image);
    cv::imshow("Grayscale", gray);

    cv::waitKey(0);

    return 0;
}