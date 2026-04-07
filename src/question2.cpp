#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
using vector2 = std::vector<std::vector<float>>;
using Pixel = uchar;

class Question2 {
    private:
    
    cv::Mat image;

    public:

    Question2(std::string image_path) {
        image = cv::imread(image_path, cv::IMREAD_GRAYSCALE);
    }

    void convolution_in_space_domain(vector2 &kernel, int d) {

        int width = image.cols;
        int height = image.rows;
        int padding = d/2;

        std::cout << width << '\n' << height << '\n';

        for (int w = padding;w < width - padding;w ++) {
        for (int h = padding;h < height - padding;h ++) {

            int value = 0;

            for (int i = 0;i < d;i ++) {
            for (int j = 0;j < d;j ++) {
                Pixel pixel = image.at<Pixel>(h - padding + i, w - padding + j);
                value += kernel[i][j] * pixel;
            }}

            //std::cout << value << '\n';

            image.at<Pixel>(h, w) = value;
        }}
    }

    void show() {
        //cv::imwrite("output.bmp", image);
        cv::imshow("Result", image);
        cv::waitKey(0);
    }
};

int main() {

    vector2 kernel = {
        {0.11f, 0.11f, 0.11f},
        {0.11f, 0.11f, 0.11f},
        {0.11f, 0.11f, 0.11f}
    };
    int d = kernel.size();
        
    auto q = Question2("images/linux.bmp");
    q.convolution_in_space_domain(kernel, d);
    q.show();
}