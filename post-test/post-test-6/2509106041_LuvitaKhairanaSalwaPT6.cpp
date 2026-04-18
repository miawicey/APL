#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <cmath>

using namespace std;

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

void garis(){
    cout<<"=================================================\n";
}

void garisKecil(){
    cout<<"-----------------------------------------------\n";
}

// SORTING 
// 1. BUBBLE SORT 
void sortTransaksiAsc(Keuangan data[], int n){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(data[j].transaksi > data[j+1].transaksi){
                swap(data[j], data[j+1]);
            }
        }
    }
}

// 2. SELECTION SORT 
void sortJumlahDesc(Keuangan data[], int n){
    for(int i=0;i<n-1;i++){
        int maxIndex = i;
        for(int j=i+1;j<n;j++){
            if(data[j].jumlah > data[maxIndex].jumlah){
                maxIndex = j;
            }
        }
        swap(data[i], data[maxIndex]);
    }
}

// 3. INSERTION SORT 
void sortIdAsc(Keuangan data[], int n){
    for(int i=1;i<n;i++){
        Keuangan key = data[i];
        int j = i - 1;

        while(j >= 0 && data[j].id > key.id){
            data[j+1] = data[j];
            j--;
        }
        data[j+1] = key;
    }
}

int jumpSearchID(Keuangan data[], int n, int cari){

    int step = sqrt(n);
    int prev = 0;

    while(data[min(step,n)-1].id < cari){
        prev = step;
        step += sqrt(n);
        if(prev >= n)
            return -1;
    }

    for(int i=prev; i<min(step,n); i++){
        if(data[i].id == cari)
            return i;
    }

    return -1;
}

// REKURSIF
int hitungTotalMasuk(Keuangan *data, int n){
    if(n==0) return 0;
    if((data+n-1)->jenis=="masuk")
        return (data+n-1)->jumlah + hitungTotalMasuk(data,n-1);
    return hitungTotalMasuk(data,n-1);
}

// OVERLOADING
int hitungSaldo(int masuk,int keluar){
    return masuk-keluar;
}

// INPUT
void inputTransaksi(User *u){

    if(u->jumlahData>=100){
        cout<<"Data sudah mencapai batas maksimum!\n";
        return;
    }

    int i=u->jumlahData;

    garis();
    cout<<"        INPUT DATA TRANSAKSI\n";
    garis();

    u->data[i].id=i+1;

    cout<<"ID Transaksi     : "<<u->data[i].id<<endl;

    cout<<"Nama Transaksi   : ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin,u->data[i].transaksi);

    cout<<"Jenis (masuk/keluar) : ";
    getline(cin,u->data[i].jenis);

    cout<<"Jumlah           : ";
    cin>>u->data[i].jumlah;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');

    u->jumlahData++;

    cout<<"\n>>> Data berhasil ditambahkan <<<\n";
}

// ================= LIHAT + SORTING =================
void lihatLaporan(User *u){

    Keuangan temp[100];
    int totalKeluar=0;

    // SORT TRANSAKSI A-Z
    for(int i=0;i<u->jumlahData;i++) temp[i]=u->data[i];
    sortTransaksiAsc(temp, u->jumlahData);

    garis();
    cout<<"   LAPORAN (SORT TRANSAKSI A-Z)\n";
    garis();

    for(int i=0;i<u->jumlahData;i++){
        cout<<temp[i].id<<" | "
            <<temp[i].transaksi<<" | "
            <<temp[i].jenis<<" | "
            <<temp[i].jumlah<<endl;
    }

    // SORT JUMLAH DESC
    for(int i=0;i<u->jumlahData;i++) temp[i]=u->data[i];
    sortJumlahDesc(temp, u->jumlahData);

    garis();
    cout<<"   LAPORAN (SORT JUMLAH TERBESAR)\n";
    garis();

    for(int i=0;i<u->jumlahData;i++){
        cout<<temp[i].id<<" | "
            <<temp[i].transaksi<<" | "
            <<temp[i].jenis<<" | "
            <<temp[i].jumlah<<endl;
    }

    // SORT ID ASC
    for(int i=0;i<u->jumlahData;i++) temp[i]=u->data[i];
    sortIdAsc(temp, u->jumlahData);

    garis();
    cout<<"   LAPORAN (SORT ID TERKECIL)\n";
    garis();

    for(int i=0;i<u->jumlahData;i++){
        cout<<temp[i].id<<" | "
            <<temp[i].transaksi<<" | "
            <<temp[i].jenis<<" | "
            <<temp[i].jumlah<<endl;
    }

    // TOTAL
    for(int i=0;i<u->jumlahData;i++){
        if(u->data[i].jenis=="keluar")
            totalKeluar+=u->data[i].jumlah;
    }

    int totalMasuk=hitungTotalMasuk(u->data,u->jumlahData);
    int saldo=hitungSaldo(totalMasuk,totalKeluar);

    garis();
    cout<<"Total Pemasukan   : "<<totalMasuk<<endl;
    cout<<"Total Pengeluaran : "<<totalKeluar<<endl;
    cout<<"Saldo Perusahaan  : "<<saldo<<endl;
    garis();
}

