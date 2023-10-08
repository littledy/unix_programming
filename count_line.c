#include <stdio.h>

#define MAX_LINE_LEN 1024

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		return 1;
	}
	
	FILE *fp = fopen(argv[1], "r");
	if (fp == NULL) {
		perror("fopen");
		return 1;
	}
	
	int line_count = 0;
	char line[MAX_LINE_LEN];
	
	while (fgets(line, MAX_LINE_LEN, fp) != NULL) {
		++line_count;
	}
	
	fclose(fp);
	
	printf("The file %s has %d lines.\n", argv[1], line_count);
	
	return 0;
}
