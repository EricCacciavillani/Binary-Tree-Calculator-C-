//
//  binaryCalTree.cpp
//  binary_tree_calc
//
//  Created by Eric Cacciavillani on 10/29/16.
//  Copyright © 2016 Eric Cacciavillani. All rights reserved.
//


#include"binarycalTree.h"


using namespace std;

// Defualt Constructor
// create a tree of one node (root) and sets it to null
Binary_Cal_Tree::Binary_Cal_Tree()
{
    main_root = NULL;//set root to default null
}



/******** Destructor ********/
Binary_Cal_Tree::~Binary_Cal_Tree()
{
    // Returns the given nodes back to the heap
    if(main_root != NULL)
    {
        /*
         by seperating it into left and right from the main root
         we can save function memmory address for our recursive recall.
         */
        //deletes the leaves/branches of the main root have been deleted
        
        free_tree(main_root->left);
        free_tree(main_root->right);
    }
    
    delete main_root;
    
}



// deallocate memory used for the branch/tree
void Binary_Cal_Tree::free_tree(T_Node* node)
{
    if (node != NULL)
    {
        free_tree(node->left);
        free_tree(node->right);
        
        delete node;
    }
    
}


//Print outs based off of given tree traversal to print out each node

/*
 -----------------------------------------------------------
 Each function uses a recursive hub and recursive call
 function just to keep main_root private away from the user
 and to just make using the print out functions look cleaner
 -----------------------------------------------------------
 */

void Binary_Cal_Tree::print_post_order()
{
    print_post_order_recursive(main_root);
}

void Binary_Cal_Tree::print_post_order_recursive(T_Node* node)
{
    if ( node != NULL )
    {
        print_post_order_recursive(node->left);
        print_post_order_recursive(node->right);
        cout << node->data << " ";
    }
}

void Binary_Cal_Tree::print_in_order()
{
    print_in_order_recursive(main_root);
}

void Binary_Cal_Tree::print_in_order_recursive(T_Node* node)
{
    if (node != NULL)
    {
        print_in_order_recursive(node->left);
        cout << node->data << " ";
        print_in_order_recursive(node->right);
    }
}

void Binary_Cal_Tree::print_pre_order()
{
    print_pre_order_recursive(main_root);
}

void Binary_Cal_Tree::print_pre_order_recursive(T_Node* node)
{
    if ( node != NULL )
    {
        cout << node->data << " ";
        print_pre_order_recursive(node->left);
        print_pre_order_recursive(node->right);
    }
}

/************************************************************
 Find the height of tree
 
 *
 *   Traverses as far down on both parts of the tree and counts
 *   each level until the lowest part is hit then compares the left
 *   and right heights and sees which one is bigger and declares that
 *   as the height.
 *
 ************************************************************/
int Binary_Cal_Tree::find_height_of_tree()
{
    if(main_root != NULL)
    {
        //looks left and right of the main root and grabs the height of both branches
        int left_branch_height  = find_height_of_branch(main_root->left),
            right_branch_height = find_height_of_branch(main_root->right);
        
        return ((left_branch_height > right_branch_height) ? left_branch_height : right_branch_height);//which is greater? left or right?
    }
    else
    {
        return 0;
    }
}

//
/************************************************************
 Find the height of branch
 
 *   Recursively moves across the given node until NULL is hit
 *   adding 1 for every node level hit. Which ever side (Left or right)
 *   is greater it will return out the count of nodes for that given
 *   side at the time.
 *   -------------------------------------------------------
 *   It will continue to do this until the end of the
 *   branch is found which is null which will then finally print out which
 *   again will return the side that is bigger (left or right).
 *
 ************************************************************/

int Binary_Cal_Tree::find_height_of_branch(T_Node* branch)
{
    if (branch == NULL)//end of the given sub-tree
    {
        return 0;//do not increase in count of the given side
    }
    
    int left_height = find_height_of_branch(branch->left);//recursive calls on the given node
    int right_height = find_height_of_branch(branch->right);
    
    if (left_height > right_height)
    {
        return left_height + 1;//append by one
    }
    else
    {
        return right_height + 1;
    }
}




