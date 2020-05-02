#include "tokenizer.h"
#include <memory>

// Constructs an expression tree from a qvector of 
// tokens. Assumes that the formula is syntactically 
// correct. 
class Expression {
public:
	Expression(QVector tokens);
private:
	QString token_;
	std::unique_ptr<Expression> lhs_;
	std::unique_ptr<Expression> rhs_;
};