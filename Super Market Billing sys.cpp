#include <iostream>
#include<sstream>
#include<string>
const int T_S = 10;
using namespace std;
struct HashTableEntry {
    long long int itemID;
   string name;
   int rate;
   int quantity;

   HashTableEntry *next;
   HashTableEntry *previous;
   HashTableEntry( long long int itemID, string name, int rate,int quantity) {
      this->itemID = itemID;
      this->name = name;
      this->rate = rate;
      this->quantity = quantity;
      this->next = nullptr;
      this->previous=nullptr;
   }
};

class inventory {
   public:
      HashTableEntry **ht;
      inventory() {
         ht = new HashTableEntry*[T_S];
         for (int i = 0; i < T_S; i++)
            ht[i] = nullptr;
      }
      int HashFunc( long long int itemID)
      {
         return itemID % T_S;
      }



      void Add_item( long long int itemID, string name,int rate,int quantity) {

         int hash_index = HashFunc(itemID);
         HashTableEntry* previous = nullptr;
         HashTableEntry* current = ht[hash_index];
         while (current!= nullptr) {
            previous = current;
            current = current->next;
         }
         if (current == nullptr) {
            current = new HashTableEntry(itemID, name, rate, quantity);
            if (previous == nullptr) {
               ht[hash_index] = current;
            } else {
               previous->next = current;
            }
         } else {
            current->name = name;
            current->rate = rate;
            current->quantity = quantity;
         }


      }
       void Delete_item( long long int itemID) {
         int hash_index = HashFunc(itemID);
         HashTableEntry* current = ht[hash_index];
         HashTableEntry* previous = nullptr;
         if (current == nullptr) {
            cout<<"\nNo item found with this itemID "<<itemID<<endl;
            return;
         }
         while (current->next != nullptr) {
                if(current->itemID == itemID)
                break;
            previous = current;
            current = current->next;

         }
         if (previous != nullptr) {
            previous->next = current->next;
         }
         delete current;
         cout<<"\nItem Deleted"<<endl;
      }

      void Update_item( long long int itemID)
      {
          string newname;
          int newrate;
          int newquantity;
          int hash_index = HashFunc(itemID);
          int flag = 0;
         HashTableEntry* current = ht[hash_index];
         if (current != nullptr) {
            while (current != nullptr) {
               if (current->itemID == itemID) {
                  flag = 1;
               }
               if (flag==1) {
               cout<<"\nEnter new name : ";
               cin>>newname;
               cout<<"\nEnter new Rate : ";
               cin>>newrate;
               cout<<"\nEnter new Quantity : ";
               cin>>newquantity;

               current->name = newname;
               current->rate = newrate;
               current->quantity = newquantity;
               cout<<"\n\nInfo. Updated Successfully! "<<endl;
               break;
               }
               current = current->next;
            }
         }
            if(flag==0)
                cout<<"\nNo Item found at this ItemID."<<endl;
      }

      void get_product_info( long long int itemID) {
         int hash_index = HashFunc(itemID);
         int flag = 0;
         HashTableEntry* current = ht[hash_index];
         if (current != nullptr) {
            while (current != nullptr) {
               if (current->itemID == itemID) {
                  flag = 1;
               }
               if (flag==1) {

                  cout<<"\nDetails of Item found at this ItemID :"<<itemID<<": "<<endl;
                  cout<<"\nName of Item : "<<current->name<<endl;
                  cout<<"Rate of Item : "<<current->rate<<endl;
                  cout<<"Quantity of Item : "<<current->quantity<<endl;
                  break;

               }

               current = current->next;
            }
         }
         if (flag==0)
            cout<<"No Item found at this ItemID "<<itemID<<endl;
      }

      void Update_after_purchase(int itemID,int sold_quantity,int indication)
      {

          int hash_index = HashFunc(itemID);
          HashTableEntry* current = ht[hash_index];
          if(current != nullptr)
          {
              while(current!=nullptr)
              {
                  if(current->itemID==itemID)
                  {
                     if(indication==-1)
                        current->quantity = (current->quantity)-sold_quantity;
                     if(indication==+1)
                        current->quantity = (current->quantity)+sold_quantity;
                  }
                  current = current->next;
              }

          }
          else
            cout<<"\nINCORRECT ITEM ID "<<endl;
          }




