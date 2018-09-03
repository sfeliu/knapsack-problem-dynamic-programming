#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <chrono>
using namespace std;

int sumar_conjunto(vector<int> &numbers){
	int suma = 0;
	for(int i = 0; i < numbers.size(); i++){
		suma += numbers[i];
	}
	return suma;
}


/*void find_subsets_n(vector<int> &numbers, vector<int> &subsets, int subset_length){
	// vector<int> subset;
	int partial_sum = 0;
	for(int i=0; i<numbers.size(); subset_length++){
		partial_sum = 0;
		if(i+<numbers.size())
		for(int j=0; j<subset_length && i+j<numbers.size(); j++){
			partial_sum += numbers[i+j];
		}
	}
}*/

vector<int> get_sum_parts(vector<int> numbers, int parts){
	vector<int> sum_parts;
	if(parts==1){
		for(int i=0; i<numbers.size(); i++){
			sum_parts.push_back(numbers[i]);
		}
	}else{
		vector<int> partial_sums;
		vector<int> partial_numbers = numbers;
		for(int i=0; i<numbers.size()-1; i++){
			partial_numbers.erase(partial_numbers.begin());
			partial_sums = get_sum_parts(partial_numbers, parts - 1);
			for(int j=0; j<partial_sums.size(); j++){
				sum_parts.push_back(numbers[i] + partial_sums[j]);
				//cout << partial_sums[j] << endl;
				//cout << "entre" << endl;
			}
		}
	}
	return sum_parts;
}


vector<vector<int>> solveFuerzaBruta(vector<int> numbers, int &cantIteraciones){
	if(numbers.size() == 0){
		vector<vector<int>> partial_sums;
		vector<int> base;
		base.push_back(0);
		base.push_back(0);
		partial_sums.push_back(base);
		cantIteraciones++;
		return partial_sums;
	}else{
		int first_number = numbers[0];
		numbers.erase(numbers.begin());
		vector<vector<int>> partial_sums = solveFuerzaBruta(numbers, cantIteraciones);
		int size = partial_sums.size();
		vector<int> partial_sum;
		for(int i=0; i<size; i++){
			partial_sum.clear();
			partial_sum.push_back(first_number + partial_sums[i][0]);
			partial_sum.push_back(partial_sums[i][1] + 1);
			partial_sums.push_back(partial_sum);
			cantIteraciones++;
		}
		return partial_sums;
	}

	
}

vector<int> get_sum_parts_with_poda(vector<int> numbers, int parts, int value, bool &found){
	vector<int> sum_parts;
	if(parts==1){
		for(int i=0; i<numbers.size() && !found; i++){
			if(numbers[i] == value){
				found = true;
			}else if(numbers[i] < value && numbers[i] != 0){
				sum_parts.push_back(numbers[i]);
			}
		}
	}else{
		vector<int> partial_sums;
		vector<int> partial_numbers = numbers;
		int partial_sum;
		for(int i=0; i<numbers.size()-1 && !found; i++){
			partial_numbers.erase(partial_numbers.begin());
			partial_sums = get_sum_parts(partial_numbers, parts - 1);

			for(int j=0; j<partial_sums.size() && !found; j++){
				partial_sum = numbers[i] + partial_sums[j];
				if(partial_sum == value){
					found = true;
				}else if(partial_sum < value){
					sum_parts.push_back(partial_sum);
					//cout << partial_sums[j] << endl;
					//cout << "entre" << endl;
				}
			}
		}
	}
	return sum_parts;
}

void print_lista(vector<vector<int>> lista){
	cout << "Lista parcial.." << endl << "[";
	for(int i=0; i<lista.size(); i++){
		cout << lista[i][0] << ", ";
	}
	cout << "]" << endl;
}


vector<vector<int>> solveBacktracking(vector<int> numbers, int &cantIteraciones, int expected, int &cardinal){
	if(numbers.size() == 0){
		if(expected == 0){
			cardinal = 0;
		}
		vector<vector<int>> partial_sums;
		vector<int> base;
		base.push_back(0);
		base.push_back(0);
		partial_sums.push_back(base);
		cantIteraciones++;
		return partial_sums;
	}else{
		int first_number = numbers[0];
		numbers.erase(numbers.begin());
		vector<vector<int>> partial_sums = solveBacktracking(numbers, cantIteraciones, expected, cardinal);
		print_lista(partial_sums);
		int size = partial_sums.size();
		for(int i=0; i<size; i++){
			vector<int> partial_sum;
			cout << "Primer numero " << first_number << " sumando al proximo " << partial_sums[i][0] << endl;
			partial_sum.push_back(first_number + partial_sums[i][0]);
			partial_sum.push_back(partial_sums[i][1] + 1);
			if(partial_sum[0] < expected and first_number != 0 and partial_sum[1] < cardinal){
				cout << "Entre con " << partial_sum[0] << endl;
				//partial_sum.push_back(partial_sum[0]);
				//partial_sum.push_back(partial_sum[1]);
				partial_sums.push_back(partial_sum);
				//cout << partial_sums[0][0];
			}else if(partial_sum[0] == expected){
				cout << "Encontre el valor esperado" << endl;
				cardinal = partial_sum[1];
			}
			cantIteraciones++;
		}
		return partial_sums;
	}

	
}


