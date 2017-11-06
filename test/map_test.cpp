#include <unordered_map>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include "data/load.h"
#include "../src/util/util.h"
#include "../src/hash_func.h"
#include "../lib/MurmurHash3.h"
#include "time_lapse.h"

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::back_insert_iterator;
using std::back_inserter;
using std::copy;

template <typename T>
using hash = gud::murmur_hash<T>;

template <typename K, typename V>
using hash_map = std::unordered_map<K, V, hash<K> >;

vector<string> load_test_data(const string& filename);
void test_insert(hash_map<string, string>& test_map, const vector<string>& data);

int main()
{
	string dataFile = "test/data/composers.txt";
	vector<string> data = load_test_data(dataFile);
	hash_map<string, string> test_map;
	
	cout << "Inserting: " << data.size() << " entries" << endl;
	cout << "Time: " << time_lapse::measure<>::execution(test_insert, test_map, data) << " ms" << endl;
	cout << "Resulting Bucket Count: " << test_map.bucket_count() << endl;
	cout << "Resulting Load Factor: " << test_map.load_factor() << endl;
}

vector<string> load_test_data(const string& filename)
{
	vector<string> data;
	vector<string> lines = load_text_file(filename);
	vector<string> split;
	back_insert_iterator< vector<string> > dataItr = back_inserter(data);
	for (vector<string>::iterator itr = lines.begin(), end = lines.end();
			itr < end; itr++)
	{
		split = gud::split(*itr, ' ');
		copy(split.begin(), split.end(), dataItr);
	}

	return data;
}

void test_insert(hash_map<string, string>& test_map, const vector<string>& data)
{
	int i = 0;
	for (vector<string>::const_iterator itr = data.begin(), end = data.end();
			itr < end; itr++, i++)
	{
		test_map[*itr] = *itr;
	}
}
