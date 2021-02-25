#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int fileToBuffer(char**, const char*);


int main(void) {
	char file_name[20] = "studenti_kafici.txt";
	char* buffer = NULL;
	int check = 0;

	check = fileToBuffer(&buffer, file_name);

	if (check == -1) {
		puts("Zaustavljanje programa");
		free(buffer);
		return -1;
	}

	printf("\n%s\n", buffer);

	free(buffer);
	buffer = NULL;

	return 0;
}


int fileToBuffer(char** buffer, const char* file_name) {

	int file_size = 0;
	FILE* fp = NULL;

	if (!file_name) {
		fputs("Neuspjesno proslijedeno ime datoteke!\n", stderr);
		return -1;
	}

	fp = fopen(file_name, "rb");

	if (!fp) {
		perror("fopen() failed");
		return -1;
	}

	if (fseek(fp, 0L, SEEK_END)) {
		perror("fseek() ");
		fclose(fp);
		return -1;
	}

	file_size = ftell(fp);

	if (file_size == -1L) {
		perror("ftell() ");
		fclose(fp);
		return -1;
	}

	if (fseek(fp, 0L, SEEK_SET)) {
		perror("fseek() ");
		fclose(fp);
		return -1;
	}

	*buffer = (char*)calloc(sizeof(char), file_size + 1);

	if (!*buffer) {
		perror("calloc() ");
		fclose(fp);
		return -1;
	}

	if (fread(*buffer, 1, file_size, fp) != file_size) {
		perror("fread() ");
		fclose(fp);

		return -1;
	}

	if (fclose(fp)) {
		perror("fclose() ");
		return -1;
	}

	return file_size;
}
