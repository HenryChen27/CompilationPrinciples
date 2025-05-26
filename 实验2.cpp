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
//	return;
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
int main(){
	string s;
	cout<<"请输入代码，末尾行以'*/'结束:\n/*\n";
	
	nll.type="terminal";
	nll.val="$";
	stateStack.push_back(0);
	while(cin>>s){
		if(s=="*/") break;
		checkToken(s);	
	}

	inputGrammar();
	
//	输出first或者follow集 
//	for(int i=0;i<grammar.size();i++) {
//		cout<<grammar[i][0].val<<"->{";
//		for (auto it = follow[grammar[i][0]].begin(); it != follow[grammar[i][0]].end(); ++it) {
//        cout << (*it).val << " ";
//        }
//        cout<<"}\n";
//	}

	//求解自动机 
	getAutomaton();


	tokenStream.push_back(nll);
	int idx=0,cnt=0;
	prt(idx); 
	while(!stateStack.empty()){	
		cout<<"step "<<(++cnt)<<":\n";
		string opt=analysisTable[stateStack[stateStack.size()-1]][tokenStream[idx]];
		if(opt=="r0") {
			cout<<"acc 完成语法分析";
			break;	//完成语法分析 
		}
		cout<<"执行操作:"<<opt<<endl;
		if(opt==""){
			cout<<"error";
			return 0;
		}
		if(opt[0]=='s'){		//s移入 
			opt.erase(0, 1);
			tokenStack.push_back(tokenStream[idx]);
			idx++;
			stateStack.push_back(stoi(opt));
		}else{		//r规约 
			opt.erase(0, 1);
			int num=stoi(opt);
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
