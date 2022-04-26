#include<iostream>
#include<sstream>
#include<fstream>
#include <set>


using namespace std;

class Book
{	
	string bid, name, author, publisher;
	
	public:
		Book() {}  // Default Constructer
		Book(string bid, string name,string author, string publisher,bool writeToFile)
		// Parameterized Constructor
		{
			this->bid=bid;
			this->name=name;
			this->author=author;
			this->publisher=publisher;
			
			if(writeToFile)
			{
				ofstream out;
				out.open("Book.txt", std::fstream::app);
				out<<bid<<" "<<name<<" "<<author<<" "<<publisher<<endl;
				out.close();
			}
		}
};


class User:public Book
{
	protected:
		string eno,name,phone,email,pass,enroll,password;
	
	public:
		User(){}
		User(string eno,string name, string phone, string email,string pass, bool writeToFile)
		{
			this->eno = eno;
			this->pass = pass;
			this->name = name;
			this->phone = phone;
			this->email = email;
			
			if(writeToFile)
			{
				ofstream out;
				out.open("User.txt", std::fstream::app);
				out<<eno<<" "<<name<<" "<<phone<<" "<<email<<" "<<pass<<endl;
				out.close();
			}
		}
		
		
		
		void signup()
		{
			system("clear");
			//cout<<"Enter Enrollment :-> ";
			//cin>>eno;
			cout<<"Enter First Name :-> ";
			cin>>name;
			cout<<"Enter Password :-> ";
			cin>>pass;
			cout<<"Enter Contact no :-> ";
			cin>>phone;
			cout<<"Enter Email Id :-> ";
			cin>>email;
			
			int flag = 0;
			string key;
			key=eno;
			ifstream in;
			in.open("User.txt");
			
 			set<int> s1; // declaring Set s1
 			int max_element;

 
			while(!in.eof())
			{
				 	string book;
					getline(in,book);
	
					if(book.length() > 0)
					{
						
						stringstream ss(book);
						string bid, name, author, publisher;
						
						ss>>bid>>name>>author>>publisher;
				
						int num=stoi(bid);
						s1.insert(num);
						   						
						cout<<endl;
						
					}
			}
				

			while(!in.eof())
			{

				string user;
				getline(in,user);
	
				if(user.length() > 0)
				{
	   				stringstream ss(user);
	   				string eno, name, phone, email;
	   				ss>>eno>>name>>phone>>email;
			
	   				if(eno == key)
					{
						flag = 1;
						cout<<"User Already Exixts..";
						in.close();
						break;
					}			
				}
			}
			if(flag == 0)
				{
					 if (!s1.empty())
        				max_element = *(s1.rbegin());
        				//cout<<"sadsadasdsadasd  "<<max_element;
        				int id=max_element + 1;
        				
        				eno= to_string(id);
					User user(eno,name, phone, email, pass, true);
			
					fstream out;
					out.open("user_sign.txt",std::fstream::app);
					out<<eno<<" "<<pass<<endl;
					out.close();
			
					cout<<endl<<"***** Successfully Created User account *****"<<endl;
					cout<<"\n\n";
					
				}	

		}
		
		
		void signin()
		{
			system("clear");
			int check=-1;
			cout<<endl<<"Enter Enrollment: ";
			cin>>eno;
			cout<<"Enter Password: ";
			cin>>pass;
			
			int flag=0;
			ifstream in;
			in.open("user_sign.txt");
			
			if(in.eof())
			{
				cout<<endl<<"!!!  No User present in the record  !!!"<<endl;	
			}
			else
			{
				while(!in.eof())
				{
					string user;
					getline(in,user);
	
					if(user.length() > 0)
					{
						stringstream ss(user);
						ss>>enroll>>password;
						
						if(enroll==eno && password==pass)
						{
							flag=1;
							cout<<endl<<"***** Successfully logged in as User *****"<<endl;
							while(check!=0)
							{
								cout<<endl<<"Available Choices :"<<endl<<endl;
								cout<<endl<<"1 - View All Books"<<endl;
								cout<<"2 - Issue Book"<<endl;
								cout<<"3 - Issued Books"<<endl;
								cout<<"4 - Return Book"<<endl;
								cout<<"0 - Logout"<<endl;
								
								cout<<endl<<"Enter your choice :-> ";
								cin>>check;
								
								switch(check)
								{
									case 1: viewAllBooks();
										break;
									case 2: issueBook();
										break;
									case 3: viewMyIssuedBooks();
										break;
									case 4: returnBook();
										break;
									default: cout<<endl<<"User logged Out Successfully..\n"<<endl;
								}
							}
						}
					}
				}
				if(flag==0)
				{
					cout<<endl;
					cout<<"!!!  User not found  !!!"<<endl<<endl;
				}
			}
			in.close();
		}
		
		
		
