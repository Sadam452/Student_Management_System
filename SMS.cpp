/*
1. Discover how to use templates
2. Get the concept of exception handling
3. How to avoid runtime errors
4. Concept of Multilevel Inheritance

Design Thinking Activity:
Problem:   Institution Management System
Generate Ideas:
Flow of the Inheritance :
								Institution
									|
								Departments
									|		\
								Programs	Faculty
For demonstration of templates : 
								Class Employees and templateDemo() function
								
1. User can login as student | Faculty | admin
2. Faculty member can view his/her profile, manage attendence and marks
3. Admin is having more controls. 
	1 : Admit student	2 : Remove Student	3 : Add Faculty	4 : Remove Faculty
	5 : View student Marks	6 : View Faculty	7 : View Attendence
	8 : Modify Student	9: Add Programs 10: View Programs
	11 : Clear Screen    12: Show Profile	13: Exit
4. User can create any instances of Student class and add data. Before saving the data, user will be asked for confirmation to save the details
6. User can display all the details of logged in user including his attendence and marks
7. Faculty can't enter negative attendence, if entered, then exception will be thrown
Note :  five files are created during this program namely: student.dat,Faculty.dat,attendence.dat,marks.dat.programs.dat
		student.dat stores student details
		Faculty.dat stores Faculty details
		attendence.dat stores student attendence marked by Faculty members
		marks.dat stores marks of students entered by Faculty members
		programs.dat stores all the programs offered by the university
*/
#include <iostream>
#include <iomanip> //header for setw(),setprecision() function to work
#include <fstream> //for file handling to work
#include <cstring>
#include <conio.h>
#include <windows.h>  //for Sleep() to work
#define Admin_PASS "OOP"
#define F_NOT_FOUND -1
#define SUCCESS 0
int flag,subject=0;
using namespace std;

class Institution
{
	protected:
		char name[50],uni_type[20],location[30],grade[10];
	public:
		Institution(){                      //default constructor
			name[0]=uni_type[0]=location[0]=grade[0]='\0';
		} 
		Institution(char name[50],char uni_type[20],char location[30],char grade[10]){ //parameterizd constructor
			strcpy(this->name,name);
			strcpy(this->uni_type,uni_type);
			strcpy(this->location,location);
			strcpy(this->grade,grade);
		}
};

class Departments:public Institution{
	protected:
		int DeptCode;
		char DeptName[30];
	public:
		Departments(){
			DeptCode=0;
			DeptName[0] ='\0';
		}
		Departments(char name[50],char uni_type[20],char location[30],char grade[10],
		int DeptCode,char DeptName[30]):Institution(name,uni_type,location,grade){
			this->DeptCode = DeptCode;
			strcpy(this->DeptName,DeptName);
		}
};

class Programs:public Departments{
	public:
	int ProgramCode;
	char ProgramName[30];
	int Seats;
	int ProgDuration;
	Programs(){
		ProgramCode = Seats = ProgDuration = 0;
		ProgramName[0] = '\0';
	}
	Programs(char name[50],char uni_type[20],char location[30],char grade[10],int DeptCode,char DeptName[30],char ProgramName[30],int ProgramCode,
	int Seats,int ProgDuration):
		Departments(name,uni_type,location,grade,DeptCode,DeptName){
			strcpy(this->ProgramName,ProgramName);
			this->ProgramCode = ProgramCode;
			this->Seats = Seats;
			this->DeptCode = DeptCode;
			this->ProgDuration = ProgDuration;
		}
	void getDetails(){
		cout<<"University Name:";cin>>name;
		cout<<"University Type:";cin>>uni_type;
		cout<<"Location:";cin>>location;
		cout<<"University Grade:";cin>>grade;
		cout<<"Department Code:";cin>>DeptCode;
		cout<<"Department Name:";cin>>DeptName;
		cout<<"ProgramName:";cin>>ProgramName;
		cout<<"ProgramCode:";cin>>ProgramCode;
		cout<<"Seats:";cin>>Seats;
		cout<<"Program Duration:";cin>>ProgDuration;
		//This function when called, add details to particular object	
	}
	void displayDetails(){ //this function displays Program details when called.
		cout<<"\nUniversity Name:"<<name;
		cout<<"\nUniversity Type:"<<uni_type;
		cout<<"\nLocation:"<<location;
		cout<<"\nUniversity Grade:"<<grade;
		cout<<"\nDepartment Code:"<<DeptCode;
		cout<<"\nDepartment Name:"<<DeptName;
		cout<<"\nProgramName:"<<ProgramName;
		cout<<"\nProgramCode:"<<ProgramCode;
		cout<<"\nSeats:"<<Seats;
		cout<<"\nProgram Duration:"<<ProgDuration;
	}
	int  getID()
	{
		return ProgramCode;
	}
};

