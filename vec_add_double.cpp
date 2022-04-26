//
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
//
//typedef double data_t;
//
//
//#define  vec_len 10000000
//data_t src1[vec_len];
//data_t src2[vec_len];
//
//data_t dst[vec_len];
//
//
//void time_measure(void func(), const char* msg = "", size_t trials = 100) {
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
//
//// set 0
//void vec_reset() {
//	for (size_t i = 0; i < vec_len; i++)
//	{
//		dst[i] = 0;
//	}
//}
//
//// print the mat to check
//template<class T>
//static void log_vec(T a[], size_t size) {
//	for (size_t i = 0; i < size; i++) {
//		cout << a[i] << ' ';
//	}
//	printf("\n\n");
//	vec_reset();
//}
//
//
//// origin version
//void vec_add_origin() {
//	for (size_t i = 0; i < vec_len; i++)
//	{
//		dst[i] = src1[i] + src2[i];
//	}
//}
//
//
//void vec_add_sse() {
//	constexpr size_t step_len = 128 / 8 / sizeof(data_t);
//	for (size_t i = 0; i < vec_len; i += step_len)
//	{
//		__m128d oprn1(_mm_loadu_pd(&src1[i]));
//		__m128d oprn2(_mm_loadu_pd(&src2[i]));
//
//		__m128d rst = _mm_add_pd(oprn1, oprn2);
//		_mm_store_pd(&dst[i], rst);
//	}
//}
//
//// avx
//void vec_add_avx() {
//	constexpr size_t step_len = 256 / 8 / sizeof(data_t);
//	for (size_t i = 0; i < vec_len; i += step_len)
//	{
//		__m256d oprn1(_mm256_loadu_pd(& src1[i]));
//		__m256d oprn2(_mm256_loadu_pd(& src2[i]));
//
//		__m256d rst = _mm256_add_pd(oprn1, oprn2);
//		_mm256_storeu_pd(& dst[i], rst);
//	}
//}
//
//
//
//
//
//int main() {
//
//	for (size_t i = 0; i < vec_len; i++)
//	{
//		src1[i] = i;
//		src2[i] = i;
//	}
//
//	time_measure(vec_add_origin, "origin");
//	log_vec<data_t>(dst, 5ull);
//
//	time_measure(vec_add_sse, "sse");
//	log_vec<data_t>(dst, 5ull);
//
//	time_measure(vec_add_avx, "avx");
//	log_vec<data_t>(dst, 5ull);
//
//	return 0;
//}