      string get_name( long long int itemID)
     {
         int hash_index = HashFunc(itemID);

         HashTableEntry* current = ht[hash_index];

         if (current != nullptr) {
            while (current != nullptr) {
               if (current->itemID == itemID)
                {
                    return current->name;
                    break;
               }
               current = current->next;
            }
         }
         else
         {cout<<"\nIncorrect itemID"<<endl;
         return 0;}
     }
     int get_rate(long long int itemID)
     {
         int hash_index = HashFunc(itemID);
         HashTableEntry* current = ht[hash_index];
         if (current != nullptr) {
            while (current != nullptr) {
               if (current->itemID == itemID) {
                  return current->rate;
                  break;}
               current = current->next;
            }
         }
         else
         { cout<<"\n Incorrect itemID ";
         return 0;}
     }


};





class billing
{
    public:
      HashTableEntry **ht_b;
      billing() {
         ht_b = new HashTableEntry*[T_S];
         for (int i = 0; i < T_S; i++)
            ht_b[i] = nullptr;
      }
      ~billing()
      {
          delete [] ht_b;
      }
      int HashFunc(long itemID)
      {
         return itemID % T_S;
      }

      void Buy_item(long long int itemID,string name,int rate,int quantity)
      {
         int hash_index = HashFunc(itemID);
         HashTableEntry* previous = nullptr;
         HashTableEntry* current = ht_b[hash_index];
         while (current!= nullptr) {
            previous = current;
            current = current->next;
         }
         if (current == nullptr) {
            current = new HashTableEntry(itemID, name, rate, quantity);
            if (previous == nullptr) {
               ht_b[hash_index] = current;
            } else {
               previous->next = current;
            }
         } else {
            current->name = name;
            current->rate = rate;
            current->quantity = quantity;
      }
      }

      int Cancel_item(long long int itemID)
      {
           int hash_index = HashFunc(itemID);
         HashTableEntry* current = ht_b[hash_index];
         HashTableEntry* previous = nullptr;
         if (current == nullptr ) {
            cout<<"\nNo item found with this itemID "<<itemID<<endl;
            return 0;
         }


            while (current->next != nullptr) {
                     if(current->itemID==itemID)
                     { break;}
                     previous=current;
                     current=current->next;
            }

          int temp = current->quantity;
          current->name="canceled";
          current->quantity=0;
          current->rate=0;

           if(previous!=nullptr)
            previous->next = current->next;

            cout<<"\nItem canceled Successfully"<<endl;



         return temp;
      }

      int Update_quantity(long long int itemID)
      {


          int newquantity;
          int hash_index = HashFunc(itemID);
          int flag = 0;
         HashTableEntry* current = ht_b[hash_index];
         if (current != nullptr) {
            while (current != nullptr) {
               if (current->itemID == itemID) {
                  flag = 1;
               }
               if (flag==1) {

               cout<<"\nEnter new Quantity : ";
               cin>>newquantity;

               current->quantity = newquantity;
               cout<<"\n\nQuantity Updated Successfully! "<<endl;
               return newquantity;
               break;
               }
               current = current->next;
            }
         }
            if(flag==0)
               {
                   cout<<"\nNo Item found at this ItemID."<<endl;
                return 0;}
      }

       int get_quantity(long long int itemID)
     {
         int hash_index = HashFunc(itemID);
         HashTableEntry* current = ht_b[hash_index];
         if (current != nullptr) {
            while (current != nullptr) {
               if (current->itemID == itemID) {
                  return current->quantity;
                  break;}
               current = current->next;
            }
         }
         else
         { cout<<"\n Incorrect itemID ";
         return 0;}
     }





      int make_payment(long long int customerID,int points)
      {
          int tr;
          int total_amount=0;

          cout<<"****************************************************************"<<endl;
          cout<<"*************************** BILL *******************************"<<endl;
          cout<<"\nTransaction ID : "<<tr<<endl;
          cout<<"\nCustomer ID : "<<customerID<<endl;
          cout<<"\n\nITEM_ID    |   NAME        |       RATE       |      QUANTITY"<<endl;
          for(int i=0;i<T_S;i++)
          {
              if(ht_b[i]== nullptr)
              {
                  continue;
              }
              else
              {
                  HashTableEntry* current = ht_b[i];
                  while(current!= nullptr)
                  {
                      cout<<"\n "<<current->itemID<<"            "<<current->name<<"             Rs."<<current->rate<<"             "<<current->quantity<<endl;
                      total_amount = total_amount + ((current->rate)*(current->quantity));
                      current = current->next;

                  }

              }
               ht_b[i]=nullptr;
          }

          cout<<"\n\n-----------------------------------------------------------------"<<endl;
          cout<<"\n                                             Total Amount= Rs."<<total_amount<<endl;
          cout<<"\n-----------------------------------------------------------------"<<endl;

          cout<<"\n\n Updated points : "<<points + total_amount;
          cout<<"\n\n**************** THANK YOU FOR YOUR VISIT************************";
          cout<<"\n*****************************************************************";
          return points + total_amount;


      }


};

