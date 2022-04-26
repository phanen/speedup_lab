
//#include<thread>
//#include<iostream>
//#include<vector>
//#include<numeric>
//#include<chrono>
// 
//using namespace std;
//
//// description
//// the vector is implicitly divided into SEGMENT_NUM segments
//// for each thread: clac the sub-sum in a segment
//// for main thread: clac the sum of each sub-sum
//
//typedef  long long data_t;
//#define IDENTITY data_t(0)
//
//struct accumulate_block
//{
//	void operator()(vector<data_t>::const_iterator first, vector<data_t>::const_iterator  last, data_t& result)
//	{
//		result = std::accumulate(first, last, result);
//	}
//};
//
//data_t myaccumulate_1(vector<data_t>::const_iterator begin, vector<data_t>::const_iterator end, data_t& init) {
//	for (auto p = begin; p != end; p++)
//		init += *p;
//	return init;
//}
//
//
//data_t myaccumulate_2a(vector<data_t>::const_iterator begin, vector<data_t>::const_iterator end, data_t& init) {
//	auto p1 = begin; auto p2 = begin + 1;
//	for (; p1 != end && p2 != end; p1 += 2, p2 += 2)
//		init += (*p1 + *p2);
//	if (p2 == end) init += *p1;
//	return init;
//}
//
//data_t myaccumulate_4a1(vector<data_t>::const_iterator begin, vector<data_t>::const_iterator end, data_t& init) {
//	auto p1 = begin; auto p2 = begin + 1;
//	auto p3 = begin + 2; auto p4 = begin + 3;
//	for (; p1 != end && p2 != end && p3 != end && p4 != end; p1 += 4, p2 += 4, p3 += 4, p4 += 4)
//		init += ((*p1 + *p2) + (*p3 + *p4));
//	if (p2 == end) init += *p1;
//	else if (p3 == end) init += *p1 + *p2;
//	else if (p4 == end) init += *p1 + *p2 + *p3;
//	return init;
//}
//
//data_t myaccumulate_4a2(vector<data_t>::const_iterator begin, vector<data_t>::const_iterator end, data_t& init1, data_t& init2) {
//	auto p1 = begin; auto p2 = begin + 1;
//	auto p3 = begin + 2; auto p4 = begin + 3;
//	for (; p1 != end && p2 != end && p3 != end && p4 != end; p1 += 4, p2 += 4, p3 += 4, p4 += 4) {
//		init1 += (*p1 + *p2);
//		init2 += (*p3 + *p4);
//	}
//	if (p2 == end) init1 += *p1;
//	else if (p3 == end) init1 += *p1 + *p2;
//	else if (p4 == end) init1 += *p1 + *p2 + *p3;
//	return init1 + init2;
//}
//
//int main() {
//	// initialize the vector
//	vector<data_t> v;
//	constexpr size_t vec_len = 1000000000;
//	for (size_t i = 0; i < vec_len; i++)
//		v.emplace_back(i);
//	auto accum = myaccumulate_2a;
//	constexpr size_t seg_num = 4;
//	constexpr size_t seg_len = vec_len / seg_num;
//	vector<thread> threads_lst;
//	vector<data_t> buf(seg_num);
//	//vector<data_t> buf(seg_num << 1);
//
//	auto begin = chrono::high_resolution_clock::now();
//	auto ptr = v.cbegin();
//
//	for (size_t i = 0; i < seg_num - 1; i++) {
//		auto nect_ptr = ptr + seg_len;
//		// accumulate_block
//		threads_lst.emplace_back(thread(accum, ptr, nect_ptr, ref(buf[i])));
//		// threads_lst.emplace_back(thread(accum, ptr, nect_ptr, ref(buf[i << 1]), ref(buf[1 + (i << 1)])));
//		ptr = nect_ptr;
//	}
//	threads_lst.emplace_back(thread(accum, ptr, v.cend(), ref(buf[seg_num - 1])));
//	//threads_lst.emplace_back(thread(accum, ptr, v.cend(), ref(buf[2 * seg_num - 2]) ,ref(buf[2 * seg_num - 1])));
//
//	for (size_t i = 0; i < seg_num; i++)
//		threads_lst[i].join();
//
//	data_t theSum = 0;
//	for (size_t i = 0; i < seg_num; i++)
//		theSum += buf[i];
//
//	auto end = chrono::high_resolution_clock::now();
//
//	cout << "data scale:\t" << vec_len << endl;
//	cout << "Sum[Concurrency]:\t" << theSum << endl;
//	printf("Time measured[Concurrency]: %.9f\n\n",
//		chrono::duration_cast<chrono::nanoseconds>(end - begin).count() * 1e-9);
//
//
//	// Non-concurrency
//	theSum = 0;
//	data_t theSum2 = 0;
//	begin = chrono::high_resolution_clock::now();
//	theSum = accum(v.cbegin(), v.cend(), theSum);
//	//theSum = accum(v.cbegin(), v.cend(), theSum, theSum2);
//	end = chrono::high_resolution_clock::now();
//	cout << "Sum[Non-concurrency]:\t" << theSum << endl;
//	printf("Time measured: %.9f\n\n",
//		chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() * 1e-9);
//
//}
