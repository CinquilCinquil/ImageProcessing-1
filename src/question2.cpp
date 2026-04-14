#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <algorithm>
using vector2 = std::vector<std::vector<float>>;
using Pixel = uchar;

class Question2 {
    private:
    
    cv::Mat image;
    std::string image_path;

    public:

    Question2(std::string image_path) : image_path(image_path) {
        refresh();
    }

    void convolution_in_space_domain(vector2 &kernel, int d) {

        int width = image.cols;
        int height = image.rows;
        int padding = d/2;

        float highest_value = -255.0f, lowest_value = 255.0f;
        cv::Mat values(height, width, CV_32FC1);

        // Calculating image values

        for (int w = padding;w < width - padding;w ++) {
        for (int h = padding;h < height - padding;h ++) {

            float value = 0.0f;

            for (int i = 0;i < d;i ++) {
            for (int j = 0;j < d;j ++) {
                Pixel pixel = image.at<Pixel>(h - padding + i, w - padding + j);
                value += kernel[i][j] * static_cast<float>(pixel);
            }}

            highest_value = std::max(value, highest_value);
            lowest_value = std::min(value, lowest_value);
            values.at<float>(h - padding, w - padding) = value;
        }}

        // Modifying the image

        for (int w = padding;w < width - padding;w ++) {
        for (int h = padding;h < height - padding;h ++) {

            float value = values.at<float>(h - padding, w - padding);
            float normalized_value = 255.0f * ((value - lowest_value)/(highest_value - lowest_value));

            image.at<Pixel>(h, w) = static_cast<Pixel>(normalized_value);

        }}
    }

    void save(std::string filename) {
        cv::imwrite("images/results/" + filename + ".bmp", image);
    }
    
    void refresh() {
        image = cv::imread(image_path, cv::IMREAD_GRAYSCALE);
    }
};

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cout << argc << '\n';
        std::cout << "You need to pass excatly one input image path as an argument!";
        return -1;
    }

    std::string filepath = argv[1];
    auto q = Question2(filepath);

    // Low-Pass
    vector2 low_pass_kernel = {
        {0.11f, 0.11f, 0.11f},
        {0.11f, 0.11f, 0.11f},
        {0.11f, 0.11f, 0.11f}
    };

    q.convolution_in_space_domain(low_pass_kernel, low_pass_kernel.size());
    q.save("question2_low_pass_result");

    // High-Pass

    vector2 high_pass_kernel = {
        {-1.0f, -1.0f, -1.0f},
        {-1.0f, 8.0f, -1.0f},
        {-1.0f, -1.0f, -1.0f}
    };

    q.refresh();
    q.convolution_in_space_domain(high_pass_kernel, high_pass_kernel.size());
    q.save("question2_high_pass_result");
}