/************************************************************
 Balanced tree check recursive func
 
 *
 *   Traverses as far down as the fatherest root and checks left
 *   and right to see if the difference of the two is equal to zero
 *   or one to ensure it is balanced. If it is balanced it will move up
 *   to the next given node and check from that point to see if balanced is found.
 *   ------------------------------------------------------------------------------
 *   If it is found that it is not balanced, then end all recursive calls
 *   and return false
 *
 ************************************************************/
void Binary_Cal_Tree::is_tree_balanced_recursive(T_Node* given_node,bool& checking_balance)
{
    //end of tree/branch hit return back
    if(given_node == NULL)
    {
        return;
    }
    
    /*
     at some point the tree was found to be unbalance therefore all
     checks from this point are meaningless attempt to end all recursive calls
     */
    if(checking_balance == false)
    {
        return;
    }
    
    is_tree_balanced_recursive(given_node->left,checking_balance);//recursive calls
    is_tree_balanced_recursive(given_node->right,checking_balance);
    
    //see previous
    if(checking_balance == false)
    {
        return;
    }
    
    int leftBranch_height = find_height_of_branch(given_node->left),
    rightBranch_height = find_height_of_branch(given_node->right),
    differences_of_height = 0;
    
    //dif of heights,dif must be positive int
    if(rightBranch_height > leftBranch_height)
    {
        differences_of_height = rightBranch_height - leftBranch_height;
    }
    else
    {
        differences_of_height = leftBranch_height - rightBranch_height;
    }
    
    if(differences_of_height <= 1)//checks to see if the dif is 0 or 1(can't be negative)
    {
        checking_balance =  true;
    }
    else
    {
        checking_balance =  false;
    }
}

//Hub function for checking if the tree is balanced
bool Binary_Cal_Tree::is_tree_balanced()
{
    bool checking_balance = true;
    
    is_tree_balanced_recursive(main_root,checking_balance);
    
    return checking_balance;
}

/******************** MATH FUNCTIONS ********************/
int Binary_Cal_Tree::factorial(int n)
{
    int result = 1;
    
    if(n < 0)
    {
        return 0;
    }
    
    for(int i = n; i > 0; i--)
    {
        result = result * i;
    }
    return result;
}

int Binary_Cal_Tree::permutations(int n, int r)
{
    int result = 1;
    int difference = n-r;
    
    if(difference < 0 || n < 0 || r < 0)
    {
        return 0;
    }
    
    for(int i = n; i > difference; i--)
    {
        result = result * i;
    }
    
    return result;
}
int Binary_Cal_Tree::combinations(int n, int r)
{
    
    if(r > n / 2)//combinations(n, r) == combinations(n, n - r)
    {
        r = n - r;
    }
    int result = 1,i;
    
    for(i = 1; i <= r; i++)
    {
        result = result * n - r + i;
        result = result / i;
    }
    
    return result;
}
/******************** MATH FUNCTIONS ********************/



/********************* Functions for creating cal tree *********************/

/************************************************************
 Create tree with infix
 
 *   Creates the nodes in proper areas based on the given node data.
 *
 *   -- Basic operators get a node left and right
 *   -- Functions get either left, right, or left and right
 *      based on where there vars should be so if a in order
 *      print is called it shows in the correct sequnce.
 *
 ************************************************************/
