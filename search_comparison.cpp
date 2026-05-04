#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cstring>

using namespace std;

// Global variable to track comparison count during searches
long long comparisonCount = 0;

// Sequential (Linear) search template that counts comparisons
template <class elemType>
int seqSearch(const elemType list[], int length, const elemType& item)
{
    int loc;
    bool found = false;
    
    loc = 0;
    
    // Linear scan through the list until we find the item or reach the end
    while (loc < length && !found)
    {
        comparisonCount++;  // Count each comparison
        if (list[loc] == item)
            found = true;
        else
            loc++;
    }
    
    // Return the index if found, otherwise return -1
    if (found)
        return loc;
    else
        return -1;
} // end seqSearch

// Binary search template that counts comparisons
template <class elemType>
int binarySearch(const elemType list[], int length, const elemType& item)
{
    int first = 0;
    int last = length - 1;
    int mid;
    
    bool found = false;
    
    // Keep dividing the search space in half until we find the item or space is exhausted
    while (first <= last && !found)
    {
        comparisonCount++;  // Count each comparison
        mid = (first + last) / 2;
        
        // Check if we found it at the midpoint
        if (list[mid] == item)
            found = true;
        // If item is larger, search the right half
        else if (list[mid] > item)
            last = mid - 1;
        // If item is smaller, search the left half
        else
            first = mid + 1;
    }
    
    // Return the index if found, otherwise return -1
    if (found)
        return mid;
    else
        return -1;
} // end binarySearch

// Function to display the menu interface
void displayMenu(unsigned long long currentTarget, long long seqComparisons, long long binComparisons)
{
    cout << "\n";
    cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
    cout << "*                 Search Algorithm Comparison               *\n";
    cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
    cout << "\n";
    cout << "CURRENT TARGET: ~" << currentTarget << "\n";
    cout << "\n";
    cout << "Search Metrics\n";
    cout << "* Sequential: Target:~" << currentTarget << " iterations: " << seqComparisons << " comparisons\n";
    cout << "* Binary: Target:~" << currentTarget << " iterations: " << binComparisons << " comparisons\n";
    cout << "\n";
    cout << "* <1> Enter long long integer to search\n";
    cout << "* <2> Perform Sequential (Linear) search\n";
    cout << "* <3> Perform Binary search\n";
    cout << "* <4> Quit\n";
    cout << "\n";
    cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
    cout << "* Choose from the menu:\n";
}

int main()
{
    // Read the data file into a vector
    ifstream inputFile("data/1000000.dat", ios::binary);
    
    // Ensure the file opens successfully
    if (!inputFile)
    {
        cerr << "Error: Could not open the file 'data/1000000.dat'" << endl;
        return 1;
    }
    
    // Load all data from the binary file into our vector
    vector<unsigned long long> dataArray;
    unsigned long long value;
    while (inputFile.read(reinterpret_cast<char*>(&value), sizeof(unsigned long long)))
    {
        dataArray.push_back(value);
    }
    inputFile.close();
    
    // Verify that we loaded the correct amount of data
    cout << "Successfully loaded " << dataArray.size() << " integers from the data file.\n";
    
    // Variables to track search results and metrics
    unsigned long long searchTarget = 0;
    long long seqResult = -1;
    long long binResult = -1;
    long long seqComparisons = 0;
    long long binComparisons = 0;
    
    int menuChoice = 0;
    
    // Main menu loop - keep running until user quits
    do
    {
        // Display the current menu with metrics
        displayMenu(searchTarget, seqComparisons, binComparisons);
        
        // Get the user's choice
        cin >> menuChoice;
        
        // Handle invalid input
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nInvalid input. Please enter a number between 1 and 4.\n";
            continue;
        }
        
        // Process the user's choice
        switch (menuChoice)
        {
            case 1:
                // Option 1: Get a new search target from the user
                cout << "\nEnter the integer to search for: ";
                cin >> searchTarget;
                
                // Reset comparison counters for new search
                seqComparisons = 0;
                binComparisons = 0;
                seqResult = -1;
                binResult = -1;
                break;
                
            case 2:
                // Option 2: Perform sequential search and count comparisons
                comparisonCount = 0;
                seqResult = seqSearch(&dataArray[0], dataArray.size(), searchTarget);
                seqComparisons = comparisonCount;
                
                // Display the result of the sequential search
                cout << "\nSequential Search Result:\n";
                if (seqResult != -1)
                    cout << "  Found at index: " << seqResult << "\n";
                else
                    cout << "  Item not found in the array.\n";
                cout << "  Total comparisons: " << seqComparisons << "\n";
                break;
                
            case 3:
                // Option 3: Perform binary search and count comparisons
                comparisonCount = 0;
                binResult = binarySearch(&dataArray[0], dataArray.size(), searchTarget);
                binComparisons = comparisonCount;
                
                // Display the result of the binary search
                cout << "\nBinary Search Result:\n";
                if (binResult != -1)
                    cout << "  Found at index: " << binResult << "\n";
                else
                    cout << "  Item not found in the array.\n";
                cout << "  Total comparisons: " << binComparisons << "\n";
                break;
                
            case 4:
                // Option 4: Exit the program gracefully
                cout << "\nThank you for using the Search Algorithm Comparison tool!\n";
                break;
                
            default:
                // Handle invalid menu selections
                cout << "\nInvalid choice. Please select an option between 1 and 4.\n";
        }
        
    } while (menuChoice != 4);
    
    return 0;
}
