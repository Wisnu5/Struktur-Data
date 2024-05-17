#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <unordered_map>
using namespace std;

// Struktur data untuk menyimpan informasi pemilih
struct Voter
{
    string username;
    string password;
    bool hasVoted;
};

// Deklarasi fungsi
void saveVoterHistory(const Voter &voter, deque<Voter> &votersHistory);

// Fungsi untuk login
int login()
{
    int choice;
    cout << "=== Selamat datang di sistem e-voting === \n"
         << endl;
    cout << "Silakan pilih jenis login: \n";
    cout << "1. Admin\n";
    cout << "2. Pemilih\n"
         << endl;
    cout << "Pilihan Anda: ";
    cin >> choice;
    return choice;
}

// Fungsi untuk input data login
void inputLoginData(int userType, vector<Voter> &voters)
{
    Voter voter;
    cout << "Masukkan username: ";
    cin >> voter.username;
    for (auto &it : voters)
    {
        if (it.username == voter.username)
        {
            cout << "Username telah terpakai" << endl;
            return;
        }
    }
    cout << "Masukkan password: ";
    cin >> voter.password;
    voter.hasVoted = false;
    voters.push_back(voter);
    cout << "Pemilih berhasil didaftarkan.\n"
         << endl;
}

// Fungsi untuk mendaftarkan pemilih oleh admin
void registerVoterByAdmin(vector<Voter> &voters)
{
    cout << "=== Daftar Pemilih Baru ===\n";
    inputLoginData(2, voters);
}

// Fungsi untuk mendaftarkan calon oleh admin
void registerCandidate(unordered_map<string, int> &candidates)
{
    string name;
    cout << "Masukkan nama calon: ";
    cin >> name;
    candidates[name] = 0;
    cout << "Calon berhasil didaftarkan.\n"
         << endl;
}

// Fungsi untuk memilih calon oleh pemilih
void chooseCandidate(vector<Voter> &voters, unordered_map<string, int> &candidates, vector<Voter>::iterator it)
{
    cout << "=== Pilihan Calon ===\n";
    int index = 1;
    for (const auto &candidate : candidates)
    {
        cout << index << ". " << candidate.first << endl;
        index++;
    }

    int choice;
    cout << "Pilih calon (1-" << candidates.size() << "): ";
    cin >> choice;

    if (choice >= 1 && choice <= candidates.size())
    {
        cout << "Apakah anda yakin dengan pilihan ini? (Y/N) : ";
        char pilih;
        cin >> pilih;
        if (tolower(pilih) == 'y')
        {
            (*it).hasVoted = true;

            string choiceCandidate;
            index = 1;
            for (const auto &candidate : candidates)
            {
                if (index == choice)
                    choiceCandidate = candidate.first;
                index++;
            }

            candidates[choiceCandidate]++;
            cout << "Terima kasih atas partisipasinya.\n"
                 << endl;
        }
        else
            chooseCandidate(voters, candidates, it);
    }
    else
    {
        cout << "Pilihan tidak valid.\n"
             << endl;
        chooseCandidate(voters, candidates, it);
    }
}

// Fungsi untuk melakukan voting oleh pemilih
void vote(vector<Voter> &voters, unordered_map<string, int> &candidates, deque<Voter> &votersHistory)
{
    string username, password;
    cout << "Masukkan username Anda: ";
    cin >> username;
    cout << "Masukkan password Anda: ";
    cin >> password;

    auto it = find_if(voters.begin(), voters.end(), [username, password](const Voter &v)
                      { return v.username == username && v.password == password; });

    if (it != voters.end())
    {
        if ((*it).hasVoted)
        {
            cout << "Anda sudah melakukan voting.\n"
                 << endl;
        }
        else
        {
            chooseCandidate(voters, candidates, it);
            saveVoterHistory(*it, votersHistory); // Panggil fungsi saveVoterHistory di sini
        }
    }
    else
    {
        cout << "Username atau password tidak valid.\n"
             << endl;
    }
}

// Fungsi untuk menyimpan riwayat pemilih
void saveVoterHistory(const Voter &voter, deque<Voter> &votersHistory)
{
    votersHistory.push_back(voter);
    cout << "Riwayat pemilih berhasil disimpan.\n"
         << endl;
}

// Fungsi untuk menampilkan riwayat pemilih
void displayVoterHistory(const deque<Voter> &votersHistory)
{
    cout << "=== Riwayat Pemilih ===\n";
    for (const auto &voter : votersHistory)
    {
        cout << "Username: " << voter.username << "\n";
        cout << "Password: " << voter.password << "\n";
        cout << "Status Voting: " << (voter.hasVoted ? "Sudah melakukan voting" : "Belum melakukan voting") << "\n";
        cout << endl;
    }
}