void Binary_Cal_Tree::form_cal_tree(T_Node* given_node,stack<string>& prefix_expersion, bool& error_checking_tree_create)
{
    if(prefix_expersion.size() == 0)//end recursive calls if the stack no longer has any data to pass out
    {
        return;
    }
    
    if(is_basic_operator(given_node->data))
    {
        given_node->left = new T_Node(prefix_expersion.top());
        
        if(prefix_expersion.size() == 0)//checks to see if prefix_expersion can be pulled from
        {
            error_checking_tree_create = EXIT_FAILURE;
            return;
        }
        prefix_expersion.pop();
        
        form_cal_tree(given_node->left,prefix_expersion,error_checking_tree_create);//recursive call to check the new node created to see how it should be handled
        
        given_node->right = new T_Node(prefix_expersion.top());
        
        if(prefix_expersion.size() == 0)
        {
            error_checking_tree_create = EXIT_FAILURE;
            return;
        }
        
        prefix_expersion.pop();
        form_cal_tree(given_node->right,prefix_expersion,error_checking_tree_create);
    }
    else if (is_func(given_node->data))//is the string a function?
    {
        if(functions_map[given_node->data] == VAR_LEFT_ONLY || functions_map[given_node->data] == VAR_LEFT_RIGHT_ONLY)
        {
            
            given_node->left = new T_Node(prefix_expersion.top());
            
            if(prefix_expersion.size() == 0)
            {
                error_checking_tree_create = EXIT_FAILURE;
                return;
            }
            prefix_expersion.pop();
            
            form_cal_tree(given_node->left,prefix_expersion,error_checking_tree_create);
        }
        if (functions_map[given_node->data] == VAR_LEFT_RIGHT_ONLY || functions_map[given_node->data] == VAR_RIGHT_ONLY)
        {
            given_node->right = new T_Node(prefix_expersion.top());
            
            if(prefix_expersion.size() == 0)
            {
                error_checking_tree_create = EXIT_FAILURE;
                return;
            }
            
            prefix_expersion.pop();
            form_cal_tree(given_node->right,prefix_expersion,error_checking_tree_create);
        }
        if(functions_map[given_node->data] != VAR_LEFT_ONLY && functions_map[given_node->data] != VAR_LEFT_RIGHT_ONLY && functions_map[given_node->data] != VAR_RIGHT_ONLY)
        {
            if(functions_map[given_node->data] < VAR_RIGHT_ONLY)
            {
                /*
                 This is where functions that have more than 1 input to the right of them go. In the future I would like to design a method for this
                 */
            }
            else
            {
                error_checking_tree_create = EXIT_FAILURE;
                //an unknown value exists within the map for some reason this literally cannot occur but just in  case
            }
        }
    }
    else if(is_value(given_node->data))//return if just a value is found
    {
        return;
    }
    
}
/************************************************************
 Create tree with infix
 
 *   Does all the given operations needed to create the tree
 *   --Error checking
 *   --Pulling elements
 *   --Operation checking
 *   --Checking/creating function maps
 *   --Clears out past tree
 *
 ************************************************************/
void Binary_Cal_Tree::create_tree_with_infix(string& equation_string)
{
    stack<string> inverted_infix_expersion;
    stack<string> prefix_expersion;
    
    bool error_checking_tree_create = EXIT_SUCCESS;
    
    if(functions_map.size() <= 0 )
    {
        init_functions_map(given_functions, size_of_function_array);
    }
    if(syntax_checking_to_fixing_string(equation_string,inverted_infix_expersion) == EXIT_SUCCESS)
    {
        //cout << "No errors caught in syntax checking...\n\n";
        inverted_infix_to_prefix(inverted_infix_expersion, prefix_expersion);
        
        //error check that check prefix_expersion is uninit
        if(prefix_expersion.size() <= 0)
        {
            cout << "An error in prefix_conversion was found\n";
            return;
        }
        
        if(main_root != NULL)
        {
            free_tree(main_root);//delete all parts of the previous tree if it is pre-existing
        }
        
        main_root = new T_Node(prefix_expersion.top());//create main root with top of the stack
        prefix_expersion.pop();//pop the element off because we just used it.
        
        form_cal_tree(main_root,prefix_expersion,error_checking_tree_create);//Finally! Create the given tree with the prefix_expersion
        
        if(error_checking_tree_create == EXIT_SUCCESS)
        {
            //print_in_order();//de-bugging
            //cout << equation_string << "\n";
        }
        else
        {
            cout << "An error has occured during the creation of the tree!";
            if(main_root != NULL)//delete all parts of the tree
            {
                free_tree(main_root);
            }
        }
    }
    else
    {
        cout << "A syntax error was caught!\n";
        if(main_root != NULL)//delete all parts of the tree just in case
        {
            free_tree(main_root);
        }
    }
}

/************************************************************
 Evaluate tree hub
 
 *   Allows for a more descriptive output if the main_root is NULL
 *   and simplier function call for the user.
 *
 ************************************************************/
