#ifndef YELLIN_WRAP_H
#define YELLIN_WRAP_H

#include <stdbool.h>

extern unsigned char _binary_CMaxf_in_start;
extern unsigned char _binary_CMaxf_in_end;
extern unsigned char _binary_CMaxf_in_size;

extern unsigned char _binary_CMaxfLow_in_start;
extern unsigned char _binary_CMaxfLow_in_end;
extern unsigned char _binary_CMaxfLow_in_size;

extern unsigned char _binary_CMaxfLowNew_in_start;
extern unsigned char _binary_CMaxfLowNew_in_end;
extern unsigned char _binary_CMaxfLowNew_in_size;

extern unsigned char _binary_y_vs_CLf_in_start;
extern unsigned char _binary_y_vs_CLf_in_end;
extern unsigned char _binary_y_vs_CLf_in_size;

extern unsigned char _binary_ymintable_in_start;
extern unsigned char _binary_ymintable_in_end;
extern unsigned char _binary_ymintable_in_size;

extern unsigned char _binary_CLtable_txt_start;
extern unsigned char _binary_CLtable_txt_end;
extern unsigned char _binary_CLtable_txt_size;

extern unsigned char _binary_CLtableNew_in_start;
extern unsigned char _binary_CLtableNew_in_end;
extern unsigned char _binary_CLtableNew_in_size;

extern float upperlim_(float*, int*, int*,float*,float*,float*,int*);

extern void usenewconfl_(bool*);
extern void usenewcmax_(bool*);

char *templatetmp;
char* yellin_init();
int yellin_end();

float upperlim(float cl, int If, int n, float *cdfevt, float muB, float *cdfB, int *Iflag, bool usenew);

#endif