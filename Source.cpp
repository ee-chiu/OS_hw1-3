#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <ctime>
#include <fstream>
#include <dirent.h>
#include <string.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <sys/wait.h>

using namespace std;

bool isDigit(char c) {
	return c >= '0' && c <= '9';
}

bool isNumber(char* d_name) {
	int i = 0;
	while (isdigit(d_name[i]))
		i++;
	return d_name[i] == '\0';
}

bool sameUid(struct dirent* dirp, uid_t my_uid, uid_t &this_uid) {
	string pid = dirp->d_name;
	string status = "/proc/" + pid + "/status";
	fstream file;
	file.open(status, ios::in);
	string s;
	while (s != "Uid:")
		file >> s;

	file >> this_uid;

	return this_uid == my_uid;
}

string getCMD(struct dirent* dirp) {
	string pid = dirp->d_name;
	string cmdline = "/proc/" + pid + "/cmdline";
	string CMD;
	fstream file;

	file.open(cmdline, ios::in);
	file >> CMD;

	return CMD;
}

int main(void)
{
	string arg; /*command line arguments*/
	int should_run = 1; /*flag to determine when to exit program*/

	while (should_run) {
		printf("osh>");
		fflush(stdout);

		/**
		* your code!
		* After reading user input, the step are:
		* (1) fork a child process using fork()
		* (2) the child process will invoke execvp()
		*/

		cin >> arg;
		if (arg == "exit")
			break;

		else if (arg == "cat") {
			string arg1 = "cat";
			string arg2;
			cin >> arg2;

			char* arg[3] = { strdup(arg1.c_str()), strdup(arg2.c_str()), NULL };
			pid_t pid = fork();
			if (pid == 0)
				execvp(arg[0], arg);
			else if (pid > 0)
				wait(NULL);
			
			continue;
		}

		else if (arg == "ls") {
			string arg1 = "ls";

			char* arg[3] = { strdup(arg1.c_str()), NULL };
			pid_t pid = fork();
			if (pid == 0)
				execvp(arg[0], arg);
			else if (pid > 0)
				wait(NULL);

			continue;
		}

		else if (arg == "date") {
			string arg1 = "date";

			char* arg[3] = { strdup(arg1.c_str()), NULL };
			pid_t pid = fork();
			if (pid == 0)
				execvp(arg[0], arg);
			else if (pid > 0)
				wait(NULL);

			continue;
		}

		else if (arg == "ps") {
			string f;
			cin >> f;
			if (f != "-f") {
				cout << "Error command!" << endl;
				continue;
			}
			
			string arg1 = "ps";
			string arg2 = "-f";

			char* arg[3] = { strdup(arg1.c_str()), strdup(arg2.c_str()), NULL };
			pid_t pid = fork();
			if (pid == 0) 
				execvp(arg[0], arg);
			else if (pid > 0)
				wait(NULL);

			continue;
		}
	}

	return 0;
}


