#include <iostream>
#include <cstring>
#include <string>
#define SIZE 2
#define SIZE2 10
using namespace std;

class Admin;
class Reservation;
class Land;
class LandDetails;
class Payment;
class Customer;

class Admin{
  private:
    string AdminID;
    string AdminPassword;
    string Name;
    string NIC;
    string Email;
    Customer *C;
    Land *L;
    Reservation *R;
    Payment *P;
    
  public:
    Admin(string pAdminID,string pAdminPassword,string pName,string pNIC,string pEmail,Customer *pC, Land *pL, Reservation *pR,Payment *pP){
      AdminID=pAdminID;
      AdminPassword=pAdminPassword;
      Name=pName;
      NIC=pNIC;
      Email=pEmail;
      C=pC;
      L=pL;
      R=pR;
      P=pP;
      
    }
    void DisplayAdminDetails(){
      cout << "\n_______________________**ADMIN DETAILS**_______________________\n"<< endl;
      cout<<"Admin ID : "<<AdminID<<endl;
      cout<<"Admin Name : "<<Name<<endl;
      cout<<"Admin NIC : "<<NIC<<endl;
      cout<<"Admin Email : "<<Email<<endl;
      cout << "\n___________________________________________________________________\n"<< endl;
    }
    bool AdminLogin();
    void CheckCustomerDetails();
    void CheckLandDetails();
    void CheckReservationDetails();
    void displayPaymentDetails();
};

class Customer {
  protected:
    string UserName;
    string Password;
    string FirstName;
    string LastName;
    string NIC;
    string Email;
    long PhoneNumber;
    string Category;
    Land *addLand[SIZE2];
		int noOfLand;
    Reservation *ReservLand[SIZE2];
		int noOfReserv;
  public:
    Customer(string pUserName, string pPassword,string pFirstName,string pLastName, string pNIC,string pEmail,long pPhoneNumber,string pCategory) 
    { 
      UserName = pUserName;
      Password = pPassword;
      FirstName=pFirstName;
      LastName=pLastName;
      NIC=pNIC;
      Email=pEmail;
      PhoneNumber=pPhoneNumber;
      Category=pCategory;
      noOfLand = 0;
      noOfReserv = 0;
      
  }
  ~Customer(){cout<<"Customer Account Deleted\n\n";}
  virtual void DisplayCustomerDetails() {}
  void CustomerDetailsDisplay();
  bool Login();
  void purchaseALand(Land *La);
  void ReserveALand(Reservation *RE);
  void DisplayLanddetails();
  void DisplayReserLandDetails();
  void SearchALand();
};

class Seller : public Customer {
  protected:
    string SellerID;
  public:
    Seller(string pUserName, string pPassword,string pFirstName,string pLastName, string pNIC,string pEmail,long pPhoneNumber,string pCategory,string pSellerID) : Customer( pUserName,pPassword,pFirstName,pLastName,pNIC,pEmail,pPhoneNumber,pCategory) 
    {
      SellerID=pSellerID;
    }
    void DisplayCustomerDetails();
};

class Buyer : public Customer {
  private:
    string BuyerID;
  public:
    Buyer(string pUserName, string pPassword,string pFirstName,string pLastName, string pNIC,string pEmail,long pPhoneNumber,string pCategory, string pBuyerID): Customer(pUserName,pPassword,pFirstName,pLastName,pNIC,pEmail,pPhoneNumber,pCategory) 
    { 
      BuyerID=pBuyerID;
    }
    void DisplayCustomerDetails();
};

class LandDetails {
  private:
    string LandNo;
    float LandSize;
    bool Availability;
  public:
    LandDetails(string pLandNo, float pLandSize,bool pAvailability) {
       LandNo = pLandNo;
       LandSize=pLandSize;
       Availability=pAvailability;
    }
    ~LandDetails()
    {
      cout << "Deleting Land Details " << LandNo << endl;
    }
    void DisplayLandDetails();
    bool getAvalability();
    
};

class Land {
  private:
      string LandName;
      string LandLocation;
      long double LandPrice;
      LandDetails *l[SIZE]; 
      Customer *Custo;
  public:
    Land() {}
    Land(string pLandName,string pLandLocation, long double pLandPrice,string  LandNo1,  float LandSize1,bool Availability1, string  LandNo2,float LandSize2,bool Availability2,Customer *pCusto) {
        LandName=pLandName;
        LandLocation=pLandLocation;
        LandPrice=pLandPrice;
        l[0] = new LandDetails(LandNo1,LandSize1,Availability1);
        l[1] = new LandDetails(LandNo2,LandSize2,Availability2);

        Custo = pCusto;
        Custo->purchaseALand(this);
     }
    ~Land() 
    {
        cout << "Land Deleting " << endl;
        for (int r=0; r<SIZE; r++)
        {delete l[r];}           
        cout << "Delete Completed" << endl;
    }
    void DisplayLand();
    void ReservLandDetailsDisplay();
    float GetPrice(); 
};

