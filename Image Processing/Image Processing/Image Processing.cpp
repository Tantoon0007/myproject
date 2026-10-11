/*
Name                ID              what he did;            section

Mohamed Sayed       20240500        2,6,10                  S
Eyad Wael           20250100        3,7                     S
Abd El-Rahman Amr   20250368        4,8,12,16               S
Tony Samir Sobhy    20240132        1,5,13                  S

*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#include "Image_Class.h"
#include <cmath>
#include <numbers>

void applygrayscale(Image& image)
{
    for (int i = 0; i < image.width; ++i)
    {

        for (int j = 0; j < image.height; ++j)
        {
            unsigned int avg = 0;
            for (int k = 0; k < image.channels; ++k)
            {
                avg += image(i, j, k);
            }

            avg /= image.channels;
            for (int k = 0; k < image.channels; ++k)
            {
                image(i, j, k) = avg;
            }
        }
    }
}

void blackandwhite(Image& image)
{

    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            unsigned int avg = 0; // Initialize average value

            for (int k = 0; k < 3; ++k)
            {
                avg += image(i, j, k); // Accumulate pixel values
            }

            avg /= 3; // Calculate average

            avg = (avg < 128) ? 0 : 255;
            // Set all channels to the average value
            image(i, j, 0) = avg;
            image(i, j, 1) = avg;
            image(i, j, 2) = avg;
        }
    }
}

void invert(Image& image)
{

    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {

            for (int k = 0; k < 3; ++k)
            {
                image(i, j, k) = 255 - image(i, j, k);
            }
        }
    }
}

void frame(Image& image)
{

    int size = 70;

    for (int y = 0; y < image.height; y++)
    {
        for (int x = 0; x < image.width; x++)
        {

            if (x < size || x >= image.width - size || y < size || y >= image.height - size)
            {
                image(x, y, 0) = 255;
                image(x, y, 1) = 0;
                image(x, y, 2) = 255;
            }
        }
    }
}

class Flipped_Image {
public:

    static void flip_Horizontally(Image& image) {
        for (int x = 0; x < image.width / 2; x++) {
            for (int y = 0; y < image.height; y++) {
                for (int z = 0; z < image.channels; z++) {
                    swap(image(x, y, z), image(image.width - 1 - x, y, z));
                }
            }
        }
    }

    static void flip_vertically(Image& image) {
        for (int x = 0; x < image.width; x++) {
            for (int y = 0; y < image.height / 2; y++) {
                for (int z = 0; z < image.channels; z++) {
                    swap(image(x, y, z), image(x, image.height - 1 - y, z));
                }
            }
        }
    }

    static void processflip(Image& image) {
        int choice;
        while (true) {
            cout << "=======================================\n";
            cout << "   Welcome to Image Flipper Program    \n";
            cout << "=======================================\n";
            cout << "Please select flip direction:\n";
            cout << "1. Horizontal Flip (Left to Right)\n";
            cout << "2. Vertical Flip (Top to Bottom)\n";
            cout << "---------------------------------------\n";
            cout << "Enter your choice (1 or 2): ";

            cin >> choice;

            switch (choice) {
            case 1:
                flip_Horizontally(image);
                cout << "\nImage Flipped Horizontally Successfully!\n";
                return;

            case 2:
                flip_vertically(image);
                cout << "\nImage Flipped Vertically Successfully!\n";
                return;

            default:
                cout << "\n[Error] Invalid choice! Please enter 1 or 2.\n\n";
            }
        }
    }
};

void rotate(Image& image)
{


    cout << "How do you want to rotate your image clockwise?\n";
    cout << "Choose a number from the following options!\n";
    cout << "1- 90 \n";
    cout << "2- 180 \n";
    cout << "3- 270 \n";
    int degree_choice;
    cin >> degree_choice;


    for (int r = 0; r < degree_choice; r++) {
        Image image2 = image;
        image.height = image2.width;
        image.width = image2.height;
        for (int i = 0; i < image.width; ++i)
        {
            for (int j = 0; j < image.height; ++j)
            {
                for (int k = 0; k < image.channels; ++k)
                {
                    image(i, j, k) = image2(j, image2.height - i - 1, k);
                }

            }
        }
    }
}

void applylightendarken(Image& image, int choice)
{
    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            for (int k = 0; k < image.channels; ++k)
            {
                if (choice == 1)
                {
                    int newvalue = image(i, j, k) + ((255 - image(i, j, k)) * 0.5);
                    image(i, j, k) = min(255, newvalue);
                }
                else if (choice == 2)
                {
                    image(i, j, k) = image(i, j, k) * 0.5;
                }
            }
        }
    }
}

void resize(Image& image, int new_width = 0, int new_height = 0)
{
    if (new_width == 0 || new_height == 0) {

        int new_width, new_height;
        cout << "pls enter the new width you want:" << endl;
        cin >> new_width;
        cout << "pls enter the new height you want:" << endl;
        cin >> new_height;
    }
    Image resizedImage(new_width, new_height);

    for (int y = 0; y < new_height; y++)
    {
        for (int x = 0; x < new_width; x++)
        {
            int originalX = x * image.width / new_width;
            int originalY = y * image.height / new_height;

            for (int c = 0; c < image.channels; c++)
            {
                resizedImage(x, y, c) = image(originalX, originalY, c);
            }
        }
    }

    image = resizedImage;
}

void merge_function(Image& image, Image& image2)
{
    int w = (image.width < image2.width) ? image.width : image2.width;
    int h = (image.height < image2.height) ? image.height : image2.height;
    Image merged_image(w, h);
    for (int i = 0; i < merged_image.width; ++i)
    {
        for (int j = 0; j < merged_image.height; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                merged_image(i, j, k) = (image(i, j, k) + image2(i, j, k)) / 2;
            }
        }
    }
    image = merged_image;
}
void merge(Image& image)
{

    string filename2;
    cout << "Pls enter the second colored image name to merge :";
    cin >> filename2;
    Image image2(filename2);

    if (image.height == image2.height && image.width == image2.width) {
        merge_function(image, image2);
    }
    else {
        cout << "these two picturs aren't the same dimentions Please choose one of these next options:\n";
        int chosen_option;
        cout << "(1) resize the smaller image or both images to the biggest height and the biggest width and then merge" << endl;
        cout << "(2) merge the commonarea of the smaller width and the smaller height. " << endl;
        cin >> chosen_option;

        if (chosen_option == 1) {
            int bigger_width = (image.width > image2.width) ? image.width : image2.width;
            int bigger_height = (image.height > image2.height) ? image.height : image2.height;
            resize(image, bigger_width, bigger_height);
            resize(image2, bigger_width, bigger_height);
            merge_function(image, image2);
        }
        else if (chosen_option == 2) {
            merge_function(image, image2);
        }

    }
}

void edges(Image& image)
{

    blackandwhite(image);
    Image image2 = image;

    for (int i = 1; i < image.width - 1; ++i)
    {
        for (int j = 1; j < image.height - 1; ++j)
        {
            if (image(i, j, 0) == 0 && (image2(i - 1, j, 0) != image2(i + 1, j, 0) || image2(i, j - 1, 0) != image2(i, j + 1, 0)))
            {
                image(i, j, 0) = 0;
                image(i, j, 1) = 0;
                image(i, j, 2) = 0;
            }
            else
            {
                image(i, j, 0) = 255;
                image(i, j, 1) = 255;
                image(i, j, 2) = 255;
            }
        }
    }
}

void blur(Image& image)
{
    Image image2 = image;

    for (int i = 1; i < image.width - 1; ++i)
    {
        for (int j = 1; j < image.height - 1; ++j)
        {
            // unsigned int avg = 0;

            for (int k = 0; k < 3; ++k)
            {

                unsigned int avg = 0;
                avg = (image(i, j, k) + image(i + 1, j, k) + image(i - 1, j, k) + image(i, j + 1, k) + image(i, j - 1, k) + image(i - 1, j - 1, k) + image(i + 1, j + 1, k) + image(i - 1, j + 1, k) + image(i + 1, j - 1, k)) / 9;

                image(i, j, k) = avg;
            }
        }
    }
}

void natural_sunlight(Image& image) {

    /*
        either we
        reduce the blue
        or
        increase the red and green
    */

    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {

            // if((image(i,j,0) + 40)>255 || (image(i,j,1) + 40)>255 ){
            //     image(i,j,0)=255;
            //     image(i,j,1)=255;
            //     continue;
            // }
            // else{
            //     image(i,j,0) += 40;
            //     image(i,j,1) += 40;

            if ((image(i, j, 2) - 40) < 0) { //to ensure we don't go out of range
                image(i, j, 2) = 0;
                continue;
            }
            else {
                image(i, j, 2) -= 40;
            }
        }
    }

}

