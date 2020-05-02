#include <QVector>
#include <QString>
#include <QChar>
#include <set>

// Converts a string into a vector of tokens. Valid tokens
// are defined as private members. The same tokenizer can
// be used for several strings.
class Tokenizer {
public:
	Tokenizer();
	// tokenizes a string. Returns false if the string 
	// contains invalid tokens. 
	bool tokenize(const QString & formula);
	// returns the vector with tokens.
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