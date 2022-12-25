/* 
TITLE: INVENTORY CONTROL SYSTEM
Author: SAYED MUSHAHID RAZA QUADRI
Date: 13th of November 2020
Language: C++
*/

#include<iostream>
#include<fstream>
#include<string.h>
#define MAX 5
#define MAX_ORDER 3
#define EXIT_SUCCESS 0
using namespace std;

//GLOBAL VARIABLES
int cus_count, sup_count, prod_count,purch_count;	//TOTAL NO. OF CUSTOMERS, SUPPLIERS & PRODUCTS


//Class Definations
/*----------------------------------------------------------*/
//ABSTRACT CLASS STARTS
class Person		
{
	public:
		int id;
		char name [25];
		char direction [100];
	
		Person ()
		{
			id=-1;
			strcpy(this->name,"\0");
			strcpy(this->direction,"\0");
		}
		
		Person(int i,char n [25],char dir[100])	//POLYMORPHISM
		{
			strcpy(this->name,n);
			strcpy(this->direction,dir);
			this->id=i;
		}
		
		virtual void print() = 0; //Pure Virtual Function To Make Class Abstract (ABSTRACTION)		
};
//ABSTRACT CLASS ENDS HERE!

/*----------------------------------------------------------*/

//Class Customer Starts Here
class Customer : public Person	//Inherits Person
{
		
	public:
		Customer()
		{
			//NEEDS TO DO NOTHING
		}
		
		Customer(int i, char n[25], char dir[100]) : Person(i,n,dir)
		{
			//this->customer_count++;
			//this->WriteDataToFile();
			//No Work Required Here
		}
		
		void AddCustomer(int i, char n[25], char dir[100])
		{
			strcpy(this->name,n);
			strcpy(this->direction,dir);
			this->id=i;
			//this->WriteDataToFile();
		}

		void DeleteCustomer()
		{
			strcpy(this->name,"\0");
			strcpy(this->direction,"\0");
			this->id=-1;
		}
		
		void WriteDataToFile()
		{
			ofstream customer;
			customer.open ("customer.txt",ios::app);
			customer<<this->id<<" "<<this->name<<" "<<this->direction<<endl;
			customer.close();
		}
				
		void print()
		{
			cout<<"Customer ID: "<<this->id<<endl
				<<"Customer Name: "<<this->name<<endl
				<<"Customer Direction: "<<this->direction<<endl<<endl;
		}	
};
//Class Customer Ends Here

/*----------------------------------------------------------*/

//Class Supplier Starts Here
class Supplier: public Person		//INHERITS PERSON
{
	
	public:
		Supplier()
		{
			//Left Blank
		}
		
		Supplier(int i, char n[25], char dir[100]):Person(i,n,dir)
		{
			//this->WriteDataToFile();	
		}
		
		void AddSupplier(int i, char n[25], char dir[100])
		{
			strcpy(this->name,n);
			strcpy(this->direction,dir);
			this->id=i;
			//this->WriteDataToFile();
		}

		void DeleteSupplier()
		{
			strcpy(this->name,"\0");
			strcpy(this->direction,"\0");
			this->id=-1;
		}
		
		void WriteDataToFile()
		{
			ofstream supplier;
			supplier.open ("supplier.txt",ios::app);
			supplier<<this->id<<" "<<this->name<<" "<<this->direction<<endl;
			supplier.close();
		}
		
		void print()
		{
			cout<<"Supplier ID: "<<this->id<<endl
				<<"Supplier Name: "<<this->name<<endl
				<<"Supplier Direction: "<<this->direction<<endl<<endl;
		}
};
//Class Supplier Ends Here

/*----------------------------------------------------------*/

//Class Product Starts Here
class Product
{
	private:
		int pro_id;
		char name[25];
		int supplier_id;
		char descrp[100];
		float price;
	public:
		Product()
		{
			pro_id = -1;
			strcpy(name,"\0");
			strcpy(descrp,"\0");
			supplier_id = 0;
			price = 0;
		}
		
		Product(int pro, char n[25], float p, char d[100], int s)
		{
			this->pro_id=pro;
			strcpy(this->name,n);
			strcpy(this->descrp,d);
			this->supplier_id = s;
			this->price = p;
		}
		
