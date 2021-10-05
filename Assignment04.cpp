// Author: Avery Nguyen
// Section: 1002
// Date Last Modified: 9/28/2021
// Program Description: This program will demonstrate understanding of threads and mutex functions
#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <mutex>
using namespace std;
mutex t_lock;
//global vectors
    vector<short> num1;
    vector<short> num2;
    vector< vector<short> > vectorstorage;
//function prototypes
    void multiply( int num, int place);
    void add(vector<short> &answer);
//------------------------------
//MAIN FUNCTION
//------------------------------
int main() {
    string firstnum;
    string secondnum;
    int temp = 0;
    int place = 0;
    vector<short> answer;
    vector<thread> threads;
    int maxThreads = thread::hardware_concurrency();
//Reads in the user input of number 1 and number 2
    cout << "Enter number1: " ;
    cin >> firstnum;
    cout << "Enter number2: " ;
    cin >> secondnum;
//Populates the vectors with the given numbers
    for(int i = 0; i < firstnum.size(); i++){
        temp = firstnum[i] - '0';
        num1.push_back(temp);
    }
    
    for(int i = 0; i < secondnum.size(); i++){
        temp = secondnum[i]- '0';
        num2.push_back(temp);
    }
//Populates empty vector answer of maximum lenght.
    for(int i = 0; i < secondnum.size() + firstnum.size(); i++){
        temp = 0;
        answer.push_back(temp);
    }
 
//thread loops
    place = num2.size();
    for(int i = 0; i < num2.size(); i++){
        //creates multiply function thread
        place--;
        threads.push_back( thread(multiply, num2[i], place) );
      
        //ensures no more threads are made than the system can handle
        if(threads.size() % maxThreads == 0){
            for (int j = 0; j < threads.size(); j++){
                threads[j].join();
            }
            threads.clear();
        }
    }
    for(int i = 0; i < threads.size(); i++)
        threads[i].join();
    threads.clear();
    //calls the add function
    add(answer);
    //prints out answer prompt
    cout << "The product is: " ;
    //prints the answer excluding leading 0's
    bool leadingzero = true;
    for(int i = 0; i < answer.size(); i++)
    if(answer[i] == 0 &&  leadingzero == true){
    }
    else{
        cout << answer[i];
        leadingzero = false;
    }
    if(leadingzero == true){
        cout << "0" ;
    }
    return 0;
}
//------------------------------
// FUNCTIONS
//------------------------------
    void multiply( int num, int place){
        int num1it = num1.size()-1;
        int temp = 0;
        int largest = num1.size() + num2.size();
        int ans = 0;
        vector<short> result;
        int remainder = 0;
        //initializes vector of 0's with the maximum possible spacing
        for(int i = 0; i < largest; i++){
            result.push_back(0);
        }
       
        //makes iterator for result
        int iterator = result.size()-1 - place;
        //loops, multiplying numbers, adding the remainder, and then finding new ans and remainder
        for(int i = 0; i < num1.size(); i++){
            temp = num1[num1it] * num;
           
            temp = temp + remainder;
            ans = temp%10;
            remainder = temp/10;
            result[iterator] = ans;
            iterator--;
            num1it--;
        }
        //if final remainder doesn't equal 0 then places remainder in front position
        if(remainder != 0){
            result[iterator] = remainder;
        }
        //pushesback into 2d vector
        t_lock.lock();
        vectorstorage.push_back(result);
        t_lock.unlock();
    }
    void add( vector<short> &answer){
        int tempsum = 0;
        int ans = 0;
        int remainder = 0;
        int bigit = vectorstorage.size()-1;
        int smallit = vectorstorage[0].size()-1;
        //runs through every line vertically from right to left of 2d vector
        for(int i = 0; i < vectorstorage[0].size(); i++){
            bigit = vectorstorage.size()-1;
            //runs through vertical lines adding each number and carrying remainder
            for(int j = 0; j < vectorstorage.size(); j++){
                tempsum = tempsum + vectorstorage[bigit][smallit];
                bigit--;
            }
            tempsum = tempsum + remainder;
            ans = tempsum%10;
            remainder = tempsum/10;
            answer[smallit] = ans;
            smallit--;
            tempsum = 0;
        }
    }









