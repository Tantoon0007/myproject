#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Image_Class.h"
using namespace std;

class Oil_painting {
public:
    static Image Oil_painted(Image& img) {
        Image output(img.width, img.height);

        int radius = 3;
        int levels = 20;

        for (int x = 0; x < img.width; x++) {
            for (int y = 0; y < img.height; y++) {
                 
                int count[3][20] = {};
                int sum[3][20] = {};

                for (int dx = -radius; dx <= radius; dx++) {
                    for (int dy = -radius; dy <= radius; dy++) {

                        int nx = x + dx;
                        int ny = y + dy;

                        if (nx < 0 || nx >= img.width ||
                            ny < 0 || ny >= img.height) {
                            continue;
                        }

                        for (int z = 0; z < img.channels && z < 3; z++) {
                            int color = img(nx, ny, z);
                            int level = color * levels / 256;

                            if (level >= levels)
                                level = levels - 1;

                            count[z][level]++;
                            sum[z][level] += color;
                        }
                    }
                }

                for (int z = 0; z < img.channels; z++) {
                    if (z < 3) {
                        int bestLevel = 0;

                        for (int i = 1; i < levels; i++) {
                            if (count[z][i] > count[z][bestLevel]) {
                                bestLevel = i;
                            }
                        }

                        if (count[z][bestLevel] > 0) {
                            output(x, y, z) =
                                sum[z][bestLevel] / count[z][bestLevel];
                        }
                    }
                    else {
                        output(x, y, z) = img(x, y, z);
                    }
                }
            }
        }

        return output;
    }
};

int main() {
    string filename;   

    cout << "Enter your filename: ";
    cin >> filename;

    Image img(filename);
    Image result = Oil_painting::Oil_painted(img);

    result.saveImage("Painted_Image.jpg");

    cout << "Image saved successfully!" << endl;

    return 0;
}
