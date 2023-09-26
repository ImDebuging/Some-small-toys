#include <iostream>
#include <string>
#include<Windows.h>

std::string TrueToComplement(std::string binary);
std::string AddBinary(std::string a, std::string b);

std::string DecimalToBinary(int decimal) {		//��һ��ʮ��������ת��Ϊ��������ʽ��string��������λ�����Ϊ8λ��������λ������ܱ�ʾ127��
	std::string binary;
	if (decimal > 0){
		int i = 0;
		do {
			binary.insert(0, std::to_string(decimal % 2));
			decimal /= 2;
			i++;
		} while (decimal);
		while (i < 8){
			binary.insert(binary.begin(), '0');
			i++;
		}
	}
	else{
		decimal = -1 * decimal;
		int i = 0;
		do {
			binary.insert(0, std::to_string(decimal % 2));
			decimal /= 2;
			i++;
		} while (decimal);
		while (i < 7){
			binary.insert(binary.begin(), '0');
			i++;
		}
		binary.insert(binary.begin(), '1');
		binary = TrueToComplement(binary);
	}
	return binary;
}

std::string TrueToComplement(std::string binary)
{
	if (binary[0] == '0'){	//�����Ĳ������������
		return binary;
	}
	for (int i = 1; i < binary.size(); ++i){	//����������ķ���
		if (binary[i] == '0'){
			binary[i] = '1';
		}
		else{
			binary[i] = '0';
		}
	}
	//������ڷ���+1
	binary = AddBinary(binary,"00000001");
	return binary;
}

std::string AddBinary(std::string a, std::string b) {
	int i = a.size() - 1;
	int j = b.size() - 1;
	std::string result;
	bool flag = false;
	for (; i > 0 && j > 0; --i, --j)
	{
		if (flag == false){
			if (a[i] == '1'&&b[j] == '1'){
				result.insert(result.begin(), '0');
				flag = true;
			}
			else if (a[i] == '0'&&b[j] == '0'){
				result.insert(result.begin(), '0');
				flag = false;
			}
			else{
				result.insert(result.begin(), '1');
				flag = false;
			}
		}
		else if (flag == true){
			if (a[i] == '1'&&b[j] == '1'){
				result.insert(result.begin(), '1');
				flag = true;
			}
			else if (a[i] == '0'&&b[j] == '0'){
				result.insert(result.begin(), '1');
				flag = false;
			}
			else{
				result.insert(result.begin(), '0');
				flag = true;
			}
		}
	}
	return result;
}

int main() {
	std::string a=DecimalToBinary(3);
	std::string b = DecimalToBinary(-8);
	std::string sum = AddBinary(a,b);
	sum = TrueToComplement(sum);
	std::cout << sum;
	system("pause");

	return 0;
}