		void AddProduct(int pro, char n[25], float p, char d[100], int s)
		{
			this->pro_id=pro;
			strcpy(this->name,n);
			strcpy(this->descrp,d);
			this->supplier_id = s;
			this->price = p;
			//this->WriteDataToFile();
		}
				
		void WriteDataToFile()
		{
			ofstream product;
			product.open ("product.txt",ios::app);
			product<<this->pro_id<<" "<<this->name<<" "<<this->descrp<<" "<<this->price<<" "<<this->supplier_id<<endl;
			product.close();
		}
		
		int GetID()
		{
			return pro_id;
		}
		
		char* GetName()
		{
			return name;
		}
		
		float GetPrice()
		{
			return price;
		}
		
		void print()
		{
			cout<<"Product ID: "<<this->pro_id<<endl
				<<"Product Name: "<<this->name<<endl
				<<"Product Price: "<<this->price<<endl
				<<"Supplier ID: "<<this->supplier_id<<endl
				<<"Product Description: "<<this->descrp<<endl<<endl;
		}
};
//Class Product Ends Here

/*----------------------------------------------------------*/

//Class Purchasing Starts Here
class Purchasing
{
	private:		
	int cus_id;
	int item_count;
	int prod_id[MAX_ORDER];
 	char name [MAX_ORDER][25];
	int qty [MAX_ORDER];
	float price[MAX_ORDER];
	float total_price;
	
	public:
		Purchasing()
		{
			this->cus_id = 0;
			this->item_count = 0;
			this->total_price = 0;
		}
				
		int AddItem(int pro_id, int qty, int cus, Product products[])
		{
			bool found = false;
			for(int i=0;i<prod_count;i++)
			{
				if (products[i].GetID() == pro_id)
				{
					found = true;
					this->prod_id[item_count] = pro_id;
					this->price[item_count] = products[i].GetPrice();
					this->qty[item_count] = qty;
					strcpy(this->name[item_count],products[i].GetName());
					item_count++;
				}	
			}
			
			if(found == false)
			{
				cout<<"Error: Product Not Found!"<<endl;
				return 0;
			}
			this->cus_id = cus;
			return 1;
		}
		
		float CaluclateTotalPrice()
		{
			for(int i=0;i<item_count;i++)
			{
				total_price = total_price + (qty[i]*price[i]);	
			}
		}
		
		void GenerateBill(int pur_ord)
		{
			ofstream bill;
			bill.open ("bill.txt",ios::app);
			
			bill<<"Purchasing Order # "<< pur_ord+1<<endl<<endl;
			cout<<"Purchasing Order # "<< pur_ord+1<<endl<<endl;
			bill<<"Sno.\tItemName\tQty\tPrice"<<endl;
			cout<<"Sno.\tItemName\tQty\tPrice"<<endl;
			for(int i=0;i<item_count;i++)
			{
				bill<<i+1<<"\t"<<name[i]<<"\t\t"<<qty[i]<<"\t"<<price[i]<<endl;
				cout<<i+1<<"\t"<<name[i]<<"\t\t"<<qty[i]<<"\t"<<price[i]<<endl;
			} 
			this->CaluclateTotalPrice();
			cout<<endl<<endl<<"TOTAL PRICE = "<<total_price<<endl;
			bill<<endl<<endl<<"TOTAL PRICE = "<<total_price<<endl;
			bill.close();
		}
		
};
//Class Purchasing Ends Here

/*----------------------------------------------------------*/

//Class Sale Starts Here
class Sale
{
	private:
	float total_sale;	//total sale from bills
	int count;
	
	public:
		Sale()
		{
			total_sale = 0;
		}
		
		void GenerateSalesReport()
		{
			ifstream sale;
			sale.open("bill.txt");
			string line;
			cout<<"SALES REPORT:"<<endl<<endl;
			while(!sale.eof())
			{
				getline(sale,line);
				cout<<line<<endl;
			}
		}
};
//Class Sale Ends Here

/*----------------------------------------------------------*/
//CLASS DEFINATIONS ENDED HERE



