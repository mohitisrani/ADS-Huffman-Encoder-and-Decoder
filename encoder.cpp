#include<iostream>
#include<fstream>
#include<vector>
#include<bitset>
#include<ctime>
#include<sstream>
#include<string.h>
#include<stdlib.h>
using namespace std;

///////////  Basic element in the file /////////
struct Node{
    struct Node* left=NULL;     //For Huffman Tree
    struct Node* right=NULL;
    struct Node* leftX=NULL;   //For Pairing Heap
    struct Node* rightX=NULL;
    struct Node* child=NULL;


    int d1;
    int d2;


};


class infileBuffer{           //www.cplusplus.com/reference/istream/istream/read/
private:
    ifstream infile;

public:
    char* buffer; char* buffer_cp;
    infileBuffer(string s)
    :infile(s){
      if (infile) {
    // get length of file:
    infile.seekg (0, infile.end);
    int length = infile.tellg();
    infile.seekg (0, infile.beg);

    buffer = new char [length];
    buffer_cp=new char [length];

   // std::cout << "Reading " << length << " characters... ";
    // read data as a block:
    infile.read (buffer,length);
    for(int i=0;i<length;i++){buffer_cp[i]=buffer[i];}

  /*  if (infile)
     std::cout << "all characters read successfully.";
    else
      std::cout << "error: only " << infile.gcount() << " could be read";*/
    infile.close();
      }}

    ~infileBuffer(){
         delete[] buffer;
    }

};

////////  Create Frequency Table Using Array. (Optional) Create and Output Frequency Table file ////////
class freqT_arr{
    public:
        infileBuffer bf;
        freqT_arr(string infileName)
        :infile (infileName),
        fq (1000000),
        bf(infileName),
        fqtable ("frequencytable.txt")
        {
        createFreqT();
   //     printFreqT();
        }

        vector<int> fq;


        void printFreqT(){
            for(i=0;i<1000000;i++){
            if((fq[i])!=0)fqtable<<i<<" "<<fq[i]<<endl;}}

    private:
        char p[100];
        ifstream infile;
        ofstream fqtable;
        int i;

        void createFreqT(){
            for(i=0;i<1000000;i++)   //
                {fq[i]=0;}i=0;
            char * nums;
            nums = strtok (bf.buffer,"\n");
            while(nums!=NULL){
                fq[atoi(nums)]++;
                nums=strtok(NULL,"\n");}
        }


               };


////////////////////////////////////////Binary Heap Structure Start///////////////////////////////
class BinaryHeap{
    public:
        BinaryHeap()
        {}
        void Insert(Node* element){
            heap.push_back(element);
            heapifyup(heap.size() -1);}

        void DeleteMin(){ //Take care that heap is not Empty
            heap[0] = heap.at(heap.size() - 1);
            heap.pop_back();
            heapifydown(0);}

        Node* ExtractMin() {  //Take care that heap size is NOT zero
            return heap.front();}
        int Size(){
            return heap.size();}
    private:
        vector <Node*> heap;
        int left(int parent){
            int l = 2 * parent + 1;
            if (l < heap.size())
                return l;
            else
                return -1;}

        int right(int parent){
            int r = 2 * parent + 2;
            if (r < heap.size())
                return r;
            else
                return -1;}

        int parent(int child){
            int p = (child - 1)/2;
            if (child == 0)
                return -1;
            else
                return p;}

        void heapifyup(int in){
            if (in >= 0 && parent(in) >= 0 && heap[parent(in)]->d2 > heap[in]->d2){
                Node* temp = heap[in];
                heap[in] = heap[parent(in)];
                heap[parent(in)] = temp;
                heapifyup(parent(in)); }}

        void heapifydown(int in){
            int child = left(in);
            int child1 = right(in);
            if (child >= 0 && child1 >= 0 && heap[child]->d2 > heap[child1]->d2){
               child = child1;}
            if (child > 0 && heap[in]->d2 > heap[child]->d2){
                Node* temp = heap[in];
                heap[in] = heap[child];
                heap[child] = temp;
                heapifydown(child); }}};


////////////////////////////////////////4Way Heap Structure Start///////////////////////////////
class FwayHeap{
    public:
        FwayHeap(){
        heap.push_back(NULL);heap.push_back(NULL);heap.push_back(NULL);//Initialising for cache optimization
        }
        void Insert(Node* element){
            heap.push_back(element);
            heapifyup(heap.size() -1);}

        void DeleteMin(){ //Take care that heap is not Empty
            heap[3] = heap.at(heap.size() - 1);
            heap.pop_back();
            heapifydown(3);}

        Node* ExtractMin() {  //Take care that heap size is NOT zero
            return heap[3];}
        int Size(){
            return heap.size()-3;}
    private:
        vector <Node*> heap;
        int c1(int parent){
            int l = 4 * (parent-2);
            if (l < heap.size())
                return l;
            else
                return -1;}

