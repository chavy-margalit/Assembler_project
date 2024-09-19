#include "openextern.h"


void write_to_extern_file(FILE * ifp, char * file_name)
{
	char line[MAX_LINE];
	char * token;
	char * word;
	long beg;/*will hold beggining position of ofp*/
	FILE * ofp;
	strcat(file_name, ".ext");
	ofp = fopen(file_name, "w");/* create new file for writing*/
	fseek(ifp,0,SEEK_SET);
	
	if (ofp == NULL) 
	{ 
		printf("Failed to open file.\n");
		return;
	}
	else
	{
		while (fgets(line, sizeof(line), ifp)) /*while not end of file*/
		{
			char copy[MAX_LINE];
			token = NULL;
			strcpy(copy, line);
			token = strtok(copy, " ,\n\t");
			if(token != NULL)
			{
				if(strcmp(token, ".extern") == 0)/* if is extern line*/
				{
					token = strtok(NULL, " ,\n\t");/*isolate label name after '.extern' */
					word = token;
					find_the_words(word, ifp, ofp);/* find uses of label*/
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
}


void find_the_words(char *word, FILE *ifp, FILE *ofp)
{
    char *took;
    long pos = ftell(ifp); /* saves previous position of ifp to find next label in previous function */
    char line[MAX_LINE];
    char copy[MAX_LINE];
    int line_num = -1; /* Counts the number of lines with code */
    int word_num = 0;
    int actual_line_num = -1; /* Counts the actual line numbers in the file */
    fseek(ifp, 0, SEEK_SET);
    while (fgets(line, sizeof(line), ifp)) /* pass on line line */
    {
        actual_line_num++;
        word_num = 0;
        strcpy(copy, line);
        took = strtok(copy, " ,\n\t");

        /* Skip lines with directives such as .extern, .entry, etc. */
        if (took != NULL && (strcmp(took, ".extern") == 0 || strcmp(took, ".entry") == 0 || strcmp(took, ".data") == 0 || strcmp(took, ".string") == 0))
        {
            continue; /* Skip the line and move to the next one */
        }

        /* Only increment line_num for lines containing code */
        line_num++;

        while (took != NULL)
        {
            if (strcmp(took, word) == 0) /* if label use found, print name and address to extern file */
            {
                fprintf(ofp, "%s\t", word);
                fprintf(ofp, "%d\n", (codes[line_num].address + word_num));
            }
            took = strtok(NULL, " ,\n\t");
            word_num++;
        }
    }
    fseek(ifp, pos, SEEK_SET);
}