//Additional Helper Functions Begins

void InitiateSystem(Customer customers[], Supplier suppliers[], Product products[],Purchasing purchasing[], Sale sales)
{
	cout<<"Initating Load Data ... Please Wait!"<<endl;
	
	//FOR CUSTOMERS
	//int cus_count;
	ifstream customer;
	customer.open("customer.txt");
	customer>>cus_count;
	cout<<cus_count<<endl;
	int cus_id;
	char cus_name[25], cus_direct[100];
	for (int i=0;i<cus_count;i++)
	{
		customer>>cus_id>>cus_name>>cus_direct;
		customers[i].AddCustomer(cus_id,cus_name,cus_direct);
		//cout<<id<<" "<<name<<" "<<direct<<" "<<endl;
		//customers[i].print();	
	}
	customer.close();
	
	
	//FOR SUPPLIERS
	//int sup_count;
	ifstream supplier;
	supplier.open("supplier.txt");
	supplier>>sup_count;
	cout<<sup_count<<endl;
	int sup_id;
	char sup_name[25], sup_direct[100];
	for (int i=0;i<sup_count;i++)
	{
		supplier>>sup_id>>sup_name>>sup_direct;
		suppliers[i].AddSupplier(sup_id,sup_name,sup_direct);
	}
	supplier.close();
	
	//FOR PRODUCTS
	//int prod_count;
	ifstream prod;
	prod.open("product.txt");
	prod>>prod_count;
	cout<<prod_count<<endl;
	int prod_id,prod_sup_id;
	char prod_name[25], prod_des[100];
	float prod_price;
	for (int i=0;i<prod_count;i++)
	{
		prod>> prod_id>>prod_name>>prod_des>>prod_price>>prod_sup_id;
		products[i].AddProduct(prod_id,prod_name,prod_price,prod_des,prod_sup_id);
	}
	prod.close();
	
	system("cls");
}

void AddCustomer(Customer customers[])
{
	system("cls");
	int choice;
	cout<<"Press 1 To Add Customer"<<endl
		<<"Press 0 To Return Back"<<endl<<endl
		<<"Enter Your Choice: ";
	cin>>choice;
	while (!(choice != 0 || choice !=1))
	{
		cout<<"Error: Kindly Re-Enter Choice: ";
		cin>>choice;
	}
	
	if (choice == 1)
	{
		int id;
		char name[25];
		char direction[100];
		
		cout<<"Enter Customer ID: ";
		cin>>id;
		cout<<"Enter Customer Name: ";
		cin>>name;
		cout<<"Enter Customer Direction: ";
		cin>>direction;
		cout<<endl;
		
		//Check if Entered id is not already taken
		bool found = false;
		for(int i=0; i<cus_count;i++)
		{
			if(customers[i].id == id)
			{		
				found = true;
				break;
			}
		}
		if (found==false)
		{
			customers[cus_count++].AddCustomer(id,name,direction);
		}
		cout<<"User Already Exists!"<<endl;
		system("PAUSE");
	}
	
}

void AddSupplier(Supplier suppliers[])
{
	system("cls");
	int choice;
	cout<<"Press 1 To Add Supplier"<<endl
		<<"Press 0 To Return Back"<<endl<<endl
		<<"Enter Your Choice: ";
	cin>>choice;
	while (!(choice != 0 || choice !=1))
	{
		cout<<"Error: Kindly Re-Enter Choice: ";
		cin>>choice;
	}
	
	if (choice == 1)
	{
		int id;
		char name[25];
		char direction[100];
	
		cout<<"Enter Supplier ID: ";
		cin>>id;
		cout<<"Enter Supplier Name: ";
		cin>>name;
		cout<<"Enter Supplier Direction: ";
		cin>>direction;
		cout<<endl;
		
		//Check if Entered id is not already taken
		bool found = false;
		for(int i=0; i<sup_count;i++)
		{
			if(suppliers[i].id == id)
			{		
				found = true;
				break;
			}
		}
		if (found==false)
		{
			suppliers[sup_count++].AddSupplier(id,name,direction);
		}
		cout<<"Supplier Already Exists!"<<endl;
		system("PAUSE");
	}
}