		void returnBook()
		{
			system("clear");
			cout<<endl<<"Your Bookshelf : "<<endl<<endl;
			viewMyIssuedBooks();
			
			ofstream out;
			out.open("temp.txt", std::fstream::out);
			
			int flag = 0;
			string key1, key2;
			
			cout<<endl;
			cout<<"Enter Enrollment no :-> ";
			cout<<enroll<<endl;
			cout<<"Enter Book Id :-> ";
			cin>>key2;
			
			ifstream in;
			in.open("Issued_Books.txt");
	
			if(in.eof())
			{
				cout<<endl<<"!!!  No data present in the record  !!!"<<endl;	
			} 
			else 
			{
				while(!in.eof())
				{
					string issue;
					getline(in,issue);
	
					if(issue.length() > 0)
					{
						stringstream ss(issue);
						string eno, bid;
						ss>>eno>>bid;
			
						if(eno == enroll && bid == key2)
						{
							flag = 1;
						}
						else
						{
							out<<enroll<<" "<<bid<<endl;
						}
					}
				}
				
				if(flag == 0)
				{
					cout<<endl;
					cout<<"!!!  No Records found  !!!"<<endl;
				}
				else
				{
					cout<<endl;
					cout<<"***** Returned successfully *****"<<endl;
				}
			}
	
			
			in.close();
			out.close();
			
			remove("Issued_Books.txt");
			rename("temp.txt","Issued_Books.txt");
		}
		
		
		
		
		void viewAllBooks()
		{
			system("clear");
			ifstream in;
			in.open("Book.txt");
	
			if(in.eof())
			{
				cout<<endl<<"!!!  No book present in shelf  !!!"<<endl;	
			}
			else
			{
				while(!in.eof())
				{
					string book;
					getline(in,book);
	
					if(book.length() > 0)
					{
						stringstream ss(book);
						string bid, name, author, publisher;
						ss>>bid>>name>>author>>publisher;
				
						cout<<endl;
						cout<<"Book Id :-> "<<bid<<endl;
						cout<<"Name :-> "<<name<<endl;
						cout<<"Author :-> "<<author<<endl;
						cout<<"Publisher :-> "<<publisher<<endl;
					}
				}
			}
			in.close();
		}
		
		
		
		
		void issueBook()
		{	
			system("clear");
			int flag=0;
			viewAllBooks();
		
			string eno, bid;
			
			cout<<endl;
			cout<<"Enter Enrollment no :-> ";
			cout<<enroll<<endl;
			cout<<"Enter Book Id :-> ";
			cin>>bid;
			
			ifstream in;
			in.open("Book.txt");
			while(!in.eof())
			{
				string book;
					getline(in,book);
	
					if(book.length() > 0)
					{
						stringstream ss(book);
						string b_id;
						ss>>b_id;
						
						if(b_id==bid)
						{
							flag=1;
							cout<<endl<<"***** Book issued Successfully *****"<<endl;							
							ofstream out;
							out.open("Issued_Books.txt", std::fstream::app);
							out<<enroll<<" "<<bid<<endl;
							out.close();
						}					
					}						
			}	
			if(flag==0)
						cout<<endl<<"!!!  Requested Book is not available  !!"<<endl;
			in.close();
		}
		
		
		
		
		void viewMyIssuedBooks()
		{
			system("clear");
			int flag=0;
			ifstream in;
			in.open("Issued_Books.txt");
	
			if(in.eof())
			{
				cout<<endl<<"!!!  No Issue present in the record  !!!"<<endl;	
			}
			else
			{
				while(!in.eof())
				{
					string book;
					getline(in,book);
	
					if(book.length() > 0) 
					{
						stringstream ss(book);
						string eno,bid;
						ss>>eno>>bid;
						
						if(enroll==eno)
						{
							cout<<endl;
							flag=1;
							cout<<"Name :-> "<<eno<<endl;
							cout<<"Book Id :-> "<<bid<<endl;	
						}
					}
				}
				if(flag==0)
					cout<<endl<<"!!!  You have not issued any books  !!!"<<endl;
			}
		}
};

