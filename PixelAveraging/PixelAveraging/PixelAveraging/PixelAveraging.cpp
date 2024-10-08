// PixelAveraging.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

Image* AveragePixels(Image data) {
    int width = data.getSize().x; 
    int height = data.getSize().y;
    Image* result = new Image;
    result->create(width, height);

    for (int pixelY = 0; pixelY < height; pixelY++) {
        for (int pixelX = 0; pixelX < width; pixelX++) {
            int neighborCount = 0; //init neighbor count
            int redAcc=0,greenAcc=0,blueAcc=0; // init RGB accumulators
            //find surrounding pixels, aware of borders
            int minX = max(pixelX - 1, 0);
            int maxX = min(pixelX + 1, width - 1);
            int minY = max(pixelY - 1, 0);
            int maxY = min(pixelY + 1, height - 1);
            for (int y = minY; y <= maxY; y++) {
                for (int x = minX; x <= maxX; x++) {
                   Color neighborColor= data.getPixel(x, y);
                   redAcc += neighborColor.r;
                   greenAcc += neighborColor.g;
                   blueAcc += neighborColor.b;
                    neighborCount++;
                }
            }
            result->setPixel(pixelX, pixelY, Color(redAcc/neighborCount,
                greenAcc/neighborCount,blueAcc/neighborCount));
        }
    }
    return result;
}


int main()
{
    Image sourceImg;
    sourceImg.loadFromFile("images/Salto de Eyipantla.png");
    Image* result = AveragePixels(sourceImg);
    result->saveToFile("Salto de Eyipantla Avg.png");
    delete result;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
