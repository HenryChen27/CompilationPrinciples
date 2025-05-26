#include<bits/stdc++.h>
using namespace std;
struct symbolString{		//符号表 
	string val,type;
}symbolTable[101010];
int tots;
struct tokenString{			//token串表 
	string type,val;
	symbolString *addr; 
};

vector <tokenString> tokenStream;
bool checkLetter(char c){
	return (c>='a'&&c<='z')||(c>='A'&&c<='Z')||c=='_';
} 
bool checkDigit(char c){
	return (c>='0'&&c<='9');
} 
void checkToken(string s){
	if(s=="") return ;
	//根据运算符切割字符串s 
	string op[]={"+","-","*","/",">","<","=","(",")",";","'","==",">=" ,"<=","!="};
	string opToken[]={
        "ADD_OP",      // +
        "SUB_OP",      // -
        "MUL_OP",      // *
        "DIV_OP",      // /
        "REL_OP_GT",   // >
        "REL_OP_LT",   // <
        "ASSIGN_OP",   // =
        "LEFT_PAREN",  // (
        "RIGHT_PAREN", // )
        "SEMICOLON",   // ;
        "QUOTE",       // '
        "REL_OP_EQ",   // ==
        "REL_OP_GE",   // >=
        "REL_OP_LE",   // <=
        "REL_OP_NE"    // !=
    };
    int opLen = sizeof(op) / sizeof(op[0]);
    
    for(int i=0;s[i];i++){
    	for(int j=0;j<opLen;j++){
    		if(i+op[j].length()-1>=s.length()) continue;
    		if(s.substr(i,op[j].length())==op[j]){
    			checkToken(s.substr(0,i));
    			tokenString x;
    			x.type=opToken[j];
    			x.val=op[j];
    			x.addr=NULL;
    			tokenStream.push_back(x);
				checkToken(s.substr(i+op[j].length(),s.length()-i-op[j].length()));
    			return;
			}
		}
    	
	}


	 //关键字 
	 string keyword[]={"if","else","while","int","float"};
	 int keyLen = sizeof(keyword) / sizeof(keyword[0]);
	 for(int i=0;i<keyLen;i++)
	{
		if(s==keyword[i]) {
			tokenString x;
    		x.type="KEYWORD";
    		x.val=s;
    		x.addr=NULL;
    		tokenStream.push_back(x);
    		return;
		} 
	 } 
	 

	 //变量
	 bool isId=checkLetter(s[0]);
	 for(int i=0;s[i];i++) if(!checkLetter(s[i])&&!checkDigit(s[i])){
	 	isId=false;
	 	break;
	 }
	 if(isId) {
	 		symbolString *p=NULL;
	 		for(int i=1;i<=tots;i++){
	 			if(symbolTable[i].val==s&&symbolTable[i].type=="IDENTIFIER"){
	 				p=symbolTable+i;
	 				break;
				 }
			 }
			 if(!p){
			 	symbolTable[++tots].val=s;
    			symbolTable[tots].type="IDENTIFIER";
    			p=symbolTable+tots;
			 }
    		
	 	
			tokenString x;
    		x.type="ID";
    		x.val=s;
    		x.addr=p;
    		tokenStream.push_back(x);
    		return;
		} 
	 
	 //数字
	 bool isDigit=true;
	 for(int i=0;s[i];i++) if(!checkDigit(s[i])){
	 	isDigit=false;
	 	break;
	 }
	 if(isDigit){
	 		symbolString *p=NULL;
	 		for(int i=1;i<=tots;i++){
	 			if(symbolTable[i].val==s&&symbolTable[i].type=="CONST"){
	 				p=symbolTable+i;
	 				break;
				 }
			 }
			 if(!p){
			 	symbolTable[++tots].val=s;
    			symbolTable[tots].type="CONST";
    			p=symbolTable+tots;
			 }
    		
			tokenString x;
    		x.type="NUM";
    		x.val=s;
    		x.addr=symbolTable+tots;
    		tokenStream.push_back(x);
    		return;
		} 
	  
	cout<<"[Error] '"<<s<<"' was not invalid in this scope!\n";
	 return ;
} 
int main(){
	string s;
	cout<<"请输入代码，末尾行以'*/'结束:\n/*\n";
	while(cin>>s){
		if(s=="*/") break;
		checkToken(s);	
	}
	cout<<"\ntoken stream:\n";
	for(int i=0;i<tokenStream.size();i++) {
		
		cout<<"<";
		if(tokenStream[i].type=="KEYWORD"){
			for(int j=0;tokenStream[i].val[j];j++) putchar(tokenStream[i].val[j]+'A'-'a');
		} 
		else cout<<tokenStream[i].type;
		
		cout<<",";
		if(tokenStream[i].addr){
			cout<<tokenStream[i].addr;
		}else cout<<"_";
		cout<<">\n";
		
	}
	cout<<"\nsymbol table:\n";
	for(int i=1;i<=tots;i++){
		cout<<&symbolTable[i]<<" "<<symbolTable[i].type<<" "<<symbolTable[i].val<<endl;
	}
	
	freopen("token stream.txt","w",stdout);
	for(int i=0;i<tokenStream.size();i++) {
		
		cout<<"<";
		if(tokenStream[i].type=="KEYWORD"){
			for(int j=0;tokenStream[i].val[j];j++) putchar(tokenStream[i].val[j]+'A'-'a');
		} 
		else cout<<tokenStream[i].type;
		
		cout<<",";
		if(tokenStream[i].addr){
			cout<<tokenStream[i].addr;
		}else cout<<"_";
		cout<<">\n";
		
	}
	freopen("symbol table.txt","w",stdout);
	for(int i=1;i<=tots;i++){
		cout<<&symbolTable[i]<<" "<<symbolTable[i].type<<" "<<symbolTable[i].val<<endl;
	}
	return 0;
}

