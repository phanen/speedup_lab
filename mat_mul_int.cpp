
#include <stdio.h>
//#include <emmintrin.h>
//#include <immintrin.h>
#include <intrin.h>
#include <stdint.h>
#include <time.h>
#include <chrono>
#include <iostream>
using namespace std;
// NOTE: 
// The size of matrix must be multiple of block_size
// For example: when using avx 256-bit reg, 
// 8 couple of int type can be add together
// So the mat_size should be divided by 8

#define _CRT_SECURE_NO_WARNING

#define mat_size 200
#define trial_num 10

int src1[mat_size][mat_size]{};
int src2[mat_size][mat_size]{};

int dst[mat_size][mat_size]{};

typedef int data_t;
void time_measure(void func(), const char* msg = "", size_t trials = 100);



// set 0
void mat_reset() {
	for (size_t i = 0; i < mat_size; i++)
	{
		for (size_t j = 0; j < mat_size; j++)
		{
			dst[i][j] = 0;
		}
	}
}

// print the mat to check
template<class T>
void log_mat(T a[mat_size][mat_size], size_t size) {
	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < size; j++)
		{
			cout << a[i][j] << ' ';
		}
		printf("\n");
	}
	printf("\n\n");
	mat_reset();
}


// origin version
void mat_mul_origin() {
	for (size_t i = 0; i < mat_size; i++)
		for (size_t j = 0; j < mat_size; j++)
		{
			int tmp = 0;
			for (size_t k = 0; k < mat_size; k++)
			{
				tmp += src1[i][k] * src2[k][j];
			}
			dst[i][j] = tmp;
		}
}


// using pointer to access instead of index and array
void mat_mul_idx2ptr() {

	int* ptr = dst[0];
	for (size_t i = 0; i < mat_size; i++)
		for (size_t j = 0; j < mat_size; j++)
		{
			int tmp = 0;
			for (size_t k = 0; k < mat_size; k++)
			{
				tmp += src1[i][k] * src2[k][j];
			}
			*ptr++ = tmp;
		}
}


// Assumption: The second oprand matrix is stored in transposed format
void mat_mul_trsp() {

	for (size_t i = 0; i < mat_size; i++)
		for (size_t j = 0; j < mat_size; j++)
		{
			int tmp = 0;
			for (size_t k = 0; k < mat_size; k++)
			{
				tmp += src1[i][k] * src2[j][k];
			}
			dst[i][j] = tmp;
		}

}

// reorder the loop
void mat_mul_loop_reorder() {
	for (size_t i = 0; i < mat_size; i++) {
		for (size_t k = 0; k < mat_size; k++)
		{
			int tmp = src1[i][k];
			for (size_t j = 0; j < mat_size; j++)
			{
				dst[i][j] += tmp * src2[k][j];
			}
		}
	}
}







// _mm256_set_epi32(src2[k + 7][j], src2[k + 6][j], src2[k + 5][j], src2[k + 4][j], src2[k + 3][j], src2[k + 2][j], src2[k + 1][j], src2[k][j])


// v1 -- AVX/AVX2
void mat_mul_avx_reorder() {
	// 256 / (sizeof(int) * 8)
	for (size_t i = 0; i < mat_size; i++)
	{
		for (size_t k = 0; k < mat_size; k++)
		{
			__m256i oprd1 = _mm256_set1_epi32(src1[i][k]);
			//__m256i oprd1 = _mm256_set_epi32(src1[i][k], src1[i][k], src1[i][k], src1[i][k], src1[i][k], src1[i][k], src1[i][k], src1[i][k]);
			for (size_t j = 0; j < mat_size; j += 8)
			{
				__m256i oprd2 = _mm256_loadu_si256((__m256i*) & src2[k][j]);

				__m256i adder = _mm256_mullo_epi32(oprd1, oprd2);


				__m256i ret = _mm256_loadu_si256((__m256i*) & dst[i][j]);
				ret = _mm256_add_epi32(ret, adder);
				_mm256_storeu_si256((__m256i*) & dst[i][j], ret);
			}
		}

		//_mm256_storeu_si256((__m256i*) & dst[i], _mm256_add_epi32(_mm256_loadu_si256((__m256i*) & src1[i]), _mm256_loadu_si256((__m256i*) & src2[i])));
	}
}


void mat_mul_avx_reorder_plus() {

	for (size_t i = 0; i < mat_size; i++)
	{
		for (size_t k = 0; k < mat_size; k++)
		{
			__m256i oprd1 = _mm256_set1_epi32(src1[i][k]);
			for (size_t j = 0; j < mat_size; j += 8)
			{
				_mm256_storeu_si256((__m256i*) & dst[i][j], _mm256_add_epi32(_mm256_loadu_si256((__m256i*) & dst[i][j]), _mm256_mullo_epi32(oprd1, _mm256_loadu_si256((__m256i*) & src2[k][j]))));
			}
		}
	}
}


