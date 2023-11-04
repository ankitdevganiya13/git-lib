#ifndef SPIFFS_H
#define SPIFFS_H



void SPIFFS_INIT(void);

int SPIFFS_Read(const char * filename);

int SPIFFS_Write(const char * filename,const char *filedata);

int get_file_size(const char* file_name);
int append_file(const char* file_name,const char* data);
int file_line_count(const char* file_name,int file_size );
int read_nth_line(const char* file_name,int linenumber,char *save_data);
int print_all_line(const char* file_name);
int delete_line(const char* file_name,int line_number,const char* temp_file_name) ;


#endif