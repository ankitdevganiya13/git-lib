#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "esp_spiffs.h"
#include "esp_log.h"

#include "SPIFFS.h"


void SPIFFS_INIT(void){

    printf("Initializing SPIFFS\n");
  
  esp_vfs_spiffs_conf_t config = {
      .base_path = "/spiffs",
      .partition_label = NULL,
      .max_files = 5,
      .format_if_mount_failed = true,
  };

   esp_err_t ret = esp_vfs_spiffs_register(&config);   // config SPIFFS

       if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            printf("Failed to mount or format filesystem\n");
        } else if (ret == ESP_ERR_NOT_FOUND) {
            printf("Failed to find SPIFFS partition\n");
        } else {
            printf("Failed to initialize SPIFFS (%s)\n", esp_err_to_name(ret));
        }
        return;
    }


    #ifdef CONFIG_EXAMPLE_SPIFFS_CHECK_ON_START
    printf("Performing SPIFFS_check().");
    ret = esp_spiffs_check(config.partition_label);
    if (ret != ESP_OK) {
        printf("SPIFFS_check() failed (%s)", esp_err_to_name(ret));
        return;
    } else {
        printf("SPIFFS_check() successful");
    }
#endif


 size_t total = 0, used = 0;
    ret = esp_spiffs_info(config.partition_label, &total, &used);
    if (ret != ESP_OK) {
        printf("Failed to get SPIFFS partition information (%s). Formatting...", esp_err_to_name(ret));
        esp_spiffs_format(config.partition_label);
        return;
    } else {
        printf("Partition size: total: %d, used: %d", total, used);
    }

     // Check consistency of reported partiton size info.
    if (used > total) {
        printf("Number of used bytes cannot be larger than total. Performing SPIFFS_check().");
        ret = esp_spiffs_check(config.partition_label);


        if (ret != ESP_OK) {
            printf("SPIFFS_check() failed (%s)", esp_err_to_name(ret));
            return;
        } else {
            printf("SPIFFS_check() successful");
        }
    }


}




int SPIFFS_Read(const char * filename)
{

    printf("Opening file\r\n");

    char fileN[30];
    strcpy(fileN,"/spiffs/");
    strcat(fileN,filename);

    FILE *file = fopen(fileN, "r");
  if(file ==NULL)
  {
    printf("File does not exist!");
  }
  else 
  {
    //char line[256];

    char *line = malloc(1024 * sizeof(char));

    while(fgets(line, sizeof(line), file) != NULL)
    {
      printf(line);
    }
    fclose(file);
  }
  esp_vfs_spiffs_unregister(NULL);

    return 0;
}


int SPIFFS_Write(const char * filename,const char *filedata)
{

    printf("Creating  file:%s\r\n",filename);

    char fileN[30];
    strcpy(fileN,"/spiffs/");
    strcat(fileN,filename);

    FILE *file = fopen(fileN, "w");
  if(file ==NULL)
  {
    printf("File does not exist!");
  }
  else 
  {
    printf( "Writing data to file: %s\r\n",filename);

    fprintf(file, filedata);  // write data to txt file
    printf("\n");
    fclose(file);
    printf("File written\r\n");
    
}
return 0;
}

int get_file_size(const char* file_name)
{
    char fileN[30];
    strcpy(fileN,"/spiffs/");
    strcat(fileN,file_name);

    FILE *file = fopen(fileN, "r");

    if(file == NULL)
        return 0;

    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fclose(file);

    return size;
}


int append_file(const char* file_name,const char* data)   {

        printf( "Opening file \n");

        char fileN[30];
        strcpy(fileN,"/spiffs/");
        strcat(fileN,file_name);

        
        FILE* file = fopen(fileN, "a+");
        if (file == NULL) {
    	   printf("Failed to open file for writing \n");
    	   return 0;
       }
       fprintf(file,"%s\n",data);
       fclose(file);
       printf("File written \n");
       return 0;
}


int file_line_count(const char* file_name,int file_size )   {

        char fileN[30];
        strcpy(fileN,"/spiffs/");
        strcat(fileN,file_name);

	        FILE *f2;
	    	int count = 0; // Line counter (result)
	    	//char filename2[100]= file_name;
	    	 char c; // To store a character read from file

	    	// Open the file
	    	f2 = fopen(fileN, "r");

	    	// Check if file exists
	    	if (f2 == NULL)
	    	{
	    		printf("Could not open file %s\n", file_name);
	    		 return 0;
	    	}

	    	
	    	for (int i =0; i <file_size; i++)  {
	    		c = getc(f2);
	    		if (c == '\n')   { // Increment count if this character is newline
	    			count = count + 1;
	    			//printf("counting line %d \n",count);
	    			//break;
	    	     }
	    	}
	    	// Close the file
	    	fclose(f2);
	    	printf("The file %s has %d lines\n", file_name, count);
	    	return count;
}



int read_nth_line(const char* file_name,int line_number,char *save_data)   {

        char fileN[30];
        strcpy(fileN,"/spiffs/");
        strcat(fileN,file_name);

            FILE *f3;
            //char data[256];
    char *data = malloc(1024 * sizeof(char));

     int i = 0;
	f3 = fopen(fileN, "r");
	if(f3 == NULL)
	{
	 return 0;
	}
	    while (fgets(data, sizeof(data), f3)) {
	        i++;
	        if(i == line_number )
	        {
	            printf("selected line = %d data = %s\n",i, data);
	            strcpy(save_data,data);
	        }
	    }

	    fclose(f3);

	    return 0;

}

int print_all_line(const char* file_name)   {


        char fileN[30];
        strcpy(fileN,"/spiffs/");
        strcat(fileN,file_name);

FILE *f3;
 //char data[256];

 char *data = malloc(1024 * sizeof(char));

       	    	f3 = fopen(fileN, "r");
       	    	if(f3 == NULL){
       	    	        return 0;
       	    	}
       	    	    int i = 0;

       	    	    while (fgets(data, sizeof(data), f3)) {
       	    	        i++;
       	    	         printf("file name = %s line number = %d data = %s\n",file_name, i,data);
       	    	    }

       	    	 fclose(f3);
       	    	 return 0;

}


int delete_line(const char* file_name,int line_number,const char* temp_file_name) {

                         int ctr = 1;
    	    	         char ch;
    	    	         FILE *fptr1, *fptr2;

        char fileN[30];
        strcpy(fileN,"/spiffs/");
        strcat(fileN,file_name);

         char *str = malloc(1024 * sizeof(char));            

    	    	        // char str[256];
        printf("\n\n Delete a specific line from a file :\n");
        printf("line number to be deleted is =  %d\n",line_number);
            fptr1 = fopen(fileN, "r");
            if (fptr1 == NULL)
                    {
                        printf("Could not open file %s", file_name);
                            return 0;
                    }
            fptr2 = fopen(temp_file_name, "w"); // open the temporary file in write mode
            if (fptr2 == NULL)
            {
                printf("Could not open file %s\n", temp_file_name);
                    return 0;
            }


        line_number++;
            // copy all contents to the temporary file except the specific line
            while (!feof(fptr1))
            {
                strcpy(str, "\0");
                fgets(str, 256, fptr1);
                if (!feof(fptr1))
                {
                    ctr++;
                    /* skip the line at given line number */
                    if (ctr != line_number)
                    {
                        fprintf(fptr2, "%s", str);
                    }
                }
            }
            fclose(fptr1);
            fclose(fptr2);
            remove(file_name);  		// remove the original file

            rename(temp_file_name, file_name); 	// rename the temporary file to original name
            printf("file deleted and updated\n");
            return 0;

}

