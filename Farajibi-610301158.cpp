//mohammadreza isapour 610301158
#include <bits/stdc++.h>


using namespace std;
class Sarafi;
class Currency{
private:
    string Name;
    float Value;
public:
    Currency(string name = " ", float value = 0){
        Name = name;
        Value = value;
    }
    string getCurrencyName(){
        return Name;
    }
    float getCurrencyValue(){
        return Value;
    }
};
class Balance{
private:
    Currency currency;
    float amount;
public:
    Balance(Currency c, int a){
        currency = c;
        amount = a; 
    }
    string getCurrencyName(){
        return currency.getCurrencyName();
    }
    float getBalance(){
        return amount;
    }
    void setBalance(float amount){
        this->amount = amount;
    }
};
class Account{
private:
    string Name;
    vector<Balance> balance;
public:
    Account(string name = "SAFARI"){
        Name = name;
    }
    void setBalance(Currency c, float amount){
        Balance b(c,amount);
        balance.push_back(b);
    }
    void changeBalance(int CurrencyIndex, float amount){
        balance[CurrencyIndex].setBalance(amount);
    }
    string  getName(){
        return Name;
    }
    float getBalance(int CurrencyIndex){
        return balance[CurrencyIndex].getBalance();
    }
};
class Sarafi : public Account{
public:

};
class Wallet{
private:
    vector<Account> accounts;
    vector<Currency> currencys;
    Sarafi sarafi;
    int PrivateKey,PublicKey;
public:
    Wallet(int p, int q){
        makePublicandPrivateKey(p,q);
    }
    void addCurrency(string currency_name, int currency_value){
        Currency currency(currency_name,currency_value);
        currencys.push_back(currency);
    }
    void AddAccount(string name){
        Account account(name);
        accounts.push_back(account);
    }
    void addAccountsBalance(int AccountIndex,int CurrencyIndex, int amount){
        accounts[AccountIndex].setBalance(currencys[CurrencyIndex],amount);
    }
    void addSarafiBalance(int CurrencyIndex,int amount){
        sarafi.setBalance(currencys[CurrencyIndex],amount);
    }
    void getAccounts(){
    }
    void getSarafi(){
    }
    void getCurrencys(){
    }
    void getRecords(){
        for(int i = 0; i < currencys.size(); i++){
            cout << fixed << setprecision(2) << sarafi.getBalance(i) << " ";
        }
        cout << "\n";
        for(int i = 0; i < accounts.size(); i++){
            for(int j = 0; j < currencys.size(); j++){
                cout << fixed << setprecision(2)<<accounts[i].getBalance(j) << " ";
            }
            cout << "\n";
        }
    }
    vector<string> simple_tokenizer(string s);
    int searchAccount(string name);
    int searchCurrency(string name);
    int power(int a,int b, int n); 
    int find_d(int phi_n,int e);
    int relative_prime(int a, int b);
    void makePublicandPrivateKey(int p, int q);
    void WITHDRAW(string AccountName, string CurrencyName,float amount);
    void TRANSFER(string Command, int n);
    void DEPOSIT(string AccountName, string CurrencyName, float amount);
    void EXCHANGE(string AccountName, string CurrencyName1,string CurrencyName2, float amount);
    void TRANSFER(string AccountName1,string AccountName2, string CurrencyName, float amount);
    void DoCommand(string Command,int n);
    string DecryptRSA(int encrypted[100],int NumberOfWords);
};

int main(){
    Wallet wallet(19,101);
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        string CurrencyName;
        int CurrencyValue;
        cin >> CurrencyName >> CurrencyValue;
        wallet.addCurrency(CurrencyName,CurrencyValue);
    }
    string s;
    cin >> s;
    for(int i = 0; i < n; i++){
        int balance;
        cin >> balance;
        wallet.addSarafiBalance(i,balance); 
    }
    int NumberOfUsers;
    cin >> NumberOfUsers;
    for(int i = 0; i < NumberOfUsers; i++){
        string s;
        cin >> s;
        wallet.AddAccount(s);
        int balance;
        for(int j = 0; j < n; j++){
            cin >> balance;
            wallet.addAccountsBalance(i,j,balance);
        }   
           
    }
    int NumberOfCommands;
    cin >> NumberOfCommands;
    for(int i = 0; i < NumberOfCommands; i++){
        int NumberOfWords;
        cin >> NumberOfWords;
        int Words[NumberOfWords]; 
        for(int j = 0; j < NumberOfWords; j++){
            cin >> Words[j];
        }
        string Command = wallet.DecryptRSA(Words,NumberOfWords);
        wallet.DoCommand(Command,NumberOfWords);
    }
    wallet.getRecords();
}

