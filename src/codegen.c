#include "codegen.h"
#include "string.h"

int FormatAsmArray(char ** outBuffer, const unsigned char * array, 
	const int rows, const int columns, const char * name, const char * format)
{
	int j,bufcnt = 0;
	size_t length = 0;
	if ( outBuffer != NULL ) 
		length = strlen(*outBuffer);
	// TODO: according to format
	size_t outSize = columns * (5 + 4 * rows) * sizeof(char) + 100 + length;
	fprintf(stderr,"previous length = %ld, outSize = %ld \n", length, outSize );

	*outBuffer = (char*) realloc(*outBuffer,outSize);
	if (*outBuffer == NULL)
	{
		perror(":realloc");
		return 0;
	}
	else fprintf(stderr,"realloc ok\n" );

	const unsigned char * parray = array;

	char *localPointer = *outBuffer + length;
	fprintf(stderr, "localPointer = 0x%p\n", localPointer);

	bufcnt += sprintf(localPointer + bufcnt, "\n._%s\n",name);

	for(int i = 0; i < rows; i++)
	{
		fprintf(stderr, "defb ");
		bufcnt += sprintf(localPointer + bufcnt, "defb ");
		for( j = 0; j < columns - 1; j++)
		{
			fprintf(stderr, format, *(parray + j));
			fprintf(stderr, ",");
			bufcnt += sprintf(localPointer + bufcnt, format, *(parray + j));			
			bufcnt += sprintf(localPointer + bufcnt, ",");
		}
		fprintf(stderr, format, *(parray + j + 1));
		fprintf(stderr, "\n");
		bufcnt += sprintf(localPointer + bufcnt, format, *(parray + j + 1));
		bufcnt += sprintf(localPointer + bufcnt, "\n");
		parray += columns;
	}
	return bufcnt;
}