
/*
四部分:
1.bmp文件头  14字节
2.位图信息头 40字节
3.调色板     1024字节
4.位图数据
*/

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

BITMAPFILEHEADER bmpfileheader;
BITMAPINFOHEADER bmpinfoheader;
FILE *fp, *fq;
char **buffer;

void GetFileSource();
void GetBmpFileHeader();
void GetBmpInfoHeader();
void GetBmpData();
void ReleaseSource();

int main() {
    GetFileSource();
    GetBmpFileHeader();
    GetBmpInfoHeader();
    GetBmpData();
    ReleaseSource();
    return 0;
}

void GetFileSource() {
    fp = fopen("G:\\template matching\\current_g_A.bmp", "rb");
    fq = fopen("G:\\template matching\\current_g_A.dat", "wb");
}

void GetBmpFileHeader() {
    fseek(fp, 0, SEEK_SET);
    fread(&bmpfileheader.bfType, sizeof(char), 2, fp);
    fread(&bmpfileheader.bfSize, sizeof(char), 4, fp);
    fread(&bmpfileheader.bfReserved1, sizeof(char), 2, fp);
    fread(&bmpfileheader.bfReserved2, sizeof(char), 2, fp);
    fread(&bmpfileheader.bfOffBits, sizeof(char), 4, fp);
}

void GetBmpInfoHeader() {
    fseek(fp, 14, SEEK_SET);
    fread(&bmpinfoheader.biSize, sizeof(char), 4, fp);
    fread(&bmpinfoheader.biWidth, sizeof(char), 4, fp);
    fread(&bmpinfoheader.biHeight, sizeof(char), 4, fp);
    fread(&bmpinfoheader.biPlanes, sizeof(char), 2, fp);
    fread(&bmpinfoheader.biBitCount, sizeof(char), 2, fp);
    fread(&bmpinfoheader.biCompression, sizeof(char), 4, fp);
    fread(&bmpinfoheader.biSizeImage, sizeof(char), 4, fp);
    fread(&bmpinfoheader.biXPelsPerMeter, sizeof(char), 4, fp);
    fread(&bmpinfoheader.biYPelsPerMeter, sizeof(char), 4, fp);
    fread(&bmpinfoheader.biClrUsed, sizeof(char), 4, fp);
    fread(&bmpinfoheader.biClrImportant, sizeof(char), 4, fp);
}

void GetBmpData() {
//    printf("height: %d width: %d\n", bmpinfoheader.biHeight, bmpinfoheader.biWidth);
    fseek(fp, 1078, SEEK_SET);
    int size = bmpinfoheader.biWidth * bmpinfoheader.biHeight;
    buffer = (char**)malloc(sizeof(char*) * bmpinfoheader.biHeight);
    int i, j;
    for(i=0; i<bmpinfoheader.biHeight; ++i) {
        buffer[i] = (char*)malloc(sizeof(char) * bmpinfoheader.biWidth);
    }
    fread(buffer, sizeof(char), size, fp);
    for(i=0; i<bmpinfoheader.biHeight; ++i) {
        for(j=0; j<bmpinfoheader.biWidth; ++j) {
 //           printf("%c", buffer[i][j]);
            fputc(buffer[i][j], fq);
        }
 //       printf("\n");
    }
}

void ReleaseSource() {
    fclose(fp);
    fclose(fq);
    int i;
    for(i=0; i<bmpinfoheader.biHeight; ++i) {
        free(buffer[i]);
    }
    free(buffer);
}
