#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<iomanip>
#include<cmath>

using namespace std;



float applyFunction(float variablePar, vector<float> functionPar) {

	float returnValue = 0;

	for (int i = 0; i < functionPar.size(); i++) {

		returnValue += (functionPar[i] * pow(variablePar, i));

	}

	return returnValue;
}

int getSize(string fileNamePar) {

	ifstream inputFile;

	int fileSize = 0;

	inputFile.open(fileNamePar);

	if (!inputFile.is_open()) {

		cout << "File cannot be opened.";

		exit(0);
	}

	inputFile >> fileSize;

	inputFile.close();

	return fileSize;
}

vector<float> getFunction(int vectorSizePar, string fileNamePar) {

	ifstream inputFile;

	vector<float> returnVector;

	double dump;

	returnVector.resize(vectorSizePar);

	inputFile.open(fileNamePar);

	inputFile >> dump;

	for (int i = 0; i < vectorSizePar; i++) {

		inputFile >> returnVector[i];

	}

	inputFile.close();

	return returnVector;
}

vector<float> getDerivative(vector<float> inputFunctionPar) {

	vector<float> returnVector;

	returnVector.resize(inputFunctionPar.size() - 1);

	for (int i = 0; i < returnVector.size(); i++) {

		returnVector[i] = (inputFunctionPar[i + 1] * (i + 1));
	}

	return returnVector;
}

float functionSecant(float a, float b, long long maxIterPar, vector<float> functionPar, string fileTitle) {

	ofstream outputFile;

	float fa = 0;
	float fb = 0;
	float d = 0;

	fa = applyFunction(a, functionPar);
	fb = applyFunction(b, functionPar);


	for (int i = 1; i <= maxIterPar; i++) {

		if (abs(fa) > abs(fb)) {

			swap(a, b);
			swap(fa, fb);

		}

		//checks if d calculation will be undefined
		if ((fb - fa) == 0) {

			cout << "Algorithm has converged after " << i << " iterations!" << endl;

			outputFile.open(fileTitle + "sol");

			outputFile << a << " " << i << " success";

			outputFile.close();

			return a;

		}

		d = (b - a) / (fb - fa);
		b = a;
		fb = fa;
		d *= fa;

		if (d == 0 || d == -0) {

			cout << "Algorithm has converged after " << i << " iterations!" << endl;

			outputFile.open(fileTitle + "sol");

			outputFile << a << " " << i << " success";

			outputFile.close();

			return a;

		}

		a -= d;
		fa = applyFunction(a, functionPar);

	}

	cout << "Max iterations reached without convergence..." << endl;

	outputFile.open(fileTitle + "sol");

	outputFile << a << " " << maxIterPar << " fail";

	outputFile.close();

	return a;

}

float functionNewton(float x, long long maxIterPar, vector<float> functionPar, string fileTitle) {

	ofstream outputFile;

	float delta = .00001;
	float fx = 0;
	float fd = 0;
	float d = 0;

	vector<float> derivativePar;
	derivativePar.resize(functionPar.size() - 1);

	derivativePar = getDerivative(functionPar);

	fx = applyFunction(x, functionPar);

	for (int i = 1; i <= maxIterPar; i++) {

		fd = applyFunction(x, derivativePar);

		if (abs(fd) < delta) {

			cout << "Small slope!";

			outputFile.open(fileTitle + "sol");

			outputFile << x << " " << i << " fail";

			outputFile.close();

			return x;

		}

		d = fx / fd;
		x -= d;
		fx = applyFunction(x, functionPar);

		if (d == 0 || d == -0) {

			cout << "Algorithm has converged after " << i << " iterations!" << endl;

			outputFile.open(fileTitle + "sol");

			outputFile << x << " " << i << " success";

			outputFile.close();

			return x;

		}

	}

	cout << "Max iterations reached by newton without convergence..." << endl;

	outputFile.open(fileTitle + "sol");

	outputFile << x << " " << maxIterPar << " fail";

	outputFile.close();

	return x;

}

float functionBisection(float a, float b, long long maxIterPar, vector<float> functionPar, string fileTitle) {

	ofstream outputFile;

	float c = 0;
	float fa = 0;
	float fb = 0;
	float fc = 0;
	float error;

	fa = applyFunction(a, functionPar);
	fb = applyFunction(b, functionPar);

	if ((fa * fb) >= 0) {

		cout << "Inadequate values for a and b." << endl;

		exit(0);

	}

	error = b - a;

	for (int i = 1; i <= maxIterPar; i++) {

		error = error / 2;
		c = a + error;
		fc = applyFunction(c, functionPar);

		if (error == 0 || error == -0) {

			cout << "Algorithm has converged after " << i << " iterations!" << endl;

			outputFile.open(fileTitle + "sol");

			outputFile << c << " " << i << " success";

			outputFile.close();

			return c;

		}

		if ((fa * fc) < 0) {

			b = c;
			fb = fc;

		}
		else {

			a = c;
			fa = fc;
		}

	}

	cout << "Max iterations reached for bisection without convergence..." << endl;

	//creates a file and store output info in it
	outputFile.open(fileTitle + "sol");

	outputFile << c << " " << maxIterPar << " fail";

	outputFile.close();


	return c;

}

