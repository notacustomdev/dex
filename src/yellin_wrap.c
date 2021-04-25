#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#include "yellin_wrap.h"

/*create temporary folder with yellin data and return it's path*/
char* yellin_init(char *template){
    templatetmp = (char*)malloc(strlen("/tmp/yellinXXXXXX")+1);
    strcpy(templatetmp, "/tmp/yellinXXXXXX");
    mkdtemp(templatetmp);
    /*file name with max, 20 is bigger than all yellin filenames*/
    char *fname = (char*) malloc(strlen(templatetmp)+20);
    /*successfully created tmp folder, copy data from symbols*/
    if(templatetmp){
        strcpy(fname, templatetmp);
        strcat(fname, "/");
        strcat(fname, "CLtable.txt");
        FILE *f = fopen(fname, "wb");
        if(!f){
            printf("Error creating %s\n", fname);
            free(fname);
            return 0;
        }
       
        fwrite(&_binary_CLtable_txt_start,  &_binary_CLtable_txt_end - &_binary_CLtable_txt_start, 1, f);
        fclose(f);

        strcpy(fname, templatetmp);
        strcat(fname, "/");
        strcat(fname, "CLtableNew.in");
        f = fopen(fname, "wb");
        if(!f){
            printf("Error creating %s\n", fname);
            free(fname);
            return 0;
        }
        fwrite(&_binary_CLtableNew_in_start, &_binary_CLtableNew_in_end - &_binary_CLtableNew_in_start, 1, f);
        fclose(f);

        strcpy(fname, templatetmp);
        strcat(fname, "/");
        strcat(fname, "CMaxf.in");
        f = fopen(fname, "wb");
        if(!f){
            printf("Error creating %s\n", fname);
            free(fname);
            return 0;
        }
        fwrite(&_binary_CMaxf_in_start, &_binary_CMaxf_in_end - &_binary_CMaxf_in_start, 1, f);
        fclose(f);

        strcpy(fname, templatetmp);
        strcat(fname, "/");
        strcat(fname, "CMaxfLow.in");
        f = fopen(fname, "wb");
        if(!f){
            printf("Error creating %s\n", fname);
            free(fname);
            return 0;
        }
        fwrite(&_binary_CMaxfLow_in_start, &_binary_CMaxfLow_in_end - &_binary_CMaxfLow_in_start, 1, f);
        fclose(f);

        strcpy(fname, templatetmp);
        strcat(fname, "/");
        strcat(fname, "CMaxflowNew.in");
        f = fopen(fname, "wb");
        if(!f){
            printf("Error creating %s\n", fname);
            free(fname);
            return 0;
        }
        fwrite(&_binary_CMaxfLowNew_in_start, &_binary_CMaxfLowNew_in_end - &_binary_CMaxfLowNew_in_start, 1, f);
        fclose(f);

        strcpy(fname, templatetmp);
        strcat(fname, "/");
        strcat(fname, "y_vs_CLf.in");
        f = fopen(fname, "wb");
        if(!f){
            printf("Error creating %s\n", fname);
            free(fname);
            return 0;
        }
        fwrite(&_binary_y_vs_CLf_in_start, &_binary_y_vs_CLf_in_end - &_binary_y_vs_CLf_in_start, 1, f);
        fclose(f);

        strcpy(fname, templatetmp);
        strcat(fname, "/");
        strcat(fname, "ymintable.in");
        f = fopen(fname, "wb");
        if(!f){
            printf("Error creating %s\n", fname);
            free(fname);
            return 0;
        }
        fwrite(&_binary_ymintable_in_start, &_binary_ymintable_in_end - &_binary_ymintable_in_start, 1, f);
        fclose(f);

    }
    return templatetmp;
}

int yellin_end(){

    char *fname = (char*) malloc(strlen(templatetmp)+20);

    /*successfully created tmp folder, copy data from symbols*/
    
    strcpy(fname, templatetmp);
    strcat(fname, "/");
    strcat(fname, "CLtable.txt");
    
    if(unlink(fname)<0){
        printf("Error %d: %s\n", errno, strerror(errno));
        free(fname);
        return -1;
    }
   
    strcpy(fname, templatetmp);
    strcat(fname, "/");
    strcat(fname, "CLtableNew.in");
    
    if(unlink(fname)<0){
        printf("Error %d: %s\n", errno, strerror(errno));
        free(fname);
        return -1;
    }
        
    strcpy(fname, templatetmp);
    strcat(fname, "/");
    strcat(fname, "CMaxf.in");
    
    if(unlink(fname)<0){
        printf("Error %d: %s\n", errno, strerror(errno));
        free(fname);
        return -1;
    }

    strcpy(fname, templatetmp);
    strcat(fname, "/");
    strcat(fname, "CMaxfLow.in");

    if(unlink(fname)<0){
        printf("Error %d: %s\n", errno, strerror(errno));
        free(fname);
        return -1;
    }

    strcpy(fname, templatetmp);
    strcat(fname, "/");
    strcat(fname, "CMaxflowNew.in");
    
    if(unlink(fname)<0){
        printf("Error %d: %s\n", errno, strerror(errno));
        free(fname);
        return -1;
    }
    
    strcpy(fname, templatetmp);
    strcat(fname, "/");
    strcat(fname, "y_vs_CLf.in");
    
    if(unlink(fname)<0){
        printf("Error %d: %s\n", errno, strerror(errno));
        free(fname);
        return -1;
    }

    strcpy(fname, templatetmp);
    strcat(fname, "/");
    strcat(fname, "ymintable.in");
    
    if(unlink(fname)<0){
        printf("Error %d: %s\n", errno, strerror(errno));
        free(fname);
        return -1;
    }

    int res = rmdir(templatetmp);
    free(fname);
    free(templatetmp);
    return res;
}

float upperlim(float cl, int If, int n, float *cdfevt, float muB, float *cdfB, int *Iflag, bool usenew){
    char cwd[PATH_MAX];

    getcwd(cwd, sizeof(cwd));

    chdir(templatetmp);

    usenewcmax_(&usenew);
    usenewconfl_(&usenew);

    float res = upperlim_(&cl, &If, &n, cdfevt, &muB, cdfB, Iflag);

    chdir(cwd);

    return res;
}