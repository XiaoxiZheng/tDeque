
#include <stdio.h>
#include<string>
#include<iostream>
#include<sstream>
#include<stdexcept>

using namespace std;

/*
class notEnough: public exception{
    virtual const char* what() const throw()
    {
        return "You cannot remove an element because the queue is already empty.";
    }
} notEnough;
*/
template <class T>
class Deque {
private:
    T *queue, remove;
//    string *queue, remove;

    int num_elements, size_of_queue, head, tail,previousHead,previousTail,minSize;// dont think I need a "start" variable;

public:

Deque(){//default constructor
    queue = new T[9];//the array with the minimal (8) element but with actually 9 containers(including 0)since I decided to use index0 as an "imaginary" pointer position for head;
    size_of_queue = 8;//The capacity of the queue by default is 8
    minSize = 8;//I used this variable to make sure the array doesn't shrink below this number
    num_elements = 0;//The # of elements in the array initially is 0
    head = 0; // head is 0 (never utilized)
    tail = size_of_queue+1; //an imaginary indexing that represents the end of an array(not utilized, and can't be utilized);
    previousHead=0;
    previousTail=0;
}

~Deque(){
    delete [] queue;
} //Destructor

void grow(int initiSize,  T temp[]){//called when the "old array" is fulled. //passed in the original size of array, and the array itself.
    try{
        //int size = 2*initiSize;
        queue = new T[initiSize+1];
   // cout<<"initialized new array with x2 the space"<<endl;


        int i = tail;    //this method and while loop basically copied everything from previous array starting from it's original tail(as the first element of the new array), and ends
        int j=1;         //when all the elements from the old array are copied, meaning it ends at the original head.
                     // Reorganized the elements in the array so when pop from head or tail that it would be equivalent in old array.
        while(j<=num_elements){
            if(i==(size_of_queue+1)){
                i = 1;
            }
            queue[j]=temp[i];
            j++;
            i++;
        }
    }
    catch(exception& e){
        //cerr<<"FATAL ERROR!Out of memory"<<endl;
        throw out_of_range("Out of Memory!!!");
    }
}




void shrink(int initiSize,  T temp[]){ //called when the array is only 1/4 full, and shrinks the size of array to 1/2 of previous
    try{
        //cout<<"shrink the array to 1/2 of previous size(because of the # of elements presented)"<<endl;
        queue = new T[initiSize+1];

        int i = tail;
        int j=1;

        while(j<=num_elements){  // Reorganized the elements in the array so when pop from head or tail that it would be equivalent in old array.
            if(i==(size_of_queue+1)){  //refer to grow method for more explanation
                i = 1;
            }
            queue[j]=temp[i];
            j++;
            i++;
        }
    }
    catch(...){
        //cerr<<"out of memory!"<<endl;
        throw out_of_range("OUT OF MEMORY!!!");
    }
}


void push_front(T element){
    if(num_elements==size_of_queue){ //if the num of elements in the array reaches the current capacity, then call this and grow.
        num_elements++;
       // cout<<"realizes its full"<<endl;//if that happens the current array is fulled...need to resize
        grow(size_of_queue*2, queue);//calls grow helper method, which x2 the size of array.
       // cout<<"successfully called grow"<<endl;
        size_of_queue=size_of_queue*2; //new size of queue is doubled
        head = size_of_queue/2; //new head is @ 1/2 of the new size of queue
        tail = size_of_queue+1; //new tail @ the end of array+1 bc of my implementation (this is an imaginary position/ refer to default constructor for more info.
        queue[++head] = element; // after it grow, pushes the element into the queue. its [++head] index bc the head is always one index behind where actual empty spaces are.
    }
    else{  //if pushing something to the front doesn't reaches the capacity. by default, do this.
       queue[++head] = element; //its [++head] index bc the head is always one index behind where actual empty spaces are.
        num_elements++; //increases the # of elements in the queue.

    }

}


void push_back(T element ){ //extremely similar to the push_front implementation , refer to above more info.
    if(num_elements==size_of_queue){//if the array is  full, do the following
        num_elements++;
        //cout<<"realizes its full"<<endl;//if that happens the current array is fulled...need to resize
        grow(size_of_queue*2, queue);//calls grow helper method, which x2 the size of array.
       // cout<<"successfully called grow"<<endl;
        size_of_queue=size_of_queue*2;
        head = size_of_queue/2;
        tail = size_of_queue+1; ////tail is always the size of queue+1(an imaginary position for pointer purposes
        queue[--tail] = element;

    }
    else{
        queue[--tail] = element;
        num_elements++;
    }
}

T pop_front(){ //for pop front and back I havee a temp string remove[], should the return type remain as string?or just change to the T?
    //T remove;//a local temp variable that saves the string to be removed

    if(empty()){
       // throw notEnough;
       throw invalid_argument("Your Queue is empty!!!Can't pop anything!");
    }
    else if((num_elements<=(size_of_queue/4))&&(head==0)&& (size_of_queue>minSize)){ //this else if statement is needed bc if the pop method happens to run into 1/4 and we are @ the very "front" of the array, I need to make the pointer go around to the "very back" of the array
        //cout<<"leftMost of the array and less than 1/4 full"<<endl;
        num_elements--;
        int previousHead = size_of_queue; //the previous head before the new pointers gets new locations, again head is a pointer that is always +1 then the actual element, so decrements for the previousHead.

        remove = queue[previousHead];//
        //queue[previousHead]="";

        shrink(size_of_queue/2, queue);

        size_of_queue =size_of_queue/2;
        head = (size_of_queue/2)-1; //new head in the middle of new queue
        tail=(size_of_queue+1); //new tail in the end of new queue
      //  cout<<"You just removed: " << remove <<endl; used for debugging purposes...
        return remove;

    }

    else if((num_elements<=(size_of_queue/4))&& (size_of_queue > minSize)){ //always check if num_of_elements reached below the 1/4 line and above the minimal array size[8]
        num_elements--; //subtract the num of elements inside the array.
        int previousHead = head--; //the previous head before the new pointers gets new locations, again head is a pointer that is always +1 then the actual element, so decrements for the previousHead.


        remove = queue[previousHead];//
        //queue[previousHead]="";//after set it to remove, replace whatever element that was in there previously with an empty string

        shrink(size_of_queue/2, queue);// call the shrink helper method
        //cout<<"shrinks successfully"<<endl;
        size_of_queue = size_of_queue/2;



        head=(size_of_queue/2)-1; // For some reason my array wont shrink until it actually hits below 1/4. so the head now is 1 less than the 1/2 the size of the current array
        tail=size_of_queue+1;

       // cout<<"You just removed: " << remove <<endl;
        return remove;
    }
    else if(head==0){ // if the head reaches 0, the array has reached the leftMost end of the array.
        cout<<"leftMost of the array"<<endl;
        head = size_of_queue; //turn the tail pointer around to point to the end, and pop it.
       //int x = head;
        int x = head--;//  the usual decrement, this is the line that caused a bug from submission part a.
        remove = queue[x]; //set the string to be remove before its emptied

        //queue[x] ="";//emptied string in the element
        num_elements--; //decrement the num of element

        //cout<<"You just removed: " << remove <<endl;
        return remove;
    }
    else{
        int x = head--; //All other cases, just decrements the head when poping.
        remove = queue[x];//
       // queue[x]="";//after set it to remove, replace whatever element that was in there previously with an empty string
        //head-- ; //decrement head
        num_elements--; //subtract the num of elements inside the array.
        //cout<<"You just removed: " << remove <<endl;
        return remove;
    }
}


T pop_back(){ //extremely similar implementation from pop_front(), refer there if needed
    //T remove;//a local temp variable that saves the string to be removed
    if(empty()){
        //throw notEnough;
         throw runtime_error("Your Queue is empty!!!Can't pop anything!");
    }
    else if((num_elements<=(size_of_queue/4))&& (size_of_queue > minSize)){ //always check if num_of_elements reached below the 1/4 line
        num_elements--; //subtract the num of elements inside the array.

        int previousTail = tail++;//stores previous tail before tail changes.
        remove = queue[previousTail];//again head is a pointer that is always +1 then the actual element, so set the element to be removed.
        //queue[previousTail]="";//after set it to remove, replace whatever element that was in there previously with an empty string
        //cout<<"You just removed: " << remove <<endl;

        shrink(size_of_queue/2, queue);//if it does, then call the shrink helper method
        size_of_queue = size_of_queue/2;

        tail=size_of_queue+1;
        head=(size_of_queue/2)-1;//new head is @ the new size/2 -1, again bc my array wont actually shrink until it's less than 1/4 full. so the head need to be decremented


        return remove;
    }
    else if(num_elements<=(size_of_queue/4)&&(tail==(size_of_queue+1))){
        //cout<<"rightMost of the array and less than 1/4 full"<<endl;
        num_elements--; //decrement before it resizes
        shrink(size_of_queue/2, queue);
        size_of_queue = size_of_queue/2;

        tail = 0; //turn the tail pointer around to point to 0, and pop
        head=(size_of_queue/2)-1;

        int x = tail++;
        remove = queue[x];
       // queue[x] ="";
       // cout<<"You just removed: " << remove <<endl;
        return remove;
    }
    else if(tail==(size_of_queue+1)){ // if the head reaches sizeOfQueue +1(the initial tail position), the array has reached the rightMost end of the array.
       // cout<<"rightMost of the array"<<endl;
        tail = 1; //turn the tail pointer around to point to 1, and pop it.
        int x = tail++;
        remove = queue[x];
        //queue[x] ="";
        num_elements--;
        //cout<<"You just removed: " << remove <<endl;
        return remove;
    }
    else{
        int x = tail++;
        remove = queue[x];//
        //queue[x]="";//after set it to remove, replace whatever element that was in there previously with an empty string
        num_elements--; //subtract the num of elements inside the array.
        //cout<<"You just removed: " << remove <<endl;
        return remove;
    }
}


int size(){
    return size_of_queue; //return the size of queue

}
bool empty(){
    if(num_elements==0) return true;
    else{
        return false;
    }
}


string toStr(){
	stringstream output;
	//string output;
    string* temp;

    //if(num_elements==0){
      //  output<<"The array is empty, nothing to output"<<endl;
        //throw notEnough;//same situation when the array is empty, wasn't sure if I should throw this exception
  //  }
    //else{
        int i=head;  //print from starting from the head of queue
        int j=0; //J starts 0
        while(j<num_elements){ //as long as my there's still element in the list
            if(i==0){ //comes here when the head reaches the leftEnd of Queue
            //ss << j;
                i = size_of_queue; //change the head to the rightEnd of queue
            }
        //ss << j;
        output<<queue[i]<<endl; //set output to what queue @ i index
        j++; //j increments
        i--; //while i decrements
        }
   // }
     //cout<<"Array current size is: "<< size_of_queue <<endl;
    // cout << "There are " << num_elements << " elements in the array" << endl;
        return output.str();
}
//this is just something I used to debugg....

//the Following method is used for debugging purposes, for more visual usage of the array
/*
void print_queue(){
    cout << "\n\n\nThe size_of_queue size of the queue is: " << size_of_queue<< endl;
    cout << "There are " << num_elements << " elements in the array" << endl;
    for(int i = 1; i <size_of_queue +1; i++) {
        string temp = queue[i];
        if(temp == "") {
            cout << "Index position " << i << " is empty." << endl;
        }
        else {
            cout << "The content at the index position " << i << " is: " << temp << endl;
        }
    }
    cout << "\n\n\n" << endl;
}
*/

};