class customer
{

     public:
      HashTableEntry **ht_c;
      customer() {
         ht_c = new HashTableEntry*[T_S];
         for (int i = 0; i < T_S; i++)
            ht_c[i] = nullptr;
      }
      int HashFunc(long long int customerID)
      {
         return customerID % T_S;
      }

     void Add_customer(long long int customerID,string name, int points,int quantity) {

         int hash_index = HashFunc(customerID);
         HashTableEntry* previous = nullptr;
         HashTableEntry* current = ht_c[hash_index];
         while (current!= nullptr) {
            previous = current;
            current = current->next;
         }
         if (current == nullptr) {
            current = new HashTableEntry(customerID, name, points, quantity);
            if (previous == nullptr) {
               ht_c[hash_index] = current;
            } else {
               previous->next = current;
            }
         } else {
            current->name = name;
            current->rate = points;
            current->quantity = quantity;
         }
     }
        void Update_points(long long int customerID,int newpoints)
      {

          int hash_index = HashFunc(customerID);
          int flag = 0;
         HashTableEntry* current = ht_c[hash_index];
         if (current != nullptr) {
            while (current != nullptr) {
               if (current->itemID == customerID) {
                  flag = 1;
               }
               if (flag==1) {

               current->rate = newpoints;
               break;
               }
               current = current->next;
            }
         }
            if(flag==0)
                cout<<"\nINVALID CUSTOMER ID ";
      }

      int get_points( long long int customerID)
      {
           int hash_index = HashFunc(customerID);
         HashTableEntry* current = ht_c[hash_index];
         if (current != nullptr) {
            while (current != nullptr) {
               if (current->itemID == customerID) {
                  return current->rate;
                  break;}
               current = current->next;
            }
         }
         else
         { cout<<"\n Incorrect itemID ";
         return 0;}



      }




};