class Reservation{
  private:
    int ReservationNo;
    string LandNo;
    float TotalPerches;
    string DateReservation;
    string TimeReservation;
    string Comment;
    Customer *Cust;
    Land *lan;
    Payment *Pay;
  public:
    Reservation(int pReservationNo,string pLandNo,float pTotalPerches,string pDateReservation,string pTimeReservation, string pComment,Customer *pCust,Land *plan,Payment *pPay)
    {
      ReservationNo=pReservationNo;
      LandNo=pLandNo;
      TotalPerches=pTotalPerches;
      DateReservation=pDateReservation;
      TimeReservation=pTimeReservation;
      Comment=pComment;
      
      Cust = pCust;
      Cust->ReserveALand(this);

      lan=plan;
      Pay=pPay;
    }
    ~Reservation()
    {
      cout<<"Reservation Deleted\n";
    }
    void getDate();
    float CalcReservLandAmount();
    void DisplayStatus();
    
};

class Payment{
  protected:
    string PaymentMethod;
    int PaymentId;
  public:
    Payment(string pPaymentMethod,int pPaymentId)
    {
      PaymentMethod=pPaymentMethod;
      PaymentId=pPaymentId;
      
    }
    ~Payment(){
      cout<<"Payment Details Deleted"<<endl;
    }
    void Authorize();
    virtual void DisplayPaymentDetails();
    void PaymentDisplay();
};

class Cash: public Payment{
private:
  string PaymentName;
  string Description;
public:
  Cash(string pPaymentMethod,int pPaymentId,string pPaymentName,string pDescription):Payment(pPaymentMethod,pPaymentId)
  {
    PaymentName=pPaymentName;
    Description=pDescription;

  }
  void DisplayPaymentDetails();
};

class Loan: public Payment{
private:
  string PaymentName;
  string Description;
public:
  Loan(string pPaymentMethod,int pPaymentId,string pPaymentName,string pDescription):Payment(pPaymentMethod,pPaymentId)
  {
    PaymentName=pPaymentName;
    Description=pDescription;
  }
  void DisplayPaymentDetails();
};
void Customer::CustomerDetailsDisplay()
{
  cout << "\n_______________________**CUSTOMER DETAILS**_______________________\n"<< endl;
    DisplayCustomerDetails();
    cout << "Full Name : Mr/Ms." <<FirstName<<" "<<LastName<< endl;
    cout << "NIC No : " <<NIC<< endl;
    cout << "Email Address : " <<Email<< endl;
    cout << "Phone Number : " <<PhoneNumber<< endl<< endl;
    cout << "\n___________________________________________________________________\n"<< endl;
} 

void Seller::DisplayCustomerDetails() 
{
    cout << "Seller ID: " <<SellerID<<endl;
}

void Buyer::DisplayCustomerDetails() 
{
    cout << "Buyer ID :" <<BuyerID<< endl;
}

void Customer::purchaseALand(Land *La)
{
        if (noOfLand < SIZE2)
        {
          addLand[noOfLand] = La;
          noOfLand++;
        }
           
}

void Customer::DisplayLanddetails()
{
  cout << "\n_______________________**LAND DETAILS**_______________________\n"<< endl;
    for( int i = 0; i < noOfLand; i++)
    {
      addLand[i]-> DisplayLand();
    }
    cout << "\n______**Land Owner Details**______\n"<< endl;
    DisplayCustomerDetails();
    cout << "Full Name : Mr/Ms." <<FirstName<<" "<<LastName<< endl;
    cout << "\n___________________________________________________________________\n"<< endl;
}

 void Customer::ReserveALand(Reservation *RE)
{
        if (noOfLand < SIZE2)
           ReservLand[noOfReserv] = RE;
        noOfReserv++;
}

void Customer::DisplayReserLandDetails()
{
  cout << "\n_______________________**RESERVATION STATUS**_______________________\n"<< endl;
    for( int i = 0; i < noOfReserv; i++)
    {
      ReservLand[i]-> DisplayStatus();
    }
    cout << "\n______**Buyer Details**______\n"<< endl;
    DisplayCustomerDetails();
    cout << "Full Name : Mr/Ms." <<FirstName<<" "<<LastName<< endl;
    cout << "\n___________________________________________________________________\n"<< endl;
}

