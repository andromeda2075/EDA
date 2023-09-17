#include <cstddef>
#include <iostream> // cout
#include <fstream>  // ofstream, ifstream
#include <cmath>
#include <memory>
#include "demo.h"
#include "array.h"
#include "matrix.h"
#include "foreach.h"
#include "doublelinkedlist.h"
#include "linkedlist.h"

using namespace std;

template <typename T, int N>
void increment(T &x)
{  x+= N; }

template <typename T>
void print(T &x)
{  cout << x; }

// Object function
template <typename T>
class ClassX
{          int m_inc = 0;
    public:  ClassX(int n) : m_inc(n){}
    void operator()(T &n){  n += m_inc;     }
};

void Fx1(int n ) {    n++;    }
void Fx2(int &n) {    n++;    }
void Fx3(int *pi){    ++*pi;  pi = nullptr; }
void Fx4(int *&rp){   ++*rp;  rp = nullptr; }

void DemoBasicPointers(){
    int i = 10, j = 20, &r = i; 
    int *b /*Peligro*/, *p = nullptr, *q = nullptr, **pp = nullptr;
    p = &i;     q = &j;     pp = &p;
    float f = 3.14;
    cout << "***** Fx1 *****" << endl;
    Fx1(i);     cout << i << endl;  //  10
    Fx1(15);
    Fx1(*p);    cout << i << endl;  //  10
    Fx1(**pp);  cout << i << endl;  //  10
    Fx1(r);     cout << i << endl;  //  10
    
    cout << "***** Fx2 *****" << endl;
    i = 10;     // r = 10;
    Fx2(i);     cout << i << endl;  // 11
    // Fx2(20);
    // Fx2(i+5);
    // Fx2(i+j);
    // Fx2(f);
    Fx2(r);     cout << i << endl;  // 12

    cout << "***** Fx3 *****" << endl;
    **pp = 10;  // *p = 10;     i = 10;
    *q = 20;    //  j = 20;
    Fx3(p);     cout << i << endl;  // 11
    Fx3(*pp);   cout << i << endl;  // 12
    Fx3(&i);    cout << i << endl;  // 13
    Fx3(q);     cout << j << endl;  // 21
    Fx3(&j);    cout << j << endl;  // 22

    cout << "***** Fx4 *****" << endl;
    p = &i;     q = &j;     pp = &p;
    **pp = 50;  // *p = 10;     i = 10;
    *q   = 60;  //  j = 20;
    Fx4(p);     cout << i << " p: :" << p << endl;  // 51
    p = &i;     // *pp = &i;
    Fx4(*pp);   cout << i << " p: :" << p << endl;  // 52, p: 0x0
    // Fx4(&i);    Error ! es un valor
    Fx4(q);     cout << j << " q: :" << q << endl;  // 61 q: 0x0
    // Fx4(&j);    cout << j << endl;  // 22
}

void DemoSmartPointers(){
    CArray< TraitArrayIntInt > v2("Lucero"), *pX; //, *pV3 = new CArray("Luis");
    
    shared_ptr< CArray< TraitArrayFloatString > > pV3(new CArray< TraitArrayFloatString >("Luis")), pV4;
    pV4 = pV3;
    auto &rA = *pV3;
    for(auto i = 100 ; i < 112 ; i++)
    {   v2.insert(i, i*i);
        pV3->insert(sqrt(i), string("**")+to_string(sqrt(i)+5)+string("**"));
        //  (*pv3).insert(i);
        //  rA.insert(i);
    }
    cout << "Printing pV3 float -> string (greater)" << endl;
    cout << *pV3 ;
}

void DemoDynamicMatrixes(){

    cout << "----------------mat1--------------------" << endl;
    CMatrix<MatrixTraitFloat> mat1(3, 4);
    mat1.fill(1);
    //cout << "k : " << mat1.m_rows<<endl;
    cout << mat1;

    cout << "----------------mat1--------------------" << endl;
    CMatrix<MatrixTraitFloat> mat2(4, 5);
    mat2.fill(2.5);
    cout << mat2;

    cout << "----------------mat1*mat2--------------------" << endl;
    // TODO #1: overload operator*(CMatrix<Traits> &other)
    CMatrix<MatrixTraitFloat> mat3 = mat1 * mat2;
    cout << mat3;

    cout <<endl;
    cout << "----------------Iterator matrix--------------------" << endl;
    // TODO #2: Create Iterator for CMatrix
    cout <<endl<< "----mat1----" << endl;
    foreach(mat1, ::print<TX>);
    cout << endl;

    cout <<endl<< "----mat1 sumando un contador----" << endl;
    TX x = 1;
    // // Lambda function
    // foreach(mat1, [x](TX &n){ n += x; x++; });
    // foreach(mat1, ::print<TX>); cout << endl;
    // ClassX<TX> ope(5);
    // foreach(mat1, ope);
    // foreach(mat1, ::print<TX>); cout << endl;
    // foreach(mat1, ClassX<TX>(8) );
    // foreach(mat1, ::print<TX>); cout << endl;

     // // TODO #3: prepare Matrix to be used as a matrix from outside
    // // overload operator[](size_t row)
    cout << "----------------Operator [] and ()-------------------" << endl;
    mat1[2][3] = 8.2;
    mat1(2, 2) = 7.5; // Operator () is returning a value_type &
    cout << mat1;
    cout << endl;
}

