/*
 * @Author: SeaFever
 * @Date: 2020.4.7
 * @Function: 快速批量将B站 BV 号转换成 AV 号
 * @Parameter: 
 * 		- [-d/D dirPath] 
 * 			+ dirPath 为批量从文件读取 BV 号的文件路径
 * 		- BVxxxxxxxxxx/bvxxxxxxxxxx/xxxxxxxxxx
 * 			+ 可同时传递多个 BV 号做参数
 * 			+ 但是必须声明在 -d/D 参数前，否则无效
 * 		- v/V/H/h
 * 			+ 查看相关信息
 */

#include <iostream>
#include <map>
#include <string>
#include <fstream>

using namespace std;

// 非法字符检测
void illegal_Character_Interception(string detection_Object)
{
	for (int i = 0; i < detection_Object.size(); i++) {
		if (detection_Object[i] < 48) { throw 6; }
		else if (detection_Object[i] > 57 && detection_Object[i] < 65) { throw 6; }
		else if (detection_Object[i] > 90 && detection_Object[i] < 97) { throw 6; }
		else if (detection_Object[i] > 122) { throw 6; }
		// 检测是否存在 0、I、O和l 字符
		else if (48 == detection_Object[i] || 73 == detection_Object[i] || 79 == detection_Object[i] || 108 == detection_Object[i]) { throw 7; }
		// 不存在异常
		else { break; }
	}
}

// 重写 pow 函数，解决精度问题(可能是由 pow 函数数据存储方式引起)
// 不支持开根号运算
unsigned long long pow(const int num, const int index)
{
	unsigned long long res;
	(index <= 0)? (res = 1):(res = num); 
	for (int i=1;i< index;i++){
		res *= num;
	}
	return res;
}

/*
 * @Author: SeaFever
 * @Date: 2020.4.7
 * @Function: 将 BV 号转为 AV 号
 * @Parameter: 
 * 		- const string bv_arr BV号
 * 		- 返回值 AV号
 */
unsigned long long Translate(const string bv_arr)
{
	// 解码表(BV -> AV)
	map<string ,string> translator;
	translator["1"]="13";
	translator["2"]="12";
	translator["3"]="46";
	translator["4"]="31";
	translator["5"]="43";
	translator["6"]="18";
	translator["7"]="40";
	translator["8"]="28";
	translator["9"]="5";
	translator["A"]="54";
	translator["B"]="20";
	translator["C"]="15";
	translator["D"]="8";
	translator["E"]="39";
	translator["F"]="57";
	translator["G"]="45";
	translator["H"]="36";
	translator["J"]="38";
	translator["K"]="51";
	translator["L"]="42";
	translator["M"]="49";
	translator["N"]="52";
	translator["P"]="53";
	translator["Q"]="7";
	translator["R"]="4";
	translator["S"]="9";
	translator["T"]="50";
	translator["U"]="10";
	translator["V"]="44";
	translator["W"]="34";
	translator["X"]="6";
	translator["Y"]="25";
	translator["Z"]="1";
	translator["a"]="26";
	translator["b"]="29";
	translator["c"]="56";
	translator["d"]="3";
	translator["e"]="24";
	translator["f"]="0";
	translator["g"]="47";
	translator["h"]="27";
	translator["i"]="22";
	translator["j"]="41";
	translator["k"]="16";
	translator["m"]="11";
	translator["n"]="37";
	translator["o"]="2";
	translator["p"]="35";
	translator["q"]="21";
	translator["r"]="17";
	translator["s"]="33";
	translator["t"]="30";
	translator["u"]="48";
	translator["v"]="23";
	translator["w"]="55";
	translator["x"]="32";
	translator["y"]="14";
	translator["z"]="19";
	map<string ,string >::iterator l_it;
	
	// 必须使用 unsigned long long 类型，不然会数据溢出
	unsigned long long a_dec = 0;

	for(int i=0;i<bv_arr.size(); i++){
		// 翻译
		// 1. 将BV号每个字符按照 map 表翻译为一个对应的十进制数据
		string single_str = bv_arr.substr(i, 1);
		
		try {
			illegal_Character_Interception(single_str);
		} catch (int e) {
			(6 == e) && (cout << "\nERROR6:\n\t出现非法字符 " << single_str << " !\n\t请检查后再次尝试!" << endl);
			(7 == e) && (cout << "\nERROR7:\n\t检测到非法字符 " << single_str << " !\n\t请检查 BV 号是否正确" << endl);
			return 0;
		}
		
		string temp = translator.find(single_str)->second;
		string::size_type sz; 
		int temp_int = stoi(temp,&sz);
		// 2. 将每个的十进制数据按如下规则计算，得到一个巨大的十进制数
		switch (i) {
			case 0:a_dec += temp_int * pow(58, 6);break;
			case 1:a_dec += temp_int * pow(58, 2);break;
			case 2:a_dec += temp_int * pow(58, 4);break;
			case 3:a_dec += temp_int * pow(58, 8);break;
			case 4:a_dec += temp_int * pow(58, 5);break;
			case 5:a_dec += temp_int * pow(58, 9);break;
			case 6:a_dec += temp_int * pow(58, 3);break;
			case 7:a_dec += temp_int * pow(58, 7);break;
			case 8:a_dec += temp_int * pow(58, 1);break;
			case 9:a_dec += temp_int * pow(58, 0);break;
			default:throw 3;// 抛出“ERROR3:运算错误”异常
		}
	}
	// 3. 将这个十进制数先减去 100618342136696320，再与 177451812 异或即可得到AV号
	a_dec -= 100618342136696320;
	a_dec ^= 177451812;
	// 抛出“ERROR4:不存在 AV 号”异常
	if (a_dec < 0 || a_dec >= 100000000) throw 4;
	
	return a_dec;
}

