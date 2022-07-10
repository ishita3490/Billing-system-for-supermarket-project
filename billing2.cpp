#include<iostream>
#include<stdio.h>
#include<fstream>

using namespace std;

class product{
    public: 
        int pcode;
        string pname;
        float price;
        float dis;
        int quantity;
};

class administrator: public product{
    public:
        void admin();
        void add();
        void edit();
        void rem();
        void edit(int a,string b,float c,float d,int e);
};

class customer : public product{
    public:
        void buy();
        void list();
        void receipt();
        void edit_quantity(int a,string b,float c,float d,int e);
};

class supermarket : private administrator, private customer{
    public:
        void menu();
};

void supermarket :: menu(){
    m:
    int choice ;
    string email;
    string password ; 

    cout<<"\t\t\t\t_________________________________________________"<<endl;
    cout<<"\t\t\t\t                                                 "<<endl;
    cout<<"\t\t\t\t         supermarket main menu                   "<<endl;
    cout<<"\t\t\t\t_________________________________________________"<<endl;
    cout<<"\t\t\t\t                                                 "<<endl;
    cout<<"\t\t\t\t  1) Administrator                               "<<endl;
    cout<<"\t\t\t\t  2) customer                                       "<<endl;
    cout<<"\t\t\t\t  3) Exit                                        "<<endl;
    cout<<"\t\t\t\t                                                 "<<endl;
    
    cout<<"\t\t\t\t  Please Select : ";
    cin>>choice;

    switch(choice){   
        case 1 : 
            {   
                cout<<"\t\t\t\t Please Login -------------\n";
                cout<<"\t\t\t\t Enter Email :  ";
                cin>>email;
                cout<<"\t\t\t\t password : ";
                cin>>password;

                if(email=="robby@gmail.com" && password=="robby@123"){
                    administrator::admin();
                }else{
                    cout<<"\n\t\t\t\tINVALID EMAIL/PASSWORD  \n";
                }
                break;
            }
        case 2 :
            {
                customer::buy();
                break;
            }
        case 3 :
            {
                exit(0);
            }
        default : 
            {
                cout<<"Please select from the given options";
            }
    }
    goto m;
}

void administrator :: admin(){
    m:
    int choice;
    cout<<"\n\n\t\t\t___________Administration menu__________________";
    cout<<"\n\t\t\t\t   1) Add the Product";
    cout<<"\n\t\t\t\t   2) Modify the Product";
    cout<<"\n\t\t\t\t   3) Delete the Product";
    cout<<"\n\t\t\t\t   4) Back to Main menu";
    cout<<"\n\n\t\t\t\t   Please enter your choice :";
    cin>>choice;

    bool flag = false; 

    switch (choice)
    {
        case 1 : 
            add();
            break; 
        case 2 : 
            edit();
            break;
        case 3 : 
            rem();
            break;
        case 4 : 
            flag = true;
            break;

        default: 
            cout<<"INVALID CHOICE!";
    }

    if(flag){
        return ;
    }

    goto m;
}

void customer :: buy(){
    m:
    int choice; 
    cout<<"\n\t\t\t                            ";
    cout<<"\n\t\t\t\t___________customer____________";
    cout<<"\n\t\t\t                            ";
    cout<<"\n\t\t\t\t___________1) Buy Product___";
    cout<<"\n\t\t\t                            ";
    cout<<"\n\t\t\t\t___________2) Go back_______";
    cout<<"\n\t\t\t                            ";
    cout<<"\n\t\t\t\t___________Enter your choice : ";
    cin>>choice;

    bool flag = false; 

    switch (choice)
    {
        case 1 : 
            receipt();
            break; 
        case 2 : 
            flag = true; 
            break;

        default: 
            cout<<"INVALID CHOICE";
    }

    if(flag) return ;

    goto m;
}

