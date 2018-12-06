// For this exercise, you are going to read in data from a file called 'data.txt'
// Increment all of the values by 1.
// 
// You will compile this source using the following:
// 
// clang -std=c11 -mavx2 ex1.c -o ex1prog
//
// Run as normal with: 
// 
// ./ex1prog
//
#include <stdio.h>
#include <immintrin.h>



// print
void print__m256(__m256 data){
	float*f = (float*)&data;
	printf("%f %f %f %f %f %f %f %f\n", f[0],f[1],f[2],f[3],f[4],f[5],f[6],f[7]);
}

int main(){


	FILE *filePointer;

	filePointer = fopen("data.txt", "r");

	float buffer;
	float bufferr[32];
	int i = 0;


	while(fscanf(filePointer,"%f",&buffer) == 1) {


		bufferr[i] = buffer + 1;
		i++;


	}

	for (i=0; i < 32; i = i + 8 ) {


		float * aligned_32 = (float*)aligned_alloc(32, 64* sizeof(float));

		aligned_32[0] = bufferr[i];
		aligned_32[1] = bufferr[i+1];
		aligned_32[2] = bufferr[i+2];
		aligned_32[3] = bufferr[i+3];
		aligned_32[4] = bufferr[i+4];
		aligned_32[5] = bufferr[i+5];
		aligned_32[6] = bufferr[i+6];
		aligned_32[7] = bufferr[i+7];

		__m256 aligned_avx = _mm256_load_ps(aligned_32);
		print__m256(aligned_avx);

		free(aligned_32);


	}

	fclose(filePointer);

	return 0;
}
