#include <iostream>
#include <string>
#include <list>
using namespace std;


std::list<string> tokens;
std::list<string>::iterator it;
int tokenscount = 0;
void tokenize(string);
void createtoken(string);
int parse(int, int);
int parse_primary();
string peek_token();
string read_token();
int domath(char, int, int);
int conv_char_prec(char oper);

int main()
{
	cout << "Enter an equation with the operators /,*,+,-" << endl;
	string equation;
	int result;
	while (true)
	{
		getline(cin, equation);
		tokenize(equation);
		it = tokens.begin();
		try
		{
			result = parse(parse_primary(), 0);
			cout << result << endl;
		}
		catch (int e)
		{
			cout << "invalid input" << endl;
		}
		tokens.clear();
		tokenscount = 0;
	}
}

void tokenize(string equation)
{
	string cattoken;
	for (size_t i = 0; i < equation.length(); i++)
	{
		if (equation[i] == ' ')
			continue;
		if (isdigit(equation[i]))
		{
			cattoken = equation[i];
			for (i += 1; i < equation.length() && isdigit(equation[i]); i++)
			{
				cattoken.append(1, equation[i]);
			}
			i--;
			createtoken(cattoken);
		}
		if (equation[i] == '+' || equation[i] == '-' || equation[i] == '*' || equation[i] == '/')
		{
			cattoken = equation[i];
			createtoken(cattoken);
		}
	}

}

int parse(int lhs, int min_preclevel)
{
	string lookahead = peek_token();
	while (!isdigit(lookahead[0]) && conv_char_prec(lookahead[0]) >= min_preclevel)
	{
		string op = lookahead;
		++it;
		int rhs = parse_primary();
		lookahead = peek_token();
		while (!isdigit(lookahead[0]) && conv_char_prec(lookahead[0]) >= conv_char_prec(op[0]))
		{
			rhs = parse(rhs, conv_char_prec(lookahead[0]));
			lookahead = peek_token();
		}
		lhs = domath(op[0], lhs, rhs);
	}
	return lhs;
}

void createtoken(string tokenchar)
{

	tokens.push_back(tokenchar);
}

int parse_primary()
{
	string token = read_token();
	if (isdigit(token[0]))
		return stoi(token);
	if (token == "(")
	{
		++it;
		return parse(stoi(*it), 0);
	}
	if (token == ")")
	{
		++it;
	}

}

string peek_token()
{
	if (it != tokens.end())
		return (*it);
	return ";";
}

string read_token()
{
	if (it != tokens.end())
		return (*it++);

}

int conv_char_prec(char oper)
{
	char lookahead = oper;
	int lookaheadprec;
	if (lookahead == '+')
		lookaheadprec = 1;
	if (lookahead == '-')
		lookaheadprec = 1;
	if (lookahead == '*')
		lookaheadprec = 2;
	if (lookahead == '/')
		lookaheadprec = 2;
	if (lookahead == ';')
		lookaheadprec = -1;
	if (lookahead == ')')
		lookaheadprec = -1;
	return lookaheadprec;
}

int domath(char oper, int lhs, int rhs)
{
	int result;
	if (oper == '+')
		result = lhs + rhs;
	if (oper == '-')
		result = lhs - rhs;
	if (oper == '*')
		result = lhs * rhs;
	if (oper == '/')
		result = lhs / rhs;

	return result;
}