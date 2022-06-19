#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

/**
 * A 2D vector that stores integers.
*/
typedef vector<vector<int>> matrix;

/**
 * @brief A that implements a simulation of the Banker's algorithm 
 * to get safe sequences to execute processes in an operation system.
 */
class BankerAlgorithm
{
public:
	/**
	 * @brief Construct a new Banker Algorithm object
	 *
	 * @param numOfProcesses
	 * @param numOfResourceTypes
	 */
	BankerAlgorithm(size_t numOfProcesses, size_t numOfResourceTypes);

	/**
	 * @brief
	 *
	 * @param process
	 * @param resource
	 * @param numOfInstances
	 */
	void add_allocation(size_t process, size_t resource, const int numOfInstances);

	/**
	 * @brief
	 *
	 * @param process
	 * @param resource
	 * @param numOfInstances
	 */
	void add_max(size_t process, size_t resource, const int numOfInstances);

	/**
	 * @brief
	 *
	 * @param resource
	 * @param val
	 */
	void add_available(size_t resource, const int val);

	/**
	 * @brief
	 *
	 * @param test_sequence
	 * @return true
	 * @return false
	 */
	bool check_safety(vector<int> test_sequence);

	/**
	 * @brief
	 *
	 */
	void calculate_need();

	/**
	 * @brief Get the safe sequences object
	 *
	 */
	void get_safe_sequences();

	/**
	 * @brief
	 *
	 * @param process
	 * @param requested_resource
	 * @return True if the request is safe to be granted. False if the request would make the system unsafe.
	 */
	bool request(size_t process, vector<int> requested_resource);

	/**
	 * @brief Get the need object
	 *
	 * @return matrix
	 */
	matrix get_need() { return need; }

	/**
	 * @brief print the safe sequences to execute the processes.
	 * 
	 */
	void print_solution();

private:
	/// The number of processes currently in the system
	const size_t numOfProcesses; 

	/// The number of resource types currently in the system.
	const size_t numOfResourceTypes;

	///Each element represents the number of instances of a resource type. Each index represents a resource type.
	vector<int> available;

	/**
	 * The first index represents the process. 
	 * The second index represents the resource type. 
	 * The value represents the max number of instances this process can request from this resource type.
	*/
	matrix max;
	
	/**
	 * The first index represents the process. 
	 * The second index represents the resource type. 
	 * The value represents the number of instances this process needs from this resource type.
	*/ 
	matrix need;

	/**
	 * The first index represents the process. 
	 * The second index represents the resource type. 
	 * The value represents the max number of instances this process holds from this resource type.
	*/ 
	matrix allocation;
	vector<int> sequence;
	vector<vector<int>> safe_sequences;

	void generate_safe_sequences(vector<int> sequence, int low, int high);
	bool process_is_safe_to_run(int current_process, vector<int> work);
	void run_process(int current_process, vector<int> &work);
	template <class T>
	void swap(T &x, T &y)
	{
		T temp = x;
		x = y;
		y = temp;
	}
	void print_matrix(vector<vector<int>> mat);
};

inline BankerAlgorithm::BankerAlgorithm(size_t numOfProcesses, size_t numOfResourceTypes)
	: numOfProcesses(numOfProcesses),
	  numOfResourceTypes(numOfResourceTypes),
	  available(numOfResourceTypes, 0),
	  max(numOfProcesses, vector<int>(numOfResourceTypes, 0)),
	  allocation(numOfProcesses, vector<int>(numOfResourceTypes, 0)),
	  need(numOfProcesses, vector<int>(numOfResourceTypes, 0)),
	  sequence(numOfProcesses)
{
	for (size_t i = 0; i < numOfProcesses; i++)
		sequence[i] = i + 1;
}

void BankerAlgorithm::add_allocation(size_t process, size_t resource, const int val)
{
	allocation[process][resource] += val;
}

void BankerAlgorithm::add_max(size_t process, size_t resource, const int val)
{
	max[process][resource] += val;
}

void BankerAlgorithm::add_available(size_t resource, const int val)
{
	available[resource] += val;
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

inline void BankerAlgorithm::print_solution()
{
	cout << "The safe ways to execute are:\n";
	print_matrix(safe_sequences);
}

void BankerAlgorithm::calculate_need()
{
	for (size_t i = 0; i < numOfProcesses; i++)
		for (size_t j = 0; j < numOfResourceTypes; j++)
			need[i][j] = max[i][j] - allocation[i][j];
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------*/

void BankerAlgorithm::get_safe_sequences()
{
	safe_sequences = matrix();
	calculate_need();
	generate_safe_sequences(sequence, 0, numOfProcesses - 1);
}

void BankerAlgorithm::generate_safe_sequences(vector<int> sequence, int low, int high)
{
	if (low == high)
	{
		if (check_safety(sequence))
			safe_sequences.push_back(sequence);
		return;
	}
	for (int i = low; i <= high; i++)
	{
		swap(sequence[low], sequence[i]);
		generate_safe_sequences(sequence, low + 1, high);
		swap(sequence[low], sequence[i]);
	}
}

bool BankerAlgorithm::check_safety(vector<int> test_sequence)
{
	vector<int> work(available);
	vector<bool> finished_processes(numOfResourceTypes, false);
	int current_process;
	for (int i = 0; i < numOfProcesses; i++)
	{
		current_process = test_sequence[i] - 1;
		if (!process_is_safe_to_run(current_process, work))
			return false;
		run_process(current_process, work);
	}
	return true;
}

inline bool BankerAlgorithm::process_is_safe_to_run(int current_process, vector<int> work)
{
	for (int current_resource = 0; current_resource < numOfResourceTypes; current_resource++)
		if (need[current_process][current_resource] > work[current_resource])
			return false;
	return true;
}

inline void BankerAlgorithm::run_process(int current_process, vector<int> &work)
{
	for (int current_resource = 0; current_resource < numOfResourceTypes; current_resource++)
		work[current_resource] += allocation[current_process][current_resource];
}

bool BankerAlgorithm::request(size_t process, vector<int> requested_resource)
{
	bool grant = true;

	for (int i = 0; i < numOfResourceTypes; i++)
	{
		available.at(i) -= requested_resource.at(i);
		need.at(process).at(i) -= requested_resource.at(i);
		add_allocation(process, i, requested_resource.at(i));
	}
	get_safe_sequences();
	if (safe_sequences.empty())
		grant = false;
	return grant;
}