void AddProduct(Product products[])
{
	system("cls");
	int choice;
	cout<<"Press 1 To Add Product"<<endl
		<<"Press 0 To Return Back"<<endl<<endl
		<<"Enter Your Choice: ";
	cin>>choice;
	while (!(choice != 0 || choice !=1))
	{
		cout<<"Error: Kindly Re-Enter Choice: ";
		cin>>choice;
	}
	
	if (choice == 1)
	{	//TEMP VARIABLES
		int id;
		int sup_id;
		float price;
		char name[25];
		char des[100];
		
		cout<<"Enter Product ID: ";
		cin>>id;
		cout<<"Enter Product Name: ";
		cin>>name;
		cout<<"Enter Product Price: ";
		cin>>price;
		cout<<"Enter Product Description: ";
		cin>>des;
		cout<<"Enter Product's Supplier ID: ";
		cin>>sup_id;
		cout<<endl;
		
		//Check if Entered id is not already taken
		bool found = false;
		for(int i=0; i<prod_count;i++)
		{
			if(products[i].GetID() == id)
			{		
				found = true;
				break;
			}
		}
		if (found==false)
		{
			products[prod_count++].AddProduct(id,name,price,des,sup_id);
		}
		cout<<"Product Already Exists!"<<endl;
		system("PAUSE");
	}
}

void MakePurchasing(Purchasing purchasing[],Product products[])
{
	system("cls");
	int choice;
	cout<<"Press 1 To Add Item To Purchase"<<endl
		<<"Press 0 To Return Back"<<endl<<endl
		<<"Enter Your Choice: ";
	cin>>choice;
	while (!(choice != 0 || choice !=1))
	{
		cout<<"Error: Kindly Re-Enter Choice: ";
		cin>>choice;
	}
	int cus,qty,prod;
	if (choice==1)
	{
		system("cls");
		cout<<"Enter Customer ID: ";
		cin>>cus;
		cout<<"Enter Product ID: ";
		cin>>prod;
		cout<<"Enter Quantity: ";
		cin>>qty;
		if(purchasing[purch_count].AddItem(prod,qty, cus,products))
		{
			cout<<"Item Added Successfully"<<endl;
			for (int i=0; i<MAX_ORDER-1;i++)
			{
				system("cls");
				int choice;
				cout<<"Press 1 To Add Item To Purchase"<<endl
					<<"Press 0 To Return Back"<<endl<<endl
					<<"Enter Your Choice: ";
				cin>>choice;
				while (!(choice != 0 || choice !=1))
				{
					cout<<"Error: Kindly Re-Enter Choice: ";
					cin>>choice;
				}
				int cus,qty,prod;
				if (choice==1)
				{
					system("cls");
					cout<<"Enter Product ID: ";
					cin>>prod;
					cout<<"Enter Quantity: ";
					cin>>qty;
					if(purchasing[purch_count].AddItem(prod,qty, cus,products))
						cout<<"Item Added Successfully"<<endl;
				}
				else
					break;
			}
			system("cls");
			purchasing[purch_count].GenerateBill(purch_count);
		}

	}
	return;
	
}

void GenerateSalesReport(Sale sales)
{
	system("cls");
	sales.GenerateSalesReport();
}

void ShowEverything()
{
	system("cls");
	int choice;
	cout<<"Press 1 To See Customers' Data"<<endl
		<<"Press 2 To See Suppliers' Data"<<endl
		<<"Press 3 To See Products' Data"<<endl
		<<"Press 0 To Return Back"<<endl<<endl
		<<"Enter Your Choice: ";
	cin>>choice;
	while (!(choice>=0 && choice<=3))
	{
		cout<<"ERROR INVALID CHOICE KINDLY RE-ENTER: ";
		cin>>choice;
	}
	
	if (choice == 1)
	{
		system("CLS");
		ifstream myfile;
		myfile.open("customer.txt");
		string line;
		cout<<"CUSTOMERS DATA:"<<endl<<endl;
		while(!myfile.eof())
		{
			getline(myfile,line);
			cout<<line<<endl;
		}
	}
	
	else if (choice == 2)
	{
		system("CLS");
		ifstream myfile;
		myfile.open("supplier.txt");
		string line;
		cout<<"SUPPLIERS DATA:"<<endl<<endl;
		while(!myfile.eof())
		{
			getline(myfile,line);
			cout<<line<<endl;
		}
	}
	
	else if(choice == 3)
	{
		system("CLS");
		ifstream myfile;
		myfile.open("product.txt");
		string line;
		cout<<"PRODUCTS DATA:"<<endl<<endl;
		while(!myfile.eof())
		{
			getline(myfile,line);
			cout<<line<<endl;
		}
	}
	else
		return;
	system("PAUSE");
	
}


