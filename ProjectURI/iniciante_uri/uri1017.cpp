#include <iostream>
#include <iomanip>
using namespace std;

int main (){
    int time,vel;
    float dist;
    double l;
    cin >> time;
    cin >> vel;
    dist = vel*time;
    l = dist/12;
    cout << fixed << setprecision(3) << l << endl;
    return 0;
}