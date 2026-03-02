#include <iostream>
using namespace std;

int main() {
    string username, password;
    string UserAsli = "Vita";   
    string passwordAsli = "041";    
    int attempt = 0; // Berfungsi agar pas melakukan percobaan login dimulai  dari 0

    
    while (attempt < 3) {
        cout << "\n=============================================\n";
        cout << "                   LOGIN                     \n";
        cout << "=============================================\n";
        cout << "  Username  : ";
        cin >> username;
        cout << "  Password  : ";
        cin >> password;
        cout << "---------------------------------------------\n";

        if (username == UserAsli && password == passwordAsli) {
            cout << "Login Berhasil!\n\n";
            break;
        } else {
            cout << "Login Salah!\n\n";
            attempt++;
        }

        if (attempt == 3) {
            cout << "Anda gagal login 3 kali. Program berhenti.\n";
            return 0;
        }
    }

    int pilihan = 0;
    double nilai;

    while (pilihan != 4) {

        cout << "\n=====================================\n";
        cout << "           MENU KONVERSI             \n";
        cout << "=====================================\n";
        cout << "  1. Meter      -> Kilometer & Cm    \n";
        cout << "  2. Kilometer  -> Meter & Cm        \n";
        cout << "  3. Centimeter -> Meter & Km        \n";
        cout << "  4. Keluar                          \n";
        cout << "-------------------------------------\n";
        cout << "  Pilih menu [1-4] : ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                cout << "Masukkan nilai Meter: ";
                cin >> nilai;
                cout << "Hasil:\n";
                cout << nilai / 1000 << " Kilometer\n";
                cout << nilai * 100 << " Centimeter\n";
                break;

            case 2:
                cout << "Masukkan nilai Kilometer: ";
                cin >> nilai;
                cout << "Hasil:\n";
                cout << nilai * 1000 << " Meter\n";
                cout << nilai * 100000 << " Centimeter\n";
                break;

            case 3:
                cout << "Masukkan nilai Centimeter: ";
                cin >> nilai;
                cout << "Hasil:\n";
                cout << nilai / 100 << " Meter\n";
                cout << nilai / 100000 << " Kilometer\n";
                break;

            case 4:
                cout << "Terima kasih sudah menggunakan program ini!\n";
                break;

            default:
                cout << "Pilihan tidak valid!\n";
        }
    }

    return 0;
}