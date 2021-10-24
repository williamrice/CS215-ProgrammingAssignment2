/***********************************************
 * Created by William Rice
 * CS215U-19Z1
 * Fall 2021
 * Programming Assignment 2
 * 
 * Description: This program will allow the user
 * to input a series of whole number values to 
 * be stored in a list or it will randomly generate
 * a list for them based on user specifications/
 * list limitations. The program will then allow 
 * users to perform different search/sort operations 
 * on the list.
 * 
 * Program Preconditions: The user must follow all 
 * limitations of the list such as the Maximum List
 * Size, represented as MLS of type int, which is 
 * currently set to 50 elements for this assignment.
 * If the user chooses to reset/input a list manually,
 * the user must be aware that they must enter -1 at 
 * the end to signal to the program that they are done
 * inputting values. The list must be in order prior to 
 * doing a binary search. 
 * 
 * Program Postconditions: If a user chooses to sort
 * the list, we must guarantee that we track the list
 * is in order with isKnownOrdered boolean value being
 * updated after a successful sort. The program must also
 * guarantee that if the user searches for a value using
 * one of the search methods, the program returns accurate
 * results and stats. If the user elects to generate a 
 * random list, we must guarantee that the values are 
 * 1.)random based on seeding with the current time,
 * 2.)the amount of elements generated is accurate to
 * what the user entered as the size
 * 3.)the values generated are within the lower and 
 * upper bounds entered by the user.  
 * 
************************************************/


/***********************************************
 * Include area for external headers
************************************************/
#include <iostream>
#include <cstring>
#include <iomanip>
#include <cmath>
#include <math.h>

/***********************************************
 * Using namespace area
************************************************/
using namespace std;

/***********************************************
 * Global constants and typedefs
************************************************/
const int MLS = 50;
typedef int element;
const element SENTINAL = -1;

/***********************************************
 * Function prototype area
************************************************/
element read_element();
void print_option_list();
void print_program_header();
void reset_list_from_keyboard();
void reset_list_with_random_gen();
void perform_insertion_sort();
void perform_linear_search();
void perform_binary_search();

/***********************************************
 * Class prototype for AList class
************************************************/
class AList{
    private: 
        element items[MLS];
        bool isKnownOrdered = true;
        int size;
        void Swap(int pos1, int pos2);
        void ResetList();

    public:
        void Read();
        void Print();
        int GetSize();
        bool IsKnownOrdered();
        void BubbleSort();
        void InsertionSort(int & comparisons, int & movements);
        void SelectionSort();
        void LinearSearch(element target, bool & found, int & position);
        void BinarySearch(element target, bool & found, int & position,
                int & comparisons);
        void GenerateRandomList(int size, int low_bound, int high_bound);
};

AList aList; //global aList object to be used during the program

/***********************************************
 * Main function: Entry point of the application.
 * Includes a main loop that will run infinitely
 * until the user chooses to the action to exit. 
************************************************/
int main(){
    print_program_header();
    while(true){
        cout << endl; //Always have atleast 1 space no matter what above list
        aList.Print();

        print_option_list();

        int action; // the users action

        cout << "Choose an action: " << endl;
        cin >> action;
        
        switch (action)
        {
            case 1:
                reset_list_from_keyboard();
                break;
            case 2:
                reset_list_with_random_gen();
                break;
            case 3:
                aList.BubbleSort();
                break;
            case 4:
                perform_insertion_sort();
                break;
            case 5:
                aList.SelectionSort();
                break;
            case 6:
                perform_linear_search();
                break;
            case 7:
                perform_binary_search();
                break;
            case 8:
                exit(0);
                break;
            default:
                cout << "Error, you must choose a valid option from the " << 
                        "list" << endl;
                break;
        }
    }
}

/***********************************************
 * This section contains functions that modularize
 * our program 
************************************************/

element read_element(){
    //PRE: the user must enter a series of zero or more non-valid
    //     element values, followed by a valid element value

    //POST: all entered non-valid element values will be successfully 
    //      discarded, and the first valid element value entered will
    //      be returned

    element userval;

    cin >> boolalpha >> userval;
    while(! cin.good()){
        cin.clear();
        cin.ignore(80, '\n');
        cout << "Invalid data type, should be an element, "
            << "try again: ";
        cin >> boolalpha >> userval;
    }
    return userval;
}

