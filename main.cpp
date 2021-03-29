#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

//
// checkArrays
//
// checks to make sure the data was input correctly
//

void checkArrays(int accounts[], double balances[], int N) {
    cout << fixed;
    cout << setprecision(2);
    cout << "** Checking arrays..." << endl;
    cout << "1. " << accounts[0] << ", $" << balances[0] << endl;
    cout << N << ". " << accounts[N-1] << ", $" << balances[N-1] << endl;
}

//
// search
//
// Searches for the account that matches "acct" and returns its index
// if not found -1 is returned.
//

int search(int accounts[], int N, int acct){
    for (int i = 0; i < N; ++i){
        if (accounts[i] == acct){
            return i;
        }
    }
    return -1;
}

//
// maxBalance
//
//
// Searches for the highest balance and returns index of account
// If there's a tie the first index is returned
//

int maxBalance(double balances[], int N){
    double max = 0;
    int max_index;
    
    for (int i = 0; i < N; ++i){
        if (balances[i] > max){
            max = balances[i];
            max_index = i;
        }
    } 
    return max_index;
}

int main() {
    cout << "** Welcome to UIC Bank v2.0 **" << endl;
    
    //
    // (1) Input banking filename, confirm file can be opened, and input the 5 bank accounts:
    //
    
    string filename;
    cout << "Enter bank filename> " << endl;
    cin >> filename;
    
    ifstream  infile;
    infile.open(filename);
    
    cout << "** Inputting account data..." << endl;
   
    if (!infile.good()) {
      cout << "**Error: unable to open input file '" << filename << "'" << endl;
      return 0;
     } 
    
    //
    // (2) Display account data in order
    //
    
    int N;
    infile >> N;
    
    int* A = new int[N];
    double* B = new double[N];

    int customer;
    double balance;
    
    for (int i = 0; i < N; ++i){
        infile >> customer;
        A[i] = customer;
       
        infile >> balance;
        B[i] = balance;
   }
    
    checkArrays(A, B, N);
    
    //
    // (3) Prompt the user for commands and execute commands until 'x' is entered
    //
    
    cout << "** Processing user commands..." << endl;
    
    string command;
    
    cout << "Enter command (+, -, ?, ^, *, <, $, add, del, x): " << endl;
    cin >> command;
    
    int account;
    double amount;
    
    while (command != "x"){
        
        if (command == "+"){
            cin >> account;
            cin >> amount;
            
            int x = search(A, N, account);
            
            if (x != -1){
                B[x] = B[x] + amount;
                cout << "Account " << account << ": balance $" << fixed << setprecision(2) << B[x] << endl;
            }
            else {
                cout << "** Invalid account, transaction ignored" << endl;
            }
        }
        else if (command == "-"){
            cin >> account;
            cin >> amount;
            
            int x = search(A, N, account);
            
            if (x != -1){
                B[x] = B[x] - amount;
                cout << "Account " << account << ": balance $" << fixed << setprecision(2) << B[x] << endl;     
            }
            else {
                cout << "** Invalid account, transaction ignored" << endl;
            }
        }
        else if (command == "?"){
            cin >> account;
            
            int x = search(A, N, account);
            
            if (x != -1){
                cout << "Account " << account << ": balance $" << fixed << setprecision(2) << B[x] << endl;   
            }
            else {
                cout << "** Invalid account, transaction ignored" << endl;
            }
        }
        else if (command == "^"){
            int x = maxBalance(B, N);
                
            cout << "Account " << A[x] << ": balance $" << fixed << setprecision(2) << B[x] << endl;
        }
        else if (command == "*"){
            int low, high, low_index, high_index;
                       
            cin >> low;
            cin >> high;
            
            low_index = 0;
            high_index = N-1;
            
            for (int i = 0; i < N; ++i){
                if (A[i] == low){
                    low_index = i;
                }    
                else if (low > A[i] && low < A[(i+1)]) {
                    low_index = (i+1);
                }
            }
                
           for (int i = 0; i < N; ++i){               
               if (A[i] == high){
                    high_index = i;
                } 
                else if (high > A[i]) {
                    high_index = (i);
                }
            }

            for (int i = low_index; i < high_index+1; ++i){
                cout << "Account " << A[i] << ": balance $" << fixed << setprecision(2) << B[i] << endl;
            }
        }
        else if (command == "<"){
            for (int i = 0; i < N; ++i){
                if (B[i] < 0){
                    cout << "Account " << A[i] << ": balance $" << fixed << setprecision(2) << B[i] << endl;
                }
            }
        }
        else if (command == "$"){
            double total = 0;
            
            for (int i = 0; i < N; ++i){
                if (B[i] > 0){
                    total = total + B[i];
                }
            }
            cout << "Total deposits: $" << total << endl;
        }
        else if (command == "add"){
            int acct_num = A[N-1] + 1;
            
            int* new_A = new int[N+1];
            double* new_B = new double[N+1];
            
            for (int i = 0; i < N; ++i){
                new_A[i] = A[i];
                new_B[i] = B[i];
            }
            new_A[N] = acct_num;
            new_B[N] = 0.00;
            
            delete[] A;
            delete[] B;
            
            A = new_A;
            B = new_B;
            
            N += 1;
            
            cout << "Added account " << A[N-1] << ": balance $" << B[N-1] << endl;
        }
        else if (command == "del"){
            int del_num;
            cin >> del_num;
            
            int x = search(A, N, del_num);
            
            if (x != -1){
                int* del_A = new int[N-1];
                double* del_B = new double[N-1];
            
                for (int i = 0; i < x; ++i){
                    del_A[i] = A[i];
                    del_B[i] = B[i];
                }
                
                for (int i = x; i < N-1; ++i){
                    del_A[i] = A[i+1];
                    del_B[i] = B[i+1];
                }
                
                N = N - 1;
            
                delete[] A;
                delete[] B;
            
                A = del_A;
                B = del_B;
            
                cout << "Deleted account " << del_num << endl;  
            }
            else {
                cout << "** Invalid account, transaction ignored" << endl;
            }
        }
        else {
            cout << "** Invalid command, try again..." << endl;
        }
        cout << "Enter command (+, -, ?, ^, *, <, $, add, del, x): " << endl;
        cin >> command;
    }
    
    //
    // (4) Update banking file and end program
    //
    
    cout << "** Saving account data..." << endl;
    cout << "** Done **" << endl;
    
    infile.close();
    
    ofstream  outfile;
    outfile.open(filename);
    
    outfile << N << endl;
    
    for (int i = 0; i < N; ++i){
        outfile << A[i] << " " << fixed << setprecision(2) << B[i] << endl;
    }    
    
    outfile.close();
    delete[] A;
    delete[] B;

    return 0;
}