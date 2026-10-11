#define _CRT_SECURE_NO_WARNINGS 
#include<iostream>
#include"Image_Class.h"
using namespace std; 

class Merge_Image {
public:
	static Image merged_image(Image &img1 , Image &img2 ) {
		if (img1.width == img2.width && img1.height == img2.height) {
			Image output(img1.width , img1.height);
			for (int x = 0; x < img1.width; x++) {
				for (int y = 0; y < img1.height; y++) {
					for (int z = 0; z < img1.channels; z++) { 
						int val1 = img1(x, y, z);
						int val2 = img2(x, y, z);
						output(x, y, z) = (val1 + val2) / 2;
					}
				}
			}
			return output;
		}
		else {
			int max_w, max_h;
			if (img1.width  > img2.width) {
				max_w = img1.width;
			}
			else {
				max_w = img2.width;
			}
			if (img1.height > img2.height) {
				max_h = img1.height;
			}
			else {
				max_h = img2.height;
			}
			Image output(max_w,max_h);
			for (int x = 0; x < max_w; x++) {
				for (int y = 0; y < max_h; y++) {
					for (int z = 0; z < output.channels; z++) {
						if (x < img1.width && y < img1.height && x < img2.width && y < img2.height) {
							int val1 = img1(x, y, z);
							int val2 = img2(x, y, z);
							output(x, y, z) = (val1 + val2) / 2;
						}
						else if (x < img1.width && y < img1.height) {
							output(x, y, z) = img1(x, y, z);
						}
						else if (x < img2.width && y < img2.height) {
							output(x, y, z) = img2(x, y, z);
						}
					}
				}
			}
			return output;
		}
	}
};

int main() {
	string first_filename, second_filename;
	cout << " Enter your first filename: ";
	cin >> first_filename; 
	cout << "Enter your second filename: ";
	cin >> second_filename;
	Image img1(first_filename);
	Image img2(second_filename);

	Image output = Merge_Image::merged_image(img1,img2);
	output.saveImage("Merged_Image.jpg");
	cout << "Saved as Merged_Image successfully" << endl;
	return 0;
}
