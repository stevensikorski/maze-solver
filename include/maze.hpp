#ifndef MAZE_HPP
#define MAZE_HPP

#include <iostream>
#include <opencv2/opencv.hpp>

struct Point
{
    cv::Vec3b data;
    int red, green, blue;
    bool allowed;
    bool checked;
    bool path;
};

enum Colors
{
    WHITE,
    BLACK,
    RED,
    GREEN,
    NONE
};

class Maze
{
    private:
        Point** maze;
        cv::Mat image;
        int width, height;
        int startX, startY, endX, endY;
        int x, y;

    public:
        Maze(cv::Mat image); // Create maze from image
        ~Maze();
        void findStart();
        void findEnd();
        void determinePath();
        void findPath();
        bool validMove(int x, int y);
        bool DFS(int x, int y, std::vector<std::pair<int, int>> &path);
        void printMaze();
};

Colors determineColor(int red, int green, int blue);

#endif