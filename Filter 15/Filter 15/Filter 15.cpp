#define _CRT_SECURE_NO_WARNINGS 
#include"Image_Class.h"
#include<iostream>
using namespace std;

class Makepurple_atnight {
public:
	static void make_purple(Image& image, float night_reduction = 0.35f) {
		for (int x = 0; x < image.width; x++) {
			for (int y = 0; y < image.height; y++) {
				double avg = (image(x, y, 0) + image(x, y, 1) + image(x, y, 2)) / 3.0;
				for (int z = 0; z < image.channels; z++) {
					double new_value = 0;
					switch (z) {
					case 0:
						new_value = avg * night_reduction * 0.8;
						break;
					case 1:
						new_value = 0;
						break;
					case 2:
						new_value = avg * night_reduction * 1.2;
						break;
					}
					if (new_value > 255) new_value = 255;
					if (new_value < 0) new_value = 0;
					image(x, y, z) = (int)new_value;
				}
			}
		}
	}
};
int main() {
	string file_name;
	cout << "Enter your file name: ";
	cin >> file_name;
	Image My_image(file_name);
	if (My_image.width == 0 || My_image.height == 0) {
		cout << "Error loading image! " << endl;
		return 1;
	}
	Makepurple_atnight::make_purple(My_image, 0.35f);
	My_image.saveImage("output.jpg");
	cout << "Saved successfully as output.jpg\n";

	return 0;
}