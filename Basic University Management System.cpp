#include<iostream>
#include<fstream>
#include<cstring>
#include<climits>
#include<cctype>
#include<iomanip>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<process.h>
#include<limits>
#include<ios>
#include<windows.h>
using namespace std;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);


// Define the university structure
struct university {
    char name[15], Usn[15], age[10], Sem[10], Branch[15];
    char COURSE[10], CID[5], sdate[5], edate[5], smonth[10], emonth[10], syear[5], eyear[5];
    char sname[10], usn[5], course[10], branch[10], sem[10], theory1[12], theory2[12], theory3[12], theory4[12], theory5[12], theory6[12], lab1[12], lab2[12];
    char Tname[15], Tid[10], department[15], subject[15],Tqualification[50],Tresearch[50],researchDate[15];
}unirec[500], found[100];

char findex[500][90], rt_name[50];

// Utility function to clean user input
void cleanInput(char* input, size_t maxLength) {
    cin.getline(input, maxLength);
    int index = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (isalnum(input[i]) || isspace(input[i]) || input[i] == ':' || input[i] == '|') {
            input[index++] = input[i];
        }
    }
    input[index] = '\0';
}

// ************************* Student Module *************************

void studentadd_records() {
    fstream file;
    int no, cnt;
    char line[50];
    SetConsoleTextAttribute(h,14);
    cout << "\nEnter the number of students: ";
    cin >> no;
    cin.ignore(INT_MAX, '\n');
    cnt = 0;  // Simulating reading current records count
    for (int i = cnt; i < cnt + no; i++) {
        SetConsoleTextAttribute(h,14);
        cout << "\nNAME   : ";
        cleanInput(line, sizeof(line));
        strcpy(unirec[i].name, line);

        SetConsoleTextAttribute(h,14);
        cout << "\nAGE    : ";
        cleanInput(line, sizeof(line));
        strcpy(unirec[i].age, line);

        while (true) {
            bool isDuplicate = false;

            cout << "\nUSN    : ";
            cleanInput(line, sizeof(line));

            // Check if the USN already exists in the file
            fstream checkFile;
            checkFile.open("studentrecord.txt", ios::in);
            if (checkFile) {
                char existingName[15], existingAge[10], existingUSN[15], existingSem[10], existingBranch[15];
                while (checkFile.getline(existingName, 15, '|') &&
                       checkFile.getline(existingUSN, 15, '|') &&
                       checkFile.getline(existingAge, 10, '|') &&
                       checkFile.getline(existingSem, 10, '|') &&
                       checkFile.getline(existingBranch, 15, '\n')) {
                    if (strcmp(existingUSN, line) == 0) {
                        isDuplicate = true;
                        break;
                    }
                }
                checkFile.close();
            }

            if (isDuplicate) {
                cout << "Error: USN already exists. Please enter a unique USN.\n";
            } else {
                strcpy(unirec[i].Usn, line);
                break;
            }
        }

        SetConsoleTextAttribute(h,14);
        cout << "\nSEMESTER: ";
        cleanInput(line, sizeof(line));
        strcpy(unirec[i].Sem, line);

        SetConsoleTextAttribute(h,14);
        cout << "\nBRANCH : ";
        cleanInput(line, sizeof(line));
        strcpy(unirec[i].Branch, line);
    }

    file.open("studentrecord.txt", ios::out | ios::app);
    if (file) {
        for (int i = cnt; i < cnt + no; i++) {
            file << unirec[i].name << "|" << unirec[i].Usn << "|" << unirec[i].age << "|" << unirec[i].Sem << "|" << unirec[i].Branch << "\n";
        }
        file.close();
        SetConsoleTextAttribute(h,10);
        cout << "Records added successfully!" << endl;
    } else {
        SetConsoleTextAttribute(h,12);
        cout << "Error opening file!" << endl;
    }
}
////////////////////////////////////////////////////////////////////////////////////////
void studentdelete_record(const char* usn) {
    fstream file, tempFile;
    bool found = false;

    file.open("studentrecord.txt", ios::in);
    if (!file) {
            SetConsoleTextAttribute(h,12);
        cout << "Error opening student record file!" << endl;
        return;
    }

    tempFile.open("temp.txt", ios::out);
    if (!tempFile) {
            SetConsoleTextAttribute(h,12);
        cout << "Error opening temporary file!" << endl;
        file.close();
        return;
    }

    char name[15], age[10], Sem[10], Branch[15], USN[15];

    while (file.getline(name, 15, '|') &&
           file.getline(USN, 15, '|') &&
           file.getline(age, 10, '|') &&
           file.getline(Sem, 10, '|') &&
           file.getline(Branch, 15, '\n')) {
        if (strcmp(USN, usn) == 0) {
            found = true;
            SetConsoleTextAttribute(h,14);
            cout << "Record with USN: " << USN << " deleted successfully.\n";
        } else {
            tempFile << name << "|" << USN << "|" << age << "|" << Sem << "|" << Branch << "\n";
        }
    }

    file.close();
    tempFile.close();

    if (!found) {
            SetConsoleTextAttribute(h,12);
        cout << "No record found with USN: " << usn << endl;
        remove("temp.txt"); // Clean up if no changes were made
    } else {
        remove("studentrecord.txt");         // Remove old file
        rename("temp.txt", "studentrecord.txt"); // Rename temp file to original name
    }
}


