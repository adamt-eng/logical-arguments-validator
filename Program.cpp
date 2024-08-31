#include <iostream>
#include <iomanip>
#include <array>

using namespace std;

struct statement
{
    string variables;
    string implication_hypothesis;
    string implication_conclusion;

    char implication_hypothesis_operator = 0;
    char op = 0;

    bool implication_negate_conclusion = false;
    bool negate_first = false;
    bool negate_second = false;
    bool implication_negate_hypothesis_one = false;
};

namespace
{
    bool translate_variable(char variable, const array<int, 3>& values)
    {
        switch (variable)
        {
        case 'A': return values[0];
        case 'B': return values[1];
        case 'C': return values[2];
        default: return false;
        }
    }

    bool translate_operator(char Operator, bool variable_1, bool variable_2)
    {
        switch (Operator)
        {
	        case '|': return variable_1 || variable_2;
	        case '&': return variable_1 && variable_2;
	        case '>': return !variable_1 || variable_2;
	        default: return false;
        }
    }

    bool evaluate_statement(const statement& stmt, const array<int, 3>& values)
    {
        if (stmt.op == '|' || stmt.op == '&')
        {
            bool first = translate_variable(stmt.variables[0], values);
            bool second = translate_variable(stmt.variables[1], values);

            first = stmt.negate_first ? !first : first;
            second = stmt.negate_second ? !second : second;

            return translate_operator(stmt.op, first, second);
        }

        if (stmt.op == '>')
        {
            bool conclusion = translate_variable(stmt.implication_conclusion[0], values);
            conclusion = stmt.implication_negate_conclusion ? !conclusion : conclusion;

            if (stmt.implication_hypothesis.length() == 2)
            {
                bool hypothesis = translate_operator(stmt.implication_hypothesis_operator,
                    translate_variable(stmt.implication_hypothesis[0], values),
                    translate_variable(stmt.implication_hypothesis[1], values));
                return translate_operator(stmt.op, hypothesis, conclusion);
            }

            if (stmt.implication_hypothesis.length() == 1)
            {
	            bool hypothesis = translate_variable(stmt.implication_hypothesis[0], values);
	            hypothesis = stmt.implication_negate_hypothesis_one ? !hypothesis : hypothesis;

	            return translate_operator(stmt.op, hypothesis, conclusion);
            }
        }

        return translate_variable(stmt.variables[0], values);
    }

    void get_input(const string& label, statement& stmt)
    {
        cout << "\nType the variables you want to use in " << label << " (A/B/C) (Maximum 3 if it contains an implication, 2 if not): ";
        cin >> stmt.variables;

        if (stmt.variables.length() > 1)
        {
            char implication = 0;
            cout << "Is there an implication in the statement? (Y/N): ";
            cin >> implication;

            if (implication == 'Y')
            {
                stmt.op = '>';

                cout << "Type the variables you want to use in the hypothesis (Maximum 2) (A/B/C): ";
                cin >> stmt.implication_hypothesis;

                if (stmt.implication_hypothesis.length() == 1)
                {
                    char prompt = 0;
                    cout << "Do you want to negate that variable? (Y/N): ";
                    cin >> prompt;
                    stmt.implication_negate_hypothesis_one = (prompt == 'Y');
                }
                else if (stmt.implication_hypothesis.length() == 2)
                {
                    cout << "What's the operator between the two variables in the hypothesis (OR/AND): ";

                    string op;
                    cin >> op;

                    stmt.implication_hypothesis_operator = (op == "OR") ? '|' : '&';
                }

                cout << "Which variable do you want to use for the conclusion (Maximum 1) (A/B/C): ";
                cin >> stmt.implication_conclusion;

                char prompt = 0;
                cout << "Do you want to negate that variable? (Y/N): ";
                cin >> prompt;
                stmt.implication_negate_conclusion = (prompt == 'Y');
            }
            else if (implication == 'N')
            {
                cout << "What's the operator between your variables (OR/AND): ";

                string op;
                cin >> op;

                stmt.op = op == "OR" ? '|' : '&';

                char prompt = 0;
                cout << "Do you want to negate the first variable? (Y/N): ";
                cin >> prompt;
                stmt.negate_first = (prompt == 'Y');

                cout << "Do you want to negate the second variable? (Y/N): ";
                cin >> prompt;
                stmt.negate_second = (prompt == 'Y');
            }
        }
    }
}

class logical_evaluator
{
	array<int, 3> values_ = { 1, 1, 1 }; // Replaces global variables a, b, c

public:
    void set_values(int a, int b, int c)
    {
        values_ = { a, b, c };
    }

    bool evaluate_statement(const statement& stmt) const
    {
        return ::evaluate_statement(stmt, values_);
    }
};

int main()
{
    cout << "Give each of your variables a name for clarity in the truth table (A/B/C):\n";
    array<string, 3> variable_names = { "A", "B", "C" };

    for (auto& variable_name : variable_names)
    {
        cout << variable_name << ": ";
        cin >> variable_name;
    }

    // Gets input from the user for variables to use in each statement and its operators
    statement p1, p2, conc;
    get_input("Premise 1", p1);
    get_input("Premise 2", p2);
    get_input("Conclusion", conc);

    // Displays the truth table's header.
    cout << "\n" << setw(variable_names[0].size()) << variable_names[0] << "\t"
	<< setw(variable_names[1].size()) << variable_names[1] << "\t"
	<< setw(variable_names[2].size()) << variable_names[2] << "\tPremise 1\tPremise 2\tConclusion\n\n";

    logical_evaluator evaluator;
    constexpr int num_rows = 8;
    array<bool, num_rows> valid = {};
    int count = 0;

    // Display truth table values.
    for (int a = 1; a >= 0; a--)
    {
        for (int b = 1; b >= 0; b--)
        {
            for (int c = 1; c >= 0; c--)
            {
                evaluator.set_values(a, b, c);

                // Gets the logical representation of each statement.
                bool premise_1 = evaluator.evaluate_statement(p1);
                bool premise_2 = evaluator.evaluate_statement(p2);
                bool conclusion = evaluator.evaluate_statement(conc);

                // Set the current index to true regardless of whether it's a critical row or not.
                valid[count] = true;

                // If it's a critical row, check validity.
                if (premise_1 && premise_2 && !conclusion)
                {
                    valid[count] = false;
                }

                // Increment to save the next value in the following index.
                count++;

                cout << setw(variable_names[0].size()) << a << "\t"
                    << setw(variable_names[1].size()) << b << "\t"
                    << setw(variable_names[2].size()) << c << "\t"
                    << setw(9) << premise_1 << "\t"
                    << setw(9) << premise_2 << "\t"
                    << setw(10) << conclusion << "\n";
            }
        }
    }

    for (bool is_valid : valid)
    {
        if (!is_valid)
        {
            cout << "\nThe argument is invalid because the conclusion is false at a critical row at least once.";
            while (true) {}
        }
    }

    cout << "\nThe argument is valid.";
    while (true) {}
}
