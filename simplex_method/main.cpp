#include <iostream>
#include <vector>
#include <string>
#include <cmath>


std::vector<std::vector<float>> table;
std::vector<float> begginingF;


// Function to check if number is endless
bool is_number_endless(float number) {
    if (number == 0) {
        return false;
    }

    number *= 1000;

    int intnum = (int)abs(number);
    std::string temp = std::to_string(intnum);

    if (temp[1] == '0') {
        return false;
    }

    return (temp[1] == temp[2]) && (temp[1] == temp[2]);
}


// Function to turn endless number into string
std::string turn_endless_number_into_str(float number) {
    number *= 100;

    int intnum = (int)(number);
    std::string temp = std::to_string(intnum);
    bool is_positive = intnum >= 0;

    int index;

    if (is_positive) {
        index = 1;
    } else {
        index = 2;
    }

    char endlessNumber = temp[index];

    int tempNumber = intnum / 100;

    if (is_positive) {
        return std::to_string(tempNumber) + ".(" + endlessNumber + ')';
    } else {
        tempNumber = abs(tempNumber);
        return '-' + std::to_string(tempNumber) + ".(" + endlessNumber + ')';
    }
}


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
            if (is_number_endless(table[i][j])) {
                std::cout << turn_endless_number_into_str(table[i][j]) << "\t";
            } else {
                std::cout << table[i][j] << "\t";
            }
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

    begginingF = oddsOfMaxEquation;

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
}


// Function to check if there is at least one number larger than 0
bool are_answers_positive() {
    for (int i = 0; i < table[table.size()-1].size(); i++) {
        if (table[table.size()-1][i] > 0)
            return true;
    }

    return false;
}


// Function to output columns odds
void output_column_odds(std::vector<std::vector<float>> &columnOdds, std::vector<int> &columnsOfPositiveAnswers, float &maxOfMaxs) {
    std::cout << "\n\nColumn odds:\n";

    for (int i = 0; i < columnOdds.size(); i++) {
        std::cout << " " << columnsOfPositiveAnswers[i]+1 << " col\t";

        for (int j = 0; j < columnOdds[i].size()-1; j++) {
            if (columnOdds[i][j] != -1) {
                std::cout << columnOdds[i][j] << "\t";
            } else {
                std::cout << "-\t";
            }
        }
        std::cout << "=> " << columnOdds[i][columnOdds[i].size() - 1];
        if (columnOdds[i][columnOdds[i].size() - 1] == maxOfMaxs) {
            std::cout << " (max)";
        }
        std::cout << "\n";
    }
}


// Function to fill column odds of positive answers
bool fill_column_of_odds(std::vector<std::vector<float>> &columnsOdds, std::vector<int> &columnsOfPositiveAnswers) {
    bool are_answers_endless = true;
    std::vector<float> currentColumn;

    for (int i = 0; i < columnsOfPositiveAnswers.size(); i++) {
        currentColumn.resize(0);

        for (int j = 0; j < table.size()-1; j++) {
            if (table[j][columnsOfPositiveAnswers[i]] < 0) {
                currentColumn.push_back(-1);
            } else {
                currentColumn.push_back(table[j][table[j].size()-1] / table[j][columnsOfPositiveAnswers[i]]);
            }
        }

        columnsOdds.push_back(currentColumn);
    }

    for (int i = 0; i < currentColumn.size(); i++) {
        if (currentColumn[i] != -1)
            are_answers_endless = false;
    }

    if ((columnsOdds.size() == 1) &&
            (are_answers_endless)) {
        return true;
    } else {
        return false;
    }
}

// Function to add to column of adds maximums
std::vector<int> add_to_column_of_odds_maximums(std::vector<std::vector<float>> &columnsOdds, std::vector<int>  &columnsOfPositiveAnswers) {
    std::vector<int> indexesOfMinInColumns;

    for (int i = 0; i < columnsOdds.size(); i++) {
        float minOfColumn = 1000;
        int indexOfMin = -1;

        for (int j = 0; j < columnsOdds[i].size(); j++) {
            if ((columnsOdds[i][j] != -1) && (columnsOdds[i][j] < minOfColumn)) {
                minOfColumn = columnsOdds[i][j];
                indexOfMin = j;
            }
        }

        if (minOfColumn != -2) {
            columnsOdds[i].push_back(minOfColumn * table[table.size()-1][columnsOfPositiveAnswers[i]]);
        } else {
            columnsOdds[i].push_back(-1);
        }

        indexesOfMinInColumns.push_back(indexOfMin);
    }

    return indexesOfMinInColumns;
}


// Function max between max in columns of odds
float search_max_of_maxs_in_columns_of_odds(std::vector<std::vector<float>> &columnsOdds) {
    float max = -2;

    for (int i = 0; i < columnsOdds.size(); i++) {
        if (max < columnsOdds[i][columnsOdds[i].size() - 1]) {
            max = columnsOdds[i][columnsOdds[i].size() - 1];
        }
    }

    return max;
}