// Fungsi untuk perhitungan suara
void calculateVotes(unordered_map<string, int> &candidates)
{
    cout << "=== Hasil Perhitungan Suara ===\n";
    for (const auto &candidate : candidates)
    {
        cout << candidate.first << ": " << candidate.second << " suara\n";
    }
}

// Fungsi untuk mencari pemilih oleh admin
void searchVoter(const vector<Voter> &voters)
{
    string username;
    cout << "Masukkan username pemilih yang ingin dicari: ";
    cin >> username;

    auto it = find_if(voters.begin(), voters.end(), [username](const Voter &v)
                      { return v.username == username; });

    if (it != voters.end())
    {
        cout << "Data pemilih ditemukan:\n";
        cout << "Username: " << (*it).username << "\n";
        cout << "Password: " << (*it).password << "\n";
        cout << "Status Voting: " << ((*it).hasVoted ? "Sudah melakukan voting" : "Belum melakukan voting") << "\n";
    }
    else
    {
        cout << "Pemilih tidak ditemukan.\n"
             << endl;
    }
}

// Fungsi untuk menghapus data pemilih oleh admin
void deleteVoter(vector<Voter> &voters)
{
    string username;
    cout << "Masukkan username pemilih yang ingin dihapus: ";
    cin >> username;

    auto it = find_if(voters.begin(), voters.end(), [username](const Voter &v)
                      { return v.username == username; });

    if (it != voters.end())
    {
        voters.erase(it);
        cout << "Pemilih berhasil dihapus.\n"
             << endl;
    }
    else
    {
        cout << "Pemilih tidak ditemukan.\n"
             << endl;
    }
}

// Fungsi untuk memperbarui data pemilih oleh admin
void updateVoterData(vector<Voter> &voters)
{
    string username;
    cout << "Masukkan username pemilih yang ingin diperbarui: ";
    cin >> username;

    auto it = find_if(voters.begin(), voters.end(), [username](const Voter &v)
                      { return v.username == username; });

    if (it != voters.end())
    {
        cout << "Masukkan password baru: ";
        cin >> (*it).password;
        cout << "Data pemilih berhasil diperbarui.\n"
             << endl;
    }
    else
    {
        cout << "Pemilih tidak ditemukan.\n"
             << endl;
    }
}

int main()
{
    vector<Voter> voters;
    unordered_map<string, int> candidates;
    deque<Voter> votersHistory;

    while (true)
    {
        int choice = login();

        if (choice == 1)
        { // Admin
            string adminUsername = "admin";
            string adminPassword = "password";
            string username, password;

            cout << "Masukkan username admin: ";
            cin >> username;
            cout << "Masukkan password admin: ";
            cin >> password;

            if (username == adminUsername && password == adminPassword)
            {
                cout << "Login admin berhasil.\n"
                     << endl;
                while (true)
                {
                    int adminChoice;

                    cout << " ======={ Menu Admin }======= \n";
                    cout << "+-----------------------------+\n";
                    cout << "|   1. Daftarkan Pemilih      |\n";
                    cout << "|   2. Daftarkan Calon        |\n";
                    cout << "|   3. Cari Pemilih           |\n";
                    cout << "|   4. Hapus Pemilih          |\n";
                    cout << "|   5. Perbarui Data Pemilih  |\n";
                    cout << "|   6. Lihat Hasil Suara      |\n";
                    cout << "|   7. Lihat Riwayat Pemilih  |\n";
                    cout << "|   8. Keluar                 |\n";
                    cout << "+-----------------------------+\n";
                    cout << "Pilihan Anda: ";
                    cin >> adminChoice;

                    switch (adminChoice)
                    {
                    case 1:
                        registerVoterByAdmin(voters);
                        break;
                    case 2:
                        registerCandidate(candidates);
                        break;
                    case 3:
                        searchVoter(voters);
                        break;
                    case 4:
                        deleteVoter(voters);
                        break;
                    case 5:
                        updateVoterData(voters);
                        break;
                    case 6:
                        calculateVotes(candidates);
                        break;
                    case 7:
                        displayVoterHistory(votersHistory);
                        break;
                    case 8:
                        cout << "Keluar dari sistem admin.\n";
                        break;
                    default:
                        cout << "Pilihan tidak valid.\n";
                    }

                    if (adminChoice == 8)
                    {
                        break;
                    }
                }
            }
            else
            {
                cout << "Login admin gagal.\n"
                     << endl;
            }
        }
        else if (choice == 2)
        { // Pemilih
            vote(voters, candidates, votersHistory);
        }
        else
        {
            cout << "Pilihan tidak valid.\n"
                 << endl;
        }
    }

    return 0;
}