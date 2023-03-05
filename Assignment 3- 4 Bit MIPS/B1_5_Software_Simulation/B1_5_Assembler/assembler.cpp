//Here we go again

#include <bits/stdc++.h>
#include <fstream>
using namespace std;
#define ll long long
#define pb push_back
#define mp make_pair
#define ui unsigned int
#define uc unsigned char
#define vs vector<string >
#define psi pair<string , int >
#define msi map<string, int> 
#define pii pair<int, int>
#define f first
#define s second
#define up upper_bound
#define lp lower_bound
#define pq priority_queue
#define pdi pair<ll, pll>
#define inf 1e8
#define minf -1e15
#define pi 3.14159265
#define mod 1000000007
// #include<boost/algorithm/string.hpp>

#define ZERO "0"
#define T0 "1"
#define T1 "2"
#define T2 "3"
#define T3 "4"
#define T4 "5"
#define SP "6"


#define SLL "0"
#define SRL "1"
#define J "2"
#define ADDI "3"
#define ORI "4"
#define SUBI "5"
#define ADD "6"
#define ANDI "7"
#define OR "8"
#define SW "9"
#define BEQ "a"
#define AND "b"
#define SUB "c"
#define NOR "d"
#define BNEQ "e"
#define LW "f"

using namespace std;

msi LineNo;
vector<psi> BranchCalls;
vector<psi>JumpCalls;
//ifstream fp;

static inline void lefttrim(string &str) {
    str.erase(str.begin(), find_if(str.begin(), str.end(), [](uc c) {
        return !isspace(c);
    }));
}

static inline void righttrim(string &str) {
    str.erase(find_if(str.rbegin(), str.rend(), [](uc c) {return !isspace(c);}).base(), str.end());
}
static inline string trim(string &str) {
    lefttrim(str);
    righttrim(str);
    return str;
}
vector<string> String_splitter(const string& str, const char& delim) {
    stringstream ss(str);
    string item;
    vector<string> element;
    while (getline(ss, item, delim)) {
        element.pb(trim(item));
    }

    return element;
}

string determineRegister(string register_name) {    
    if (register_name == "$t0") return T0;
    else if (register_name == "$t1") return T1;
    else if (register_name == "$t2") return T2;
    else if (register_name == "$t3") return T3;
    else if (register_name == "$t4") return T4;
    else if (register_name == "$zero") return ZERO;
    else if (register_name == "$sp") return SP;

    return "ERROR";
}

string toBinary(int n, int length) {
    string r;
    unsigned u = n;

    while(u!=0) 
    {
        if(u%2==0)
            r="0"+r;
        else 
            r="1"+r;
        u/=2;
    }


    if (r.size() < length) 
    {
        while (r.size() != length)
         {
            r = "0" + r;
        }
    } else if (r.size() > length) 
        r = r.substr(r.size() - length, length);
    return r;
}

string toHex(int n, int length) {
    string r = toBinary(n, length);
    //string r1 = toBinary(-10, 4);
    //cout<<r1<<endl;
    string hex = "";
    for (int i = 0; i < r.size(); i += 4) {
        string temp = r.substr(i, 4);
        if (temp == "0000") {
            hex += "0";
        }
        if (temp == "0001") {
            hex += "1";
        } 
        if (temp == "0010") {
            hex += "2";
        }
        if (temp == "0011") {
            hex += "3";
        } 
        if (temp == "0100") {
            hex += "4";
        }
        if (temp == "0101") {
            hex += "5";
        } 
        if (temp == "0110") {
            hex += "6";
        } 
        if (temp == "0111") {
            hex += "7";
        } 
        if (temp == "1000") {
            hex += "8";
        } 
        if (temp == "1001") {
            hex += "9";
        } 
        if (temp == "1010") {
            hex += "a";
        } 
        if (temp == "1011") {
            hex += "b";
        } 
        if (temp == "1100") {
            hex += "c";
        } 
        if (temp == "1101") {
            hex += "d";
        } 
        if (temp == "1110") {
            hex += "e";
        } 
        if (temp == "1111") {
            hex += "f";
        }
    }
    return hex;
}