double Binary_Cal_Tree::evaluate_tree(bool& error_handling)
{
    error_handling = EXIT_SUCCESS;
    
    if(main_root == NULL)
    {
//        cout << "\nThere is no tree to evulate either because the one you provided was faulty in it infix notation or you never inputed one in the first place.\n";
        error_handling = EXIT_FAILURE;
    }
    
    if(error_handling == EXIT_SUCCESS)
    {
        return evaluate_tree_recursive(main_root,error_handling);
    }
    else
    {
        return -1;
    }
}
/************************************************************
 Evaluate tree recursive
 
 *   Recursively move through the tree and return the given element
 *   if it is a value and if it is an operations traverse
 *   left,right,or both left and right depending on the operation in question.
 
 ----------------------------------------------------------------
 
 *   Then with the given values will passed through the operations
 *    -Should continue to traverse left and right until the given values are passed
 ----------------------------------------------------------------
 
 *   Will end all recursive calls if error_handling is EXIT_FAILURE
 *   --Which will only occur if the node is null or the data inside the
 *       node is not init.
 *
 ----------------------------------------------------------------
 ************************************************************/
double Binary_Cal_Tree::evaluate_tree_recursive(T_Node* given_node,bool& error_handling)
{
    if(given_node == NULL || given_node->data == "")//Error found null node and unit data
    {
        error_handling = EXIT_FAILURE;
        return -1;
    }
    if(error_handling == EXIT_FAILURE)//end all recursive calls if error_handling is EXIT_FAILURE
    {
        return -1;
    }
    if(is_value(given_node->data))//is a value
    {
        return stod(given_node->data);//convert to a double and return the given value
    }
    //traverse down the tree to evaluate and process the values to pass back to the given operations
    else if(is_basic_operator(given_node->data))
    {
        if(given_node->data == "+")
        {
            return evaluate_tree_recursive(given_node->left,error_handling) + evaluate_tree_recursive(given_node->right,error_handling);
        }
        else if(given_node->data == "-")
        {
            return evaluate_tree_recursive(given_node->left,error_handling) - evaluate_tree_recursive(given_node->right,error_handling);
        }
        else if(given_node->data == "/")
        {
            return (evaluate_tree_recursive(given_node->left,error_handling) / evaluate_tree_recursive(given_node->right,error_handling));
        }
        else if(given_node->data == "*" || given_node->data == "x")
        {
            return evaluate_tree_recursive(given_node->left,error_handling) * evaluate_tree_recursive(given_node->right,error_handling);
        }
        else if (given_node->data == "^")
        {
            return pow(evaluate_tree_recursive(given_node->left,error_handling),evaluate_tree_recursive(given_node->right,error_handling));
        }
        else//unknown basic operator was added somehow (this should never occur)
        {
            error_handling = EXIT_FAILURE;
            return -1;
        }
    }
    else if (is_func(given_node->data))
    {
        if(given_node->data == "!")
        {
            return factorial(evaluate_tree_recursive(given_node->left,error_handling));
        }
        else if(given_node->data == "tan(")
        {
            return tan(evaluate_tree_recursive(given_node->right,error_handling));
        }
        else if(given_node->data == "sin(")
        {
            return sin(evaluate_tree_recursive(given_node->right,error_handling));
        }
        else if (given_node->data == "cos(")
        {
            return cos(evaluate_tree_recursive(given_node->right,error_handling));
        }
        else if (given_node->data == "npr")
        {
            return permutations(evaluate_tree_recursive(given_node->left,error_handling),evaluate_tree_recursive(given_node->right,error_handling));
        }
        else if (given_node->data == "ncr")
        {
            return combinations(evaluate_tree_recursive(given_node->left,error_handling),evaluate_tree_recursive(given_node->right,error_handling));
        }
        else//unknown basic function was added somehow (this should never occur)
        {
            error_handling = EXIT_FAILURE;
            return -1;
        }
    }
    else//unknown event occured
    {
        error_handling = EXIT_FAILURE;
        return -1;
    }
    
}
/************************************************************
 Init functions map
 
 *   Passes an array of strings over and takes apart the given
 *   string to grab the given function name making that the key of
 *   the map and based off the postioning and amount of the
 *   operands/vars will dictate the value of the key.
 *
 ************************************************************/
