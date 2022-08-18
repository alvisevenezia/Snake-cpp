#include "csv_utils.h"
#include "fstream"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <sys/stat.h>  

void writeCSVFile(const char* fileToWrite,float* buffer,int intToWrite,int mapSize,int step){

    FILE* file = fopen(fileToWrite,"a");

    if(file == NULL){

        std::cout<<"..."<<std::endl;
        return;
    }
    std::string s = "step"+std::to_string(step)+"\n";
    fputs(s.c_str(),file);

    for(int id = 0; id< intToWrite;id++){

        switch ((char)buffer[id])
        {
        case -1:
            fputc('p',file);
            break;
        
        case 0:
            fputc('_',file);
            break;

        case 1:
            fputc('H',file);    
            break;

        default :
            fputc('c',file);
            break;
        }

        if((id+1) % mapSize == 0) fputc('\n',file);

    }

    fputc('\n',file);
    fclose(file);
   
}