#include <iostream>
#include <iomanip>
#include <limits>
#include <cstdlib>
using namespace std;


//nested crud
struct Keuangan{ 
    int id;
    string transaksi;
    string jenis;
    int jumlah;
};

struct User{
    string nama;
    string password;

    Keuangan data[100]; 
    int jumlahData;
};

int main(){

    User users[10];
    int jumlahUser = 1;
// login tanpa regist
    users[0].nama = "Vita"; 
    users[0].password = "041";
    users[0].jumlahData = 0;

    int menuAwal;
    string username, password;
    bool loginBerhasil = false;
    int userLogin = -1;

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

        users[jumlahUser].jumlahData = 0;

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
                userLogin = i;
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

            int i = users[userLogin].jumlahData;

            cout << " ID            : ";
            cin >> users[userLogin].data[i].id;

            cout << " Nama Transaksi: ";
            cin >> users[userLogin].data[i].transaksi;

            cout << " Jenis (masuk/keluar): ";
            cin >> users[userLogin].data[i].jenis;

            cout << " Jumlah        : ";
            cin >> users[userLogin].data[i].jumlah;

            users[userLogin].jumlahData++;

            cout << "Data berhasil ditambahkan!\n";
        }

        else if(pilih == 2){

            cout << "\n================ DATA KEUANGAN ==================\n";

            int totalMasuk = 0;
            int totalKeluar = 0;

            int jumlahData = users[userLogin].jumlahData;

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

                    cout << left << setw(10) << users[userLogin].data[i].id
                         << setw(20) << users[userLogin].data[i].transaksi
                         << setw(15) << users[userLogin].data[i].jenis
                         << setw(10) << users[userLogin].data[i].jumlah << endl;

                    if(users[userLogin].data[i].jenis == "masuk"){
                        totalMasuk += users[userLogin].data[i].jumlah; 
                    }
                    else if(users[userLogin].data[i].jenis == "keluar"){
                        totalKeluar += users[userLogin].data[i].jumlah;
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

            for(int i = 0; i < users[userLogin].jumlahData; i++){

                if(users[userLogin].data[i].id == cari){

                    cout << "Transaksi baru : ";
                    cin >> users[userLogin].data[i].transaksi;

                    cout << "Jenis baru     : ";
                    cin >> users[userLogin].data[i].jenis;

                    cout << "Jumlah baru    : ";
                    cin >> users[userLogin].data[i].jumlah;

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

            for(int i = 0; i < users[userLogin].jumlahData; i++){

                if(users[userLogin].data[i].id == cari){

                    for(int j = i; j < users[userLogin].jumlahData - 1; j++){
                        users[userLogin].data[j] = users[userLogin].data[j+1];
                    }

                    users[userLogin].jumlahData--;

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
        cin.ignore(); // menghilangkan buffer
        cin.get();

    }while(pilih != 5);

    cout << "\nProgram selesai.\n";

    return 0;
}