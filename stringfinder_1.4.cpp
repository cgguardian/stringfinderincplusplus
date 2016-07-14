#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <dirent.h>
#include <algorithm>
#include <unistd.h>
#include <windows.h>
#include <sys/types.h>
#include <sys/stat.h>
using namespace std;

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

int main () { 
	char restart = 'y';
	cout << "Welcome.\n";
	cout << "Please make sure your input (.txt) files are labeled according to this list:\n" << "___________________________________________________________________________\n";
	cout << "Input files are in the input folder\n";
	cout << "Words/strings to find are in find.txt\n" << "Words/strings to replace with are in replace.txt\n";
	cout << "List of document names to search are in olddocs.txt\n" << "Names of the output documents are in newdocs.txt\n\n" << endl;
		
	while (restart == 'y'){
		char toCont = ' ';
		cout << "Are all of your documents ready for use? (y/n): ";
		cin >> toCont;
		
		while ((toCont != 'y')&&(toCont != 'n')){
			cout << "Please enter a valid selection. (y/n): ";
			cin >> toCont;
		}
		
		if (toCont == 'y'){
			char choice = ' ';
			cout << "___________________________________________________________________________\n";
			cout << "Would you like to edit the contents of a single file or directory?\n" << "(Single = s, Directory = d): ";
			cin >> choice;
			
			while ((choice != 's') && (choice != 'd')){
			  	cout <<  "That is not a valid option. Please choose one of the correct options. (Single = s, Directory = d): ";
				cin >> choice;
			}
			
			if (choice == 's'){
				char isInSingle = ' ';
				cout << "\nIs the file in this program's folder? (y/n): ";
				cin >> isInSingle;
				
				while ((isInSingle != 'y') && (isInSingle != 'n')){
				  	cout <<  "That is not a valid option. Please choose one of the correct options. (y/n): ";
					cin >> isInSingle;
				}
			
				if (isInSingle == 'y'){
					
					string fileName, fileType, singleEdit, singleDone;
					char inOut;
					
					cout << "Are you using input/output folders? (y/n): ";
					cin >> inOut;
					cout << "\nFile name?: ";
					cin >> fileName;
					cout << "File type?: ";
					cin >> fileType;
					
					transform(fileType.begin(), fileType.end(), fileType.begin(), ::tolower);
					
					
					while ((inOut != 'y') && (inOut != 'n')){
					  	cout <<  "That is not a valid option. Please choose one of the correct options. (y/n): ";
						cin >> inOut;
					}
					
					if (inOut == 'y'){
						singleEdit = "input\\" + fileName + "." + fileType;
						singleDone = "output\\" + fileName + "-new" + "." + fileType;
					}
					else if (inOut == 'n'){
						singleEdit = fileName + "." + fileType;
						singleDone = fileName + "-new" + "." + fileType;
					}
					else{}
					
					ifstream myfile_in(singleEdit.c_str());
					ofstream myfile_out(singleDone.c_str());
					
					int i = 0;
				    int in = 0;
					string line, ismade;
					int t, numWords;
					
					cout << "How many words/strings are you searching for?: ";
					cin >> numWords;
					
					ifstream finding("find.txt");
					string find[numWords];
					
					for(t = 0; t < numWords; ++t)
					{
					    finding >> find[t];
					}
					        
					ifstream replacing("replace.txt");
					string replace[numWords];
					
					for(t = 0; t < numWords; ++t)
					{
					    replacing >> replace[t];
					}
					
					while (!myfile_in.eof())
				    {		
						getline (myfile_in,line, ' ');
						for (in = 0; in < numWords; in++){
						    if (line.find(find[in]) != std::string::npos){
								replaceAll(line, find[in], replace[in]);
						        myfile_out << line << endl;
								i++;
						    }
						
							else{
							}
						}
							
						if (i == 0){
							myfile_out << line << endl;
						}
						i = 0;	
					}
					myfile_in.close();
					//system("PAUSE");
				}
				
				else if (isInSingle == 'n'){
					string dirName, fileName, fileType, singleEdit, singleDone;
					
					cout << "\nWhat is the directory of the input/output folders?: ";
					cin >> dirName;
	
					const char * bb = dirName.c_str();
					
					struct stat info;
	
					while ( stat( bb, &info ) != 0 ){
					    cout << "Cannot access " << dirName << ".\n";
					    cout << "Please enter a valid directory: ";
					    cin >> dirName;
						bb = dirName.c_str();
					}
					
					/*
					if( info.st_mode & S_IFDIR){
					    cout << "There is a directory named "<< dirName << endl;
					}*/
					
					cout << "\nFile name?: ";
					cin >> fileName;
					cout << "File type?: ";
					cin >> fileType;
					
					transform(fileType.begin(), fileType.end(), fileType.begin(), ::tolower);
					
					singleEdit = dirName + "\\input\\" + fileName + "." + fileType;
					
					singleDone = dirName + "\\output\\" + fileName + "-new" + "." + fileType;
				
					ifstream myfile_in(singleEdit.c_str());
					ofstream myfile_out(singleDone.c_str());
					
					int i = 0;
				    int in = 0;
					string line, ismade;
					int t, numWords;
					
					cout << "How many words/strings are you searching for?: ";
					cin >> numWords;
					
					ifstream finding("find.txt");
					string find[numWords];
					
					for(t = 0; t < numWords; ++t)
					{
					    finding >> find[t];
					}
					        
					ifstream replacing("replace.txt");
					string replace[numWords];
					
					for(t = 0; t < numWords; ++t)
					{
					    replacing >> replace[t];
					}
					
					
					while (!myfile_in.eof())
				    {		
						getline (myfile_in,line, ' ');
						for (in = 0; in < numWords; in++){
						    if (line.find(find[in]) != std::string::npos){
								replaceAll(line, find[in], replace[in]);
						        myfile_out << line << endl;
								i++;
						    }
						
							else{
							}
						}
							
						if (i == 0){
							myfile_out << line << endl;
						}
						i = 0;	
					}
					myfile_in.close();
					//system("PAUSE");
				}
				
			}
			
			else if (choice == 'd'){
			string dirName;
			
			cout << "\nDirectory to open?: ";
			cin >> dirName;
			
			transform(dirName.begin(), dirName.end(), dirName.begin(), ::tolower);
			
			/////////////////////////////////////////////////////////////////////////////////////////////////////////
			
			const char * bb = dirName.c_str();
					
				struct stat info;
	
				while ( stat( bb, &info ) != 0 ){
					cout << "Cannot access " << dirName << ".\n";
					cout << "Please enter a valid directory: ";
					cin >> dirName;
					bb = dirName.c_str();
				}
				
			string dirFull = dirName + "\\input";
			const char * cc = dirFull.c_str();
			int count;
			
			DIR *dir;
			struct dirent *ent;
			if ((dir = opendir (cc)) != NULL) {
			  while ((ent = readdir (dir)) != NULL) {
			    count++;
			  }
			  closedir (dir);
			} else {
			  perror ("");
			  return EXIT_FAILURE;
			}
			
			/////////////////////////////////////////////////////////////////////////////////////////////////////////
			
			int t, g, k;
			int numDocs = 41;
			int numWords = 0;
			string word;
			
			cout << "\nHow many words/strings are you searching for?: ";
			cin >> numWords;
			
			ifstream finding("find.txt");
			
			string find[numWords];
			
			for(t = 0; t < numWords; ++t)
			{
			    finding >> find[t];
			}
			        
			ifstream replacing("replace.txt");
			string replace[numWords];
			
			for(t = 0; t < numWords; ++t)
			{
			    replacing >> replace[t];
			}
			
			/////////////////////////////////////////////////////////////////////////////////////////////////////////
			
			/*
			int g, t, k, numWords;
			int numDocs = count - 2;
			string fileType;
			
			ifstream finding("find.txt");
			
			int A = 0;
			int B = 0;
			string word, wordi;
			
			while (finding >> word) { 
			A++; }
			
			string *find;
			find=new string[A];

			
			for(t = 0; t < A; ++t)
			{
			    finding >> find[t];
			}
			        
			ifstream replacing("replace.txt");
			while (replacing >> wordi) { 
			++B; }

			string *replace;
			replace=new string[B];
			
			for(k = 0; t < B; ++k)
			{
			    replacing >> replace[k];
			}
			
			if (A != B) {
			  	cout << "\nError! The program must use two documents of equal length.\n";
			  	cout << "find.txt == " << A << " items.\n";
			  	cout << "replace.txt == " << B << " items.\n";
				cout << "Please adjust the files accordingly. Thank you." << endl;
				system("PAUSE");
				cout << "This window will now close.\n";
				return 0;
			}
			else {
				numWords = A;
			}
			*/
			/////////////////////////////////////////////////////////////////////////////////////////////////////////
			
			string fileType;
			
			ifstream oldFiles("olddocs.txt");
			string oldF[numDocs];
			
			for(t = 0; t < numDocs; ++t)
			{
			    oldFiles >> oldF[t];
			}
			        
			ifstream newFiles("newdocs.txt");
			string newF[numDocs];
			
			for(t = 0; t < numDocs; ++t)
			{
			    newFiles >> newF[t];
			}
			
			/////////////////////////////////////////////////////////////////////////////////////////////////////////
			
			cout << "\nWhat type of files will you be editing? (File extension): ";
			cin >> fileType;
			
			for (g = 0; g < numDocs; g++){
				string firstfile, secondfile;
		
				firstfile = dirName + "\\input\\" + oldF[g] + "." + fileType;
				secondfile = dirName + "\\output\\" + newF[g] + "." + fileType;
				
				ifstream myfile_in(firstfile.c_str());
				ofstream myfile_out(secondfile.c_str());
				
				/////////////////////////////////////////////////////////////////////////////////////////////////////////
				
				int i = 0;
			    int in = 0;
				string line, ismade;
				
				/*
				while (!myfile_in.eof())
			    {		
					getline (myfile_in,line, ' ');
					
					for (in = 0; in < numWords; in++){
					    if (line.find(find[in]) != std::string::npos){
							replaceAll(line, find[in], replace[in]);
							//myfile_out << line << endl;
					    }
					
						else{
						}
					}
					//cout << line << endl;
					myfile_out << line << endl;
					i = 0;
					//system("PAUSE");
				}
				*/
				
				while (!myfile_in.eof())
			    {
					getline (myfile_in,line, ' ');
					//system("PAUSE");
					for (in = 0; in < numWords; in++){
					    if (line.find(find[in]) != std::string::npos){
							replaceAll(line, find[in], replace[in]);
					        myfile_out << line << endl;
					        //cout << line << endl;
							i++;
					    }
					
						else{
						}
					}
						
					if (i == 0){
						myfile_out << line << endl;
						//cout << line << endl;
					}
					i = 0;	
				}
				myfile_in.close();
				//system("PAUSE");
			}
		  	
		  }
		  else{
		  	cout << "Break. Please report this to the administrator.\n";
			system("PAUSE");
			return 0;;
			}
		}
		else{
		cout << "\nThank you, please prepare your documents for the next use of this program.\n" << "Goodbye.\n" << endl;
		system("PAUSE");
		return 0;	
		}
		
		cout << "\nPlease wait";
		sleep(2);
		cout << ".";
		sleep(2.5);
		cout << ".";
		sleep(3);
		cout << ".";
		sleep(1);
		cout << "\n\n";
		
		cout << "Your file(s) have been modified.\n" << "Would you like to run this program again? (y/n): ";
		cin >> restart;
		
		while ((restart != 'y')&&(restart != 'n')){
			cout << "Please enter a valid selection. (y/n): ";
			cin >> restart;
		}
		system("cls");
	}
	cout << "Thank you for using this program. Have a nice day!\n" << endl;
	system("PAUSE");
	return 0;
}
