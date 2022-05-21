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
		sequence(np),
		safe_sequences(np, vector<int>(np))
	{
		for (size_t i = 0; i < np; i++)
		{
			sequence.push_back(i + 1);
		}
	}
	void add_allocation(size_t process, size_t resource, const int val);
	void add_max(size_t process, size_t resource, const int val);
	void add_available(size_t resource, const int val);

	bool check_safety();
	void calculate_need();
	vector<vector<int>> get_safe_sequences();
	matrix get_need() { return need; }


private:
	const size_t num_of_processes, num_of_resource_types;
	vector<int> available;
	matrix max, need, allocation;
	vector<int> sequence;
	vector<vector<int>> safe_sequences;
	void generate_safe_sequences(vector<int> sequence, int low, int high);
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
		if (check_safety())
			safe_sequences.push_back(sequence);
	}
	else
	{
		// Permutations made
		for (int i = low; i <= high; i++)
		{

			// Swapping done
			swap(sequence[low], sequence[i]);

			// Recursion called
			generate_safe_sequences(sequence, low + 1, high);

			//backtrack
			swap(sequence[low], sequence[i]);
		}
	}
}

vector<vector<int>> BankerAlgorithm::get_safe_sequences()
{
	generate_safe_sequences(sequence, 0, num_of_processes - 1);
	return(safe_sequences);
}

bool BankerAlgorithm::check_safety()
{
	vector<int> work(available);
	vector<bool> finished_processes(num_of_resource_types, false);
	calculate_need();

	bool danger = false;
	int current_process;
	for (int i = 0; i < num_of_processes; i++)
	{
		current_process = sequence[i];
		for (int current_resource = 0; current_resource < 3; current_resource++)
		{
			if (need[current_process][current_resource] > work[current_resource]) return false;
			work[current_resource] += allocation[current_process][current_resource];
		}
	}
	return true;
}