void print_option_list(){
    //PRE: none

    //POST: Outputs the list of options

    cout << "Actions:" << endl;
    cout << "\t1. Reset the current list from the keyboard" << endl;
    cout << "\t2. Reset the current list using randomly generated" <<
            " elements" << endl;
    cout << "\t3. Perform Bubble Sort on the current list" << endl;
    cout << "\t4. Perform Insertion Sort on the current list" << endl;
    cout << "\t5. Perform Selection Sort on the current list" << endl;
    cout << "\t6. Perform Linear Search on the current list" << endl;
    cout << "\t7. Perform Binary Search on the current list" << endl;
    cout << "\t8. Quit the program" << endl;
}

void print_program_header(){

    //PRE: none

    //POST: Prints the program header

    cout << "Sort and Search Demo Program, version 1.0" << endl;
    cout << "(c) 2021, William Rice" << endl;
}

void reset_list_from_keyboard(){
    //PRE: none

    //POST: Calls the Read method from the AList class
    //      to allow the user to reset the list
    cout << "\nResetting the current list from the " << 
            "keyboard.\n" << endl;

    aList.Read();

    cout << "\nFinsihed resetting, " << aList.GetSize() << 
            " elements entered." << endl;
}

void reset_list_with_random_gen(){
    //PRE: the number of elements inputted by the user must be
    //      greater than 0 and less than MLS

    //POST: a valid AList is generated via the Alist method 
    //      GenerateRandomList. A confirmation is outputted 
    //      to the console telling the user that they 
    //      successfully generated a list with the parameters
    //      they provided

    int num_of_elements;
    int low_bound;
    int high_bound;

    cout << "\nResetting the current list using randomly generated " <<
    "elements" << endl;
    

    cout << "\nHow many elements (1-50): ";
    cin >> num_of_elements;
    while(! cin.good() || (num_of_elements < 0 ||num_of_elements > MLS)){
        cin.clear();
        cin.ignore(80, '\n');
        if(num_of_elements < 0 ||num_of_elements > MLS)
            cout << "Response must be between 0 and" << MLS <<
            " , try again: ";
        else
            cout << "Response must be a whole number, "
                << "try again: ";
        cin >> num_of_elements;
    }
    


    cout << "\nEnter the lower limit of the range: ";
    cin >> low_bound;

    // Since we are doing our input validation after both ranges
    // are inputted, this will temporarily ignore bad type input
    // from the low bound and allow the user to go ahead and 
    // enter the upper bound. The validation loop will catch the 
    // error. 
    if(! cin.good()){
        cin.clear();
        cin.ignore(80, '\n');
    }

    cout << "Enter the upper limit of the range: ";
    cin >> high_bound;

    while(! cin.good() || (low_bound > high_bound)){
        //Clearn the cin buffer
        cin.clear();
        cin.ignore(80, '\n');

        if(low_bound > high_bound)
            cout << "Error. The low range can't be larger " << 
                    "than the high range. Let's try that again..." <<
                    endl;
        else
            cout << "Error. Both ranges must be a whole number. " <<
            "Let's try that again..." << endl;

        cout << "\nEnter the lower limit of the range: ";
        cin >> low_bound;

        if(! cin.good()){
        cin.clear();
        cin.ignore(80, '\n');
        }

        cout << "Enter the upper limit of the range: ";
        cin >> high_bound;
    }
    
    aList.GenerateRandomList(num_of_elements, low_bound, high_bound);

    cout << "\nFinished resetting, " << num_of_elements << " between " <<
            low_bound << " and " << high_bound << 
            " randomly generated.\n" << endl;
}

void perform_insertion_sort(){
    //PRE: none
    //POST: uses the AList method of InsertionSort to sort the list. 
    //      stats of the search including comparisons and movements
    //      for theoretical and actual data

    //used to track comparisons and movements for stats
    int comparisons;
    int movements;

    cout << "\nPerforming Insertion Sort on the current list" << endl;

    aList.InsertionSort(comparisons, movements);

    cout << setw(45) << left << "\nTheoretical sort statistics:";
    cout << (int)(pow(aList.GetSize(), 2.0) / 2) << 
            " element comparisons, " <<
            (int)(3 * ((pow(aList.GetSize(), 2.0) / 2))) <<
            " element movements" 
        << endl;
    

    cout << setw(45) << left << "Actual sort statistics:";
    cout << comparisons << " element comparisons, " <<
            movements << " element movements" 
        << endl;
}