void Binary_Cal_Tree::init_functions_map(string functions[],unsigned int size_of_array)
{
    //explict var names and values for hash map
    
    
    //checks the beginning and end of the string to see if a var exist there
    bool var_caught_begin,
    var_caught_end;
    
    size_t length_of_string;
    
    string function_name = "";//function name for map key
    
    
    int start_indexer = 0,//start indexer for each part of the string
    given_order_type = 0;//used for value for map key
    
    //allocate vars for iner nested loops
    int k =0,
    n = 0;
    //Traverse the array of strings
    for(int i = 0; i < size_of_array; i++)
    {
        length_of_string = functions[i].size();
        
        //resets all values
        start_indexer = 0;
        
        var_caught_begin = false;
        var_caught_end = false;
        
        given_order_type = 0;
        function_name = "";
        
        //make sure the string could be a function (var and char size of 2)
        if(length_of_string > 1)
        {
            //checks the first part of the given string
            if(functions[i][0] == 'x')
            {
                var_caught_begin = true;
                start_indexer++;
                
                if(functions[i][1] == ' ')
                {
                    start_indexer++;
                }
            }
            //checks the last part of the given string
            if(functions[i][length_of_string-1] == 'x')
            {
                var_caught_end = true;
                length_of_string--;
                
                if(functions[i][length_of_string-1] == ' ')
                {
                    length_of_string--;
                }
            }
            
            /*
             Traverses across the rest of the string that must be the function name unless it is a function that has more then two inputs on the right hand side.
             */
            for(k = start_indexer; k < length_of_string; k++)
            {
                function_name = function_name + functions[i][k];
            }
            
            //Based off the booleans get the value for function name
            if(var_caught_begin == true && var_caught_end == false)
            {
                given_order_type = VAR_LEFT_ONLY;
            }
            else if (var_caught_begin == true && var_caught_end == true)
            {
                given_order_type = VAR_LEFT_RIGHT_ONLY;
            }
            else if (var_caught_begin == false && var_caught_end == true)
            {
                given_order_type = VAR_RIGHT_ONLY;
            }
            else if (var_caught_begin == false && var_caught_end == false)
            {
                function_name = "";//clear out string
                
                //traverse until char '|'
                for(n = 0; n < length_of_string && functions[i][n] != '|'; n++)
                {
                    function_name = function_name + functions[i][n];
                }
                
                for(; n < length_of_string; n++)
                {
                    if(functions[i][n] == 'x')//count the amount of vars
                    {
                        given_order_type--;
                    }
                }
            }
        }
        
        if(given_order_type != 0)
        {
            functions_map[function_name] = given_order_type;//create a hash map with the key and value
        }
    }
}

//Passes back true if the given char is a basic operator
bool Binary_Cal_Tree::is_basic_operator(char character)
{
    if(character == '+' || character == '-' || character == '*' || character == '/' || character == 'x' || character == '^')
    {
        return true;
    }
    else
    {
        return false;
    }
}
//Overloading is_basic_operator for string
bool Binary_Cal_Tree::is_basic_operator(string str)
{
    if(str == "+" || str == "-" || str == "*" || str == "x" || str == "/"|| str == "^")
    {
        return true;
    }
    else
    {
        return false;
    }
}

