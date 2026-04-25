#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <cmath>
#include <algorithm>
#include <windows.h> // Untuk Sleep

using namespace std;

struct Keuangan {
    int id;
    string transaksi;
    string jenis;
    int jumlah;
};

struct User {
    string nama;
    string password;
    Keuangan data[100];
    int jumlahData;
};

// =================================================================
// SECTION: FUNGSI DEKORASI & ESTETIKA
// =================================================================

void garis() {
    cout << "=================================================\n";
}

void garisKecil() {
    cout << "-----------------------------------------------\n";
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void loading() {
    cout << "Memproses ";
    for(int i = 0; i < 3; i++) {
        cout << ". ";
        Sleep(300); 
    }
    cout << "\n";
}

// =================================================================
// SECTION: ALGORITMA (SORTING & SEARCHING)
// =================================================================

void sortTransaksiAsc(Keuangan data[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (data[j].transaksi > data[j + 1].transaksi) swap(data[j], data[j + 1]);
        }
    }
}

void sortJumlahDesc(Keuangan data[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int maxIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (data[j].jumlah > data[maxIndex].jumlah) maxIndex = j;
        }
        swap(data[i], data[maxIndex]);
    }
}

void sortIdAsc(Keuangan data[], int n) {
    for (int i = 1; i < n; i++) {
        Keuangan key = data[i];
        int j = i - 1;
        while (j >= 0 && data[j].id > key.id) {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = key;
    }
}

int jumpSearchID(Keuangan data[], int n, int cari) {
    if (n == 0) return -1;
    int step = sqrt(n);
    int prev = 0;
    while (data[min(step, n) - 1].id < cari) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) return -1;
    }
    for (int i = prev; i < min(step, n); i++) {
        if (data[i].id == cari) return i;
    }
    return -1;
}

// =================================================================
// SECTION: FUNGSI LOGIKA (REKURSIF & OVERLOADING)
// =================================================================

int hitungTotalMasuk(Keuangan *data, int n) {
    if (n == 0) return 0;
    if ((data + n - 1)->jenis == "masuk")
        return (data + n - 1)->jumlah + hitungTotalMasuk(data, n - 1);
    return hitungTotalMasuk(data, n - 1);
}

int hitungSaldo(int masuk, int keluar) {
    return masuk - keluar;
}

// =================================================================
// SECTION: FUNGSI MANAJEMEN DATA
// =================================================================