void perform_linear_search(){
    //PRE: none

    //POST: the result of the search is outputted to the screen 
    //      and if found, the user is informed that the target 
    //      was found and the position. If the target is not
    //      found, the user if informed that it was not found. 
    //      Stats are outputted to the user by the number of
    //      theoretical and actual elements that were searched

    element target;
    bool found;
    int position;

    cout << "\nPerforming Linear Search on the current list" << endl;
    cout << "\nEnter a target element to search for: ";
    target = read_element();

    aList.LinearSearch(target, found, position);

    if(found)
        cout << "\nThe target was FOUND on the current list in " << 
                "position " << position << "." << endl;
    else
        cout << "\nThe target was NOT FOUND on the current list";

    cout << setw(45) << left << "\nTheoretical search statistics:";
    cout << aList.GetSize() << " element comparisons" << endl;
    

    cout << setw(45) << left << "Actual search statistics:";
    cout << (position + 1) << " element comparisons" << endl;
    
}

void perform_binary_search(){

    //PRE: none

    //POST: the result of the search is outputted to the screen 
    //      and if found, the user is informed that the target 
    //      was found and the position. If the target is not
    //      found, the user if informed that it was not found. 
    //      Stats are outputted to the user by the number of
    //      theoretical and actual elements that were searched

    element target;
    bool found;
    int position;
    int comparisons;

    if(! aList.IsKnownOrdered()){
        cout << "Sorry, since the current list is not known " <<
                "to be ordered, the Binary Search cannot be " <<
                "performed at this time. Please sort the " <<
                "current list first." << endl;
        return;
    }
    else{
        cout << "Performing Binary Search\n" << endl;
    }

    cout << "\nEnter a target element to search for: ";
    target = read_element();

    aList.BinarySearch(target, found, position, comparisons);

    if(found)
        cout << "\nThe target was FOUND on the current list in " << 
                "position " << position << " ." << endl;
    else
        cout << "\nThe target was NOT FOUND on the current list";

    cout << setw(45) << left << "\nTheoretical search statistics:";
    cout << (int)ceil(log2(aList.GetSize())) << 
            " element comparisons" << endl;
    

    cout << setw(45) << left << "Actual search statistics:";
    cout << comparisons << " element comparisons" << endl;


}


/***********************************************
 * This section contains all the implementation
 * for the AList class. 
************************************************/
void AList::ResetList(){

    //PRE: The N.O list contains atleast 1 element

    //POST: The N.O list elements are all set to the 
    //      value of zero. isKnownOrdered is set back
    //      to the default state of true. Size is set
    //      back to 0
    if(size > 0){
        memset(items, 0, size);
        isKnownOrdered = true;
        size = 0;
    }
        
}

int AList::GetSize(){

    //PRE: none

    //POST: The value from the size attribute is returned

    return size;
}

bool AList::IsKnownOrdered(){

    //PRE: none

    //POST: The value from the isKnownOrdered attribute
    //      is returned

    return isKnownOrdered;
}

void AList::Read(){
    //PRE: none

    //POST: the Native Object (N.O) AList is now valid, holding elements 
    //      provided by the user

    element userval;

    //We want to reset the list and set the size to 0 before allowing
    //entry of new elements
    if(size > 0)
        ResetList();

    size = 0;

    cout << "Enter elements, " << SENTINAL << " to stop: ";
    userval = read_element();
    while ((userval != SENTINAL) && (size < MLS))
    {
        items[size] = userval;
        size++;
        if(size < MLS)
            userval = read_element();
        else
            cout << "List is now full, ending input" << endl;
    }
    isKnownOrdered = false;
    
}

void AList::Print(){
    //PRE: the N.O. AList is valid

    //POST: the N.O Alist is unchanged, and its elements have been displayed
    //      to the user if they exist. If no elements are present, the list
    //      is assumed empty and (empty) is outputted. We also check to see
    //      if the list is known to be in order and display the status after
    //      the list is displayed 

    if(size == 0)
        cout << "(empty) ";
    else{
        for(int i = 0; i < size; i++){
            cout << items[i] << " ";
        }
    }

    //Ternary operator displays if the list is in order or not
    string orderedMessage = isKnownOrdered ? "KNOWN" : "NOT KNOWN";
    cout << "(" << orderedMessage << " to be ordered)\n" << endl;
    
}