string checkSp(string line){
    static unsigned linecnt = 0;
    string instruction = "";
    string withoutLabel = "";

    if (line.back() == ':') {
        LineNo[line.substr(0, line.size() - 1)] = linecnt;
        return "ERROR";
    }

    // first look for labels
    vector<string> labelSplitted = String_splitter(line, ':');
    if (labelSplitted.size() > 1) {
        // label found
        withoutLabel = labelSplitted[1];
        // add label to map
        LineNo[labelSplitted[0]] = linecnt;

    } else {
        // no label found
        withoutLabel = line;
    }

    // split with space
    string opcode = String_splitter(withoutLabel, ' ')[0];
    return opcode;
}

string getSp(string line){
    static unsigned linecnt = 0;
    string instruction = "";
    string instruction1 = "";
    string withoutLabel = "";

    if (line.back() == ':') {
        LineNo[line.substr(0, line.size() - 1)] = linecnt;
        return "ERROR";
    }

    // first look for labels
    vector<string> labelSplitted = String_splitter(line, ':');
    if (labelSplitted.size() > 1) {
        // label found
        withoutLabel = labelSplitted[1];
        // add label to map
        instruction+=labelSplitted[0];
        instruction+=":";
        LineNo[labelSplitted[0]] = linecnt;

    } else {
        // no label found
        withoutLabel = line;
    }


    // split with space
    string opcode = String_splitter(withoutLabel, ' ')[0];
    string withoutComment = String_splitter(withoutLabel, '/')[0];
    vector<string> commaSplitted = String_splitter(withoutComment.substr(opcode.size(), withoutComment.size()-opcode.size()), ',');
    if (opcode == "push") instruction1 += SW;
    else if (opcode == "pop") instruction1 += LW;

     if(commaSplitted.size()<=1 && (instruction1 == SW)){ // push 
            instruction+="subi $sp, $sp, 1\n";
            instruction += "sw ";
            instruction += commaSplitted[0];
            instruction += ",";
            instruction+= "0($sp)";  

        }
        else if(commaSplitted.size()<=1 && (instruction1 == LW)){ // pop 
            //instruction="";
            instruction+= "lw ";  //addi $sp, $sp, 1
            instruction += commaSplitted[0];
            instruction += ",";
            instruction+= "0($sp)\n"; 
            instruction+="addi $sp, $sp, 1";
            
        }
        return instruction;

}

string convert(string line) {
    static unsigned linecnt = 0;
    string instruction = "";
    string withoutLabel = "";

    if (line.back() == ':') {
        LineNo[line.substr(0, line.size() - 1)] = linecnt;
        return "ERROR";
    }

    // first look for labels
    vector<string> labelSplitted = String_splitter(line, ':');
    if (labelSplitted.size() > 1) {
        // label found
        withoutLabel = labelSplitted[1];
        // add label to map
        //cout << labelSplitted[0] << " " << linecnt << endl;
        LineNo[labelSplitted[0]] = linecnt;

    } else {
        // no label found
        withoutLabel = line;
    }

    // split with space
    string opcode = String_splitter(withoutLabel, ' ')[0];
    string withoutComment = String_splitter(withoutLabel, '/')[0];
    vector<string> commaSplitted = String_splitter(withoutComment.substr(opcode.size(), withoutComment.size()-opcode.size()), ',');
    if (opcode == "sll") instruction += SLL;
    else if (opcode == "srl") instruction += SRL;
    else  if (opcode == "j") instruction += J;
    else if (opcode == "addi") instruction += ADDI;
    else if (opcode == "ori") instruction += ORI;
    else if (opcode == "subi") instruction += SUBI;
    else if (opcode == "add") instruction += ADD;
    else if (opcode == "andi") instruction += ANDI;
    else if (opcode == "or") instruction += OR;
    else if (opcode == "sw") instruction += SW;
    else if (opcode == "beq") instruction += BEQ;
    else if (opcode == "and") instruction += AND;
    else if (opcode == "sub") instruction += SUB;
    else if (opcode == "nor") instruction += NOR;
    else if (opcode == "bneq") instruction += BNEQ;
    else if (opcode == "lw") instruction += LW;
    else if (opcode == "push") instruction += SW;
    else if (opcode == "pop") instruction += LW;
    else return "ERROR";


       // S format : sll, srl
    if((instruction == SLL)||(instruction == SRL)){
        // rs
        instruction += determineRegister(commaSplitted[1]);     

        // rd
        instruction += determineRegister(commaSplitted[0]);

        // shamt
        instruction += toHex(stoi(commaSplitted[2]), 4);

        linecnt++;
        return instruction;
    }
    // R format : sub, or, and, add, nor
    else if ((instruction == SUB)||(instruction == OR)||(instruction == AND)||(instruction == ADD)||(instruction == NOR)) {
        instruction += determineRegister(commaSplitted[1]);
        instruction += determineRegister(commaSplitted[2]);
        instruction += determineRegister(commaSplitted[0]);
        linecnt++;
        return instruction;
    }
    // I format constant : ori, addi, andi, subi
    else if((instruction == ORI)||(instruction == ADDI)||(instruction == ANDI)||(instruction == SUBI)){
        // rs
        instruction += determineRegister(commaSplitted[1]);       

        // rd
        instruction += determineRegister(commaSplitted[0]);             

        // constant
        instruction += toHex(stoi(commaSplitted[2]), 4); 
        linecnt++;
        return instruction;
    }

    // I format control : beq, bneq
    else if((instruction == BEQ)||(instruction == BNEQ)){
        instruction += determineRegister(commaSplitted[0]);
        instruction += determineRegister(commaSplitted[1]); 
        // offset
        //cout<<instruction<<endl;
        BranchCalls.pb(mp(commaSplitted[2], linecnt));
        cout<<commaSplitted[2]<<" "<<linecnt<<endl;
        //cout<<instruction<<endl;
        
        linecnt++;
        return instruction;
    }

    // I format memory : sw, lw
    else if((instruction == SW)||(instruction == LW)){
            vector<string> parenthesisSplitted1 = String_splitter(commaSplitted[1], '(');
            vector<string> parenthesisSplitted2 = String_splitter(parenthesisSplitted1[1], ')');
            instruction += determineRegister(parenthesisSplitted2[0]);
            instruction += determineRegister(commaSplitted[0]);
            instruction += toHex(stoi(parenthesisSplitted1[0]), 4);

        
        linecnt++;
        return instruction;
    }
    // J format : j
    else if((instruction == J)){
        // address
        //cout<<commaSplitted[0]<<" jump "<<linecnt<<endl;
        JumpCalls.pb(mp(commaSplitted[0], linecnt));   
        linecnt++;
        return instruction;
    }

    cout << "ERROR " << linecnt << " " << line << endl;
    return "ERROR";
}