void mat_mul_avx_trsp() {
	constexpr int step_len = 256 / 8 / sizeof(data_t);
	for (size_t i = 0; i < mat_size; i++)
	{
		for (size_t j = 0; j < mat_size; j++)
		{
			//data_t tmp = 0;
			__m256i tmp = _mm256_setzero_si256();
			for (size_t k = 0; k < mat_size; k += step_len)
			{
				// tmp += src1[i][k] * src2[k][j];
				// transpose-assumpiton : tmp += src1[i][k] * src2[j][k];
				tmp =
					_mm256_add_epi32(
						tmp,
						_mm256_mullo_epi32(
							_mm256_loadu_si256((__m256i*) & src1[i][k]),
							_mm256_loadu_si256((__m256i*) & src2[j][k])
						)
					);

			}
			dst[i][j] =
				(
					(_mm256_extract_epi32(tmp, 0) + _mm256_extract_epi32(tmp, 1))
					+
					(_mm256_extract_epi32(tmp, 2) + _mm256_extract_epi32(tmp, 3))
					)
				+
				(
					(_mm256_extract_epi32(tmp, 4) + _mm256_extract_epi32(tmp, 5))
					+
					(_mm256_extract_epi32(tmp, 6) + _mm256_extract_epi32(tmp, 7))
					);

			//dst[i][j] = _mm256_extract_epi32(tmp, 0) + _mm256_extract_epi32(tmp, 1)
			//	+ _mm256_extract_epi32(tmp, 2) + _mm256_extract_epi32(tmp, 3)
			//	+ _mm256_extract_epi32(tmp, 4) + _mm256_extract_epi32(tmp, 5)
			//	+ _mm256_extract_epi32(tmp, 6) + _mm256_extract_epi32(tmp, 7);
			//_mm256_storeu_si256((__m256i*) & dst[i][j], tmp);
		}
	}
}

void mat_mul_avx_trsp_hadd() {

	constexpr int step_len = 256 / 8 / sizeof(data_t);
	for (size_t i = 0; i < mat_size; i++)
	{
		for (size_t j = 0; j < mat_size; j++)
		{
			//data_t tmp = 0;
			__m256i tmp = _mm256_setzero_si256();
			for (size_t k = 0; k < mat_size; k += step_len)
			{
				// tmp += src1[i][k] * src2[k][j];
				// transpose-assumpiton : tmp += src1[i][k] * src2[j][k];
				tmp =
					_mm256_add_epi32(
						tmp,
						_mm256_mullo_epi32(
							_mm256_loadu_si256((__m256i*) & src1[i][k]),
							_mm256_loadu_si256((__m256i*) & src2[j][k])
						)
					);

			}
			// 8 - > h:4 l:4
			__m128i l = _mm256_extracti128_si256(tmp, 0);
			__m128i h = _mm256_extracti128_si256(tmp, 1);
			// 4,4 -> 4
			l = _mm_add_epi32(l, h);
			// 4 -> 2 * 2
			l = _mm_hadd_epi32(l, l);
			// 2 -> 1
			dst[i][j] = _mm_extract_epi32(l, 0) + _mm_extract_epi32(l, 1);
		}
	}
}


int main()
{

	for (size_t i = 0; i < mat_size; i++)
	{
		for (size_t j = 0; j < mat_size; j++)
		{
			src1[i][j] = i + j;
			src2[j][i] = i + j;
		}
	}

	time_measure(mat_mul_origin, "mat_mul_origin");
	//log_mat<data_t>(dst, 5ull);

	time_measure(mat_mul_idx2ptr, "mat_mul_idx2ptr");
	//log_mat<data_t>(dst, 5ull);


	time_measure(mat_mul_idx2ptr, "mat_mul_idx2ptr");
	//log_mat<data_t>(dst, 5ull);

	time_measure(mat_mul_loop_reorder, "mat_mul_loop_reorder");
	//log_mat<data_t>(dst, 5ull);


	time_measure(mat_mul_avx_reorder, "mat_mul_avx_reorder");
	//log_mat<data_t>(dst, 5ull);

	time_measure(mat_mul_avx_reorder_plus, "mat_mul_avx_reorder_plus");
	//log_mat<data_t>(dst, 5ull);

	time_measure(mat_mul_avx_trsp, "mat_mul_avx_trsp");
	//log_mat<data_t>(dst, 5ull);


	time_measure(mat_mul_avx_trsp_hadd, "mat_mul_avx_trsp_hadd");
	log_mat<data_t>(dst, 5ull);


	return 0;
}