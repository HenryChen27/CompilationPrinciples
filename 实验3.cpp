#include<bits/stdc++.h>
using namespace std;
struct symbolString{		//符号表 
	string val,type;
	int addr;
	symbolString(){
		addr=-1;
	}
}symbolTable[101010];
int tots;
struct tokenString{			//token串表 
	string type,val;
	symbolString *addr; 
};
tokenString nll;
bool operator <(tokenString a,tokenString b){
	if(a.type==b.type){
		if(a.type=="NUM"||a.type=="ID") return 0;
		else return a.val<b.val;
	}
	return a.type<b.type;
}
bool operator !=(tokenString a,tokenString b){
	if(a.type=="id") return a.type!=b.type;
	return a.type!=b.type||a.val!=b.val;
}
bool operator ==(tokenString a,tokenString b){
	if(a.type=="id") return a.type==b.type;
	return a.type==b.type&&a.val==b.val;
}
vector <tokenString> tokenStream;
bool checkLetter(char c){
	return (c>='a'&&c<='z')||(c>='A'&&c<='Z')||c=='_';
} 
bool checkDigit(char c){
	return (c>='0'&&c<='9');
} 
string op[]={"==",">=" ,"<=","!=","+","-","*","/",">","<","=","(",")",";","'"};
string opToken[]={
		"REL_OP_EQ",   // ==
        "REL_OP_GE",   // >=
        "REL_OP_LE",   // <=
        "REL_OP_NE"    // !=
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
        
};
string keyword[]={"if","else","while","int","float"};
void checkToken(string s){
	if(s=="") return ;
	//根据运算符切割字符串s 
	

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
void printToken(){
	cout<<"\nHere is the token stream:\n";
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

} 
void printSymbol(){
	cout<<"\nHere is the symbol table:\n";
	for(int i=1;i<=tots;i++){
		cout<<&symbolTable[i]<<" "<<symbolTable[i].type<<" "<<symbolTable[i].val<<endl;
	}
	

}
vector <vector <tokenString> > grammar;
tokenString stotoken(string s){
	tokenString ret;
	ret.val=s;
	if(s=="digits"){
		ret.type="NUM";
		return ret;
	}
	if(s=="id"){
		ret.type="ID";
		return ret;
	}
	if(s=="$"){
		ret.type="terminal";
		return nll;
	} 
	int keyLen = sizeof(keyword) / sizeof(keyword[0]);
	 for(int i=0;i<keyLen;i++)
	{
		if(s==keyword[i]) {
    		ret.type="KEYWORD";
    		ret.val=s;		
    		return ret;
		} 
	 } 
	int opLen = sizeof(op) / sizeof(op[0]);
	 for(int i=0;i<opLen;i++)
	{
		if(s==op[i]) {
    		ret.type=opToken[i];
    		ret.val=s;		
    		return ret;
		} 
	 } 
	 ret.type="none-terminal";
	return ret;
}
map<tokenString,set<tokenString>> first;
void get_first(tokenString t,int k){
	if(!first[t].empty()) return;
	int n=grammar.size();
	for(int i=k;i<n;i++){
		if(grammar[i][0]!=t) continue;
		if(grammar[i].size()==1) {
			first[grammar[i][0]].insert(nll);
			continue;
		}
		if(grammar[i][1].type=="none-terminal"){
			int j=1;
			while(j<grammar[i].size()){
				get_first(grammar[i][j],i+1);
				first[grammar[i][0]].insert(first[grammar[i][j]].begin(),first[grammar[i][j]].end());
				if(first[grammar[i][j]].find(nll)!=first[grammar[i][j]].end()){
					j++;
					if(j<grammar[i].size()) first[grammar[i][0]].erase(nll);

				}else break;	
			}
			
		}else{
			first[grammar[i][0]].insert(grammar[i][1]);
		}
	}
	
}
map<tokenString,set<tokenString>> follow;
void get_follow(){
	follow[grammar[0][0]].insert(nll);
	
	for(int i=0;i<grammar.size();i++){
		for(int j=1;j+1<grammar[i].size();j++){
			if(grammar[i][j+1].type=="none-terminal") follow[grammar[i][j]].insert(first[grammar[i][j+1]].begin(),first[grammar[i][j+1]].end());
			else follow[grammar[i][j]].insert(grammar[i][j+1]);
		}
	}
	for(int i=0;i<grammar.size();i++)
	{
		if(grammar[i][grammar[i].size()-1].type=="none-terminal")
			follow[grammar[i][grammar[i].size()-1]].insert(follow[grammar[i][0]].begin(),follow[grammar[i][0]].end());
		if(follow[grammar[i][0]].empty()) follow[grammar[i][0]].insert(nll);
	}
}
void inputGrammar(){
	freopen("grammar.txt","r",stdin);
	int n;
	cin>>n;
	string s;
	getline(cin,s);
	while(n--){
		getline(cin,s);
		stringstream ss(s);
		string word;
		vector <tokenString> curline;
		while (ss >> word) {
        	curline.push_back(stotoken(word));
    	}
    	grammar.push_back(curline);
	}

	for(int i=0;i<grammar.size();i++) get_first(grammar[i][0],0);

	get_follow();
	get_follow();

	
	return;
	for (const auto& line : grammar) {         // 遍历第一维
        for (const auto& token : line) {        // 遍历第二维
            cout << token.val << " ";               // 元素之间输出空格
        }
        cout << endl;  
    }
	
}
vector <tokenString> tokenStack,inputStr;
vector <int> stateStack;
vector<map <tokenString,string>> analysisTable;
vector<map <string,string>> attriStack;


struct lrItem{
	int gnum,idx;
	tokenString tok;
}; 
bool operator<(lrItem x,lrItem y){
	if(x.gnum==y.gnum&&x.idx==y.idx) return x.tok<y.tok;
	if(x.gnum==y.gnum) return x.idx<y.idx;
	return x.gnum<y.gnum;
}
bool operator==(lrItem x,lrItem y){
	return x.gnum==y.gnum&&x.idx==y.idx&&x.tok==y.tok;
}
void extendI(lrItem x,set <lrItem> &I){
	if(x.idx+1>=grammar[x.gnum].size()) return;
	if(grammar[x.gnum][x.idx+1].type=="none-terminal"){
		for(int i=0;i<grammar.size();i++){
			
			if(grammar[i][0]!=grammar[x.gnum][x.idx+1]) continue;
			lrItem u;
			if(x.idx+2>=grammar[x.gnum].size())
			{
				u={i,0,x.tok};
				if(I.insert(u).second) extendI(u,I);
			}
			else if(grammar[x.gnum][x.idx+2].type=="none-terminal"){
				for(auto it=first[grammar[x.gnum][x.idx+2]].begin();it!=first[grammar[x.gnum][x.idx+2]].end();it++){
					u={i,0,(*it)};
					if(I.insert(u).second) extendI(u,I);
				}
			}	
			else{
				u={i,0,grammar[x.gnum][x.idx+2]};
				if(I.insert(u).second) extendI(u,I);
			}
						
		}
	}else return;
}
void printI(set <lrItem> &I){
	for(auto it=I.begin();it !=I.end();it++){
		cout<<grammar[(*it).gnum][0].val<<"->";
		for(int i=1;i<=(*it).idx&&i<grammar[(*it).gnum].size();i++) cout<<grammar[(*it).gnum][i].val<<" ";
		cout<<"·";
		for(int i=(*it).idx+1;i<grammar[(*it).gnum].size();i++) cout<<grammar[(*it).gnum][i].val<<" ";
		cout<<",";
		cout<<(*it).tok.val<<endl;
	}
}
vector <set <lrItem>> state;
vector <map <tokenString,int>> lst;
void nextI(int x,tokenString tok){
	set <lrItem> I0;
	set <lrItem> I=state[x];
	for(auto it=I.begin();it !=I.end();it++){
		if(grammar[(*it).gnum].size()==(*it).idx+1) continue;
		if(grammar[(*it).gnum][(*it).idx+1]!=tok) continue;
		
		I0.insert({(*it).gnum,(*it).idx+1,(*it).tok});
		extendI({(*it).gnum,(*it).idx+1,(*it).tok},I0);
	}
	int to=-1;
	for(int i=0;i<state.size();i++) {
		if(state[i]==I0) {
			to=i;
			lst[x][tok]=to;
			if(tok.type=="none-terminal") analysisTable[x][tok]=to_string(to);
			else analysisTable[x][tok]="s"+to_string(to);
			return;
			break;
		}
	}
	if(to==-1){
		state.push_back(I0);
		to=state.size()-1;
		map<tokenString,int> tmp;
		lst.push_back(tmp);
		map<tokenString,string> pmt;
		analysisTable.push_back(pmt);
	}
	lst[x][tok]=to;
	if(tok.type=="none-terminal") analysisTable[x][tok]=to_string(to);
	else analysisTable[x][tok]="s"+to_string(to);
	I=state[to];
	for(auto it=I.begin();it !=I.end();it++){
		if(grammar[(*it).gnum].size()==(*it).idx+1)
		{
			analysisTable[to][(*it).tok]="r"+to_string((*it).gnum);
			continue;
		}
		if(!lst[to][grammar[(*it).gnum][(*it).idx+1]]) nextI(to,grammar[(*it).gnum][(*it).idx+1]);
	}
}
void getAutomaton(){
	set <lrItem> I;
	I.insert((lrItem){0,0,nll});
	extendI((lrItem){0,0,nll},I);
	state.push_back(I);
	map<tokenString,int> tmp;
	lst.push_back(tmp);
	map<tokenString,string> pmt;
	analysisTable.push_back(pmt);
	for(auto it=I.begin();it !=I.end();it++){
		if(grammar[(*it).gnum].size()==(*it).idx+1) continue;
		nextI(0,grammar[(*it).gnum][(*it).idx+1]);
	}
	return;
	for(int i=0;i<state.size();i++) {
		printf("I%d:\n",i);
		printI(state[i]);
		cout<<endl;
	}
}
void prt(int idx){
	cout<<"状态栈:\n";
	for(int i=0;i<stateStack.size();i++) cout<<stateStack[i]<<" ";
	cout<<"\ntoken栈:\n";
	for(int i=0;i<tokenStack.size();i++) cout<<tokenStack[i].val<<" ";
	cout<<"\n输入:\n";
	for(int i=idx;i<tokenStream.size();i++) cout<<tokenStream[i].val<<" ";
	cout<<"\n\n";
}

void prtA(){
	for (size_t i = 0; i < analysisTable.size(); ++i) {
	    cout << "状态 " << i << ":\n";
	    size_t j = 0;
	    for (const auto& entry : analysisTable[i]) {
	        const tokenString& key = entry.first;
	        const string& value = entry.second;
	
	//        cout << "  Column " << j << ": ";
	        cout << "type = " << key.type << ", val = " << key.val << ", mapped string = " << value << endl;
	        ++j;
	    }
	}
	cout<<endl; 

}

int offset=0;
void enter(string idName,string type,int addr){		//填入符号的信息（类型、地址） 
	for(int i=1;i<=tots;i++){
		if(symbolTable[i].val==idName) {
			symbolTable[i].addr=addr;
			symbolTable[i].type=type;
			return;
		}
	}
}

int newtemp(){		//申请一个新的变量 
	offset+=4;
	return offset-4;
}
int lookup(string idName){		//查询符号表返回地址 
	for(int i=1;i<=tots;i++)
		if(symbolTable[i].val==idName) {
			if(symbolTable[i].addr==-1) {
				if(symbolTable[i].type=="CONST")
					symbolTable[i].addr=newtemp();	
				else return -1;
			}
				
			return symbolTable[i].addr;
		}
			
	return -1;	
}
struct codeBlock{	
	string code;
	int idx;
	codeBlock *nxt,*bfr,*end,*go;
};
codeBlock* newcode(string ss){		//新增代码节点 
	codeBlock* ret=new codeBlock();
	ret->bfr=ret->nxt=ret->go=NULL;
	ret->code=ss;
	ret->end=ret;
	ret->idx=0;
	return ret;
}
codeBlock* cnct(codeBlock *a,codeBlock *b){		//连接连段代码 
	if(!a) return b;
	if(!b) return a;
	a->end->nxt=b;
	b->bfr=a->end;
	a->end=b->end;		
	return a;
}
vector <codeBlock*> codeStack;
vector <map<string,set<codeBlock*>>> nodelist;
set<codeBlock *> makelist(codeBlock * i){
	set<codeBlock *> ret;
	if(i) ret.insert(i);
	return ret;
}
set<codeBlock *> merge(set<codeBlock *> p1,set<codeBlock *> p2){
	for (const auto& i : p2) p1.insert(i);
	return p1;
}
void backpatch(set<codeBlock *> p,codeBlock* i){
	for (const auto& j : p) j->go=i;
}
void r(int x){
	map <string,string> attri;
	codeBlock* retCode=NULL;
	map<string,set<codeBlock*>> newlist;
	string code="";
	if(x==0){	//P->D S 
		retCode=codeStack[codeStack.size()-2];
		retCode=cnct(retCode,codeStack[codeStack.size()-1]);
	}if(x==1){	//D->L id ; D
		enter(tokenStack[tokenStack.size()-3].val,attriStack[attriStack.size()-4]["type"],offset);
		offset+=stoi(attriStack[attriStack.size()-4]["width"]);
		
	}if(x==2){	//D-> 
			
	}if(x==3){	//L->int
		attri["type"]="int";
		attri["width"]="4";
	}if(x==4){	//L->float
		attri["type"]="float";
		attri["width"]="4";	
	}if(x==5){	//S->id = E ;        
		string idName=tokenStack[tokenStack.size()-4].val;
		int p=lookup(idName);
		if(p==-1) {
			cout<<"[error] '"<<idName<<"' was not declare in this scope!\n";
			return;
		}
		code=to_string(p)+"="+attriStack[attriStack.size()-2]["addr"];
		retCode=cnct(codeStack[codeStack.size()-2],newcode(code));
	}if(x==6){	//S->if  ( C )  S 
		retCode=cnct(codeStack[codeStack.size()-3],codeStack[codeStack.size()-1]);
		backpatch(nodelist[nodelist.size()-3]["truelist"],codeStack[codeStack.size()-1]);
		newlist["nextlist"]=merge(nodelist[nodelist.size()-3]["falselist"],nodelist[nodelist.size()-1]["nextlist"]);
	}if(x==7){	//S->if  ( C ) S   else   S
		retCode=cnct(codeStack[codeStack.size()-5],codeStack[codeStack.size()-3]);	
		code="goto_";
		codeBlock* code1=newcode(code);
		retCode=cnct(codeStack[codeStack.size()-5],code1);	
		retCode=cnct(codeStack[codeStack.size()-5],codeStack[codeStack.size()-1]);
		backpatch(nodelist[nodelist.size()-5]["truelist"],codeStack[codeStack.size()-3]);	
		backpatch(nodelist[nodelist.size()-5]["falselist"],codeStack[codeStack.size()-1]);
		newlist["nextlist"]=merge(nodelist[nodelist.size()-1]["nextlist"],nodelist[nodelist.size()-3]["nextlist"]);
		newlist["nextlist"].insert(code1);
	}if(x==8){	//S->while ( C )   S  
		retCode=cnct(codeStack[codeStack.size()-3],codeStack[codeStack.size()-1]);	
		code="goto_";
		codeBlock* code1=newcode(code);
		code1->go=codeStack[codeStack.size()-3];
		retCode=cnct(codeStack[codeStack.size()-3],code1);	
		backpatch(nodelist[nodelist.size()-1]["nextlist"],codeStack[codeStack.size()-3]);
		backpatch(nodelist[nodelist.size()-3]["truelist"],codeStack[codeStack.size()-1]);
		newlist["nextlist"]=nodelist[nodelist.size()-3]["falselist"];
	}if(x==9){	//S->S  S
		retCode=cnct(codeStack[codeStack.size()-2],codeStack[codeStack.size()-1]);
		backpatch(nodelist[nodelist.size()-2]["nextlist"],codeStack[codeStack.size()-1]);
		newlist["nextlist"]=nodelist[nodelist.size()-1]["nextlist"];
	}if(x==10){	//C->E > E
		code="if "+attriStack[attriStack.size()-3]["addr"]+" > "+attriStack[attriStack.size()-1]["addr"]+" goto_";
		codeBlock *code1=newcode(code);
		code="goto_";
		codeBlock *code2=newcode(code);
		retCode=cnct(code1,code2);
		newlist["truelist"]=makelist(code1);
		newlist["falselist"]=makelist(code2);
	}if(x==11){	//C->E < E                  
		code="if "+attriStack[attriStack.size()-3]["addr"]+" < "+attriStack[attriStack.size()-1]["addr"]+" goto_";
		codeBlock *code1=newcode(code);
		code="goto_";
		codeBlock *code2=newcode(code);
		retCode=cnct(code1,code2);
		newlist["truelist"]=makelist(code1);
		newlist["falselist"]=makelist(code2);
	}if(x==12){	//C->E  ==  E                 
		code="if "+attriStack[attriStack.size()-3]["addr"]+" == "+attriStack[attriStack.size()-1]["addr"]+" goto_";
		codeBlock *code1=newcode(code);
		code="goto_";
		codeBlock *code2=newcode(code);
		retCode=cnct(code1,code2);
		newlist["truelist"]=makelist(code1);
		newlist["falselist"]=makelist(code2);
	}if(x==13){	//E->E  +  T      
		attri["addr"]=to_string(newtemp());
		code=attri["addr"]+"="+attriStack[attriStack.size()-3]["addr"]+"+"+attriStack[attriStack.size()-1]["addr"];
		retCode=codeStack[codeStack.size()-3];
		retCode=cnct(retCode,codeStack[codeStack.size()-1]);
		retCode=cnct(retCode,newcode(code));
	}if(x==14){	//E->E  -  T 	
		attri["addr"]=to_string(newtemp());
		code=attri["addr"]+"="+attriStack[attriStack.size()-3]["addr"]+"-"+attriStack[attriStack.size()-1]["addr"];
		retCode=codeStack[codeStack.size()-3];
		retCode=cnct(retCode,codeStack[codeStack.size()-1]);
		retCode=cnct(retCode,newcode(code));
	}if(x==15){	//E->T 				
		attri=attriStack[attriStack.size()-1];
		retCode=codeStack[codeStack.size()-1];		
	}if(x==16){	//T->F 				
		attri=attriStack[attriStack.size()-1];
		retCode=codeStack[codeStack.size()-1];	
	}if(x==17){	//T->T  *  F 			
		attri["addr"]=to_string(newtemp());
		code=attri["addr"]+"="+attriStack[attriStack.size()-3]["addr"]+"*"+attriStack[attriStack.size()-1]["addr"];
		retCode=codeStack[codeStack.size()-3];
		retCode=cnct(retCode,codeStack[codeStack.size()-1]);
		retCode=cnct(retCode,newcode(code));
	}if(x==18){	//T->T  /  F 			
		attri["addr"]=to_string(newtemp());
		code=attri["addr"]+"="+attriStack[attriStack.size()-3]["addr"]+"/"+attriStack[attriStack.size()-1]["addr"];
		retCode=codeStack[codeStack.size()-3];
		retCode=cnct(retCode,codeStack[codeStack.size()-1]);
		retCode=cnct(retCode,newcode(code));
	}if(x==19){	//F->(  E  )			   
		attri=attriStack[attriStack.size()-2];
		retCode=codeStack[codeStack.size()-2];		
	}if(x==20){	//F->id 			   
		string idName=tokenStack[tokenStack.size()-1].val;
		int p=lookup(idName);	
		if(p==-1) {
			cout<<"[error] '"<<idName<<"' was not declare in this scope!\n";
			return;
		}
		attri["addr"]=to_string(p);	
	}if(x==21){	//F->digits 		
		string dName=tokenStack[tokenStack.size()-1].val;
		int p=lookup(dName);	
		if(p==-1) {
			cout<<"[error] '"<<dName<<"' was not declare in this scope!\n";
			return;
		}
		attri["addr"]=to_string(p);
	}
	
	attriStack.erase(attriStack.end() - grammar[x].size()+1, attriStack.end());
	codeStack.erase(codeStack.end() - grammar[x].size()+1, codeStack.end());
	nodelist.erase(nodelist.end() - grammar[x].size()+1, nodelist.end());
	attriStack.push_back(attri);
	codeStack.push_back(retCode);
	nodelist.push_back(newlist);
}
int main(){
	string s;
	cout<<"请输入代码，末尾行以'*/'结束:\n/*\n";
	
	nll.type="terminal";
	nll.val="$";
	stateStack.push_back(0);
//	tokenStack.push_back(nll);
	while(cin>>s){
		if(s=="*/") break;
		checkToken(s);	
	}

	inputGrammar();

	//求解自动机 
	getAutomaton();

	tokenStream.push_back(nll);
	int idx=0,cnt=0;
	prt(idx); 
	while(!stateStack.empty()){	
		cout<<"step "<<(++cnt)<<":\n";
		string opt=analysisTable[stateStack[stateStack.size()-1]][tokenStream[idx]];
		if(opt!="r0") cout<<"执行操作:"<<opt<<endl;
		if(opt==""){
			cout<<"error";
			return 0;
		}
		if(opt[0]=='s'){		//s移入 
			opt.erase(0, 1);
			tokenStack.push_back(tokenStream[idx]);
			idx++;
			stateStack.push_back(stoi(opt));
			map <string,string> attri;
			attriStack.push_back(attri);
			codeStack.push_back(NULL);
			map<string,set<codeBlock*>> lst;
			nodelist.push_back(lst);
		}else{		//r规约 
			opt.erase(0, 1);
			int num=stoi(opt);
			r(num);
			if(num==0){				
				cout<<"acc完成语法分析!\n\n符号表:\n";
				for(int i=1;i<=tots;i++)
					cout<<"<"<<symbolTable[i].val<<","<<symbolTable[i].type<<"> addr="<<symbolTable[i].addr<<"\n";
				cout<<"\n中间代码:\n";
				int addr=100;
				for(codeBlock* i=codeStack[0];i;i=i->nxt) i->idx=addr++;
				for(codeBlock* i=codeStack[0];i;i=i->nxt){
					if(i->go) {
						i->code.pop_back();
						i->code=i->code+" "+to_string(i->go->idx);
					}
					cout<<i->idx<<"  "<<i->code<<endl;
				}				
				break;
			}
			tokenStack.erase(tokenStack.end() - grammar[num].size()+1, tokenStack.end());
			stateStack.erase(stateStack.end() - grammar[num].size()+1, stateStack.end());
			tokenStack.push_back(grammar[num][0]);
			stateStack.push_back(stoi(analysisTable[stateStack.back()][grammar[num][0]]));	
		}
		prt(idx); 
		
	}
	
	 
	return 0;
}
/*
int a;
int b;
int c;
a=2;
b=1;
		  if (a>b)
c=a+b;
else
c=a-b;
*/
/*
int a;
a=a+3;
*/
/*
int a;
int b;
a=2;
b=3+2;
while(a==1)
  if(a>0)
    b=b+1;
  else
    a=a+1;
*/
