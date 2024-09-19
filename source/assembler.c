/*@autor: Chavy Margalit*/

#include "utils.h"
#include "macro.h"
#include "firstpass.h"
#include "improve.h"
#include "secondpass.h"
#include "openentry.h"
#include "openextern.h"
#include "output.h"
#include "validate.h"


/*This function adds ".as" ending to users file. */
void new_file_name(const char * , char *);

/*includes functions to check that file is legal and functions that
	clear unnecessary whitespaces */
FILE * check_and_fix_file(FILE *);

/*This is the main function. Users file is opened here and
	all functions are called from here.*/
int main(int argc, char * argv[])
{
	int i;
	FILE * ifp;
	FILE * ifp_am;
	FILE * ifp2;
	char * token;

	if(argc < 2)
	{
		printf("The number of arguments is not as required\n");
		return 0;
	}
	else
	{
		for (i = 1; i < argc; i++)
		{
			char file_name[30] = {0};/*holds user file name and is sent to functions(strcat used on it)*/
			char file_name1[30] = {0};/*holds file name to over write concatenated 'file_name'*/
			char new_file_name_str[30] = {0}; /*holds the new file name with .as extension*/
			token = argv[i];
			strcpy(file_name, token);
			strcpy(file_name1, file_name);
			new_file_name(token, new_file_name_str);
			ifp = fopen(new_file_name_str , "r+");
			if(ifp == NULL)
			{
				printf("Cannot open file %s, continue with next file.\n\n", token);
				return 0;
			}
		
			else
			{
				error = 0;
				ifp = add_space(ifp);
				ifp = remove_comments(ifp);
				firstpass();
				ifp_am = macros(ifp, file_name);

				if(error == 1)/* if there were errors in preprocessor*/
				{
					fprintf(stderr, "ERROR - in preprocessing. Can not compile the file\n");
					strcpy(file_name, file_name1);
					remove(strcat(file_name, ".am"));
					remove("with_space");/*delete all temporary files */
					remove("delete_comment");
					exit(1);
				}
				ifp2 = check_and_fix_file(ifp_am);
				set_array_code(ifp2);
				process_file(ifp2);
				if(error == 1)/* if errors in compilation*/
				{
					fprintf(stderr, "ERROR - can not compile the file\n");
					strcpy(file_name, file_name1);
					remove(strcat(file_name, ".ext"));
					strcpy(file_name, file_name1);
					remove(strcat(file_name, ".ent"));
					strcpy(file_name, file_name1);
					remove(strcat(file_name, ".ob"));
					remove("with_space");/*delete all temporary files */
					remove("clearmid");
					remove("delete_comment");
					remove("del_lab");			
					exit(1);
				}
				strcpy(file_name, file_name1);
				write_to_entry_file(ifp2, file_name);/*the function writing to the file px.ent the labels end the address*/
				strcpy(file_name, file_name1);
				write_to_extern_file(ifp2, file_name);
				strcpy(file_name, file_name1);
				write_to_output_file(file_name);
				remove("with_space");/*delete all temporary files */
				remove("clearmid");
				remove("delete_comment");
				remove("del_lab");			
			}
			fclose(ifp);
			fclose(ifp2);
			fclose(ifp_am);
			free(codes);
			free(data_table);
			free(labels);
		}
	}	
	return 0;
}

void new_file_name(const char * file_name, char * new_file_name_str)
{
    strcpy(new_file_name_str, file_name);
    strcat(new_file_name_str, ".as");
}


FILE * check_and_fix_file(FILE * ifp_am)
{
	FILE * ifp2;
	ifp2 = erase_white_space(ifp_am);
	ifp2 =  delete_stray_labels(ifp2);
	check_label(ifp2);
	check_multiple_colons_in_line(ifp2);
	process_data(ifp2);
	process_string(ifp2);
	process_entry(ifp2);
	process_extern(ifp2);
	process_opcode(ifp2);
	
	return ifp2;
}
