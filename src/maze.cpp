#include <iostream>
#include <opencv2/opencv.hpp>
#include "../include/maze.hpp"

Maze::Maze(cv::Mat image)
{
    width = image.cols;
    height = image.rows;

    maze = new Point*[width];
    for (int i = 0; i < width; i++)
    {
        maze[i] = new Point[height];
    }

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            Point pixel;
            pixel.data = image.at<cv::Vec3b>(j, i);
            pixel.red = (int)pixel.data[2];
            pixel.green = (int)pixel.data[1];
            pixel.blue = (int)pixel.data[0];
            pixel.allowed = true;
            pixel.checked = false;
            pixel.path = false;

            maze[i][j] = pixel;
        }
    }
    findStart();
    findEnd();
    determinePath();
    findPath();
    printMaze();
}

Maze::~Maze()
{
    for (int i = 0; i < width; i++)
    {
        delete [] maze[i];
        maze[i] = nullptr;
    }
    delete [] maze;
    maze = nullptr;
}

void Maze::findStart()
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            Point pixel = maze[i][j];
            Colors type = determineColor(pixel.red, pixel.green, pixel.blue);
            if (type == RED)
            {
                startX = i;
                startY = j;
            }
        }
    }

    x = startX;
    y = startY;
}

void Maze::findEnd()
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            Point pixel = maze[i][j];
            Colors type = determineColor(pixel.red, pixel.green, pixel.blue);
            if (type == GREEN)
            {
                endX = i;
                endY = j;
            }
        }
    }
}

void Maze::determinePath()
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            Point pixel = maze[i][j];
            Colors type = determineColor(pixel.red, pixel.green, pixel.blue);
            if (type == WHITE)
            {
                maze[i][j].allowed = true;
            }
            if (type == BLACK)
            {
                maze[i][j].allowed = false;
            }
        }
    }
}

void Maze::findPath()
{
    std::vector<std::pair<int, int>> path;
    int x = startX;
    int y = startY;

    DFS(x, y, path);

    for (int i = 0; i < path.size(); i++)
    {
        int a = path[i].first;
        int b = path[i].second;

        maze[a][b].path = true;
    }
}

bool Maze::validMove(int x, int y)
{
    return x >= 0 && x < width && y >= 0 && y < height && maze[x][y].allowed && maze[x][y].checked == false;
}

bool Maze::DFS(int x, int y, std::vector<std::pair<int, int>> &path)
{

    if (x == endX && y == endY)
    {
        path.push_back({x, y});
        return true;
    }

    if (validMove(x, y))
    {
        path.push_back({x, y});
        maze[x][y].checked = true;

        if (DFS(x + 1, y, path) || DFS(x, y + 1, path) || DFS(x - 1, y, path) || DFS(x, y - 1, path))
        {
            return true;
        }

        path.pop_back();
    }

    return false;
}

void Maze::printMaze()
{
    std::cout << std::endl;
    for (int j = 0; j < width; j++)
    {
        for (int i = 0; i < height; i++)
        {
            if (i == startX & j == startY)
            {
                std::cout << "A";
                continue;
            }

            else if (i == endX && j == endY)
            {
                std::cout << "B";
                continue;
            }

            else if (maze[i][j].path)
            {
                std::cout << "·";
                continue;
            }

            else if (maze[i][j].allowed)
            {
                std::cout << " ";
                continue;
            }

            else
            {
                std::cout << "█";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

Colors determineColor(int red, int green, int blue)
{
    if (red == 255 && green == 255 && blue == 255)
    {
        return WHITE;
    }
    if (red == 0 && green == 0 && blue == 0)
    {
        return BLACK;
    }
    if (red == 255 && green == 0 && blue == 0)
    {
        return RED;
    }
    if (red == 0 && green == 255 && blue == 0)
    {
        return GREEN;
    }

    return NONE;
}