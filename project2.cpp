#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

struct Lagu
{
    string judul;
    string artis;
    int jumlahPendengar;
    string genre;
    float rating;
    string playlist; // nama playlist tempat lagu ini
    Lagu *next;
};

struct Playlist
{
    string nama;
    Playlist *next;
};

Lagu *head = nullptr;
Playlist *headPlaylist = nullptr;

// Tambah playlist baru
void tambahPlaylist(string nama)
{
    Playlist *temp = headPlaylist;
    while (temp)
    {
        if (temp->nama == nama)
        {
            cout << "Playlist \"" << nama << "\" sudah ada.\n";
            return;
        }
        temp = temp->next;
    }
    Playlist *baru = new Playlist{nama, nullptr};
    if (!headPlaylist)
    {
        headPlaylist = baru;
    }
    else
    {
        Playlist *last = headPlaylist;
        while (last->next)
            last = last->next;
        last->next = baru;
    }
    cout << "Playlist \"" << nama << "\" berhasil dibuat.\n";
}

// Tampilkan semua playlist
void tampilkanPlaylist()
{
    if (!headPlaylist)
    {
        cout << "Belum ada playlist yang terbuat.\n";
        return;
    }
    cout << "\nDaftar playlist!\n";
    Playlist *temp = headPlaylist;
    int no = 1;
    while (temp)
    {
        cout << no++ << ". " << temp->nama << "\n";
        temp = temp->next;
    }
}

// Cek ada playlist atau tidak
bool adaPlaylist()
{
    return headPlaylist != nullptr;
}

// Tambah lagu biasa (dipakai di load dari file)
void tambahLagu(string judul, string artis, int jumlahPendengar, string genre, float rating, string playlist)
{
    Lagu *baru = new Lagu{judul, artis, jumlahPendengar, genre, rating, playlist, nullptr};
    if (!head)
    {
        head = baru;
    }
    else
    {
        Lagu *temp = head;
        while (temp->next)
            temp = temp->next;
        temp->next = baru;
    }
}

// Tambah lagu dengan tanya playlist interaktif
void tambahLaguInteraktif()
{
    string judul, artis, genre, playlist = "";
    int jumlahPendengar;
    float rating;
    cout << "\nMasukkan Judul Lagu\t\t\t: ";
    getline(cin, judul);
    cout << "Artis\t\t\t\t\t: ";
    getline(cin, artis);
    cout << "Masukkan Jumlah Pendengar\t\t: ";
    cin >> jumlahPendengar;
    cin.ignore();
    cout << "Masukkan Genre (Pop/Rock/Jazz/Hip-Hop)\t: ";
    getline(cin, genre);
    cout << "Masukkan Rating (1 - 10)\t\t: ";
    cin >> rating;
    cin.ignore();

    if (rating < 1 || rating > 10)
    {
        cout << "Rating tidak valid. Harus antara 1 hingga 10.\n";
        return;
    }

    char pilihanPlaylist;
    cout << "\nApakah ingin memasukkan lagu ke playlist? (y/n) : ";
    cin >> pilihanPlaylist;
    cin.ignore();

    if (pilihanPlaylist == 'y' || pilihanPlaylist == 'Y')
    {
        if (!adaPlaylist())
        {
            cout << "\nBelum ada playlist yang terbuat. Silakan buat playlist dulu!\n";
            string namaPlaylist;
            cout << "\nMasukkan nama playlist baru : ";
            getline(cin, namaPlaylist);
            tambahPlaylist(namaPlaylist);
            playlist = namaPlaylist;
        }
        else
        {
            cout << "\nPilih opsi!\n";
            cout << "1. Buat playlist baru\n";
            cout << "2. Masukkan playlist yang sudah ada\n";
            cout << "Pilih : ";
            int opsi;
            cin >> opsi;
            cin.ignore();

            if (opsi == 1)
            {
                string namaPlaylist;
                cout << "\nMasukkan nama playlist baru : ";
                getline(cin, namaPlaylist);
                tambahPlaylist(namaPlaylist);
                playlist = namaPlaylist;
            }
            else if (opsi == 2)
            {
                tampilkanPlaylist();
                cout << "Masukkan nama playlist dari daftar di atas : ";
                getline(cin, playlist);

                Playlist *temp = headPlaylist;
                bool ketemu = false;
                while (temp)
                {
                    if (temp->nama == playlist)
                    {
                        ketemu = true;
                        break;
                    }
                    temp = temp->next;
                }
                if (!ketemu)
                {
                    cout << "Playlist tidak ditemukan, lagu tidak dimasukkan ke playlist.\n";
                    playlist = "";
                }
            }
            else
            {
                cout << "Pilihan tidak valid, lagu tidak dimasukkan ke playlist.\n";
            }
        }
    }

    tambahLagu(judul, artis, jumlahPendengar, genre, rating, playlist);
    cout << "\nLagu \"" << judul << "\" berhasil ditambahkan!\n";
    system("cls");
}