void administrator :: add(){
    fstream data; 
    int c ;
    int token = 0;
    float p;
    float d;
    string n;
    int q;

    cout<<"\n\n\t\t\t\t ---------Add new product-------------"<<endl;
    cout<<"\n\t\t\t\t Product code of the product : ";
    cin>>pcode; 
    cout<<"\n\t\t\t\t Name of the product : ";
    cin>>pname;
    cout<<"\n\t\t\t\t Price of the Product : ";
    cin>>price ;
    cout<<"\n\t\t\t\t Discount on Product : ";
    cin>>dis; 
    cout<<"\n\t\t\t\t quantity on Product : ";
    cin>>quantity;

    data.open("database.txt",ios::in);

    if(!data){
        data.open("database.txt",ios::app|ios::out);
        data<<" "<<pcode<<" "<<pname<<" "<<price<<" "<<dis<<" "<<quantity<<endl; 
        data.close();
        return;
    }
    else{
        data>>c>>n>>p>>d>>q; 

        while(!data.eof()){
            if(c == pcode){
                if(pname != n){
                    cout<<"\n\t\t\t\t A different product with same product code exist : ";
                    cout<<"\n\n\t\t\t\t Record not inserted ! " ;
                    break;
                }

                int temp = q + quantity;
                edit(c,n,p,d,temp);
                token++;
                break;
            }
            data>>c>>n>>p>>d; 
        }
        data.close();
        
        if(token != 1){
            data.open("database.txt",ios::app|ios::out);
            data<<" "<<pcode<<" "<<pname<<" "<<price<<" "<<dis<<" "<<quantity<<endl; 
            data.close();
        }
    }
    cout<<"\n\n\t\t\t\t Record inserted ! " ;
}

void administrator :: edit(){
    fstream data,data1;

    int pkey;
    int token=0;
    int c;
    float p;
    float d; 
    string n;
    int q;

    cout<<"\n\t\t\t\t Modify the record";
    cout<<"\n\t\t\t\t Product code : ";
    cin>>pkey;

    data.open("database.txt",ios::in);
    if(!data){
        cout<<"\n\nFile doesn't exist! ";
        return ;
    }else{
        data1.open("database1.txt",ios::app|ios::out);
        data>>pcode>>pname>>price>>dis>>quantity;
        
        while(!data.eof()){
            if(pkey == pcode){
                cout<<"\n\t\t\t\t product new code: ";
                cin>>c; 
                cout<<"\n\t\t\t\t Name of the Product : ";
                cin>>n;
                cout<<"\n\t\t\t\t Price : ";
                cin>>p;
                cout<<"\n\t\t\t\t Discount : ";
                cin>>d; 
                cout<<"\n\t\t\t\t quantity : ";
                cin>>q;
                data1<<" "<<c<<" "<<n<<" "<<p<<" "<<d<<" "<<q<<"\n";
                cout<<"\n\n\t\t\t\t Record Edited";
                token++;
            }else{
                data1<<" "<<pcode<<" "<<pname<<" "<<price<<" "<<dis<<" "<<quantity<<"\n";
            }
            data>>pcode>>pname>>price>>dis>>quantity;
        }
        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt","database.txt");

        if(token == 0){
            cout<<"Record Not Found! ";
        }
    }
}

void administrator :: edit(int a,string b,float c,float e,int f){
    fstream data,data1;

    int pkey = a;
    int token=0;
    float p = c ;
    float d = e; 
    string n = b;
    int q = f;

    
    data.open("database.txt",ios::in);
    
    if(!data){
        cout<<"\n\nFile doesn't exist! ";
        return ;
    }else{
        data1.open("database1.txt",ios::app|ios::out);

        data>>pcode>>pname>>price>>dis>>quantity;
        while(!data.eof()){
            if(pkey == pcode){
                data1<<" "<<pcode<<" "<<n<<" "<<p<<" "<<d<<" "<<q<<"\n";
            }else{
                data1<<" "<<pcode<<" "<<pname<<" "<<price<<" "<<dis<<" "<<quantity<<"\n";
            }
            data>>pcode>>pname>>price>>dis>>quantity;
        }
        data.close();
        data1.close(); 
        
        remove("database.txt");
        rename("database1.txt","database.txt");  
    }
}

void administrator:: rem(){
    fstream data,data1;
    int pkey;
    int token=0;
    cout<<"\n\n\t\t\t\t Delete product";
    cout<<"\n\n\t\t\t\t Product code : ";
    cin>>pkey;

    data.open("database.txt",ios::in); // reading mode 
    if(!data){
        cout<<"\n\t\t\t\tFile doesn't exist! ";
    }else{
        data1.open("database1.txt",ios::app|ios::out);      // append and writing mode 
    
        data>>pcode>>pname>>price>>dis>>quantity;

        while(!data.eof()){
            if(pcode == pkey){
                cout<<"\n\n\t\t\t\t Product deleted successfully";
                token++;
            }else{
                data1<<" "<<pcode<<" "<<pname<<" "<<price<<" "<<dis<<" "<<quantity<<endl;
            }

            data>>pcode>>pname>>price>>dis>>quantity;
        }

        data.close();
        data1.close();
        remove("database.txt");
        rename("database1.txt","database.txt");

        if(token == 0){
            cout<<"\n\n\t\t\t\t Record not found";
        } 
    }
}

