#include <iostream>
#include <vector>
#include <string>

std::vector<std::vector<float>> table;


// Function to output table
void output_table() {
    std::cout << "Table status:\n";

    std::cout << "     \t";
    for (int i = 0; i < table[i].size(); i++) {
        std::cout << i+1 << " col\t";
    }
    std::cout << "\n";

    for (int i = 0; i < table.size(); i++) {
        if (i != table.size() - 1) {
            std::cout << " " << i+1 << " row\t";
        } else {
            std::cout << "      \t";
        }
        for (int j = 0; j < table[i].size(); j++) {
            std::cout << table[i][j] << "\t";
        }
        if (i == table.size() - 1) {
            std::cout << "f\t";
        }
        std::cout << "\n";
    }
}


// Function to create empty template for table
void creating_table(int &amountOfEquations, int &numberOfVariables) {
    std::vector<float> temp;

    for (int i = 0; i < numberOfVariables; i++) {
        temp.push_back(0);
    }

    for (int i = 0; i < amountOfEquations; i++) {
        table.push_back(temp);
    }
}


// Function to sort odds in the line
void sortOdds(std::string &equation, std::vector<float> &vec, int &numberOfVariables) {
    for (int j = 0; j < numberOfVariables; j++) {
        std::string x = "x";
        x.append(std::to_string(j+1));

        if (equation.find(x) == -1) {
            vec[j] = 0;
        } else {
            if (equation.substr(0, equation.find(x)) == "-") {
                vec[j] = -1;
            } else if ((equation.substr(0, equation.find(x)) == "+") || (equation.find(x) == 0)) {
                vec[j] = 1;
            } else {
                vec[j] = atof(equation.substr(0, equation.find(x)).c_str());
            }
            equation.erase(0, equation.find(x)+2);
        }
    }
}



// Function create new x
void createX(std::string &equation, int &i) {
    if (equation[0] != '=') {
        float addingValue = 0;
        if (equation[0] == '<') {
            addingValue = 1;
        } else {
            addingValue = -1;
        }

        for (int k = 0; k < table.size(); k++) {
            if (i == k) {
                table[k].push_back(addingValue);
            } else {
                table[k].push_back(0);
            }
        }
    }

    equation.erase(0, equation.find('=')+1);
}


// Function to fill line of odds of equation we must max
void oddsOfEquation(std::string &maxEquation, int &numberOfVariables) {
    std::vector<float> oddsOfMaxEquation(numberOfVariables);

    maxEquation.erase(0, 2);

    sortOdds(maxEquation, oddsOfMaxEquation, numberOfVariables);

    for (int i = 0; i < table[0].size() - numberOfVariables; i++) {
        oddsOfMaxEquation.push_back(0);
    }

    table.push_back(oddsOfMaxEquation);
}


// Function to input equations
void input_equations(std::string &maxEquation, int &numberOfVariables) {
    std::cout << "Input equations without spaces (!)\n";
    std::cout << "Example:\n";
    std::cout << "-x1+2x2-3x3<=2\n\n";

    std::string equation;
    std::vector<float> finalValues;

    for (int i = 0; i < table.size(); i++) {
        std::cout << "Input " << i + 1 << " equation:\n";
        std::cin >> equation;

        // Sort odds in the line, that are in equation
        sortOdds(equation, table[i], numberOfVariables);

        // Create new column with xs
        createX(equation, i);

        finalValues.push_back(atof(equation.c_str()));
        std::cout << "\n";
    }

    // Fill line of odds of equation we must max
    oddsOfEquation(maxEquation, numberOfVariables);

    for (int i = 0; i < finalValues.size(); i++) {
        table[i].push_back(finalValues[i]);
    }

    std::cout << "\n\n";
    output_table();
}


int main() {
    // Greetings
    std::cout << "\nSimplex method\n\n\n";


    {
        // Input max equation
        std::string maxEquation;

        std::cout << "Input equation that we need to max:\n";
        std::cout << "Example: 'f=2x1-3x2'\n";
        std::cin >> maxEquation;


        // Creating vector for table
        int amountOfEquations, numberOfVariables;

        std::cout << "\nInput quantity of equations you have in system of equations\n";
        std::cout << "(except equations like 'x1 >= 0', 'x2>= 0' and etc.):\n";
        std::cin >> amountOfEquations;

        std::cout << "\nInput quantity of variables:\n";
        std::cin >> numberOfVariables;
        std::cout << "\n\n";
        creating_table(amountOfEquations, numberOfVariables);

        // Input equations
        input_equations(maxEquation, numberOfVariables);
    }



    return 0;
}
