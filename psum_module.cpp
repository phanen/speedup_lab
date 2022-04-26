//// Using the module provided by <<The C++ Concurrency Practice>>
//
//#include<thread>
//#include<iostream>
//#include<vector>
//#include<chrono>
//#include<numeric>
//#include<algorithm>
//#include <functional>
//using namespace std;
//
// 
//typedef int data_t;
//
//// length of the vector
//#define VECTOR_LEN 1000000
//data_t v[VECTOR_LEN];
//
//
//struct accumulate_block
//{
//	void operator()(const data_t* first, const data_t* last, data_t& result)
//	{
//		result = std::accumulate(first, last, result);
//	}
//};
//
//void parallel_accumulate(const data_t* first, size_t len, data_t& ret, size_t num_threads)
//{
//	unsigned long const seg_len = len / num_threads;
//
//	vector<data_t> bufs(num_threads);
//	vector<thread> threads_lst(num_threads - 1);
//
//	const data_t* ptr = first;
//	for (size_t i = 0; i < num_threads - 1; ++i)
//	{
//		const data_t* next_ptr = ptr + seg_len;
//		threads_lst[i] = thread(accumulate_block(), ptr, next_ptr, ref(bufs[i]));
//		ptr = next_ptr;
//	}
//	accumulate_block()(ptr, first + len, bufs[num_threads - 1]);
//
//
//	for (auto& c : threads_lst)
//		c.join();
//	for (auto& c : bufs)
//		ret += c;
//	 //for_each(threads_lst.begin(), threads_lst.end(), mem_fn(&thread::join));
//	// ret = accumulate(bufs.begin(), bufs.end(), data_t(0)); 
//}
//
//
//
//
//
//// sum the given vector/sub-vector
//void my_accumulate(const data_t* ptr, size_t len, data_t& ret) {
//	for (const data_t* p = ptr; p != ptr + len; ++p)
//		ret += *p;
//}
//
//
//
//int main() {
//
//	// initial the vector
//	for (size_t i = 0; i < VECTOR_LEN; i++)
//		v[i] = 666;
//
//
//	// cout << "correct result:\t" << (VECTOR_LEN - 1) * VECTOR_LEN / 2 << endl;
//	// cout << std::thread::hardware_concurrency();
//
//	data_t ret0 = 0;
//	data_t ret1 = 0;
//
//	auto begin0 = chrono::high_resolution_clock::now();
//	my_accumulate(v, VECTOR_LEN, ret0);
//	auto end0 = chrono::high_resolution_clock::now();
//
//	auto begin1 = chrono::high_resolution_clock::now();
//	parallel_accumulate(v, VECTOR_LEN, ret1, 15);
//	auto end1 = chrono::high_resolution_clock::now();
//
//	cout << "ret0:\t" << ret0 << endl;
//	cout << "ret1:\t" << ret1 << endl;
//
//
//	std::printf("Time measured[Nonconcurrency]: %.9f\n\n",
//		std::chrono::duration_cast<std::chrono::nanoseconds>(end0 - begin0).count() * 1e-9);
//
//	std::printf("Time measured[Concurrency]: %.9f\n\n",
//		std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - begin1).count() * 1e-9);
//
//
//
//}