// UPDATE
void updateTransaksi(User *u){

    int cari;

    cout<<"\nMasukkan ID yang diupdate : ";
    cin>>cari;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');

    for(int i=0;i<u->jumlahData;i++){
        if(u->data[i].id==cari){

            cout<<"Transaksi baru : ";
            getline(cin,u->data[i].transaksi);

            cout<<"Jenis baru : ";
            getline(cin,u->data[i].jenis);

            cout<<"Jumlah baru : ";
            cin>>u->data[i].jumlah;
            cin.ignore(numeric_limits<streamsize>::max(),'\n');

            cout<<">>> Data berhasil diupdate <<<\n";
            return;
        }
    }

    cout<<"Data tidak ditemukan\n";
}

// HAPUS
void hapusTransaksi(User *u){

    int cari;

    cout<<"\nMasukkan ID yang dihapus : ";
    cin>>cari;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');

    for(int i=0;i<u->jumlahData;i++){
        if(u->data[i].id==cari){

            for(int j=i;j<u->jumlahData-1;j++)
                u->data[j]=u->data[j+1];

            u->jumlahData--;

            cout<<">>> Data berhasil dihapus <<<\n";
            return;
        }
    }

    cout<<"Data tidak ditemukan\n";
}

// CARI
void cariData(User *u){

    int pilih;
    bool ketemu=false;

    garis();
    cout<<"          PENCARIAN TRANSAKSI\n";
    garis();

    cout<<"1. Cari ID (Jump Search)\n";
    cout<<"2. Cari Nama Transaksi (Linear)\n";
    cout<<"Pilih : ";
    cin>>pilih;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');

    
    if(pilih==1){
        int cari;
        cout<<"Masukkan ID transaksi : ";
        cin>>cari;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');

        sortIdAsc(u->data, u->jumlahData); // wajib

        int index = jumpSearchID(u->data, u->jumlahData, cari);

        if(index != -1){
            cout<<"\n>>> Data ditemukan <<<\n";
            cout<<"ID        : "<<u->data[index].id<<endl;
            cout<<"Transaksi : "<<u->data[index].transaksi<<endl;
            cout<<"Jenis     : "<<u->data[index].jenis<<endl;
            cout<<"Jumlah    : "<<u->data[index].jumlah<<endl;
        }else{
            cout<<"Data tidak ditemukan\n";
        }
    }

    
    else if(pilih==2){
        string cari;
        cout<<"Masukkan nama transaksi : ";
        getline(cin,cari);

        for(int i=0;i<u->jumlahData;i++){
            if(u->data[i].transaksi == cari){

                cout<<"\n>>> Data ditemukan <<<\n";
                cout<<"ID        : "<<u->data[i].id<<endl;
                cout<<"Transaksi : "<<u->data[i].transaksi<<endl;
                cout<<"Jenis     : "<<u->data[i].jenis<<endl;
                cout<<"Jumlah    : "<<u->data[i].jumlah<<endl;

                ketemu=true;
            }
        }
    }

    if(!ketemu){
        cout<<"Data tidak ditemukan\n";
    }
}

// MENU
void menuUtama(User *user){

    int pilih;

    do{
        garis();
        cout<<"      MENU UTAMA - SISTEM KEUANGAN\n";
        garis();
        cout<<"User : "<<user->nama<<endl;
        garisKecil();

        cout<<"1. Input Data Transaksi\n";
        cout<<"2. Lihat Laporan Keuangan\n";
        cout<<"3. Update Transaksi\n";
        cout<<"4. Hapus Transaksi\n";
        cout<<"5. Cari Transaksi\n";
        cout<<"6. Keluar\n";

        garisKecil();
        cout<<"Pilih Menu : ";
        cin>>pilih;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');

        if(pilih==1) inputTransaksi(user);
        else if(pilih==2) lihatLaporan(user);
        else if(pilih==3) updateTransaksi(user);
        else if(pilih==4) hapusTransaksi(user);
        else if(pilih==5) cariData(user);

    }while(pilih!=6);
}

// MAIN
int main(){

    User users[10];
    int jumlahUser=1;

    users[0].nama="Vita";
    users[0].password="041";
    users[0].jumlahData=0;

    string username,password;
    bool loginBerhasil=false;
    int userLogin=-1;

    int menuAwal;

    garis();
    cout<<"  SISTEM MANAJEMEN KEUANGAN PERUSAHAAN\n";
    garis();

    cout<<"1. Login\n";
    cout<<"2. Register\n";
    cout<<"3. Keluar\n";

    garis();
    cout<<"Pilih menu : ";
    cin >> menuAwal;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if(menuAwal==3) return 0;

    if(menuAwal==2){
        garis();
        cout<<"        REGISTER USER\n";
        garis();

        cout<<"Username : ";
        getline(cin, users[jumlahUser].nama);

        cout<<"Password : ";
        getline(cin, users[jumlahUser].password);

        users[jumlahUser].jumlahData=0;
        jumlahUser++;

        cout<<">>> Register berhasil <<<\n";
    }

    int percobaan=0;

    while(percobaan<3){
        garis();
        cout<<"              LOGIN\n";
        garis();

        cout<<"Username : ";
        getline(cin, username);

        cout<<"Password : ";
        getline(cin, password);

        for(int i=0;i<jumlahUser;i++){
            if(username==users[i].nama && password==users[i].password){
                loginBerhasil=true;
                userLogin=i;
                break;
            }
        }

        if(loginBerhasil){
            cout<<">>> Login berhasil <<<\n";
            menuUtama(&users[userLogin]);
            break;
        }

        cout<<"Login gagal\n";
        percobaan++;
    }

    if(!loginBerhasil)
        cout<<"Login gagal 3 kali\n";

    cout<<"\nPROGRAM SELESAI DIGUNAKAN\n";
}