// Tampilkan semua lagu
void tampilkanLagu()
{
    if (!head)
    {
        cout << "Belum ada lagu.\n";
        return;
    }
    Lagu *temp = head;
    int i = 1;
    while (temp)
    {
        cout << "\nJudul\t\t\t: " << temp->judul << endl;
        cout << "Artis\t\t\t: " << temp->artis << endl;
        cout << "Jumlah Pendengar\t: " << temp->jumlahPendengar << " Kali Didengar" << endl;
        cout << "Genre\t\t\t: " << temp->genre << endl;
        cout << "Rating\t\t\t: " << fixed << setprecision(1) << temp->rating << endl;
        cout << "Playlist\t\t: " << (temp->playlist.empty() ? "-" : temp->playlist) << endl;
        temp = temp->next;
    }
}

// Cari lagu berdasarkan judul (substring)
void cariLagu(string keyword)
{
    Lagu *temp = head;
    bool ketemu = false;
    while (temp)
    {
        if (temp->judul.find(keyword) != string::npos)
        {
            cout << "\nJudul\t\t\t: " << temp->judul << endl;
            cout << "Artis\t\t\t: " << temp->artis << endl;
            cout << "Jumlah Pendengar\t: " << temp->jumlahPendengar << endl;
            cout << "Genre\t\t\t: " << temp->genre << endl;
            cout << "Rating\t\t\t: " << fixed << setprecision(1) << temp->rating << endl;
            cout << "Playlist\t\t: " << (temp->playlist.empty() ? "-" : temp->playlist) << endl;
            ketemu = true;
        }
        temp = temp->next;
    }
    if (!ketemu)
        cout << "\nLAGU TIDAK DITEMUKAN!!!\n";
}

// Sorting berdasarkan jumlah pendengar (descending)
void urutkanLagu()
{
    if (!head)
        return;
    bool swapped;
    do
    {
        swapped = false;
        Lagu *curr = head;
        while (curr->next)
        {
            if (curr->jumlahPendengar < curr->next->jumlahPendengar)
            {
                swap(curr->judul, curr->next->judul);
                swap(curr->artis, curr->next->artis);
                swap(curr->jumlahPendengar, curr->next->jumlahPendengar);
                swap(curr->genre, curr->next->genre);
                swap(curr->rating, curr->next->rating);
                swap(curr->playlist, curr->next->playlist);
                swapped = true;
            }
            curr = curr->next;
        }
    } while (swapped);
    cout << "Lagu berhasil diurutkan berdasarkan jumlah pendengar.\n";
}

// Filter berdasarkan artis atau genre
void filterLagu(string kriteria, string value)
{
    Lagu *temp = head;
    bool ketemu = false;
    while (temp)
    {
        if ((kriteria == "artis" && temp->artis == value) ||
            (kriteria == "genre" && temp->genre == value))
        {
            cout << "\nJudul\t\t\t: " << temp->judul << endl;
            cout << "Artis\t\t\t: " << temp->artis << endl;
            cout << "Jumlah Pendengar\t: " << temp->jumlahPendengar << endl;
            cout << "Genre\t\t\t: " << temp->genre << endl;
            cout << "Rating\t\t\t: " << fixed << setprecision(1) << temp->rating << endl;
            cout << "Playlist\t\t: " << (temp->playlist.empty() ? "-" : temp->playlist) << endl;
            ketemu = true;
        }
        temp = temp->next;
    }
    if (!ketemu)
        cout << "\nTidak ada lagu dengan " << kriteria << " tersebut.\n";
}