void oldtv(Image& image) {

    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            for (int k = 0; k < image.channels; ++k)
            {
                image(i, j, k) = image(i, j, k) * 0.5;
            }
            j++;
            if (j > image.height)
                break; //to avoid out of range problem
        }
    }

}

void infrared(Image& image)
{

    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            image(i, j, 0) = 0;
        }
    }
    invert(image);
}

void skew(Image& image)
{

    double degree;
    cout << "pls enter the drgree of skewness you want ?\n";
    cin >> degree;
    double radians = degree * (numbers::pi / 180.0);
    int the_added_width = sin(radians) * (image.height / cos(radians));
    Image image2(image.width + the_added_width, image.height);
    double z = double(the_added_width) / double(image.width);


    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            for (int k = 0; k < image.channels; ++k)
            {
                image2(i + (the_added_width - z * j), j, k) = image(i, j, k);
            }
        }
    }
    // cout<<"done\n";
    image = image2;
}

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


int main()
{
    string filename;
    cout << "Pls enter colored image name to use :";
    cin >> filename;
    Image image(filename);

    while (true) {
        cout << "\n which filter do you want to apply? \n";
        cout << "1- grayscale\n";
        cout << "2- back and white\n";
        cout << "3- invert\n";
        cout << "4- frame\n";
        cout << "5- flip\n";
        cout << "6- rotate\n";
        cout << "7.lighten \n";
        cout << "77.darken \n";
        cout << "8.resize \n";
        cout << "9-  merge \n";
        cout << "10- Detect Image Edges\n";
        cout << "12- Blur Image\n";
        cout << "13- natural sunlight\n";
        cout << "14- old Den Den Mushi (televisions)\n";
        cout << "16- infrared\n";
        cout << "17- Image Skewing Filter\n";
        cout << "18- Oil Painting\n";
        cout << "0- exit\n";
        int choice;
        cin >> choice;

        if (choice == 1)
        {
            applygrayscale(image);
        }

        else if (choice == 2)
        {
            blackandwhite(image);
        }

        else if (choice == 3)
        {
            invert(image);
        }

        else if (choice == 4)
        {
            frame(image);
        }

        else if (choice == 5)
        {
            if (image.width == 0 || image.height == 0) {
                cout << "Error loading image!\n";
                return 1;
            }

            Flipped_Image::processflip(image);
        }

        else if (choice == 6)
        {
            rotate(image);
        }

        else if (choice == 7)
        {
            applylightendarken(image, 1);
            cout << "lighten filter applied successfully \n";
        }

        else if (choice == 77)
        {
            applylightendarken(image, 2);
            cout << "darken filter applied successfully \n";
        }

        else if (choice == 8)
        {
            resize(image);
        }

        else if (choice == 9)
        {
            merge(image);
        }

        else if (choice == 10)
        {
            edges(image);
        }

        else if (choice == 12)
        {
            for (int i = 0; i < 50; i++)
            {
                // cout << i << endl;
                blur(image);
            }
        }

        else if (choice == 13)
        {
            natural_sunlight(image);
        }

        else if (choice == 14)
        {
            oldtv(image);
        }

        else if (choice == 16)
        {
            infrared(image);
        }

        else if (choice == 17)
        {
            skew(image);
        }
        else if (choice == 18)
        {
            Oil_painting::Oil_painted(image);
        }

        else
        {
            if (choice == 0)
                break;
            else
                cout << "you entered an invalid choice \n";
            return 0;
        }
    }
    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga:\n";

    cin >> filename;
    image.saveImage(filename);
    cout << "Image saved successfully as " << filename << endl;

    return 0;
}