int main()
{
    inventory hash;
    billing hash2;
    int ch1;
    customer cus;
    string customerName;
    int points;
    long long int customerID;
    long long int itemID;
    string name;
    int rate;
    int quantity;
    int ch,mch,bch;
    int j=1;


    long long INVENTORY_DATASET[100][4] = {
{111100000001,1,100,20},{111100000002,2,110,20},{111100000003,3,120,20},{111100000004,4,130,20},{111100000005,5,140,20},{111100000006,6,150,20},{111100000007,7,160,20},{111100000008,8,170,20},{111100000009,9,180,20},{111100000010,10,190,20},
{111100000011,11,200,20},{111100000012,12,210,20},{111100000013,13,220,20},{111100000014,14,230,20},{111100000015,15,240,20},{111100000016,16,250,20},{111100000017,17,260,20},{111100000018,18,270,20},{111100000019,19,280,20},{111100000020,20,290,20},
{111100000021,21,300,20},{111100000022,22,310,20},{111100000023,23,320,20},{111100000024,24,330,20},{111100000025,25,340,20},{111100000026,26,350,20},{111100000027,27,360,20},{111100000028,28,370,20},{111100000029,29,380,20},{111100000030,30,390,20},
{111100000031,31,400,20},{111100000032,32,410,20},{111100000033,33,420,20},{111100000034,34,430,20},{111100000035,35,440,20},{111100000036,36,450,20},{111100000037,37,460,20},{111100000038,38,470,20},{111100000039,39,480,20},{111100000040,40,490,20},
{111100000041,41,500,20},{111100000042,42,510,20},{111100000043,43,520,20},{111100000044,44,530,20},{111100000045,45,540,20},{111100000046,46,550,20},{111100000047,47,560,20},{111100000048,48,570,20},{111100000049,49,580,20},{222200001111,50,590,20},
{222200001114,51,600,20},{222200001117,52,610,20},{222200001120,53,620,20},{222200001123,54,630,20},{222200001126,55,640,20},{222200001129,56,650,20},{222200001132,57,660,20},{222200001135,58,670,20},{222200001138,59,680,20},{222200001141,60,690,20},
{222200001144,61,700,20},{222200001147,62,710,20},{222200001150,63,720,20},{222200001153,64,730,20},{222200001156,65,740,20},{222200001159,66,750,20},{222200001162,67,760,20},{222200001165,68,770,20},{222200001168,69,780,20},{222200001171,70,790,20},
{222200001174,71,800,20},{222200001177,72,810,20},{222200001180,73,820,20},{222200001183,74,830,20},{222200001186,75,840,20},{222200001189,76,850,20},{222200001192,77,860,20},{222200001195,78,870,20},{222200001198,79,880,20},{222200001201,80,890,20},
{222200001204,81,900,20},{222200001207,82,910,20},{222200001210,83,920,20},{222200001213,84,930,20},{222200001216,85,940,20},{222200001219,86,950,20},{222200001222,87,960,20},{222200001225,88,970,20},{222200001228,89,980,20},{222200001231,90,990,20},
{222200001234,91,1000,20},{222200001237,92,1010,20},{222200001240,93,1020,20},{222200001243,94,1030,20},{222200001246,95,1040,20},{222200001249,96,1050,20},{222200001252,97,1060,20},{222200001255,98,1070,20},{222200001258,99,1080,20},{222200001261,100,1090,20},
};

for(int i=0;i<100;i++)
{
    itemID = INVENTORY_DATASET[i][0];
    int temp = INVENTORY_DATASET[i][1];
    name=to_string(temp);
    rate = INVENTORY_DATASET[i][2];
    quantity = INVENTORY_DATASET[i][3];
    hash.Add_item(itemID,name,rate,quantity);


}

long long CUSTOMER_DATASET[100][3] = {
{9400000001,1,0},{9400000002,2,0},{9400000003,3,0},{9400000004,4,0},{9400000005,5,0},{9400000006,6,0},{9400000007,7,0},{9400000008,8,0},{9400000009,9,0},{9400000010,10,0},
{9400000011,11,0},{9400000012,12,0},{9400000013,13,0},{9400000014,14,0},{9400000015,15,0},{9400000016,16,0},{9400000017,17,0},{9400000018,18,0},{9400000019,19,0},{9400000020,20,0},
{9400000021,21,0},{9400000022,22,0},{9400000023,23,0},{9400000024,24,0},{9400000025,25,0},{9400000026,26,0},{9400000027,27,0},{9400000028,28,0},{9400000029,29,0},{9400000030,30,0},
{9400000031,31,0},{9400000032,32,0},{9400000033,33,0},{9400000034,34,0},{9400000035,35,0},{9400000036,36,0},{9400000037,37,0},{9400000038,38,0},{9400000039,39,0},{9400000040,40,0},
{9400000041,41,0},{9400000042,42,0},{9400000043,43,0},{9400000044,44,0},{9400000045,45,0},{9400000046,46,0},{9400000047,47,0},{9400000048,48,0},{9400000049,49,0},{9400000050,50,0},
{9400000051,51,0},{9400000052,52,0},{9400000053,53,0},{9400000054,54,0},{9400000055,55,0},{9400000056,56,0},{9400000057,57,0},{9400000058,58,0},{9400000059,59,0},{9400000060,60,0},
{9400000061,61,0},{9400000062,62,0},{9400000063,63,0},{9400000064,64,0},{9400000065,65,0},{9400000066,66,0},{9400000067,67,0},{9400000068,68,0},{9400000069,69,0},{9400000070,70,0},
{9400000071,71,0},{9400000072,72,0},{9400000073,73,0},{9400000074,74,0},{9400000075,75,0},{9400000076,76,0},{9400000077,77,0},{9400000078,78,0},{9400000079,79,0},{9400000080,80,0},
{9400000081,81,0},{9400000082,82,0},{9400000083,83,0},{9400000084,84,0},{9400000085,85,0},{9400000086,86,0},{9400000087,87,0},{9400000088,88,0},{9400000089,89,0},{9400000090,90,0},
{9400000091,91,0},{9400000092,92,0},{9400000093,93,0},{9400000094,94,0},{9400000095,95,0},{9400000096,96,0},{9400000097,97,0},{9400000098,98,0},{9400000099,99,0},{9400000100,100,0},
};

for(int j=0;j<100;j++)
{
    customerID=CUSTOMER_DATASET[j][0];
    int temp1=CUSTOMER_DATASET[j][1];
    customerName=to_string(temp1);
    points=CUSTOMER_DATASET[j][2];

    cus.Add_customer(customerID,customerName,points,0);

}


    cout<<" WELCOME \n\n";

    while(j!=0)
    {
        int k=1,m=1;
        cout<<"\n Press 1 : Manager "<<endl;
        cout<<" Press 2 : Customer"<<endl;
        cout<<" Press 3 : To Exit "<<endl;
        cout<<" ENTER YOUR CHOICE : ";
        cin>>ch;

        switch(ch)
        {
        case 1 :
            {
                while(k!=0){
                cout<<"\n Press 1 : To Add item to store"<<endl;
                cout<<" Press 2 : To Delete item from store"<<endl;
                cout<<" Press 3 : To Update item Info. present in store "<<endl;
                cout<<" Press 4 : To get Product Info. present in store"<<endl;
                cout<<" Press 5 : To Exit"<<endl;
                cout<<" ENTER YOUR CHOICE : ";
                cin>>mch;

                switch(mch)
                {
                case 1 :
                    {
                        cout<<"\n\nItemID : ";
                        cin>>itemID;
                        cout<<"\nName : ";
                        cin>>name;
                        cout<<"\nRate : ";
                        cin>>rate;
                        cout<<"\nQuantity : ";
                        cin>>quantity;
                        hash.Add_item(itemID,name,rate,quantity);
                        break;

                    }
                case 2 :
                    {

                        cout<<"\n\nItemID : ";
                        cin>>itemID;
                        hash.Delete_item(itemID);
                        break;
                    }
                case 3 :
                    {
                        cout<<"\n\nItemID : ";
                        cin>>itemID;
                        hash.Update_item(itemID);
                        break;
                    }
                case 4 :
                    {

                        cout<<"\n\nItemID : ";
                        cin>>itemID;
                        hash.get_product_info(itemID);

                        break;
                    }
                case 5 :
                    {

                        k=0;
                        break;
                    }
                }
            }
            break;
        }

     case 2 :
    {
        while(m!=0){
            cout<<"\n\n Press 1: To add item in your cart "<<endl;
            cout<<" Press 2 : To remove item from cart"<<endl;
            cout<<" Press 3 : To update quantity "<<endl;
            cout<<" Press 4 : To make Payment "<<endl;
            cout<<" Press 5 : To Exit "<<endl;
            cout<<" ENTER YOUR CHOICE : ";
            cin>>bch;

            switch(bch)
            {
            case 1 :
                {
                    cout<<"\n\n Enter Item ID : ";
                    cin>>itemID;
                    cout<<"\n Enter Quantity : ";
                    cin>>quantity;
                    string nname=hash.get_name(itemID);
                    int rrate=hash.get_rate(itemID);

                    hash2.Buy_item(itemID,nname,rrate,quantity);
                    hash.Update_after_purchase(itemID,quantity,-1);

                    break;
                }
            case 2 :
                {
                    cout<<"\n\n Enter Item ID of product you want to remove from cart : ";
                    cin>>itemID;
                    int temp1=hash2.Cancel_item(itemID);
                    hash.Update_after_purchase(itemID,temp1,+1);
                    break;

                }
            case 3 :
                {
                    cout<<"\n\nEnter Item ID of product you want to update quantity: ";
                    cin>>itemID;
                    int oldquantity = hash2.get_quantity(itemID);
                    int newquantity = hash2.Update_quantity(itemID);
                    if(newquantity>oldquantity)
                        hash.Update_after_purchase(itemID,newquantity-oldquantity,-1);
                    if(oldquantity>newquantity)
                        hash.Update_after_purchase(itemID,oldquantity-newquantity,+1);

                    break;
                }
            case 4 :
                {

                    int points;
                     cout<<"\n Press 1 : if you are new customer ";
                     cout<<"\n Press 2 : if you are Regular customer ";
                     cout<<"\n ENTER YOUR CHOICE : ";
                     cin>>ch1;
                     if(ch1==1)
                    {
                       cout<<"\n Your Phone No. will your Customer ID, Enter your phone No. : ";
                       cin>>customerID;
                       cus.Add_customer(customerID,"noname",0,0);
                       points = 0;
                     }
                    if(ch1==2)
                   {
                      cout<<"\n Enter your Phone No. : ";
                      cin>>customerID;
                      points=cus.get_points(customerID);
                    }

                    int newpoints=hash2.make_payment(customerID,points);
                     cus.Update_points(customerID,newpoints);
                    break;
                }
            case 5 :
                {
                    m=0;
                    break;
                }
            }
        }
        break;

    }
     case 3 :
        {
            j=0;
            break;
        }
   }
}

return 0;
}