// Hapus lagu berdasarkan judul
void hapusLagu(string judul)
{
    Lagu *temp = head;
    Lagu *prev = nullptr;
    while (temp)
    {
        if (temp->judul == judul)
        {
            if (prev)
                prev->next = temp->next;
            else
                head = temp->next;
            delete temp;
            cout << "\nLagu \"" << judul << "\" berhasil dihapus.\n";
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    cout << "LAGU TIDAK DITEMUKAN!!!\n";
}

// Simpan ke file
void simpanKeFile(string filename)
{
    ofstream file(filename);
    Lagu *temp = head;
    while (temp)
    {
        file << temp->judul << "," << temp->artis << "," << temp->jumlahPendengar << ","
             << temp->genre << "," << temp->rating << "," << temp->playlist << "\n";
        temp = temp->next;
    }
    file.close();
    cout << "\nData disimpan ke " << filename << endl;
}

// Load dari file
void loadDariFile(string filename)
{
    ifstream file(filename);
    if (!file)
    {
        cout << "\nGagal membuka file " << filename << endl;
        return;
    }
    void hapusSemua();
    string line;
    while (getline(file, line))
    {
        size_t pos = 0;
        string arr[6];
        int idx = 0;
        while ((pos = line.find(',')) != string::npos && idx < 5)
        {
            arr[idx++] = line.substr(0, pos);
            line.erase(0, pos + 1);
        }
        arr[idx] = line;

        int jumlahPendengar = stoi(arr[2]);
        float rating = stof(arr[4]);

        tambahLagu(arr[0], arr[1], jumlahPendengar, arr[3], rating, arr[5]);
    }
    file.close();
    cout << "\nData dimuat dari " << filename << endl;
}

// Hapus semua lagu dan playlist dari memori
void hapusSemua()
{
    while (head)
    {
        Lagu *temp = head;
        head = head->next;
        delete temp;
    }
    while (headPlaylist)
    {
        Playlist *temp = headPlaylist;
        headPlaylist = headPlaylist->next;
        delete temp;
    }
}

int main()
{
    int pilih;
    do
    {
        cout << "\n=== MENU SPOTIFY ===\n";
        cout << "1. Tambah Lagu\n";
        cout << "2. Tampilkan Lagu\n";
        cout << "3. Cari Lagu (by Judul)\n";
        cout << "4. Urutkan Lagu (Jumlah Pendengar)\n";
        cout << "5. Filter Lagu (by Artis/Genre)\n";
        cout << "6. Hapus Lagu\n";
        cout << "7. Tampilkan Playlist\n";
        cout << "8. Simpan ke File\n";
        cout << "9. Load dari File\n";
        cout << "0. Keluar\n";
        cout << "Pilih : ";
        cin >> pilih;
        cin.ignore();
        system("cls");

        switch (pilih)
        {
        case 1:
            tambahLaguInteraktif();
            break;
        case 2:
            tampilkanLagu();
            break;
        case 3:
        {
            string keyword;
            cout << "Masukkan Judul Lagu : ";
            getline(cin, keyword);
            cariLagu(keyword);
            break;
        }
        case 4:
            urutkanLagu();
            break;
        case 5:
        {
            string kriteria, value;
            cout << "Filter berdasarkan (artis/genre) : ";
            getline(cin, kriteria);
            cout << "Masukkan " << kriteria << " : ";
            getline(cin, value);
            filterLagu(kriteria, value);
            break;
        }
        case 6:
        {
            string judul;
            cout << "Masukkan judul lagu yang ingin dihapus : ";
            getline(cin, judul);
            hapusLagu(judul);
            break;
        }
        case 7:
            tampilkanPlaylist();
            break;
        case 8:
        {
            string filename;
            cout << "Masukkan Nama File : ";
            getline(cin, filename);
            simpanKeFile(filename);
            break;
        }
        case 9:
        {
            string filename;
            cout << "Masukkan Nama File : ";
            getline(cin, filename);
            loadDariFile(filename);
            break;
        }
        case 0:
            hapusSemua();
            cout << "Terima Kasih Program Akan Di tutup!\n";
            break;
        default:
            cout << "Pilihan tidak valid.\n";
        }

    } while (pilih != 0);

    return 0;
}