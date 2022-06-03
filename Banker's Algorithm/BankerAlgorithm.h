#pragma once
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<vector<int>> matrix;

class BankerAlgorithm
{
public:
	BankerAlgorithm(size_t np, size_t nr)
		: num_of_processes(np),
		num_of_resource_types(nr),
		available(nr),
		max(np, vector<int>(nr, 0)),
		allocation(np, vector<int>(nr, 0)),
		need(np, vector<int>(nr, 0)),
		sequence(np)
	{
		for (size_t i = 0; i < np; i++)
		{
			sequence[i] = i + 1;
		}
	}
	void add_allocation(size_t process, size_t resource, const int val);
	void add_max(size_t process, size_t resource, const int val);
	void add_available(size_t resource, const int val);

	bool check_safety(vector<int> test_sequence);
	void calculate_need();
	void get_safe_sequences();
	matrix get_need() { return need; }
	void print_solution();


private:
	const size_t num_of_processes, num_of_resource_types;
	vector<int> available;
	matrix max, need, allocation;
	vector<int> sequence;
	vector<vector<int>> safe_sequences;
	void generate_safe_sequences(vector<int> sequence, int low, int high);
	template<class T>
	void swap(T& x, T& y) 
	{
		T temp = x; x = y; y = temp;
	}
	void print_matrix(vector<vector<int>> mat);
};

void BankerAlgorithm::add_allocation(size_t process, size_t resource, const int val)
{
	allocation[process][resource] = val;
}

void BankerAlgorithm::add_max(size_t process, size_t resource, const int val)
{
	max[process][resource] = val;
}

void BankerAlgorithm::add_available(size_t resource, const int val)
{
	available[resource] = val;
}

void BankerAlgorithm::calculate_need()
{
	for (size_t i = 0; i < num_of_processes; i++)
		for (size_t j = 0; j < num_of_resource_types; j++)
			need[i][j] = max[i][j] - allocation[i][j];
}

void BankerAlgorithm::generate_safe_sequences(vector<int> sequence, int low, int high)
{
	if (low == high)
	{
		if (check_safety(sequence)) safe_sequences.push_back(sequence);
		return;
	}
	for (int i = low; i <= high; i++)
	{
		swap(sequence[low], sequence[i]);
		generate_safe_sequences(sequence, low + 1, high);
		swap(sequence[low], sequence[i]);
	}
}

inline void BankerAlgorithm::print_matrix(vector<vector<int>> mat)
{
	for (size_t i = 0; i < mat.size(); i++)
	{
		for (size_t j = 0; j < mat[i].size(); j++)
			cout << mat[i][j] << " ";
		cout << "\n";
	}
}

void BankerAlgorithm::get_safe_sequences()
{
	calculate_need();
	generate_safe_sequences(sequence, 0, num_of_processes - 1);
}

inline void BankerAlgorithm::print_solution()
{
	cout << "The safe ways to execute are:\n";
	print_matrix(safe_sequences);
}

bool BankerAlgorithm::check_safety(vector<int> test_sequence)
{
	vector<int> work(available);
	vector<bool> finished_processes(num_of_resource_types, false);
	int current_process;
	for (int i = 0; i < num_of_processes; i++)
	{
		current_process = test_sequence[i] - 1;
		for (int current_resource = 0; current_resource < 3; current_resource++)
		{
			if (need[current_process][current_resource] > work[current_resource]) return false;
			work[current_resource] += allocation[current_process][current_resource];
		}
	}
	return true;
}