#include <string>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "version.h"
// New Comment Update
using namespace std;

int main(int argc, char *argv[]) {
	displayVersion();
	string url = argv[1];
	
	// Variables for website parts
	string protocol;
	string domain;
	int port = 0;
	string filePath;
	string parameters;
	bool protocolCorrect = true;
	bool portCorrect = true;
	bool domainCorrect = true;
	bool filePathCorrect = true;
	bool portExist = false;
	bool parameterExist = false;

	int currentPosition = 0;
	int endPosition = 0;

	endPosition = url.find("://", currentPosition);
	protocol = url.substr(currentPosition, endPosition);
	
	if(protocol != "http" &&  protocol != "https" && protocol != "ftp" && protocol != "ftps")
		protocolCorrect = false;

	currentPosition = endPosition + 3;

	endPosition = url.find(".", currentPosition);
	endPosition = url.find(".", endPosition+1);

	string domainCheck;

	int portCheck = 0;

	portCheck = url.find(":", endPosition+1);

	if(portCheck != -1) {
		domainCheck = url.substr(endPosition+1, portCheck - endPosition - 1);
		
		endPosition = portCheck;
		domain = url.substr(currentPosition, endPosition - currentPosition);

		endPosition = url.find("/", portCheck+1);
		portExist = true;

		string stringPort = url.substr(portCheck+1, endPosition - portCheck - 1);
		port = atoi(stringPort.c_str());
		
		if(port < 1 || port > 65535)
			portCorrect = false;

		currentPosition = endPosition + 1;
	}
	else {
		int domainCheckStart = endPosition+1;
	
		endPosition = url.find("/", endPosition+1);

		domainCheck = url.substr(domainCheckStart, endPosition - domainCheckStart);

		domain = url.substr(currentPosition, endPosition - currentPosition);
		
		currentPosition = endPosition + 1;
	}

	if(domainCheck != "com" && domainCheck != "gov" && domainCheck != "edu" && domainCheck != "net" && domainCheck != "biz")
		domainCorrect = false;

	endPosition = url.find(".", currentPosition);
	
	string filePathCheck;

	int parameterCheck = 0;

	parameterCheck = url.find("?", endPosition+1);

	if(parameterCheck != -1) {
		filePathCheck = url.substr(endPosition+1, parameterCheck - endPosition - 1);

		endPosition = parameterCheck;
		filePath = url.substr(currentPosition-1, endPosition - currentPosition+1);
		
		parameterExist = true;
		currentPosition = endPosition+1;
		
		parameters = url.substr(currentPosition-1, -1);
	}
	else {
		filePathCheck = url.substr(endPosition+1, -1);

		filePath = url.substr(currentPosition-1, -1);
	}
	
	if(filePathCheck != "html" && filePathCheck != "htm")
		filePathCorrect = false;

	if(filePathCorrect == false || domainCorrect == false || portCorrect == false || protocolCorrect == false) {
		cout << "Invalid URL with following erroneous components:" << endl;
		if(protocolCorrect ==  false) {
			cout << left << setw(20) << "Protocol:";
			cout << protocol << " is not a valid protocol." << endl;
		}

		if(domainCorrect == false) {
			cout << left << setw(20) << "Domain:";
			cout << domainCheck << " is an invalid domain name." << endl;
		}

		if(portCorrect == false) {
			cout << left << setw(20) << "Port:";
			cout << "port number must be between 1 and 65535" << endl;
		}

		if(filePathCorrect == false) {
			cout << left << setw(20) << "File path:";
			cout << filePathCheck << " is not a valid file path." << endl;
		}
	}
	else {
		cout << left << setw(20) << "Protocol:";
		cout << protocol << endl;
		cout << setw(20) << "Domain:";
		cout << domain << endl;
		
		if(portExist == true){
			cout << setw(20) << "Port:";
			cout << port << endl;
		}
		
		cout << setw(20) << "File Path:";
		cout << filePath << endl;

		if(parameterExist == true) {
			cout << setw(20) << "Parameters:";
			cout << parameters << endl;
		}
	}
}
