#include "tokenizer.h"

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