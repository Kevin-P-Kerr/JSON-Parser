// A JSON Parser
// 0 is true, 1 is false

#include <stdio.h>
#define MAXLINE 1000

char Look;

void GetChar(void) {
	Look = getchar();
}

int IsAlph(void) {
	if ((Look <= 'z') && (Look >= 'a') ||((Look <= 'Z') && (Look >= 'A')))
		return 0;
	else
		return 1;
}

int IsNum(void) {
	if ((Look <= '9') && (Look >='0'))
		return 0;
	else
		return 1;
}

int IsWhite(void) {
	if ((Look == ' ') || ((Look == '\t') || (Look == '\n'))) 
		return 0;
	else
		return 1;
}


int IsAlphNum(void) {
	if ((IsAlph() == 0) || (IsNum() == 0)) 
		return 0;
	else 
		return 1;
}

void SkipWhite(void) {
	while (IsWhite() == 0) 
		GetChar();
}


void GetNum(void) {
	int i = 0;
	char line[MAXLINE];

	while (IsNum() == 0) {  
		line[i] = Look;
		i = ++i;
		GetChar();
} 
	line[i] = '\0';
	printf("%s", line);
	SkipWhite();
}

void GetString(void) {
	int i = 0;
	char line[MAXLINE];
	while (IsAlphNum() == 0) {
		line[i] = Look;
		i = ++i;
		GetChar(); 
}
	line[i + 1] = '\0';
	printf("%s", line);
	SkipWhite();
}

void Match(char c) {
	if (Look!=c) {
		printf("Expected %c", c);	
}
	else {
		GetChar();
		SkipWhite();
}
}	

/////////////////////////////////////////

// Parse and Note a String
void String(void) {
	printf("<STRING\n>");
	GetString();
	printf("</STRING>\n");
}
// Parse and Identify a Fraction
void Frac(void) {
	Match('.');
	printf("<FRACTION\n>");
	GetNum();
	printf("</FRACTION>\n");
}

// Parse and Identiry an Exponent
void E(void) {
	GetChar();
	if (Look == '-') {
		Match('-');
		printf("<NEGATIVE EXP>\n");
		GetNum();
		printf("</NEGATIVE EXP>\n</NUMBER>\n");
}
	else {
		printf("<EXP>\n");
		GetNum();
		printf("<EXP>\n</NUMBER>\n");
}
}

// Parse and Identify a Number/
void Number(void) {
	printf("<NUMBER>\n");
	GetNum();
	if (Look == '.')
		Frac();
        if ((Look == 'E') || (Look == 'e'))
		E();
	else 
		printf("</NUMBER>\n");
}
// Parse and Note Elements
void Elements(void) {
	printf("<ELEMENT\n");
	Value();
	printf("</ELEMENT\n");
	while (Look == ',') {
		Match(','); 
		printf("<ELEMENT>\n");
		Value();
		printf("</ELEMENT>\n");
 }
}
// Parse and Note an Array
void Array(void) {
	printf("<ARRAY>\n");
	Match('[');
	Elements();
	Match(']');
	printf("</ARRAY>\n");
}
	

// Identify What the value is
void Ident(void) {
	if (IsAlph() == 0) 
		String();
	else if (IsNum() == 0)
		Number();
	else if (Look =='{')
		Object();
	else if (Look == '[')
		Array();
}

// Parse and Note A Value
void Value(void) {
	printf("<VALUE>\n");
	Ident();
	printf("</VALUE>\n");
}
	
	

// Parse and Note a Pair
void Pair(void) {
	printf("<PAIR>\n");
	String();
	Match(':');
	Value();
	printf("</PAIR>\n");
	printf("</MEMBER>\n");
	if (Look!='}')
		Member();
}
// Parse and Note a Member
void Member(void) {
	printf("<MEMBER>\n");
	Pair();

}


// Parse and Note an Object
void Object(void) {
	Match('{');
	if (Look == '}')
		printf("NULL OBJECT");
	else {
		printf("<OBJECT>\n");
		Member();
		printf("</OBJECT>\n");
}
}

//initalize
void Init(void) {
	GetChar();
	SkipWhite();
}

//main
main() {
	Init();
	Object();
	printf("\nFinished");
}

