#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <ctime>
using namespace std;


class user{
	protected:
		string password;
	protected:
		string userid;
		string email;
		string ph_no;
		string address;
		int zipcode;
		string country;
	public:
	int sign_up(){
		int count=0;
		string id;
		system("cls");
		cout << "Enter User Name " << endl;
		cin >> userid ;
		ifstream inp("Users.txt");
		while(inp >> id){
			if(id==userid ){
				cout << "user already exist" << endl; 
				count=1;
				break;
			}
		}
		if(count==0){
			inp.close();
			cout << "Enter Password " << endl ;
			cin >> password;
			cout << "Enter Email " << endl;
			cin >> email ;
			cout << "Enter phone number " << endl ;
			fflush(stdin);
			getline(cin, ph_no);
			cout << "Enter Address " << endl;
			getline(cin, address);
			cout << "Enter Zip code " << endl ;
			cin >> zipcode;
			cout << "Enter country " << endl ;
			cin >> country;
			ofstream obj_wr("Users.txt",ios::app);
			obj_wr << userid << " " << password << " "<< email << " " <<  ph_no << " " << address << " " <<  zipcode << " " << country << endl;	
			obj_wr.close();
			system("cls");
			cout << "Your account successfully created " << endl;
			string f_name_p=userid;
			ofstream obw_P(f_name_p.c_str(),ios::app);
			obw_P << 0;
  			obw_P.close();
			}
		}
	
	
	int log_in(){
		int count = 0;
    	ifstream inp("Users.txt");
		string id,pass;
		cout << "Enter user id: ";
		cin >> id;
		cout << "Enter Password: " ;
		cin >> pass;
		if (!inp.is_open()) {
	        cout << "Error in opening the file!" << endl;
	    } 
	    else{
   	 		while (inp >> userid >> password >> email >> ph_no >> address >> zipcode >> country ) {
        		if (id == userid && pass == password) {
            		count = 1;
            		system("cls");
            		break;
        		}
    		}		
		}
    	inp.close();

    	if (count == 1) {
        	cout << "Login Successful" << endl;
        	return 1;
    	} 
		else {
        	cout << "User does not exist" << endl;
        	return 0;
    	}
	}
	void forget(){
		int opt,count=0,coun=0;
		string id, pass;
		cout << "Enter user id: ";
		cin >> id;
		ifstream inp("Users.txt");
		int temp;
		while(inp >> userid >> password >> email >> ph_no >> address >> zipcode >> country ){
			if(id==userid){
					inp.close();
					cout << "Your password is "  << password << endl ;
					inp.close();
					count=1;//if user found
					cout << "Do you want change password to enter 1 " << endl ;
					cout << "If not want to change password enter 0" << endl;
					int choice;
					cin >> choice ;
					if( choice ==1){
							cout << "Enter new password: " ;
							cin >> password;
							ifstream input_file("Users.txt");
    						ofstream output_file("Users_temp.txt");
    						int temp;
							while(input_file >> id >> pass >> email >> ph_no >> address >> zipcode >> country ){
								if(id==userid){
									coun=1;
									output_file << id << " " << password << " " << email << " " << ph_no << " " << address << " " << zipcode << " " << country  <<endl;
								}
								else {
            						output_file << id << " " << pass << " " << email << " " << ph_no << " " << address << " " << zipcode << " " << country << endl;
            					}
							}
							input_file.close();
							output_file.close();
    				}
					break;	
				}
				else {
					count=0;
				}
			}
		if (count == 0) {    	
       		cout << "User not found" << endl;
			
    	}
    	else if (coun==0){
    		remove("Users_temp.txt");
		}
		else if(coun==1){
   			remove("Users.txt");
   			rename("Users_temp.txt", "Users.txt");
    		remove("Users_temp.txt");
		}
	}
};
	class account:public user{
		private:
			double account_balance;
			double deposit;
			double withdraw;
			string person;
			int act;
		public:
			account(){
				account_balance=0.0;
				deposit=0.0;
				withdraw=0.0;
				act = 1;
			}
			void action(){
				while(act!=0)
				{
					cout << "--------------------------------------" << endl <<endl;
					cout << "Press 1 to deposit money " << endl;
					cout << "Press 2 to withdraw money " << endl;
					cout << "Press 3 to check balance " << endl;
					cout << "Press 4 to transfer money to other account " << endl ;
					cout << "Press 5 to get statement or transaction history " << endl;
					cout << "Press 0 to logout " << endl;
					cout << "--------------------------------------" << endl <<endl;
					cin >> act;
					switch(act){
						case 1:
							set_balance();
							break;
						case 2:
							withdrawMoney();
							break;
						case 3:
							get_balance();
							break;
						case 4:
							transaction();
							break;
						case 5:
							statement();
							break;
						 case 0 :
						 	cout << "Logged out " << endl;
						 	system("cls");
						 	break;
					}
				}
			}
			
			void set_balance() {
        char* f_name = new char[userid.length() + 5];
        for (int i = 0; i < userid.length(); i++) {
            f_name[i] = userid[i];
        }
        f_name[userid.length()] = '.';
        f_name[userid.length() + 1] = 't';
        f_name[userid.length() + 2] = 'x';
        f_name[userid.length() + 3] = 't';
        f_name[userid.length() + 4] = '\0';

        fstream file(f_name, ios::in | ios::out);
        if (!file.is_open()) {
            cout << "Error in opening the file!" << endl;
            delete[] f_name;
            return;
        }

        // Ask the user for the amount of money to be added
        double amount;
        cout << "Enter the amount of money to be added: ";
        cin >> amount;

        // Read the current amount of money from the file
        file >> account_balance;

        // Add the new amount of money to the current amount
        account_balance += amount;

        // Close the file
        file.close();

        // Reopen the file in truncate mode to clear its content
        file.open(f_name, ios::out | ios::trunc);
        if (!file.is_open()) {
            cout << "Error in opening the file for truncation!" << endl;
            delete[] f_name;
            return;
        }

        // Write the updated balance to the file
        file << account_balance;

        // Close the file
        file.close();
        delete[] f_name;

        cout << "The money has been updated successfully." << endl;
		time_t now = time(0);
				char* date_time = ctime(&now);
   				char* fname = new char[userid.length()+6];
			 	    		for(int i=0;i<userid.length();i++){
								fname[i]=userid[i];
							}
							fname[userid.length()]='T' ;
							fname[userid.length()+1]='.' ;
							fname[userid.length()+2]='t' ;
							fname[userid.length()+3]='x' ;
							fname[userid.length()+4]='t' ;
							fname[userid.length()+5] = '\0';
							ofstream objs(fname,ios::app);
							account_balance=get_balance();
							objs << account_balance << " " << "Type: " << "Deposited" << " "  << " "<< userid << " " << "+" << " " <<  date_time  <<  endl;
							objs.close();	
							delete[] fname;
    }

    void withdrawMoney() {
        char* f_name = new char[userid.length() + 5];
        for (int i = 0; i < userid.length(); i++) {
            f_name[i] = userid[i];
        }
        f_name[userid.length()] = '.';
        f_name[userid.length() + 1] = 't';
        f_name[userid.length() + 2] = 'x';
        f_name[userid.length() + 3] = 't';
        f_name[userid.length() + 4] = '\0';

        fstream file(f_name, ios::in | ios::out);
        if (!file.is_open()) {
            cout << "Error in opening the file!" << endl;
            delete[] f_name;
            return;
        }

        cout << "Enter amount that you want to withdraw: ";
        cin >> withdraw;

        if (withdraw <= 0) {
            cout << "Transaction failed." << endl;
            cout << "This amount is not withdrawable." << endl;
            file.close();
            delete[] f_name;
            return;
        }

        // Read the current amount of money from the file
        file >> account_balance;

        if (withdraw > account_balance) {
            cout << "Insufficient Balance to proceed with this transaction." << endl;
        } else {
            // Subtract the withdrawal amount from the current amount
            account_balance -= withdraw;

            // Close the file
            file.close();

            // Reopen the file in truncate mode to clear its content
            file.open(f_name, ios::out | ios::trunc);
            if (!file.is_open()) {
                cout << "Error in opening the file for truncation!" << endl;
                delete[] f_name;
                return;
            }

            // Write the updated balance to the file
            file << account_balance;

            // Close the file
            file.close();
            delete[] f_name;

            cout << "Withdrawal successful." << endl;
        }

        time_t now = time(0);
				char* date_time = ctime(&now);
   				char* f_nam = new char[userid.length()+6];
			 	    		for(int i=0;i<userid.length();i++){
								f_nam[i]=userid[i];
							}
							f_nam[userid.length()]='T' ;
							f_nam[userid.length()+1]='.' ;
							f_nam[userid.length()+2]='t' ;
							f_nam[userid.length()+3]='x' ;
							f_nam[userid.length()+4]='t' ;
							f_nam[userid.length()+5] = '\0';
							ofstream objs(f_nam,ios::app);
							account_balance=get_balance();
							objs << account_balance << " "<< "Type: " << "Withdraw" << " " << "by" << " "<< userid << " " << "-" << " " <<  date_time  <<  endl;
							objs.close();	
							delete[] f_nam;
    }
			double get_balance(){
				char* f_name = new char[userid.length()+5];
			    for(int i=0;i<userid.length();i++){
					f_name[i]=userid[i];
				}
				f_name[userid.length()]='.' ;
				f_name[userid.length()+1]='t' ;
				f_name[userid.length()+2]='x' ;
				f_name[userid.length()+3]='t' ;
				f_name[userid.length()+4] = '\0';
				ifstream file(f_name);
				file >> account_balance ;
				cout << "balance is " << account_balance  << endl << endl ;	
				return account_balance;
			}
			
			void transaction(){
				string id; double amount; int c=1;
				cout << "Enter account holder name that you want to transfer " << endl;
				cin >> person;
				ifstream inp("users.txt");
				while(inp >> id){
					if(person==userid){
						cout << "This is your account name what you enter" << endl;
						c=0;
						break;
					}
					if(person==id){
						c=1;
						cout << "Enter amount " << endl ;
						cin >> amount;
						char* f_name = new char[userid.length()+5];
			 	    	for(int i=0;i<userid.length();i++){
							f_name[i]=userid[i];
						}
						f_name[userid.length()]='.' ;
						f_name[userid.length()+1]='t' ;
						f_name[userid.length()+2]='x' ;
						f_name[userid.length()+3]='t' ;
						f_name[userid.length()+4] = '\0';
						fstream file(f_name, ios::in | ios::out);
						file >> account_balance;
						if (!file.is_open()) {
      						cout << "Error in opening the file!" << endl;
      					}
						if(amount>account_balance){
							cout << "Insufficient Balance to proceed this transaction " << endl;
							cout << "Transaction unsuccessful " << endl;
							c=-1;
						}
						else{
							account_balance -= amount;
		    				file.seekg(0, ios::beg);
   							file << account_balance;
   							delete[] f_name;
   							file.close();
   							char* second = new char[person.length()+5];
			 	    		for(int i=0;i<person.length();i++){
								second[i]=person[i];
							}
							second[person.length()]='.' ;
							second[person.length()+1]='t' ;
							second[person.length()+2]='x' ;
							second[person.length()+3]='t' ;
							second[person.length()+4] = '\0';
							fstream f2(second, ios::in | ios::out);
							f2 >> account_balance;
							if (!f2.is_open()) {
      							cout << "Error in opening the file!" << endl;
      						}
      						else{
      							account_balance += amount;
		    					f2.seekg(0, ios::beg);
   								f2 << account_balance;
							}
      						f2.close();
      						delete[] second;
						}
						break;
					}
					else {
						c=0;
					}
				}
				if (c==0){
					cout << "No account name " << person << endl <<  endl;
				}
				else if (c==1){
					cout << "Transaction successful " << endl;
					time_t now = time(0);
				    char* date_time = ctime(&now);
				    cout << "The current date and time is: " << date_time << endl;
							char* second = new char[person.length()+6];
			 	    		for(int i=0;i<person.length();i++){
								second[i]=person[i];
							}
							second[person.length()]='T' ;
							second[person.length()+1]='.' ;
							second[person.length()+2]='t' ;
							second[person.length()+3]='x' ;
							second[person.length()+4]='t' ;
							second[person.length()+5] = '\0';
							ofstream obj_w(second,ios::app);
							obj_w << "Type: " << "recieved"  << " " << "from " << " "<< userid << " " <<  "+" << " " << date_time << endl;
							obj_w.close();	
							delete[] second;
							char* f_name = new char[userid.length()+6];
			 	    		for(int i=0;i<userid.length();i++){
								f_name[i]=userid[i];
							}
							f_name[userid.length()]='T' ;
							f_name[userid.length()+1]='.' ;
							f_name[userid.length()+2]='t' ;
							f_name[userid.length()+3]='x' ;
							f_name[userid.length()+4]='t' ;
							f_name[userid.length()+5] = '\0';
							ofstream objs(second,ios::app);
							account_balance=get_balance();
							objs << account_balance << " "<< "Type: " << "transfer" << " " << "to " << " "<< userid << " " << "-" << " " <<  date_time  <<  endl;
							objs.close();	
							delete[] f_name;
				}
				inp.close();
				
			}
			void statement(){
				char* f_name = new char[userid.length()+6];
			 	for(int i=0;i<userid.length();i++){
					f_name[i]=userid[i];
				}
				f_name[userid.length()]='T' ;
				f_name[userid.length()+1]='.' ;
				f_name[userid.length()+2]='t' ;
				f_name[userid.length()+3]='x' ;
				f_name[userid.length()+4]='t' ;
				f_name[userid.length()+5] = '\0';
				ifstream file(f_name);
    			if (!file) {
        			cerr << "Error: could not open file.\n";
        			cout << file;
   				}
   				string line;
   				cout << "------------------------------------------------------------------------------" << endl ;
    			while (getline(file, line)) {
        			cout << line << '\n';
    			}
    			cout << "------------------------------------------------------------------------------ " << endl;
			}
	};
int main(){
	
	int choice=1 ;
	int check;
	while(choice!=0){
		cout << "===============================================" << endl;
		cout << "\t\t\tOnline Banking system \t\t\t" << endl;
		cout << "Press 1 to sign up " << endl;
		cout << "Press 2 to log in" << endl ;
		cout << "Press 3 to if you forget your password " << endl;
		cout << "Press 0 to Exit " << endl ;
		cout << "===============================================" << endl;
		cin >> choice;
		account ob;
		switch(choice){
			case 1:
				ob.sign_up();
				break;
			case 2: 
				check=ob.log_in();
				if(check==1){
					system("cls");
					ob.action();
				}
				break;
			case 3: 
				ob.forget();
				break;
			case 0:
				cout << "Thankyou " ;
				break;
			default :
				cout << "Invalid Choice " << endl ;
				break;
			}
		}
	}