class Librarian:public User
{
	string name,pass;
	public:
		Librarian(){}

		void signup()
		{
			system("clear");
			cout<<"Enter Name: ";
			cin>>name;
			cout<<"Enter Password: ";
			cin>>pass;
			
			fstream out;
			out.open("Librarian_sign.txt",std::fstream::app);
			out<<name<<" "<<pass<<endl;
			out.close();
			
			cout<<endl<<"***** Successfully created Librarian account *****"<<endl;
		}
		
		
		
		void signin()
		{
			system("clear");
			int check=-1;
			cout<<"Enter Name: ";
			cin>>name;
			cout<<"Enter Password: ";
			cin>>pass;
			
			int flag=0;
			ifstream in;
			in.open("Librarian_sign.txt");
			
			if(in.eof())
			{
				cout<<endl<<"!!!  No Librarian present in the record  !!!"<<endl;	
			}
			else
			{
				while(!in.eof())
				{
					string user;
					getline(in,user);
	
					if(user.length() > 0)
					{
						stringstream ss(user);
						string lname,password;
						ss>>lname>>password;
						
						if(lname==name && password==pass)
						{
							flag=1;
							cout<<endl<<"***** Successfully logged in as Librarian. *****"<<endl;
							while(check!=0)
							{
								cout<<endl<<"Available Choices :"<<endl<<endl;
								cout<<endl<<"1 - Create New User"<<endl;
								cout<<"2 - Search User"<<endl;
								cout<<"3 - View All Users"<<endl;
								cout<<"4 - Insert Book"<<endl;
								cout<<"5 - View All Books"<<endl;
								cout<<"6 - Issue Book"<<endl;
								cout<<"7 - Search Books"<<endl;
								cout<<"8 - Issued Books"<<endl;
								cout<<"9 - Return Book"<<endl;
								cout<<"10 - Delete User"<<endl;
								cout<<"0 - Logout"<<endl;
								
								cout<<endl<<"Enter your choice :-> ";
								cin>>check;
								
								switch(check)
								{
									case 1: signup();
										break;
									case 2: searchUser();
										break;
									case 3: viewAllUsers();
										break;
									case 4: insertBook();
										break;
									case 5: viewAllBooks();
										break;
									case 6: issueBook();
										break;
									case 7: searchBook();
										break;	
									case 8: viewIssuedBooks();
										break;
									case 9: returnBook();
										break;
									case 10: deleteUser();
										break;
									default: cout<<endl<<"Librarian logged Out Successfully..\n"<<endl;
								}
							}
						}
					}	
				}
				if(flag==0)
				{
					cout<<endl;
					cout<<"!!!  Librarian not found  !!!"<<endl<<endl;
				}
			}
			in.close();
		}
		
		
		
		
		void viewAllUsers()
		{
			system("clear");
			ifstream in;
			in.open("User.txt");
	
			if(in.eof())
			{
				cout<<endl<<"!!!  No user present in the record  !!!"<<endl;	
			}
			else 
			{
				while(!in.eof())
				{
					string user;
					getline(in,user);
	
					if(user.length() > 0)
					{
						stringstream ss(user);
						string eno, name, phone, email;
						ss>>eno>>name>>phone>>email;
			
						cout<<endl;
						cout<<"Enrollment No :-> "<<eno<<endl;
						cout<<"Name :-> "<<name<<endl;
						cout<<"Phone No :-> "<<phone<<endl;
						cout<<"Email :-> "<<email<<endl;	
					}
				}	
			}
	
			in.close();
		}
		
		
		
		
		void searchUser()
		{
			system("clear");
			int flag = 0;
			string key;
			
			cout<<endl;
			cout<<"Enter Enrollment no :-> ";
			cin>>key;
			
			ifstream in;
			in.open("User.txt");
	
			if(in.eof())
			{
				cout<<endl<<"!!!  No user present in the record  !!!"<<endl;	
			}
			else
			{
				while(!in.eof())
				{
					string user;
					getline(in,user);
	
					if(user.length() > 0)
					{
						stringstream ss(user);
						string eno, name, phone, email;
						ss>>eno>>name>>phone>>email;
			
						if(eno == key)
						{
							flag = 1;
							cout<<endl;
							cout<<"Enrollment No :-> "<<eno<<endl;
							cout<<"Name :-> "<<name<<endl;
							cout<<"Phone No :-> "<<phone<<endl;
							cout<<"Email :-> "<<email<<endl;
							break;
						}			
					}
				}
				
				if(flag == 0)
				{
					cout<<endl;
					cout<<"!!!  User not found  !!!"<<endl<<endl;
				}	
			}
			in.close();
		}
	
	
	
	
		void deleteUser()
		{
			system("clear");
			ofstream out;
			out.open("temp.txt", std::fstream::out);
			
			int flag = 0;
			string key;
			
			cout<<endl;
			cout<<"Enter Enrollment no :-> ";
			cin>>key;
			
			ifstream in;
			in.open("User.txt");
	
			if(in.eof())
			{
				cout<<endl<<"!!!  No user present in the record  !!!"<<endl;	
			}
			else
			{
				while(!in.eof())
				{
					string user;
					getline(in,user);
	
					if(user.length() > 0)
					{
						stringstream ss(user);
						string eno, name, phone, email;
						ss>>eno>>name>>phone>>email;
			
						if(eno == key)
						{
							flag = 1;
						}
						else
						{
							out<<eno<<" "<<name<<" "<<phone<<" "<<email<<endl;
						}
					}
				}
				
				if(flag == 0)
				{
					cout<<endl;
					cout<<"!!!  No user found  !!!"<<endl;
				}
				else
				{
					cout<<endl;
					cout<<"***** User Deleted Successfully *****"<<endl;
				}
			}
	
			
			in.close();
			out.close();
			
			remove("User.txt");
			rename("temp.txt","User.txt");
		}
			
		
		
