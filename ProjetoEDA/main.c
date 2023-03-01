#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ficheiros.h"

int main() {
	FILE* txt;
	Meio* meios = NULL;

	txt = fopen("meios.bin", "rb");
	meios = pegarregistromeios(meios, txt);
	fclose(txt);

	txt = fopen("meios.bin", "wb");
	escrevertxtmeios(meios, txt);
	fclose(txt);

	return 1;
}