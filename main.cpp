#include <iostream>
#include <string>
#include <cstdio>
#include <thread>
#include <chrono>
#include <unistd.h>

using namespace std;

string GetStringFromCommand(string cmd) 
{
	string data;
	FILE * stream;
	const int max_buffer = 256;
	char buffer[max_buffer];
	cmd.append(" 2>&1");

	stream = popen(cmd.c_str(), "r");
	if (stream) 
	{
		while (!feof(stream))
			if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
			pclose(stream);
	}
	return data;
}

void writeToFileSerialNumberWithoutSpaces()
{
	int k = 0;
	int spaces = 0;
	string ls = GetStringFromCommand("sudo dmidecode -t system | grep Serial");
	char p[ls.length()];

	for (int i = 0; i < sizeof(p); i++) {
		p[i] = ls[i];
		if (p[i] == ' ') {
			spaces++;
		}
	}

	char serialKey[ls.length() - spaces];

	for (int i = 16; i < sizeof(p); i++) {
		if (p[i] != ' ') {
			serialKey[k] = p[i];
			k++;
		}
	}

	freopen ("system_key.txt","w",stdout);
	printf("%s" , serialKey);
	fclose(stdout);
}
string login, password;
char key[1000];
int key_size = 0;

string char_encrypting(char c)
{
	if(isdigit(c) == true)
	{
		switch(c){	
			case '0' :
	        	return "a"; 
	         	break;

			case '1' :
	        	return "b"; 
	         	break;

	        case '2' :
	        	return "c"; 
	         	break;

	        case '3' :
	        	return "d"; 
	         	break;   

	        case '4' :
	        	return "e"; 
	         	break;

	        case '5' :
	        	return "f"; 
	         	break;

	        case '6' :
	        	return "g"; 
	         	break;     

	        case '7' :
	        	return "h"; 
	         	break;

			case '8' :
	        	return "i"; 
	         	break;

			case '9' :
	        	return "j"; 
	         	break;

		}
	}
	else if(isdigit(c) == false)
	{
		switch(c)
		{
			case 'a' :
	        	return "1"; 
	         	break;

			case 'b' :
	        	return "2"; 
	         	break;

	        case 'c' :
	        	return "3"; 
	         	break;

	        case 'd' :
	        	return "4"; 
	         	break;   

	        case 'e' :
	        	return "5"; 
	         	break;

	        case 'f' :
	        	return "6"; 
	         	break;

	        case 'g' :
	        	return "7"; 
	         	break;     

	        case 'h' :
	        	return "8"; 
	         	break;

			case 'i' :
	        	return "9"; 
	         	break;

			case 'j' :
	        	return "10"; 
	         	break;

			case 'k' :
	        	return "11"; 
	         	break;

			case 'l' :
	        	return "12"; 
	         	break;

	        case 'm' :
	        	return "13"; 
	         	break;

	        case 'n' :
	        	return "14"; 
	         	break;   

	        case 'o' :
	        	return "15"; 
	         	break;

	        case 'p' :
	        	return "16"; 
	         	break;

	        case 'q' :
	        	return "17"; 
	         	break;     

	        case 'r' :
	        	return "18"; 
	         	break;

			case 's' :
	        	return "19"; 
	         	break;

			case 't' :
	        	return "20"; 
	         	break;

	        case 'u' :
	        	return "21"; 
	         	break;

	        case 'v' :
	        	return "22"; 
	         	break;

	        case 'w' :
	        	return "23"; 
	         	break;     

	        case 'x' :
	        	return "24"; 
	         	break;

			case 'y' :
	        	return "25"; 
	         	break;

			case 'z' :
	        	return "26"; 
	         	break;
	    }
	}
}


void key_generator(string s1 , string s2)
{
	string adding_enc = "";
	for(int i = 0; i < s1.size(); i++)
	{
		adding_enc = char_encrypting(s1[i]);
		if(adding_enc.size() == 2)
		{
			key[key_size] = adding_enc[0];
			key[key_size + 1] = adding_enc[1];
			key_size += 2;
		}
		else if(adding_enc.size() == 1)
		{
			key[key_size] = adding_enc[0];
			key_size++;
		}
	}
	for(int i = 0; i < s2.size(); i++)
	{
		adding_enc = char_encrypting(s2[i]);
		if(adding_enc.size() == 2)
		{
			key[key_size] = adding_enc[0];
			key[key_size + 1] = adding_enc[1];
			key_size += 2;
		}
		else if(adding_enc.size() == 1)
		{
			key[key_size] = adding_enc[0];
			key_size++;
		}
	}	

	freopen ("user_key.txt","w",stdout);
	printf("%s" ,key);
	fclose(stdout);
}  

char key2[1000];
int key_size2 = 0;
void key_generator_temp(string s1 , string s2)
{
	string adding_enc = "";
	for(int i = 0; i < s1.size(); i++)
	{
		adding_enc = char_encrypting(s1[i]);
		if(adding_enc.size() == 2)
		{
			key2[key_size2] = adding_enc[0];
			key2[key_size2 + 1] = adding_enc[1];
			key_size2 += 2;
		}
		else if(adding_enc.size() == 1)
		{
			key2[key_size2] = adding_enc[0];
			key_size2++;
		}
	}
	for(int i = 0; i < s2.size(); i++)
	{
		adding_enc = char_encrypting(s2[i]);
		if(adding_enc.size() == 2)
		{
			key2[key_size2] = adding_enc[0];
			key2[key_size2 + 1] = adding_enc[1];
			key_size2 += 2;
		}
		else if(adding_enc.size() == 1)
		{
			key2[key_size2] = adding_enc[0];
			key_size2++;
		}
	}	

	freopen ("user_key_temp.txt","w",stdout);
	printf("%s" ,key2);
	fclose(stdout);
}  

void openModule()
{
	string open1 = GetStringFromCommand("make");
	string open2 = GetStringFromCommand("sudo insmod project.ko");
}

void closeModule()
{
	string open3 = GetStringFromCommand("sudo rmmod project");	
}

void doLogin()
{

	printf("Enter your login:\n");
	cin >> login;
	printf("Enter your password:\n");
	cin >> password;
	printf("Check you PC info...\n");
	key_generator_temp(login, password);

	for (int i = 0; i < 1000; i++)
	{
		usleep(5000000);
		openModule();
		closeModule();
	}
}

void doRegister()
{
	printf("You can use only one licence for 1 PC and 1 User.\n");
	printf("Enter your login:\n");
	cin >> login;
	printf("Enter your password:\n");
	cin >> password;
	printf("Saving your PC info\n");
	writeToFileSerialNumberWithoutSpaces();
	key_generator(login, password);
	printf("Successfull\n");
}


void helloUser()
{
	printf("Hello, User\n");
	printf("If you have license, please log in. Otherwise register a license.\n");
	printf("For log in type: 1\n");
	printf("For register type: 2\n");
	int userChoise = 0;
	cin >> userChoise;

	switch (userChoise) {
		case 1:
		{
			doLogin();
			break;
		}
		case 2:
		{
			doRegister();
			break;
		}
		default:
		{
			printf("Please, enter 1 or 2.\n");
			break;
		}
	}
}

int main ()
{

	//string ls = GetStringFromCommand("sudo dmidecode -t system | grep Serial");
	//getSerialNumberWithoutSpaces();

	helloUser();
	return 0;
}