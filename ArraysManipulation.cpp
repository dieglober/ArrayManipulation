// ArraysManipulation.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Autor:; Diego Rozo Herrera
//

#include <iostream>
#include <vector>
#include <algorithm> //std::copy_if
#include <numeric>   //std::accumulate
#include <execution> // for std:reduce


using namespace std;

void print(vector<int> const& input)
{
    copy(input.begin(), input.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

int main()
{
    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> evenNumbers;
    vector<int> mappedNumbers;

    
    //filter
    copy_if(numbers.begin(), numbers.end(), back_inserter(evenNumbers), [](int i) { return i % 2 == 0; });
    print(evenNumbers);

    //map: Cambios a elementos de un array obteniendo un nuevo array de elementos transformados 
    transform(numbers.begin(), numbers.end(), back_inserter(mappedNumbers), [](int i) { return i * 2; });
    print(mappedNumbers);

    //reduce
    int result = accumulate(numbers.begin(), numbers.end(), 0, [](int a, int b) { return a + b; });
    cout << result << endl;

    //reduce: Si el array tuviera muchos datos se puede elegir la politica de ejecucion
    // por ejemplo en paralelo aprovechando los procesadores modernos multicore    
    
    /* 
    ===============
    https://blog.tartanllama.xyz/accumulate-vs-reduce/
    Execution policies
    Execution policies are a C++17 feature which allows programmers to ask for algorithms to be parallelised.There are three execution policies in C++17:

    std::execution::seq – do not parallelise
        std::execution::par – parallelise
        std::execution::par_unseq – parallelise and vectorise(requires that the operation can be interleaved, so no acquiring mutexes and such)
    ===============

    */

    //Nota: modificar las propiedades del proyecto ISO C++17 Standard (/std:c++17) o superior

    int reduceResult = reduce(execution::par, numbers.begin(), numbers.end(), 0, [](int a, int b) { return a + b; });
    cout << reduceResult << endl;
    


}
