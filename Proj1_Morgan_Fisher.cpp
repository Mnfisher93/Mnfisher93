// Morgan Fisher
// CPL Project One
#include <iostream>
#include <string>

using namespace std;

FILE *file;
char nextChar = 0;
string lexeme = "", nextToken = "", charClass = "";
int com = 0;

void getnewChar(){

  nextChar = getc(file);

  if( nextChar != EOF){ //(nextChar = getc(file)) != EOF
    if(isalpha(nextChar)){
      charClass = "letter";
      
    }else if(isdigit(nextChar)){
      charClass = "digit";
    }else charClass = "unknown";
  }else{
    nextChar = 0; 
    charClass = "EOF";
  }
}


void getNonBlank(){
  //if (nextChar == '\n') cout << "new line\n";
  while(isspace(nextChar)) getnewChar();
  
}
/*pppp*/

void lookup(string l){
  
  if(l == "read"){
    nextToken = "read";
  }else if(l == "write"){
    nextToken = "write";
  }else if(l == "*"){
    com ^= 1;
    nextToken = "times";
  }else if(l == "+"){
    nextToken = "plus";
  }else if(l == "-"){
    nextToken = "minus";
  }else if(l == "/"){
    com = 1;
    nextToken = "div";
  }else if(l == ")"){
    nextToken = "rparen";
  }else if(l == "("){
    nextToken = "lparen";
  }else if(l == ":="){
    nextToken = "assign";
  }else if(l == "."){
    nextToken = "digit";
  }
  lexeme = "";
}

void addChar(){
  if (nextChar != 0)
    lexeme += nextChar; 
}

string scan(){
  
  getNonBlank();
  
  if(charClass == "letter"){
    
    addChar();
    getnewChar();
    while(charClass == "letter"){
      addChar();
      getnewChar();
    }
    
    lookup(lexeme);
    
  }else if(charClass == "digit"){
    addChar();
    getnewChar();
    while(charClass == "digit"){
      addChar();
      getnewChar();
    }
    nextToken = "digit";
  }else if(charClass == "EOF"){
    nextToken = "EOF";
    addChar();
  }else {
    addChar();
    getnewChar();
    if(nextChar == '='){
      addChar();
      getnewChar();
    }
    if(nextToken == "div" && nextChar == '*'){
      while(nextChar != '/') getnewChar();
    }
    
    lookup(lexeme);
  }
  return nextToken;
}


int main(int argc, char* argv[]){
  // if(argc != 2){
  //   cout << "Missing input file.";
  // }else{
    file = fopen("input.txt", "r");
    string tokens[100];
    int t = 0;
    
    while(charClass != "EOF"){
      string tk = scan();
   
      if(tk != ""){
        tokens[t++] = tk;
      }
      
    }

    cout << "Tokens: (";
    for(int i = 0; i< t; i++){
      cout << tokens[i] << ',';
    }
    cout << ")" << endl;

    cout << "Final tok is: " << lexeme << endl; 
  

  return 0;
}