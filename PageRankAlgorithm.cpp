#include <iostream>
#include <limits>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

//declarations
class myGraph {
private:
	double** matrix;
	int numV;
public:
	myGraph(int numV);

	void addEdge(int a, int b);
	void print();

	void changeVals(int j);
	double findM(int i);

	double ** getMatrix();

};

//definitions
myGraph::myGraph(int numV) {
	this->numV = numV;
	matrix = new double*[numV];
	for (int i = 0; i < numV; i++) {
		matrix[i] = new double[numV];
		for (int j = 0; j < numV; j++)
			matrix[i][j] = 0.0;
	}
}

void myGraph::addEdge(int a, int b) {
	matrix[b][a] = 1.0;
}

void myGraph::print() {
	for (int i = 0; i < numV; i++) {
		cout << i << " : ";
		for (int j = 0; j < numV; j++)
			cout << matrix[i][j] << "  ";
		cout << "\n";
	}

}

void myGraph::changeVals(int j) {
	//go down column j and count the amount of times a value is 1 and divide 1 by amtValues and change all 1.0s to
	// this new value
	double amtValues = 0.0;

	for (int i = 0; i < numV; i++) {
		if (matrix[i][j] == 1.0) {
			amtValues += 1.0;
		}
	}

	double changedValue = 1.0 / amtValues;

	for (int i = 0; i < numV; i++) {
		if (matrix[i][j] == 1.0) {
			matrix[i][j] = changedValue;
		}
	}

}

double myGraph::findM(int i) {
	//add up each number in row i and return the total
	double total = 0.0;
	for (int j = 0; j < numV; j++) {
		total = total + matrix[i][j];
	}

	return total;
}

double ** myGraph::getMatrix() {
	this->matrix = matrix;
	return matrix;
}


// main code
int main()
{
	// Step 1: Map URLs to a unique ID using: VECTOR

	string line;
	string from_URL;
	string to_URL;
	int numLines = 0;
	int numPI = 0;
	vector<string> uniqueURLs;
	vector<string> fVector;
	vector<string> tVector;

	getline(cin, line);
	numLines = stoi(line.substr(0, line.find(" ")));
	numPI = stoi(line.substr(2, 3));


	//get the from_URL values and put them into a vector

	for (int i = 0; i < numLines; i++) {
		cin >> from_URL;
		cin >> to_URL;

		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		//update from and to Vectors
		fVector.push_back(from_URL);
		tVector.push_back(to_URL);

		//if from_URL is not in the vector, add it
		if (find(uniqueURLs.begin(), uniqueURLs.end(), from_URL) == uniqueURLs.end()) {
			uniqueURLs.push_back(from_URL);
		}

		if (find(uniqueURLs.begin(), uniqueURLs.end(), to_URL) == uniqueURLs.end()) {
			uniqueURLs.push_back(to_URL);
		}
	}

	//sort the unique vector alphabetically
	sort(uniqueURLs.begin(), uniqueURLs.end());


	int V = uniqueURLs.size();


	// Step 2: Graph Representation using: ADJACENCY MATRIX

	// create a graph with an adjacency matrix of size V x V
	myGraph myGraph(V);

	// Then we need to populate the matrix with where the directed edges are. that means we need to know
	// where each from_URL points. i have two vectors where the index of vector F is the from_URL and the same
	// index of vector T is the corresponding to_URL

	// check each row in the matrix (i)
	for (int i = 0; i < V; i++) {
		string curFromStringVal = uniqueURLs[i];

		//check to see where this website is in FVector and then check the corresponding index of tVector to get
		// which indexes should be updated in the matrix to true (representing that they have an edge between them)
		for (int m = 0; m < fVector.size(); m++) {

			//if the current index is equal to the uniqueURL
			if (fVector[m] == curFromStringVal) {
				string ToVal = tVector[m];

				//find ToVal in uniqueURLs
				int c = 0;
				bool found = false;
				while (!found) {
					if (c >= uniqueURLs.size()) {
						found = true;
					}
					else if (uniqueURLs[c] == ToVal) {
						found = true;
					}
					else {
						c++;
					}
				}

				//now update the adj matrix element at [i][c] to be true
				myGraph.addEdge(i, c);
			}
		}
	}

	//change the values from 1.0 to their values based on how many elements are in the column
	for (int i = 0; i < V; i++) {
		myGraph.changeVals(i);
	}

	//print the matrix
	// myGraph.print();




	// Step 3: Power Iteration r(t+1) = M*r(t)

	//create initial values for r(t)
	vector<double> r;
	for (int i = 0; i < V; i++) {
		r.push_back(1.0 / V);
	}

	// Okay so now we need to calculate values for the M vector, so add all the values in each row
	vector<double> M;
	for (int i = 0; i < V; i++) {

		double amtValues = myGraph.findM(i);
		M.push_back(amtValues);

	}



	vector<double> finalVals;
	//do no multiplications
	if (numPI == 1) {
		for (int i = 0; i < uniqueURLs.size(); i++) {
			cout << uniqueURLs[i];
			cout << " " << setprecision(2) << fixed << r[i] << endl;
		}
	}
	//only do one multiplication, so multiply the M vector values by the r(t) vector values and store it in
	// a final values vector
	else if (numPI == 2) {
		//multiply and fill the finalVals vector
		for (int i = 0; i < V; i++) {
			double num = r[i] * M[i];
			finalVals.push_back(num);
		}

		//print it out
		for (int i = 0; i < uniqueURLs.size(); i++) {
			cout << uniqueURLs[i];

			cout << " " << setprecision(2) << fixed << finalVals[i] << endl;

		}
	}

	// do numPI-1 multiplications
	else if (numPI > 2) {

		// do the first power iteration (multiply and fill the finalVals vector)
		for (int i = 0; i < V; i++) {
			finalVals.push_back(r[i] * M[i]);
		}



		double ** myMatrix = myGraph.getMatrix();



		// do the rest of the power iterations with the modified r(t) values
		for (int m = 1; m < numPI - 1; m++) {

			//set r(t) to be the finalVals vector
			r = finalVals;

			//empty the finalVals vector
			finalVals.clear();

			// access the matrix and check which index is not 0 in row i
			// then to go that index in r and multiply 
			double tmpVal = 0.0;
			for (int i = 0; i < V; i++) {
				for (int j = 0; j < V; j++) {
					if (myMatrix[i][j] != 0.0) {
						tmpVal += r[j] * myMatrix[i][j];
					}
				}
				finalVals.push_back(tmpVal);
				tmpVal = 0.0;
			}


		}

		//print results
		for (int i = 0; i < uniqueURLs.size(); i++) {
			cout << uniqueURLs[i];

			cout << " " << setprecision(2) << fixed << finalVals[i] << endl;

		}
	}


	return 0;
}