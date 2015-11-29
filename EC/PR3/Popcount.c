//gcc -Wall -m32 -O1 -fno-omit-frame-pointer popcount.c -o popcount

#include <stdio.h>      // para printf()
#include <stdlib.h>     // para exit()
#include <sys/time.h>   // para gettimeofday(), struct timeval
#define TEST                0
#define COPY_PASTE_CALC     1

#if ! TEST
    #define NBITS 20
    #define SIZE (1<<NBITS)
    unsigned lista[SIZE];
    #define RESULT (1<<NBITS-1)
#else
/* ------------------------------------------------------------------------------- * /
	#define SIZE 4
	unsigned lista[SIZE]={0x80000000, 0x00100000, 0x00000800, 0x00000001};
	#define RESULT 4
/* ------------------------------------------------------------------------------- * /
	#define SIZE 8
	unsigned lista[SIZE]={0x7fffffff, 0xffefffff, 0xfffff7ff, 0xfffffffe,
						  0x01000024, 0x00357600, 0x8900ac00, 0x00bd00ef};
	#define RESULT 156
/* ------------------------------------------------------------------------------- * /
	#define SIZE 8
	unsigned lista[SIZE]={0x0       , 0x10204080, 0x3590ac06, 0x70b0d0e0,
						  0xffffffff, 0x12345678, 0x9abcdef0, 0xcafebeef};
	#define RESULT 116
/* ------------------------------------------------------------------------------- */
#endif

int resultado = 0;

/* ------------------------------------------------------------------------------- */

int popcount1(unsigned* array, int len) {
    int i, j, res = 0;
    unsigned x;
    int val;
    for(i=0; i<len; i++){
        for(j=0; j<8*sizeof(unsigned); j++){
            unsigned mask = 1 << j;
            res += (array[i] & mask) != 0;
        }
    }
    return res;
}

/* ------------------------------------------------------------------------------- */

int popcount2(unsigned* array, int len) {
    int res = 0, i;
    unsigned x;
    int val;
    for (i = 0; i < len; i++) {
        x = array[i];
        while(x){
            res += x & 0x1;
            x >>= 1;
        }
    }
    return res;
}

/* ------------------------------------------------------------------------------- */

int popcount3(unsigned* array, int len) {
    int res = 0, i;
    unsigned x;
    for (i = 0; i < len; i++) {
        x = array[i];
        asm(
            "bucle:\n"
            "shr $0x1, %[x]\n"
            "adc $0x0, %[r]\n"
            "cmp $0x0, %[x]\n"
            "jne bucle \n"
            :[r] "+r" (res)
            :[x] "r" (x)
        );
    }
    return res;
}

/* ------------------------------------------------------------------------------- */


// Versión C de CS:APP

int popcount4(unsigned* array, int len) {
    int i, k;
    int result = 0;
    for (i = 0; i < len; i++) {
        int val = 0;
        unsigned x = array[i];
        for (k = 0; k < 8; k++) {
            val += x & 0x01010101; //00000001 00000001 00000001 00000001
            x >>= 1;
        }
        //val += (val >> 32);
        val += (val >> 16);
        val += (val >> 8);
        result += (val & 0xff);
    }
    return result;
}

/* ------------------------------------------------------------------------------- */

 // Versión SSSE3

int popcount5(unsigned* array, int len) {
    int i;
    int val, result = 0;
    int SSE_mask[] = { 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f };
    int SSE_LUTb[] = { 0x02010100, 0x03020201, 0x03020201, 0x04030302 };

    if (len & 0x3)
        printf("leyendo 128b pero len no múltiplo de 4?\n");
    for (i = 0; i < len; i += 4)
    {
        asm("movdqu        %[x], %%xmm0 \n\t"
            "movdqa  %%xmm0, %%xmm1 \n\t"
            "movdqu    %[m], %%xmm6 \n\t"
            "psrlw           $4, %%xmm1 \n\t"
            "pand    %%xmm6, %%xmm0 \n\t"
            "pand    %%xmm6, %%xmm1 \n\t"

            "movdqu    %[l], %%xmm2 \n\t"
            "movdqa  %%xmm2, %%xmm3 \n\t"
            "pshufb  %%xmm0, %%xmm2 \n\t"
            "pshufb  %%xmm1, %%xmm3 \n\t"

            "paddb   %%xmm2, %%xmm3 \n\t"
            "pxor    %%xmm0, %%xmm0 \n\t"
            "psadbw  %%xmm0, %%xmm3 \n\t"
            "movhlps %%xmm3, %%xmm0 \n\t"
            "paddd   %%xmm3, %%xmm0 \n\t"
            "movd    %%xmm0, %[val] \n\t"
            : [val]"=r" (val)
            : [x] "m" (array[i]),
            [m] "m" (SSE_mask[0]),
            [l] "m" (SSE_LUTb[0])
            );
            result += val;
    }
    return result;
}

/* ------------------------------------------------------------------------------- */

int popcount6(unsigned* array, int len) {
    int i;
    unsigned x;
    int val, result = 0;
    for (i = 0; i < len; i++) {
        x = array[i];
        asm("popcnt %[x], %[val]        \n\t"
            : [val]"=r"(val)
            : [x] "r" (x)
        );
        result += val;
    }
    return result;
}

/* ------------------------------------------------------------------------------- */

int popcount7(unsigned* array, int len) {
    int i;
    unsigned x1, x2;
    int val, result = 0;
    if (len & 0x1)
        printf("Leer 64b y len impar?n");
    for (i = 0; i < len; i += 2) {
        x1 = array[i];
        x2 = array[i + 1];
        asm("popcnt %[x1], %[val]       \n\t"
            "popcnt %[x2], %%edi    \n\t"
            "add    %%edi, %[val]   \n\t"
            : [val]"=r"(val)
            : [x1] "r" (x1),
            [x2] "r" (x2)
            : "edi"
        );
        result += val;
    }
    return result;
}

/* ------------------------------------------------------------------------------- */

void crono(int (*func)(), char* msg) {
    struct timeval tv1, tv2; // gettimeofday() secs-usecs
    long tv_usecs; // y sus cuentas

    gettimeofday(&tv1, NULL);
    resultado = func(lista, SIZE);
    gettimeofday(&tv2, NULL);

    tv_usecs=(tv2.tv_sec -tv1.tv_sec)*1E6+
             (tv2.tv_usec-tv1.tv_usec);

#if COPY_PASTE_CALC
    printf("%ld" "\n", tv_usecs);
#else
    printf("resultado = %d\t", resultado);
    printf("%s:%9ld us\n", msg, tv_usecs);
#endif
}

int main() {

#if ! TEST
    int i;                      // inicializar array
    for (i = 0; i < SIZE; i++)  // se queda en cache
        lista[i] = i;
#endif

    crono(popcount1, "popcount1 (    en lenguaje C for  )");
    crono(popcount2, "popcount2 (    en lenguaje C whi  )");
    crono(popcount3, "popcount3 (    Ahorrando máscara  )");
    crono(popcount4, "popcount4 (Sumando bytes completos)");
    crono(popcount5, "popcount5 (        SSSE3          )");
    crono(popcount6, "popcount6 (        SSSE4.2        )");
    crono(popcount7, "popcount7 (        SSSE4.2 64b    )");

#if ! COPY_PASTE_CALC
    printf("calculado = %d\n", RESULT);
#endif

    exit(0);
}
