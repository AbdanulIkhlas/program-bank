#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <windows.h>
using namespace std;

struct data_akun
{
    string user_name, password;
    long jumlah_uang;
};

struct data_diri {
    string nama, NIK;
    int rekening;
    data_akun akun;
};

fstream file;

void tukar(data_diri arr[][100], int z, int x, int y);

void bubble_sort(data_diri arr[][100], int lenA, int lenB);

bool binary_search(data_diri arr[][100], int idx, int* idx_target, string target, int len, int min = 0);
bool sequential_search_rekening(data_diri arr[][100], int idx, int* idx_target, int target, int len);

string remove_space(string str);

string remove_underscore(string str);

void file_to_struct(int* idx_a, int* idx_b, data_diri nasabah[][100]);

void print_struct(data_diri nasabah[][100], int idx, int len);

int main()
{
    data_diri nasabah[2][100]; //indeks 0 dimensi 1 mewakili nasabah Bank A, indeks 1 dimensi 1 mewakiliki nasabah Bank B
    char konfirmasi = 'y';
    int menu, idx_a = 0, idx_b = 0, uang, temp = 0, temp_target = 0, rekening, idx, idx_target, admin, kesempatan;
    string username, password;
    bool cek = 0, cek_target = 0, ulang1 = 0;
    char ulang = 'y',ulang2; 
    do
    {
        kesempatan = 3;
        system("cls");
        cout << "=============== PROGRAM BANK ===============" << endl;
        cout<<endl<<endl;
        file_to_struct(&idx_a, &idx_b, nasabah);
        cout << "+------------------------------------------+" << endl;
        cout << "|                MENU AWAL                 |" << endl;
        cout << "+------------------------------------------+"<< endl;
        cout << "| 1. Login                                 |\n"
             << "| 2. Buka Rekening (jika belum ada akun)   |\n"
             << "| 3. Tampilkan Data                        |\n"
             << "| 4. Exit                                  |\n";
    	cout << "+------------------------------------------+"<< endl;
        cout << " Menu : ";
         cin >> menu;
        if (menu == 1) {
            do {
                system("cls");
                bubble_sort(nasabah, idx_a, idx_b);
                cout << "+==============================+" << endl;
                cout << "|            LOGIN             |" << endl;
                cout << "+==============================+" << endl;
                cout << "| 1. Bank A                    |\n"
                     << "| 2. Bank B                    |\n";
                cout << "+==============================+" << endl;     
                cout << "Pilih : ";
                cin >> menu;
                if (menu == 1) {
                    do
                    {
                        system("cls");
                        cout << "+===============================+" << endl;
                        cout << "|            BANK A             |" << endl;
                        cout << "+===============================+" << endl;
                        cout << endl;
                        cout << "Username : ";
                        if(kesempatan==3) cin.ignore();
                        getline(cin, username);
                        cout << "Password : ";
                        getline(cin, password);
                        cek = binary_search(nasabah, 0, &temp, username, idx_a - 1);
                        if (cek == false || password != nasabah[0][temp].akun.password) {
                            cout << "Username atau Password Salah!!";
                            kesempatan -= 1;
                            system("pause>0");
                        }else{
                        	cout<<endl;
                        	cout << "LOGIN BERHASIL"<<endl;
                        	cout <<"<Tekan sembarang untuk lanjut>"<<endl;
                        	system("pause>0");
						}
                        idx = 0;
                        ulang1 = 0;
                    } while (kesempatan > 0 && (cek == false || password != nasabah[0][temp].akun.password));
                }
                else if (menu == 2) {
                    do
                    {
                        system("cls");
                        cout << "+===============================+" << endl;
                        cout << "|            BANK B             |" << endl;
                        cout << "+===============================+" << endl;
                        cout << endl;
                        cout << "Username : ";
                        cin.ignore();
                        getline(cin, username);
                        cout << "Password : ";
                        getline(cin, password);
                        cek = binary_search(nasabah, 1, &temp, username, idx_a - 1);
                        if (cek == false || password != nasabah[1][temp].akun.password) {
                            cout << "Username atau Password Salah!!";
                            system("pause>0");
                            kesempatan -= 1;
                        }else{
                        	cout<<endl;
                        	cout << "LOGIN BERHASIL"<<endl;
                        	cout <<"<Tekan sembarang untuk lanjut>"<<endl;
                        	system("pause>0");
						}
                        idx = 1;
                        ulang1 = 0;
                    } while (kesempatan > 0 && (cek == false || password != nasabah[1][temp].akun.password));
                }
                else {
                    system("cls");
                    cout << "Inputan Menu Salah\nTekan Enter Untuk Kembali";
                    ulang1 = 1;
                    system("pause>0");
                }
                if (kesempatan == 0) {
                    system("cls");
                    cout << "Coba Lagi Nanti!!!";
                    system("pause>0");
                    return 0;
                }
            } while (ulang1 == 1);
            do
            {
                system("cls");
                cout << "+----------------------------+" << endl;
                cout << "|          TRANSAKSI         |" << endl;
                cout << "+----------------------------+" << endl;
                cout << "| 1. Setor Tunai             |\n"
                     << "| 2. Tarik Tunai             |\n"
                     << "| 3. Transfer                |\n"
                     << "| 4. Cek Saldo               |\n";
                cout << "| 5. Balik Ke Menu Awal      |\n";
                cout << "+----------------------------+" << endl;
                cout << "Menu : ";
                cin >> menu;
                if (menu == 1) {
                    system("cls");
                    cout << "SETOR TUNAI\n";
                    cout << "-------------" << endl;
                    cout << "Masukkan Jumlah Uang\t: ";
                    cin >> uang;
                    nasabah[idx][temp].akun.jumlah_uang += uang;
                    if (idx == 0) {
                        file.open("data_nasabah_a.txt", ios::out);
                    }
                    else {
                        file.open("data_nasabah_b.txt", ios::out);
                    }
                    if (file.is_open()) {
                        for (int i = 0; i < idx_a; i++) {
                            file << setw(20) << left << remove_space(nasabah[idx][i].nama) << setw(20) << nasabah[idx][i].NIK << setw(15) << nasabah[idx][i].rekening << setw(30)
                                << nasabah[idx][i].akun.jumlah_uang << setw(20) << remove_space(nasabah[idx][i].akun.user_name) << setw(20) << remove_space(nasabah[idx][i].akun.password);
                            file << endl;
                        }
                        file.close();
                    }
                    cout << endl;
                    cout << "Setor Tunai Sebesar Rp " << uang << endl << "Berhasil!!!" << endl << endl;
                    cout<<"Balik Ke Menu Transaksi (y/n)? ";
                    cin >> ulang2;
                }
                else if (menu == 2) {
                    system("cls");
                    cout << "TARIK TUNAI\n";
                    cout << "-------------" << endl;
                    cout << "Masukkan Jumlah Uang\t: ";
                    cin >> uang;
                    if (nasabah[idx][temp].akun.jumlah_uang < uang) {
                        cout << "\nSaldo Tidak Cukup\n"
                            << "Sisa Saldo Anda\t: Rp "
                            << nasabah[idx][temp].akun.jumlah_uang;
                        cout << endl << endl;
                        cout << "Balik Ke Menu Transaksi (y/n)? ";
                        cin >> ulang2;
                    }
                    else {
                        nasabah[idx][temp].akun.jumlah_uang -= uang;
                        cout << endl << "Tarik Tunai Sebesar Rp " << uang << endl << "Berhasil!!!" << endl << endl << "Sisa Saldo Anda Sebesar Rp " << nasabah[idx][temp].akun.jumlah_uang
                            << endl << endl;
                        cout << "Balik Ke Menu Transaksi (y/n)? ";
                        cin >> ulang2;
                    }
                    if (idx == 0) {
                        file.open("data_nasabah_a.txt", ios::out);
                    }
                    else {
                        file.open("data_nasabah_b.txt", ios::out);
                    }
                    if (file.is_open()) {
                        cout << idx_a;
                        for (int i = 0; i < idx_a; i++) {
                            file << setw(20) << left << remove_space(nasabah[idx][i].nama) << setw(20) << nasabah[idx][i].NIK << setw(15) << nasabah[idx][i].rekening << setw(30)
                                << nasabah[idx][i].akun.jumlah_uang << setw(20) << remove_space(nasabah[idx][i].akun.user_name) << setw(20) << remove_space(nasabah[idx][i].akun.password);
                            file << endl;
                        }
                        file.close();
                    }
                }
                else if (menu == 3) {
                    system("cls");
                    cout << "TRANSFER\n";
                    cout << "-------------" << endl;
                    cout << "Rekening yang ingin di transfer: ";
                    cin >> rekening;
                    if (rekening >= 213210000) {
                        cek_target = sequential_search_rekening(nasabah, 1, &temp_target, rekening, idx_b);
                        idx_target = 1;
                    }
                    else if (rekening < 213210000) {
                        cek_target = sequential_search_rekening(nasabah, 0, &temp_target, rekening, idx_a);
                        idx_target = 0;
                    }
                    if (cek_target == 0) {
                        cout << "Rekening Tidak Ditemukan\n\n";
                        cout << "Balik Ke Menu Transaksi (y/n)? ";
                        cin >> ulang2;
                    }
                    else if (cek_target == 1) {
                        system("cls");
                        cout << "REKENING TUJUAN DITEMUKAN" << endl << endl ;
                        cout << "Rekening Tujuan Atas Nama       : " << nasabah[idx_target][temp_target].nama << endl;
                        cout << "\nMasukkan jumlah uang transfer\t: ";
                        cin >> uang;
                        if ((idx == 0 && idx_target == 1) || (idx == 1 && idx_target == 0)) {
                            cout << "biaya admin\t\t\t: 5000\n";
                            if (nasabah[idx][temp].akun.jumlah_uang < uang + 5000) {
                                cout << "\nSaldo Tidak Cukup\n"
                                    << "Sisa Saldo Anda\t: Rp "
                                    << nasabah[idx][temp].akun.jumlah_uang;
                                cek = 0;
                                cout << "\nBalik Ke Menu Transaksi (y/n)? ";
                                cin >> ulang2;
                            }else{
                            	cek=1;
							}
                        }
                        else if ((idx == 0 && idx_target == 0) || (idx == 1 && idx_target == 1)) {
                            if (nasabah[idx][temp].akun.jumlah_uang < uang) {
                                cout << "Saldo Tidak Cukup\n"
                                    << "Sisa Saldo Anda\t: Rp "
                                    << nasabah[idx][temp].akun.jumlah_uang;
                                cek = 0;
                                cout << endl << "\nBalik Ke Menu Transaksi (y/n)? ";
                                cin >> ulang2;
                            }else{
                            	cek=1;
							}
                        }
                        if (cek == 1) {
                            cout << "Konfirmasi Transfer (y/t)\t: ";
                            cin >> konfirmasi;
                            if (konfirmasi == 'y' || konfirmasi == 'Y') {
                                if ((idx == 1 && idx_target == 0) || (idx == 0 && idx_target == 1)) {
                                    nasabah[idx][temp].akun.jumlah_uang -= (uang + 5000);
                                }
                                else {
                                    nasabah[idx][temp].akun.jumlah_uang -= uang;
                                }
                                nasabah[idx_target][temp_target].akun.jumlah_uang += uang;
                                system("cls");
                                cout << "+===================================================================================+"<<endl; Sleep(1000);                                
                                cout << "|                             -- BUKTI TRANSFER --                                  |" << endl; Sleep(1000);                                
                                cout << "+===================================================================================+"<<endl; Sleep(1000);
                                cout << "|                                                                                   |"<<endl; Sleep(1000);
                                cout << "|     Transfer kepada : " << setw(60)<< left << nasabah[idx_target][temp_target].rekening << "|" << endl; Sleep(1000);
                                cout << "|     Atas Nama       : " << setw(60)<< left << nasabah[idx_target][temp_target].nama << "|" << endl; Sleep(1000);
                                cout << "|     Jumlah transfer : " << setw(60)<< left << uang  << "|" << endl; Sleep(1000);
                                cout << "|                                                                                   |"<<endl; Sleep(1000);
                                cout << "+===================================================================================+"<<endl; Sleep(1000);
                                cout << "|                                                                                   |"<<endl; Sleep(1000);
                                cout << "|                                    SUKSES                                         |"<<endl; Sleep(1000);
                                cout << "|                                                                                   |"<<endl; Sleep(1000);
                                cout << "+===================================================================================+"<<endl; Sleep(1000);
                                Sleep(1000);
    							cout << endl << endl;
                                cout << "Balik Ke Menu Transaksi (y/n)? ";
                                cin >> ulang2;
                            }
                            else {
                                system("cls");
                                cout << "Transfer Dibatalkan!!!\n\n";
                                cout << "Balik Ke Menu Transaksi (y/n)? ";
                                cin >> ulang2;
                            }
                        }
                    }
                    file.open("data_nasabah_a.txt", ios::out);
                    if (file.is_open()) {
                        for (int i = 0; i < idx_a; i++) {
                            file << setw(20) << left << remove_space(nasabah[0][i].nama) << setw(20) << nasabah[0][i].NIK << setw(15) << nasabah[0][i].rekening << setw(30)
                                << nasabah[0][i].akun.jumlah_uang << setw(20) << remove_space(nasabah[0][i].akun.user_name) << setw(20) << remove_space(nasabah[0][i].akun.password);
                            file << endl;
                        }
                        file.close();
                    }
                    file.open("data_nasabah_b.txt", ios::out);
                    if (file.is_open()) {
                        for (int i = 0; i < idx_b; i++) {
                            file << setw(20) << left << remove_space(nasabah[1][i].nama) << setw(20) << nasabah[1][i].NIK << setw(15) << nasabah[1][i].rekening << setw(30)
                                << nasabah[1][i].akun.jumlah_uang << setw(20) << remove_space(nasabah[1][i].akun.user_name) << setw(20) << remove_space(nasabah[1][i].akun.password);
                            file << endl;
                        }
                        file.close();
                    }
                }
                else if (menu == 4) {
                    system("cls");
                    cout << "CEK SALDO\n";
                    cout << "-------------" << endl;
                    cout << "Rekening Atas Nama\t: " << nasabah[idx][temp].nama << endl
                        << "Sisa Saldo\t\t: Rp " << nasabah[idx][temp].akun.jumlah_uang;
                    cout << "\n\nBalik Ke Menu Transaksi (y/n)? ";
                    cin >> ulang2;
                }
                else if (menu == 5) {
                    ulang2 = 'n';
                }
                else
                {
                    system("cls");
                    cout << "Inputan Menu Salah!!!\n\n";
                    cout << "Balik Ke Menu Transaksi (y/n)? ";
                    cin >> ulang2;
                }
            } while (ulang2 == 'y' || ulang2 == 'Y');
        }
        else if (menu == 2) {
            system("cls");
            cout << "+=====================================+" << endl;
            cout << "|            BUKA REKENING            |" << endl;
            cout << "+=====================================+" << endl;
            cout << "| 1. Bank A                           |\n"
                 << "| 2. Bank B                           |\n";
            cout << "+=====================================+" << endl;
            cout << "Pilih : ";
            cin >> menu;
            system("cls");
            if (menu == 1) {
                file.open("data_nasabah_a.txt", ios::app);
                cout << "+=====================================+" << endl;
                cout << "|        BUKA REKENING BANK A         |" << endl;
                cout << "+=====================================+" << endl;
                cout << endl;
                cout << "Masukkan Nama Lengkap\t: ";
                cin.ignore();
                getline(cin, nasabah[0][idx_a].nama);
                cout << "Masukkan NIK\t\t: ";
                getline(cin, nasabah[0][idx_a].NIK);
                cout << "Saldo Awal\t\t: ";
                cin >> nasabah[0][idx_a].akun.jumlah_uang;
                cin.ignore();
                do {
                    system("cls");
                    cout << "Membuat Username Dan Password" << endl;
                    cout << "-----------------------------" << endl << endl;
                    cout << "Masukkan Username\t: ";
                    getline(cin, nasabah[0][idx_a].akun.user_name);
                    cek = binary_search(nasabah, 0, &temp, nasabah[0][idx_a].akun.user_name, idx_a - 1);
                    if (cek == 1) {
                        cout << "Username Telah Digunakan!!!";
                        system("pause>0");
                    }
                } while (cek == 1);
                cout << "Masukkan Password\t: ";
                getline(cin, nasabah[0][idx_a].akun.password);
                nasabah[0][idx_a].rekening = 123210000 + idx_a;
                system("cls");
                cout << "BUKA REKENING\n\n"
                    << "Atas Nama\t: " << nasabah[0][idx_a].nama << endl
                    << "Nomor Rekening\t: " << nasabah[0][idx_a].rekening << endl
                    << "Jumlah Saldo\t: " << nasabah[0][idx_a].akun.jumlah_uang << endl << endl
                    << "BERHASIL!!!";
                file << setw(40) << left << remove_space(nasabah[0][idx_a].nama) << setw(20) << nasabah[0][idx_a].NIK << setw(15) << nasabah[0][idx_a].rekening << setw(30)
                    << nasabah[0][idx_a].akun.jumlah_uang << setw(20) << remove_space(nasabah[0][idx_a].akun.user_name) << setw(20) << remove_space(nasabah[0][idx_a].akun.password);
                file << endl;
                idx_a += 1;
                file.close();
                cout << endl << "Balik ke menu awal (y/n)? ";
                cin >> ulang;
            }
            else if (menu == 2) {
                file.open("data_nasabah_b.txt", ios::app);
                cout << "+=====================================+" << endl;
                cout << "|        BUKA REKENING BANK B         |" << endl;
                cout << "+=====================================+" << endl;
                cout << endl;
                cout << "Masukkan Nama Lengkap\t: ";
                cin.ignore();
                getline(cin, nasabah[1][idx_b].nama);
                cout << "Masukkan NIK\t\t: ";
                getline(cin, nasabah[1][idx_b].NIK);
                cout << "Saldo Awal\t\t: ";
                cin >> nasabah[1][idx_b].akun.jumlah_uang;
                cin.ignore();
                do {
                    system("cls");
                    cout << "Membuat Username Dan Password" << endl;
                    cout << "-----------------------------" << endl << endl;
                    cout << "Masukkan Username\t: ";
                    getline(cin, nasabah[1][idx_b].akun.user_name);
                    cek = binary_search(nasabah, 1, &temp, nasabah[1][idx_b].akun.user_name, idx_b - 1);
                    if (cek == 1) {
                        cout << "Username Telah Digunakan!!!";
                        system("pause>0");
                    }
                } while (cek == 1);
                cout << "Masukkan Password\t: ";
                getline(cin, nasabah[1][idx_b].akun.password);
                nasabah[1][idx_b].rekening = 231210000 + idx_b;
                system("cls");
                cout << "BUKA REKENING\n\n"
                    << "Atas Nama\t: " << nasabah[1][idx_b].nama << endl
                    << "Nomor Rekening\t: " << nasabah[1][idx_b].rekening << endl
                    << "Jumlah Saldo\t: " << nasabah[1][idx_b].akun.jumlah_uang << endl << endl
                    << "BERHASIL!!!";
                file << setw(40) << left << remove_space(nasabah[1][idx_b].nama) << setw(20) << nasabah[1][idx_b].NIK << setw(15) << nasabah[1][idx_b].rekening << setw(30)
                    << nasabah[1][idx_b].akun.jumlah_uang << setw(20) << remove_space(nasabah[1][idx_b].akun.user_name) << setw(20) << remove_space(nasabah[1][idx_b].akun.password);
                file << endl;
                idx_b += 1;
                file.close();
                cout << endl << "Balik ke menu awal (y/n)? ";
                cin >> ulang;
            }
            else {
                system("cls");
                cout << "Inputan Menu Salah!!!\nTekan Enter untuk kembali ";
                system("pause>0");
            }
        
        }
        else if (menu == 3) {
            system("cls");
            cout << "+=====================================+" << endl;
            cout << "|           LIST DATA NASABAH         |" << endl;
            cout << "+=====================================+" << endl;
            cout << "| 1. Bank A                           |\n"
                 << "| 2. Bank B                           |\n";
        	cout << "+=====================================+" << endl;
            cout << "Pilih : ";
            cin >> menu;
            if (menu == 1) {
                do
                {
                    system("cls");
                    cout << "+=====================================+" << endl;
                    cout << "|         ADMINISTRATOR BANK A        |" << endl;
                    cout << "+=====================================+" << endl;
                    cout << endl;
                    cout << "username : "; //adminA
                    if (kesempatan == 3) cin.ignore();
                    getline(cin, username);
                    cout << "password : "; //adminA123
                    getline(cin, password);
                    if (username != "adminA" || password != "adminA123") {
                        cout << "Username atau Password Salah!!!";
                        system("pause>0");
                        kesempatan -= 1;
                    }
                } while (kesempatan > 0 && (username != "adminA" || password != "adminA123"));
                if (kesempatan > 0) {
                    system("cls");
                    cout << "List Data Nasabah Bank A\n\n";
                    print_struct(nasabah, 0, idx_a);
                    cout << endl << "Balik ke menu awal (y/n)? ";
                    cin >> ulang;
                }
            }
            else if (menu == 2) {
                do
                {
                    system("cls");
                    cout << "+=====================================+" << endl;
                    cout << "|         ADMINISTRATOR BANK B        |" << endl;
                    cout << "+=====================================+" << endl;
                    cout << endl;
                    cout << "username : ";//adminB
                    if (kesempatan == 3) cin.ignore();
                    getline(cin, username);
                    cout << "password : ";//adminB123
                    getline(cin, password);
                    if (username != "adminB"  || password != "adminB123") {
                        cout << "Username atau Password Salah!!!";
                        system("pause>0");
                        kesempatan -= 1;
                    }
                } while (kesempatan > 0 && (username != "adminB" || password != "adminB123"));
                if (kesempatan > 0) {
                    system("cls");
                    cout << "List Data Nasabah Bank B\n\n";
                    print_struct(nasabah, 1, idx_b);
                    cout << endl << "Balik ke menu awal (y/n)? ";
                    cin >> ulang;
                }
            }
            else {
                system("cls");
                cout << "Inputan Menu Salah!!!\nTekan Enter untuk kembali ";
                system("pause>0");
            }
            
            if (kesempatan == 0) {
                system("cls");
                cout << "Coba Lagi Nanti!!!";
                system("pause>0");
                return 0;
            }
        }
        else if (menu == 4) {
            system("cls");
            cout << "PROGRAM SELESAI\n";
            return 0;
        }
        else {
            system("cls");
            cout << "Inputan Menu Salah!!!\nTekan Enter untuk kembali ";
            system("pause>0");
        }
    } while (ulang == 'y' || ulang == 'Y');
    cout << endl << "PROGRAM SELESAI";
}

