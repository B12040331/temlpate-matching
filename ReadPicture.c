
#include <stdio.h>

int main() {
    FILE *fp, *fq;
    fp = fopen("G:\\template matching\\input.jpg", "rb");
    fq = fopen("G:\\template matching\\output.jpg", "wb");
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    char ch;
    int i;
    fseek(fp, 0, SEEK_SET);
    for(i=0; i<size; ++i) {
        ch = fgetc(fp);
        fputc(ch, fq);
 //       printf("%c", ch);
    }
    fclose(fp);
    fclose(fq);
    return 0;
}
