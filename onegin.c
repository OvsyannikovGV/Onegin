#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

const int strln = 100;
const int poemlines = 10000;

void AlphSort();
void OnegSort();
int strcmpRev (char str1[strln], char str2[strln]);
int strcmpEdt (const void * str1, const void * str2);
int isletter (const char * c);

int main () {
    printf("#  STRING SORTER 5000\n");
    printf("# (c) Gleb Ovsyannikoff 2017\n\n");

	AlphSort ();
	//OnegSort ();
}

void AlphSort(){

    int i = 0, j = 0, n = 0;
    char str[poemlines][strln];
	void * pointstr[poemlines];
	void * temp;

	FILE *input = fopen ("input.txt", "r");
	FILE *output = fopen ("AlphSort.txt", "w");

	while (fgets (str[i], strln, input) != NULL) {
		pointstr[i] = &str[i][0];
		fprintf(stdout, "%d\n", *(unsigned char *)&str[i][0]);
		i++;
	}

	n = i;
	printf("%d\n\n", n);

	for (i = 0; i <= n - 1; i++) {
		for (j = i + 1; j < n; j++) {
			if (strcmpEdt((char *)pointstr[i], (char *)pointstr[j]) > 0) {
				temp = pointstr[i];
				pointstr[i] = pointstr[j];
				pointstr[j] = temp;
			}
		}
	}
	
	

    for (i = 0; i <= n - 1; i++){
        fputs ((char *)pointstr[i], output);
	    fprintf(stdout, "%d\n", *(unsigned char *)pointstr[i]);
    }

	fclose (input);
	fclose (output);
}

void OnegSort () {

    int i = 0, j = 0, n;
    char str[poemlines][strln], temp[strln];

	FILE *input = fopen ("input.txt", "r");
	FILE *output = fopen ("RythmSort.txt", "w");

    while (fgets(str[i], sizeof(str), input) != NULL)
	    i++;

	n = i - 1;

    for (i = 0; i <= n; i++){
        for (j = i + 1; j <= n; j++){
            if (strcmpRev(str[i], str[j]) > 0) {
                strcpy (temp, str[i]);
                strcpy (str[i], str[j]);
                strcpy (str[j], temp);
            }
        }
    }

    for (i = 0; i <= n; i++){
        fputs (str[i], output);
    }

	fclose (input);
	fclose (output);
}

int strcmpRev (char str1[strln], char str2[strln]) {

    long long int i = 0, j = 0;
	int flag = 0;

    i = strlen (str1);
    j = strlen (str2);

    while(i!=0 && j!=0){

        i--;
        j--;

        if (str1[i] == str2[j])
            flag = 0;
        else {
            if (str1[i] < str2[j])
                flag = -1;
            else
                flag = 1;
            break;
        }
    }

    return flag;
}

int strcmpEdt (const void * str1, const void * str2) {

	int i = 0, j = 0;

	while (!isletter((char *)(str1 + i)))
		i++;
	while (!isletter((char *)(str2 + j)))
		j++;
	return strcasecmp((char *)(str1 + i), (char *)(str2 + j));
}

int isletter (const char * c) {
	if (!ispunct(*c) && !isspace(*c))
		return 1;
	return 0;
}