        int c2(int parent){
            int l = 4 * (parent-2)+1;
            if (l < heap.size())
                return l;
            else
                return -1;}

        int c3(int parent){
            int l = 4 * (parent-2)+2;
            if (l < heap.size())
                return l;
            else
                return -1;}

         int c4(int parent){
            int l = 4 * (parent-2)+3;
            if (l < heap.size())
                return l;
            else
                return -1;}

        int parent(int child){
            int p = (child/4)+2;
            if (child < 4)
                return -1;
            else
                return p;}

        void heapifyup(int in){
            if (in >= 3 && parent(in) >= 3 && heap[parent(in)]->d2 > heap[in]->d2){
                Node* temp = heap[in];
                heap[in] = heap[parent(in)];
                heap[parent(in)] = temp;
                heapifyup(parent(in)); }}

        void heapifydown(int in){
            int child = c1(in);
            int child1 = c2(in);
            int child2 = c3(in);
            int child3 = c4(in);

         /*   if (child >= 3 && child1 >= 3 && heap[child]->d2 > heap[child1]->d2){
               child = child1;}
            if (child >= 3 && child2 >= 3 && heap[child]->d2 > heap[child2]->d2){
               child = child2;}
            if (child >= 3 && child3 >= 3 && heap[child]->d2 > heap[child3]->d2){
               child = child3;}
            if (child > 3 && heap[in]->d2 > heap[child]->d2){
                Node* temp = heap[in];
                heap[in] = heap[child];
                heap[child] = temp;
                heapifydown(child); }}};*/
            if (child!=-1){
            if (child1!=-1 && heap[child]->d2 > heap[child1]->d2){
               child = child1;}
            if (child2!=-1 && heap[child]->d2 > heap[child2]->d2){
               child = child2;}
            if (child3!=-1 && heap[child]->d2 > heap[child3]->d2){
               child = child3;}
            if (heap[in]->d2 > heap[child]->d2){
                Node* temp = heap[in];
                heap[in] = heap[child];
                heap[child] = temp;
                heapifydown(child); }}
                }};


////////////////////////////////////////Pairing Heap Structure Start///////////////////////////////
class pairingHeap{
    private:
            Node* children;
            Node* head;
            Node* headP;
            Node* root = NULL;
            int sz;
            Node* temp;
            Node* tempz;
            Node* Meld(Node* l,Node* r){
                l->rightX=NULL;l->leftX=NULL;
                r->leftX=NULL;r->rightX=NULL;
                if((r->d2)<(l->d2))
                {
                     tempz=r->child;
                    r->child=l;l->rightX=tempz;
                    l->leftX=r;
                    if(l->rightX!=NULL)
                    {
                        l->rightX->leftX=l;
                    }
                    return r;
                }
                else{
                    tempz=l->child;
                    l->child=r;r->rightX=tempz;
                    r->leftX=l;if(r->rightX!=NULL)r->rightX->leftX=r;
                    return l;}
                }
    public:
            pairingHeap()
            :sz(0),
            temp(NULL){}
            void Insert(Node* element){
            sz=sz+1;
            if(root==NULL){
                root=element;}
            else {
                    root=Meld(root,element);}}

            void DeleteMin(){
                sz=sz-1;
                temp=NULL;
                head=NULL;
                headP=NULL;
                children=NULL;
                if(root->child){
                    children=root->child;
                    children->leftX=NULL;
                    head=children;

                    if(children->rightX){
                        if(children->rightX->rightX){
                            temp=children->rightX->rightX;
                            children=Meld(children,children->rightX);
                            children->rightX=temp;
                            temp->leftX=children;
                            headP=children;
                            head=temp;
                            if(children->rightX->rightX == NULL)
                            {
                                root=Meld(children,head);
                                return;
                            }
                        }
                        else{
                            root=Meld(head,head->rightX);
                            return;
                        }
                    }
                    while(head->rightX){
                        if(head->rightX->rightX){
                            temp=head->rightX->rightX;
                            headP->rightX=Meld(head,head->rightX);
                            headP->rightX->leftX=headP;
                            headP=headP->rightX;
                            head=temp;head->leftX=headP;
                        }
                        else{
                            head=Meld(head,head->rightX);
                            head->leftX=headP;
                            headP->rightX=head;
                        }
                    }

                  //////////////////////////////
                    while(head->leftX){
                        if(head->leftX->leftX){
                            temp=head->leftX->leftX;
                            head=Meld(head->leftX,head);
                            temp->rightX=head;
                            head->leftX=temp;

       }
                        else{
                            children=Meld(head->leftX,head);
                            head=children;
                        }
                    }
                    root=children;
                }
                else{
                        root=NULL;
                }
            }

            Node* ExtractMin(){
                return root;}

            int Size(){
                return sz;}};

///////////Create Huffman Tree,  Create Code Table, and Encoding.   //////////
class huffmanT{

