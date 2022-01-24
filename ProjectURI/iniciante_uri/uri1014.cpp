#include <iostream>
#include <iomanip>
using namespace std;

int main (){
    int km;
    float l;
    double cons;
    cin >> km;
    cin >> l;
    cons = km/l;
    cout << fixed << setprecision(3) << cons << " km/l" << endl;

    return 0;
}