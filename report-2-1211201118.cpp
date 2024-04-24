/*1211201118 　林　優花*/
/*問題文から題意をとらえるのが難しかったです。為替レートをコンストラクタの引数とupdate_ex_rateの引数の両方で値を入れる方法しかわかりませんでした。これ以外の方法で引数を与える回数が一度で済む方法を知りたいです。また、派生クラスのコンストラクタの継承をしようとしたら何度も初期化が何たらというエラーが出て、動かすのに時間がかかりました。*/


#include <iostream>
#include <string>

using namespace std;

class Account {
protected:
  string name; // 名前
  int balance; // 円残高（単位：円）

public:
  // コンストラクタ  
  Account(string _name, int _balance) {
    name = _name;       // 名前を初期化
    balance = _balance; // 円残高を初期化
  }
  // 名前を調べる
  string get_name() {
    return name;
  }
  // 円残高を調べる
  int get_balance() {
    return balance;
  }
  // 預ける
  void deposit(int amnt) {
    balance += amnt;
  }
  // おろす
  void withdraw(int amnt) {
    balance -= amnt;
  }
};

class AccountFx : public Account{ //派生クラス

public: 
//データメンバ
int balance_cent; //米セントの残高
float ex_rate; //為替レート

// コンストラクタの継承
AccountFx(string _name, int _balance, int _balance_cent, float _ex_rate) : Account(_name, _balance){   
   ex_rate = _ex_rate; // 為替レートを初期化
   balance_cent = _balance_cent; //セント残高を初期化
 }

//クラスAccountで定義されたbalanceの日本円の一部を為替レートex_rateでセントに両替
void ex_to_cent(int yen){
  if (yen>balance){
   cout<<"日本円残高が不足しているため、米セントへの両替を中止しました。"<<endl;;
  }
  else{
  int cent = (int)((float)yen / ex_rate);
  balance -= yen;
  balance_cent += cent;
  }    
}
//クラスAccountで定義されたbalanceの米セントを為替レートex_rateで日本円に両替
void ex_to_yen(int cent){
  if (cent>balance_cent){
   cout<<"米セント残高が不足しているため、日本円への両替を中止しました。"<<endl;;
  }
  else{
  int yen = (int)((float)cent * ex_rate);
  balance_cent -= cent;
  balance += yen;
  }
}
//米セント残高をreturnにより返す。
int get_balance_cent(){
  return balance_cent;
}
//為替レートを引数_ex_rateで指定した値に更新
void update_ex_rate(float _ex_rate){
 ex_rate = _ex_rate;
}
};

int main (){  
AccountFx person1("ameria",10000,400,1.50); //(名前、日本円残高、米セント残高、為替レート)
person1.update_ex_rate(1.50); //一セント＝1.50円
person1.ex_to_cent(100); //円→セント
person1.ex_to_yen(100000); //セント→円
cout<<"お名前："<<person1.get_name()<<" 様"<<endl;
cout<<"日本円残高："<<person1.get_balance()<<" 円"<<endl;
cout<<"米セント残高："<<person1.get_balance_cent()<<" セント"<<endl;

cout<<endl;
  
AccountFx person2("alejandoro",500,10000,1.30); //(名前、日本円残高、米セント残高、為替レート)
person2.update_ex_rate(1.30); //一セント＝1.30円
person2.ex_to_cent(100); //円→セント
person2.ex_to_yen(200); //セント→円
cout<<"お名前："<<person2.get_name()<<" 様"<<endl;
cout<<"日本円残高："<<person2.get_balance()<<" 円"<<endl;
cout<<"米セント残高："<<person2.get_balance_cent()<<" セント"<<endl;
return 0;  
}