    private:
        //map<int,string> store;
        //vector<vector<char>> store_;
        vector<string> store;
        string line;
        ofstream code;
        int a;
        ifstream infile ;
        ofstream encode ;
        stringstream ss;


       pairingHeap pq;
//      BinaryHeap pq;
//       FwayHeap pq;
        //freqT ft;

        Node *m1=new Node;
        Node *m2=new Node;


    public:
        vector<char> sss;
        freqT_arr ft;
        huffmanT(string s)
            :code ("code_table.txt"),
            infile (s),
            ft(s),

            encode ("encoded.bin",ios::binary|ios::out),
            store(1000000)//,
            //store_(1000000)
            {}

        Node* CreateTree(){
          /*  for(map<int,int>::iterator it=ft.fq.begin();it!=ft.fq.end();it++){
                Node*temp = new Node;
                temp->d1=it->first;
                temp->d2=it->second;
                pq.Insert(temp);}*/

             for(int i=0;i<1000000;i++){
                if(ft.fq[i]!=0){
                    Node*temp = new Node;
                    temp->d1=i;
                    temp->d2=ft.fq[i];
                    pq.Insert(temp);}}

            while(pq.Size()>=2){
                m1=pq.ExtractMin();pq.DeleteMin();
                m2=pq.ExtractMin();pq.DeleteMin();
                Node *temp=new Node;
                temp->left=m1;
                temp->right=m2;
                temp->d2=m1->d2+m2->d2;
                pq.Insert(temp);
                }
            return pq.ExtractMin();}

        void codeTable(Node* element,vector<char> st)
            {
            if (!element) // end the recursion if node == nullptr
               return;
            if(element->left)st.push_back('0');
            codeTable(element->left,st);            // display the left subtree
            if(element->left)st.pop_back();
            if(!(element->left)){
                    store[element->d1]=string(st.begin(),st.end()); // display the current node
                    //code<<string(st.begin(),st.end())<<" "<<element->d1<<endl;
                    ss<<string(st.begin(),st.end())<<" "<<element->d1<<endl;

            }
            if(element->right)st.push_back('1');
            codeTable(element->right,st);           // display the right subtree
            }

            void printCodeTable(){
            code<<ss.rdbuf();
            code.close();
            }

        void Ncode(){

            char * nums;
            stringstream bl;
            string st_;
            bitset<8> temp;
            int length;
            int i=7;
            temp.reset();
            //char blocks[1024*1024+1];
            nums = strtok (ft.bf.buffer_cp,"\n");
            while(nums!=NULL){
                st_=store[atoi(nums)];
                length=st_.size();
                for(int j=0;j<length;j++)
                {
                    //cout<<st_[j];
                    if(st_[j]=='0'){                                                 //https://codeyarns.com/2013/12/27/how-to-write-binary-file-in-c/
                        temp.set(i--,0);
                    }
                    else{
                        temp.set(i--,1);
                    }
                if(i==-1){
                   ss<<static_cast<char>( temp.to_ulong() );
                   //cout<<temp;
                   i=7;
                }}
                nums=strtok(NULL,"\n");}
          //  temp.set(i--,1);
          //  while(i>=0){
          //      temp.set(i--,0);
          //  }
          //  ss<<static_cast<char>( temp.to_ulong() );
            encode<<ss.rdbuf();

            //while(ss.get(blocks,1024*1024+1)){
            //encode.write((char*)&blocks,16*8*1024*sizeof(double));}     //http://www.cplusplus.com/forum/general/21018/
            //encode<<ss.str();

            encode.close();
        }

    };

int main(int argc, char * argv[])
{
//Initialization
    string s=argv[1];
    vector<char> st;
    Node* root=new Node;

//Creating Huffman Tree
                                                                    clock_t s1 = clock();cout<<endl<<"////////////////////////////////////////////////////////////////////////"<<endl<<"Creating Frequency Table...  ";
    huffmanT hf(s);                                                 clock_t s2 = clock();cout<<double(s2 - s1) / CLOCKS_PER_SEC<<" sec"<<endl<<"Creating Huffman Tree...   ";
    root=hf.CreateTree() ;                                          clock_t s3 = clock();cout<<double(s3 - s2) / CLOCKS_PER_SEC<<" sec"<<endl<<"Creating Code Table...     ";
    hf.codeTable(root,st);
    hf.printCodeTable();                                            clock_t s4 = clock();cout<<double(s4 - s3) / CLOCKS_PER_SEC<<" sec"<<endl<<"Encoding...               ";
//Encode given file
    hf.Ncode();                                                     clock_t s5 = clock();cout<<double(s5 - s4) / CLOCKS_PER_SEC<<" sec"<<endl<<"The files: encoded.bin and code_table.txt are ready to be transmitted"<<endl<<"///////////////////////////////////////////////////////////////////////"<<endl;

    return 0;

    }
