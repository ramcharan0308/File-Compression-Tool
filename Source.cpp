#include<iostream>
#include<fstream>
#include<vector>
#include"Header.h"
#include<string>
#include<stdio.h> 

using namespace std;


int main()
{
	/*ofstream fout3("input.txt");
	string inp;
	cout << "Enter input: " << endl;
	cin >> inp;
	for (int i = 0; i < inp.size(); i++)
		fout3 << inp[i];
	fout3.close();*/

	hash_table_input<key_val> table;
	vector<char> file_data;
	ifstream fin("input.txt");            // opening input file and taking data from it
	if (!fin.fail())                    // check if the file is opened
	{
		cout << "Input: " << endl;
		while (!fin.eof())               // taking input from the file
		{
			char buff[1000];
			fin.getline(buff, 1000);
			for (int i = 0; buff[i] != '\0'; i++)
			{
				file_data.push_back(buff[i]);   // saving all characters for encoding
				key_val obj;
				obj.character = buff[i];
				obj.freq = 1;
				table.insert(obj);            // mapping data in hash table

				cout << buff[i];
			}

		}
		fin.close();          // closing file after using it
	}
	else
		cout << "File not opened !" << endl;
	//table.print();      // ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	vector<binary_tree<key_val>> v;
	
	int i = 0;									  // making n binary trees & inserting them in vector
	for (int j = 0; j < table.h_table.size(); j++)
	{
		i = 1;
		dlist<key_val>::diterator diter;
		diter = table.h_table[j].begin();
		for (; diter != table.h_table[i].end(); ++diter)
		{
			if (diter.getCurr() != nullptr)
			{
				key_val temp = *diter;
				binary_tree<key_val> bt;
				bt.insert(temp);
				v.push_back(bt);
				i++;
			}
		}
	}

	heap<binary_tree<key_val>> h;

	for (int i = 0; i < v.size(); i++)          // printting binary trees
	{
		// v[i].print_binary_tree();
	}
	for (int i = 0; i < v.size(); i++)        // making heap of binary trees
	{
		h.insert(v[i]);
	}
	// h.printheap();
	tnode<key_val> * t = h.huff_man();          //  applying huffman encoding algorithm
	
	//h.print_after_huffman(t);

	vector<int> arr;                 // for storing generated code
	hash_table_code<key_val> table_for_code;

	h.encode(table_for_code,arr,t);          // generating codes from tree
	//table_for_code.print();       // ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
	ofstream fout;
	int bit_count = 0;    // calculate no of bits of last byte
	fout.open("compressed.txt");      // compression
	if (!fout.fail())                     // storing data in output file
	{
		int counts = 0, bit = 0;
		char output = 0;
		cout << endl << endl << "After Compression: " << endl;
		for (int i = 0; i < file_data.size(); i++)
		{
			key_code file_char = table_for_code.serach(file_data[i]);
			if (file_char.character != '\0')
			{
				for (int j = 0; j < file_char.code.size(); j++)
				{
					if (counts == 8)
					{
						fout << output;
						cout << output;
						counts = 0;
						output = 0;
						bit = 0;
					}
					counts++;
					bit_count++;
					output = output << 1;
					bit = file_char.code[j];
					if (bit != 0)
						output = output | 1;
				}
			}
		}
		for (int i = 0; i < 8 - counts; i++)
		{
			output = output << 1;
		}
		fout << output;       // writing last byte 
		cout << output;
		fout.close();        // closing file
		//cout << "compressed sussessfully" << endl;
	}
	else
		cout << "File for Compression not opened !" << endl;

	//vector<int> dcode;
	//vector<char> out;
	//int bit = 128;				  // 1000000   
	//int count2 = 0,j=0;
	//char buff[1000], dcode_char;
	//char in;

	//ifstream fin1;
	//fin1.open("compressed.txt");
	//if (!fin1.fail())
	//{
	//	while (!fin1.eof())               // taking input from the file
	//	{ 
	//		fin1.getline(buff, 1000);
	//		int i = 0; 
	//		while(j < bit_count)
	//		{
	//			in = buff[i];
	//			count2 = 0;
	//			while (count2 < 8)
	//			{
	//				if (j == bit_count)     // writing bits == j
	//					break;
	//				bit = 128;            // 1000000
	//				bit = bit & in;
	//				in = in << 1;
	//				count2++;
	//				j++;
	//				if (bit == 0)
	//				{
	//					dcode.push_back(0);
	//				}
	//				else
	//				{
	//					dcode.push_back(1);
	//				}
	//				dcode_char = table_for_code.serach_char(dcode);   // search in hash table
	//				if (dcode_char != '\0')
	//				{
	//					out.push_back(dcode_char);
	//					dcode.clear();
	//				}
	//			}
	//			in = NULL;
	//			i++;
	//		}
	//	}
	//	fin1.close();
	//	//cout << "Decompressed sussessfully" << endl;
	//}
	//else
	//	cout << "File for Decompression not opened !" << endl;


	vector<int> dcode;
	vector<char> out;
	ifstream fin1("compressed.txt");
	if (!fin1.fail())
	{
		while (!fin1.eof())               // taking input from the file
		{
			int bit = 128;				  // 1000000   
			int count2 = 0;
			char buff[150], dcode_char;
			char in;
			fin1.getline(buff, 150);
			for (int i = 0; buff[i] != '\0'; i++)
			{
				in = buff[i];
				count2 = 0;
				while (count2 < 8)
				{
					bit = 128;            // 1000000
					bit = bit & in;
					count2++;
					in = in << 1;

					if (bit == 0)
					{
						dcode.push_back(0);
					}
					else
					{
						dcode.push_back(1);
					}
					dcode_char = table_for_code.serach_char(dcode);   // search in hash table
					if (dcode_char != '\0')
					{
						out.push_back(dcode_char);
						dcode.clear();
					}
				}
			}
		}

		fin1.close();
	}
	else
		cout << "File for Decompression not opened !" << endl;


	ofstream fout1("decompress.txt");

	if (!fout1.fail())     // writing data in desired file
	{
		cout << endl << endl << "After decompression: " << endl;
		for (int i = 0; i < out.size(); i++)
		{
			fout1 << out[i];
			cout << out[i];
		}
		fout1.close();
		cout << endl << endl;
	}
	else
		cout << "File for saving decompress not opened !" << endl;


	return 0;
}