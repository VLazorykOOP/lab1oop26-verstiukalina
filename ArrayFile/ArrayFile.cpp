#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int InputSize()
{
    int n = 0;
    do
    {
        cout << "Input size (0 < n < 650): ";
        cin >> n;
    } while (n <= 0 || n >= 650);
    return n;
}

bool ReadArrayFromFile(const char *fileName, vector<int> &arr)
{
    ifstream fin(fileName);
    if (!fin)
        return false;

    int n = 0;
    fin >> n;
    if (!fin || n <= 0 || n >= 650)
        return false;

    arr.assign(n, 0);
    for (int i = 0; i < n; i++)
    {
        fin >> arr[i];
        if (!fin)
            return false;
    }

    return true;
}

void WriteArrayToFile(const char *fileName, const vector<int> &arr)
{
    ofstream fout(fileName);
    if (!fout)
        return;

    fout << arr.size() << '\n';
    for (size_t i = 0; i < arr.size(); i++)
        fout << arr[i] << ' ';
}

vector<int> InputArray()
{
    int n = InputSize();
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cout << "A[" << i << "] = ";
        cin >> arr[i];
    }
    return arr;
}

vector<int> LoadOrCreateInputArray()
{
    vector<int> arr;
    if (ReadArrayFromFile("input.txt", arr))
    {
        cout << "Read array from " << "input.txt" << '\n';
        return arr;
    }

    cout << "File input.txt not found.\n";
    cout << "Enter array from console.\n";
    arr = InputArray();
    WriteArrayToFile("input.txt", arr);
    cout << "Saved input array to input.txt\n";
    return arr;
}

void PrintArray(const vector<int> &arr, const char *title)
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

void SolveTask1()
{
    vector<int> A = LoadOrCreateInputArray();
    vector<int> B;

    for (int x : A)
    {
        if (x < 0)
            B.push_back(x);
    }

    PrintArray(B, "Task 1 result (negative elements):");
    WriteArrayToFile("task1_result.txt", B);
    cout << "Saved to task1_result.txt\n";
}

void SolveTask2()
{
    vector<int> A = LoadOrCreateInputArray();

    int T;
    cout << "Input T: ";
    cin >> T;

    int posT = -1;
    for (size_t i = 0; i < A.size(); i++)
    {
        if (A[i] == T)
        {
            posT = static_cast<int>(i);
            break;
        }
    }

    vector<int> out;
    if (posT != -1)
    {
        bool found = false;
        int maxNeg = 0;
        for (int i = 0; i < posT; i++)
        {
            if (A[i] < 0 && (!found || A[i] > maxNeg))
            {
                maxNeg = A[i];
                found = true;
            }
        }
        if (found)
            out.push_back(maxNeg);
    }

    if (out.empty())
        cout << "Task 2: no result.\n";
    else
        cout << "Task 2 result: " << out[0] << '\n';

    WriteArrayToFile("task2_result.txt", out);
    cout << "Saved to task2_result.txt\n";
}

void SolveTask3()
{
    vector<int> A = LoadOrCreateInputArray();
    vector<int> B;

    for (size_t i = 0; i < A.size(); i++)
    {
        int count = 0;
        for (size_t j = 0; j < A.size(); j++)
        {
            if (A[j] == A[i])
                count++;
        }

        if (count > 1)
        {
            bool exists = false;
            for (int x : B)
            {
                if (x == A[i])
                {
                    exists = true;
                    break;
                }
            }
            if (!exists)
                B.push_back(A[i]);
        }
    }

    PrintArray(B, "Task 3 result (repeating elements):");
    WriteArrayToFile("task3_result.txt", B);
    cout << "Saved to task3_result.txt\n";
}

void ShowMainMenu()
{
    cout << "MENU\n";
    cout << "1. Task 1\n";
    cout << "2. Task 2\n";
    cout << "3. Task 3\n";
    cout << "0. Exit\n";
    cout << "Your choice: ";
}

int main()
{
    while (true)
    {
        ShowMainMenu();

        int choice;
        cin >> choice;
        cout << '\n';

        switch (choice)
        {
        case 1:
            SolveTask1();
            break;
        case 2:
            SolveTask2();
            break;
        case 3:
            SolveTask3();
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