void tukar(data_diri arr[][100], int z, int x, int y) {
    /*
        menukar struct[z][x] dengan struct[z][y]
    */
    string temp_str; int temp_int;

    temp_str = arr[z][x].nama;
    arr[z][x].nama = arr[z][y].nama;
    arr[z][y].nama = temp_str;

    temp_str = arr[z][x].NIK;
    arr[z][x].NIK = arr[z][y].NIK;
    arr[z][y].NIK = temp_str;

    temp_int = arr[z][x].rekening;
    arr[z][x].rekening = arr[z][y].rekening;
    arr[z][y].rekening = temp_int;

    temp_str = arr[z][x].akun.user_name;
    arr[z][x].akun.user_name = arr[z][y].akun.user_name;
    arr[z][y].akun.user_name = temp_str;

    temp_str = arr[z][x].akun.password;
    arr[z][x].akun.password = arr[z][y].akun.password;
    arr[z][y].akun.password = temp_str;

    temp_int = arr[z][x].akun.jumlah_uang;
    arr[z][x].akun.jumlah_uang = arr[z][y].akun.jumlah_uang;
    arr[z][y].akun.jumlah_uang = temp_int;
}

void bubble_sort(data_diri arr[][100], int lenA, int lenB) {
    /*
    mensorting array berdasarkan username dari kecil ke besar
    arr[][100] = array dari seluruh nasabah bank
    lenA = banyak nasabah bankA
    lenB = banyak nasabah bankB
    */
    int len;
    for (int z = 0; z < 2; z++) {
        if (z == 0) {
            len = lenA;
        }
        else {
            len = lenB;
        }
        for (int i = 0; i < len - 1; i++) {
            for (int j = 0; j < len - i - 1; j++) {
                if (arr[z][j].akun.user_name > arr[z][j + 1].akun.user_name) {
                    tukar(arr, z, j, j + 1);
                }
            }
        }
    }
}