void DemoPreandPostIncrement(){
    int x = 10, y, z;
    y = x++;
    cout << "y=" << y << " x=" << x << endl;
    x = 10;
    z = ++x;
    cout << "z=" << z << " x=" << x << endl;
}

void DemoArray(){   
    cout << "Hello from DemoArray()" <<endl;
    cout << "Vector #1()" <<endl;
    
    CArray< TraitArrayIntInt > v1("Antonio"); 
    for(auto i = 0 ; i < 15 ; i++)
        v1.insert(i, i+5);   //  insert(&v1);

    cout << "Vector #2()" <<endl;
    CArray< TraitFloatLong > v2("Cristian Vera"), 
           *pV3 = new CArray< TraitFloatLong >("Guiomar ABC");
    auto &rA = *pV3;
    for(auto i = 100 ; i < 112 ; i++)
    {   v2.insert(sqrt(i), i);
        pV3->insert(i, sqrt(i));
        //  (*pv3).insert(i);
        //  rA.insert(i);
    }
    cout << "Printing V1 (TraitArrayIntInt)" << endl;
    cout << v1; // v1.print(cout);

    cout << "Printing V2 (TraitFloatLong)" << endl;
    ostream &tmp = cout << v2 << "More text" << endl;
    tmp << "Hola !!!" << endl;
    cout << &tmp << "..." << &cout <<endl;
    // cout << x << f << y << endl;

    cout << "Printing pv3 (TraitFloatLong)" << endl;
    pV3->print(cout);
    // (*pV3).print();     *pV3 is already an object
    // rA.print();          rA is also an object
    // pV3[0].print();      pV3 is also an array with just 1 element [0]
    // (*(pV3+0)).print();
    // (*(0+pV3)).print();
    // 0[pV3].print();
    // delete pV3;

    // Using an array with []
    for(auto i = 0 ; i < v2.size() ; i++)
        cout << "v2[" << i << "] = " << v2[i] << endl;
    ofstream of("test.txt", ios::out);
    of << v2 << endl; 
    cout << "DemoArray finished !" << endl;

    //using TraitStringString = ArrayTrait<string, string  , std::less<NodeArray<string, string> &>>;
    CArray< TraitStringString > vx("Ernesto Cuadros");
    vx.insert("Ernesto", "Cuadros");
    vx.insert("Luis"   , "Tejada");
    vx.insert("Jorge"  , "Lozano");
    vx.insert("Edson"  , "Caceres");
    vx.insert("Franz"  , "Maguiña");
    vx.print(cout);
}

void DemoIterators(){
    CArray< TraitArrayIntInt > v1("Jorge");
    
    v1.insert(30, 40);
    v1.insert(18, 45);
    v1.insert(20, 35);
    v1.insert(7 , 64);
    v1.insert(12, 25);
    v1.insert(8 , 17);

    cout << v1 << endl;
    // array_forward_iterator<CArray< TraitArrayIntInt >> iter = v1.begin();
    //CArray< TraitArrayIntInt >::iterator iter = v1.begin();
    auto iter = v1.begin();
    foreach(iter, v1.end(), ::increment<TX, 7>);
    cout << v1 << endl;
    foreach(v1, ::increment<TX, 4>);
    cout << v1 << endl;

    foreach(v1, ::print<TX>);
    cout << endl;
    // Lambda function
    int x = 3;
    foreach(v1, [x](TX &n){ n *= 2*x; });
    foreach(v1, ::print<TX>); cout << endl;
    ClassX<TX> ope(5);
    foreach(v1, ope);
    foreach(v1, ::print<TX>); cout << endl;
    foreach(v1, ClassX<TX>(8) );
    foreach(v1, ::print<TX>); cout << endl;
}

void DemoReverseIterators(){
    cout << "DemoReverseIterators: " << endl;
    CArray< TraitArrayIntInt > v1("Edson Cáceres");
    v1.insert(30, 40);
    v1.insert(18, 45);
    v1.insert(20, 35);
    v1.insert(7 , 64);
    v1.insert(12, 25);
    v1.insert(8 , 17);

    cout << "Printing asc : " << endl;
    cout << v1 << endl;
    cout << "Printing desc : " << endl;
    foreach(v1.rbegin(), v1.rend(), ::print<TX>);
}

void DemoHeap()
{
    cout << "Hello from DemoHeap()" <<endl;
}

