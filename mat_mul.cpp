
//#include<thread>
//#include<iostream>
//#include<vector>
//#include<chrono>
//#include<mutex>
//using namespace std;
// 
//
//// description
//typedef long long data_t;
//
//// length of the vector
//#define MAT_SIZE 200
//
//// the matrix
//data_t mat_a[MAT_SIZE][MAT_SIZE]{};
//data_t mat_b[MAT_SIZE][MAT_SIZE]{};
//data_t mat_ret[MAT_SIZE][MAT_SIZE]{};
//
//
//// clac the (i, j) item of the result matrix;  
//// i or j range form 0 to ... MAT_SIZE - 1
//void mat_multiply_item(size_t i, size_t j) {
//	data_t* ptr_a = &mat_a[i][0];
//	data_t* ptr_b = &mat_b[0][j];
//	data_t& ret = mat_ret[i][j];
//
//	for (size_t k = 0; k < MAT_SIZE; k++)
//	{
//		// ret += mat_a[i][k] * mat_b[k][j];
//		ret += (*ptr_a) * (*ptr_b);
//		++ptr_a;
//		ptr_b += MAT_SIZE;
//	}
//}
//
//std::mutex aa;
//
//// clac the items from the first-th row to (first + size)-th row(exclude)
//void mat_multiply_rows(size_t first, size_t size) {
//	// brute-force
//	//for (size_t i = first; i < first + size; i++)
//	//{
//	//	for (size_t j = 0; j < MAT_SIZE; j++)
//	//	{
//	//		data_t& ret = mat_ret[i][j];
//	//		for (size_t k = 0; k < MAT_SIZE; k++)
//	//		{
//	//			ret += mat_a[i][k] * mat_b[k][j];
//	//		}
//	//	}
//	//}
//
//	// loop order swap
//	for (size_t k = 0; k < MAT_SIZE; k++)
//	{
//		data_t* ptr = &mat_ret[first][0];
//		for (size_t i = first; i < first + size; i++) {
//			data_t tmp = mat_a[i][k];
//			for (size_t j = 0; j < MAT_SIZE; j++)
//			{
//				(*ptr++) += tmp * mat_b[k][j];
//			}
//		}
//	}
//}
//
//int main() {
//	// initialize the vector
//	data_t cnt = 0;
//	for (size_t i = 0; i < MAT_SIZE; i++) {
//		for (size_t j = 0; j < MAT_SIZE; j++)
//		{
//			mat_a[i][j] = cnt++;
//			mat_b[j][i] = cnt++;
//		}
//	}
//
//
//	// speed up a little by change the order of loop
////for (size_t k = 0; k < MAT_SIZE; k++)
////{
////	data_t* ptr = &mat_ret[0][0];
////	for (size_t i = 0; i < MAT_SIZE; i++) {
////		data_t tmp = mat_a[i][k];
////		for (size_t j = 0; j < MAT_SIZE; j++)
////		{
////			(*ptr++) += tmp * mat_b[k][j];
////		}
////	}
////}
//
//	auto begin = chrono::high_resolution_clock::now();
//
//
//	// clac each item
//	//for (size_t i = 0; i < MAT_SIZE; i++) {
//	//	for (size_t j = 0; j < MAT_SIZE; j++)
//	//	{
//	//		mat_multiply_item(i, j);
//	//	}
//	//}
//
//
//	// brute-force multiply (item by item)
//	//for (size_t i = 0; i < MAT_SIZE; i++)
//	//{
//	//	for (size_t j = 0; j < MAT_SIZE; j++)
//	//	{
//	//		data_t& ret = mat_ret[i][j];
//	//		for (size_t k = 0; k < MAT_SIZE; k++)
//	//		{
//	//			ret += mat_a[i][k] * mat_b[k][j];
//	//		}
//	//	}
//	//}
//
//
//	// speed up a little by change the order of loop
//	//for (size_t k = 0; k < MAT_SIZE; k++)
//	//{
//	//	data_t* ptr = &mat_ret[0][0];
//	//	for (size_t i = 0; i < MAT_SIZE; i++) {
//	//		data_t tmp = mat_a[i][k];
//	//		for (size_t j = 0; j < MAT_SIZE; j++)
//	//		{
//	//			(*ptr++) += tmp * mat_b[k][j];
//	//		}
//	//	}
//	//}
//
//	vector<thread> threads_lst;
//	size_t threads_num = 1;
//	size_t seg_size = MAT_SIZE / threads_num;
//	size_t first = 0;
//	for (size_t i = 0; i < threads_num - 1; i++)
//	{
//		threads_lst.push_back(thread(mat_multiply_rows, first, seg_size));
//		first += seg_size;
//	}
//	threads_lst.push_back(thread(mat_multiply_rows, first, MAT_SIZE - first));
//
//
//	for (size_t i = 0; i < threads_num; i++)
//		threads_lst[i].join();
//
//
//	auto end = chrono::high_resolution_clock::now();
//	printf("Time measured: %.9f\n\n",
//		chrono::duration_cast<chrono::nanoseconds>(end - begin).count() * 1e-9);
//
//
//	//// log mat_a
//	//cout << "mat_a" << endl;
//	//for (size_t i = 0; i < MAT_SIZE; i++) {
//	//	for (size_t j = 0; j < MAT_SIZE; j++)
//	//		cout << mat_a[i][j] << ' ';
//	//	cout << endl;
//	//}
//
//	//// log mat_b
//	//cout << "mat_b" << endl;
//	//for (size_t i = 0; i < MAT_SIZE; i++) {
//	//	for (size_t j = 0; j < MAT_SIZE; j++)
//	//		cout << mat_b[i][j] << ' ';
//	//	cout << endl;
//	//}
//
//	//// log mat_ret
//	//cout << "mat_ret" << endl;
//	//for (size_t i = 0; i < MAT_SIZE; i++) {
//	//	for (size_t j = 0; j < MAT_SIZE; j++)
//	//		cout << mat_ret[i][j] << "\t\t";
//	//	cout << endl;
//	//}
//
//}
