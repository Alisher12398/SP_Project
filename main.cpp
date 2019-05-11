#include <iostream>
#include <string>
#include <cstdio>

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
}

void doLogin()
{
	/*
	printf("Enter your login:\n");
	cin >> login;
	printf("Enter your password:\n");
	cin >> password;
	printf("Thank You!\n Now we can generate your personal key...\n");
	key_generator(login, password);
	printf("The key value is generated, Congratulatons!\n");
	printf("key value: %s key_size: %d\n" ,key ,key_size);

	freopen ("new_key.txt","w",stdout);
	printf("%s" ,key);
	*/

	printf("Enter your login:\n");
	cin >> login;
	printf("Enter your password:\n");
	cin >> password;
	printf("Check you PC info...\n");
}


void helloUser()
{
	printf("Hello, User\n");
	printf("If you have license, please log in. Otherwise register a license.\n");
	printf("For log in type: 1\n");
	printf("For register type: 1\n");
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