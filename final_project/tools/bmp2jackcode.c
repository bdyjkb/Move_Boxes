#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAXWIDTH 1000

int main(int argc, char const *argv[])
{
	FILE *fin;
	FILE *fout;

	fin = fopen(argv[1], "r");
	assert(fin != NULL);

	fout = fopen(argv[2], "w");
	assert(fout != NULL);

	fprintf(fout, "//edit by Yisheng Lin\n");

	char buf[MAXWIDTH];

	printf("start to convert the file.\n");

	int row = 0;
	int i, cond, cnt;
	while(fgets(buf, MAXWIDTH, fin) != NULL){
		printf("%s", buf);
		cond = 0;
		cnt = 0;
		for(i=0; i<strlen(buf); i++){
			if(buf[i] == '1')
				cnt++;
			else if(cond == 1 && ( (buf[i] == '0') || (i == strlen(buf)-1) )){
				if(cnt == 1)
					fprintf(fout, "do Screen.drawPixel(x+%d, y+%d);\n", i-1, row);
				else
					fprintf(fout, "do Screen.drawLine(x+%d, y+%d, x+%d, y+%d);\n", i-cnt, row, i-1, row);
				cnt = 0;
			}
			else
				cnt = 0;

			if(buf[i] == '1')
				cond = 1;
			else
				cond = 0;
		}
		row++;
	}

	fclose(fin);
	fclose(fout);

	return 0;
}