void savePrograms(){ //save a program record to file "programs.dat"
    Programs pr;
    char choice;
	ofstream outFile;
	pr.getDetails();
	cout<<"\nWe have recieved the following details:";
	pr.displayDetails();
	cout<<"\nDo you want to save the above details? (y/n):";
	cin>>choice;
	if(choice == 'y' || choice == 'Y'){
	outFile.open("programs.dat",ios::binary|ios::app);
	outFile.write(reinterpret_cast<char *> (&pr), sizeof(Programs));
	outFile.close();
    cout<<"\nRecord Has Been Created...Pess any key to continue...";
}
	else
	cout<<"\nWe have ignored the above details.....press any key to continue";
	cin.ignore();
	cin.get();
}

void viewPrograms(){ 
	Programs pr;
	ifstream File;
	File.open("programs.dat",ios::binary);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
    	while(!File.eof())
	{
 
		File.read(reinterpret_cast<char *> (&pr), sizeof(Programs));
		pr.displayDetails();
	}
	File.close();
	cin.ignore();
	cin.get();
}

class Faculty:public Departments{
	protected:
		char facultyName[30],facultyID[20],designation[20],email[30],subject[20];
	public:
		Faculty(){
			facultyName[0] = facultyID[0] = designation[0] = email[0] = subject[0] = '\0';
		}
		Faculty(char name[50],char uni_type[20],char location[30],char grade[10],int DeptCode,
		char DeptName[30],char facultyName[30],char facultyID[20],char designation[20],char email[30],char subject[20]):
		Departments(name,uni_type,location,grade,DeptCode,DeptName)
		{
			strcpy(this->facultyName,facultyName);
			strcpy(this->facultyID,facultyID);
			strcpy(this->designation,designation);
			strcpy(this->email,email);
			strcpy(this->subject,subject);
		}
		void getDetails(){
		cout<<"University Name:";cin>>name;
		cout<<"University Type:";cin>>uni_type;
		cout<<"Location:";cin>>location;
		cout<<"University Grade:";cin>>grade;
		cout<<"Department Code:";cin>>DeptCode;
		cout<<"Department Name:";cin>>DeptName;
		cout<<"Faculty Name:";cin>>facultyName;
		cout<<"Faculty ID:";cin>>facultyID;
		cout<<"Designation:";cin>>designation;
		cout<<"Email ID:";cin>>email;
		cout<<"Subject:";cin>>subject;
		//This function when called, add details to particular object	
	}
	void displayDetails(){ //this function displays Program details when called.
		cout<<"\nUniversity Name:"<<name;
		cout<<"\nUniversity Type:"<<uni_type;
		cout<<"\nLocation:"<<location;
		cout<<"\nUniversity Grade:"<<grade;
		cout<<"\nDepartment Code:"<<DeptCode;
		cout<<"\nDepartment Name:"<<DeptName;
		cout<<"\nFaculty Name:"<<facultyName;
		cout<<"\nFaculty ID:"<<facultyID;
		cout<<"\nDesignation:"<<designation;
		cout<<"\nEmail:"<<email;
		cout<<"\nSubject:"<<subject;
	}
	char* getid()
	{
		return facultyID;
	}
	
	int manageAttendence();
    int manageMarks();
	void showDetails_(char*);	
};

//function to clear the screen
inline void clrscr(){
    system("cls");
}

