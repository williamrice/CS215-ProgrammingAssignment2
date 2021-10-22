#include <iostream>

using namespace std;

const int MLS = 50;
typedef int element;
const element SENTINAL = -1;

element read_element();

class AList{
    private: 
        element items[MLS];
        int size;
        void Swap(int pos1, int pos2);

    public:
        void Read();
        void Print();
        void BubbleSort();
        void InsertionSort();
        void SelectionSort();
        void LinearSearch(element target, bool & found, int & position);
        void BinarySearch(element target, bool & found, int & position);
};

int main(){
    AList aList;
    aList.Read();
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

void AList::Read(){
    //PRE: none

    //POST: the Native Object (N.O) AList is now valid, holding elements 
    //      provided by the user

    element userval;

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
    
}