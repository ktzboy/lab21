#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    if(argc == 1) cout << "Please input numbers to find average.";
    else {
        float sum = 0;
        for(int i=0 ; i<argc-1 ; i++) sum += atof(argv[i+1]);
        
        cout << "---------------------------------\n";
        cout << "Average of " << argc-1 << " numbers = " << sum/(argc-1);
        cout << "\n---------------------------------";
    }
    
    return 0;
}
