#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void AlphSort(const long poemlines);
void OnegSort(const long poemlines);
int strcmpRev (const void * str1, const void * str2);
int strcmpEdt (const void * str1, const void * str2);
int isletter (const char * c);
size_t my_strlen (const char * str);
long clearinput ();

int main () {
	printf("#  STRING SORTER 5000\n");
	printf("# (c) Gleb Ovsyannikoff 2017\n\n");

	long poemlines = clearinput ();
	fprintf(stdout, "%ld\n", poemlines);
	//AlphSort (poemlines);
	//OnegSort (poemlines);
	return 0;
}

void AlphSort(const long poemlines){

	int i = 0, j = 0, n = 0;
	size_t sizeoffile;
	void * pointstr[poemlines];
	void * temp;
	void * begin;

	FILE *input = fopen ("input.txt", "r");
	FILE *output = fopen ("AlphSort.txt", "w");

	fseek (input, 0, SEEK_END); //end of file
	sizeoffile = ftell(input);  //position in file
	fseek (input, 0, SEEK_SET); //return to the beginning

	begin = calloc(sizeoffile, sizeof(char));
	pointstr[0] = begin;

	j = 0;
	for (i = 0; i < sizeoffile; i++) {
		*((char *)pointstr[0] + i) = fgetc(input);
		if (*((char *)pointstr[0] + i) == '\n') {
			j++;
			pointstr[j] = (void *)((char *)pointstr[0] + i + 1);
		}
	}
	j++;

	n = j;

	for (i = 0; i < n; i++) {
		for (j = i + 1; j < n; j++) {
			if (strcmpEdt((char *)pointstr[i], (char *)pointstr[j]) > 0) {
				temp = pointstr[i];
				pointstr[i] = pointstr[j];
				pointstr[j] = temp;
			}
		}
	}

	for (i = 0; i < n - 1; i++){
		if (my_strlen((char *)pointstr[i])) {
			j = 0;
			while (*((char *) pointstr[i] + j) != '\n') {
				fputc(*((char *) pointstr[i] + j), output);
				j++;
			}
			fprintf(output, "\n");
		}
	}

	free(begin);
	fclose (input);
	fclose (output);
}

void OnegSort (const long poemlines) {

	int i = 0, j = 0, n = 0;
	size_t sizeoffile;
	void * pointstr[poemlines];
	void * temp;
	void * begin;

	FILE * input = fopen ("input.txt", "r");
	FILE * output = fopen ("RythmSort.txt", "w");

	fseek (input, 0, SEEK_END); //end of file
	sizeoffile = ftell(input);  //position in file
	fseek (input, 0, SEEK_SET); //return to the beginning

	begin = calloc(sizeoffile, sizeof(char));
	pointstr[0] = begin;

	j = 0;
	for (i = 0; i < sizeoffile - 1; i++) {//writing into the memory
		*((char *)pointstr[0] + i) = fgetc(input);
		if (*((char *)pointstr[0] + i) == '\n') {
			j++;
			pointstr[j] = (void *)((char *)pointstr[0] + i + 1);
		}
	}
	j++;

	n = j;

	for (i = 0; i < n - 1; i++) {
		for (j = i + 1; j < n - 1; j++) {
			if (strcmpRev((char *)pointstr[i], (char *)pointstr[j]) > 0) {
				temp = pointstr[i];
				pointstr[i] = pointstr[j];
				pointstr[j] = temp;
			}
		}
	}

	for (i = 0; i < n - 1; i++) {
		if (my_strlen((char *)pointstr[i])) {
			j = 0;
			while (*((char *) pointstr[i] + j) != '\n') {
				fputc(*((char *) pointstr[i] + j), output);
				j++;
			}
			fprintf(output, "\n");
		}
	}

	free (begin);
	fclose (input);
	fclose (output);
}

int strcmpEdt (const void * str1, const void * str2) {

	int i = 0, j = 0;

	while (!isletter((char *)str1 + i))
		i++;
	while (!isletter((char *)str2 + j))
		j++;
	return strcasecmp((char *)str1 + i, (char *)str2 + j);
}

int strcmpRev (const void * str1, const void * str2) {

	int i = 0, j = 0, result = 0;

	size_t strlen1 = my_strlen((char *)str1), strlen2 = my_strlen((char *)str2);

	void * strr1 = calloc(strlen1, sizeof(char)),
			* strr2 = calloc(strlen2, sizeof(char));

	for (i = 0; i < strlen1 - 1; i++)
		*((char *)strr1 + i) = *((char *)str1 + strlen1 - i - 1);
	*((char *)strr1 + i) = '\n';
	i = 0;
	for (j = 0; j < strlen2 - 1; j++)
		*((char *)strr2 + j) = *((char *)str2 + strlen2 - j - 1);
	*((char *)strr2 + j) = '\n';
	j = 0;

	while (!isletter((char *)(strr1 + i)))
		i++;
	while (!isletter((char *)(strr2 + j)))
		j++;
	result = strcasecmp((char *)(strr1 + i), (char *)(strr2 + j));
	free(strr1);
	free(strr2);
	return result;
}

int isletter (const char * c) {
	if (!ispunct(*c) && !isspace(*c))
		return 1;
	return 0;
}

size_t my_strlen (const char * str) {
	size_t i = 0;
	while (*(str + i) != '\n')
		i++;
	return i;
}

long clearinput () {
	long i = 0, n = 0, poemlines = 0;
	FILE * input = fopen ("ishodny_text.txt", "r");
	FILE * output = fopen ("input.txt", "w");
	size_t sizeoffile;
	void * begin, * begin1;
	int flag = 0;
	char buf = ' ';

	fseek (input, 0, SEEK_END); //end of file
	sizeoffile = ftell(input);  //position in file
	fprintf(stdout, "size of file = %lld\n", sizeoffile);
	fseek (input, 0, SEEK_SET); //return to the beginning

	begin = calloc(sizeoffile, sizeof(char));

	for (n = -1; n < sizeoffile; n++) {
		while (buf == ' ' && flag == 0) {
			fprintf(stdout, "%ld", n);
			buf = getc(input);
			n++;
		}
		flag = 1;
		if (buf == '{') {
			while (buf != '}') {
				buf = getc(input);
				n++;
			}
		}
		if (buf == '\n') {
			flag = 0;
			poemlines++;
		}
		*((char *)begin + i) = buf;
		i++;
	}

	free(begin);
	fclose (input);
	fclose (output);
	return poemlines;
}