void LandDetails::DisplayLandDetails() 
{
       cout << "Land No : " << LandNo << endl;
       cout << "Land Size(perches) : " << LandSize << endl;
}

void Land::DisplayLand() 
{
      cout <<"Land Name :" <<LandName<<endl;
      cout <<"Land Location :" <<LandLocation<<endl;
      cout << "Land(per Perch) Price(LKR) : " << LandPrice << endl;
      for (int r=0; r<SIZE; r++)
      {
         l[r]->DisplayLandDetails();
      }
}

void Land::ReservLandDetailsDisplay()
{
  cout <<"Land Name :" <<LandName<<endl;
}
float Land::GetPrice()
{
  return LandPrice;
}

void Reservation::getDate()
{
}

void Reservation::DisplayStatus()
{
      lan->ReservLandDetailsDisplay();
      cout <<"Reservation Number : " <<ReservationNo <<endl;
      cout <<"Reservation Land No : " <<LandNo <<endl;
      cout <<"Reservation Date : " <<DateReservation <<endl;
      cout <<"Reservation Time : "<<TimeReservation<<endl;
      cout<<"Reservation Comment : "<<Comment<<endl;
      cout<<"Reserved Land Perches : "<<TotalPerches<<endl;
      cout<<"Reserved Land Price(LKR) : "<<CalcReservLandAmount()<<endl;
      Pay->DisplayPaymentDetails();
}

float Reservation::CalcReservLandAmount()
{
  
  return TotalPerches*lan->GetPrice();

}



void Payment::Authorize()
{
}
void Payment::DisplayPaymentDetails()
{

}
void Cash::DisplayPaymentDetails()
{
  cout<<"Payment Type : "<<PaymentName<<endl;
  cout<<"Payment Description : "<<Description<<endl;
}

void Loan::DisplayPaymentDetails()
{
  cout<<"Payment Type : "<<PaymentName<<endl;
  cout<<"Payment Description : "<<Description<<endl;
}
void Payment::PaymentDisplay()
{
    cout<<"Payment ID : "<<PaymentId<<endl;
    DisplayPaymentDetails();
}

void Admin::displayPaymentDetails()
{
  
}
void Admin::CheckCustomerDetails()
{

}
void Admin::CheckLandDetails()
{
  
}
void Admin::CheckReservationDetails()
{

}



int main()
{
Admin *AdObj;
Customer *CusObj[2];//create a 2 array object because need to assing the data for both 2 ways 
Land *LandObj;
Reservation *ReservObj;
Payment *PayObj[2];

//to Assing Payment Details
PayObj[0] = new Cash("CASH",001,"Cash in Hand","You can pay in your money");
PayObj[1] = new Loan("LOAN",002,"Bank Loan","You can Get a Bank Loan");

CusObj[0] = new Seller("Cus@001","password","Amila","Devin","961010789V","amiladevin@gmail.com",94776659628,"Customer","Seller001");//if customer Login as a Seller

CusObj[1] = new Buyer("Cus@002","password","Hashini","Imeshika","961210734V","hashiniimeshika@gmail.com",94757012345,"Buyer001","Buyer001");//if customer Login as a Buyer

//to Assing Land Details 
LandObj = new Land("Colombo Luxury","Colombo",100000.00,"CMBL01",20,true,"CMBL02",25.5,true,CusObj[0]);

//To Assing Reservation Details
ReservObj = new Reservation(001,"CMBL01",10,"2020/05/20","14.02PM", "Comment",CusObj[1],LandObj,PayObj[0]);

AdObj = new Admin("Admin001","adminpassword","Tharanga","8712345678V","tharanga@gmail.com",CusObj[0],LandObj, ReservObj,PayObj[1]);
AdObj->DisplayAdminDetails();


//to Display Customer Details
for (int i=0;i<2; i++)
{
CusObj[i]->CustomerDetailsDisplay();
}

CusObj[0]->DisplayLanddetails();//To display Land Details

//To Display All Payment Methods
cout<<"\n_______________________**PAYMENT METHODS**_______________________\n";
PayObj[0]->PaymentDisplay();
cout<<endl;
PayObj[1]->PaymentDisplay();
cout<<"\n___________________________________________________________________\n";

cout<<endl;

CusObj[1]->DisplayReserLandDetails();//to Display Reservation Details
cout<<endl;

//As a Admin: Can Delete All the Objects
//As a Seller: Can Delete Land details and Customer details only
//As a Buyer : Can Delete Reservation Details and Customer Details only
delete ReservObj;
delete LandObj;	
cout<<endl;
delete CusObj[0];
delete CusObj[1];
delete PayObj[0];
delete PayObj[1];

//char ch;
//cin >> ch;
return 0;
}



