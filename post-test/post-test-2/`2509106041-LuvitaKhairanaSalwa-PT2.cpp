#include <iostream>
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

    User users[10]; // max user
    int jumlahUser = 1; 

    // akun admin awal
    users[0].nama = "Vita";
    users[0].password = "041";

    int menuAwal;
    string username, password;
    bool loginBerhasil = false;

    cout << "=====================================\n";
    cout << "           SISTEM KEUANGAN           \n";
    cout << "=====================================\n";
    cout << " 1. Login\n";
    cout << " 2. Register\n";
    cout << " 3. Keluar\n";
    cout << "=====================================\n";
    cout << " Pilih menu : ";
    cin >> menuAwal;

if(menuAwal == 3){
    cout << "Program ditutup.\n";
    return 0;
}

    if(menuAwal == 2){
        cout << "\n=========== REGISTER ===============\n";
        cout << " Username : ";
        cin >> users[jumlahUser].nama;
        cout << " Password : ";
        cin >> users[jumlahUser].password;

        jumlahUser++;

        cout << "=====================================\n";
        cout << " Register berhasil! Silakan login.\n";
        cout << "=====================================\n";
    }

    int percobaan = 0;

    while(percobaan < 3){ // percobaan max 3 kali

        cout << "\n============= LOGIN =================\n";
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

    Keuangan data[100]; // Membuat array bernama data yang bisa menyimpan 100 data
    int jumlahData = 0; // menyimpan berapa data yang sudah diinput
    int pilih;

    do{
    // Menu utama 
        cout << "\n=====================================\n";
        cout << "              MENU UTAMA             \n";
        cout << "=====================================\n";
        cout << " 1. Tambah Data\n";
        cout << " 2. Lihat Data\n";
        cout << " 3. Update Data\n";
        cout << " 4. Hapus Data\n";
        cout << " 5. Keluar\n";
        cout << "=====================================\n";
        cout << " Pilih menu : ";
        cin >> pilih;

        if(pilih == 1){

            cout << "\n=========== TAMBAH DATA ============\n";
            cout << " ID            : ";
            cin >> data[jumlahData].id;

            cout << " Nama Transaksi: ";
            cin >> data[jumlahData].transaksi;

            cout << " Jenis (masuk/keluar): ";
            cin >> data[jumlahData].jenis;

            cout << " Jumlah        : ";
            cin >> data[jumlahData].jumlah;

            jumlahData++;

        }

       else if(pilih == 2){

    cout << "\n=========== DATA KEUANGAN ==========\n";

    int totalMasuk = 0;
    int totalKeluar = 0;

    if(jumlahData == 0){
        cout << "Belum ada data.\n";
    }

    for(int i = 0; i < jumlahData; i++){
        cout << "-------------------------------------\n";
        cout << " ID        : " << data[i].id << endl;
        cout << " Transaksi : " << data[i].transaksi << endl;
        cout << " Jenis     : " << data[i].jenis << endl;
        cout << " Jumlah    : " << data[i].jumlah << endl;
        if(data[i].jenis == "masuk"){
            totalMasuk += data[i].jumlah;
        }
        else if(data[i].jenis == "keluar"){
            totalKeluar += data[i].jumlah;
        }
    }
         int saldo = totalMasuk - totalKeluar;

             cout << "-------------------------------------\n";
             cout << " Total Pemasukan   : " << totalMasuk << endl;
             cout << " Total Pengeluaran : " << totalKeluar << endl;
             cout << " Saldo Akhir       : " << saldo << endl;
}

        else if(pilih == 3){

            int cari;
            cout << "Masukkan ID yang ingin diubah: ";
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
                }
            }

        }

        else if(pilih == 4){

            int cari;
            cout << "Masukkan ID yang ingin dihapus: ";
            cin >> cari;

            for(int i = 0; i < jumlahData; i++){
                if(data[i].id == cari){

                    for(int j = i; j < jumlahData - 1; j++){
                        data[j] = data[j+1];
                    }

                    jumlahData--;
                    cout << "Data berhasil dihapus!\n";
                    break;
                }
            }

        }

    }while(pilih != 5);

    cout << "\nProgram selesai.\n";

    return 0;
}