vector <string> Wallet :: simple_tokenizer(string s){
    stringstream ss(s);
    vector <string> Words;
    string word;
    while (ss >> word) {
        Words.push_back(word);
    }
    return Words;

}   
int Wallet :: searchCurrency(string name){
    for(int i = 0; i < currencys.size(); i++){
        if(name == currencys[i].getCurrencyName()){
            return i;
        }
    }
    return -1;
}
int Wallet :: searchAccount(string name){
    for(int i = 0; i < accounts.size(); i++){
        if(name == accounts[i].getName()){
            return i;
        }
    }
    return -1;
}
void Wallet :: WITHDRAW(string AccountName, string CurrencyName,float amount){
    int AccountIndex = searchAccount(AccountName);
    if(AccountIndex == -1){
        cout << "Invalid User: " << AccountName << "\n";
    }
    int CurrencyIndex = searchCurrency(CurrencyName);
    if(accounts[AccountIndex].getBalance(CurrencyIndex) - amount < 0){
        cout << "Insufficient Funds: " << AccountName << "\n";
    }
    else{
        accounts[AccountIndex].changeBalance(CurrencyIndex,accounts[AccountIndex].getBalance(CurrencyIndex) - amount);
        sarafi.changeBalance(CurrencyIndex,sarafi.getBalance(CurrencyIndex)+amount);
    }
}
void Wallet :: DEPOSIT(string AccountName, string CurrencyName,float amount){
    int AccountIndex = searchAccount(AccountName);
    if(AccountIndex == -1){
        cout << "Invalid User: " << AccountName << "\n";
    }
    int CurrencyIndex = searchCurrency(CurrencyName);
    if(sarafi.getBalance(CurrencyIndex) - amount < 0){
        cout << "Insufficient Funds: " << "SARAFI" << "\n";
    }
    else{
        accounts[AccountIndex].changeBalance(CurrencyIndex,accounts[AccountIndex].getBalance(CurrencyIndex) + amount);
        sarafi.changeBalance(CurrencyIndex,sarafi.getBalance(CurrencyIndex)-amount);
    }
}
void Wallet :: EXCHANGE(string AccountName, string CurrencyName1,string CurrencyName2, float amount){
    int AccountIndex = searchAccount(AccountName);
    if(AccountIndex == -1){
        cout << "Invalid User: " << AccountName << "\n";
    }
    int CurrencyIndex1 = searchCurrency(CurrencyName1);
    int CurrencyIndex2 = searchCurrency(CurrencyName2);
    if(amount >= 1000){
        if(accounts[AccountIndex].getBalance(CurrencyIndex1) - (amount + (10.0/(currencys[CurrencyIndex1].getCurrencyValue()))) >= 0){
            if(sarafi.getBalance(CurrencyIndex2) - ((currencys[CurrencyIndex1].getCurrencyValue()) * amount)/currencys[CurrencyIndex2].getCurrencyValue() < 0){
                cout << "Insufficient Funds: SARAFI\n";
                return;
            }
            accounts[AccountIndex].changeBalance(CurrencyIndex1,accounts[AccountIndex].getBalance(CurrencyIndex1) - (amount + (10.0/currencys[CurrencyIndex1].getCurrencyValue())));
            accounts[AccountIndex].changeBalance(CurrencyIndex2,accounts[AccountIndex].getBalance(CurrencyIndex2) + (currencys[CurrencyIndex1].getCurrencyValue() * amount)/currencys[CurrencyIndex2].getCurrencyValue());
            sarafi.changeBalance(CurrencyIndex1,sarafi.getBalance(CurrencyIndex1) + (amount + (10.0/currencys[CurrencyIndex1].getCurrencyValue())));
            sarafi.changeBalance(CurrencyIndex2,sarafi.getBalance(CurrencyIndex2) - (currencys[CurrencyIndex1].getCurrencyValue() * amount)/currencys[CurrencyIndex2].getCurrencyValue());
        }
        else{
            cout << "Insufficient Funds: " << AccountName << "\n";
            return;
        }
    }
    else if(amount < 1000){
        if(accounts[AccountIndex].getBalance(CurrencyIndex1) - (amount + amount/100) >= 0){
            if(sarafi.getBalance(CurrencyIndex2) - ((currencys[CurrencyIndex1].getCurrencyValue()) * amount)/currencys[CurrencyIndex2].getCurrencyValue() < 0){
                cout << "Insufficient Funds: SARAFI\n";
                return;
            }
            accounts[AccountIndex].changeBalance(CurrencyIndex1,accounts[AccountIndex].getBalance(CurrencyIndex1) - (amount + amount/100));
            accounts[AccountIndex].changeBalance(CurrencyIndex2,accounts[AccountIndex].getBalance(CurrencyIndex2) + (currencys[CurrencyIndex1].getCurrencyValue() * amount)/currencys[CurrencyIndex2].getCurrencyValue());
            sarafi.changeBalance(CurrencyIndex1,sarafi.getBalance(CurrencyIndex1) + (amount + amount/100));
            sarafi.changeBalance(CurrencyIndex2,sarafi.getBalance(CurrencyIndex2) - (currencys[CurrencyIndex1].getCurrencyValue() * amount)/currencys[CurrencyIndex2].getCurrencyValue());
        }
        else{
            cout << "Insufficient Funds: " << AccountName << "\n";
            return;
        }
    }
}
void Wallet :: TRANSFER(string AccountName1,string AccountName2, string CurrencyName, float amount){
    int Account1Index = searchAccount(AccountName1);
    if(Account1Index == -1){
        cout << "Invalid User: " << AccountName1 << "\n";
        return; 
    }
    int Account2Index = searchAccount(AccountName2);
    if(Account2Index == -1){
        cout << "Invalid User: " << AccountName2 << "\n"; 
        return;     
    }
    int CurrencyIndex = searchCurrency(CurrencyName); 
    if(amount <= 100){
        if((accounts[Account1Index].getBalance(CurrencyIndex) - (amount + amount/10)) < 0){
            cout << "Insufficient Funds: " << AccountName1 << "\n";
            return;
        }
        accounts[Account1Index].changeBalance(CurrencyIndex,accounts[Account1Index].getBalance(CurrencyIndex) - ((amount + amount/10)));
        accounts[Account2Index].changeBalance(CurrencyIndex,accounts[Account2Index].getBalance(CurrencyIndex)+amount);
        sarafi.changeBalance(CurrencyIndex,sarafi.getBalance(CurrencyIndex) + amount/10);
    }
    else{
        if(accounts[Account1Index].getBalance(CurrencyIndex) - (amount + 10/(currencys[CurrencyIndex].getCurrencyValue())) < 0){
            cout << "Insufficient Funds: " << AccountName1 << "\n";
            return;
        }
        accounts[Account1Index].changeBalance(CurrencyIndex,accounts[Account1Index].getBalance(CurrencyIndex) - ((amount + 10/(currencys[CurrencyIndex].getCurrencyValue()))));
        accounts[Account2Index].changeBalance(CurrencyIndex,accounts[Account2Index].getBalance(CurrencyIndex)+amount);
        sarafi.changeBalance(CurrencyIndex,sarafi.getBalance(CurrencyIndex) + 10/currencys[CurrencyIndex].getCurrencyValue());
    }
}
void Wallet :: DoCommand(string Command, int n){ 
    vector <string> splited = simple_tokenizer(Command);
    if(splited[0] == "WITHDRAW"){
        WITHDRAW(splited[1],splited[2],stoi(splited[3]));
    }    
    else if(splited[0] == "DEPOSIT"){
        DEPOSIT(splited[1],splited[2],stoi(splited[3]));
    }
    else if(splited[0] == "EXCHANGE"){
        EXCHANGE(splited[1],splited[2],splited[3],stoi(splited[4]));
    }
    else if(splited[0] == "TRANSFER"){
        TRANSFER(splited[1],splited[2],splited[3],stoi(splited[4]));
    }
    else{
        cout << "Invalid Command\n";
    }
}
int Wallet :: power(int a,int b, int n){
    int power = 1;
    for(int i = 0; i < b; i++){
        power = (power * (a % n) ) % n;
    }
    return power;
}
void Wallet::makePublicandPrivateKey(int p, int q){
    int n,private_key, public_key;
    n = p * q;
    int phi_n = (p-1) * (q-1);
    PublicKey = relative_prime(1,phi_n);
    PrivateKey = find_d(phi_n,PublicKey);  
}
string Wallet :: DecryptRSA(int encyrpted[100],int NumberOfCommands){
    string temp;
    for(int i = 0; i < NumberOfCommands; i++){
        temp += power(encyrpted[i],PrivateKey, 19 * 101);
    }
    return temp; 
}
int Wallet :: relative_prime(int a, int b){
    for(int i = a + 1; i < b ; i++){
        if(__gcd(i,b) == 1){
            return i;
        }
    }
    return 1;
}
int Wallet :: find_d(int phi_n,int e){
    for(int i = 1; ; i++){
        if(((i * phi_n) + 1)% e == 0){
            return (((i * phi_n) + 1) / e);
        }
    }
}