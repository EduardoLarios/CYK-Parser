import sys
import os.path
import fileinput

input_str = [["" for i in range(100)] for i in range(100)]
productions = [["" for i in range(100)] for i in range(100)]
new_grammar = [["" for i in range(100)] for i in range(100)]
dpr = ["" for i in range(100)]
num_productions = 0
p = 0

# TODO: Give friendly names to several variables, including pr, dpr, and r

def concat(a, b):
    r = a
    for i in range(0,len(b)):
        if r.find(b[i]) > len(b):
            r = r + b[i]
    return r

def create_productions(p):
    # iteradores verticales y horizontales
    r = ""
    
    for j in range(0, num_productions):
        k = 1
        while new_grammar[j][k] != "":
            if new_grammar[j][k] == p:
                r = concat(r, new_grammar[j][0])
            k = k + 1
    return r
    
def create_combinations(a,b):
    pri = a
    pri = a
    
    for i in range(0,len(a)):
        for j in range(0,len(b)):
            pri = ""
            pri = pri + a[i] + b[j]
            re = re + create_productions(pri)
    return re
    
def break_grammar(a):
    p = 0
    
    while len(a):
        i = a.find(" ")
        if i == -1:
            dpr[p] = a
            p += 1
            a = ""
        else:
            dpr[p] = a[0:i]
            p += 1
            a = a[i + 1 : i + 1 + len(a)]
            
            
def main():
    # flags e iteradores
    grammar = True
    i = 0
    j = 0
    k = 0
    lines = []
    
    for line in fileinput.input():
        lines.append(line.replace("\n",""))
    
    for line in lines:
        if line[0] > 'Z' or line[0] < 'A':
            grammar = False
            input_str[i][0] = line
            i += 1
        
        if grammar:
            productions[j][0] = line
            if (j == 0):
                start = line[0]
            j += 1
    #----------------------------------------------------------------------        
    input_number = i
    num_productions = j
    #----------------------------------------------------------------------
    for i in range(0,num_productions):
        temp = ""
        for aux in range(0, 100):
            temp = temp + productions[i][aux]
            
        a = temp
        pt = a.find(" ")
        new_grammar[i][0] = a[0:pt]
        
        a = a[pt + 1: ]
        #pt = a.find(" ")
        break_grammar(a)
        
        for j in range(0, p):
            new_grammar[i][j + 1] = dpr[j]
        
    matrix = [["" for i in range(100)] for i in range(100)]
    
    for cd in range(0, input_number):
        temp = ""
        for temporal in range(0, 100):
            temp = temp + input_str[cd][temporal]
        str = temp
        
        for i in range(0,len(str)):
            r = ""
            st = ""
            st = st + str[i]
            for j in range(0, num_productions):
                k = 1
                while (new_grammar[j][k] != ""):
                    if(new_grammar[j][k] == st):
                        r = concat(r, new_grammar[j][0]);
                    k += 1
            matrix[i][i] = r
            
        for k in range(1,len(str)):    
            for j in range(k, len(str)):
                r = ""
                for l in range((j-k), j):
                    pr = create_combinations(matrix[j - k][l], matrix[l + 1][j])
                    r = concat(r, pr)
                matrix[j -k][j] = r
                
        f = 0
        flag = True
        
        # Return Acepted/Rejected 
        for i in range(0, len(start)):
            if matrix[0][len(str) - 1].find(start[i]) <= len(matrix[0][len(str) - 1]):
                print('Accepted')
                flag = False
        if flag:
            print('Rejected')
            
            
    print(new_grammar)
    
if __name__ == '__main__':
    main()
