#include "output.h"


void write_to_output_file(char * file_name)
{
	FILE * ofp;
	long beg;/*will hold beggining position of ofp*/
	strcat(file_name, ".ob");
	ofp = fopen(file_name, "w"); 	
	if(ofp == NULL) 
	{ 
		printf("Failed to open file.\n");
		return;
	}
	else
	{
		int i = 0;
		int j = 0;
		if(IC + DC > 3996) 
		{
			fprintf(stderr, "ERROR - no allocation\n");
		}
		fprintf(ofp, "   %d %d\n", IC, DC);
		while(codes[i].code_line != NULL)/* while still code to print */
		{
			j = 0;
			for(j = 0; j < codes[i].num_of_words; j++)
			{
				if(((codes[i].address) + j) < 1000)
				{	
					fprintf(ofp, "0%d  ", (codes[i].address) + j);
					printOctal(codes[i].code_line[j], ofp);
				}

				else
				{	
					fprintf(ofp, "%d  ", (codes[i].address) + j);
					printOctal(codes[i].code_line[j], ofp);
				}
			}
			i++;
		}
		for(i = 0; i < DC; i++)
		{
			if((IC + 100 + i) < 1000)
			{
				fprintf(ofp, "0%d  ", (IC + 100 + i));
				printOctal(data_table[i], ofp);
			}

			else
			{
				fprintf(ofp, "%d  ", (IC + 100 + i));
				printOctal(data_table[i], ofp);
			}
		}
	}
	fseek(ofp, 0, SEEK_SET);
	beg = ftell(ofp);
	fseek(ofp, 0, SEEK_END);
	if(beg == ftell(ofp))
	{
		remove(file_name);
	}
	fclose(ofp);
}


void printOctal(short num, FILE *ofp)
{
	int i;
	unsigned short decimal = (unsigned short)num; /*Convert the input number to an unsigned short*/
	char octal_str[6]; /*Buffer to hold the octal representation*/
	int index = 0;

	if (decimal == 0) 
	{
     	   octal_str[index++] = '0'; /*Special case for zero*/
	}	

	else 
	{
		while (decimal > 0) /*Convert decimal to octal*/
		{
			octal_str[index++] = '0' + (decimal % 8); /*Append the current octal digit*/
			decimal /= 8; /*Reduce the number*/
		}
	}

	while (index < 5) /*Fill remaining space with '0's to ensure a length of 5*/
	{
		octal_str[index++] = '0'; 
	}

	octal_str[index] = '\0'; /*Null-terminate the string*/

	for (i = 4; i >= 0; i--) /*Print the octal representation in reverse order*/
	{
		fprintf(ofp, "%c", octal_str[i]);
    	}
	fprintf(ofp, "\n"); /*Newline after printing*/
}
