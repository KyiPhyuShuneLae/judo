#include <iostream>
#include <algorithm>

using namespace std;

void swap(string &a, string &b)
{
    string temp = a;
    a = b;
    b = temp;
}

int getNextGap(int gap)
{
    gap = (gap * 10) / 13;
    if (gap < 1)
        return 1;
    return gap;
}

void combSort(string arr[], int n)
{
    int gap = n;

    bool swapped = true;

    while (gap != 1 || swapped)
    {
        gap = getNextGap(gap);

        swapped = false;

        for (int i = 0; i < n - gap; i++)
        {
            if (arr[i] > arr[i + gap])
            {
                swap(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
    }
}

int main()
{
    const int arraySize = 6;
    string strings[arraySize] = {"apple", "orange", "banana", "grape", "kiwi", "pear"};
    combSort(strings, arraySize);
    cout << "\n\nSorted strings:" << endl;
    for (int i = 0; i < arraySize; ++i)
    {
        cout << strings[i] << " ";
    }

    return 0;
}