		void viewIssuedBooks()
		{
			system("clear");
			ifstream in;
			in.open("Issued_Books.txt");
	
			if(in.eof())
			{
				cout<<endl<<"!!!  No book present in the record  !!!"<<endl;	
			}
			else
			{
				while(!in.eof())
				{
					string issue;
					getline(in,issue);
	
					if(issue.length() > 0)
					{
						stringstream ss(issue);
						string eno, bid;
						ss>>eno>>bid;
			
						cout<<endl;
						cout<<"Enrollment No :-> "<<eno<<endl;
						cout<<"Book Id :-> "<<bid<<endl;	
					}
				}	
			}
	
			in.close();
		}
		
		
		
		
		void insertBook()
		{
			system("clear");
			string bid, name, author, publisher;
	
			cout<<endl;
			cout<<"Enter Book Id :-> ";
			cin>>bid;
			cout<<"Enter Book Name :-> ";
			cin>>name;
			cout<<"Enter Author Name :-> ";
			cin>>author;
			cout<<"Enter Publisher :-> ";
			cin>>publisher;
			
			int flag = 0;
string key;
key=bid;
ifstream in;
in.open("Book.txt");
	while(!in.eof())
				{
					string book;
					getline(in,book);
	
					if(book.length() > 0)
					{
						stringstream ss(book);
						string bid, name, author, publisher;
						ss>>bid>>name>>author>>publisher;
			
						if(bid == key )
						{
							flag = 1;
							cout<<"Book Already Exists";
							in.close();
							break;
						}			
					}
				}
				
				if(flag == 0)
				{
					Book book(bid, name, author, publisher, true);
					cout<<"Book Added Successtully..";
					
				}	
			
			
			
		}
		
		
		
		void searchBook()
		{
			system("clear");
			int flag = 0;
			string key;
			
			
			cout<<endl;
			cout<<"Enter Book Id :-> ";
			cin>>key;
			
			ifstream in;
			in.open("Book.txt");
	
			if(in.eof())
			{
				cout<<endl<<"!!!  No Book present in the record  !!!"<<endl;	
			}
			else
			{
				while(!in.eof())
				{
					string book;
					getline(in,book);
	
					if(book.length() > 0)
					{
						stringstream ss(book);
						string bid, name, author, publisher;
						ss>>bid>>name>>author>>publisher;
			
						if(bid == key)
						{
							flag = 1;
							cout<<endl;
							cout<<"Book Id :-> "<<bid<<endl;
							cout<<"Name :-> "<<name<<endl;
							cout<<"Author :-> "<<author<<endl;
							cout<<"Publisher :-> "<<publisher<<endl;
							break;
						}			
					}
				}
				
				if(flag == 0)
				{
					cout<<endl;
					cout<<"!!!  Book not found  !!!"<<endl<<endl;
				}	
			}
			in.close();
		}
		
};

