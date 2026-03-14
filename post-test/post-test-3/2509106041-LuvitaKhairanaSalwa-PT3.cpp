#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

//nested STRUCT 
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

// REKURSIF 
int hitungTotalMasuk(Keuangan data[], int n){
    if(n == 0)
        return 0;

    if(data[n-1].jenis == "masuk")
        return data[n-1].jumlah + hitungTotalMasuk(data, n-1);

    return hitungTotalMasuk(data, n-1);
}

// OVERLOADING
int hitungSaldo(int masuk, int keluar){
    return masuk - keluar;
}

int hitungSaldo(User u){
    int masuk = 0;
    int keluar = 0;

    for(int i=0;i<u.jumlahData;i++){
        if(u.data[i].jenis == "masuk")
            masuk += u.data[i].jumlah;
        else if(u.data[i].jenis == "keluar")
            keluar += u.data[i].jumlah;
    }

    return masuk - keluar;
}

// PROSEDUR CARI DATA
void cariData(User &u){

    int cari;
    bool ketemu = false;

    cout << "\n=========== PENCARIAN TRANSAKSI ===========\n";
    cout << "Masukkan ID transaksi : ";
    cin >> cari;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for(int i=0;i<u.jumlahData;i++){

        if(u.data[i].id == cari){

            cout << "\nData ditemukan\n";
            cout << "ID        : " << u.data[i].id << endl;
            cout << "Transaksi : " << u.data[i].transaksi << endl;
            cout << "Jenis     : " << u.data[i].jenis << endl;
            cout << "Jumlah    : " << u.data[i].jumlah << endl;

            ketemu = true;
            break;
        }
    }

    if(!ketemu)
        cout << "Data tidak ditemukan\n";
}