int fuerzaBruta2(vector<int> &numbers, int expected){
	int cantIteraciones = 0;
	vector<vector<int>> all_possible_sums = solveFuerzaBruta(numbers, cantIteraciones);
	int lowest_cardinal = numbers.size() + 1;
	for(int i = 0; i<all_possible_sums.size(); i++){
		if(all_possible_sums[i][0] == expected && all_possible_sums[i][1] < lowest_cardinal){
			lowest_cardinal = all_possible_sums[i][1];
		}
	}
	cout << endl << endl << "Solucion encontrada despues de: " << cantIteraciones << " iteraciones" << endl;
	if(lowest_cardinal == numbers.size() + 1){
		lowest_cardinal = -1;
	}
	return lowest_cardinal;
}


int fuerzaBruta(vector<int> &numbers, int expected){
	for(int i=1; i<= numbers.size(); i++){
		vector<int> sum_parts = get_sum_parts(numbers, i);
		for(int j=0; j<sum_parts.size(); j++){
			if(sum_parts[j] == expected){
				cout << "encontre el numero esperado" << endl;
				return i;
			}
		}
	}
	return -1;
}



int backtracking(vector<int> &numbers, int expected){
	bool found = false;
	for(int i=1; i<= numbers.size(); i++){
		vector<int> sum_parts = get_sum_parts_with_poda(numbers, i, expected, found);
		if(found){
			return i;
		}
	}
	return -1;
}



int backtracking2(vector<int> &numbers, int expected){
	int cantIteraciones = 0;
	int lowest_cardinal = numbers.size() + 1;
	vector<vector<int>> factible_sums = solveBacktracking(numbers, cantIteraciones, expected, lowest_cardinal);
	cout << endl << endl << "Solucion encontrada despues de: " << cantIteraciones << " iteraciones" << endl;
	if(lowest_cardinal == numbers.size() + 1){
		lowest_cardinal = -1;
	}
	return lowest_cardinal;
}


int main(int argc, char *argv[]){
	if(argc < 2){
		cout << "Missing file parameter...";
		return -1;
	}
	ifstream infile;
	infile.open(argv[1]);
	int vector_size, searching_value;
	bool encontre;
	infile >> vector_size >> searching_value;
	vector<int> numbers;
	int number;
	for(int i = 0; i < vector_size && infile; i++){
		infile >> number;
		numbers.push_back(number);
	}
	infile.close();
	cout << "Your vector is:" << endl;
	for(int i = 0; i < vector_size; i++){
		cout << numbers[i] << " ";
	}
	cout << endl;
	cout << endl;
	cout << "And your Expected value is: " << searching_value << endl; 
/*
	vector<int> nparts = get_sum_parts(numbers, 4);
	for(int i=0; i<nparts.size(); i++){
		cout<<endl;
		cout<<nparts[i];
	}
	*/


    cout << "steady_clock" << endl;
    cout << chrono::steady_clock::period::num << endl;
    cout << chrono::steady_clock::period::den << endl;
    cout << "steady = " << boolalpha << chrono::steady_clock::is_steady << endl << endl;


    cout << endl << endl;
    auto startFuerzaBruta = chrono::steady_clock::now();
	int cardinal = fuerzaBruta(numbers, searching_value);
	cout << cardinal;
	cout<<endl;
    auto endFuerzaBruta = chrono::steady_clock::now();
    auto diffFuerzaBruta = endFuerzaBruta - startFuerzaBruta;
    cout << "Tiempo utilizado por Fuerza bruta " << chrono::duration <double, milli> (diffFuerzaBruta).count() << " ms" << endl;

    cout << endl << endl;
    auto startFuerzaBruta2 = chrono::steady_clock::now();
	cardinal = fuerzaBruta2(numbers, searching_value);
	cout << cardinal;
	cout<<endl;
    auto endFuerzaBruta2 = chrono::steady_clock::now();
    auto diffFuerzaBruta2 = endFuerzaBruta2 - startFuerzaBruta2;
    cout << "Tiempo utilizado por True Fuerza bruta " << chrono::duration <double, milli> (diffFuerzaBruta2).count() << " ms" << endl;


    cout << endl << endl;
    auto startBackTracking = chrono::steady_clock::now();
	cardinal = backtracking(numbers, searching_value);
	cout << cardinal;
	cout<<endl;
    auto endBackTracking = chrono::steady_clock::now();
    auto diffBackTracking = endBackTracking - startBackTracking;
    cout << "Tiempo utilizado por Back Tracking " << chrono::duration <double, milli> (diffBackTracking).count() << " ms" << endl;


    cout << endl << endl;
    auto startBackTracking2 = chrono::steady_clock::now();
	cardinal = backtracking2(numbers, searching_value);
	cout << cardinal;
	cout<<endl;
    auto endBackTracking2 = chrono::steady_clock::now();
    auto diffBackTracking2 = endBackTracking2 - startBackTracking2;
    cout << "Tiempo utilizado por True Back Tracking " << chrono::duration <double, milli> (diffBackTracking2).count() << " ms" << endl;
    
}