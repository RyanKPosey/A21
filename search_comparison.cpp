#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cstring>

using namespace std;

// Note: we count iterations locally inside each search function and
// return the iteration count via a reference parameter. This avoids
// using a global counter and makes the metrics explicit.

// Sequential (Linear) search template that counts comparisons
template <class elemType>
int seqSearch(const elemType list[], long long length, const elemType& item, long long &iterations)
{
    long long loc = 0;
    bool found = false;
    iterations = 0;

    // Linear scan through the list until we find the item or reach the end
    while (loc < length && !found)
    {
        iterations++;            // Count this loop iteration
        if (list[loc] == item)
            found = true;
        else
            loc++;
    }

    // Return the index if found, otherwise return -1
    return found ? (int)loc : -1;
} // end seqSearch

// Binary search template that counts comparisons
template <class elemType>
int binarySearch(const elemType list[], long long length, const elemType& item, long long &iterations)
{
    long long first = 0;
    long long last = length - 1;
    long long mid;
    iterations = 0;

    bool found = false;

    // Keep dividing the search space in half until we find the item or space is exhausted
    while (first <= last && !found)
    {
        iterations++;          // Count this loop iteration
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

    return found ? (int)mid : -1;
} // end binarySearch

// Function to display the menu interface
void displayMenu(unsigned long long currentTarget, long long seqComparisons, long long binComparisons,
                 long long seqIterations, long long binIterations)
{
    cout << "\n";
    cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
    cout << "*                 Search Algorithm Comparison               *\n";
    cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
    cout << "\n";
    cout << "CURRENT TARGET: ~" << currentTarget << "\n";
    cout << "\n";
    cout << "Search Metrics\n";
    cout << "* Sequential: Target:~" << currentTarget << " iterations: " << seqIterations << " comparisons: " << seqComparisons << "\n";
    cout << "* Binary:     Target:~" << currentTarget << " iterations: " << binIterations << " comparisons: " << binComparisons << "\n";
    cout << "\n";
    cout << "* <1> Enter long long integer to search\n";
    cout << "* <2> Perform Sequential (Linear) search\n";
    cout << "* <3> Perform Binary search\n";
    cout << "* <4> Quit\n";
    cout << "\n";
    cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
    cout << "* Choose from the menu (1-4): ";
    cout.flush();  // Ensure the prompt is displayed immediately
}

int main()
{
    // Available data files for the user to choose from
    vector<string> dataFiles = {
        "data/10.dat",
        "data/100.dat",
        "data/1000.dat",
        "data/10000.dat",
        "data/100000.dat",
        "data/1000000.dat"
    };
    
    // Display file selection menu
    cout << "\n=== Select Data File to Search ===" << endl;
    for (size_t i = 0; i < dataFiles.size(); i++)
    {
        cout << "<" << (i + 1) << "> " << dataFiles[i] << endl;
    }
    cout << "\nEnter your choice (1-" << dataFiles.size() << "): ";
    
    int fileChoice;
    cin >> fileChoice;
    
    // Validate user's file selection
    if (fileChoice < 1 || fileChoice > (int)dataFiles.size())
    {
        cerr << "Error: Invalid selection. Please enter a number between 1 and " << dataFiles.size() << endl;
        return 1;
    }
    
    // Get the selected filename
    string selectedFile = dataFiles[fileChoice - 1];
    
    // Read the selected data file into a vector
    ifstream inputFile(selectedFile);
    
    // Ensure the file opens successfully
    if (!inputFile)
    {
        cerr << "Error: Could not open the file '" << selectedFile << "'" << endl;
        return 1;
    }
    
    // Load all data from the text file into our vector
    vector<unsigned long long> dataArray;
    unsigned long long value;
    while (inputFile >> value)
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
    long long seqComparisons = 0; // comparisons counted (equal to iterations for these simple searches)
    long long binComparisons = 0;
    long long seqIterations = 0;  // explicit iteration counts
    long long binIterations = 0;
    bool targetSet = false; // track whether user has entered a search target (allows 0 as valid)
    
    int menuChoice = 0;
    
    // Main menu loop - keep running until user quits
    do
    {
        // Display the current menu with metrics
        displayMenu(searchTarget, seqComparisons, binComparisons, seqIterations, binIterations);
        
        // Get the user's choice
        cin >> menuChoice;
        
        // Handle invalid input
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\n[ERROR] Invalid input. Please enter a number between 1 and 4.\n";
            continue;
        }
        
        // Process the user's choice
        switch (menuChoice)
        {
            case 1:
                // Option 1: Get a new search target from the user
                cout << "Enter the integer to search for: ";
                cin >> searchTarget;
                
                // Handle invalid input for search target
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "[ERROR] Invalid input. Please enter a valid integer.\n";
                    searchTarget = 0;
                    break;
                }
                
                // Set flag to indicate a valid search target was entered (0 is allowed)
                targetSet = true;

                // Reset comparison counters and iteration counters for new search
                seqComparisons = 0;
                binComparisons = 0;
                seqIterations = 0;
                binIterations = 0;
                seqResult = -1;
                binResult = -1;
                cout << "Search target set to: " << searchTarget << "\n";
                break;
                
            case 2:
                // Option 2: Perform sequential search and count comparisons
                if (!targetSet)
                {
                    cout << "\n[WARNING] Please enter a search target first (option 1).\n";
                    break;
                }
                
                seqIterations = 0;
                seqResult = seqSearch(&dataArray[0], (long long)dataArray.size(), searchTarget, seqIterations);
                seqComparisons = seqIterations; // for this simple search comparisons == iterations
                
                // Display the result of the sequential search
                cout << "\n=== Sequential Search Result ===\n";
                if (seqResult != -1)
                    cout << "  ✓ Found at index: " << seqResult << "\n";
                else
                    cout << "  ✗ Item not found in the array.\n";
                cout << "  Total comparisons: " << seqComparisons << "\n";
                break;
                
            case 3:
                // Option 3: Perform binary search and count comparisons
                if (!targetSet)
                {
                    cout << "\n[WARNING] Please enter a search target first (option 1).\n";
                    break;
                }
                
                binIterations = 0;
                binResult = binarySearch(&dataArray[0], (long long)dataArray.size(), searchTarget, binIterations);
                binComparisons = binIterations; // comparisons == iterations here as well
                
                // Display the result of the binary search
                cout << "\n=== Binary Search Result ===\n";
                if (binResult != -1)
                    cout << "  ✓ Found at index: " << binResult << "\n";
                else
                    cout << "  ✗ Item not found in the array.\n";
                cout << "  Total comparisons: " << binComparisons << "\n";
                break;
                
            case 4:
                // Option 4: Exit the program gracefully
                cout << "\nThank you for using the Search Algorithm Comparison tool!\n";
                break;
                
            default:
                // Handle invalid menu selections
                cout << "\n[ERROR] Invalid choice '" << menuChoice << "'. Please select an option between 1 and 4.\n";
        }
        
    } while (menuChoice != 4);
    
    return 0;
}