void ShowMenu(Customer customers[], Supplier suppliers[], Product products[],Purchasing purchasing[], Sale sales)
{
	cout<<"WELCOME TO INVENTORY CONTROL SYSTEM"<<endl<<endl
		<<"Press 1 To Add Customer"<<endl
		<<"Press 2 To Add Supplier"<<endl
		<<"Press 3 To Add Product"<<endl
		<<"Press 4 To Make Purchasing"<<endl
		<<"Press 5 To Generate Sales Report"<<endl
		<<"Press 6 To See Customers, Suppliers, Products"<<endl
		<<"Press 0 To Exit"<<endl<<endl
		<<"Enter Your Choice: ";
	
	int choice = -1;
	cin>>choice;
	while (!(choice>=0 && choice<=6))
	{
		cout<<"ERROR INVALID CHOICE, RE ENTER: ";
		cin>>choice;
	}
	
	//Calling For Appropriate Functions For Given Menu
	switch (choice)
	{
		case 0:
			return;
		case 1:
			{
				AddCustomer(customers);
				break;
			}
			
		case 2:
			{
				AddSupplier(suppliers);
				break;
			}
		case 3:
			{
				AddProduct(products);	
				break;
			}
		case 4:
			{
				MakePurchasing(purchasing,products);
				break;
			}
		case 5:
			{
				GenerateSalesReport(sales);
				break;
			}
		case 6:
			{
				ShowEverything();
			}
		default: cout<<"ERROR!"<<endl;
		}
		
		system("cls");
		ShowMenu(customers,suppliers,products,purchasing,sales);	
}


void TerminateSystem(Customer customers[], Supplier suppliers[], Product products[],Purchasing purchasing[], Sale sales)
{
	cout<<"TERMINATE SYSTEM INITIATED"<<endl
		<<"Please Wait... Savings Files"<<endl;
	
	//FOR CUSTOMERS
	ofstream cus;
	cus.open("customer.txt");
	cus<<cus_count<<endl;
	cus.close();
	for (int i=0;i<cus_count;i++)
	{
		customers[i].WriteDataToFile();
	}
	
	
	//FOR SUPPLIERS
	ofstream sup;
	sup.open("supplier.txt");
	sup<<sup_count<<endl;
	sup.close();
	for (int i=0;i<sup_count;i++)
	{
		suppliers[i].WriteDataToFile();
	}


	//FOR PRODUCTS
	ofstream prod;
	prod.open("product.txt");
	prod<<prod_count<<endl;
	prod.close();
	for (int i=0;i<prod_count;i++)
	{
		products[i].WriteDataToFile();
	}

	
	//FOR PURCHASING
	
	
	//FOR SALES
	
	cout<<"GOOD BYE!"<<endl<<endl;
}


//Driver Code
int main ()
{
	//DECLARATIONS
	Customer customers[MAX];
	Supplier suppliers[MAX];
	Product products[MAX];
	Purchasing purchasing[MAX];
	Sale sales;
	
	InitiateSystem(customers,suppliers,products,purchasing,sales);	//LOAD EXISTING DATA FROM FILES
	
	ShowMenu(customers,suppliers,products,purchasing,sales);		//SHOWS CHOICES AND RUN OPERATIONS
	
	TerminateSystem(customers,suppliers,products,purchasing,sales);	//STORE UPDATED DATA BACK TO FILES FOR FUTURE USE
	return EXIT_SUCCESS;

}