void inputTransaksi(User *u) {
    clearScreen();
    if (u->jumlahData >= 100) {
        cout << "\033[1;31mData sudah mencapai batas maksimum!\033[0m\n";
        Sleep(1000);
        return;
    }

    int i = u->jumlahData;
    garis();
    cout << "         INPUT DATA TRANSAKSI\n";
    garis();

    u->data[i].id = i + 1;
    cout << "ID Transaksi     : " << u->data[i].id << endl;
    cout << "Nama Transaksi   : ";
    getline(cin, u->data[i].transaksi);

    cout << "Jenis (masuk/keluar) : ";
    getline(cin, u->data[i].jenis);

    try {
        cout << "Jumlah           : ";
        if (!(cin >> u->data[i].jumlah)) throw "Input harus berupa angka!";
        if (u->data[i].jumlah < 0) throw "Jumlah tidak boleh negatif!";
    }
    catch (const char* msg) {
        cout << "\033[1;31mError: " << msg << "\033[0m" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        Sleep(1500);
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    u->jumlahData++;
    loading();
    cout << "\033[1;32m>>> Data berhasil ditambahkan <<<\033[0m\n";
    Sleep(1000);
}

void lihatLaporan(User *u) {
    clearScreen();
    if (u->jumlahData == 0) {
        cout << "\n\033[1;33mBelum ada data transaksi.\033[0m\n";
        cout << "Tekan Enter untuk kembali...";
        cin.get();
        return;
    }

    Keuangan temp[100];
    int pilihanSort;
    
    garis();
    cout << "         PILIH URUTAN LAPORAN\n";
    garis();
    cout << "1. Berdasarkan Nama Transaksi (A-Z)\n";
    cout << "2. Berdasarkan Jumlah (Terbesar)\n";
    cout << "3. Berdasarkan ID (Terkecil)\n";
    cout << "Pilih tampilan: ";
    
    if (!(cin >> pilihanSort)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        pilihanSort = 3; 
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < u->jumlahData; i++) temp[i] = u->data[i];

    if (pilihanSort == 1) sortTransaksiAsc(temp, u->jumlahData);
    else if (pilihanSort == 2) sortJumlahDesc(temp, u->jumlahData);
    else sortIdAsc(temp, u->jumlahData);

    clearScreen();
    garis();
    cout << "               LAPORAN KEUANGAN\n";
    garis();
    cout << left << setw(5) << "ID" << " | " << setw(18) << "Transaksi" << " | " << setw(10) << "Jenis" << " | " << "Jumlah" << endl;
    garisKecil();
    for (int i = 0; i < u->jumlahData; i++) {
        cout << left << setw(5) << temp[i].id << " | "
             << setw(18) << temp[i].transaksi << " | "
             << setw(10) << temp[i].jenis << " | "
             << temp[i].jumlah << endl;
    }

    int totalKeluar = 0;
    for (int i = 0; i < u->jumlahData; i++) {
        if (u->data[i].jenis == "keluar")
            totalKeluar += u->data[i].jumlah;
    }

    int totalMasuk = hitungTotalMasuk(u->data, u->jumlahData);
    int saldo = hitungSaldo(totalMasuk, totalKeluar);

    garis();
    cout << "Total Pemasukan   : \033[1;32m" << totalMasuk << "\033[0m" << endl;
    cout << "Total Pengeluaran : \033[1;31m" << totalKeluar << "\033[0m" << endl;
    cout << "Saldo Perusahaan  : \033[1;36m" << saldo << "\033[0m" << endl;
    garis();
    cout << "\nTekan Enter untuk kembali...";
    cin.get();
}

void updateTransaksi(User *u) {
    clearScreen();
    int cari;
    garis();
    cout << "           UPDATE TRANSAKSI\n";
    garis();
    cout << "Masukkan ID yang diupdate : ";
    if (!(cin >> cari)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\033[1;31mInput ID harus berupa angka.\033[0m\n";
        Sleep(1000);
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < u->jumlahData; i++) {
        if (u->data[i].id == cari) {
            cout << "Transaksi baru : ";
            getline(cin, u->data[i].transaksi);
            cout << "Jenis baru     : ";
            getline(cin, u->data[i].jenis);
            try {
                cout << "Jumlah baru    : ";
                if (!(cin >> u->data[i].jumlah)) throw "Input harus angka!";
            } catch (const char* msg) {
                cout << "\033[1;31m" << msg << "\033[0m" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            loading();
            cout << "\033[1;32m>>> Data berhasil diupdate <<<\033[0m\n";
            Sleep(1000);
            return;
        }
    }
    cout << "\033[1;31mData tidak ditemukan\033[0m\n";
    Sleep(1000);
}

void hapusTransaksi(User *u) {
    clearScreen();
    int cari;
    garis();
    cout << "           HAPUS TRANSAKSI\n";
    garis();
    cout << "Masukkan ID yang dihapus : ";
    if (!(cin >> cari)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\033[1;31mInput ID harus berupa angka.\033[0m\n";
        Sleep(1000);
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < u->jumlahData; i++) {
        if (u->data[i].id == cari) {
            for (int j = i; j < u->jumlahData - 1; j++)
                u->data[j] = u->data[j + 1];
            u->jumlahData--;
            loading();
            cout << "\033[1;32m>>> Data berhasil dihapus <<<\033[0m\n";
            Sleep(1000);
            return;
        }
    }
    cout << "\033[1;31mData tidak ditemukan\033[0m\n";
    Sleep(1000);
}

void cariData(User *u) {
    clearScreen();
    int pilih;
    bool ketemu = false;

    garis();
    cout << "          PENCARIAN TRANSAKSI\n";
    garis();
    cout << "1. Cari ID (Jump Search)\n";
    cout << "2. Cari Nama Transaksi\n";
    cout << "Pilih : ";
    
    if (!(cin >> pilih)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (pilih == 1) {
        int cari;
        cout << "Masukkan ID transaksi : ";
        if(cin >> cari) {
            sortIdAsc(u->data, u->jumlahData); 
            int index = jumpSearchID(u->data, u->jumlahData, cari);
            if (index != -1) {
                cout << "\n\033[1;32m>>> Data ditemukan <<<\033[0m\n";
                cout << "ID        : " << u->data[index].id << endl;
                cout << "Transaksi : " << u->data[index].transaksi << endl;
                cout << "Jenis     : " << u->data[index].jenis << endl;
                cout << "Jumlah    : " << u->data[index].jumlah << endl;
                ketemu = true;
            }
        }
    } else if (pilih == 2) {
        string cari;
        cout << "Masukkan nama transaksi : ";
        getline(cin, cari);
        for (int i = 0; i < u->jumlahData; i++) {
            if (u->data[i].transaksi == cari) {
                cout << "\n\033[1;32m>>> Data ditemukan <<<\033[0m\n";
                cout << "ID        : " << u->data[i].id << endl;
                cout << "Transaksi : " << u->data[i].transaksi << endl;
                cout << "Jenis     : " << u->data[i].jenis << endl;
                cout << "Jumlah    : " << u->data[i].jumlah << endl;
                ketemu = true;
            }
        }
    }
    if (!ketemu) cout << "\033[1;31mData tidak ditemukan\033[0m\n";
    cout << "\nTekan Enter...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void menuUtama(User *user) {
    int pilih;
    do {
        clearScreen();
        garis();
        cout << "      MENU UTAMA - SISTEM KEUANGAN\n";
        garis();
        cout << "Selamat Datang, \033[1;36m" << user->nama << "\033[0m" << endl;
        garisKecil();
        cout << "1. Input Data Transaksi\n";
        cout << "2. Lihat Laporan Keuangan\n";
        cout << "3. Update Transaksi\n";
        cout << "4. Hapus Transaksi\n";
        cout << "5. Cari Transaksi\n";
        cout << "6. Keluar (Logout)\n";
        garisKecil();
        cout << "Pilih Menu : ";
        
        if (!(cin >> pilih)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (pilih == 1) inputTransaksi(user);
        else if (pilih == 2) lihatLaporan(user);
        else if (pilih == 3) updateTransaksi(user);
        else if (pilih == 4) hapusTransaksi(user);
        else if (pilih == 5) cariData(user);

    } while (pilih != 6);
}

// =================================================================
// SECTION: MAIN PROGRAM
// =================================================================

int main() {
    User users[10];
    int jumlahUser = 1;
    users[0] = {"Vita", "041", {}, 0};

    while (true) {
        clearScreen();
        garis();
        cout << "  SISTEM MANAJEMEN KEUANGAN PERUSAHAAN\n";
        garis();
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Keluar\n";
        garis();
        cout << "Pilih menu : ";
        
        int menuAwal;
        if (!(cin >> menuAwal)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (menuAwal == 3) break;

        if (menuAwal == 2) {
            clearScreen();
            garis();
            cout << "          REGISTER USER\n";
            garis();
            if (jumlahUser < 10) {
                cout << "Username : "; getline(cin, users[jumlahUser].nama);
                cout << "Password : "; getline(cin, users[jumlahUser].password);
                users[jumlahUser].jumlahData = 0;
                jumlahUser++;
                cout << "\033[1;32mRegister Berhasil!\033[0m\n";
            } else {
                cout << "\033[1;31mKapasitas user penuh!\033[0m\n";
            }
            Sleep(1000);
        } else if (menuAwal == 1) {
            string uname, pass;
            clearScreen();
            garis();
            cout << "              LOGIN\n";
            garis();
            cout << "Username : "; getline(cin, uname);
            cout << "Password : "; getline(cin, pass);

            bool login = false;
            for(int i = 0; i < jumlahUser; i++) {
                if(uname == users[i].nama && pass == users[i].password) {
                    loading();
                    menuUtama(&users[i]);
                    login = true;
                    break;
                }
            }
            if(!login) {
                cout << "\033[1;31mUsername/Password Salah!\033[0m\n";
                Sleep(1200);
            }
        }
    }
    
    clearScreen();
    cout << "\nPROGRAM SELESAI DIGUNAKAN. TERIMA KASIH!\n";
    return 0;
}