// Function
std::vector<int> search_index_of_needed_number_in_table(std::vector<std::vector<float>> &columnsOdds, std::vector<int> &columnsOfPositiveAnswers, float &maxOfMaxs, std::vector<int> &indexesOfMinInColumns) {
    std::vector<int> indexOfNeededNumber;

    int indexOfColumnThereIsMax = -1;
    for (int i = 0; i < columnsOdds.size(); i++) {
        if (columnsOdds[i][columnsOdds[i].size()-1] == maxOfMaxs) {
            indexOfColumnThereIsMax = i;
            break;
        }
    }

    indexOfNeededNumber.push_back(indexesOfMinInColumns[indexOfColumnThereIsMax]);
    indexOfNeededNumber.push_back(columnsOfPositiveAnswers[indexOfColumnThereIsMax]);

    return indexOfNeededNumber;
}


// Function
void dividving_table_on_row(std::vector<int> &indexOfNeededNumberInTable) {
    float multiplier;

    for (int i = 0; i < table.size(); i++) {
        if (i != indexOfNeededNumberInTable[0]) {
            multiplier = table[i][indexOfNeededNumberInTable[1]];
            for (int j = 0; j < table[i].size(); j++) {
                table[i][j] = table[i][j] - table[indexOfNeededNumberInTable[0]][j] * multiplier;
            }
        }
    }
}


// Function
std::vector<float> search_numbers_of_x(int &numberOfVariables) {
    std::vector<float> numbersOfX;

    for (int i = 0; i < numberOfVariables; i++) {
        if (table[table.size()-1][i] == 0) {
            int indexOf1;

            for (int j = 0; j < table.size()-1; j++) {
                if (table[j][i] == 1) {
                    indexOf1 = j;
                    break;
                }
            }

            numbersOfX.push_back(table[indexOf1][table[indexOf1].size()-1]);
        } else {
            numbersOfX.push_back(0);
        }
    }

    return numbersOfX;
}


// Function to find result
std::string find_result(int &numberOfVariables) {
    bool areAnswersEndless = false;
    while ((are_answers_positive()) && (!areAnswersEndless)) {
        std::cout << "\n\n";
        output_table();

        std::vector<int> columnsOfPositiveAnswers;

        for (int i = 0; i < table[table.size()-1].size(); i++) {
            if (table[table.size()-1][i] > 0)
                columnsOfPositiveAnswers.push_back(i);
        }


        std::vector<std::vector<float>> columnsOdds;

        areAnswersEndless = fill_column_of_odds(columnsOdds, columnsOfPositiveAnswers);

        if (areAnswersEndless) {
            break;
        }
        std::vector<int> indexesOfMinInColumns =  add_to_column_of_odds_maximums(columnsOdds, columnsOfPositiveAnswers);

        float maxOfMaxs = search_max_of_maxs_in_columns_of_odds(columnsOdds);

        output_column_odds(columnsOdds, columnsOfPositiveAnswers, maxOfMaxs);

        std::vector<int> indexOfNeededNumberInTable = search_index_of_needed_number_in_table(columnsOdds, columnsOfPositiveAnswers, maxOfMaxs, indexesOfMinInColumns);

        // Outputting info about needed number
        std::cout << "\nNeeded number is " << table[indexOfNeededNumberInTable[0]][indexOfNeededNumberInTable[1]]
                << "\n";
        std::cout << "Indexes of needed number: " << indexOfNeededNumberInTable[0]
                << " " << indexOfNeededNumberInTable[0] << "\n\n";

        if (table[indexOfNeededNumberInTable[0]][indexOfNeededNumberInTable[1]] != 1) {
            std::cout << "In case needed number is not equal 1, we do dividing of string on number: "
                    << table[indexOfNeededNumberInTable[0]][indexOfNeededNumberInTable[1]] << "\n\n";
            float divider = table[indexOfNeededNumberInTable[0]][indexOfNeededNumberInTable[1]];
            for (int i = 0; i < table[indexOfNeededNumberInTable[0]].size(); i++) {
                table[indexOfNeededNumberInTable[0]][i] /= divider;
            }

            output_table();
        }

        std::cout << "\nNow we need to make column all zeros, except needed row\n\n";

        dividving_table_on_row(indexOfNeededNumberInTable);

        output_table();
    }

    if (!areAnswersEndless) {
        std::vector<float> numbersOfX = search_numbers_of_x(numberOfVariables);

        float result = 0;

        std::string strResult = "X: ";

        for (int i = 0; i < numbersOfX.size(); i++) {
            result += numbersOfX[i]  * begginingF[i];
            strResult += std::to_string(numbersOfX[i]) + " ";
        }

        strResult += "\n Fmax = ";
        strResult += std::to_string(result);

        return strResult;
    }
    return " Answer are endless!\n";
}


int main() {
    // Greetings
    std::cout << "\nSimplex method\n\n\n";


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


    // Find result
    std::string result = find_result(numberOfVariables);

    std::cout << "\n\n\n      Result!    \n" << result << "\n";

    return 0;
}
