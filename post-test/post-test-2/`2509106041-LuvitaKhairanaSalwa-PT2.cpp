#include <iostream>
#include <iomanip>
#include <limits>
#include <cstdlib>
using namespace std;

struct User{
    string nama;
    string password;
};

struct Keuangan{
    int id;
    string transaksi;
    string jenis;
    int jumlah;
};

int main(){

    User users[10];
    int jumlahUser = 1;

    users[0].nama = "Vita";
    users[0].password = "041";

    int menuAwal;
    string username, password;
    bool loginBerhasil = false;

    cout << "=================================================\n";
    cout << "           SISTEM MANAJEMEN KEUANGAN\n";
    cout << "=================================================\n";
    cout << " 1. Login\n";
    cout << " 2. Register\n";
    cout << " 3. Keluar\n";
    cout << "=================================================\n";
    cout << " Pilih menu : ";
    cin >> menuAwal;

    if(menuAwal == 3){
        cout << "Program ditutup.\n";
        return 0;
    }

    if(menuAwal == 2){

        cout << "\n================ REGISTER =======================\n";

        cout << " Username : ";
        cin >> users[jumlahUser].nama;

        cout << " Password : ";
        cin >> users[jumlahUser].password;

        jumlahUser++;

        cout << "Register berhasil! Silakan login.\n";
    }

    int percobaan = 0;

    while(percobaan < 3){

        cout << "\n================ LOGIN ==========================\n";

        cout << " Username : ";
        cin >> username;

        cout << " Password : ";
        cin >> password;

        for(int i = 0; i < jumlahUser; i++){
            if(username == users[i].nama && password == users[i].password){
                loginBerhasil = true;
                break;
            }
        }

        if(loginBerhasil){
            cout << "Login berhasil!\n";
            break;
        }else{
            cout << "Login gagal!\n";
            percobaan++;
        }
    }

    if(!loginBerhasil){
        cout << "Kesempatan login habis.\n";
        return 0;
    }

    Keuangan data[100];
    int jumlahData = 0;
    int pilih;

    do{

        system("cls");

        cout << "=================================================\n";
        cout << "                    MENU UTAMA\n";
        cout << "=================================================\n";
        cout << " 1. Tambah Data\n";
        cout << " 2. Lihat Data\n";
        cout << " 3. Update Data\n";
        cout << " 4. Hapus Data\n";
        cout << " 5. Keluar\n";
        cout << "=================================================\n";
        cout << " Pilih menu : ";

        if(!(cin >> pilih)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input harus angka!\n";
            continue;
        }

        if(pilih == 1){

            cout << "\n=============== TAMBAH DATA =====================\n";

            cout << " ID            : ";
            cin >> data[jumlahData].id;

            cout << " Nama Transaksi: ";
            cin >> data[jumlahData].transaksi;

            cout << " Jenis (masuk/keluar): ";
            cin >> data[jumlahData].jenis;

            cout << " Jumlah        : ";
            cin >> data[jumlahData].jumlah;

            jumlahData++;

            cout << "Data berhasil ditambahkan!\n";
        }

        else if(pilih == 2){

            cout << "\n================ DATA KEUANGAN ==================\n";

            int totalMasuk = 0;
            int totalKeluar = 0;

            if(jumlahData == 0){
                cout << "Belum ada data.\n";
            }
            else{

                cout << left << setw(10) << "ID"
                     << setw(20) << "Transaksi"
                     << setw(15) << "Jenis"
                     << setw(10) << "Jumlah" << endl;

                cout << "---------------------------------------------------------\n";

                for(int i = 0; i < jumlahData; i++){

                    cout << left << setw(10) << data[i].id
                         << setw(20) << data[i].transaksi
                         << setw(15) << data[i].jenis
                         << setw(10) << data[i].jumlah << endl;

                    if(data[i].jenis == "masuk"){
                        totalMasuk += data[i].jumlah;
                    }
                    else if(data[i].jenis == "keluar"){
                        totalKeluar += data[i].jumlah;
                    }
                }

                int saldo = totalMasuk - totalKeluar;

                cout << "---------------------------------------------------------\n";
                cout << "Total Pemasukan   : " << totalMasuk << endl;
                cout << "Total Pengeluaran : " << totalKeluar << endl;
                cout << "Saldo Akhir       : " << saldo << endl;
            }
        }

        else if(pilih == 3){

            int cari;
            bool ketemu = false;

            cout << "Masukkan ID yang ingin diubah : ";
            cin >> cari;

            for(int i = 0; i < jumlahData; i++){

                if(data[i].id == cari){

                    cout << "Transaksi baru : ";
                    cin >> data[i].transaksi;

                    cout << "Jenis baru     : ";
                    cin >> data[i].jenis;

                    cout << "Jumlah baru    : ";
                    cin >> data[i].jumlah;

                    cout << "Data berhasil diupdate!\n";

                    ketemu = true;
                    break;
                }
            }

            if(!ketemu){
                cout << "Data tidak ditemukan!\n";
            }
        }

        else if(pilih == 4){

            int cari;
            bool ketemu = false;

            cout << "Masukkan ID yang ingin dihapus : ";
            cin >> cari;

            for(int i = 0; i < jumlahData; i++){

                if(data[i].id == cari){

                    for(int j = i; j < jumlahData - 1; j++){
                        data[j] = data[j+1];
                    }

                    jumlahData--;

                    cout << "Data berhasil dihapus!\n";

                    ketemu = true;
                    break;
                }
            }

            if(!ketemu){
                cout << "Data tidak ditemukan!\n";
            }
        }

        cout << "\nTekan enter untuk lanjut...";
        cin.ignore();
        cin.get();

    }while(pilih != 5);

    cout << "\nProgram selesai.\n";

    return 0;
}