int main()
{
	int choice = -1,check=-1;
	
	system("clear");
	
    	cout<<"\n\t\t\t-------------------------------------------------------------------------------"<<endl;
    	cout<<"\n\t\t\t| ########################################################################### |"<<endl;
    	cout<<"\n\t\t\t| ############                                                   ############ |"<<endl;
    	cout<<"\n\t\t\t| ############             Library Management System             ############ |"<<endl;
    	cout<<"\n\t\t\t| ############                                                   ############ |"<<endl;
    	cout<<"\n\t\t\t| ########################################################################### |"<<endl;
    	cout<<"\n\t\t\t-------------------------------------------------------------------------------\n"<<endl;
    	
    	cout<<"\n";
    	
    	cout<<"\n\t\t\t      **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**"<<endl;
    	cout<<"\n\t\t\t      **                                                             **"<<endl;
    	cout<<"\n\t\t\t      **    =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=    **"<<endl;
    	cout<<"\n\t\t\t      **    =                    WELCOME TO                     =    **"<<endl;
    	cout<<"\n\t\t\t      **    =             LIBRARY MANAGEMENT SYSTEM             =    **"<<endl;
    	cout<<"\n\t\t\t      **    =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=    **"<<endl;
    	cout<<"\n\t\t\t      **                                                             **"<<endl;
    	cout<<"\n\t\t\t      **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n"<<endl;
    	
    	cout<<"\n\t\t\t      **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**"<<endl;	
    	cout<<"\n\t\t\t      **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**"<<endl;
    	cout<<"\n\t\t\t      **                                                             **"<<endl;
    	cout<<"\n\t\t\t      **    =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=    **"<<endl;
    	cout<<"\n\t\t\t      **    =-                                                 -=    **"<<endl;
    	cout<<"\n\t\t\t      **    =-               TEAM MEMBERS                      -=    **"<<endl;
    	cout<<"\n\t\t\t      **    =-              _______________                    -=    **"<<endl;
    	cout<<"\n\t\t\t      **    =-                                                 -=    **"<<endl;
    	cout<<"\n\t\t\t      **    =-              1.  Arjit Dubey                    -=    **"<<endl;
    	cout<<"\n\t\t\t      **    =-              2.  Dinesh Jagtap                  -=    **"<<endl;
    	cout<<"\n\t\t\t      **    =-              3.  Krishna Vishwakarma            -=    **"<<endl;
    	cout<<"\n\t\t\t      **    =-              4.  Rahul Malik                    -=    **"<<endl;
    	cout<<"\n\t\t\t      **    =-              5.  Ummed Singh                    -=    **"<<endl;
    	cout<<"\n\t\t\t      **    =-                                                 -=    **"<<endl;
    	cout<<"\n\t\t\t      **    =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=    **"<<endl;
    	cout<<"\n\t\t\t      **                                                             **"<<endl;
    	cout<<"\n\t\t\t      **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**"<<endl;
    	cout<<"\n\t\t\t      **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n"<<endl;
	
	
	cout<<"***************************************************"<<endl;
	cout<<"**********                               **********"<<endl;
	cout<<"**********   Library Management System   **********"<<endl;
	cout<<"**********                               **********"<<endl;
	cout<<"***************************************************"<<endl;
	
	while(choice!=0)
	{
		cout<<endl<<"Available Choices :"<<endl<<endl;
		cout<<"1 - User Signup"<<endl;
		cout<<"2 - Librarian Signup"<<endl;
		cout<<"3 - User Login"<<endl;
		cout<<"4 - Librarian Login"<<endl;
		cout<<"0 - Exit"<<endl;
		
		cout<<endl<<"Enter your choice :-> ";
		cin>>choice;
		switch(choice)
		{
			case 1:
			{
				User user;
				user.signup();
			}
				break;
			case 2:
			{
				Librarian lib;
				lib.signup();
			}
				break;
			case 3:
				{
					User user;
					user.signin();
				}
				break;
			case 4:
				{
					Librarian lib;
					lib.signin();
				}
				break;
			default:
				cout<<endl<<"Warning :-> System Closing..."<<endl;
				cout<<endl<<".."<<endl;
				cout<<endl<<"."<<endl;
				//system("clear");
				
		}
	}
	cout<<endl<<endl<<"--------------------------------------------------------------";
	cout<<endl<<"|********** Thank You for Using Library Management **********|"<<endl;
	cout<<"--------------------------------------------------------------"<<endl<<endl;
	return 0;
}//End of main
