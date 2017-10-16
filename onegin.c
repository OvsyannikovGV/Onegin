#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void AlphSort(const size_t poemlines);
void OnegSort(const size_t poemlines);
int strcmpRev (const void * str1, const void * str2);
int strcmpEdt (const void * str1, const void * str2);
int isletter (const char * c);
size_t my_strlen (const char * str);
size_t clearinput ();

int main () {
	printf("#  STRING SORTER 5000\n");
	printf("# (c) Gleb Ovsyannikoff 2017\n\n");

	size_t poemlines = clearinput () + 1;
	fprintf(stdout, "number of lines = %lld\n", poemlines);
	AlphSort (poemlines);
	OnegSort (poemlines);
	return 0;
}

void AlphSort(const size_t poemlines){

	fprintf (stdout, "starting Alphabet sorting...\n");

	size_t i = 0, j = 0;
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

	for (i = 0; i < sizeoffile; i++) {
		*((char *)pointstr[0] + i) = fgetc(input);
		if (*((char *)pointstr[0] + i) == '\n') {
			j++;
			pointstr[j] = (void *)((char *)pointstr[0] + i + 1);
		}
	}

	for (i = 0; i < poemlines; i++) {
		for (j = i + 1; j < poemlines; j++) {
			if (strcmpEdt((char *)pointstr[i], (char *)pointstr[j]) > 0) {
				temp = pointstr[i];
				pointstr[i] = pointstr[j];
				pointstr[j] = temp;
			}
		}
	}

	for (i = 0; i < poemlines - 1; i++){
		if (my_strlen((char *)pointstr[i])) {
			j = 0;
			while (*((char *) pointstr[i] + j) != '\n') {
				fputc(*((char *) pointstr[i] + j), output);
				j++;
			}
			fprintf(output, "\n");
		}
	}

	fprintf (stdout, "Alphabet sorting is finished!\n");

	free(begin);
	fclose (input);
	fclose (output);
}

void OnegSort (const size_t poemlines) {

	fprintf (stdout, "starting Rhythm sorting...\n");

	size_t i = 0, j = 0;
	size_t sizeoffile;
	void * pointstr[poemlines];
	void * temp;
	void * begin;

	FILE *input = fopen ("input.txt", "r");
	FILE *output = fopen ("RythmSort.txt", "w");

	fseek (input, 0, SEEK_END); //end of file
	sizeoffile = ftell(input);  //position in file
	fseek (input, 0, SEEK_SET); //return to the beginning

	begin = calloc(sizeoffile, sizeof(char));
	pointstr[0] = begin;

	for (i = 0; i < sizeoffile; i++) {
		*((char *)pointstr[0] + i) = fgetc(input);
		if (*((char *)pointstr[0] + i) == '\n') {
			j++;
			pointstr[j] = (void *)((char *)pointstr[0] + i + 1);
		}
	}

	for (i = 0; i < poemlines - 1; i++) {
		for (j = i + 1; j < poemlines - 1; j++) {
			if (strcmpRev((char *)pointstr[i], (char *)pointstr[j]) > 0) {
				temp = pointstr[i];
				pointstr[i] = pointstr[j];
				pointstr[j] = temp;
			}
		}
	}

	for (i = 0; i < poemlines - 1; i++){
		if (my_strlen((char *)pointstr[i])) {
			j = 0;
			while (*((char *) pointstr[i] + j) != '\n') {
				fputc(*((char *) pointstr[i] + j), output);
				j++;
			}
			fprintf(output, "\n");
		}
	}

	fprintf (stdout, "Rhythm sorting is finished!\n");

	free(begin);
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

	size_t str1len = my_strlen((char *)str1), str2len = my_strlen((char *)str2);

	void * strr1 = calloc(str1len + 1, sizeof(char)),
			* strr2 = calloc(str2len + 1, sizeof(char));

	while (i < str1len) {
		*((char *)strr1 + i) = *((char *)str1 + str1len - 1 - i);
		i++;
	}
	*((char *)strr1 + i) = '\n';
	i = 0;

	while (j < str2len) {
		*((char *) strr2 + j) = *((char *) str2 + str2len - 1 - j);
		j++;
	}
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
	if (!ispunct(*c) && !isspace(*c) && !isdigit(*c))
		return 1;
	return 0;
}

size_t my_strlen (const char * str) {
	size_t i = 0;
	while (*(str + i) != '\n')
		i++;
	return i;
}

size_t clearinput () {
	size_t i = 0, n = 0, poemlines = 0;
	FILE * input = fopen ("ishodny_text.txt", "rb");
	FILE * output = fopen ("input.txt", "wb");
	size_t sizeoffile;
	int flag = 0;
	char buf = 0;

	fseek (input, 0, SEEK_END);
	sizeoffile = ftell(input);
	fprintf(stdout, "size of file = %lld\n", sizeoffile);
	fseek (input, 0, SEEK_SET);

	buf = getc(input);

	for (n = 0; n < sizeoffile; n++) {
		while (buf == ' ' && flag == 0) {// delete spaces in line before text
			buf = getc(input);
			n++;
		}
		flag = 1;
		if (buf == '{') {// delete author comments
			while (buf != '}') {
				buf = getc(input);
				n++;
			}
			buf = getc(input);
			n++;
		}
		if (buf == '\n') {
			flag = 0;
			poemlines++;
		}
		fprintf(output, "%c", buf);
		i++;
		buf = getc(input);
	}

	fclose (input);
	fclose (output);
	return poemlines;
}
