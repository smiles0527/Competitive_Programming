#include <bits/stdc++.h> //basically covers every sort of #include, which generally is around the same as import java*, etc
// or you can manually include every single header file
#include <iostream> //for input and output
#include <string> //for string
#include <vector> //for vector (which is sort of like arraylist)
#include <algorithm> //for algorithm
#include <cmath> //for math
#include <cstdio> //for printf and scanf
#include <cstdlib> //for malloc and free
#include <cstring> //for memset and memcpy
#include <cctype> //for isalpha and isdigit
#include <cassert> //for assert
#include <cfloat> //for FLT_MAX and FLT_MIN
//etc and goes on and on

using namespace std; //so you don't have to do std::cout, std::cin to everything, etc

int main(){  // main function (which is nice because it doesn't depend on the name of the file)
    //cout is the same as println in java
    cout << "Hello World" << endl; //endl is the same as \n in java
    //cin is the same as Scanner in java
    //cin is so much easier to use than Scanner in java as you literally just do cin >> x; LMAO
    //for strings, it's another story. but for now, cin is fine enough.

    int x;
    cin >> x;
    cout << x << endl;
    return 0; //return 0 is the same as return in java

    //a stupid thing is that you need to #include <string> to actually use string
    string s; //note that it's lowercased unlike java (i think i wrote lowercase for apcsa frq but oh well)
    s = "Hello World";
    cout << s << endl;

    //for arrays, you can do this:  
    int arr[10]; //this is the same as int[] arr = new int[10]; in java
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    cout << arr[0] << endl;
    cout << arr[1] << endl;
    cout << arr[2] << endl;
    
    //note that in cpp int[] is not dynamic of which can cause some logic errors
    //in CP (compettve programming) it's much more powerful to use dynamic arrays (which you migh recall in java as arraylist)
    //here, it's called vector
    vector<int> v; //this is the same as ArrayList<Integer> v = new ArrayList<Integer>(); in java
    //inside the <>, you can put int, string, etc.
    //note that vector is dynamic, so you don't need to specify the size like you do in java
    //you can also do vector<int> v(10); to initialize a vector of size 10
    //you can also do vector<int> v = {1, 2, 3}; to initialize a vector with values 1, 2, 3
    //you can also do vector<int> v = v1; to copy a vector
    //you can also do vector<int> v1(v2); to copy a vector
    //you can also do vector<int> v1 = v2; to copy a vector

    v.push_back(1); //this is the same as v.add(1); in java
    v.push_back(2);
    v.push_back(3);
    cout << v[0] << endl;
    cout << v[1] << endl;
    cout << v[2] << endl;
    
    //you can also put a vector inside a vector
    vector<vector<int>> v2; //this is the same as ArrayList<ArrayList<Integer>> v2 = new ArrayList<ArrayList<Integer>>(); in java
    v2.push_back(v); //this is the same as v2.add(v); in java
    cout << v2[0][0] << endl;
    cout << v2[0][1] << endl;
    cout << v2[0][2] << endl;
    
    //you can also put a vector inside a vector inside a vector
    vector<vector<vector<int>>> v3; //this is the same as ArrayList<ArrayList<ArrayList<Integer>>> v3 = new ArrayList<ArrayList<ArrayList<Integer>>>(); in java
    v3.push_back(v2); //this is the same as v3.add(v2); in java
    cout << v3[0][0][0] << endl;
    cout << v3[0][0][1] << endl;
    cout << v3[0][0][2] << endl;
    
    //you can also put a vector inside a vector inside a vector inside a vector
    vector<vector<vector<vector<int>>>> v4; //this is the same as ArrayList<ArrayList<ArrayList<ArrayList<Integer>>>> v4 = new ArrayList<ArrayList<ArrayList<ArrayList<Integer>>>>(); in java
    //ok... i think you get the point

    //heres just a list of vector methods

    //you can also do v.size() to get the size of the vector
    //you can also do v.clear() to clear the vector
    //you can also do v.empty() to check if the vector is empty
    //you can also do v.pop_back() to remove the last element of the vector
    //you can also do v.insert(v.begin() + 1, 4); to insert 4 at the second index
    //you can also do v.erase(v.begin() + 1); to erase the second element
    //you can also do v.sort(v.begin(), v.end()); to sort the vector
    //you can also do v.reverse(v.begin(), v.end()); to reverse the vector
    //you can also do v.find(v.begin(), v.end(), 4); to find the first occurrence of 4
    //you can also do v.count(4); to count the number of occurrences of 4
    //you can also do v.max_element(v.begin(), v.end()); to find the maximum element
    //you can also do v.min_element(v.begin(), v.end()); to find the minimum element
    //you can also do v.sum(v.begin(), v.end()); to find the sum of the vector
    //you can also do v.average(v.begin(), v.end()); to find the average of the vector
    
    //examples for each ones above
    v.size();
    v.clear();
    v.empty();
    v.pop_back();
    v.insert(v.begin() + 1, 4);
    v.erase(v.begin() + 1);
    v.sort(v.begin(), v.end());



    //forloops and whileloops are the same as in java
    //for(int i = 0; i < 10; i++){
    //    cout << i << endl;
    //}
    //while(condition){
    //    cout << "Hello World" << endl;
    //}
    


    //now this applies to higher level stuff in DSA - data structures and algorithms

    //in DSA, we don't only use arrays and vectors, we also use other data structures
    //we use things like stacks, queues, linked lists, trees, graphs, etc.
    //im not so sure about the syntax in java, but FOR SURE, CPP IS MATHEMATICALLY MORE POWERFUL THAN JAVA 
                                                    //although java does have more libraries and frameworks, contests use c++ cuz of the fast mathematical computations and efficiency and yada yada
    //one of the main advantages for C++ is also the feature of STL

    //you've already seen some samples of STL in the vector section!!
    //stl = standard template library
    //stl is a library of generic classes and functions that provide common data structures and algorithms
    //stl is a part of the c++ standard library
    //kind of like java.util in java, but for c++ (and yes since i'm biased, it's more powerful)
}