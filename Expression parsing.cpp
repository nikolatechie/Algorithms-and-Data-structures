/*
  Problem: Given an expression containing several types of
  operations, calculate the total time needed to execute them all.

  Operations:
    1. CONST (simulates a constant operation)
      1.1 CONST() = 10
      1.2 CONST(X) = X
    2. PARA (simulates running tasks in parallel)
      2.1 PARA(OP1, OP2,.., OPN) = MAX(OP1, OP2,.., OPN)
    3. JOIN
      3.1 JOIN(OP1, OP2,.., OPN) = OP1 + OP2 + .. + OPN
    4. ARTH
      4.1 ARTH(X) = X
      4.2 ARTH(X, OP1, OP2,.., OPN) = X + OP1 + OP2 + .. + OPN
*/

#include <iostream>
#include <vector>
using namespace std;

struct Operator {
  virtual int calculateTime() = 0;
};

struct ConstOperator : public Operator {
  static const int DEFAULT_VALUE = 10;
  int val;

  ConstOperator(int val = DEFAULT_VALUE) { this->val = val; }

  int calculateTime() override { return val; }
};

struct ParaOperator : public Operator {
  vector<shared_ptr<Operator>> subOperators;

  ParaOperator(const vector<shared_ptr<Operator>> &subOperators) {
    this->subOperators = subOperators;
  }

  int calculateTime() override {
    int maxTime = 0;

    for (const shared_ptr<Operator> &op : subOperators) {
      maxTime = max(maxTime, op->calculateTime());
    }

    return maxTime;
  }
};

struct JoinOperator : public Operator {
  vector<shared_ptr<Operator>> subOperators;

  JoinOperator(const vector<shared_ptr<Operator>> &subOperators) {
    this->subOperators = subOperators;
  }

  int calculateTime() override {
    int total = 0;

    for (const shared_ptr<Operator> &op : subOperators) {
      total += op->calculateTime();
    }

    return total;
  }
};

struct ArthOperator : public Operator {
  int val;
  vector<shared_ptr<Operator>> subOperators;

  ArthOperator(const int &val, vector<shared_ptr<Operator>> subOperators = {}) {
    this->val = val;
    this->subOperators = subOperators;
  }

  int calculateTime() override {
    int total = val;

    for (const shared_ptr<Operator> &op : subOperators) {
      total += op->calculateTime();
    }

    return total;
  }
};

/// @brief Extracts suboperators from an operator.
/// @param args
/// @return Suboperators as strings.
vector<string> extractOperators(const string &args) {
  vector<string> operators;

  for (int i = 0; i < args.size(); ++i) {
    if (!(args[i] >= 'A' && args[i] <= 'Z')) {
      continue;  // Not an operator
    }

    int j = i + 4, balance = 1;  // End index, parantheses balance

    if (args.substr(i, 5) == "CONST") {
      j = i + 5;
    }

    while (balance) {
      ++j;
      if (args[j] == '(') {
        ++balance;
      } else if (args[j] == ')') {
        --balance;
      }
    }

    operators.push_back(args.substr(i, j - i + 1));
    i = j + 1;
  }

  return operators;
}

/// @brief Recursive function that, given an expression,
/// parses it, builds the structure, and calculates the answer.
/// @param expression
/// @return Pointer to an Operator instance representing the expression.
shared_ptr<Operator> calculateExpression(string expression) {
  shared_ptr<Operator> op = nullptr;

  if (expression.starts_with("CONST")) {
    if (expression.size() > 7) {
      // Contains an argument
      int val = atoi(expression.substr(6, expression.size() - 7).c_str());
      op = make_shared<ConstOperator>(val);
    } else {
      // Does not contain an argument
      op = make_shared<ConstOperator>();
    }
  } else if (expression.starts_with("PARA") || expression.starts_with("JOIN")) {
    string args = expression.substr(5, expression.size() - 6);
    vector<string> operators = extractOperators(args);
    vector<shared_ptr<Operator>> subOps;

    for (const string &it : operators) {
      shared_ptr<Operator> subOp = calculateExpression(it);
      subOps.push_back(subOp);
    }

    if (expression.starts_with("PARA")) {
      op = make_shared<ParaOperator>(subOps);
    } else {
      op = make_shared<JoinOperator>(subOps);
    }
  } else if (expression.starts_with("ARTH")) {
    string args = expression.substr(5, expression.size() - 6);

    int val = 0;
    const size_t commaIdx = args.find(',');

    if (commaIdx != string::npos) {
      // Contains operators
      val = atoi(args.substr(0, commaIdx).c_str());

      vector<string> operators = extractOperators(args.substr(commaIdx + 1));
      vector<shared_ptr<Operator>> subOps;

      for (const string &it : operators) {
        shared_ptr<Operator> subOp = calculateExpression(it);
        subOps.push_back(subOp);
      }

      op = make_shared<ArthOperator>(val, subOps);
    } else {
      // Case: ARTH(X), no other operators
      val = atoi(args.substr(0, args.size()).c_str());
      op = make_shared<ArthOperator>(val);
    }
  }

  return op;
}

/// @brief Function that runs tests and displays the summary.
void runTests() {
  int testsFailed = 0;
  const vector<string> expressions = {
      "CONST()",
      "CONST(157)",
      "JOIN(CONST(5), CONST(4))",
      "PARA(CONST(3), CONST(12), CONST(7))",
      "ARTH(825)",
      "ARTH(341, CONST(7), CONST(1))",
      "ARTH(2, PARA(CONST(3), CONST(6)))",
      "ARTH(5, JOIN(CONST(4), PARA(CONST(2), CONST(3))))",
      "ARTH(5, PARA(CONST(4), JOIN(CONST(2), CONST(3))))",
      "JOIN(CONST(5), ARTH(4, PARA(CONST(6), CONST(7))))",
      "PARA(ARTH(5, ARTH(2)), ARTH(10))"};
  const vector<int> expectedOutputs = {10, 157, 9,  12, 825, 349,
                                       8,  12,  10, 16, 10};

  cout << "\nRunning tests...\n";

  for (int test = 0; test < expressions.size(); ++test) {
    const string &expression = expressions[test];

    shared_ptr<Operator> ans = calculateExpression(expression);
    int output = -1;

    if (ans != nullptr) {
      output = ans->calculateTime();
    }

    if (output != expectedOutputs[test]) {
      ++testsFailed;
      cerr << "Test #" << test << " failed. Expected " << expectedOutputs[test]
           << ", but found " << output << ".\n";
    }
  }

  cout << "Testing has been completed!\n";

  if (testsFailed == 0) {
    cout << "STATUS: All tests have passed!\n";
  } else {
    cout << "STATUS: " << testsFailed << " test(s) have failed!\n";
  }

  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);

  runTests();

  return 0;
}