// 输出 av 号信息到屏幕
void send_av(const string bv_arr)
{
	cout << "\n请拿好你的AV号:" << endl;
	try {
		("bv" == bv_arr.substr(0,2) || "BV" == bv_arr.substr(0,2)) ? cout << "av" << Translate(bv_arr.substr(2)) << endl : cout << "av" << Translate(bv_arr) << endl;
	} catch (int e) {
		(3 == e) && cout << "\nERROR3:\n\t转换发生错误!\n\t请检查 BV 号是否正确后再次尝试!\n\t错误 BV 号: " << bv_arr << endl;
		(4 == e) && cout << "\nERROR4:\n\t不存在该 AV 号!\n\t请检查 BV号是否正确后再次尝试!\n\t错误 BV 号: " << bv_arr << endl;
	}
}

// 输出 av 号和与之对应的 bv 号(之间用“---”连接)到 AVList.txt 文件
void output_av(const string bv_arr, ofstream &target_file)
{
	// 只是为了输出美观，使每个BV号前均有 “BV” 字样
	string out_str; 
	
	("bv" == bv_arr.substr(0,2) || "BV" == bv_arr.substr(0,2)) ? out_str = bv_arr.substr(2) : out_str = bv_arr ;
	try {
		target_file << "av" << Translate(out_str) << "---" << "BV" << out_str << endl;
	} catch (int e) {
		(3 == e) && target_file << "->NULL" << "---ERROR3---" << "BV" << out_str << endl;
		(4 == e) && target_file << "->NULL" << "---ERROR4---" << "BV" << out_str << endl;
	}
}

void footPrint()
{
	system("echo [36m");
	cout << "+=================================================+\n"
		<< "|-@version:1.0.0                                  |\n"
		<< "|-@Author:SeaFever                                |\n"
		<< "|-@Help:https://www.cnblogs.com/seafever/BTA.html |\n"
		<< "|-@GitHub:https://github.com/Derek5-SeaFever/BTA  |\n"
		<< "+=================================================+"
		<< endl;
	system("echo [37m");
}

int main(int argc, char *argv[])
{
	string bv_arr;
	int i;
	try {
		for (i = 1; i < argc; i++) {
			if ('-' == argv[i][0] && ('d' == argv[i][1]) || 'D' == argv[i][1]) {
				// 输入文件流
				ifstream get_bv_file;
				get_bv_file.open(argv[i+1]);
				if (!get_bv_file) { cout << "ERROR1:\n\t文件不存在!" << endl;break; } // 抛出“ERROR1:未能读取 BV 号文件”异常
				// 输出文件流
				ofstream output_file;
				output_file.open(".\\AV_List.txt");
				if (!output_file) { cout << "ERROR2:\n\t无法创建 AVList.txt 文件!" << endl;break; } // 抛出“ERROR2:未能创建 AV 号文件”异常
				
				while (!get_bv_file.eof()) {
					get_bv_file >> bv_arr;
					output_av(bv_arr, output_file);
				}

				get_bv_file.close();
				output_file.close();
				break;
			} else if ('-' == argv[i][0] && ('v' == argv[i][1] || 'V' == argv[i][1]) || 'h' == argv[i][1] || 'H' == argv[i][1]) {
				footPrint();
			} else {
				send_av(argv[i]);
			}
		}
	} catch (const invalid_argument e) {
		cerr << "\nERROR5:\n\t无效参数: " << argv[i] << endl;
	}
	
	return 0;
}