class Student
{
	public:
	int StudentID,RollNo;
	char Title[5],FirstName[10],SurName[10],MothersName[20],FathersName[20],Address[20],
	MobileNo[20],Adhaar[20],Gender[7],DOB[20],DOJ[20],Program[20],Email[30],Religion[20],Category[20],
	isHandicaped[5],FathersOccupation[20],
	MothersOccupation[20],isLateralEntry[5],School[20],LinkedIn[20];
	float Marks_12,QualifyingExamMarks;
	struct sub{
            int mp,co,oop,math;
            }marks,attendence;
	Student(){
		StudentID=RollNo=0;
		Email[0]=MothersName[0]=FathersName[0]=Address[0]=FirstName[0]=SurName[0]=MobileNo[0]=
		Adhaar[0]=DOB[0]=DOJ[0]=Program[0]=Religion[0]=Category[0]=FathersOccupation[0]=MothersOccupation[0]=
		School[0]=LinkedIn[0]=Gender[0]=Title[0]=isHandicaped[0]=isLateralEntry[0]='\0';
		Marks_12=QualifyingExamMarks=0;
		//Default Constructor Setting Everything equal to zero
	}
	//Parametirezed constructor
	Student(int StudentID,int RollNo,char Title[5],char FirstName[10],char SurName[10],char MothersName[20],
	char FathersName[20],char Address[20],char MobileNo[12],char Adhaar[15],char Gender[7],char DOB[12],
	char DOJ[12],char Program[20],char Email[30],char Religion[20],char Category[10],char isHandicaped[5],char FathersOccupation[10],
    char MothersOccupation[10],char isLateralEntry[5],char School[20],char LinkedIn[20],float Marks_12,float QualifyingExamMarks){
    	this->StudentID=StudentID;
    	this->RollNo,RollNo;
    	strcpy(this->Title,Title);
    	strcpy(this->FirstName,FirstName);
    	strcpy(this->SurName,SurName);
    	strcpy(this->MothersName,MothersName);
    	strcpy(this->FathersName,FathersName);
    	strcpy(this->Address,Address);
    	strcpy(this->MobileNo,MobileNo);
    	strcpy(this->Adhaar,Adhaar);
    	strcpy(this->Gender,Gender);
    	strcpy(this->DOB,DOB);
    	strcpy(this->DOJ,DOJ);
    	strcpy(this->Program,Program);
    	strcpy(this->Email,Email);
    	strcpy(this->Religion,Religion);
    	strcpy(this->Category,Category);
    	strcpy(this->isHandicaped,isHandicaped);
    	strcpy(this->FathersOccupation,FathersOccupation);
    	strcpy(this->MothersOccupation,MothersOccupation);
    	strcpy(this->isLateralEntry,isLateralEntry);
    	strcpy(this->School,School);
    	strcpy(this->LinkedIn,LinkedIn);
    	this->Marks_12=Marks_12;
    	this->QualifyingExamMarks=QualifyingExamMarks;
    	//Parametired Constructor to add details when details are passed on object creation
		
	}
	
