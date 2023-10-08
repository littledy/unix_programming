#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LINE_LEN 1024
#define MAX_NUMBER_COUNT 20
#define MAX_NUMBER 100

extern 


int num_count, file_line_count;
FILE *freader;

int count_line(char *fname) {
	FILE *fp = fopen(fname, "r");
	if (fp == NULL) {
		perror("fopen");
		return -1;
	}
	
	int line_count = 0;
	char line[MAX_LINE_LEN];
	
	while (fgets(line, MAX_LINE_LEN, fp) != NULL) {
		++line_count;
	}
	
	fclose(fp);
	return line_count;
}

int generate_random_int(char *fname) {
	int i, n;
	srand((unsigned)time(NULL));
	FILE *fp;
	int count = 0;
	fp = fopen(fname, "w");
	if (fp == NULL) {
		printf("Failed to open file.\n");
		return 1;
	}
	
	for (i=0; i<MAX_NUMBER_COUNT; ++i) {
		n = rand() % MAX_NUMBER;
		fprintf(fp, "%d", n);
		if (i == MAX_NUMBER_COUNT-1) {
			break;
		}
		fprintf(fp, "\n");
		count++;
	}
	fclose(fp);
	printf("Integer writtern to file.\n");
	
	return count;
}

int* read_from_file(char *fname) {
	freader = fopen(fname, "r");
	int buf_size = count_line(fname);
	int n;
	int index = 0;
	char line[MAX_LINE_LEN];
	if (buf_size == -1) {
		return NULL;
	}
	
	int *input = (int*)malloc(buf_size*sizeof(int));
	while (fgets(line, MAX_LINE_LEN, freader) != NULL) {
		sscanf(line, "%d", &n);
		input[index++] = n;
	}
	fclose(freader);
	return input;
}	

int main() {
	char *file_name = "integer_to_sort.txt";
	generate_random_int(file_name);
	int *nums = read_from_file(file_name);
	
	return 0;
}