void AList::GenerateRandomList(int num_of_elements, int low_bound, 
                            int high_bound){
    //PRE: The N.O AList is reset to an empty or new list. The
    //     num_of_elements can't be more than the MLS

    //POST: A new list is generate based on the size given by the parameter
    //      and the list values that are between the low_bound and high_bound

    srand(time(0)); //seed random object with current time

    if(num_of_elements > MLS){
        cout << "Invalid! The list can only hold " << MLS << 
        " elements." << endl;
        return;
    }

    // We want to reset the list and all values before generating
    // a new list
    if(size > 0)
        ResetList();

    size = 0;

    for(int i = 0; i < num_of_elements; i++){
        items[i] = (rand() % (high_bound - low_bound + 1)) + low_bound;
        size++;
    }

    isKnownOrdered = false;

}

void AList::Swap(int pos1, int pos2){

    //PRE:  the N.O. AList is valid
    //      0 <= pos1 < size
    //      0 <- pos2 < size

    //POST: the N.O. AList is unchanged, except that the two elements
    //      previously in positions pos1 and pos2 have been swapped

    element temp;

    temp = items[pos1];
    items[pos1] = items[pos2];
    items[pos2] = temp;
}

void AList::BubbleSort(){
    //PRE: the N.O. AList is valid

    //POST: the N.O. Alist is unchanged, except that
    //      its elements are now in ascending order

    for(int i = 0; i < size - 1; i++){
        for(int j = 0; j < size - 1 - i; j++){
            if(items[j] > items[j + 1])
                Swap(j, j + 1);
            else
                ;
        }
    }
    isKnownOrdered = true;
}

void AList::InsertionSort(int & comparisons, int & movements){
    //PRE: the N.O. AList is valid

    //POST: the N.O. AList is unchaged, except that 
    //      its elements are now in ascending order

    int j;
    bool done;

    comparisons = 0;
    movements = 0;

    for(int i = 1; i < size; i++){
        j = i;
        done = false;
        if(i != size - 1)
            comparisons++;
        while((j >=1) && (! done)){
            comparisons++;
            if(items[j] < items[j - 1]){
                Swap(j, j - 1);
                j -= 1;
                movements += (3 * (i - 1));
            }
            else    
                done = true;
        }
            
    }
    isKnownOrdered = true;
}

void AList::SelectionSort(){
    //PRE: the N.O. AList is valid

    //POST: the N.O. AList is unchanged, except that its
    //      its elements are now in ascending order

    int maxpos;

    for(int i = size - 1; i > 0; i--){
        maxpos = 0;
        for(int j = 1; j <= i; j++){
            if(items[j] > items[maxpos])
                maxpos = j;
            else    
                ;
        }
        Swap(maxpos, i);
    }
    isKnownOrdered = true;
}

void AList::LinearSearch(element target, bool & found, 
    int & position){
        //PRE: The N.O AList is valid

        //POST: the N.O. AList is unchaged, and 
        //      if the target exists on the N.O AList:
        //          found will be true, and position will be
        //          a location of the target on the N.O. AList
        //      otherwise
        //          found will be false, and position will
        //          be undefined

        found = false;

        position = 0;

        while((! found) && (position < size))
            if(target == items[position])
                found = true;
            else
                position++;
}

void AList::BinarySearch(element target, bool & found,
    int & position, int & comparisons){
    //PRE: The N.O AList is valid, and the elements
    //      are in ascending order

    //POST: the N.O. AList is unchanged, and 
    //      if the target exists on the N.O AList:
    //          found will be true, and position will be
    //          a location of the target on the N.O. AList
    //      otherwise
    //          found will be false, and position will
    //          be undefined
    //      each time the loop runs, the comparisons are
    //      incremented at the beginning of the loop 
    //      because there will always be atleast 1 comparison.



    int low;
    int high;
    int mid;

    low = 0;
    high = size - 1;
    found = false;
    comparisons = 0;

    while((! found) && (low <= high)){
        mid = (low + high) / 2;
        comparisons++;
        if (target == items[mid])
        {
            found = true;
            position = mid;
        }
        else if(target < items[mid]){
            high = mid - 1;
        }
        else{
            low = mid + 1;
        }
    }            
}