	void getStudentDetails(){
		cout<<"Student ID:";cin>>StudentID;
		cout<<"First Name:";cin>>FirstName;
		cout<<"Surname:";cin>>SurName;
		cout<<"Title:";cin>>Title;
		cout<<"Mothers Name:";cin>>MothersName;
		cout<<"Fathers Name:";cin>>FathersName;
		cout<<"Address:";cin>>Address;
		cout<<"Mobile Number:";cin>>MobileNo;
		cout<<"Adhaar No:";cin>>Adhaar;
		cout<<"Gender:";cin>>Gender;
		cout<<"Date of Birth:";cin>>DOB;
		cout<<"Date of Joining:";cin>>DOJ;
		cout<<"Program:";cin>>Program;
		cout<<"Roll No:";cin>>RollNo;
		cout<<"Email:";cin>>Email;
		cout<<"Religion:";cin>>Religion;
		cout<<"Category:";cin>>Category;
		cout<<"isHandicaped:";cin>>isHandicaped;
		cout<<"Fathers Occupation:";cin>>FathersOccupation;
		cout<<"Mothers Occupation:";cin>>MothersOccupation;
		cout<<"LinkedIn:";cin>>LinkedIn;
		cout<<"Marks_12:";cin>>Marks_12;
		cout<<"QualifyingExamMarks:";cin>>QualifyingExamMarks;
		cout<<"isLateralEntry:";cin>>isLateralEntry;
		cout<<"School:";cin>>School;
		//This function when called, add details to particular student	
	}
	void displayStudentDetails(){ //this function displays student details when called.
		cout<<"\nStudent ID:"<<StudentID;
		cout<<"\nFirst Name:"<<FirstName;
		cout<<"\nSurname:"<<SurName;
		cout<<"\nTitle:"<<Title;
		cout<<"\nMothers Name:"<<MothersName;
		cout<<"\nFathers Name:"<<FathersName;
		cout<<"\nAddress:"<<Address;
		cout<<"\nMobile Number:"<<MobileNo;
		cout<<"\nAdhaar No:"<<Adhaar;
		cout<<"\nGender:"<<Gender;
		cout<<"\nDate of Birth:"<<DOB;
		cout<<"\nDate of Joining:"<<DOJ;
		cout<<"\nProgram:"<<Program;
		cout<<"\nRoll No:"<<RollNo;
		cout<<"\nEmail:"<<Email;
		cout<<"\nReligion:"<<Religion;
		cout<<"\nCategory:"<<Category;
		cout<<"\nisHandicaped:"<<isHandicaped;
		cout<<"\nFathers Occupation:"<<FathersOccupation;
		cout<<"\nMothers Occupation:"<<MothersOccupation;
		cout<<"\nLinkedIn:"<<LinkedIn;
		cout<<"\nMarks_12:"<<Marks_12;
		cout<<"\nQualifyingExamMarks:"<<QualifyingExamMarks;
		cout<<"\nisLateralEntry:"<<isLateralEntry;
		cout<<"\nSchool:"<<School;
	}
	void marksDetails(){
		cout<<"Student ID:";cin>>StudentID;
		cout<<"CO Marks:";cin>>marks.co;
		cout<<"MP marks:";cin>>marks.mp;
		cout<<"OOP Marks:";cin>>marks.oop;
		cout<<"Math Marks:";cin>>marks.math;
	}
	void showMarks_(){
		cout<<"\nStudent ID:"<<StudentID;
		cout<<"\nCO Marks:"<<marks.co;
		cout<<"\nMP marks:"<<marks.mp;
		cout<<"\nOOP Marks:"<<marks.oop;
		cout<<"\nMath Marks:"<<marks.math;
	}
	void attendenceDetails(){
		cout<<"Student ID:";cin>>StudentID;
		cout<<"CO Attendence:";cin>>attendence.co;
		cout<<"MP Attendence:";cin>>attendence.mp;
		cout<<"OOP Attendence:";cin>>attendence.oop;
		cout<<"Math Attendence:";cin>>attendence.math;
		if(attendence.co < 0 || attendence.mp < 0 || attendence.oop < 0 || attendence.math < 0){   //Throw an exception
			throw(-1);
		}
	}
	void showAttendence_(){
		cout<<"\nStudent ID:     "<<StudentID;
		cout<<"\nCO Attendence:  "<<attendence.co;
		cout<<"\nMP Attendence:  "<<attendence.mp;
		cout<<"\nOOP Attendence: "<<attendence.oop;
		cout<<"\nMath Attendence:"<<attendence.math;
	}
    void showAttendence(int);
    void showMarks(int);
    friend class ADMIN;
	friend class Faculty;
	int  getID()
	{
		return StudentID;
	}
	
};

//Function Declarations
void saveStudentDetails();	 //to save all the details to file
void displayAll(int);		     //to view all the details from file
void modifyStudent(int);	 //modify a particular student
void deleteStudent(int);     // delete a particular student details

//function definations
void saveStudentDetails(){ //save a student record to file "student.dat"
    Student st;
    char c;
	ofstream outFile;
	st.getStudentDetails();
	cout<<"\nWe have recieved the following details:";
	st.displayStudentDetails();
	cout<<"\nDo you want to save the above student details? (y/n):";
	cin>>c;
	if(c=='y'){
	outFile.open("student.dat",ios::binary|ios::app);
	outFile.write(reinterpret_cast<char *> (&st), sizeof(Student));
	outFile.close();
    cout<<"\nStudent record Has Been Created...Pess any key to continue...";
}
	else
	cout<<"\nWe have ignored the above details.....press any key to continue";
	cin.ignore();
	cin.get();
}

