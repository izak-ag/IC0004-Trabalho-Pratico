#pragma once

#include <random>
#include <vector>
#include <sstream>


/*
 * enum to store exit states for certain functions in the solver
 */
enum RetVal {
    r_satisfied,   // the formula has been satisfied
    r_unsatisfied, // the formula has been unsatisfied
    r_normal       // the formula is unresolved so far
};

/*
 * class containing the member variables and functions of the CDCL SAT solver
 */
class SATSolverCDCL {
private:
    /*
    * a vector to store the state of each variable, where the assignment is as
    * 1 - assigned true
    * 0 - assigned false
    * -1 - unassigned
    */
    std::vector<int> literals;

    /*
    * a 2D vector that stores a list of literals for every clause
    * for the one indexed variable l, l is stored when it is present with
    * positive polarity and -l is stored when it is present with negative
    * polarity
    */
    std::vector<std::vector<int>> literal_list_per_clause;

    /*
    * vector that stores the total number of occurrences of the variable in the
    * formula this is updated when clauses are learnt this is used for choosing
    * the next variable to be assigned
    */
    std::vector<int> literal_frequency;

    /*
    * vector that stores the difference in the number of positive and negative
    * occurrences of the variable in the formula. this is updated when clauses
    * are learnt
    */
    std::vector<int> literal_polarity;

    /*
    * vector to store backup of the frequencies, as the original will be set to
    * -1 when the variable is assigned. this is use to reset the value back to
    * the original if and when the variable is later unassigned
    */
    std::vector<int> original_literal_frequency;
    int literal_count;    // number of variables in the formula
    int clause_count;     // number of clauses in the formula
    int kappa_antecedent; // antecedent of the conflict, kappa

    /*
    * vector to store the decision level of each variable
    * when not yet assigned, it contains -1
    */
    std::vector<int> literal_decision_level;

    /*
    * vector to store the antecedent of each variable
    * NIL is represented by -1
    */
    std::vector<int> literal_antecedent;
    int assigned_literal_count; // the number of variables assigned so far
    bool already_unsatisfied;   // if the formula contains any empty clause
                                // originally
    int pick_counter; // the number of times we have chosen a variable freely
                        // based on frequency
    std::random_device random_generator;
    std::mt19937 generator;

    int unit_propagate(int); // to perform unit propagation
    // to assign a literal with given value, antecedent and decision level
    void assign_literal(int, int, int);
    void unassign_literal(int); // to unassign a given literal
                                // to convert the one indexed literal with sign to
                                // zero indexed without sign
    int literal_to_variable_index(int);
    int conflict_analysis_and_backtrack(int); // to perform conflict analysis and backtrack
    std::vector<int> &resolve(std::vector<int> &, int);     // to resolve two clauses and get the result
    int pick_branching_variable(); // to pick the next free assignment
    bool all_variables_assigned(); // to check if all variables have already been
                                    // assigned
    void show_result(int);         // to display the result of the solver

public:
    SATSolverCDCL() : generator(random_generator()) {} // constructor
    void initialize(std::stringstream&);               // to initialize the solver
    int CDCL(); // to perform the CDCL algorithm and return the appropriate result
                // state
    void solve(); // to solve the problem and display the result
};