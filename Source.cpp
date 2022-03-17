#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<iomanip>
using namespace std;

int main(int argc, char* argv[]) {

	long long maxIt = 10000;

	float initialPoint1 = 0;
	float initialPoint2 = 0;

	bool secTag = false;
	bool newtTag = false;
	bool hybridTag = false;

	string fileName;
	string userInput;

	if (argc < 3) {

		cout << "Too few arguments. Need at least two initial points and a file name." << endl;

		return 0;

	}

	if (argc > 7) {

		cout << "Too many arguments." << endl;

		return 0;

	}

	switch (argc) {

	case 4:

		if (strtof(argv[1], NULL)) {

			initialPoint1 = stof(argv[1]);

			if (!stof(argv[2], NULL)) {

				cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
				return 0;

			}

			initialPoint2 = stof(argv[2]);
			fileName = argv[3];

			break;
		}

		if (string(argv[1]) == "-newt") {

			newtTag = true;

			if (!strtof(argv[2], NULL)) {

				cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
				return 0;

			}

			initialPoint1 = stof(argv[2]);
			fileName = argv[3];

			break;
		}

		cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
		return 0;

	case 5:

		if (string(argv[1]) == "-sec") {

			secTag = true;

			if (!strtof(argv[2], NULL)) {

				cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
				return 0;

			}

			initialPoint1 = stof(argv[2]);

			if (!strtof(argv[3], NULL)) {

				cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
				return 0;

			}

			initialPoint2 = stof(argv[3]);
			fileName = argv[4];

			break;
		}

		if (string(argv[1]) == "-hybrid") {

			hybridTag = true;

			if (!strtof(argv[2], NULL)) {

				cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
				return 0;

			}

			initialPoint1 = stof(argv[2]);

			if (!strtof(argv[3], NULL)) {

				cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
				return 0;

			}

			initialPoint2 = stof(argv[3]);
			fileName = argv[4];

			break;
		}

		cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
		return 0;

	case 6:

		if (string(argv[1]) == "-maxIt") {

			if (!strtol(argv[2], NULL, 0)) {

				cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
				return 0;

			}

			maxIt = stoi(argv[2]);

			if (!strtof(argv[3], NULL)) {

				cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
				return 0;

			}

			initialPoint1 = stof(argv[3]);

			if (!strtof(argv[4], NULL)) {

				cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
				return 0;

			}

			initialPoint2 = stof(argv[4]);
			fileName = argv[5];

			break;
		}

		if (string(argv[1]) == "-newt") {

			newtTag = true;

			if (string(argv[2]) != "-maxIt") {

				cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
				return 0;

			}

			if (!strtol(argv[3], NULL, 0)) {

				cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
				return 0;

			}

			maxIt = stoi(argv[3]);

			if (!strtof(argv[4], NULL)) {

				cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
				return 0;

			}

			initialPoint1 = stof(argv[4]);
			fileName = argv[5];

			break;
		}

		cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
		return 0;

	case 7:

		if (string(argv[1]) == "-sec") {

			secTag = true;

			if (string(argv[2]) != "-maxIt") {

				cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
				return 0;

			}

			if (!strtol(argv[3], NULL, 0)) {

				cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
				return 0;

			}

			maxIt = stoi(argv[3]);

			if (!strtof(argv[4], NULL)) {

				cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
				return 0;

			}

			initialPoint1 = stof(argv[4]);

			if (!strtof(argv[5], NULL)) {

				cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
				return 0;

			}

			initialPoint2 = stof(argv[5]);
			fileName = argv[6];

			break;
		}

		if (string(argv[1]) == "-hybrid") {

			hybridTag = true;

			if (string(argv[2]) != "-maxIt") {

				cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
				return 0;

			}

			if (!strtol(argv[3], NULL, 0)) {

				cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
				return 0;

			}

			maxIt = stoi(argv[3]);

			if (!strtof(argv[4], NULL)) {

				cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
				return 0;

			}

			initialPoint1 = stof(argv[4]);

			if (!strtof(argv[5], NULL)) {

				cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
				return 0;

			}

			initialPoint2 = stof(argv[5]);
			fileName = argv[6];

			break;
		}

		cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
		return 0;
	}

	cout << newtTag << " " << secTag << " " << hybridTag << " " << maxIt << " " << initialPoint1 << " " << initialPoint2 << " " << fileName << endl;

	return 0;
}