float functionHybrid(float a, float b, long long maxIterPar, vector<float> functionPar, string fileTitle) {

	return (functionNewton(functionBisection(a, b, 5, functionPar, fileTitle), (maxIterPar - 5), functionPar, fileTitle));

}

int main(int argc, char* argv[]) {

	long long maxIt = 10000;

	int polySize;

	float initialPoint1 = 0;
	float initialPoint2 = 0;

	bool secTag = false;
	bool newtTag = false;
	bool hybridTag = false;
	bool hasDot = false;

	vector<float> userFunction;

	string fileName = "";
	string fileTitle = "";
	string fileType = "";
	string userInput = "";

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

		if (string(argv[1]) == "-newt") {

			newtTag = true;

			if (!strtof(argv[2], NULL)) {

				if (string(argv[2]) != "0") {

					cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
					return 0;

				}

			}

			initialPoint1 = stof(argv[2]);
			fileName = argv[3];

			break;
		}

		if (strtof(argv[1], NULL)) {

			Bypass0:

			initialPoint1 = stof(argv[1]);

			if (!strtof(argv[2], NULL)) {

				if (string(argv[2]) != "0") {

					cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
					return 0;

				}

			}

			initialPoint2 = stof(argv[2]);
			fileName = argv[3];

			break;
		}

		if (string(argv[1]) == "0") {

			goto Bypass0;

		}

		

		cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
		return 0;

	case 5:

		if (string(argv[1]) == "-sec") {

			secTag = true;

			if (!strtof(argv[2], NULL)) {

				if (string(argv[2]) != "0") {

					cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
					return 0;

				}

			}

			initialPoint1 = stof(argv[2]);

			if (!strtof(argv[3], NULL)) {

				if (string(argv[3]) != "0") {

					cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
					return 0;

				}

			}

			initialPoint2 = stof(argv[3]);
			fileName = argv[4];

			break;
		}

		if (string(argv[1]) == "-hybrid") {

			hybridTag = true;

			if (!strtof(argv[2], NULL)) {

				if (string(argv[2]) != "0") {

					cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
					return 0;

				}

			}

			initialPoint1 = stof(argv[2]);

			if (!strtof(argv[3], NULL)) {

				if (string(argv[3]) != "0") {

					cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
					return 0;

				}

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

				if (string(argv[3]) != "0") {

					cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
					return 0;

				}

			}

			initialPoint1 = stof(argv[3]);

			if (!strtof(argv[4], NULL)) {

				if (string(argv[4]) != "0") {

					cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
					return 0;

				}

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

				if (string(argv[4]) != "0") {

					cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
					return 0;

				}

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

				if (string(argv[4]) != "0") {

					cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
					return 0;

				}

			}

			initialPoint1 = stof(argv[4]);

			if (!strtof(argv[5], NULL)) {

				if (string(argv[5]) != "0") {

					cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
					return 0;

				}

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

				if (string(argv[4]) != "0") {

					cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
					return 0;

				}

			}

			initialPoint1 = stof(argv[4]);

			if (!strtof(argv[5], NULL)) {

				if (string(argv[5]) != "0") {

					cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
					return 0;

				}

			}

			initialPoint2 = stof(argv[5]);
			fileName = argv[6];

			break;
		}

		cout << "Invalid input. Must use this format: polRoot [-newt, -sec, -hybrid] [-maxIt n] initP [initP2] polyFileName." << endl;
		return 0;
	}

	for (int i = 0; i < fileName.length(); i++) {

		if (hasDot == false) {

			fileTitle += fileName[i];
		}

		if (hasDot == true) {

			fileType += fileName[i];

		}

		if (fileName[i] == '.') {

			hasDot = true;

		}

	}

	if (fileType != "pol") {

		cout << "Invalid file type. Must be of type pol." << endl;

		return 0;

	}

	polySize = (getSize(fileName) + 1);

	userFunction.resize(polySize);

	userFunction = getFunction(polySize, fileName);

	reverse(userFunction.begin(), userFunction.end());

	if (newtTag == true) {

		cout << functionNewton(initialPoint1, maxIt, userFunction, fileTitle);

	}
	else {

		if (secTag == true) {

			cout << functionSecant(initialPoint1, initialPoint2, maxIt, userFunction, fileTitle);

		}
		else {

			if (hybridTag == true) {

				cout << functionHybrid(initialPoint1, initialPoint2, maxIt, userFunction, fileTitle);

			}
			else {

				cout << functionBisection(initialPoint1, initialPoint2, maxIt, userFunction, fileTitle);

			}
		}

	}

	return 0;
}
