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
//typedef int data_t;
//
//
//#define  vec_len 10000000
//data_t src1[vec_len];
//data_t src2[vec_len];
//
//data_t dst[vec_len];
//
//
//__m256i vec1[vec_len / 8];
//__m256i vec2[vec_len / 8];
//__m256i vec3[vec_len / 8];
//
//void time_measure(void func(), const char* msg = "", size_t trials = 100);
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
//
//
//void vec_add_mmx() {
//	constexpr size_t step_len = 64 / 8 / sizeof(data_t);
//	auto t1{ std::chrono::system_clock::now() };
//
//	for (size_t i = 0; i < vec_len; i += step_len)
//	{
//		__m64 oprn1 = *(__m64*) & src1[i];
//		__m64 oprn2 = *(__m64*) & src2[i];
//		__m64 rst = _m_paddd(oprn1, oprn2);
//		//dst[i] = rst.m64_i32[0];
//		//dst[i + 1] = rst.m64_i32[1];
//		//_mm_storeu_si128((__m128i*) & dst[i], rst);
//	}
//	auto t2{ std::chrono::system_clock::now() };
//	double duration = (std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() * 1e-9);
//	cout << duration << endl;
//	printf("duration: %.9f\n", duration);
//
//}
//
//void vec_add_sse() {
//	constexpr size_t step_len = 128 / 8 / sizeof(data_t);
//	for (size_t i = 0; i < vec_len; i += step_len)
//	{
//		__m128i oprn1(_mm_loadu_si128((__m128i*) & src1[i]));
//		__m128i oprn2(_mm_loadu_si128((__m128i*) & src2[i]));
//
//		__m128i rst = _mm_add_epi32(oprn1, oprn2);
//		_mm_storeu_si128((__m128i*) & dst[i], rst);
//	}
//}
//
//void vec_add_sse_plus() {
//	constexpr size_t step_len = 128 / 8 / sizeof(data_t);
//	for (size_t i = 0; i < vec_len; i += step_len)
//	{
//		_mm_storeu_si128((__m128i*) & dst[i], _mm_add_epi32(_mm_loadu_si128((__m128i*) & src1[i]), _mm_loadu_si128((__m128i*) & src2[i])));
//	}
//}
//
//// avx
//void vec_add_avx() {
//	constexpr size_t step_len = 256 / 8 / sizeof(data_t);
//
//
//	for (size_t i = 0; i < vec_len; i += step_len)
//	{
//		__m256i oprn1(_mm256_load_si256((__m256i*) & src1[i]));
//		__m256i oprn2(_mm256_load_si256((__m256i*) & src2[i]));
//
//		__m256i rst = _mm256_add_epi32(oprn1, oprn2);
//		_mm256_storeu_si256((__m256i*) & dst[i], rst);
//	}
//
//
//}
//
//
//void vec_add_avx_plus1() {
//	constexpr size_t step_len = 256 / 8 / sizeof(data_t);
//	for (size_t i = 0; i < vec_len; i += step_len)
//	{
//		_mm256_storeu_si256((__m256i*) & dst[i], _mm256_add_epi32(*(__m256i*) & src1[i], *(__m256i*) & src2[i]));
//
//	}
//}
//
//void vec_add_avx_plus2() {
//	constexpr size_t step_len = 256 / 8 / sizeof(data_t);
//	for (size_t i = 0; i < vec_len; i += step_len)
//	{
//		_mm256_storeu_si256((__m256i*) & dst[i], _mm256_add_epi32(_mm256_load_si256((__m256i*) & src1[i]), _mm256_load_si256((__m256i*) & src2[i])));
//	}
//}
//
//
//// avx online
//void vec_add_avx_off() {
//	// 8
//	constexpr size_t step_len = 256 / 8 / sizeof(data_t);
//
//	auto t1{ std::chrono::system_clock::now() };
//
//
//	for (size_t i = 0; i < vec_len / step_len; i++)
//	{
//		vec1[i] = _mm256_loadu_si256((__m256i*) & src1[i << 3]);
//		vec2[i] = _mm256_loadu_si256((__m256i*) & src2[i << 3]);
//	}
//	auto t2{ std::chrono::system_clock::now() };
//
//	auto t3{ std::chrono::system_clock::now() };
//
//	for (size_t i = 0; i < vec_len / step_len; i++)
//		vec3[i] = _mm256_add_epi32(vec1[i], vec2[i]);
//	auto t4{ std::chrono::system_clock::now() };
//
//	auto t5{ std::chrono::system_clock::now() };
//
//	for (size_t i = 0; i < vec_len / step_len; i++)
//	{
//
//		_mm256_storeu_si256((__m256i*) & dst[i << 3], vec3[i]);
//	}
//	auto t6{ std::chrono::system_clock::now() };
//
//	printf("Time measured[inline in the func]:%.9f %.9f %.9f\n\n",
//		(std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() * 1e-9),
//		(std::chrono::duration_cast<std::chrono::nanoseconds>(t4 - t3).count() * 1e-9),
//		(std::chrono::duration_cast<std::chrono::nanoseconds>(t6 - t5).count() * 1e-9));
//}
//
//void pp() {
//	printf("%.9f", 1.1000000000000001e-07);
//}
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
//	vec_add_mmx();
//	vec_add_mmx();
//	vec_add_mmx();
//	vec_add_mmx();
//	vec_add_mmx();
//	vec_add_mmx();
//	vec_add_mmx();
//	vec_add_mmx();
//	vec_add_mmx();
//
//	//log_vec<data_t>(dst, 5ull);
//	time_measure(vec_add_sse_plus, "vec_add_sse_plus");
//	log_vec<data_t>(dst, 5ull);
//
//	time_measure(vec_add_origin, "vec_add_origin");
//	log_vec<data_t>(dst, 5ull);
//
//
//	time_measure(vec_add_sse, "vec_add_sse");
//	log_vec<data_t>(dst, 5ull);
//
//
//
//
//	time_measure(vec_add_avx, "vec_add_avx");
//	log_vec<data_t>(dst, 5ull);
//
//	time_measure(vec_add_avx_plus1, "vec_add_avx_plus1");
//	log_vec<data_t>(dst, 5ull);
//
//	time_measure(vec_add_avx_plus2, "vec_add_avx_plus2");
//	log_vec<data_t>(dst, 5ull);
//	
//	//time_measure(vec_add_avx_off, "vec_add_avx_off");
//
//
//	//int xx = 10;
//	//while (xx--)
//	//{
//	//vec_add_avx_off();
//	//}
//	//return 0;
//
//}