#include <iostream>
#include <cstring>

using namespace std;

const int MLS = 50;
typedef int element;
const element SENTINAL = -1;


element read_element();
void print_option_list();
void print_program_header();
void reset_list_from_keyboard();
void reset_list_with_random_gen();
void perform_linear_search();
void perform_binary_search();

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
        void BubbleSort();
        void InsertionSort();
        void SelectionSort();
        void LinearSearch(element target, bool & found, int & position);
        void BinarySearch(element target, bool & found, int & position);
        void GenerateRandomList(int size, int low_bound, int high_bound);
};


AList aList;
int main(){
    print_program_header();
    while(true){
        aList.Print();

        print_option_list();

        int action;

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
                aList.InsertionSort();
                break;
            case 5:
                aList.SelectionSort();
                break;
            case 6:
                //perform_linear_search();
                break;
            case 7:
                //perform_binary_search();
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

element read_element(){
    //PRE: the user must enter a series of zero or more non-valid
    //     element values, followed by a valid element value

    //POST: all enetered non-valid element values will be successfully 
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
    cout << "Sort and Search Demo Program, version 1.0" << endl;
    cout << "(c) 2021, William Rice\n\n" << endl;
}

void reset_list_from_keyboard(){
    aList.Read();
}

void reset_list_with_random_gen(){
    int num_of_elements;
    int low_bound;
    int high_bound;

    cout << "How many elements (1-50): ";
    cin >> num_of_elements;
    cout << "What is the minimum value to generate: ";
    cin >> low_bound;
    cout << "What is the maximum value to generate: ";
    cin >> high_bound;
    aList.GenerateRandomList(num_of_elements, low_bound, high_bound);
}

void AList::ResetList(){
    if(size > 0){
        memset(items, 0, size);
        isKnownOrdered = true;
    }
        
}

void AList::Read(){
    //PRE: none

    //POST: the Native Object (N.O) AList is now valid, holding elements 
    //      provided by the user

    element userval;

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

    string orderedMessage = isKnownOrdered ? "KNOWN" : "NOT KNOWN";
    cout << "(" << orderedMessage << " to be ordered)\n" << endl;
    
}

void AList::GenerateRandomList(int num_of_elements, int low_bound, 
                            int high_bound){
    //PRE: The N.O AList is reset to an empty or new list. The
    //     num_of_elements can't be more than the MLS

    //POST: A new list is generate based on the size given by the parameter
    //      and the list values that are between the low_bound and high_bound

    srand(time(0));

    if(num_of_elements > MLS){
        cout << "Invalid! The list can only hold " << MLS << 
        " elements." << endl;
        return;
    }

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

void AList::InsertionSort(){
    //PRE: the N.O. AList is valid

    //POST: the N.O. AList is unchaged, except that 
    //      its elements are now in ascending order

    int j;
    bool done;

    for(int i = 1; i < size; i++){
        j = i;
        done = false;
        while((j >=1) && (! done))
            if(items[j] < items[j - 1]){
                Swap(j, j - 1);
                j -= 1;
            }
            else    
                done = true;
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