//Passes back true if the given string is a function from the pre-formed function_map
bool Binary_Cal_Tree::is_func(string str)
{
    it = functions_map.find(str);
    
    if(it != functions_map.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}
//Passes back true if the given string is a value(double data type).
bool Binary_Cal_Tree::is_value(string str)
{
    try
    {
        stod(str);
        return true;
    }
    catch (invalid_argument&)
    {
        return false;
    }
    catch (out_of_range&)
    {
        return false;
    }
}
//Overload is_value for char
bool Binary_Cal_Tree::is_value(char character)
{
    if(('0' <= character && character <= '9') || character == '.')
    {
        return true;
    }
    else
    {
        return false;
    }
}

//Cycles through all checks to see what the given type is
int Binary_Cal_Tree::check_if_val_oper_char_parth_func(char character)
{
    if(is_value(character))
    {
        return VAL_HIT;
    }
    else if (is_basic_operator(character))
    {
        return OPER_HIT;
    }
    else if (is_func(string(1,character)))//1 character function
    {
        return FUNC_HIT;
    }
    else if (character == '(')
    {
        return PAR_START_HIT;
    }
    else if (character == ')')
    {
        return PAR_END_HIT;
    }
    else
    {
        return CHAR_HIT;
    }
}

//Gives the priority level for the basic operations
int Binary_Cal_Tree::get_priority(string operator_type)
{
    if(operator_type == "+" || operator_type == "-")
    {
        return 1;
    }
    else if(operator_type == "*" || operator_type == "/" || operator_type == "x")
    {
        return 2;
    }
    else if (operator_type == "^")
    {
        return 3;
    }
    else if (is_func(operator_type))
    {
        return 4;
    }
    else
    {
        return -1;//error occured
    }
}

//Displays the stack by value not by refrence
void Binary_Cal_Tree::display_stack(stack<string> S)
{
    while(!S.empty())
    {
        cout << S.top() << ",";
        S.pop();
    }
    cout << "\n";
}

//Checks to see if op1 is greater priority level than op2 passes true, else false
bool Binary_Cal_Tree::compare_pritories(string op_1, string op_2)
{
    int op1_priority = get_priority(op_1);
    int op2_priority = get_priority(op_2);
    
    return op1_priority > op2_priority ? true : false;
}



/************************************************************
 Inverted Infix to prefix
 
 *   Requirements for usage:
 *       -Assumed that it has passed all checks for syntax checking
 *       -Each part of the infix expersion must be seperated out in a stack
 *       -The infix expersion should be passed inverted
 
 *   (Rather then writing it all down I found a video that describes what I did very nicely)
 *   https://www.youtube.com/watch?v=fUxnb5eTRS0
 *   (It shows no code implementation just the given method)
 *
 ************************************************************/
void Binary_Cal_Tree::inverted_infix_to_prefix(stack<string>& infix_expression,stack<string>& prefix_expersion)
{
    string given_element;
    
    stack<string> garbage_stack;
    
    while(!infix_expression.empty())
    {
        given_element = infix_expression.top();
        infix_expression.pop();
        
        if(is_value(given_element))//if the given string is a value add it to the stack
        {
            prefix_expersion.push(given_element);
        }
        else if(given_element == "(")//found "end" of encapsulation found (in quotes because technically makes it end)
        {
            /*
             Since the infix is inverted a '(' means an end case for the set of data. Therefore, we must have populated garbage stack with operands,operators,etc
             */
            
            //dumpt the stack until "start" of encapsaltion occurs
            while(!garbage_stack.empty() && garbage_stack.top() != ")")
            {
                prefix_expersion.push(garbage_stack.top());
                garbage_stack.pop();
            }
            if(!garbage_stack.empty())
            {
                garbage_stack.pop();//get rid of the ')'
            }
            else
            {
                //shouldn't occur but just in case error checking
                cout << "Error!!! Encapsulation of parenthesis error!";
            }
            
        }
        else if(given_element == ")")//add "start" point of encapsulation
        {
            garbage_stack.push(given_element);
        }
        else//operator or function
        {
            //Dump to prefix_expersion until the given operator has more prioty then the one bellow it
            while(!garbage_stack.empty() && compare_pritories(garbage_stack.top(),given_element))
            {
                prefix_expersion.push(garbage_stack.top());
                garbage_stack.pop();
            }
            garbage_stack.push(given_element);
        }
    }
    //Pass the rest of the garbage stack to the
    while( !garbage_stack.empty() )
    {
        prefix_expersion.push(garbage_stack.top());
        garbage_stack.pop();
    }
}

/************************************************************
 Syntax Checking to fixing string
 
 *   All functionality bellow this points is to do:
 *  -add in needed parts (such as * or ')')in the correct place)
 *  -error checking and termination of the function if need be
 
 ------------------------------------------------------------------------------
 
 *  -seperates out from the newly formed string of chars/values (given element)
 *  and describes the type with last_type because it stops when a different type
 *  is found breaking the string, this described as last type.
 *  -Using last type and current type allows for explict error handling and corrections.
 *  -Ex. The case (). if(last_type == PAR_START_HIT) && current_type == PAR_END_HIT) error errupt. (isn't exactly wrote like that down bellow but the logic is the same)
 
 ------------------------------------------------------------------------------
 
 *  -encapsulation of parthesis
 *  -check quanity of both start and end parthesis
 *  -As well as encapsulate_count (which can really be the same as start-end parthesis but an explict checker that doesn't have to do the same
 *   operation repeatdely sounds more efficent)
 ------------------------------------------------------------------------------
 
 *  --Mainly designed to allow for scalability for more error checking and verfications in the future.
 *
 ************************************************************/
bool Binary_Cal_Tree::syntax_checking_to_fixing_string(string& equation_str,stack<string>& infix_expersion)
{
    bool error_handling = EXIT_SUCCESS;
    /*
     converts everything to lower case to ensure that the functions to map comparsions are the same case type
     */
    transform(equation_str.begin(), equation_str.end(), equation_str.begin(), ::tolower);
    
    string given_element;//grabs the seperated element in which we analyze
    
    int current_type = 0,//used to tell what our current element type we are working with
        last_type = -1,//last element type we are working with
        i = 0;//iterator
    
    //counts the parthesis of both start and end as well as checking to see if they encapsulate correctly.
    unsigned int start_par_count = 0,
                 end_par_count = 0,
                 encapsulate_count = 0;
    
    for(i = 0; i <= equation_str.length() && error_handling != EXIT_FAILURE; i++)
    {
        if (equation_str[i] == ' ' || equation_str[i] == '\n' || equation_str[i] == '\t' || equation_str[i] == ',')//check white space
        {
            equation_str.erase(i, 1);//get rid of white space
            
            //go back 1 iteration and reloop
            i--;
            continue;
        }
        current_type = check_if_val_oper_char_parth_func(equation_str[i]);//check the given type of the char,(which could be function,value,char,),(,operator)
        
        //Ensures we can grab multiple chars or values to form into values or function names
        
        if((current_type == last_type || last_type == -1) && (last_type != PAR_START_HIT && last_type != PAR_END_HIT))
        {
            given_element = given_element + equation_str[i];//append char to our element we are checking
            last_type = current_type;
        }
        else
        {
            /*
             ///NEGATIVE CHECK IN TESTING (Don't feel like it is ready yet so giving it more testing before I go fully to intergrating it into the given system)
             
             //This works fine until you try something like 5+-2 because we have a check in place that checks for operator and operator touching so more work needs to be done to have this working without changing everything else
             
             
             //If there is any areas where subtraction isn't working correctly I would
             
             
             if(given_element == "-")
             {
             if(infix_expersion.size() > 0)
             {
             if(is_func(infix_expersion.top()))
             {
             if(functions_map[infix_expersion.top()] != VAR_LEFT_ONLY)
             {
             i--;
             last_type = -1;
             continue;
             }
             }
             else if (is_basic_operator(infix_expersion.top()) || infix_expersion.top() == "(")
             {
             i--;
             last_type = -1;
             continue;
             }
             }
             else
             {
             i--;
             last_type = -1;
             continue;
             }
             }
             ///NEGATIVE CHECK
             */
            if(last_type == VAL_HIT)
            {
                if(is_value(given_element) != true)//are you sure it is a value?
                {
                    error_handling = EXIT_FAILURE;
                    cout << "CONVERSION OF VALUE/SEPERATION OF VALUE ERROR OCCURED\n";
                    break;
                }
                
                if(current_type == PAR_START_HIT )
                {
                    equation_str.insert(i,"*");//insert * times if number and then '(' Ex. 5(6) == 5*(6)
                }
                else if (infix_expersion.size() > 0 && is_func(infix_expersion.top()))//ensure that infix_expersion is actually filled with data before checking top
                {
                    if(!(functions_map[infix_expersion.top()] == VAR_LEFT_RIGHT_ONLY || functions_map[infix_expersion.top()] <= VAR_RIGHT_ONLY))//checks to see if a value occured to the right of function that required a value to the right
                    {
                        error_handling = EXIT_FAILURE;
                        cout << "FUNCTION INPUT ERROR ON THE RIGHT WITH VARS\n";
                        break;
                    }
                }
            }
            else if(last_type == CHAR_HIT)
            {
                if(current_type == PAR_START_HIT)
                {
                    if(is_func(given_element + "(") == true)//atempt to see if function needs (
                    {
                        i++;//move up to ignore "(" it is part of the given function
                        given_element = given_element + "(";
                    }
                    else//atempt to see if function at all provided the check above proved false
                    {
                        if(is_func(given_element) != true)//are you sure this is a function?
                        {
                            cout << "CHAR ERROR OCCURED IN CHECKING FOR FUNCTION!\n";
                            error_handling = EXIT_FAILURE;
                            break;
                        }
                    }
                }
                else if(is_func(given_element) != true)//are you sure this is a function?
                {
                    cout << "CHAR ERROR OCCURED IN CHECKING FOR FUNCTION!\n";
                    error_handling = EXIT_FAILURE;
                    break;
                }
                //Since it past the check above it must be a function. So it is safe to check the map directly with the given string
                
                else if (functions_map[given_element] == VAR_LEFT_ONLY || functions_map[given_element] == VAR_LEFT_RIGHT_ONLY)//checks to see if a value occured to the right of function that required a value to the right
                {
                    if(infix_expersion.size() > 0 && !(is_value(infix_expersion.top())))
                    {
                        cout << "FUNCTION INPUT ERROR ON THE LEFT WITH VARS\n";
                        error_handling = EXIT_FAILURE;
                        break;
                    }
                }
            }
            else if (last_type == OPER_HIT)
            {
                //Check to see if it is a operator, an operator should not be next to another operator or an end par nor should it occur at the end of the equation
                if(is_basic_operator(given_element) != true || current_type == OPER_HIT || i == equation_str.length()||current_type == PAR_END_HIT)
                {
                    cout << "OPER ERROR OCCURED\n";
                    error_handling = EXIT_FAILURE;
                    break;
                }
            }
            else if (last_type == PAR_START_HIT)
            {
                start_par_count++;//Adds to our count check for '('
                encapsulate_count++;//An encapsulation should occur
                
                if(given_element != "(" || current_type == PAR_END_HIT || i == equation_str.length())
                {
                    cout << "PAR START ERROR\n";
                    error_handling = EXIT_FAILURE;
                    break;
                }
            }
            else if (last_type == PAR_END_HIT)
            {
                end_par_count++;//Adds to our count check for ')'
                encapsulate_count--;//An encapsulation should occur
                
                if(encapsulate_count == -1)// A end parthesis was hit without a open parthesis before hand. Therefore error
                {
                    error_handling = EXIT_FAILURE;
                    break;
                }
                if(current_type == PAR_START_HIT|| current_type == VAL_HIT)
                {
                    equation_str.insert(i,"*");
                }
                if(given_element != ")")
                {
                    cout << "PAR END ERROR\n";
                    error_handling = EXIT_FAILURE;
                    break;
                }
            }
            //cout << given_element << "f\n";//de-buger
            infix_expersion.push(given_element);
            //Resets the process for the next element to grab
            given_element = "";
            last_type = -1;
            i--;
        }
    }
    
    i--;
    
    //Ensures that we seperated out of elements correctly on the last run through of the process
    if(given_element.size() > 1 && error_handling == EXIT_SUCCESS)
    {
        error_handling = EXIT_FAILURE;
        cout << "Seperation of elements error\n";
    }
    
    
    if(error_handling != EXIT_FAILURE)
    {
        if(encapsulate_count > 0)
        {
            cout << "An attempt was made to fix the infix's parthesis...\n";
        }
        //adds in ')' or more at the end of the string to encapsulate the given equation
        for(int j = 0; j < encapsulate_count; j++)
        {
            equation_str.insert(i,")");
            infix_expersion.push(")");
            end_par_count++;
            
            i++;
        }
    }
    
    if(start_par_count != end_par_count && error_handling != EXIT_FAILURE)
    {
        cout << "The parenthesis are inequal parthesis!!!\n";
        error_handling = EXIT_FAILURE;
    }
    
    return error_handling;
}

//removes all spacing from a string of chars
void Binary_Cal_Tree::remove_spaceing(string& str)
{
    for (size_t i = 0; i < str.length(); i++)
    {
        if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
        {
            str.erase(i, 1);
            i--;
        }
    }
}
