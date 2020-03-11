//
//  binarySearchTree.hpp
//  binary_tree_calc
//
//  Created by Eric Cacciavillani on 10/29/16.
//  Copyright © 2016 Eric Cacciavillani. All rights reserved.
//


#ifndef BINARY_CAL_TREE_H
#define BINARY_CAL_TREE_H

#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <queue>
#include <stack>
#include <math.h>

using namespace std;

/******************* Node Def *******************/
struct T_Node
{
    string data;
    T_Node* left = nullptr; // left pointer to a node on the left
    T_Node* right = nullptr; // right pointer to a node on the right
    
    
    // Constructor with defualt initializrs
    T_Node(string str, T_Node* left_pass = nullptr, T_Node* right_pass = nullptr)
    {
        data = str;
        left = left_pass;
        right = right_pass;
    }
    
};
/******************* Node Def *******************/



/******************* Class Def *******************/
class Binary_Cal_Tree
{
private:
    T_Node* main_root = nullptr;
    
    map<string,int> functions_map;//hash map for function names (used to return the var placement for the given function)
    map<string,int>::iterator it;
    
    /*
     Rules for creating your own function name!
     -Do not close your function off with an ')'
     -Must be in lower case format or else it will not work(all parts)
     -Declare var placement with x
     -The function seperator checks the begining and end of the string for x currently so make sure you place the vars at the start and end of the string
     -DO NOT USE BASIC OPERATORS IN THE FUNCTION NAME!
     -------------------------------------------
     Expermintantal from this point
     -For muliple vars to the right they must be seperated by : and the start and end of the function must be declared with |
     -Ex. n_rt(|x:x|     Again please do not use this n_rt function! It has not be implmented yet!
     */
    string given_functions[7] = {"tan(x","cos(x","sin(x","x!","x npr x","x ncr x","n_rt(|x:x|"};
    
    unsigned const int size_of_function_array = sizeof(given_functions) / sizeof(string);
    
    
    //Explict def of var positions
    const int VAL_HIT = 0,
              OPER_HIT = 1,
              FUNC_HIT = 2,
              CHAR_HIT = 3,
              PAR_START_HIT = 4,
              PAR_END_HIT = 5;
    
    //Explict def of var positions
    const int VAR_LEFT_ONLY = 1,
              VAR_LEFT_RIGHT_ONLY = 2,
              VAR_RIGHT_ONLY = -1;
    
    
    void insert_node(T_Node* root, int num);    // A helper function to add nodes to the tree
    void free_tree(T_Node* root);                // Deallocate memory used for the tree
    
    /****************** PRINT OUTS **********************/
    
    /*Recursive print out to be used for the tree for hub functions*/
    void print_post_order_recursive(T_Node*);
    
    void print_in_order_recursive(T_Node*);
    
    void print_pre_order_recursive(T_Node*);
    
    /****************** PRINT OUTS **********************/
    
    
    
    /********************* SUB-Utilities *********************/
    
    int find_height_of_branch(T_Node*);//gets the height from the given node (root) down to lowest part of the branch/tree
    
    void is_tree_balanced_recursive(T_Node* given_node,bool&);//is balanced tree
    
    void init_functions_map(string[],unsigned int);//creating the given map
    
    /********************* SUB-Utilities *********************/
    
    
    
    
    
    /********************* Functions for creating cal tree *********************/
    
    
    /******* Main functionality ******/
    
    
    bool syntax_checking_to_fixing_string(string&,stack<string>&);//checks the syntax of the equation string and is valid and seperates out given
    //parts to be used for a stack
    
    void inverted_infix_to_prefix(stack<string>&,stack<string>&);//tales the inversion of the equation (which is a stack)
    
    /******* Main functionality ******/
    
    
    
    /******* Determing types ******/
    
    //Returns true if is that given type and false if it is not
    //Ex. is_basic_operator("+") would return true
    
    bool is_basic_operator(char);
    bool is_basic_operator(string);
    bool is_func(string);
    bool is_value(char);
    bool is_value(string);
    int check_if_val_oper_char_parth_func(char);
    
    /******* Determing types ******/
    
    
    
    /******* Priority checking ******/
    
    int get_priority(string);//Gets the priority levels of the operator or function type passed
    bool compare_pritories(string, string);//From left to right checks to see which string has a higher priority level
    
    /******* Priority checking ******/
    
    /******* Utilities ******/
    
    void display_stack(stack<string>);//displays a stack
    void remove_spaceing(string&);//removes spaces of a string
    
    /******* Utilities ******/
    
    /******** Added Math Functions ********/
    
    int factorial(int);
    int permutations(int, int);
    int combinations(int, int);
    
    /******** Added Math Functions ********/
    
    void form_cal_tree(T_Node*,stack<string>&,bool&);//Creates the tree
    
    /********************* Functions for creating cal tree *********************/
    
    
public:
    
    Binary_Cal_Tree();// Default Constructor
    
    void create_tree_with_infix(string&);//Allows the user to plug in their string and let all the private function fix and check all the work for them
    
    ~Binary_Cal_Tree();// Destructor
    
    //Print outs (using function hubs to start recursive loops)
    void print_post_order();
    void print_in_order();
    void print_pre_order();
    
    int find_height_of_tree();//Gets the height of the tree
    
    bool is_tree_balanced();//Checks on each sub-tree to see if it is balanced
    
    double evaluate_tree(bool&);//Calculate the equation and with the passed boolean ensure that no errors occur
    double evaluate_tree_recursive(T_Node*,bool&);
    
};

#endif

/******************* Class Def *******************/
