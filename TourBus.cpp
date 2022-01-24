#include <fstream>
#include <iostream>
#include <cstring>

class TourBus {       
    int busId;  
	char destination[200];
	char time[50];
	int maxSeats;
	int booked;
	int fare;
	
	public:
	  TourBus() {
	    busId = 0;
	    maxSeats = 50;
	    booked = 0;
	    fare = 0;
    	strcpy(time,"9:10AM");
	    strcpy(destination,"");
	  }
	  void input();
	  void showDetails();  
	  void displayData();  
	  
	  int getId(){ 
	    return busId;
	  }
	  void book(){
	    booked++;
	  }
	  char* getDestination(){
	    return destination;
	  }
	  char* getTime(){
	    return time;
      }
	  int getBooked(){
	    return booked;
	  }
	  int getMax(){
	    return maxSeats;
	  }
	  int getFare(){
		return fare;
	  }
};
void TourBus::input() {
	cout << "Enter Bus ID: ";
	cin >> busId;
	cout << "Enter Bus Destination: ";
	gets(destination);
	cout << "Enter Bus Time: ";
	cin >> time;
	cout << "Enter Bus Fare: ";
	cin >> fare;
}
void TourBus::displayData() {
	cout << busId << "\t" << destination << "\t" << time << "\t" << maxSeats << "\t" << booked<< "\t" << fare << "\n";
}
void TourBus::showDetails(){
	cout << "Bus Id: " << busId << endl;
	cout << "Desination: " << destination << endl;
	cout << "Time: "<< time << endl;
	cout <<"Available Seats: "<< maxSeats - booked <<endl;
}

class Ticket {
	char name[50];
	TourBus bus;
	
	public:
      void generate(char cname[], TourBus tourbus){
		strcpy(name, cname);
		bus = tourbus;
	  }
	  void display(){
	    cout << "Customer Name: " << name <<endl;
	    cout << "Bus Details: " << endl;
	    bus.showDetails();
	  }
};

int main(){
	int option; 
	fstream file, tFile;  
	TourBus bus; 
	do {
	  cout << "Press 1 - Add a New Tour Bus" << endl;
	  cout << "Press 2 - Show Selected Bus" << endl;
	  cout << "Press 3 - Display All Buses" << endl;
	  cout << "Press 4 - Book a ticket " << endl;
	  cout << "Press 5 - Display Booked Tickets " << endl;
	  cout << "Press 6 - Exit " << endl;
	  cout << "Enter Your Choice: ";
	  cin >> option;
	  
	  switch(option) {
	      
		case 1:
			file.open("tour.txt", ios::app);
			bus.input(); 
			file << write((char*)&bus, sizeof(bus));
			file.close();
			cout << "Bus Added Successfully: " << endl;
		    break;
		    
		case 2:
			int busID, check = 0;
			cout << "Enter Bus ID: ";
			cin >> busID;
			file.open("tour.txt", ios::in);
			if(file.fail()){
			    cout << "Some Error Occoured! "<< endl;
			} else {
				while(file.read((char*)&bus,sizeof(bus))){
					if(bus.getid() == id) {
						bus.showDetails();
						check = 1;
						break;
					}
				}
				if(check == 0){
				    cout << "Bus Not Found" << endl;
				}
			}
			file.close();
			break;

		case 3:
			file.open("tour.txt", ios::in);
			if(file.fail()){
			    cout << "Some Error Occoured! "<< endl;
			} else {
				while(file.read((char*)&bus,sizeof(bus))){
				    bus.displayData();
				}
			}
			file.close();
		    break;
		
		case 4:
			char dest[70],cname[50];
			int busID, check = 0;
			Ticket ticket;
			
			cout << "Enter the Destination: ";
			gets(dest);
			
			file.open("tour.txt", ios::in | ios::out);
			
			if(file.fail()){
			    cout << "Some Error Occoured! "<< endl;
			} else {
				while(file.read((char*)&bus, sizeof(bus))){
					if(strcmp(bus.getDestination(), dest) == 0){
						bus.showDetails();
						check=1;
						cout << "Enter Customer Name: ";
						gets(cname);
						bus.book();
						ticket.generate(cname, bus);
						tFile.open("tickets.txt", ios::app);
						tFile.write((char*)&ticket,sizeof(ticket));
						tFile.close();
						
					    file.seekp(file.tellg()-sizeof(bus),ios::beg);
                        file.write((char*)&bus, sizeof(bus));
					    cout << "Ticket Booked! " <<endl;
					    break;
					}
				}
				if(check == 0){
				    cout << "No Bus Found" << endl;
				}
			}
			file.close();
			break;
			
		case 5:
			cout << "Booked Tickets " <<endl;
			tFile.open(" tickets.txt", ios::in);
			if(tFile.fail()){
			    cout << "Some Error Occoured! "<< endl;
			} else {
				while(tFile.read((char*)&ticket, sizeof(ticket)))
				ticket.display();
			}
			tFile.close();
		}
	} while(option!=6);
	
	return 0;
}



