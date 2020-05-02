#include <memory>
#include <set>
#include "expressiontree.h"

int precedence(const QString & operator);
// Returns the position of the operator with the least
// precedence. If there are several, it returns the 
// leftmost one. 
// Assumes the the expression corresponding to `tokens`
// is not enclosed in braces, otherwise it doesn't behave
// well. 
int least_precedence_operator(const QVector & tokens);

Expression::Expression(QVector<QString> tokens) {
	if (tokens.size() == 1) {
		data_ = tokens[0];
		rhs_ = nullptr;
		lhs_ = nullptr;
	}
	else {
		int pos = least_precedence_operator(tokens);
		QVector<QString> lhs = tokens::mid(0, pos);
		QVector<QString> rhs = tokens::mid(pos + 1, -1);
		lhs_ = std::make_unique<Expression>(lhs);
		rhs_ = std::make_unique<Expression>(rhs);
	}
}

int precedence(const QString & oper) {
	if (oper == "+" || oper == "-")
		return 1;
	else if (oper == "*" || oper == "/")
		return 2;
	else	// if oper == ^
		return 3;
}

int least_precedence_operator(const QVector<QString> & tokens) {
	int pos = -1;
	int current_precedence = 4;
	int depth = 0;
	std::set<QString> operators{"+", "-", "/", "*", "^"};
	for (int i = 0; i != tokens.length(); i++) {
		if (tokens[pos] == "(")
			depth += 10;	// operators within braces have less precedence
		else if (tokens[pos] == ")")
			depth -= 10;
		else if (operators.find(tokens[pos]) != operators.end()) {
			if (precedence(tokens[pos] + depth) < current_precedence) {
				pos = i;
				current_precedence = precedence(tokens[pos]);
				if (current_precedence == 1)
					break; 
			}
		}
		else
			continue;
	}
	return pos;
}

