#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <set>

using namespace std;

void error_brackets() { cout << "��������� ����������� ������."; } // error
void error_chur() { cout << "������������ ������ ���������. ��������� � ���������� ��� ���."; }
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
	buf = resalt(a, oper, b);//��������� ���������� �������� � �����
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
	cout << "������� ���� ���������� ���������." << endl;
	cout << "����������� ����� ������� ���� ��������� �����.";
	cout << "������� �� ������ �� ���������. ������� �����������.";
	cout << "������� ���������� ��������:" << endl;
	cout << "|, &, _, ~, ->" << endl;
	getline(cin, A); cout << endl;

	//�������� ������������ �������� �������� ������������ ������
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
	if (space) { error_brackets(); return 0; } //�������� ������������ ����������� ������
	if (A.size() == 1) {
		if ((A[0] <= 'Z' && A[0] >= 'A') || (A[0] <= 'z' && A[0] >= 'a')) { cout << A << endl;  cout << "0" << " " << "0" << endl << "1" << " " << "1"; return 0; }
		else { error_chur(); return 0; }
	}
	
	//for (auto now : A) { cout << now << " "; } //��������

	multiset <string> operators; //������ ����������, ������� ����� ��������������
	operators = { "&", "_", "->", "~", "|" };
	set <char> variables; //������ ��������� � ��������� ����������
	vector <char> Main_temp; //������� ���������, ���� �� ������� �����
	vector <string> Main; //������, ��������� �� ����������, ���������� � ������
	//���������� ���������� �������� � ��������
	for (int i = 0, l = A.size(); i < l; i++) {
		char buf = A[i];
		Main.push_back(""); Main[i] += buf;
		Main_temp.push_back(' '); Main_temp[i] = buf; //?
		if (buf <= 'Z' && buf >= 'A' || buf <= 'z' && buf >= 'a') { variables.insert(A[i]); }
	}
	//for (auto now : Main) { cout << now << " "; } //��������

	//�������� ������������� �������� ���������� � ���������� + ���������� �������� - � > � ���� ��������
	for (int i = 0, l = Main.size() - 1; i < l ; i++) {
		string temp1 = "", temp2 = "";
		temp1 += Main[i];
		temp2 += Main[i + 1];
		if (temp1 == temp2 && temp1 == "_") { // ���� ����������� 2 � ��� ������� ������
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
	//for (auto now : Main) { cout << now << " "; } //��������

	struct_var variables_real[50]; //������ �������� ����������
	for (int i = 0, n = variables.size(); i < 50; i++) {
		if (i < n) { for (auto now : variables) { variables_real[i].letter = now; variables_real[i].znachenie = 0; i++; } i--;  }
		else { variables_real[i].letter = '+'; variables_real[i].znachenie = 0; }
	}
	
	vector <string> Temp_main; //������ � �������������� ���������� ����������
	int v = variables.size();

	//���� �������� ��������� �������� ���������� � ���������� �������� ���������
	for (auto now : variables) { cout << now << " "; } cout << "res" << endl;
	for (int i = 0, n = pow(2, v); i < n; i++) {
		int S = 0;
		for (int j = 0; j < v; j++) { //����� ��� ���������� .. ��������
			//cout << variables_real[i].letter << " ";
			S += variables_real[j].znachenie*pow(2, v - j - 1); //�������, ����� ������� �������������� ������� ��������� �������� ����������
			cout << variables_real[j].znachenie << " "; //����� �������� ����������
		}

		//�������� ���� ��������� ��������� Main
		for (auto now : Main) { //������� ���� ������ ���������
			if ((now[0] <= 'Z' && now[0] >= 'A') || (now[0] <= 'z' && now[0] >= 'a')) {
				for (int k = 0; k < v; k++) { //����� ���������� ���������� �� ������� ��������
					string P = ""; P += variables_real[k].letter;
					if (P == now) { //������ � ������ �������� ���������� ������ �����
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
			if (Temp_main.size() < 3) { // ���� �� �������� ������ ������� ����
				if (Temp_main.size() == 2) { //������� �����
					if (Temp_main[1] == "1") { Temp_main[0] = "0"; }//�������� �����
					else { Temp_main[0] = "1"; }		      //�� ���������������
					Temp_main.erase(iter + 1);
				}
				else { cout << Temp_main[0] << endl;  cout << "0" << " " << "0" << endl << "1" << " " << "1"; return 0; }
			}

			for (int k = 0, l = Temp_main.size(); k < l - 2; k++) {
				string temp1, temp2, temp3; //��� ������� ����� ��� �������
				temp1 = Temp_main[k]; temp2 = Temp_main[k + 1]; temp3 = Temp_main[k + 2];
				if (temp1 == "_" && (temp2 == "0" || temp2 == "1")) { //������� �����
					while (temp1 == "_") {
						if (temp2 == "1") { Temp_main[k] = "0"; }//�������� �����
						else { Temp_main[k] = "1"; }		      //�� ���������������
						Temp_main.erase(iter + k+1);
						if (k) { k--; }
						temp1 = Temp_main[k]; temp2 = Temp_main[k + 1];
						if (Temp_main.size() == 2) { break; }
					}
					if (Temp_main.size() > 2) { temp3 = Temp_main[k + 2]; }
				}
				if (temp3 == ")" && temp1 == "(") { Temp_main.erase(iter + k + 2); Temp_main.erase(iter + k); break;  } //���� ���� � �������
				if (operators.find(temp2) != operators.end()) { //���� ������� ������ - ��������
					if (temp1 != ")" && temp3 != "(") {
						if (temp2 == "&") {
							if ((temp1 == "0" || temp1 == "1") && (temp3 == "0" || temp3 == "1")) { //���� ������� - �����
								podschet(temp1, temp2, temp3, Temp_main, k);
								break;
							}
						}
						else if (temp2 == "|") {
							if (k == 0) {
								if (k + 3 == Temp_main.size()) { //���� �������� 3 �������
									podschet(temp1, temp2, temp3, Temp_main, k);
									break;
								}
								else {
									if (Temp_main[k + 3] == "&") { continue; } //���� ������ ���������
									else { //���� ��� ��������� ������
										podschet(temp1, temp2, temp3, Temp_main, k);
										break;
									}
								}
							}
							else { //���� ����� �� ������
								if (k + 3 == Temp_main.size()) { //���� ������ �����
									if (Temp_main[k - 1] == "&") { continue; } //���� ����� ���������
									else { //���� ��� ��������� ������
										podschet(temp1, temp2, temp3, Temp_main, k);
										break;
									}
								}
								else { //���� ������ � ����� �� �����������
									if (Temp_main[k - 1] == "&" || Temp_main[k + 3] == "&") { continue; } //���� ����� ��� ������ ���������
									else { //���� ��� ��������� ������ ��� �����
										podschet(temp1, temp2, temp3, Temp_main, k);
										break;
									}
								}
							}
							break;
						}
						else {
							if (k == 0) {
								if (k + 3 == Temp_main.size()) { //���� �������� 3 �������
									podschet(temp1, temp2, temp3, Temp_main, k);
									break;
								}
								else {
									if (Temp_main[k + 3] == "&" || Temp_main[k + 3] == "|") { continue; } //���� ������ ���������
									else { //���� ��� ��������� ������
										podschet(temp1, temp2, temp3, Temp_main, k);
										break;
									}
								}
							}
							else { //���� ����� �� ������
								if (k + 3 == Temp_main.size()) { //���� ������ �����
									if (Temp_main[k - 1] == "&" || Temp_main[k + 3] == "|") { continue; } //���� ����� ���������
									else { //���� ��� ��������� ������
										podschet(temp1, temp2, temp3, Temp_main, k);
										break;
									}
								}
								else { //���� ������ � ����� �� �����������
									if (Temp_main[k - 1] == "&" || Temp_main[k + 3] == "&" || Temp_main[k - 1] == "|" || Temp_main[k + 3] == "|") { continue; } //���� ����� ��� ������ ���������
									else { //���� ��� ��������� ������ ��� �����
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

		//�������� ��������� ������������ 1 � 0
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