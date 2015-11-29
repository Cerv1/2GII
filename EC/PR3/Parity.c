
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define TEST 							0
#define COPY_PASTE_CALC		1

#if ! TEST

	#define NBITS 20
	#define SIZE (1<<NBITS)
	unsigned lista[SIZE];
	#define RESULT (1<<(NBITS-1))

#else

/*-----------------------------------------------------------------------* /
	#define SIZE 4
	unsigned lista[SIZE]={0x80000000, 0x00100000, 0x00000800, 0x00000001};
	#define RESULT 4
/*-----------------------------------------------------------------------* /
	#define SIZE 8
	unsigned lista[SIZE]={0x7FFFFFFF, 0xFFEFFFFF, 0xFFFFF7FF, 0xFFFFFFFE,
						  0x01000024, 0x00356700, 0x8900AC00, 0x00BD00EF};
	#define RESULT 8
/*-----------------------------------------------------------------------* /
	#define SIZE 8
	unsigned lista[SIZE]={0x00000000, 0x10204080, 0x3590AC06, 0x70B0D0E0,
						  0xFFFFFFFF, 0x12345678, 0x9ABCDEF0, 0xCAFEBEEF};
	#define RESULT 2
/*-----------------------------------------------------------------------*/

#endif

int resultado=0;

/*-----------------------------------------------------------------------*/

int parity1(unsigned* array, int len){

    int  i, j, res=0;
		int val;
    unsigned x;

    for (i=0; i<len; i++){
    	x=array[i];
			val=0;
    	for(j=0; j<8*sizeof(unsigned); j++){
	 			val ^=  x & 0x1;
			 	x >>= 1;
		 	}
			res += val;
    }

    return res;
}

/*-----------------------------------------------------------------------*/

int parity2(unsigned* array, int len){

    int  i, res=0;
		int val;
    unsigned x;

    for (i=0; i<len; i++){
    	x=array[i];
			val=0;
    	do{
				val ^= x & 0x1;
			 	x >>= 1;
		 	}
		 while(x);
		 res += val;
    }

    return res;
}

/*-----------------------------------------------------------------------*/

int parity3(unsigned* array, int len){

	  int val=0;
		int i;
		unsigned x;
		int res=0;

    for (i=0; i<len; i++){
    	x=array[i];
			val=0;
    	while(x){
				val ^= x;
				x >>= 1;
			}
		res += val & 0x01;
    }

    return res;
}

/*-----------------------------------------------------------------------*/

int parity4(unsigned* array, int len){
	int i, res=0;
	int val;
	unsigned x;

	for(i=0; i<len; i++){
		x=array[i];
		val=0;
		asm(
			"bucle:\n\t"
			"xor %[x], %[v]\n\t"
			"shr $1, %[x]\n\t"
			"jne bucle\n\t"
			:[v]"+r"(val)
			:[x]"r"(x)
		);
		res+=val & 0x01;
	}
	return res;
}


/*-----------------------------------------------------------------------*/

int parity5(unsigned* array, int len){
	int i=0, j=0, res=0;
	unsigned x;

	for(i=0; i<len; i++){
		x=array[i];
		for(j=16; j>=1; j/=2){
			x^=x>>j;
		}
		res += x & 0x1;
	}
	return res;
}

/*-----------------------------------------------------------------------*/

int parity6(unsigned* array, int len){
	int i, res=0;
	unsigned x;

	for(i=0; i<len; i++){
		x=array[i];
		asm(
      "mov    %[x],   %%edx      \n\t"
      "shr    $16,    %%edx      \n\t"
      "xor    %[x],   %%edx      \n\t"
      "xor    %%dh,   %%dl       \n\t"
      "setpo  %%dl               \n\t"
      "movzx  %%dl,   %[x]       \n\t"
      :[x]"+r"(x)
      :
      :"edx"
    );
		res += x;
	}
	return res;
}

/*-----------------------------------------------------------------------*/

void crono(int (*func)(), char* msg){
    struct timeval tv1,tv2;		// gettimeofday() secs-usecs
    long           tv_usecs;	// y sus cuentas

    gettimeofday(&tv1,NULL);
    resultado = func(lista, SIZE);
    gettimeofday(&tv2,NULL);

    tv_usecs=(tv2.tv_sec -tv1.tv_sec )*1E6+
             (tv2.tv_usec-tv1.tv_usec);

#if COPY_PASTE_CALC
    printf(	   "%ld" "\n",		tv_usecs);
#else
    printf("resultado = %d\t", resultado);
    printf("%s:%9ld us\n", msg, tv_usecs);
#endif
}

int main()
{

#if ! TEST

    int i;									// inicializar array
    for (i=0; i<SIZE; i++)	// se queda en cache
	 lista[i]=i;

#endif

    crono(parity1, "parity1 (lenguaje C -            for)");
    crono(parity2, "parity2 (lenguaje C -          while)");
		crono(parity3, "parity3 (1.CS:APP 3.22 -  mask final)");
		crono(parity4, "parity4 (lenguaje ASM - cuerpo while)");
		crono(parity5, "parity5 (1.CS:APP 3.49 -   32b,16,1b)");
		crono(parity6, "parity6 (leng.ASM-cuerpo for - setnp)");


#if ! COPY_PASTE_CALC

    printf("calculado = %d\n", RESULT); /*OF*/

#endif

    exit(0);
}
