#include<iostream>

using namespace std;

struct myArray
{
    int total_size;
    int used_size;
    int *ptr;
};

class MyArray{
    public:
    MyArray(struct myArray *a,int tsize,int usize){
        a->total_size=tsize;
        a->used_size=usize;
        a->ptr=(int *)malloc(tsize*sizeof(int));    // Storing on Heap
    }
     
    void setVal(struct myArray *a);
    void show(struct myArray *a);
};

void MyArray::setVal(struct myArray *a){

    cout<<"\nSetting Values : "<<endl;

    for (int i = 0; i < a->used_size; i++)
    {
        cout<<"Enter the value for Element "<<i+1<<" : ";
        cin>>(a->ptr)[i];
    }
    
} 

void MyArray::show(struct myArray *a){

    cout<<"Displaying Elements : "<<endl;
    for (int i = 0; i < a->used_size; i++)
    {
        cout<<(a->ptr)[i]<<endl;
    }
}

int main(){
    
    struct myArray marks;
    int tsize,usize;

    cout<<"\nEnter the size of array to be created : ";
    cin>>tsize;
    cout<<"\nEnter the size of array to be used : ";
    cin>>usize;
    if(usize>tsize){
        cout<<"\n!Error : Used Size should be less than Total Size\n"<<endl;
        exit(0);
    }

    MyArray m(&marks,tsize,usize);      // This dynamic allocation helps to retain memory as it stores on heap
    m.setVal(&marks);   // setting values
    m.show(&marks);     // Display the elements

    return 0;
}

