#include <iostream>
#include <opencv2/opencv.hpp>
#include "include/maze.hpp"
#include "src/maze.cpp"

int main() 
{
    cv::Mat mymaze = cv::imread("../mazes/maze.png");
    cv::Mat maze1 = cv::imread("../mazes/maze1.png");
    cv::Mat maze2 = cv::imread("../mazes/maze2.png");
    cv::Mat maze3 = cv::imread("../mazes/maze3.png");

    system("clear");
    std::cout << "+-----------------------------------------+" << std::endl;
    std::cout << "\e[1m" << "|               Maze Solver               |" << "\e[0m" << std::endl;
    std::cout << "+-----------------------------------------+" << std::endl;

    bool mazeReplaced = (mymaze.cols == 1) ? 1 : 0;
    if (mazeReplaced)
    {
        std::cout << std::endl << "\x1b[33m" << "\e[1m" << "maze.png" << "\e[0m" << "\x1b[33m" << " not found " << "\x1b[0m" << std::endl;
    }

    std::cout << std::endl << "Steps to make your own maze!" << std::endl;
    std::cout << "  1. Create an image titled " << "\e[1m" << "maze.png" << "\e[0m" << std::endl;
    std::cout << "  2. Color the image with the following components." << std::endl;
    std::cout << "          Walls:" << "\x1b[30m" << "  RGB(0, 0, 0)" << "\x1b[0m" << std::endl;
    std::cout << "          Path:" << "\x1b[37m" << "   RGB(255, 255, 255)" << "\x1b[0m" << std::endl;
    std::cout << "          Start:" << "\x1b[31m" << "  RGB(255, 0, 0)" << "\x1b[0m" << std::endl;
    std::cout << "          End:" << "\x1b[32m" << "    RGB(0, 255, 0)" << "\x1b[0m" << std::endl;
    std::cout << "  3. Replace " << "\e[1m" << "maze.png" << "\e[0m" << " inside the " << "\e[1m" << "mazes" << "\e[0m" << " folder." << std::endl;
    std::cout << "  4. Restart the executable." << std::endl; 

    if (!mazeReplaced)
    {
        Maze maze(mymaze);
    }

    Maze image1(maze1);
    Maze image2(maze2);
    Maze iamge3(maze3);
}