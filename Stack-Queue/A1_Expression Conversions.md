# Expression Conversions

This document covers **all standard conversions** between **Infix**, **Prefix**, and **Postfix** expressions with **algorithms, rules, and examples**.

---

## 1. Infix → Postfix

### Rules

* Operators are placed **after operands**
* Use a **stack for operators**
* Follow **operator precedence** and **associativity**

### Precedence

```
^  : highest (right associative)
* /: medium
+ -: lowest
```

### Algorithm

1. Initialize empty stack `st` and empty result string `res`
2. Scan expression from **left to right**
3. If operand → add to `res`
4. If `(` → push to stack
5. If `)` → pop from stack to `res` until `(` is found
6. If operator `op1`:

   * While stack not empty and

     * precedence(top) > precedence(op1)
     * OR precedence equal and `op1` is left-associative
   * pop to `res`
   * push `op1`
7. After scan ends, pop remaining operators

### C++ Code

```cpp
int prec(char c){
    if(c=='^') return 3;
    if(c=='*' || c=='/') return 2;
    if(c=='+' || c=='-') return 1;
    return -1;
}

string infixToPostfix(string s){
    stack<char> st;
    string res;
    for(char c : s){
        if(isalnum(c)) res += c;
        else if(c=='(') st.push(c);
        else if(c==')'){
            while(!st.empty() && st.top()!='('){
                res += st.top(); st.pop();
            }
            st.pop();
        }
        else{
            while(!st.empty() && prec(st.top()) >= prec(c)){
                res += st.top(); st.pop();
            }
            st.push(c);
        }
    }
    while(!st.empty()){
        res += st.top(); st.pop();
    }
    return res;
}
```

---

## 2. Infix → Prefix

### Trick Method

1. Reverse the infix expression
2. Replace `(` with `)` and vice versa
3. Convert reversed infix → postfix
4. Reverse the postfix result → prefix

### C++ Code

```cpp
string infixToPrefix(string s){
    reverse(s.begin(), s.end());
    for(char &c : s){
        if(c=='(') c=')';
        else if(c==')') c='(';
    }
    string postfix = infixToPostfix(s);
    reverse(postfix.begin(), postfix.end());
    return postfix;
}
```

---

## 3. Prefix → Infix

### Algorithm (Right to Left)

1. Scan expression from **right to left**
2. Operand → push
3. Operator → pop two operands and combine

### C++ Code

```cpp
string prefixToInfix(string s){
    stack<string> st;
    for(int i=s.size()-1;i>=0;i--){
        char c=s[i];
        if(isalnum(c)) st.push(string(1,c));
        else{
            string a=st.top(); st.pop();
            string b=st.top(); st.pop();
            st.push("("+a+c+b+")");
        }
    }
    return st.top();
}
```

---

## 4. Prefix → Postfix

### Algorithm

1. Scan from **right to left**
2. Operand → push
3. Operator → pop two, form postfix

### C++ Code

```cpp
string prefixToPostfix(string s){
    stack<string> st;
    for(int i=s.size()-1;i>=0;i--){
        char c=s[i];
        if(isalnum(c)) st.push(string(1,c));
        else{
            string a=st.top(); st.pop();
            string b=st.top(); st.pop();
            st.push(a+b+c);
        }
    }
    return st.top();
}
```

---

## 5. Postfix → Infix

### Algorithm (Left to Right)

1. Operand → push
2. Operator → pop two operands

### C++ Code

```cpp
string postfixToInfix(string s){
    stack<string> st;
    for(char c : s){
        if(isalnum(c)) st.push(string(1,c));
        else{
            string b=st.top(); st.pop();
            string a=st.top(); st.pop();
            st.push("("+a+c+b+")");
        }
    }
    return st.top();
}
```

---

## 6. Postfix → Prefix

### Algorithm

1. Scan from **left to right**
2. Operand → push
3. Operator → pop two operands

### C++ Code

```cpp
string postfixToPrefix(string s){
    stack<string> st;
    for(char c : s){
        if(isalnum(c)) st.push(string(1,c));
        else{
            string b=st.top(); st.pop();
            string a=st.top(); st.pop();
            st.push(c+a+b);
        }
    }
    return st.top();
}
```

---

## 7. Summary Table

| From → To        | Method Used       |
| ---------------- | ----------------- |
| Infix → Postfix  | Operator Stack    |
| Infix → Prefix   | Reverse + Postfix |
| Prefix → Infix   | Stack (R → L)     |
| Prefix → Postfix | Stack (R → L)     |
| Postfix → Infix  | Stack (L → R)     |
| Postfix → Prefix | Stack (L → R)     |

---

## 8. Exam Tips ⭐

* **Operands** → push directly
* **Operators** → pop 2 operands
* Prefix: scan **right to left**
* Postfix: scan **left to right**
* Infix always needs **precedence handling**

---

✅ This file is **lab-exam, viva, and interview ready**.