void studentdisplay_records() {
    fstream file;
    file.open("studentrecord.txt", ios::in);
    if (!file) {
            SetConsoleTextAttribute(h,12);
        cout << "Error opening file!" << endl;
        return;
    }
    SetConsoleTextAttribute(h,3);
    cout << "NAME\t  \tUSN\t  \tAGE\t  \tSEMESTER\t  BRANCH\n";
    while (file.getline(unirec[0].name, 15, '|') &&
           file.getline(unirec[0].Usn, 15, '|') &&
           file.getline(unirec[0].age, 10, '|') &&
           file.getline(unirec[0].Sem, 10, '|') &&
           file.getline(unirec[0].Branch, 15, '\n')) {
               SetConsoleTextAttribute(h,11);
        cout << unirec[0].name << "\t\t" << unirec[0].Usn << "\t\t" << unirec[0].age << "\t\t" << unirec[0].Sem << "\t\t" << unirec[0].Branch << endl;
    }

    file.close();
}

void studentsearch_record(const char* usn) {
    fstream file;
    file.open("studentrecord.txt", ios::in);
    if (!file) {
            SetConsoleTextAttribute(h,12);
        cout << "Error opening student record file!" << endl;
        return;
    }

    char name[15], age[10], Sem[10], Branch[15], USN[15];
    bool found = false;

    while (file.getline(name, 15, '|') &&
           file.getline(USN, 15, '|') &&
           file.getline(age, 10, '|') &&
           file.getline(Sem, 10, '|') &&
           file.getline(Branch, 15, '\n')) {
        if (strcmp(USN, usn) == 0) {
                SetConsoleTextAttribute(h,14);
            cout << "Student Found:\n";
        SetConsoleTextAttribute(h,14);
            cout << "Name: " << name << "\nUSN: " << USN
                 << "\nAge: " << age << "\nSemester: " << Sem
                 << "\nBranch: " << Branch << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
            SetConsoleTextAttribute(h,12);
        cout << "No student found with USN: " << usn << endl;
    }

    file.close();
}


// ************************* College Module *************************
void collegedelete_record(const char* cid) {
    fstream file, tempFile;
    bool found = false;

    file.open("collegerecord.txt", ios::in);
    if (!file) {
            SetConsoleTextAttribute(h,12);
        cout << "Error opening college record file!" << endl;
        return;
    }

    char name[15], course[15], CID[5];

    while (file.getline(name, 15, '|') &&
           file.getline(course, 15, '|') &&
           file.getline(CID, 5, '\n')) {
        if (strcmp(CID, cid) == 0) {
            found = true;
            SetConsoleTextAttribute(h,10);
            cout << "Are you sure you want to delete this record?\n";
            cout << "College Name: " << name << ", Course: " << course << ", CID: " << CID << "\n";
            cout << "Enter 'yes' to confirm deletion or 'no' to cancel: ";

            string confirmation;
            cin >> confirmation;
            if (confirmation != "yes") {
                    SetConsoleTextAttribute(h,12);
                cout << "Deletion canceled.\n";
                file.close();
                return;
            }
            break;
        }
    }

    file.close();

    if (found) {
        // Proceed to delete the record
        tempFile.open("temp.txt", ios::out);
        file.open("collegerecord.txt", ios::in);
        while (file.getline(name, 15, '|') &&
               file.getline(course, 15, '|') &&
               file.getline(CID, 5, '\n')) {
            if (strcmp(CID, cid) != 0) {
                tempFile << name << "|" << course << "|" << CID << "\n";
            }
        }
        file.close();
        tempFile.close();
        remove("collegerecord.txt");
        rename("temp.txt", "collegerecord.txt");
        SetConsoleTextAttribute(h,10);
        cout << "Record deleted successfully.\n";
    } else {
        SetConsoleTextAttribute(h,12);
        cout << "No record found with CID: " << cid << endl;
    }
}
void collegesearch_record(const char* cid) {
    fstream file;
    file.open("collegerecord.txt", ios::in);
    if (!file) {
            SetConsoleTextAttribute(h,12);
        cout << "Error opening college record file!" << endl;
        return;
    }

    char name[15], course[15], CID[5];
    bool found = false;

    while (file.getline(name, 15, '|') &&
           file.getline(course, 15, '|') &&
           file.getline(CID, 5, '\n')) {
        if (strcmp(CID, cid) == 0) {
                SetConsoleTextAttribute(h,9);
            cout << "College Found:\n";
            cout << "College Name: " << name << "\nCourse: " << course << "\nCID: " << CID << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
            SetConsoleTextAttribute(h,12);
        cout << "No record found with CID: " << cid << endl;
    }

    file.close();
}
void collegeadd_records() {
    fstream file;
    int no;
    char line[50];
    SetConsoleTextAttribute(h,9);
    cout << "\nEnter the number of colleges: ";
    cin >> no;
    cin.ignore(INT_MAX, '\n');

    for (int i = 0; i < no; i++) {
            SetConsoleTextAttribute(h,9);
        cout << "\nCOLLEGE NAME: ";
        cleanInput(line, sizeof(line));
        strcpy(unirec[i].name, line);

        SetConsoleTextAttribute(h,9);
        cout << "\nCOURSE      : ";
        cleanInput(line, sizeof(line));
        strcpy(unirec[i].course, line);

        SetConsoleTextAttribute(h,9);
        cout << "\nID          : ";
        cleanInput(line, sizeof(line));
        strcpy(unirec[i].CID, line);
    }

    file.open("collegerecord.txt", ios::out | ios::app);
    if (file) {
        for (int i = 0; i < no; i++) {
            file << unirec[i].name << "|" << unirec[i].course << "|" << unirec[i].CID << "\n";
        }
        file.close();
        SetConsoleTextAttribute(h,10);
        cout << "College records added successfully!" << endl;
    } else {
        SetConsoleTextAttribute(h,12);
        cout << "Error opening file!" << endl;
    }
}


void display_college_inventions(const char* cid) {
    fstream file;
    file.open("college_inventions.txt", ios::in);
    if (!file) {
        cout << "Error opening college inventions file!" << endl;
        return;
    }

    char collegeCID[5], inventionTitle[50], inventionDate[15];
    bool found = false;

    cout << "\nInventions/Research Papers for College ID: " << cid << endl;
    cout << "DATE\t\tTITLE\n";

    while (file.getline(collegeCID, 5, '|') &&
           file.getline(inventionTitle, 50, '|') &&
           file.getline(inventionDate, 15, '\n')) {
        if (strcmp(collegeCID, cid) == 0) {
            found = true;
            cout << inventionDate << "\t" << inventionTitle << endl;
        }
    }

    if (!found) {
        cout << "No inventions found for College ID: " << cid << endl;
    }

    file.close();
}
void collegedisplay_records() {
    fstream file;
    file.open("collegerecord.txt", ios::in);
    if (!file) {
        SetConsoleTextAttribute(h, 12); // Red error message
        cout << "Error opening college record file!" << endl;
        return;
    }

    SetConsoleTextAttribute(h, 9); // Table header color
    cout << "COLLEGE NAME\tCOURSE\tID\n";
    while (file.getline(unirec[0].name, 15, '|') &&
           file.getline(unirec[0].course, 10, '|') &&
           file.getline(unirec[0].CID, 5, '\n')) {
        cout << unirec[0].name << "\t\t" << unirec[0].course << "\t\t" << unirec[0].CID << endl;

        // Display inventions for this college
        display_college_inventions(unirec[0].CID);
    }

    file.close();
}



// ************************* Exam Schedule Module *************************
void examsadd_records() {
    fstream file;
    int no;
    char line[50];
    SetConsoleTextAttribute(h,3);
    cout << "\nEnter the number of exams to schedule: ";
    cin >> no;
    cin.ignore(INT_MAX, '\n');

    for (int i = 0; i < no; i++) {
            SetConsoleTextAttribute(h,3);
        cout << "\nCOURSE NAME : ";
        cleanInput(line, sizeof(line));
        strcpy(unirec[i].COURSE, line);

        SetConsoleTextAttribute(h,3);
        cout << "\nSTART DATE  : ";
        cleanInput(line, sizeof(line));
        strcpy(unirec[i].sdate, line);

        SetConsoleTextAttribute(h,3);
        cout << "\nEND DATE    : ";
        cleanInput(line, sizeof(line));
        strcpy(unirec[i].edate, line);
    }

    file.open("examschedule.txt", ios::out | ios::app);
    if (file) {
        for (int i = 0; i < no; i++) {
            file << unirec[i].COURSE << "|" << unirec[i].sdate << "|" << unirec[i].edate << "\n";
        }
        file.close();
        SetConsoleTextAttribute(h,10);
        cout << "Exam schedules added successfully!" << endl;
    } else {
        SetConsoleTextAttribute(h,12);
        cout << "Error opening file!" << endl;
    }
}
void exams_display_records() {
    fstream file;
    file.open("examschedule.txt", ios::in);
    if (!file) {
            SetConsoleTextAttribute(h,12);
        cout << "Error opening exam schedule file!" << endl;
        return;
    }

    SetConsoleTextAttribute(h,3);
    cout << "COURSE\t \tSTART DATE\t END DATE\n";
    while (file.getline(unirec[0].COURSE, 10, '|') &&
           file.getline(unirec[0].sdate, 5, '|') &&
           file.getline(unirec[0].edate, 5, '\n')) {
        cout << unirec[0].COURSE << "\t\t" << unirec[0].sdate << "\t\t" << unirec[0].edate << endl;
    }
    file.close();
}





// ************************* Result Module *************************
void resultadd_records() {
    fstream file;
    int no;
    char line[50];
    SetConsoleTextAttribute(h,3);
    cout << "\nEnter the number of student results to add: ";
    cin >> no;
    cin.ignore(INT_MAX, '\n');

    for (int i = 0; i < no; i++) {
            SetConsoleTextAttribute(h,3);
        cout << "\nSTUDENT NAME : ";
        cleanInput(line, sizeof(line));
        strcpy(unirec[i].sname, line);

        SetConsoleTextAttribute(h,3);
        cout << "\nUSN          : ";
        cleanInput(line, sizeof(line));
        strcpy(unirec[i].usn, line);

        SetConsoleTextAttribute(h,3);
        cout << "\nCOURSE       : ";
        cleanInput(line, sizeof(line));
        strcpy(unirec[i].course, line);

        SetConsoleTextAttribute(h,3);

        cout << "\n RESULT  : ";
        cleanInput(line, sizeof(line));
        strcpy(unirec[i].lab1, line);
    }

    file.open("resultrecord.txt", ios::out | ios::app);
    if (file) {
        for (int i = 0; i < no; i++) {
            file << unirec[i].sname << "|" << unirec[i].usn << "|" << unirec[i].course << "|" << unirec[i].lab1 << "\n";
        }
        file.close();
        SetConsoleTextAttribute(h,10);
        cout << "Result records added successfully!" << endl;
    } else {
        SetConsoleTextAttribute(h,12);
        cout << "Error opening file!" << endl;
    }
}

void result_display_records() {
    fstream file;
    file.open("resultrecord.txt", ios::in);
    if (!file) {
            SetConsoleTextAttribute(h,12);
        cout << "Error opening result record file!" << endl;
        return;
    }

    SetConsoleTextAttribute(h,3);
    cout << "STUDENT NAME\t USN\t COURSE\t LAB1 RESULT\n";
    while (file.getline(unirec[0].sname, 10, '|') &&
           file.getline(unirec[0].usn, 5, '|') &&
           file.getline(unirec[0].course, 10, '|') &&
           file.getline(unirec[0].lab1, 12, '\n')) {
        cout << unirec[0].sname << "\t\t" << unirec[0].usn << "\t\t" << unirec[0].course << "\t\t" << unirec[0].lab1 << endl;
    }
    file.close();
}

// ************************* Teacher Module *************************
void teacheradd_records() {
    fstream teacherFile, collegeInventionsFile;
    int no;
    char line[50];

    cout << "\nEnter the number of teachers to add: ";
    cin >> no;
    cin.ignore(INT_MAX, '\n');

    for (int i = 0; i < no; i++) {
        cout << "\nTEACHER NAME: ";
        cleanInput(line, sizeof(line));
        strcpy(unirec[i].Tname, line);

        // Ensure that the Teacher ID is unique
        while (true) {
            bool isDuplicate = false;

            cout << "\nTEACHER ID  : ";
            cleanInput(line, sizeof(line));

            // Check for duplicate IDs in the teacher records file
            fstream checkFile("teacherrecord.txt", ios::in);
            if (checkFile) {
                char existingName[15], existingID[10], department[15], subject[15];
                char qualification[50], research[50], date[15];
                while (checkFile.getline(existingName, 15, '|') &&
                       checkFile.getline(existingID, 10, '|') &&
                       checkFile.getline(department, 15, '|') &&
                       checkFile.getline(subject, 15, '|') &&
                       checkFile.getline(qualification, 50, '|') &&
                       checkFile.getline(research, 50, '|') &&
                       checkFile.getline(date, 15, '\n')) {
                    if (strcmp(existingID, line) == 0) {
                        isDuplicate = true;
                        cout << "Error: Teacher ID \"" << existingID << "\" already exists. Please enter a unique ID.\n";
                        break;
                    }
                }
                checkFile.close();
            }

            if (!isDuplicate) {
                strcpy(unirec[i].Tid, line); // Save the unique ID
                break; // Exit the loop if the ID is unique
            }
        }

        cout << "\nDEPARTMENT  : ";
        cleanInput(line, sizeof(line));
        strcpy(unirec[i].department, line);

        cout << "\nSUBJECT     : ";
        cleanInput(line, sizeof(line));
        strcpy(unirec[i].subject, line);

        cout << "\nEDUCATIONAL QUALIFICATION: ";
        cleanInput(line, sizeof(line));
        strcpy(unirec[i].Tqualification, line);

        cout << "\nNEW INVENTION / RESEARCH PAPER TITLE: ";
        cleanInput(line, sizeof(line));
        strcpy(unirec[i].Tresearch, line);

        cout << "\nDATE OF INVENTION / RESEARCH PAPER (YYYY-MM-DD): ";
        cleanInput(line, sizeof(line));
        strcpy(unirec[i].researchDate, line);

        cout << "\nASSOCIATED COLLEGE ID (CID): ";
        cleanInput(line, sizeof(line));
        strcpy(unirec[i].CID, line); // Associate invention with College ID

        // Append teacher record to teacherrecord.txt
        teacherFile.open("teacherrecord.txt", ios::out | ios::app);
        if (teacherFile) {
            teacherFile << unirec[i].Tname << "|" << unirec[i].Tid << "|" << unirec[i].department << "|" << unirec[i].subject << "|"
                        << unirec[i].Tqualification << "|" << unirec[i].Tresearch << "|" << unirec[i].researchDate << "|" << unirec[i].CID << "\n";
            teacherFile.close();
            cout << "Teacher record added successfully!" << endl;
        } else {
            cout << "Error opening teacher record file!" << endl;
            continue;
        }

        // Append invention to college_inventions.txt
        collegeInventionsFile.open("college_inventions.txt", ios::out | ios::app);
        if (collegeInventionsFile) {
            collegeInventionsFile << unirec[i].CID << "|" << unirec[i].Tresearch << "|" << unirec[i].researchDate << "\n";
            collegeInventionsFile.close();
            cout << "Invention added to College Inventions section successfully!" << endl;
        } else {
            cout << "Error opening college inventions file!" << endl;
        }
    }
}



void teacherdisplay_records() {
    fstream file;
    file.open("teacherrecord.txt", ios::in);
    if (!file) {
        SetConsoleTextAttribute(h, 12); // Red error message
        cout << "Error opening teacher record file!" << endl;
        return;
    }

    SetConsoleTextAttribute(h, 6); // Table header color
    cout << "NAME\t\tID\t\tDEPARTMENT\t\tSUBJECT\t\tQUALIFICATION\t\tRESEARCH PAPER\t\tDATE\n";

    while (file.getline(unirec[0].Tname, 15, '|') &&
           file.getline(unirec[0].Tid, 15, '|') &&
           file.getline(unirec[0].department, 15, '|') &&
           file.getline(unirec[0].subject, 15, '|') &&
           file.getline(unirec[0].Tqualification, 30, '|') &&
           file.getline(unirec[0].Tresearch, 50, '|') &&
           file.getline(unirec[0].researchDate, 15, '\n')) {
        SetConsoleTextAttribute(h, 11); // Record color
        cout << unirec[0].Tname << "\t\t" << unirec[0].Tid << "\t\t" << unirec[0].department << "\t\t"
             << unirec[0].subject << "\t\t" << unirec[0].Tqualification << "\t\t" << unirec[0].Tresearch << "\t\t"
             << unirec[0].researchDate << endl;
    }

    file.close();
}





int main() {
    cout << "\033[1m..............................U N I V E R S I T Y     M A N A G E M E N T      S Y S T E M ............................\n\n\033[0m";

    int choice;
    while (true) {
        cout << "\n\tW E L C O M E    T O   O U R   U N I V E R S I T Y";
        cout << "\n\t1. STUDENT";
        cout << "\n\t2. COLLEGE";
        cout << "\n\t3. EXAMS SCHEDULE";
        cout << "\n\t4. RESULT";
        cout << "\n\t5. TEACHER";
        cout << "\n\t6. ABOUT US";
        cout << "\n\t7. EXIT";
        cout << "\n\nEnter your choice: ";

        cin >> choice;
        cin.ignore(INT_MAX, '\n');

        switch (choice) {
            case 1: {
    int student_choice;
    while (true) {
        cout<<"\n\t\t ____________________________";
		cout<<"\n\t\t|      S T U D E N T         |";
		cout<<"\n\t\t|____________________________|";
		cout<<"\n\t\t|     1.ADD RECORD           |";
		cout<<"\n\t\t|............................|";
        	cout<<"\n\t\t|     2.DISPLAY RECORD       |";
		cout<<"\n\t\t|............................|";
       		cout<<"\n\t\t|     3.SEARCH RECORD        |";
		cout<<"\n\t\t|............................|";
       		cout<<"\n\t\t|     4.DELETE RECORD         |";
		cout<<"\n\t\t|............................|";
       		cout<<"\n\t\t|     5.EXIT              |";
		cout<<"\n\t\t|............................|";

		cout<<"\n";
		cout << "\nEnter your choice: ";
        cin >> student_choice;
        cin.ignore(INT_MAX, '\n');

        if (student_choice == 1) studentadd_records();
        else if (student_choice == 2) studentdisplay_records();
        else if (student_choice == 3) {
            char usn[15];
            cout << "Enter USN to search: ";
            cin.getline(usn, sizeof(usn));
            studentsearch_record(usn);
        }
        else if (student_choice == 4) {
            char usn[15];
            cout << "Enter USN to delete: ";
            cin.getline(usn, sizeof(usn));
            studentdelete_record(usn);
        }
        else if (student_choice == 5) break;
        else cout << "Invalid choice! Please try again.\n";
    }
    break;
}

           case 2: {
    int college_choice;
    while (true) {
        cout<<"\n\t\t_____________________________";
		cout<<"\n\t\t|      C O L L E G E         |";
		cout<<"\n\t\t|____________________________|";
		cout<<"\n\t\t|     1.ADD RECORD           |";
		cout<<"\n\t\t|............................|";
        cout<<"\n\t\t|     2.DISPLAY RECORD       |";
		cout<<"\n\t\t|............................|";
        cout<<"\n\t\t|     3.SEARCH RECORD        |";
		cout<<"\n\t\t|............................|";
        cout<<"\n\t\t|     4.DELETE RECORD        |";
		cout<<"\n\t\t|............................|";
		cout<<"\n\t\t|     5.EXIT                 |";
        cout<<"\n\t\t|............................|";
        cout<<"\n\t\t|____________________________|";
		cout<<"\n";
        cin >> college_choice;
        cin.ignore(INT_MAX, '\n');


        if (college_choice == 1) collegeadd_records();
        else if (college_choice == 2) collegedisplay_records();
        else if (college_choice == 3) {
            char cid[5];
            cout << "Enter CID to search: ";
            cin.getline(cid, sizeof(cid));
            collegesearch_record(cid);
        }
        else if (college_choice == 4) {
            char cid[5];
            cout << "Enter CID to delete: ";
            cin.getline(cid, sizeof(cid));
            collegedelete_record(cid);
        }
        else if (college_choice == 5) {
                break;
        }

        else cout << "Invalid choice! Please try again.\n";
    }

    break;

}


            case 3: {
                int exams_choice;
                while (true) {
        cout<<"\n\t\t ____________________________";
		cout<<"\n\t\t|  E X A M  S C H E D U L E  |";
		cout<<"\n\t\t|____________________________|";
		cout<<"\n\t\t|     1.ADD  Schedule        |";
		cout<<"\n\t\t|............................|";
        cout<<"\n\t\t|     2.DISPLAY Schedule     |";
		cout<<"\n\t\t|............................|";
		cout<<"\n\t\t|     3.EXIT                 |";
        cout<<"\n\t\t|............................|";
		cout<<"\n\t\t|____________________________|";
		cout<<"\n";

                    cin >> exams_choice;
                    cin.ignore(INT_MAX, '\n');
                    if (exams_choice == 1) examsadd_records();
                    else if (exams_choice == 2) exams_display_records();
                    else if (exams_choice == 3) break;
                    else cout << "Invalid choice! Please try again.\n";
                }
                break;
            }
            case 4: {
                int result_choice;
                while (true) {
        cout<<"\n\t\t ____________________________";
		cout<<"\n\t\t|       R E S U L T          |";
		cout<<"\n\t\t|____________________________|";
		cout<<"\n\t\t|     1.ADD RECORD           |";
		cout<<"\n\t\t|............................|";
        cout<<"\n\t\t|     2.DISPLAY RECORD       |";
        cout<<"\n\t\t|............................|";
        cout<<"\n\t\t|     3.EXIT                 |";
        cout<<"\n\t\t|............................|";
		cout<<"\n\t\t|____________________________|";
		cout<<"\n";
                    cin >> result_choice;
                    cin.ignore(INT_MAX, '\n');
                    if (result_choice == 1) resultadd_records();
                    else if (result_choice == 2) result_display_records();
                    else if (result_choice == 3) break;
                    else cout << "Invalid choice! Please try again.\n";
                }
                break;
            }
            case 5: {
                int teacher_choice;
                while (true) {
                    cout << "\n\tTEACHER MODULE";
                    cout << "\n\t1. Add Teacher Records";
                    cout << "\n\t2. Display Teacher Records";
                    cout << "\n\t3. Exit";
                    cout << "\nEnter your choice: ";
                    cin >> teacher_choice;
                    cin.ignore(INT_MAX, '\n');
                    if (teacher_choice == 1) teacheradd_records();
                    else if (teacher_choice == 2) teacherdisplay_records();
                    else if (teacher_choice == 3) break;
                    else cout << "Invalid choice! Please try again.\n";
                }
                break;
            }
            case 6: {
        cout<<"\n\t\t _______________________________";
		cout<<"\n\t\t|      A B O U T   U S          |";
		cout<<"\n\t\t|______________________________|";
		cout<<"\n\t\t|       1.PERFORMANCE          |";
		cout<<"\n\t\t|..............................|";
        cout<<"\n\t\t|       2.EXIT                 |";
		cout<<"\n\t\t|______________________________|";
		cout<<"\n";
                break;
            }
            case 7:
                cout << "Exiting the University Management System. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}



