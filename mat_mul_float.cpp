//#include <stdio.h>
////#include <emmintrin.h>
////#include <immintrin.h>
//#include <intrin.h>
//#include <stdint.h>
//#include <time.h>
//#include <chrono>
//#include <iostream>
//using namespace std;
//
//// NOTE: 
//// The size of matrix must be multiple of block_size
//// For example: when using avx 256-bit reg, 
//// 8 couple of int type can be add together
//// So the mat_size should be divided by 8
//
//
//#define mat_size 200
//#define trial_num 10
//
//int src1[mat_size][mat_size]{};
//int src2[mat_size][mat_size]{};
//
//int dst[mat_size][mat_size]{};
//
//typedef int data_t;
//
//
//void time_measure(void func(), const char* msg = "", size_t trials = 1) {
//	auto t1{ std::chrono::system_clock::now() };
//
//	for (size_t i = 0; i < trials; i++)
//	{
//		func();
//	}
//	auto t2{ std::chrono::system_clock::now() };
//
//	printf("Time measured[func: %s, trials: %lld]:\t%.9f\n\n",
//		msg,
//		trials,
//		(std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() * 1e-9) / trials);
//}
//
//// set 0
//void mat_reset() {
//	for (size_t i = 0; i < mat_size; i++)
//	{
//		for (size_t j = 0; j < mat_size; j++)
//		{
//			dst[i][j] = 0;
//		}
//	}
//}
//
//// print the mat to check
//template<class T>
//void log_mat(T a[mat_size][mat_size], size_t size) {
//	for (size_t i = 0; i < size; i++) {
//		for (size_t j = 0; j < size; j++)
//		{
//			cout << a[i][j] << ' ';
//		}
//		printf("\n");
//	}
//	printf("\n\n");
//	mat_reset();
//}
//
//
//// origin version
//void mat_mul_origin() {
//	for (size_t i = 0; i < mat_size; i++)
//		for (size_t j = 0; j < mat_size; j++)
//		{
//			int tmp = 0;
//			for (size_t k = 0; k < mat_size; k++)
//			{
//				tmp += src1[i][k] * src2[k][j];
//			}
//			dst[i][j] = tmp;
//		}
//}
//
//
//// using pointer to access instead of index and array
//void mat_mul_idx2ptr() {
//
//	int* ptr = dst[0];
//	for (size_t i = 0; i < mat_size; i++)
//		for (size_t j = 0; j < mat_size; j++)
//		{
//			int tmp = 0;
//			for (size_t k = 0; k < mat_size; k++)
//			{
//				tmp += src1[i][k] * src2[k][j];
//			}
//			*ptr++ = tmp;
//		}
//}
//
//
//// Assumption: The second oprand matrix is stored in transposed format
//void mat_mul_transpose() {
//
//	for (size_t i = 0; i < mat_size; i++)
//		for (size_t j = 0; j < mat_size; j++)
//		{
//			int tmp = 0;
//			for (size_t k = 0; k < mat_size; k++)
//			{
//				tmp += src1[i][k] * src2[j][k];
//			}
//			dst[i][j] = tmp;
//		}
//
//}
//
//// reorder the loop
//void mat_mul_loop_reorder() {
//	for (size_t i = 0; i < mat_size; i++) {
//		for (size_t k = 0; k < mat_size; k++)
//		{
//			int tmp = src1[i][k];
//			for (size_t j = 0; j < mat_size; j++)
//			{
//				dst[i][j] += tmp * src2[k][j];
//			}
//		}
//	}
//}
//
//
//
//void version5()
//{
//	for (size_t i = 0; i < mat_size; i += 8)
//	{
//		for (size_t j = 0; j < mat_size; ++j)
//		{
//			__m256i vec_mat2 = _mm256_setr_epi32(src2[i][j], src2[i + 1][j], src2[i + 2][j], src2[i + 3][j], src2[i + 4][j], src2[i + 5][j], src2[i + 6][j], src2[i + 7][j]);
//			__m256i vec_multi = _mm256_setzero_si256();
//
//			for (size_t k = 0; k < mat_size; ++k)
//			{
//				__m256i vec_mat1 = _mm256_loadu_si256((__m256i*) & src1[k][i]); //Stores row of first matrix (eight in each iteration)
//				vec_multi = _mm256_add_epi32(vec_multi, _mm256_mullo_epi32(vec_mat1, vec_mat2));//Multiplies the vectors
//
//				dst[k][j] += _mm256_extract_epi32(vec_multi, 0) + _mm256_extract_epi32(vec_multi, 1) + _mm256_extract_epi32(vec_multi, 2) + _mm256_extract_epi32(vec_multi, 3) + _mm256_extract_epi32(vec_multi, 4) + _mm256_extract_epi32(vec_multi, 5) + _mm256_extract_epi32(vec_multi, 6) + _mm256_extract_epi32(vec_multi, 7);
//
//				vec_multi = _mm256_setzero_si256();
//			}
//		}
//	}
//}
//
//
//void mat_mul_avx() {
//
//	for (size_t i = 0; i < mat_size; i++)
//	{
//		for (size_t j = 0; j < mat_size; j++)
//		{
//			//data_t tmp = 0;
//			__m256i tmp = _mm256_setzero_si256();
//			for (size_t k = 0; k < mat_size; k += 8)
//			{
//				// tmp += src1[i][k] * src2[k][j];
//				// transpose-assumpiton : tmp += src1[i][k] * src2[j][k];
//				tmp =
//					_mm256_add_epi32(
//						tmp,
//						_mm256_mullo_epi32(
//							_mm256_loadu_si256((__m256i*) & src1[i][k]),
//							_mm256_loadu_si256((__m256i*) & src2[j][k])
//						)
//					);
//			}
//			//dst[i][j] = tmp;
//			_mm256_storeu_si256((__m256i*) & dst[i][j], tmp);
//		}
//	}
//}
//
//// _mm256_set_epi32(src2[k + 7][j], src2[k + 6][j], src2[k + 5][j], src2[k + 4][j], src2[k + 3][j], src2[k + 2][j], src2[k + 1][j], src2[k][j])
//
//
//// v1 -- AVX/AVX2
//void mat_mul_avx_reorder() {
//	// 256 / (sizeof(int) * 8)
//	for (size_t i = 0; i < mat_size; i++)
//	{
//		for (size_t k = 0; k < mat_size; k++)
//		{
//			__m256i oprd1 = _mm256_set1_epi32(src1[i][k]);
//			//__m256i oprd1 = _mm256_set_epi32(src1[i][k], src1[i][k], src1[i][k], src1[i][k], src1[i][k], src1[i][k], src1[i][k], src1[i][k]);
//			for (size_t j = 0; j < mat_size; j += 8)
//			{
//				__m256i oprd2 = _mm256_loadu_si256((__m256i*) & src2[k][j]);
//				__m256i ret = _mm256_loadu_si256((__m256i*) & dst[i][j]);
//
//				__m256i adder = _mm256_mullo_epi32(oprd1, oprd2);
//				ret = _mm256_add_epi32(ret, adder);
//
//				_mm256_storeu_si256((__m256i*) & dst[i][j], ret);
//			}
//		}
//
//		//_mm256_storeu_si256((__m256i*) & dst[i], _mm256_add_epi32(_mm256_loadu_si256((__m256i*) & src1[i]), _mm256_loadu_si256((__m256i*) & src2[i])));
//	}
//}
//
//
//void mat_mul_avx_reorder_plus() {
//
//	for (size_t i = 0; i < mat_size; i++)
//	{
//		for (size_t k = 0; k < mat_size; k++)
//		{
//			__m256i oprd1 = _mm256_set1_epi32(src1[i][k]);
//			for (size_t j = 0; j < mat_size; j += 8)
//			{
//				_mm256_storeu_si256((__m256i*) & dst[i][j], _mm256_add_epi32(_mm256_loadu_si256((__m256i*) & dst[i][j]), _mm256_mullo_epi32(oprd1, _mm256_loadu_si256((__m256i*) & src2[k][j]))));
//			}
//		}
//	}
//}
//
//
//
//
//
//
//
//
//int main()
//{
//
//	for (size_t i = 0; i < mat_size; i++)
//	{
//		for (size_t j = 0; j < mat_size; j++)
//		{
//			src1[i][j] = 1;
//			src2[j][i] = 1;
//		}
//	}
//
//	time_measure(mat_mul_idx2ptr, "idx2ptr");
//	log_mat<data_t>(dst, 5ull);
//	
//	time_measure(mat_mul_origin, "origin");
//	log_mat<data_t>(dst, 5ull);
//
//	time_measure(mat_mul_transpose, "transpose");
//	log_mat<data_t>(dst, 5ull);
//
//	time_measure(mat_mul_loop_reorder, "loop_reorder");
//	log_mat<data_t>(dst, 5ull);
//
//
//	time_measure(version5, "version5");
//	log_mat<data_t>(dst, 5ull);
//
//
//
//	time_measure(mat_mul_avx, "avx");
//	log_mat<data_t>(dst, 5ull);
//
//
//	time_measure(mat_mul_avx_reorder, "avx_reorder");
//	log_mat<data_t>(dst, 5ull);
//
//	time_measure(mat_mul_avx_reorder_plus, "avx_reorder_plus");
//	log_mat<data_t>(dst, 5ull);
//	return 0;
//}