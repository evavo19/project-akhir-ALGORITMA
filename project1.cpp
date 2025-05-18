#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Lagu
{
    string judul;
    string artis;
    int jumlahPendengar;
    string genre;
    int rating;
    string playlist;
    Lagu *next;
};

Lagu *head = nullptr;

// Tambah lagu ke linked list
void tambahLagu(string judul, string artis, int jumlahPendengar, string genre, int rating, string playlist)
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
        cout << i++ << ". " << temp->judul << " - " << temp->artis
             << " (" << temp->jumlahPendengar << " pendengar, Genre: " << temp->genre
             << ", Rating: " << temp->rating << ", Playlist: " << temp->playlist << ")\n";
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
            cout << temp->judul << " - " << temp->artis
                 << " (" << temp->jumlahPendengar << " pendengar, Genre: " << temp->genre
                 << ", Rating: " << temp->rating << ", Playlist: " << temp->playlist << ")\n";
            ketemu = true;
        }
        temp = temp->next;
    }
    if (!ketemu)
        cout << "Lagu tidak ditemukan.\n";
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
            cout << temp->judul << " - " << temp->artis
                 << " (" << temp->jumlahPendengar << " pendengar, Genre: " << temp->genre
                 << ", Rating: " << temp->rating << ", Playlist: " << temp->playlist << ")\n";
            ketemu = true;
        }
        temp = temp->next;
    }
    if (!ketemu)
        cout << "Tidak ada lagu dengan " << kriteria << " tersebut.\n";
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
            cout << "Lagu \"" << judul << "\" berhasil dihapus.\n";
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    cout << "Lagu tidak ditemukan.\n";
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
    cout << "Data disimpan ke " << filename << endl;
}

// Load dari file
void loadDariFile(string filename)
{
    ifstream file(filename);
    string judul, artis, genre, playlist;
    int jumlahPendengar, rating;

    while (getline(file, judul, ',') &&
           getline(file, artis, ',') &&
           (file >> jumlahPendengar) &&
           file.ignore() &&
           getline(file, genre, ',') &&
           (file >> rating) &&
           file.ignore() &&
           getline(file, playlist))
    {
        tambahLagu(judul, artis, jumlahPendengar, genre, rating, playlist);
    }

    file.close();
    cout << "Data dimuat dari " << filename << endl;
}

// Hapus semua lagu dari memori
void hapusSemua()
{
    while (head)
    {
        Lagu *temp = head;
        head = head->next;
        delete temp;
    }
}

int main()
{
    int pilihan;
    string judul, artis, genre, playlist, keyword, kriteria, value, filename;
    int jumlahPendengar, rating;

    do
    {
        cout << "\n=== MENU SPOTIFY ===\n";
        cout << "1. Tambah Lagu\n";
        cout << "2. Tampilkan Lagu\n";
        cout << "3. Cari Lagu (by Judul)\n";
        cout << "4. Urutkan Lagu (Jumlah Pendengar)\n";
        cout << "5. Filter Lagu (by Artis/Genre)\n";
        cout << "6. Hapus Lagu\n";
        cout << "7. Simpan ke File\n";
        cout << "8. Load dari File\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan)
        {
        case 1:
            cout << "Masukkan Judul Lagu : ";
            getline(cin, judul);
            cout << "Artis: ";
            getline(cin, artis);
            cout << "Masukkan Jumlah Pendengar : ";
            cin >> jumlahPendengar;
            cin.ignore();
            cout << "Masukkan Genre (Pop/Rock/Jazz/Hip-Hop): ";
            getline(cin, genre);
            cout << "Masukkan Rating (1 - 5): ";
            cin >> rating;
            cin.ignore();
            cout << "Playlist: ";
            getline(cin, playlist);
            tambahLagu(judul, artis, jumlahPendengar, genre, rating, playlist);
            break;
        case 2:
            tampilkanLagu();
            break;
        case 3:
            cout << "Keyword judul: ";
            getline(cin, keyword);
            cariLagu(keyword);
            break;
        case 4:
            urutkanLagu();
            break;
        case 5:
            cout << "Filter berdasarkan (artis/genre): ";
            getline(cin, kriteria);
            cout << "Masukkan " << kriteria << ": ";
            getline(cin, value);
            filterLagu(kriteria, value);
            break;
        case 6:
            cout << "Masukkan judul lagu yang ingin dihapus: ";
            getline(cin, judul);
            hapusLagu(judul);
            break;
        case 7:
            cout << "Nama file: ";
            getline(cin, filename);
            simpanKeFile(filename);
            break;
        case 8:
            cout << "Nama file: ";
            getline(cin, filename);
            loadDariFile(filename);
            break;
        case 0:
            hapusSemua();
            cout << "Keluar dari program.\n";
            break;
        default:
            cout << "Pilihan tidak valid.\n";
        }

    } while (pilihan != 0);

    return 0;
}