void displayAll(int n){ //display all the details from "student.dat" file

	Student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\nAll Student Details\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(Student)))
	{
		if(st.getID() == n)
		st.displayStudentDetails();
	}
	cout<<"\n******************Press any key to continue********************";
	inFile.close();
	cin.ignore();
	cin.get();
}

void modifyStudent(int n){ //Modify a particular student record

	bool found=false;
	Student st;
	fstream File;
	File.open("student.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
    	while(!File.eof() && found==false)
	{
 
		File.read(reinterpret_cast<char *> (&st), sizeof(Student));
		if(st.getID()==n)
		{
			st.displayStudentDetails();
			cout<<"\nPlease Enter The New Details of student"<<endl;
			st.getStudentDetails();
		    	int pos=(-1)*static_cast<int>(sizeof(st));
		    	File.seekp(pos,ios::cur);
		    	File.write(reinterpret_cast<char *> (&st), sizeof(Student));
		    	cout<<"\n Record Has Been Updated....press any key to continue";
		    	found=true;
		}
	}
	File.close();
	if(found==false)
		cout<<"\n Record Not Found in Database ...press any key to continue";
	cin.ignore();
	cin.get();
}

void deleteStudent(int n){ //Delete a particular student record
	Student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat",ios::out);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(Student)))
	{
		if(st.getID()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&st), sizeof(Student));
		}
	}
	outFile.close();
	inFile.close();
	remove("student.dat");
	rename("Temp.dat","student.dat");
	cout<<"\nRecord Has Been Deleted ....press any key to continue";
	cin.ignore();
	cin.get();
}

//display marks
void Student::showMarks(int n){
	bool found=false;
	Student st;
	ifstream File;
	File.open("marks.dat",ios::binary);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
    	while(!File.eof() && found==false)
	{
 
		File.read(reinterpret_cast<char *> (&st), sizeof(Student));
		if(st.getID()==n)
		{
			st.showMarks_();
			found=true;
		}
	}
	File.close();
	if(found==false)
		cout<<"\n Record Not Found in Database ...press any key to continue";
	cin.ignore();
	cin.get();
}

//dispaly attendencce
void Student::showAttendence(int n){
	bool found=false;
	Student st;
	ifstream File;
	File.open("attendence.dat",ios::binary);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
    	while(!File.eof() && found==false)
	{
 
		File.read(reinterpret_cast<char *> (&st), sizeof(Student));
		if(st.getID()==n)
		{
			st.showAttendence_();
			found=true;
		}
	}
	File.close();
	if(found==false)
		cout<<"\n Record Not Found in Database ...press any key to continue";
	cin.ignore();
	cin.get();

}