void DemoBinaryTree()
{
    cout << "Hello from DemoBinaryTree()" <<endl;
}

void DemoHash()
{
    cout << "Hello from DemoHash()" <<endl;
}


template <typename Node>

void printing(Node *pNode){
     cout << pNode->getData() << " ";
    }

template <typename T,typename Cout>

Cout &Print(T Node, Cout &OS){
     OS << Node.getData()<<" <= ";
     return OS;
    }


 
template <typename Container>
void DemoReadingFile(Container &mylist){

	cout << "Reading File"<<endl;

   ifstream Read_file("test.txt");
   
   Read_file>>mylist;
   
   cout<<"Printing using << : "<<endl;
   
   cout<<mylist<<endl;
	
}
template <typename Container>
void DemoForeachVariadic(Container &mylist){
    using Node = typename Container::Node;
	mylist.insert(34,9);
    mylist.insert(7,10);
    mylist.insert(11,40);
    mylist.insert(53,13);
    mylist.insert(20,18);
    mylist.insert(5,12);

    cout<<"-------Foreach One with Variadic Function-------"<<endl;
	cout<<endl;
    ForeachOne(mylist.begin(), mylist.end(), &Print<Node, ostream>, cout);
    cout<<endl;

    cout<<"-------Foreach One reverse with Variadic Function-------"<<endl;
	cout<<endl;
    ForeachOne(mylist.rbegin(), mylist.rend(), &Print<Node, ostream>, cout);
	cout << endl;

     cout<<"-------Foreach Two with Variadic Function-------"<<endl;
	cout<<endl;
    ForeachTwo(mylist,&Print<Node, ostream>, cout); 
    cout<<endl;
}

   
template <typename Container>

void DemoLinkedListFill(Container &mylist)
 {  
    const  IX nElem=6;
    using value_type        = typename Container::value_type;
    using LinkedValueType   = typename Container::LinkedValueType;
    using Node              = typename Container::Node;

    value_type key[nElem]={10,5,22,-100,50,-60};
    LinkedValueType value[nElem]={1,2,3,4,5,6};
       
    for(auto x=0; x<nElem; x++) { mylist.insert(key[x],value[x]); }
    mylist.print(cout);
    
    cout << endl;
	cout<<"-------Foreach-------"<<endl;
    foreach(mylist, [](Node& node) {printing(&node);});  
	cout << endl;
	//-------------------------------------------
		  
	
	cout << "Reading File"<<endl;

   ifstream Read_file("test.txt");
   
   Read_file>>mylist;
   
   cout<<"Printing using << : "<<endl;
   
   cout<<mylist<<endl;
 }
 
 void DemoLinkedList()
 {  cout<<"==== Linked List ====="<<endl;
    LinkedList<LLDesc> myDescList;
    LinkedList<LLAsc> myAscList;

    //cout << "Descending list" << endl;
    //DemoLinkedListFill(myDescList);

    //cout << "Ascending list" << endl;
    //DemoLinkedListFill(myAscList);
    cout<<"==== Foreach whit variadic function ====="<<endl;
    DemoForeachVariadic( myAscList);
 }


template <typename Container>
void DemoDoubleLinkedListFill(Container &myDoublelist){
	const  IX nElem=6;
    using value_type        = typename Container::value_type;
    using LinkedValueType   = typename Container::LinkedValueType;
    using Node              = typename Container::Node;

    value_type 			key[nElem]		={10,5,22,-100,50,-60};
    LinkedValueType 	value[nElem]	={1,2,3,4,5,6};
       
    for(auto x=0; x<nElem; x++) { myDoublelist.insert(key[x],value[x]); }
    
 
    myDoublelist.print(cout);
 	cout<<endl;
 	
 
	cout<<"-------Foreach-------"<<endl;
	cout<<endl;
    foreach(myDoublelist, [](Node& node) {printing(&node);});  
	cout << endl;
	
	cout<<"-------Foreach reverse-------"<<endl;
	cout<<endl;
    foreach_reverse(myDoublelist, [](Node& node) {printing(&node);});  
	cout << endl;	
}


void DemoDoubleLinkedList()
 {
    DoubleLinkedList<DLDesc> myDescDList;
     DoubleLinkedList<DLAsc> myAscDList;
    cout << "======  Double Linked LIst ======"<<endl;
   // cout << "=============Descending Double List==============" << endl;
  //DemoDoubleLinkedListFill(myDescDList);


  //cout << "===============Ascending Double List===============" << endl;
  //DemoDoubleLinkedListFill(myAscDList);


  //cout<< "========= Reading File ==============="<<endl;
    //DemoReadingFile( myDescDList);

   cout<< "========= Variadic Function  ==============="<<endl;
    DemoForeachVariadic( myDescDList);
    //DemoForeachVariadic( myAscDList);
 
    
 }
