void customer :: edit_quantity(int pkey,string n,float p,float d,int q){
    fstream data,data1;
    
    data.open("database.txt",ios::in);
    
    if(!data){
        cout<<"\n\nFile doesn't exist! ";
        return ;
    }else{
        data1.open("database1.txt",ios::app|ios::out);
        data>>pcode>>pname>>price>>dis>>quantity;
        while(!data.eof()){
            if(pkey == pcode){
                data1<<" "<<pcode<<" "<<n<<" "<<p<<" "<<d<<" "<<q<<"\n";
            }else{
                data1<<" "<<pcode<<" "<<pname<<" "<<price<<" "<<dis<<" "<<quantity<<"\n";
            }
            data>>pcode>>pname>>price>>dis>>quantity;
        }
        data.close();
        data1.close(); 
        remove("database.txt");
        rename("database1.txt","database.txt");  
    }
}

void customer :: list(){
    fstream data;   
    data.open("database.txt",ios::in);

    cout<<"\n\n_________________________________________________\n";
    cout<<"prono \t\t Name \t\t Price \t\t quantity\n";
    cout<<"|_________________________________________________\n";
    data>>pcode>>pname>>price>>dis>>quantity;

    while(!data.eof()){
        cout<<pcode<<" \t\t "<<pname<<" \t\t "<<price<<" \t\t "<<quantity<<endl;
        data>>pcode>>pname>>price>>dis>>quantity;
    }

    data.close();
}

void customer :: receipt(){
    m:
    fstream data;
    
    int arrc[1000];
    int arrq[1000];
    char choice;
    int c=0;
    float amount=0;
    float dis=0;
    float total=0;

    cout<<"\n\n\t\t\t\t  RECEIPT : ";
    data.open("database.txt",ios::in);

    if(!data){
        cout<<"\n\t\t\t\tEmpty database!" ;
    }else{
        data.close();

        list();
        cout<<"\n______________________________________________";
        cout<<"\n|                                             |";
        cout<<"\n|          Please Place the order             |";
        cout<<"\n|                                             |";
        cout<<"\n|_____________________________________________|";
        
        do{
            cout<<"\n\n Enter Product Code : ";
            cin>>arrc[c];
            cout<<"\n\n Enter the Quantity : ";
            cin>>arrq[c];

            data.open("database.txt",ios::in);
            data>>pcode>>pname>>price>>dis>>quantity;

            bool flag = false;

            while(!data.eof()){
                if(pcode == arrc[c]){
                    while(arrq[c] > quantity){
                        cout<<"\n\n Product is not available in the demanded quantity";
                        cout<<"\n\n will you like to buy in less quantity? if yes then enter 'y' else enter 'n' : ";
                        char z;
                        cin>>z; 
                        if(z == 'y' || z == 'Y'){
                            cout<<"\n\n Enter the Quantity : ";
                            cin>>arrq[c];
                        }else{
                            flag = true; 
                            break;
                        }
                    }

                    int temp = quantity-arrq[c];
                    edit_quantity(pcode,pname,price,dis,temp);

                    break;
                }
                data>>pcode>>pname>>price>>dis; 
            }
            data.close();

            if(!flag) c++;
            cout<<"\n\n Do you want to buy another product? if yes then enter 'y' else enter 'n' : ";
            cin>>choice;
        }while(choice == 'y');

        cout<<"\n\n\t\t\t__________________Receipt_____________\n";
        cout<<"\nproduct num. \t product name \t product quantity \t price \t Amount \t Amount with discount\n";

        for(int i=0;i<c;i++){
            data.open("database.txt",ios::in);
            data>>pcode>>pname>>price>>dis>>quantity;

            while(!data.eof()){
                if(pcode == arrc[i]){
                    amount = price*arrq[i];
                    dis = amount - ((amount*dis)/100);
                    total = total + dis ;

                    cout<<"\n"<<pcode<<" \t\t    "<<pname<<" \t    "<<arrq[i]<<" \t\t\t   "<<price<<" \t    "<<amount<<" \t   "<<dis;
                    break;
                }
                data>>pcode>>pname>>price>>dis; 
            }
            data.close();
        }
    }

    cout<<"\n\n_____________________________________________________";
    cout<<"\n Total Amount : "<<total<<endl;
}

int main(){
    supermarket s; 
    s.menu();

    return 0;
}