bool binary_search(data_diri arr[][100], int idx, int* idx_target, string target, int len, int min) {
    /*mencari username nasabah pada array
    arr[][100] = array dari seluruh nasabah bank
    idx = index yang mewakili jenis bank
    idx_target = index kosong. Nantinya akan mewakili index dari username nasabah yang akan dicari
    string target = username dari nasabah yang ingin dicari
    len = banyak nasabah dari suatu bank
    min = integer dengan value awal 0 yang akan digunakan pada binary search
    */
    int mid = (min + len) / 2;
    if (len >= min) {
        if (arr[idx][mid].akun.user_name == target) {
            //idx_target akan berisi alamat suatu integer dengan value index dari username yang dicari
            *idx_target = mid;

            return true;
        }

        if (arr[idx][mid].akun.user_name > target) {
            return binary_search(arr, idx, idx_target, target, mid - 1, min);
        }

        else {
            return binary_search(arr, idx, idx_target, target, len, mid + 1);
        }
    }
    else {
        //apabila username tidak ditemukan, return false
        return false;
    }
}

bool sequential_search_rekening(data_diri arr[][100], int idx, int* idx_target, int target, int len) {
    /*algoritma sequential search mencari rekening
    idx = index yang mewakili jenis bank
    idx_target = index kosong. Nantinya akan mewakili index dari username nasabah yang akan dicari
    len = banyak nasabah dari suatu bank
    */
    for (int i = 0; i < len; i++) {
        if (arr[idx][i].rekening == target) {
            *idx_target = i;
            return 1;
        }
    }
    return 0;
}