// MAIN
int main(){

    User users[10];
    int jumlahUser = 1;

    users[0].nama = "Vita";
    users[0].password = "041";
    users[0].jumlahData = 0;

    string username,password;
    bool loginBerhasil = false;
    int userLogin=-1;

    int menuAwal;

    cout << "=================================================\n";
    cout << "      SISTEM MANAJEMEN KEUANGAN PERUSAHAAN\n";
    cout << "=================================================\n";
    cout << "1. Login\n";
    cout << "2. Register\n";
    cout << "3. Keluar\n";
    cout << "=================================================\n";
    cout << "Pilih menu : ";
    cin >> menuAwal;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if(menuAwal==3)
        return 0;

    if(menuAwal==2){

        cout << "\n=========== REGISTER USER ===========\n";

        cout << "Username : ";
        getline(cin, users[jumlahUser].nama);

        cout << "Password : ";
        getline(cin, users[jumlahUser].password);

        users[jumlahUser].jumlahData=0;
        jumlahUser++;

        cout << "Register berhasil!\n";
    }

    int percobaan=0;

    while(percobaan<3){

        cout << "\n============== LOGIN ==============\n";

        cout << "Username : ";
        getline(cin, username);

        cout << "Password : ";
        getline(cin, password);

        for(int i=0;i<jumlahUser;i++){

            if(username==users[i].nama && password==users[i].password){
                loginBerhasil=true;
                userLogin=i;
                break;
            }
        }

        if(loginBerhasil){
            cout << "Login berhasil!\n";
            break;
        }

        cout << "Login gagal\n";
        percobaan++;
    }

    if(!loginBerhasil){
        cout << "Login gagal 3 kali\n";
        return 0;
    }

    int pilih;

    do{

        cout << "\n================ MENU UTAMA ================\n";
        cout << "User : " << users[userLogin].nama << endl;
        cout << "--------------------------------------------\n";
        cout << "1. Input Data Transaksi\n";
        cout << "2. Lihat Laporan Keuangan\n";
        cout << "3. Update Transaksi\n";
        cout << "4. Hapus Transaksi\n";
        cout << "5. Cari Transaksi\n";
        cout << "6. Keluar\n";
        cout << "--------------------------------------------\n";
        cout << "Pilih Menu : ";
        cin >> pilih;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // INPUT DATA
        if(pilih==1){

            if(users[userLogin].jumlahData >= 100){
                cout << "Data sudah mencapai batas maksimum!\n";
            }
            else{

                int i = users[userLogin].jumlahData;

                cout << "\n========== INPUT DATA TRANSAKSI ==========\n";

                // ID AUTOGENERATE
                users[userLogin].data[i].id = i + 1;
                cout << "ID Transaksi : " << users[userLogin].data[i].id << endl;

                cout << "Nama Transaksi : ";
                getline(cin, users[userLogin].data[i].transaksi);

                string jenis;
                cout << "Jenis (masuk/keluar) : ";
                getline(cin, jenis);

                if(jenis == "masuk")
                    users[userLogin].data[i].jenis = "masuk";
                else if(jenis == "keluar")
                    users[userLogin].data[i].jenis = "keluar";
                else{
                    cout << "Jenis tidak valid!\n";
                    continue;
                }

                cout << "Jumlah : ";
                cin >> users[userLogin].data[i].jumlah;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                users[userLogin].jumlahData++;

                cout << "Data berhasil ditambahkan\n";
            }
        }

        // LIHAT DATA
        else if(pilih==2){

            int jumlahData = users[userLogin].jumlahData;
            int totalKeluar=0;

            cout << "\n=========== LAPORAN KEUANGAN ===========\n";

            cout << left
            << setw(5)<<"No"
            << setw(10)<<"ID"
            << setw(20)<<"Transaksi"
            << setw(10)<<"Jenis"
            << setw(15)<<"Jumlah"<<endl;

            for(int i=0;i<jumlahData;i++){

                cout << left
                << setw(5)<<i+1
                << setw(10)<<users[userLogin].data[i].id
                << setw(20)<<users[userLogin].data[i].transaksi
                << setw(10)<<users[userLogin].data[i].jenis
                << setw(15)<<users[userLogin].data[i].jumlah
                << endl;

                if(users[userLogin].data[i].jenis=="keluar")
                    totalKeluar+=users[userLogin].data[i].jumlah;
            }

            int totalMasuk = hitungTotalMasuk(users[userLogin].data,jumlahData);
            int saldo = hitungSaldo(totalMasuk,totalKeluar);

            cout << "-----------------------------------------\n";
            cout << "Total Pemasukan   : " << totalMasuk << endl;
            cout << "Total Pengeluaran : " << totalKeluar << endl;
            cout << "Saldo Perusahaan  : " << saldo << endl;
        }

        // UPDATE
        else if(pilih==3){

            int cari;

            cout << "Masukkan ID yang diupdate : ";
            cin >> cari;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            for(int i=0;i<users[userLogin].jumlahData;i++){

                if(users[userLogin].data[i].id==cari){

                    cout << "Transaksi baru : ";
                    getline(cin, users[userLogin].data[i].transaksi);

                    cout << "Jenis baru : ";
                    getline(cin, users[userLogin].data[i].jenis);

                    cout << "Jumlah baru : ";
                    cin >> users[userLogin].data[i].jumlah;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    cout << "Data berhasil diupdate\n";
                }
            }
        }

        // HAPUS
        else if(pilih==4){

            int cari;

            cout << "Masukkan ID yang dihapus : ";
            cin >> cari;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            for(int i=0;i<users[userLogin].jumlahData;i++){

                if(users[userLogin].data[i].id==cari){

                    for(int j=i;j<users[userLogin].jumlahData-1;j++)
                        users[userLogin].data[j]=users[userLogin].data[j+1];

                    users[userLogin].jumlahData--;

                    cout << "Data berhasil dihapus\n";
                    break;
                }
            }
        }

        // CARI
        else if(pilih==5){
            cariData(users[userLogin]);
        }

    }while(pilih!=6);

    cout << "\nPROGRAM SELESAI DIGUNAKAN\n";

    return 0;
}