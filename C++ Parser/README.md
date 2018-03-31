Implementation of CYK algorithm in C++

The CYK algorithm is a parsing algorithm for context-free grammars. It employs bottom-up parsing and dynamic programming. It is used to check whether a particular string can be generated from a set of productions or not.

Sample Input ::

Enter the start Variable S
 
Number of productions 4
 
S->AB|BC
A->BA|a
B->CC|b
C->AB|a
 
Enter string to be checked :baaba

Sample Output :: 
 SAC 
        SCA 
          B     B 
   AS     B    SC    AS 
    B    AC    AC     B    AC 
String can be generated