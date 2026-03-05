#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>

using namespace std;

int InputSize(const int maxSize)
{
    int n = 0;
    do
    {
        cout << "Input size (0 < n < " << maxSize << "): ";
        cin >> n;
    } while (n <= 0 || n >= maxSize);
    return n;
}

bool ReadIntArrayFromFile(const char *fileName, int maxSize, int *&A, int &n)
{
    ifstream fin(fileName);
    if (!fin.is_open())
        return false;

    fin >> n;
    if (!fin || n <= 0 || n >= maxSize)
        return false;

    A = new int[n];
    if (A == nullptr)
        return false;

    for (int i = 0; i < n; i++)
    {
        fin >> A[i];
        if (!fin)
        {
            delete[] A;
            A = nullptr;
            n = 0;
            return false;
        }
    }

    return true;
}

void WriteIntArrayToFile(const char *fileName, const vector<int> &arr)
{
    ofstream fout(fileName);
    if (!fout.is_open())
        return;

    fout << arr.size() << '\n';
    for (size_t i = 0; i < arr.size(); i++)
        fout << arr[i] << ' ';
}

void WriteInputArrayToFile(const char *fileName, const int *A, int n)
{
    ofstream fout(fileName);
    if (!fout.is_open())
        return;

    fout << n << '\n';
    for (int i = 0; i < n; i++)
        fout << A[i] << ' ';
}

int LoadOrCreateInputArray(const char *inputFile, int maxSize, int *&A)
{
    int n = 0;
    if (ReadIntArrayFromFile(inputFile, maxSize, A, n))
    {
        cout << "Read array from " << inputFile << '\n';
        return n;
    }

    cout << "File " << inputFile << " not found (or invalid).\n";
    cout << "Enter array from console.\n";

    n = InputSize(maxSize);
    A = new int[n];
    if (A == nullptr)
        return 0;

    for (int i = 0; i < n; i++)
    {
        cout << "A[" << i << "] = ";
        cin >> A[i];
    }

    WriteInputArrayToFile(inputFile, A, n);
    cout << "Saved input array to " << inputFile << '\n';
    return n;
}

void PrintVector(const vector<int> &arr, const char *title)
{
    cout << title << '\n';
    if (arr.empty())
    {
        cout << "(empty)\n";
        return;
    }

    for (size_t i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << '\t';
        if ((i + 1) % 5 == 0)
            cout << '\n';
    }
    cout << '\n';
}

void ShowMainMenu()
{
    cout << "=============================\n";
    cout << "            MENU\n";
    cout << "=============================\n";
    cout << "1. Task 1\n";
    cout << "2. Task 2\n";
    cout << "3. Task 3\n";
    cout << "0. Exit\n";
    cout << "=============================\n";
    cout << "Your choice: ";
}

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    const int MAX_SIZE = 560;

    while (true)
    {
        ShowMainMenu();

        int choice;
        cin >> choice;
        cout << '\n';

        switch (choice)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 0:
            return 0;
        default:
            cout << "Wrong menu item.\n";
            break;
        }

        cout << "\nPress Enter to continue...";
        cin.ignore(10000, '\n');
        cin.get();
        system("cls");
    }
}
