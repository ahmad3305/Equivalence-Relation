#include <iostream>
using namespace std;

const int MAX_SIZE = 100; // Maximum size for elements and relations

// Function prototypes
bool isReflexive(char elements[], int totalNums, char relation[][2], int pairCount);
bool isSymmetric(char relation[][2], int pairCount);
bool isTransitive(char relation[][2], int pairCount);
int parseInput(char input[], char relation[][2]);

int main() {
    int totalNums; // Number of elements in the set
    cout << "Enter the number of elements in the set: ";
    cin >> totalNums;

    char elements[MAX_SIZE]; // Array to store set elements
    cout << "Enter the elements of the set (e.g., A B C or 1 2 3):\n";
    for (int i = 0; i < totalNums; i++) 
    {
        cin >> elements[i]; // Input elements of the set
    }

    cin.ignore(); // Clear the input buffer

    char input[MAX_SIZE * 10]; // Input string for ordered pairs
    cout << "Enter the ordered pairs as a single line (e.g., 'A A, B B, C C' or '1 1, 2 2'):\n";
    cin.getline(input, sizeof(input)); // Get the relation input as a single line

    char relation[MAX_SIZE][2]; // 2D array to store pairs of the relation
    int pairCount = parseInput(input, relation); // Parse input string into relation pairs

    // Check the properties of the relation
    bool reflexive = isReflexive(elements, totalNums, relation, pairCount);
    bool symmetric = isSymmetric(relation, pairCount);
    bool transitive = isTransitive(relation, pairCount);

    // Determine if the relation is an equivalence relation
    if (reflexive && symmetric && transitive)
    {
        cout << "The relation is an equivalence relation.\n";
    }
    else 
    {
        cout << "The relation is not an equivalence relation.\n";
    }

    // Report the missing properties
    if (!reflexive) 
    {
        cout << "The relation is not reflexive.\n";
    }
    if (!symmetric)
    {
        cout << "The relation is not symmetric.\n";
    }
    if (!transitive) 
    {
        cout << "The relation is not transitive.\n";
    }

    return 0;
}

// Function to check reflexivity
bool isReflexive(char elements[], int totalNums, char relation[][2], int pairCount) 
{
    // Check if every element is related to itself
    for (int i = 0; i < totalNums; i++) 
    {
        bool found = false; // Flag to indicate if reflexivity holds for this element
        for (int j = 0; j < pairCount; j++) 
        {
            if (relation[j][0] == elements[i] && relation[j][1] == elements[i])
            {
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Reflexivity fails due to element: " << elements[i] << endl;
            return false; // Reflexivity fails
        }
    }
    return true; // Reflexivity holds
}

// Function to check symmetry
bool isSymmetric(char relation[][2], int pairCount) 
{
    // Check if for every pair (a, b), the pair (b, a) exists
    for (int i = 0; i < pairCount; i++) 
    {
        bool found = false; // Flag to indicate if symmetry holds for this pair
        for (int j = 0; j < pairCount; j++) 
        {
            if (relation[i][0] == relation[j][1] && relation[i][1] == relation[j][0]) 
            {
                found = true;
                break;
            }
        }
        if (!found) 
        {
            cout << "Symmetry fails due to: (" << relation[i][0] << ", " << relation[i][1] << ")\n";
            return false; // Symmetry fails
        }
    }
    return true; // Symmetry holds
}

// Function to check transitivity
bool isTransitive(char relation[][2], int pairCount) 
{
    // Check if for every (a, b) and (b, c), the pair (a, c) exists
    for (int i = 0; i < pairCount; i++) 
    {
        for (int j = 0; j < pairCount; j++) 
        {
            if (relation[i][1] == relation[j][0]) 
            { // Found (a, b) and (b, c)
                bool found = false; // Flag to indicate if (a, c) exists
                for (int k = 0; k < pairCount; k++) 
                {
                    if (relation[k][0] == relation[i][0] && relation[k][1] == relation[j][1]) 
                    {
                        found = true;
                        break;
                    }
                }
                if (!found) 
                {
                    cout << "Transitivity fails due to: (" << relation[i][0] << ", " << relation[i][1]
                        << ") and (" << relation[j][0] << ", " << relation[j][1] << ")\n";
                    return false; // Transitivity fails
                }
            }
        }
    }
    return true; // Transitivity holds
}

// Function to parse input string into pairs
int parseInput(char input[], char relation[][2])
{
    int pairCount = 0; // Counter for number of pairs
    bool readingFirst = true; // Flag to track if we are reading the first or second element of a pair

    for (int i = 0; input[i] != '\0'; i++) 
    {
        // Check if character is alphanumeric
        if ((input[i] >= 'A' && input[i] <= 'Z') ||
            (input[i] >= 'a' && input[i] <= 'z') ||
            (input[i] >= '0' && input[i] <= '9')) 
        {
            if (readingFirst) 
            {
                relation[pairCount][0] = input[i]; // Store first element of the pair
            }
            else
            {
                relation[pairCount][1] = input[i]; // Store second element of the pair
                pairCount++; // Move to the next pair
            }
            readingFirst = !readingFirst; // Toggle between first and second elements
        }
    }

    return pairCount; // Return the total number of pairs
}
