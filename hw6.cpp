#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

#pragma pack(push, 1)
struct BMPhearder
{
	char sign[2];
	int size;
	int offeset;
	short reserved1;
	short reserver2;
};
struct BMPInfohearder
{
	int head_size;
	int width;
	int heigh;
	short cololr;
	short pixel;
	int image_size;
	int horizontal;
	int vertical;
	int num_color;
	int num_impotant_color;
};
#pragma pack(pop)

vector<char> BMP_read(const string& file)
{
	ifstream open(file, ios::binary);
	if (!open)
	{
		cout << "無法開啟檔案 " << file << endl;
		return {};
	}
	vector<char> data((istreambuf_iterator<char>(open)), (istreambuf_iterator<char>()));
	open.close();
	return data;
}

void BMP_write(const string& file, const vector<char>& Data)
{
	ofstream out(file, ios::binary);
	if (!out)
	{
		cout << "無法建立檔案 " << file << endl;
		return;
	}
	out.write(Data.data(), Data.size());
	out.close();
}

vector<char> compress(const vector<char>& Data)
{
	vector<char> compressedData;
	char current = Data[0];
	int count = 1;
	for (int i = 1; i < Data.size(); i++)
	{
		char pixel = Data[i];
		if (pixel == current)
			count++;
		else
		{
			compressedData.push_back(current);
			compressedData.push_back(static_cast<char>(count));
			current = pixel;
			count = 1;
		}
	}
	compressedData.push_back(current);
	compressedData.push_back(static_cast<char>(count));
	return compressedData;
}

vector<char> decompress(const vector<char>& Data)
{
	vector<char> decompressedData;
	for (int i = 0; i < Data.size(); i += 2)
	{
		char pixel = Data[i];
		char count = Data[i + 1];
		for (int j = 0; j < count; j++)
			decompressedData.push_back(pixel);
	}
	return decompressedData;
}

double calculateCompressionRate(const vector<char>& originalData, const vector<char>& compressedData)
{
	double originalSize = originalData.size();
	double compressedSize = compressedData.size();
	double compressionRate = (compressedSize / originalSize) * 100;
	return compressionRate;
}

int main()
{
	vector<string> input(3), output(3), decompress_output(3);
	input = { "img1.bmp","img2.bmp","img3.bmp" };
	output = { "img1.txt","img2.txt","img3.txt" };
	decompress_output = { "de_img1.bmp","de_img2.bmp","de_img3.bmp" };

	double totalCompressionRate = 0.0;
	int numFiles = input.size();

	for (int i = 0; i < numFiles; i++)
	{
		vector<char> input_bmp = BMP_read(input[i]);
		vector<char> compress_bmp = compress(input_bmp);
		BMP_write(output[i], compress_bmp);
		vector<char> input_com = BMP_read(output[i]);
		vector<char> decompress_txt = decompress(input_com);
		BMP_write(decompress_output[i], decompress_txt);

		double compressionRate = calculateCompressionRate(input_bmp, compress_bmp);
		totalCompressionRate += compressionRate;

		cout << "檔案 " << input[i] << " 的壓縮率為: " << fixed << setprecision(2) << compressionRate << "%" << endl;
	}

	double averageCompressionRate = totalCompressionRate / numFiles;
	cout << "平均壓縮率為: " << fixed << setprecision(2) << averageCompressionRate << "%" << endl;

	cout << "全部完成！\n";
	return 0;
}