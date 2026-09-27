#include <iostream>
#include <vector>
#include <stack>
#include <sstream>
#include <string>
using namespace std;



bool isFunction(const string& tok) {
    return tok == "sin" || tok == "cos" || tok == "tan" ||
           tok == "sqrt" || tok == "pm";
}

bool isOperator(const string& tok) {
    return tok == "+" || tok == "-" || tok == "*" || tok == "/" || tok == "^";
}

int precedence(const string& tok) {
    if (isFunction(tok)) return 4;      // functions / unary bind tightest
    if (tok == "^") return 3;
    if (tok == "*" || tok == "/") return 2;
    if (tok == "+" || tok == "-") return 1;
    return -1; // operand
}

bool isRightAssociative(const string& tok) {
    return tok == "^"; // functions are handled separately, don't need this flag
}


vector<string> tokenize(const string& expr) {
    vector<string> tokens;
    istringstream iss(expr);
    string tok;
    while (iss >> tok) tokens.push_back(tok);
    return tokens;
}


vector<string> infixToPostfix(const vector<string>& tokens) {
    stack<string> st;
    vector<string> output;

    for (const string& tok : tokens) {
        if (tok == "(") {
            st.push(tok);
        } else if (isFunction(tok)) {
        
            st.push(tok);
        } else if (tok == ")") {
           
            while (!st.empty() && st.top() != "(") {
                output.push_back(st.top());
                st.pop();
            }
            if (!st.empty()) st.pop(); // discard the "("

          
            while (!st.empty() && isFunction(st.top())) {
                output.push_back(st.top());
                st.pop();
            }
        } else if (isOperator(tok)) {
            while (!st.empty() && st.top() != "(" &&
                   (isFunction(st.top()) ||
                    precedence(st.top()) > precedence(tok) ||
                    (precedence(st.top()) == precedence(tok) && !isRightAssociative(tok)))) {
                output.push_back(st.top());
                st.pop();
            }
            st.push(tok);
        } else {
            // operand: number or identifier (theta, alpha, beta, 1, 2, ...)
            output.push_back(tok);
        }
    }

    while (!st.empty()) {
        output.push_back(st.top());
        st.pop();
    }

    return output;
}

struct TreeNode {
    string val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(string v) : val(v), left(nullptr), right(nullptr) {}
};

TreeNode* buildTreeFromPostfix(const vector<string>& postfix) {
    stack<TreeNode*> st;

    for (const string& tok : postfix) {
        TreeNode* node = new TreeNode(tok);

        if (isFunction(tok)) {
            // unary: only one child
            TreeNode* child = st.top(); st.pop();
            node->right = child;
        } else if (isOperator(tok)) {
            // binary: two children (order matters!)
            TreeNode* right = st.top(); st.pop();
            TreeNode* left = st.top(); st.pop();
            node->left = left;
            node->right = right;
        }
        // else: operand -> leaf node, no children

        st.push(node);
    }

    return st.top(); // root of the expression tree
}

string preorder(TreeNode* node) {
    if (node == nullptr) return "";

    string result = node->val;
    if (node->left) result += " " + preorder(node->left);
    if (node->right) result += " " + preorder(node->right);
    return result;
}


string joinAndPrettify(const vector<string>& tokens) {
    string s;
    for (size_t i = 0; i < tokens.size(); i++) {
        if (i > 0) s += " ";
        s += tokens[i];
    }
    size_t pos;
    while ((pos = s.find("pm")) != string::npos) {
        s.replace(pos, 2, "\u00B1"); // ±
    }
    return s;
}

string prettify(string s) {
    size_t pos;
    while ((pos = s.find("pm")) != string::npos) {
        s.replace(pos, 2, "\u00B1"); // ±
    }
    return s;
}

void convertAndDisplay(const string& label, const string& infixExpr) {
    cout << "\n===== " << label << " =====\n";
    cout << "Infix : " << prettify(infixExpr) << endl;

    vector<string> tokens = tokenize(infixExpr);
    vector<string> postfix = infixToPostfix(tokens);
    cout << "Postfix: " << joinAndPrettify(postfix) << endl;

    TreeNode* root = buildTreeFromPostfix(postfix);
    string prefix = preorder(root);
    cout << "Prefix : " << prettify(prefix) << endl;
}

int main() {
 
    string expr1 = "pm sqrt ( ( 1 - cos ( theta ) ) / ( 1 + cos ( theta ) ) )";

    string expr2 = "1 - cos ( theta ) ^ 2";

   
    string expr3 = "( 1 / 2 ) * ( cos ( alpha - beta ) - cos ( alpha + beta ) )";

    convertAndDisplay("1. Double-Angle Formula RHS", expr1);
    convertAndDisplay("2. Pythagorean Identity RHS", expr2);
    convertAndDisplay("3. Product-to-Sum Identity RHS", expr3);

    return 0;
}
