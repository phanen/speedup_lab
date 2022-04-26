//#include <stdio.h>
//#include <time.h>
//#include <immintrin.h>
//
//#define N 512
//
//float M1[N][N], M2[N][N], Mre1[N][N], Mre2[N][N];
//int Mi1[N][N], Mi2[N][N], Mrei1[N][N], Mrei2[N][N];
//double Md1[N][N], Md2[N][N], Mred1[N][N], Mred2[N][N];
//
//
//
//void initial_matrix()
//{
//	for (int i = 0; i < N; i++) {
//		for (int j = 0; j < N; j++) {
//			M1[i][j] = M2[i][j] = Md1[i][j] = Md2[i][j] = Mi1[i][j] = Mi2[i][j] = i * N + j;
//			Mre2[i][j] = Mred2[i][j] = Mrei2[i][j] = 0;
//		}
//	}
//}
//
//void clock_measure(void func(), const char* msg)
//{
//	clock_t t = clock();
//	func();
//	t = clock() - t;
//	printf("\n%s spend %d clicks (%f seconds)\n", msg, t, ((float)t) / CLOCKS_PER_SEC);
//
//}
//void int_multiply_version1()
//{
//	for (int i = 0; i < N; i++) {
//		for (int j = 0; j < N; j++) {
//			int sum = 0;
//			for (int k = 0; k < N; k++) {
//				sum += Mi1[i][k] * Mi2[k][j];
//			}
//			Mrei1[i][j] = sum;
//		}
//	}
//}
//void float_multiply_version1()
//{
//	for (int i = 0; i < N; i++) {
//		for (int j = 0; j < N; j++) {
//			float sum = 0;
//			for (int k = 0; k < N; k++) {
//				sum += M1[i][k] * M2[k][j];
//			}
//			Mre1[i][j] = sum;
//		}
//	}
//}
//
//void double_multiply_version1()
//{
//	for (int i = 0; i < N; i++) {
//		for (int j = 0; j < N; j++) {
//			double sum = 0;
//			for (int k = 0; k < N; k++) {
//				sum += Md1[i][k] * Md2[k][j];
//			}
//			Mred1[i][j] = sum;
//		}
//	}
//}
//void int_multiply_version2()
//{
//	for (int i = 0; i < N; i++) {
//		for (int k = 0; k < N; k++) {
//			int tmp = Mi1[i][k];
//			int* ptr1 = &Mrei2[i][k];
//			int* ptr2 = &Mi2[i][k];
//			for (int j = 0; j < N; j++) {
//				(*ptr1++) += tmp * (*ptr2++);
//			}
//		}
//	}
//}
//
//void int_multiply_version3()
//{
//	for (int i = 0; i < N; i++) {
//		for (int k = 0; k < N; k++) {
//			int tmp = Mi1[i][k];
//			for (int j = 0; j < N; j++) {
//				Mrei2[i][j] += tmp * M2[k][j];
//			}
//		}
//	}
//}
//void float_multiply_version2()
//{
//	for (int i = 0; i < N; i++) {
//		for (int k = 0; k < N; k++) {
//			float tmp = M1[i][k];
//			float* ptr1 = &Mre2[i][k];
//			float* ptr2 = &M2[i][k];
//			for (int j = 0; j < N; j++) {
//				(*ptr1++) += tmp * (*ptr2++);
//			}
//		}
//	}
//}
//
//void double_multiply_version2()
//{
//	for (int i = 0; i < N; i++) {
//		for (int k = 0; k < N; k++) {
//			double tmp = Md1[i][k];
//			double* ptr1 = &Mred2[i][k];
//			double* ptr2 = &Md2[i][k];
//			for (int j = 0; j < N; j++) {
//				(*ptr1++) += tmp * (*ptr2++);
//			}
//		}
//	}
//}
//
//void simd_128_int()
//{
//	__m128i res, m1, m2;
//	for (int i = 0; i < N; i++)
//	{
//		for (int j = 0; j < N; ++j)
//		{
//			m1 = _mm_set1_epi32(Mi1[i][j]);
//			for (int k = 0; k < N; k += 4)
//			{
//				m2 = _mm_loadu_si128((__m128i*) & Mi2[j][k]);
//				res = _mm_loadu_si128((__m128i*) & Mrei2[i][k]);
//				res = _mm_add_epi32(res, _mm_mullo_epi32(m1, m2));
//				_mm_storeu_si128((__m128i*) & Mrei2[i][k], res);
//			}
//		}
//	}
//}
//
//void simd_256_int()
//{
//	__m256i res, m1, m2;
//	for (int i = 0; i < N; i++)
//	{
//		for (int j = 0; j < N; ++j)
//		{
//			m1 = _mm256_set1_epi32(Mi1[i][j]);
//			for (int k = 0; k < N; k += 8)
//			{
//				m2 = _mm256_loadu_si256((__m256i*) & Mi2[j][k]);
//				res = _mm256_loadu_si256((__m256i*) & Mrei2[i][k]);
//				res = _mm256_add_epi32(res, _mm256_mullo_epi32(m1, m2));
//				_mm256_storeu_si256((__m256i*) & Mrei2[i][k], res);
//			}
//		}
//	}
//}
//
//
//void simd_128_float()
//{
//	__m128 res, m1, m2;
//	for (int i = 0; i < N; i++)
//	{
//		for (int j = 0; j < N; ++j)
//		{
//			m1 = _mm_set1_ps(M1[i][j]);
//			for (int k = 0; k < N; k += 4)
//			{
//				m2 = _mm_loadu_ps(&M2[j][k]);
//				res = _mm_loadu_ps(&Mre2[i][k]);
//				res = _mm_add_ps(res, _mm_mul_ps(m1, m2));
//				_mm_storeu_ps(&Mre2[i][k], res);
//			}
//		}
//	}
//}
//
//void simd_256_float()
//{
//	__m256 res, m1, m2;
//	for (int i = 0; i < N; i++)
//	{
//		for (int j = 0; j < N; ++j)
//		{
//			m1 = _mm256_set1_ps(M1[i][j]);
//			for (int k = 0; k < N; k += 8)
//			{
//				m2 = _mm256_loadu_ps(&M2[j][k]);
//				res = _mm256_loadu_ps(&Mre2[i][k]);
//				res = _mm256_add_ps(res, _mm256_mul_ps(m1, m2));
//				_mm256_storeu_ps(&Mre2[i][k], res);
//			}
//		}
//	}
//}
//
//void simd_128_double()
//{
//	__m128d res, m1, m2;
//	for (int i = 0; i < N; i++)
//	{
//		for (int j = 0; j < N; ++j)
//		{
//			m1 = _mm_set1_pd(M1[i][j]);
//			for (int k = 0; k < N; k += 2)
//			{
//				m2 = _mm_loadu_pd(&Md2[j][k]);
//				res = _mm_loadu_pd(&Mred2[i][k]);
//				res = _mm_add_pd(res, _mm_mul_pd(m1, m2));
//				_mm_storeu_pd(&Mred2[i][k], res);
//			}
//		}
//	}
//}
//void simd_256_double()
//{
//	__m256d res, m1, m2;
//	for (int i = 0; i < N; i++)
//	{
//		for (int j = 0; j < N; ++j)
//		{
//			m1 = _mm256_set1_pd(M1[i][j]);
//			for (int k = 0; k < N; k += 4)
//			{
//				m2 = _mm256_loadu_pd(&Md2[j][k]);
//				res = _mm256_loadu_pd(&Mred2[i][k]);
//				res = _mm256_add_pd(res, _mm256_mul_pd(m1, m2));
//				_mm256_storeu_pd(&Mred2[i][k], res);
//			}
//		}
//	}
//}
//
//int main() {
//
//	initial_matrix();
//	clock_measure(int_multiply_version1, "int_multiply_version1");
//	clock_measure(int_multiply_version2, "int_multiply_version2");
//	clock_measure(int_multiply_version3, "int_multiply_version3");
//	clock_measure(simd_128_int, "simd_128_int");
//	initial_matrix();
//	clock_measure(simd_256_int, "simd_256_int");
//
//	for (int j = 0; j < 20; j++)
//	{
//		if (Mrei1[0][j] != Mrei2[0][j])
//			printf("int res error!\n");
//	}
//
//
//	clock_measure(float_multiply_version1, "float_multiply_version1");
//	clock_measure(float_multiply_version2, "float_multiply_version2");
//	clock_measure(simd_128_float, "simd_128_float");
//	initial_matrix();
//	clock_measure(simd_256_float, "simd_256_float");
//
//	for (int j = 0; j < 20; j++)
//	{
//		if (Mre1[0][j] != Mre2[0][j])
//			printf("float res error!\n");
//	}
//
//
//	clock_measure(double_multiply_version1, "double_multiply_version1");
//	clock_measure(double_multiply_version2, "double_multiply_version2");
//	clock_measure(simd_128_double, "simd_128_double");
//	initial_matrix();
//	clock_measure(simd_256_double, "simd_256_double");
//	for (int j = 0; j < 20; j++)
//	{
//		if (Mred1[0][j] != Mred2[0][j])
//			printf("double res error!\n");
//	}
//
//}
