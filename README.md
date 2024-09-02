# Logical Arguments Validator

## Overview

The **Logical Arguments Validator** is a C++ program designed to evaluate the validity of logical arguments. Given premises and a conclusion, the program generates a truth table and checks if the argument is logically valid. An argument is considered valid if, in all cases where the premises are true, the conclusion is also true.

## Features

- **Customizable Input**: Users can define up to three variables and specify logical operations (AND, OR, implication) for premises and conclusions.
- **Truth Table Generation**: The program automatically generates a truth table for all possible truth values of the variables.
- **Argument Validity Check**: The program checks the validity of the argument by ensuring that the conclusion is true whenever the premises are true.

## Usage

1. **Enter Variable Names**: Upon running the program, you'll be prompted to assign names to your variables (e.g., A, B, C).
2. **Define Premises and Conclusion**:
   - For each premise and the conclusion, you'll specify the variables and the logical operators (AND, OR, implication).
   - You can also choose to negate variables if needed.
3. **View the Truth Table**: The program will display a truth table showing the truth values of the premises and conclusion for all possible combinations of the variables.
4. **Check Argument Validity**: The program will evaluate the truth table and indicate whether the argument is valid or not.

## Examples

### Example 1

Ahmed or Mona ate the chocolate. If Karim or Mona ate the chocolate then, Ahmed did not eat the chocolate. Thus, Ahmed or Karim ate the chocolate.

```
Give each of your variables a name for clarity in the truth table (A/B/C):
A: Ahmed
B: Karim
C: Mona

Type the variables you want to use in Premise 1 (A/B/C) (Maximum 3 if it contains an implication, 2 if not): AC
Is there an implication in the statement? (Y/N): N
What's the operator between your variables (OR/AND): OR
Do you want to negate the first variable? (Y/N): N
Do you want to negate the second variable? (Y/N): N

Type the variables you want to use in Premise 2 (A/B/C) (Maximum 3 if it contains an implication, 2 if not): ABC
Is there an implication in the statement? (Y/N): Y
Type the variables you want to use in the hypothesis (Maximum 2) (A/B/C): BC
What's the operator between the two variables in the hypothesis (OR/AND): OR
Which variable do you want to use for the conclusion (Maximum 1) (A/B/C): A
Do you want to negate that variable? (Y/N): Y

Type the variables you want to use in Conclusion (A/B/C) (Maximum 3 if it contains an implication, 2 if not): AB
Is there an implication in the statement? (Y/N): N
What's the operator between your variables (OR/AND): OR
Do you want to negate the first variable? (Y/N): N
Do you want to negate the second variable? (Y/N): N
```

#### Output

```
Ahmed   Karim   Mona    Premise 1       Premise 2       Conclusion

    1       1      1            1               0                1
    1       1      0            1               0                1
    1       0      1            1               0                1
    1       0      0            1               1                1
    0       1      1            1               1                1
    0       1      0            0               1                1
    0       0      1            1               1                0
    0       0      0            0               1                0

The argument is invalid because the conclusion is false at a critical row at least once.
```

### Example 2

The children are playing Football or Tennis. If they are watching TV or playing Tennis, then they are not playing Football. Therefore, they are not playing Football or they are not watching TV.

```
Give each of your variables a name for clarity in the truth table (A/B/C):
A: Football
B: Tennis
C: TV

Type the variables you want to use in Premise 1 (A/B/C) (Maximum 3 if it contains an implication, 2 if not): ABC
Is there an implication in the statement? (Y/N): Y
Type the variables you want to use in the hypothesis (Maximum 2) (A/B/C): AB
What's the operator between the two variables in the hypothesis (OR/AND): OR
Which variable do you want to use for the conclusion (Maximum 1) (A/B/C): C
Do you want to negate that variable? (Y/N): Y

Type the variables you want to use in Premise 2 (A/B/C) (Maximum 3 if it contains an implication, 2 if not): CB
Is there an implication in the statement? (Y/N): N
What's the operator between your variables (OR/AND): OR
Do you want to negate the first variable? (Y/N): N
Do you want to negate the second variable? (Y/N): N

Type the variables you want to use in Conclusion (A/B/C) (Maximum 3 if it contains an implication, 2 if not): CA
Is there an implication in the statement? (Y/N): N
What's the operator between your variables (OR/AND): OR
Do you want to negate the first variable? (Y/N): N
Do you want to negate the second variable? (Y/N): Y
```

#### Output

```
Football        Tennis  TV      Premise 1       Premise 2       Conclusion

       1             1   1              0               1                1
       1             1   0              1               1                0
       1             0   1              0               1                1
       1             0   0              1               0                0
       0             1   1              0               1                1
       0             1   0              1               1                1
       0             0   1              1               1                1
       0             0   0              1               0                1

The argument is invalid because the conclusion is false at a critical row at least once.
```

### Example 3

If Khalid or Mariam went hiking then, Aly did not go hiking. Aly or Mariam went hiking. Thus, Aly went hiking or Khalid did not go hiking.

```
Give each of your variables a name for clarity in the truth table (A/B/C):
A: Khalid
B: Mariam
C: Aly

Type the variables you want to use in Premise 1 (A/B/C) (Maximum 3 if it contains an implication, 2 if not): ABC
Is there an implication in the statement? (Y/N): Y
Type the variables you want to use in the hypothesis (Maximum 2) (A/B/C): AB
What's the operator between the two variables in the hypothesis (OR/AND): OR
Which variable do you want to use for the conclusion (Maximum 1) (A/B/C): C
Do you want to negate that variable? (Y/N): Y

Type the variables you want to use in Premise 2 (A/B/C) (Maximum 3 if it contains an implication, 2 if not): CB
Is there an implication in the statement? (Y/N): N
What's the operator between your variables (OR/AND): OR
Do you want to negate the first variable? (Y/N): N
Do you want to negate the second variable? (Y/N): N

Type the variables you want to use in Conclusion (A/B/C) (Maximum 3 if it contains an implication, 2 if not): CA
Is there an implication in the statement? (Y/N): N
What's the operator between your variables (OR/AND): OR
Do you want to negate the first variable? (Y/N): N
Do you want to negate the second variable? (Y/N): Y
```

#### Output

```
Khalid  Mariam  Aly     Premise 1       Premise 2       Conclusion

     1       1    1             0               1                1
     1       1    0             1               1                0
     1       0    1             0               1                1
     1       0    0             1               0                0
     0       1    1             0               1                1
     0       1    0             1               1                1
     0       0    1             1               1                1
     0       0    0             1               0                1

The argument is invalid because the conclusion is false at a critical row at least once.
```