void Faculty::showDetails_(char *id){
	Faculty st;
	ifstream inFile;
	inFile.open("Faculty.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\nFaculty Details\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(Faculty)))
	{
		if(!strcmp(st.getid(),id))
		{st.displayDetails();
		cout<<"\n**************************\n";}
	}
	cout<<"\n******************Press any key to continue********************";
	inFile.close();
	cin.ignore();
	cin.get();
}

void viewFaculty(){ //to display all Faculty members

	Faculty st;
	ifstream inFile;
	inFile.open("Faculty.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\nAll Faculty Details\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(Faculty)))
	{
		st.displayDetails();
		cout<<"\n**************************\n";
	}
	cout<<"\n******************Press any key to continue********************";
	inFile.close();
	cin.ignore();
	cin.get();
}

// Admin class inherited from <class>Faculty for managing student data with Administrative account
class Admin:public Faculty{
//Admin attributes are similar to Faculty, so same members of Faculty is used here for Admin data.
	char pass[10];
	public : Admin(char id[]){
				 strcpy(facultyID,id);
				 strcat(id,".dat");
		         ifstream fp(id,ios::in);
		         if(fp){
					fp>>pass;
			    	fp>>facultyName;
					fp>>email;
				 }
			}
		//void setsub(char *s){ strcpy(Faculty_sub,s); }
	    int addFaculty();
		int admitStudent();
		int removeFaculty(char*);
		int removeStudent(int);
		void viewMarks();
		void viewAttendence();
	    int manageAttendence();
	
		bool isValidPass(char *p){
			cout<<"\n\n\tAuthenticating...";
			Sleep(500);// has to be removed or else password "CSE" will be visible
			if(!strcmp(Admin_PASS,p)){
				return true;
			}else {false;
		}
	}
	void showProfile(char*);
};

void Admin::showProfile(char *id){
	Faculty st;
	ifstream outFile;
	outFile.open("Faculty.dat",ios::binary);
	outFile.read(reinterpret_cast<char *> (&st), sizeof(Faculty));
	{
		if(!strcmp(st.getid(),id)){
			cout<<"\n<><><><><><>Admin Details><><><><><><><>";
			st.displayDetails();
		}
	}
	outFile.close();
	cout<<"\n<><><><><><><><><><><><><><><><><><><><>";
	fflush(stdin);
	cin.get();
}

int Admin::addFaculty(){
	Faculty st;
    char choice;
	ofstream outFile;
	st.getDetails();
	cout<<"\nWe have recieved the following details:";
	st.displayDetails();
	cout<<"\nDo you want to save the above details? (y/n):";
	cin>>choice;
	if(choice == 'y' || choice == 'Y'){
	outFile.open("Faculty.dat",ios::binary|ios::app);
	outFile.write(reinterpret_cast<char *> (&st), sizeof(Faculty));
	outFile.close();
    cout<<"\nFaculty record Has Been Created...Pess any key to continue...";
}
	else
	cout<<"We have ignored the above details.....press any key to continue";
	cin.ignore();
	cin.get();
}

void Admin::viewMarks(){ 
	Student st;
	ifstream File;
	File.open("marks.dat",ios::binary);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
    	while(!File.eof())
	{
 
		File.read(reinterpret_cast<char *> (&st), sizeof(Student));
		st.showMarks_();
		cout<<"\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
	}
	File.close();
	cin.ignore();
	cin.get();
}

// admit student
// Administrator should provide all the fields required.
int Admin::admitStudent(){
	saveStudentDetails();
}
void Admin::viewAttendence(){
	Student st;
	ifstream File;
	File.open("attendence.dat",ios::binary);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
    	while(!File.eof())
	{
 
		File.read(reinterpret_cast<char *> (&st), sizeof(Student));
		st.showAttendence_();
		cout<<"\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
	}
	File.close();
	cin.ignore();
	cin.get();
}

// remove student ::by setting up all the attributes of student to null and overwriting on the old blocks
int Admin::removeStudent(int id){
	deleteStudent(id);
}

int Admin::removeFaculty(char *U){
	bool flag=false;
	long pos;
    fstream readfile("Faculty.dat",ios::binary|ios::in|ios::out);
	if(!readfile){
        cerr<<"Error in opening file...please try again";
        return F_NOT_FOUND;
     }
    Faculty temp;
	while(!readfile.eof()){
		pos=readfile.tellg(); //replace object with null bytes
        readfile.read((char*)&temp,sizeof(temp));
			if(!strcmp(U,temp.getid())){
            	flag=true;
            	break;
        	}
    }
	if(!flag){
        cerr<<"\tInvalid user "<<endl;
        return -2;
    	}
	readfile.seekp(pos);
	Faculty del;
	readfile.write((char*)&del,sizeof(Faculty));
	fflush(stdin);
	cout<<"Faculty  removed successfully...";
	cin.get();
	return SUCCESS;
}

int admin(){
    char id_[10];
    char pass[15],c;
	cout<<"\tLogin type : Administrator"<<endl;
    cout<<"\n\tEnter admin id           : ";
	cin>>id_;
	fflush(stdin);
	strupr(id_);
	strcpy(pass,id_);
    Admin ad(pass);
    cout<<"\n\tEnter admin password     : ";
	short i=0;
    while((c=getch())!=13){ pass[i]=c; i++; cout<<'*';
	  }
	pass[i]='\0';
	if(!ad.isValidPass(pass)){
		cout<<"\r\tAuthentication error..."<<pass<<endl;
      	cin.get();
    	exit(0);
	}
    while(1){
    cout<<"\tLogin type : Administrator  ["<<id_<<"]"<<endl;
    cout<<"\t\tMenu"<<endl;
    cout<<"_______________________________________________________________________________"<<endl;
	cout<<"\t\t1 : Admit student\n\t\t2 : Remove Student\n\t\t3 : Add Faculty\n\t\t4 : Remove Faculty";
	cout<<"\n\t\t5 : View student Marks\n\t\t6 : View Faculty\n\t\t7 : View Attendence \n\t\t8 : Modify Student\n\t\t9 : Add Program"
	"\n\t\t10: View Programs\n\t\t11: Clear Screen\n\t\t12: Show Profile\n\t\t13: Exit"<<endl;
	cout<<"_______________________________________________________________________________"<<endl;
	cout<<"\n\tEnter your choice  : ";
    int choice;
    cin>>choice;
    int id;
	char s[5];
	switch(choice){
		   case 1 : 
		   			ad.admitStudent();
		   				break;
		   case 2 : cout<<"\n\tEnter the valid ID : ";
		  			cin>>id;
                    ad.removeStudent(id);
		   			break;
		   	case 3 : ad.addFaculty();
		   			 break;
			case 4 :cout<<"\n\tEnter the Faculty id : "; cin>>pass;
					strupr(pass);
					ad.removeFaculty(pass);
					break;
			case 5 :ad.viewMarks();
		   		    break;
		   	case 6 :
		   			viewFaculty();
		   		   	break;
		   	case 7: ad.viewAttendence();break;
		   	case 8 :cout<<"\n\tEnter the valid ID : ";
			   		cin>>id;
			        modifyStudent(id);
		   		   	break;	
			case 9: savePrograms();
					break;
			case 10: viewPrograms();
					 break;
			case 11:
					clrscr();break;	   	
			case 12 :
					ad.showProfile(id_);break;
			case 13 :cout<<"Logging out...["<<id_<<"]";
		   			Sleep(1000);
                    return 0;
           default : cout<<"Select valid choice : ";
					Sleep(1000);
       }
    }
}

int Faculty::manageMarks(){
    Student st;
	ofstream outFile;
	st.marksDetails();
	outFile.open("marks.dat",ios::binary|ios::app);
	outFile.write(reinterpret_cast<char *> (&st), sizeof(Student));
	outFile.close();
    cout<<"\nStudent Marks Record Has Been Updated successfully...Pess any key to continue...";
	cin.ignore();
	cin.get();

}

int Faculty::manageAttendence(){
	Student st;
	ofstream outFile;
	try{                                 //try block ---exception handling
	st.attendenceDetails();
	}
	catch(int i){
		cout<<"A runtime exception has occured, terminating the current task\n Possible Cause: Attendence Can't be negative\n";
		return 0;
	}
	outFile.open("attendence.dat",ios::binary|ios::app);
	outFile.write(reinterpret_cast<char *> (&st), sizeof(Student));
	outFile.close();
    cout<<"\nStudent Attendence has been updated successfully...Pess any key to continue...";
	cin.ignore();
	cin.get();
}

int student(){
	int id;
	cout<<"\tLogin type : Student."<<endl;
	cout<<endl<<"\tEnter your ID : ";
    cin>>id;
	int choice;
    Student s;
	//object of student class initialized with ID
	while(1) {
		cout<<"\tLogin type : Student  ["<<id<<"]"<<endl;
       	cout<<"\t\tMenu"<<endl;
       	cout<<"\t\t1 : View profile\n\t\t2 : View attendence\n\t\t3 : View marks \n\t\t4 : Exit"<<endl;
       	cout<<"\tEnter your choice  : ";
       	cin>>choice;
       	switch(choice){
           case 1 : fflush(stdin);
		   			clrscr();
		   			displayAll(id);
                    break;
           case 2 : fflush(stdin);
                    clrscr();
		            s.showAttendence(id);
                     break;
           case 3 : fflush(stdin);
		   			clrscr();
		   			s.showMarks(id);
                    break;      
		   case 4 : cout<<"Logging out...["<<id<<"]";
		   			Sleep(1000);
		   			return SUCCESS;
           default : cout<<"Select valid choice : ";
		   		Sleep(1000);
       }
    }
}

int faculty(){
    char Facultyid[10];
	cout<<"\tLogin type : Faculty"<<endl;
    fflush(stdin);
    cout<<endl<<"\tEnter Faculty id      : ";
    cin>>Facultyid;
    Faculty staf;
	//object of student class initialized with usn
    while(1){
	cout<<"\tLogin type : Faculty  ["<<Facultyid<<"]"<<endl;
       cout<<"\t\tMenu"<<endl;
       cout<<"\t\t1 : View profile\n\t\t2 : Manage attendence\n\t\t3 : Manage marks\n\t\t4 : Exit"<<endl;
       cout<<"\n\tEnter your choice  : ";
       int choice;
       cin>>choice;
       switch(choice){
           case 1 :fflush(stdin); clrscr(); staf.showDetails_(Facultyid);
		   			break;
           case 2 : fflush(stdin); clrscr(); staf.manageAttendence();
                    break;
           case 3 : fflush(stdin); clrscr();
		   			staf.manageMarks();
                    break;
           case 4 : cout<<"Logging out...["<<Facultyid<<"]";
		   			Sleep(1000);
                    return SUCCESS;
            default : 
				cout<<"Select valid choice : ";
		  Sleep(1000);
		         }
    }
}
//to print title "IUST INSTITUTION MANAGEMENT SYSTEM
void header(){
	cout<<"\t\t\t\t    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
    cout<<"\t\t\t\t    % IUST INSTITUTION MANAGEMENT SYSTEM %\n";
    cout<<"\t\t\t\t    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
}

//Demonstration of Templates
//idea is to pass data type as a parameter so that we dont need to write the same code for different data types.
template<class T,class T1>
class Employee {
	public:	
		T CompanyID; //CompanyID is pf type T....which will be provided by user of any data type
		T1 Salary;
		Employee(T CompanyID,T1 Salary){
			this->CompanyID = CompanyID;
			this->Salary = Salary;
		}
		T getCompanyID(){
			return CompanyID;
		}
		showDetails(){
			cout<<"\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%";
			cout<<setw(15)<<"\nComapny ID:"<<setw(15)<<CompanyID;
			cout<<setw(15)<<"\nSalary:"<<setw(15)<<Salary;
		}
};

void templateDemo(){
	Employee <int,float> emp1(5505,54200.85); //sending int and float data
	cout<<"\nCase 1:<int, float> Company ID:  "<<emp1.getCompanyID();
	emp1.showDetails();
	Employee <string,int> emp2("MIET12",56000); //sending string and int data
	cout<<"\nCase 2:<string, int> Company ID:  "<<emp2.getCompanyID();
	emp2.showDetails();
	cout<<"\nPress any key to continue...";
	cin.ignore();
	cin.get();
}

//Main function starts from here
int main(){
    cout.setf(ios::fixed|ios::showpoint);
	cout<<setprecision(2);
	int choice = 0;
	while(1){
		clrscr();
		header();
		cout<<"\n\t\tLogin Options:"<<endl;
    	cout<<"\t\t 1 : Student "<<endl;
    	cout<<"\t\t 2 : Faculty   "<<endl;
    	cout<<"\t\t 3 : Admin "<<endl;
    	cout<<"\t\t 4 : Clear Screen "<<endl;
		cout<<"\t\t 5 : Template Demo?"<<endl;
		cout<<"\t\t 6 : Exit"<<endl;
		cout<<endl<<endl<<"\t\tEnter your choice[1/2/3/4/5/6] : ";
  		cin>>choice;
  		if(choice == 1){
		student();
		}
		else if(choice == 2){
			faculty();
		}
		else if(choice == 3){
			admin(); 
		}
		else if(choice == 4){
			clrscr();
		}
		else if(choice == 5)
			templateDemo();
		else if(choice == 6)
			break;
		else
		cout<<"\tPlease choice the correct option.";
	}
	cout<<"AM GOING TO EXIT...END OF THE PROGRAM";
	return 0;
}