int main (int argc , char *argv[]) {
    ifstream fp("assembly.txt");
    ofstream fout("intermediate.txt");
    vector<string> machineCodes;
    //fp.open(argv[1]);
    string line;
    fout<<"addi $sp, $zero, 15"<<endl;
    while (getline(fp, line)) {
        if (line.size() == 0) continue;
        if(checkSp(line)=="push"){
            string stack = getSp(line);
            fout<<stack<<endl;
            //fout<<"subi $sp, $sp, 1"<<endl;
            
        }
        else if(checkSp(line)=="pop"){
            string stack = getSp(line);
            //fout<<"addi $sp, $sp, 1"<<endl;
            cout<<stack<<endl;
            fout<<stack<<endl;
            
        }
        else{
            fout<<line<<endl;
        }




        // cout << line << endl;
    }
    fout.close();
    fp.close();

    ifstream fp1("intermediate.txt");
    while (getline(fp1, line)) {
        if (line.size() == 0) continue;

        string machineCode = convert(line);
        if (machineCode != "ERROR") {
            machineCodes.pb(machineCode);
        }

        // cout << line << endl;
    }

    // iterate over both labelCalls
    for (int i=0;i<BranchCalls.size();i++) {
        string label = BranchCalls[i].f;
        int line_cnt = BranchCalls[i].s;
        int offset = LineNo[label] - (line_cnt + 1);
        cout<<label<<" "<<line_cnt<<" "<<offset<<endl;
        // convert to hex
        string hex = toHex(offset, 4);
        cout<<hex<<endl;
        // add to machineCodes
        machineCodes[line_cnt] += hex;
    }
    for (int i=0;i<JumpCalls.size();i++) {
        string label = JumpCalls[i].f;
        int lineNo = JumpCalls[i].s;
        int offset = LineNo[label];
        // convert to hex
        string hex = toHex(offset, 8);
        // add to machineCodes
        machineCodes[lineNo] += hex + "0";
    }

    ofstream output_file("machine.txt");
    output_file << "v2.0 raw" << endl;
    //output_file<< "306F"<< endl;  //addi $sp, $zero, 15
    for (int i=0;i<machineCodes.size();i++) {
        output_file <<machineCodes[i]<< endl;
    }
    fp1.close();
    output_file.close();

return 0;
    
}
