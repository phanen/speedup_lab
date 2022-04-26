
//#include<thread>
//#include<iostream>
//#include<vector>
//#include<chrono>
//
//using namespace std;
//
// 
//// description
//// the vector is implicitly divided into SEGMENT_NUM segments
//// for each thread: clac the sub-sum in a segment
//// for main thread: clac the sum of each sub-sum
//
//
//typedef long long data_t;
//
//// length of the vector
//#define VECTOR_LEN 100000000
//// num of segments
//#define THREAD_NUM 16
//
//// the vector
//data_t v[VECTOR_LEN];
//
//
//// sum the given vector/sub-vector
//void accumulate(const data_t* ptr, size_t len, data_t& ret) {
//	for (const data_t* p = ptr; p != ptr + len; ++p)
//		ret += *p;
//}
//
//
//int main() {
//	// initial the vector
//	for (size_t i = 0; i < VECTOR_LEN; i++)
//		v[i] = 666;
//
//	// data_t vlen = data_t(VECTOR_LEN);
//	// cout << "correct result:\t" << vlen * (vlen - 1) / 2 << endl;
//
//	vector<thread> threads_lst;
//	size_t seg_len = VECTOR_LEN / THREAD_NUM;
//	size_t mod_len = VECTOR_LEN % THREAD_NUM;
//	data_t buf[THREAD_NUM]{};
//
//
//
//	// concurrency
//	auto begin1 = chrono::high_resolution_clock::now();
//	data_t* ptr = v;
//
//	for (size_t i = 0; i < THREAD_NUM - 1; i++, ptr += seg_len)
//		threads_lst.push_back(thread(accumulate, ptr, seg_len, ref(buf[i])));
//	threads_lst.push_back(thread(accumulate, ptr, seg_len + mod_len, ref(buf[THREAD_NUM - 1])));
//
//	for (size_t i = 0; i < THREAD_NUM; i++)
//		threads_lst[i].join();
//
//	data_t ret1 = 0;
//	for (size_t i = 0; i < THREAD_NUM; i++)
//		ret1 += buf[i];
//
//	auto end1 = chrono::high_resolution_clock::now();
//
//
//	// non-concurrency
//	auto begin0 = chrono::high_resolution_clock::now();
//	data_t ret0 = 0;
//	for (const data_t* p = v; p != v + VECTOR_LEN; ++p)
//		ret0 += *p;
//	// for (size_t i = 0; i < VECTOR_LEN; i++)
//	// 	ret0 += v[i];
//	auto end0 = chrono::high_resolution_clock::now();
//
//
//
//
//	cout << "sum[nonconcurrency]:\t" << ret0 << endl;
//	cout << "sum[concurrency]:\t" << ret1 << endl;
//
//
//	cout << "buf:" << endl;
//	for (size_t i = 0; i < THREAD_NUM; i++)
//		cout << "\t" << buf[i] << endl;
//
//	printf("Time measured[nonconcurrency]: %.9f\n\n",
//		chrono::duration_cast<chrono::nanoseconds>(end0 - begin0).count() * 1e-9);
//	printf("Time measured[concurrency]: %.9f\n\n",
//		chrono::duration_cast<chrono::nanoseconds>(end1 - begin1).count() * 1e-9);
//
//
//}
