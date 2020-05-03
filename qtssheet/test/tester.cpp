#include <QVector>
#include <QString>
#include <QChar>
#include <QDebug>
#include <set>
#include "/home/piet/Projects/cs106bx/qtssheet/tokenizer.h"
#include "/home/piet/Projects/cs106bx/qtssheet/expression.h"

Tokenizer::Tokenizer(){}

bool Tokenizer::tokenize(const QString & formula) {
	// reset tokenized_form_
	tokenized_form_.clear();

	int pos = 0;
	while (pos != formula.length()) {
		QString token;
		// skip whitespaces
		if (formula[pos] == " ")
			++pos;
		else if (capital_type_.find(formula[pos]) != capital_type_.end()) {
			token += formula[pos];
			++pos;
			while (number_type_.find(formula[pos]) != number_type_.end()) {
				if (formula[pos] == '.')
					return false;
				token += formula[pos];
				++pos;
			}	
			tokenized_form_.push_back(token);
			token = "";
		}
		else if (number_type_.find(formula[pos]) != number_type_.end()) {
			while (number_type_.find(formula[pos]) != number_type_.end()) {
				token += formula[pos];
				++pos;
			}	
			tokenized_form_.push_back(token);
			token = "";
		}
		else if (punctuation_type_.find(formula[pos]) != punctuation_type_.end()) {
			token = QString(formula[pos]);
			tokenized_form_.push_back(token);
			token = "";
			++pos;
		}
		else if (operation_type_.find(formula[pos]) != operation_type_.end()) {
			token = QString(formula[pos]);
			tokenized_form_.push_back(token);
			token = "";
			++pos;
		}
		else
			return false;
	}
	return true;
}

QVector<QString> Tokenizer::tokenized() const {
	return tokenized_form_;
}

int precedence(const QString & oper);
// Returns the position of the operator with the least
// precedence. If there are several, it returns the 
// leftmost one. 
// Assumes the the expression corresponding to `tokens`
// is not enclosed in braces, otherwise it doesn't behave
// well. 
int least_precedence_operator(const QVector<QString> & tokens);

Expression::Expression(QVector<QString> & tokens) {
	if (tokens.size() == 1) {
		token_ = tokens[0];
		qDebug() << "set token: " << token_;
		rhs_ = nullptr;
		lhs_ = nullptr;
	}
	else {
		// check for enclosing braces first
		if ((tokens[0] == "(") && (tokens.last() == ")"))
			tokens = tokens.mid(1, tokens.length() - 2);
		int pos = least_precedence_operator(tokens);
		token_ = tokens[pos];
		qDebug() << "position least precedence: " << pos;
		qDebug() << "set token: " << token_;
		QVector<QString> lhs = tokens.mid(0, pos);
		qDebug() << "lhs: " << lhs;
		QVector<QString> rhs = tokens.mid(pos + 1, -1);
		qDebug() << "rhs: " << rhs;
		lhs_ = std::make_unique<Expression>(lhs);
		rhs_ = std::make_unique<Expression>(rhs);
	}
}

void Expression::print() const {
	qDebug() << token_;
	if (lhs_ != nullptr) {	// either both are null, or neither
		lhs_->print();
		rhs_->print();
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
	int current_precedence = 1e6;
	int depth = 0;
	std::set<QString> operators{"+", "-", "/", "*", "^"};
	for (int i = 0; i != tokens.length(); i++) {
		if (tokens[i] == "(")
			depth += 10;	// operators within braces have less precedence
		else if (tokens[i] == ")")
			depth -= 10;
		else if (operators.find(tokens[i]) != operators.end()) {
			if (precedence(tokens[i]) + depth < current_precedence) {
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



int main() {
	QString formula1 = "A1 + B1 * C22";
	Tokenizer get_tokens;
	if (get_tokens.tokenize(formula1)) { 
		QVector<QString> tokens = get_tokens.tokenized();
		qDebug() << tokens;
		Expression expression1(tokens);
		expression1.print();
	}

	QString formula2 = "A1*(B1^C2 + 20.5)/ 3";
	if (get_tokens.tokenize(formula2)) { 
		QVector<QString> tokens_2 = get_tokens.tokenized();
		qDebug() << tokens_2;
		Expression expression2(tokens_2);
		expression2.print();
	}

	// QString formula3 = "A1 & 2";
	// if (get_tokens.tokenize(formula3)) {
	// 	QVector<QString> tokens_3 = get_tokens.tokenized();
	// 	qDebug() << tokens_3;
	// }
	// else
	// 	qDebug() << "a non-token was entered";

	// QString formula4 = "A3.";
	// if (get_tokens.tokenize(formula4)) { 
	// 	QVector<QString> tokens = get_tokens.tokenized();
	// 	qDebug() << tokens;
	// }
	// else
	// 	qDebug() << "a non-token was entered";



}