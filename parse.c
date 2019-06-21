#include<stdio.h>
#include<string.h>
#include<stdbool.h>
typedef char* S;
//bool (*form)(S),(*formWrap)(S),(*cons)(S),(*prop)(S),(*unar)(S),(*bina)(S),(*left)(S),(*righ)(S),(*unao)(S),(*bino)(S);
bool unar(S s[]);
bool bina(S s[]);
bool cons(S s[]);
bool formWrap(S s[]);
bool form(S s[]);
bool unao(S s[]);
bool righ(S s[]);
bool left(S s[]);
bool prop(S s[]);

void skipWhitespace(S s[]);
const char *NOT="not";
const char *OR = "or";
const char *AND="and";
const char *IMP="imp";
const char *IFF="iff";
const int MAX_LENGTH = 100;

bool match(S s[],const char *token);
void skipWhitespace(char *s[]){
	while(*s[0]==' '||*s[0]=='\n'||*s[0]=='\t'){*s=*s+1;}
}
bool match(char *s[],const char *token){
	if(strncmp(*s,token,strlen(token))==0){
		*s=*s+strlen(token);
		return true;
	}
	return false;
}
bool form(S s[]){
	//identify Formula
	char *orig=*s;
	skipWhitespace(s);
	if(cons(s)||prop(s)||unar(s)||bina(s))
		return true;
	*s=orig;
	return false;
}
bool unar(S s[]){
	char *orig=*s;
	skipWhitespace(s);
	if(!left(s)){
		*s=orig;
		return false;
	}
        if(!unao(s)){ 
                *s=orig;
                return false;
        }
        if(!form(s)){ 
                *s=orig;
                return false;
        }
        if(!righ(s)){ 
                *s=orig;
                return false;
        }
	return true;
}
bool bina(S s[]){
        char *orig=*s;
        skipWhitespace(s);
        if(!left(s)){
                *s=orig;
                return false;
        }
        if(!unao(s)){ 
                *s=orig;
                return false;
        }
        if(!form(s)){ 
                *s=orig;
                return false;
        }
        if(!righ(s)){ 
                *s=orig;
                return false;
        }
        return true;
}
bool left(S s[]){
	char *orig=*s;
	skipWhitespace(s);
	if(match(s,"("))
		return true;
	*s = orig;
	return false;
}
bool righ(S s[]){
        char *orig=*s;
        skipWhitespace(s);
        if(match(s,")"))
                return true;
        *s = orig;
        return false;
}
bool cons(S s[]){
        char *orig=*s;
        skipWhitespace(s);
        if(match(s,"T")||match(s,"F"))
                return true;
        *s = orig;
        return false;
}
bool prop(S s[]){
	char *orig = *s;
	skipWhitespace(s);
	char p[MAX_LENGTH];
	int numCharsRead;
	if (sscanf(*s,"%[a-z0-9]%n",&p,&numCharsRead)==1){
		*s=*s+numCharsRead;
		return true;
	}
	*s=orig;
	return false;
}
bool unao(S s[]){
	char *orig=*s;
	skipWhitespace(s);
	if(match(s,NOT))
		return true;
	*s=orig;
	return false;
}
bool bino(S s[]){
	char *orig = *s;
	skipWhitespace(s);
	if(match(s,OR)||match(s,AND)||match(s,IMP)||match(s,IFF))
		return true;
	*s=orig;
	return false;
}
bool formWrap(S s[]){
	char *orig=*s;
	if(form(s)){
		skipWhitespace(s);
		if(*s[0]=='\0')
			return true;
		else
			*s=orig;
			return false;
	}
	return false;
}

void main(void){
        bool expression(S s);
        const int MAX_LINE_SIZE=1000;
        char input[MAX_LINE_SIZE];
        char *copy;
        printf("Enter propositional logic 1/line");
        while (fgets(input,MAX_LINE_SIZE,stdin)!= NULL){
                copy = input;
                if(formWrap(&copy))
                        printf(">Is WFF\n");
                else
                        printf(">Is not WFF\n");
        }

}




