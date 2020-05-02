#include <QVector>
#include <QString>
#include <QChar>
#include <QDebug>
#include <set>

class Tokenizer {
public:
	Tokenizer();
	bool scan(const QString & formula);
	QVector<QString> tokenized() const;
private:
	std::set<QChar> capital_type_ {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
		'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 
		'U', 'V', 'W', 'X', 'Y', 'X'
	};
	std::set<QChar> number_type_ {
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'.'
	};
	std::set<QChar> punctuation_type_ {
		'(', ')' 
	};
	std::set<QChar> operation_type_ {
		'*', '/', '-', '+', '^'
	};
	QVector<QString> tokenized_form_;
};

Tokenizer::Tokenizer(){}

bool Tokenizer::scan(const QString & formula) {
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

int main() {
	QString formula1 = "A1 + B1 * C22";
	Tokenizer get_tokens;
	if (get_tokens.scan(formula1)) { 
		QVector<QString> tokens = get_tokens.tokenized();
		qDebug() << tokens;
	}

	QString formula2 = "A1*(B1^C2 + 20.5)/ 3";
	if (get_tokens.scan(formula2)) { 
		QVector<QString> tokens_2 = get_tokens.tokenized();
		qDebug() << tokens_2;
	}

	QString formula3 = "A1 & 2";
	if (get_tokens.scan(formula3)) {
		QVector<QString> tokens_3 = get_tokens.tokenized();
		qDebug() << tokens_3;
	}
	else
		qDebug() << "a non-token was entered";

	QString formula4 = "A3.";
	if (get_tokens.scan(formula4)) { 
		QVector<QString> tokens = get_tokens.tokenized();
		qDebug() << tokens;
	}
	else
		qDebug() << "a non-token was entered";

}