string remove_space(string str) {//fungsi untuk mengubah spasi menjadi '_'
    string result = "";
    for (int i = 0; str[i]; i++) {
        if (str[i] == ' ') {
            result += '_';
        }
        else {
            result += str[i];
        }
    }
    return result;
}

string remove_underscore(string str) {//fungsi untuk mengubah '_' menjadi spasi
    string result = "";
    for (int i = 0; str[i]; i++) {
        if (str[i] == '_') {
            result += ' ';
        }
        else {
            result += str[i];
        }
    }
    return result;
}

void file_to_struct(int* idx_a, int* idx_b, data_diri nasabah[][100]) {
    /*
    algoritma untuk mentransfer value dari file ke struct
    idx_a = jumlah nasabah bank a
    idx_b = jumlah nasabah bank b
    */
    *idx_a = 0;
    *idx_b = 0;
    string temp;
    file.open("data_nasabah_a.txt", ios::in);
    if (file.is_open())
    {
        ifstream in("data_nasabah_a.txt");
        while (getline(file, temp))
        {
            in >> nasabah[0][*idx_a].nama >> nasabah[0][*idx_a].NIK >> nasabah[0][*idx_a].rekening >> nasabah[0][*idx_a].akun.jumlah_uang >> nasabah[0][*idx_a].akun.user_name >> nasabah[0][*idx_a].akun.password;
            nasabah[0][*idx_a].nama = remove_underscore(nasabah[0][*idx_a].nama);
            *idx_a += 1;
        }
    }
    file.close();


    file.open("data_nasabah_b.txt", ios::in);
    if (file.is_open())
    {
        ifstream in("data_nasabah_b.txt");
        while (getline(file, temp))
        {
            in >> nasabah[1][*idx_b].nama >> nasabah[1][*idx_b].NIK >> nasabah[1][*idx_b].rekening >> nasabah[1][*idx_b].akun.jumlah_uang >> nasabah[1][*idx_b].akun.user_name >> nasabah[1][*idx_b].akun.password;
            nasabah[1][*idx_b].nama = remove_underscore(nasabah[1][*idx_b].nama);
            *idx_b += 1;
        }
    }
    file.close();

}

void print_struct(data_diri nasabah[][100], int idx, int len) {
    /*
    algoritma untuk ngeprint struct
    idx = index mewakili jenis bank
    len = banyak nasabah dari suatu bank
    */
    for (int i = 0; i < len; i++) {
        cout << "Nama\t\t: " << nasabah[idx][i].nama << endl << "NIK\t\t: " << nasabah[idx][i].NIK << endl << "Rekening\t: " << nasabah[idx][i].rekening << endl << "Jumlah uang\t: " << nasabah[idx][i].akun.jumlah_uang << endl << endl;
    }

}
