#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <cmath>
#include <algorithm>

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

void garis() {
    cout << "=================================================\n";
}

void garisKecil() {
    cout << "-----------------------------------------------\n";
}

void sortTransaksiAsc(Keuangan data[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (data[j].transaksi > data[j + 1].transaksi) {
                swap(data[j], data[j + 1]);
            }
        }
    }
}

void sortJumlahDesc(Keuangan data[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int maxIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (data[j].jumlah > data[maxIndex].jumlah) {
                maxIndex = j;
            }
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

int hitungTotalMasuk(Keuangan *data, int n) {
    if (n == 0) return 0;
    if ((data + n - 1)->jenis == "masuk")
        return (data + n - 1)->jumlah + hitungTotalMasuk(data, n - 1);
    return hitungTotalMasuk(data, n - 1);
}

int hitungSaldo(int masuk, int keluar) {
    return masuk - keluar;
}

void inputTransaksi(User *u) {
    if (u->jumlahData >= 100) {
        cout << "Data sudah mencapai batas maksimum!\n";
        return;
    }

    int i = u->jumlahData;
    garis();
    cout << "        INPUT DATA TRANSAKSI\n";
    garis();

    u->data[i].id = i + 1;
    cout << "ID Transaksi     : " << u->data[i].id << endl;
    cout << "Nama Transaksi   : ";
    getline(cin, u->data[i].transaksi);

    cout << "Jenis (masuk/keluar) : ";
    getline(cin, u->data[i].jenis);

    try {
        cout << "Jumlah           : ";
        if (!(cin >> u->data[i].jumlah)) throw "Input harus angka!";
        if (u->data[i].jumlah < 0) throw "Jumlah tidak boleh negatif!";
    }
    catch (const char* msg) {
        cout << msg << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    u->jumlahData++;
    cout << "\n>>> Data berhasil ditambahkan <<<\n";
}

void lihatLaporan(User *u) {
    if (u->jumlahData == 0) {
        cout << "\nBelum ada data transaksi.\n";
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

    cout << "\n";
    garis();
    cout << "              LAPORAN KEUANGAN\n";
    garis();
    for (int i = 0; i < u->jumlahData; i++) {
        cout << temp[i].id << " | "
             << temp[i].transaksi << " | "
             << temp[i].jenis << " | "
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
    cout << "Total Pemasukan   : " << totalMasuk << endl;
    cout << "Total Pengeluaran : " << totalKeluar << endl;
    cout << "Saldo Perusahaan  : " << saldo << endl;
    garis();
}

void updateTransaksi(User *u) {
    int cari;
    try {
        cout << "\nMasukkan ID yang diupdate : ";
        if (!(cin >> cari)) throw "ID harus angka!";
    }
    catch (const char* msg) {
        cout << msg << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < u->jumlahData; i++) {
        if (u->data[i].id == cari) {
            cout << "Transaksi baru : ";
            getline(cin, u->data[i].transaksi);
            cout << "Jenis baru : ";
            getline(cin, u->data[i].jenis);

            try {
                cout << "Jumlah baru : ";
                if (!(cin >> u->data[i].jumlah)) throw "Input harus angka!";
                if (u->data[i].jumlah < 0) throw "Jumlah tidak boleh negatif!";
            }
            catch (const char* msg) {
                cout << msg << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << ">>> Data berhasil diupdate <<<\n";
            return;
        }
    }
    cout << "Data tidak ditemukan\n";
}

void hapusTransaksi(User *u) {
    int cari;
    try {
        cout << "\nMasukkan ID yang dihapus : ";
        if (!(cin >> cari)) throw "ID harus angka!";
    }
    catch (const char* msg) {
        cout << msg << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < u->jumlahData; i++) {
        if (u->data[i].id == cari) {
            for (int j = i; j < u->jumlahData - 1; j++)
                u->data[j] = u->data[j + 1];
            u->jumlahData--;
            cout << ">>> Data berhasil dihapus <<<\n";
            return;
        }
    }
    cout << "Data tidak ditemukan\n";
}

void cariData(User *u) {
    int pilih;
    bool ketemu = false;

    garis();
    cout << "          PENCARIAN TRANSAKSI\n";
    garis();
    cout << "1. Cari ID \n";
    cout << "2. Cari Nama Transaksi \n";
    cout << "Pilih : ";
    
    if (!(cin >> pilih)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Pilihan tidak valid!\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (pilih == 1) {
        int cari;
        try {
            cout << "Masukkan ID transaksi : ";
            if (!(cin >> cari)) throw "ID harus angka!";
        }
        catch (const char* msg) {
            cout << msg << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        sortIdAsc(u->data, u->jumlahData); 
        int index = jumpSearchID(u->data, u->jumlahData, cari);

        if (index != -1) {
            cout << "\n>>> Data ditemukan <<<\n";
            cout << "ID        : " << u->data[index].id << endl;
            cout << "Transaksi : " << u->data[index].transaksi << endl;
            cout << "Jenis     : " << u->data[index].jenis << endl;
            cout << "Jumlah    : " << u->data[index].jumlah << endl;
            ketemu = true;
        }
    }
    else if (pilih == 2) {
        string cari;
        cout << "Masukkan nama transaksi : ";
        getline(cin, cari);

        for (int i = 0; i < u->jumlahData; i++) {
            if (u->data[i].transaksi == cari) {
                cout << "\n>>> Data ditemukan <<<\n";
                cout << "ID        : " << u->data[i].id << endl;
                cout << "Transaksi : " << u->data[i].transaksi << endl;
                cout << "Jenis     : " << u->data[i].jenis << endl;
                cout << "Jumlah    : " << u->data[i].jumlah << endl;
                ketemu = true;
            }
        }
    }

    if (!ketemu) {
        cout << "Data tidak ditemukan\n";
    }
}

void menuUtama(User *user) {
    int pilih;
    do {
        garis();
        cout << "      MENU UTAMA - SISTEM KEUANGAN\n";
        garis();
        cout << "User : " << user->nama << endl;
        garisKecil();
        cout << "1. Input Data Transaksi\n";
        cout << "2. Lihat Laporan Keuangan\n";
        cout << "3. Update Transaksi\n";
        cout << "4. Hapus Transaksi\n";
        cout << "5. Cari Transaksi\n";
        cout << "6. Keluar\n";
        garisKecil();
        
        try {
            cout << "Pilih Menu : ";
            if (!(cin >> pilih)) throw "Menu harus angka!";
            if (pilih < 1 || pilih > 6) throw "Menu hanya 1-6!";
        }
        catch (const char* msg) {
            cout << msg << endl;
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

int main() {
    User users[10];
    int jumlahUser = 1;

    users[0].nama = "Vita";
    users[0].password = "041";
    users[0].jumlahData = 0;

    string username, password;
    bool loginBerhasil = false;
    int userLogin = -1;
    int menuAwal;

    garis();
    cout << "  SISTEM MANAJEMEN KEUANGAN PERUSAHAAN\n";
    garis();
    cout << "1. Login\n";
    cout << "2. Register\n";
    cout << "3. Keluar\n";
    garis();
    cout << "Pilih menu : ";
    
    if (!(cin >> menuAwal)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        menuAwal = 0;
    } else {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (menuAwal == 3) return 0;

    if (menuAwal == 2) {
        garis();
        cout << "        REGISTER USER\n";
        garis();
        cout << "Username : ";
        getline(cin, users[jumlahUser].nama);
        cout << "Password : ";
        getline(cin, users[jumlahUser].password);
        users[jumlahUser].jumlahData = 0;
        jumlahUser++;
        cout << ">>> Register berhasil <<<\n";
    }

    int percobaan = 0;
    while (percobaan < 3) {
        garis();
        cout << "              LOGIN\n";
        garis();
        cout << "Username : ";
        getline(cin, username);
        cout << "Password : ";
        getline(cin, password);

        for (int i = 0; i < jumlahUser; i++) {
            if (username == users[i].nama && password == users[i].password) {
                loginBerhasil = true;
                userLogin = i;
                break;
            }
        }

        if (loginBerhasil) {
            cout << ">>> Login berhasil <<<\n";
            menuUtama(&users[userLogin]);
            break;
        }
        cout << "Login gagal\n";
        percobaan++;
    }

    if (!loginBerhasil)
        cout << "Login gagal 3 kali\n";

    cout << "\nPROGRAM SELESAI DIGUNAKAN\n";
    return 0;
}