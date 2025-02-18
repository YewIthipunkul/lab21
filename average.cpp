#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <cmath> 
using namespace std;

int main(int argc, char *argv[]) {
    if (argc<2) {
        cout<<"Please input numbers to find average."<<'\n';
        return 1;
    } 
    vector<double> numbers;
    double sum =0.0;

    for (int i=1; i<argc; i++) {
        double num = atof(argv[i]);
        numbers.push_back(num);
        sum += num;
    }
    double avg = sum/numbers.size();
    cout<<"---------------------------------"<<'\n';
    if (fmod(avg, 1.0) == 0.0) {
        cout<<"Average of "<<numbers.size()<<" numbers = "<<fixed<<setprecision(0)<<avg<<'\n';
    } else {
        cout<<"Average of "<<numbers.size()<<" numbers = "<<fixed<<setprecision(3)<<avg<<'\n';
    }
    cout<<"---------------------------------"<<'\n';

    return 0;
}
