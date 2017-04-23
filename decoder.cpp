#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include<ctime>
#include<streambuf>
#include<sstream>
#include<bitset>
#include<string.h>
#include<stdlib.h>
using namespace std;

///////////  Basic element in the file /////////
struct Node{
    struct Node* left=NULL;
    struct Node* right=NULL;
    char* d1;
};

///////////Create Huffman Tree,  Create Code Table, and Encoding.   //////////
class huffmanT{

    private:
        Node* root=new Node;
        Node* head;
        string codefile__;
        string encodedfile__;
    public:
        huffmanT(string encodedfile_,string codefile_)
        :encodedfile__(encodedfile_),
        codefile__(codefile_)
            {                       clock_t s1=clock();cout<<"Creating Decode Tree...  ";
            CreateTree() ;          clock_t s2=clock();cout<<double(s2 - s1) / CLOCKS_PER_SEC<<" sec"<<endl<<"Decoding...                ";
            Dcode();                clock_t s3=clock();cout<<double(s3 - s2) / CLOCKS_PER_SEC<<" sec";
            }
        void CreateTree()
        {
            char* buffer1;
            ifstream codefile(codefile__);
            if(codefile) {
                codefile.seekg (0, codefile.end);
                int length = codefile.tellg();
                codefile.seekg (0, codefile.beg);
                buffer1 = new char [length];
                codefile.read (buffer1,length);
                codefile.close();
            }

            char* num; char* val;
            num=strtok(buffer1," ");
            while(num!=NULL)
            {   head=root;
                val=strtok(NULL,"\n");
                for (;*num;num++)
                {
                    if(*num=='0')
                    {
                        if(head->left)
                        {
                            head=head->left;
                        }
                        else
                        {
                            Node* temp=new Node;
                            head->left=temp;
                            head=head->left;
                        }
                    }
                    else
                    {
                        if(head->right)
                        {
                            head=head->right;
                        }
                        else
                        {
                            Node* temp=new Node;
                            head->right=temp;
                            head=head->right;
                        }
                    }
                }
                 head->d1=val;
                 num=strtok(NULL," ");
            } //delete[] buffer1;
        }


        void Dcode()
        {
            head=root;
            char* buffer2;
            int length2;
            ofstream decoded("decoded.txt");
            stringstream ss;
            ifstream enfile(encodedfile__,ios::binary|ios::in);
            if(enfile)
            {
                enfile.seekg (0, enfile.end);
                length2 = enfile.tellg();
                enfile.seekg (0, enfile.beg);
                buffer2 = new char [length2];
                //cout<<length2<<endl;
                enfile.read (buffer2,length2);
                enfile.close();
            }

            char*num;int x=0;
            stringstream bits_;
            num=strtok(buffer2,"\n");
            while(x++<length2)
            {
                bitset<8> b(*num);
                //cout<<b;//[0]<<b[1]<<b[2]<<b[3]<<b[4]<<b[5]<<b[6]<<b[7];  //[7]<<b[6]<<b[5]<<b[4]<<b[3]<<b[2]<<b[1]<<b[0];
                bits_<<b;//[0]<<b[1]<<b[2]<<b[3]<<b[4]<<b[5]<<b[6]<<b[7];  //[7]<<b[6]<<b[5]<<b[4]<<b[3]<<b[2]<<b[1]<<b[0];
                num++;
            }

            //char*num;
            char num_;



            //num=strtok(buffer2,"\n");


            while(bits_.get(num_))
            {
                if(num_=='0')
                {
                    if(head->left)
                    {
                        head=head->left;
                    }
                    else
                    {
                        ss<<head->d1<<"\n";
                        head=root->left;
                    }
                }
                else
                {
                    if(head->right)
                    {
                        head=head->right;
                    }
                    else
                    {
                        ss<<head->d1<<"\n";
                        head=root->right;
                    }
                }

           // num++;
            }
        ss<<head->d1<<"\n\n";
        decoded<<ss.rdbuf();
        delete[] buffer2;
        }


    };

int main(int argc, char * argv[])
{   

    cout<<"////////////////////////////////////////////////////////////////////////////////////"<<endl;
    huffmanT hf(argv[1],argv[2]);
    cout<<endl<<"The file is decoded and saved as decoded.txt\n///////////////////////////////////////////////////////////////////////////////////"<<endl;
    return 0;
}
