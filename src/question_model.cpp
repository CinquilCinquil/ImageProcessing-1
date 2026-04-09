#include <opencv2/opencv.hpp>
#include <string>

class Question {
    protected:
    
    cv::Mat image;
    std::string image_path;

    public:

    Question(std::string image_path) : image_path(image_path) {
        refresh();
    }

    void save(std::string filename) {
        cv::imwrite("images/results/" + filename + ".bmp", image);
    }
    
    void refresh() {
        image = cv::imread(image_path, cv::IMREAD_GRAYSCALE);
    }

};