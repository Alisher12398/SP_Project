#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

string getSerialNumberWithoutSpaces()
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

	char p2[ls.length() - spaces];

	for (int i = 16; i < sizeof(p); i++) {
		if (p[i] != ' ') {
			p2[k] = p[i];
			k++;
		}
	}

	for (int i = 0; i < k; i++) {
		cout << p2[i];
	}
}

int main ()
{

	string ls = GetStringFromCommand("sudo dmidecode -t system | grep Serial");
	getSerialNumberWithoutSpaces();

	return 0;
}