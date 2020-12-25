#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <set>

using namespace std;

void error_brackets() { cout << "Проверьте расстановку скобок."; } // error
void error_chur() { cout << "Некорректная запись выражения. Проверьте и попробуйте ещё раз."; }
int resalt(string a, string b, string oper) {
	bool A, B;
	if (a == "1") { A = true; }
	else { A = false; }
	if (b == "1") { B = true; }
	else { B = false; }
	bool res;
	if (oper == "|") { res = A || B; }
	else if (oper == "&") { res = A && B; }
	else if (oper == "~") { res = (!A || B) && (A || !B); }
	else if (oper == "->") { res = !A || B; }
	if (res) { return 1; }
	else { return 0; }
}
void podschet(string a, string b, string oper, vector <string> & Temp_main, int k) {
	int buf;
	buf = resalt(a, oper, b);//результат логической операции в цифре
	auto iter = Temp_main.cbegin();
	Temp_main[k + 1] = to_string(buf);
	Temp_main.erase(iter + k + 2);
	Temp_main.erase(iter + k);
}

struct struct_var
{
	char letter;
	short int znachenie;
};

int main() {
	string A;
	setlocale(LC_CTYPE, "rus");
	cout << "Введите ваше логическае выражение." << endl;
	cout << "Переменными могут служить лишь латинские буквы.";
	cout << "Пробелы не влияют на результат. Регистр учитывается.";
	cout << "Символы логических операций:" << endl;
	cout << "|, &, _, ~, ->" << endl;
	getline(cin, A); cout << endl;

	//проверка соответствия введённых символов дозволенному списку
	int space = 0;
	for (int i = 0, l = A.size(); i < l; i++) {
		char buf = A[i];
		if (space < 0) { error_brackets(); return 0; }
		if ((buf <= 'Z' && buf >= 'A' || buf <= 'z' && buf >= 'a') || buf == '&' || buf == '_' || buf == '~' || buf == '>' || buf == '-' || buf == ')' || buf == '(' || buf == '|') {
			if (buf == '(') { space++; }
			if (buf == ')') { space--; }
			continue;
		}
		else if (buf == ' ') { auto iter = A.cbegin(); A.erase(i, 1); i--; l--; }
		else { error_chur(); return 0; }
	}
	if (space) { error_brackets(); return 0; } //проверка адекватности расстановок скобок
	if (A.size() == 1) {
		if ((A[0] <= 'Z' && A[0] >= 'A') || (A[0] <= 'z' && A[0] >= 'a')) { cout << A << endl;  cout << "0" << " " << "0" << endl << "1" << " " << "1"; return 0; }
		else { error_chur(); return 0; }
	}
	
	//for (auto now : A) { cout << now << " "; } //проверка

	multiset <string> operators; //список операторов, которые могут присутствовать
	operators = { "&", "_", "->", "~", "|" };
	set <char> variables; //список имеющихся в выражении переменных
	vector <char> Main_temp; //символы выражения, пока не понятно зачем
	vector <string> Main; //вектор, состоящий из операторов, переменных и скобок
	//заполнение предыдущих массивов и множеств
	for (int i = 0, l = A.size(); i < l; i++) {
		char buf = A[i];
		Main.push_back(""); Main[i] += buf;
		Main_temp.push_back(' '); Main_temp[i] = buf; //?
		if (buf <= 'Z' && buf >= 'A' || buf <= 'z' && buf >= 'a') { variables.insert(A[i]); }
	}
	//for (auto now : Main) { cout << now << " "; } //проверка

	//проверка неспаренности символов операторов и переменных + спаривание символов - и > в один оператор
	for (int i = 0, l = Main.size() - 1; i < l ; i++) {
		string temp1 = "", temp2 = "";
		temp1 += Main[i];
		temp2 += Main[i + 1];
		if (temp1 == temp2 && temp1 == "_") { // если встретились 2 в ряд стоящих минуса
			auto iter = Main.cbegin();
			Main.erase(iter + i+1);
			Main.erase(iter + i);
			if (Main.size() > 1) { temp1 += Main[i]; temp2 += Main[i + 1]; }
			l -= 2; i--; continue;
		}
		if (variables.find(Main_temp[i]) != variables.end() && variables.find(Main_temp[i + 1]) != variables.end()) { error_chur(); return 0; }
		if (operators.find(temp1) != operators.end() && operators.find(temp2) != operators.end() && temp1 != "_") { error_chur(); return 0; }
		if (temp1 == "-" && temp2 == ">") {
			//cout << "sdf";
			auto iter = Main.cbegin();
			Main[i] += temp2; Main.erase(iter + i + 1); l--;
			//i++;
		}
		//cout << Main[i];
	}
	//for (auto now : Main) { cout << now << " "; } //проверка

	struct_var variables_real[50]; //массив структур переменных
	for (int i = 0, n = variables.size(); i < 50; i++) {
		if (i < n) { for (auto now : variables) { variables_real[i].letter = now; variables_real[i].znachenie = 0; i++; } i--;  }
		else { variables_real[i].letter = '+'; variables_real[i].znachenie = 0; }
	}
	
	vector <string> Temp_main; //массив с подставленными значениями переменных
	int v = variables.size();

	//блок перебора вариантов значения переменных и вычисление значения выражения
	for (auto now : variables) { cout << now << " "; } cout << "res" << endl;
	for (int i = 0, n = pow(2, v); i < n; i++) {
		int S = 0;
		for (int j = 0; j < v; j++) { //вывод имён переменных .. временно
			//cout << variables_real[i].letter << " ";
			S += variables_real[j].znachenie*pow(2, v - j - 1); //счетчик, через который осуществляется перебор вариантов значений переменных
			cout << variables_real[j].znachenie << " "; //вывод значений переменных
		}

		//основной блок обработки выражения Main
		for (auto now : Main) { //перебор всех членов выражения
			if ((now[0] <= 'Z' && now[0] >= 'A') || (now[0] <= 'z' && now[0] >= 'a')) {
				for (int k = 0; k < v; k++) { //поиск подходящей переменной из массива структур
					string P = ""; P += variables_real[k].letter;
					if (P == now) { //запись в массив значения переменной вместо буквы
						if (variables_real[k].znachenie) { Temp_main.push_back("1"); }
						else { Temp_main.push_back("0"); }
						break;
					}
				}
			}
			else { Temp_main.push_back(now); }
		}

		//for (auto now : Temp_main) { cout << now << " "; }
		while (Temp_main.size() != 1) {
			auto iter = Temp_main.cbegin();
			if (Temp_main.size() < 3) { // если не возможно делать главный цикл
				if (Temp_main.size() == 2) { //унарный минус
					if (Temp_main[1] == "1") { Temp_main[0] = "0"; }//перемена числа
					else { Temp_main[0] = "1"; }		      //на противоположное
					Temp_main.erase(iter + 1);
				}
				else { cout << Temp_main[0] << endl;  cout << "0" << " " << "0" << endl << "1" << " " << "1"; return 0; }
			}

			for (int k = 0, l = Temp_main.size(); k < l - 2; k++) {
				string temp1, temp2, temp3; //три ближние знака или символа
				temp1 = Temp_main[k]; temp2 = Temp_main[k + 1]; temp3 = Temp_main[k + 2];
				if (temp1 == "_" && (temp2 == "0" || temp2 == "1")) { //унарный минус
					while (temp1 == "_") {
						if (temp2 == "1") { Temp_main[k] = "0"; }//перемена числа
						else { Temp_main[k] = "1"; }		      //на противоположное
						Temp_main.erase(iter + k+1);
						if (k) { k--; }
						temp1 = Temp_main[k]; temp2 = Temp_main[k + 1];
						if (Temp_main.size() == 2) { break; }
					}
					if (Temp_main.size() > 2) { temp3 = Temp_main[k + 2]; }
				}
				if (temp3 == ")" && temp1 == "(") { Temp_main.erase(iter + k + 2); Temp_main.erase(iter + k); break;  } //если знак в скобках
				if (operators.find(temp2) != operators.end()) { //если средний символ - оператор
					if (temp1 != ")" && temp3 != "(") {
						if (temp2 == "&") {
							if ((temp1 == "0" || temp1 == "1") && (temp3 == "0" || temp3 == "1")) { //если крайние - числа
								podschet(temp1, temp2, temp3, Temp_main, k);
								break;
							}
						}
						else if (temp2 == "|") {
							if (k == 0) {
								if (k + 3 == Temp_main.size()) { //если осталось 3 символа
									podschet(temp1, temp2, temp3, Temp_main, k);
									break;
								}
								else {
									if (Temp_main[k + 3] == "&") { continue; } //если справа умножение
									else { //если нет умножения справа
										podschet(temp1, temp2, temp3, Temp_main, k);
										break;
									}
								}
							}
							else { //если слева не начало
								if (k + 3 == Temp_main.size()) { //если справа конец
									if (Temp_main[k - 1] == "&") { continue; } //если слева умножение
									else { //если нет умножения справа
										podschet(temp1, temp2, temp3, Temp_main, k);
										break;
									}
								}
								else { //если справа и слева не ограниченно
									if (Temp_main[k - 1] == "&" || Temp_main[k + 3] == "&") { continue; } //если слева или справа умножение
									else { //если нет умножения справа или слева
										podschet(temp1, temp2, temp3, Temp_main, k);
										break;
									}
								}
							}
							break;
						}
						else {
							if (k == 0) {
								if (k + 3 == Temp_main.size()) { //если осталось 3 символа
									podschet(temp1, temp2, temp3, Temp_main, k);
									break;
								}
								else {
									if (Temp_main[k + 3] == "&" || Temp_main[k + 3] == "|") { continue; } //если справа умножение
									else { //если нет умножения справа
										podschet(temp1, temp2, temp3, Temp_main, k);
										break;
									}
								}
							}
							else { //если слева не начало
								if (k + 3 == Temp_main.size()) { //если справа конец
									if (Temp_main[k - 1] == "&" || Temp_main[k + 3] == "|") { continue; } //если слева умножение
									else { //если нет умножения справа
										podschet(temp1, temp2, temp3, Temp_main, k);
										break;
									}
								}
								else { //если справа и слева не ограниченно
									if (Temp_main[k - 1] == "&" || Temp_main[k + 3] == "&" || Temp_main[k - 1] == "|" || Temp_main[k + 3] == "|") { continue; } //если слева или справа умножение
									else { //если нет умножения справа или слева
										podschet(temp1, temp2, temp3, Temp_main, k);
										break;
									}
								}
							}
							break;
						}
					}
					else { continue; }
				}
			}
			//for (auto now : Temp_main) { cout << now << " "; }
		}
		cout << Temp_main[0] << " ";
		Temp_main.erase(Temp_main.cbegin());

		//создание следующей перестановки 1 и 0
		S++;
		//cout << S;
		for (int i = 0; i < v; i++) {
			variables_real[i].znachenie = S / pow(2, v - i - 1);
			S -= variables_real[i].znachenie * pow(2, v - i - 1);
		}
		cout << endl;
	}

	return 0;
}