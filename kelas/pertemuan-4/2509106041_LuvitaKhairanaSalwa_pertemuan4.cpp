#include <iostream>
using namespace std;

int main() {
    try {
        int pembilang = 10;
        int penyebut = 0;

        if (penyebut == 0) {
            throw "Kesalahan: Pembagian dengan nol!"; // Melempar exception string
        }
        cout << pembilang / penyebut << endl;
    } 
    catch (const char* msg) { // Menangkap exception tipe string
        cerr << msg << endl; 
    }

    return 0;
}
