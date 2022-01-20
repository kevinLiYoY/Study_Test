#include <ctype.h>
#include <iostream>
#include <string>
#include <vector>

void convert(char *src)
{
    while(*src != '\0')
    {
        *src = toupper(*src);
        ++src;
    }
}

int main()
{
    // char expected_wuw_sentence[1024];
    // strcpy(expected_wuw_sentence, "Hey Cerence");
    // convert(expected_wuw_sentence);
    // std::cout << expected_wuw_sentence << std::endl;

	//********测试引用失效问题******//
    std::vector<std::string>A;
    A.push_back("adsdf");
    A.push_back("sdfds");

	//获取Vector A 首元素引用
    std::string &referenceFirstA = A.at(0);
    std::cout << "Address A:" << &A << " item A:" << &referenceFirstA << " VALUE:" << referenceFirstA << std::endl;

    std::vector<std::string>B;
    B.push_back("ASSSS");
    B.push_back("ABSSS");
    B.push_back("ABCSS");
    B.push_back("ABCDS");
    B.push_back("CCCDE");
    B.push_back("BCDEF");
    B.push_back("ABEFG");
    B.push_back("ABFGH");
    B.push_back("EFGHI");
	
	//将B赋值给A，改变A元素值
    A = B;

	//检查引用值是否改变，实际测试结果是引用地址失效，引发未知错误，注释此条
    //std::cout << "Address A0:" << &A << " item A0:" << &referenceFirstA << " VALUE:" << referenceFirstA << std::endl;
	//重新获取A首元素，发现输出正常
	std::string &referenceFirstA0 = A.at(0);
	std::cout << "Address A1:" << &A << " item A1:" << &referenceFirstA0 << " VALUE:" << referenceFirstA0 << std::endl;
	
	//********测试vector 赋值元素内存地址改变问题******//
	//将vector B 重新赋值
	B.clear();
    B.push_back("ds");
	B.push_back("ert");
	B.push_back("fghjh");

	//获取Vector B 首元素引用，并输出内存地址
    std::string &referenceFirstB = B.at(0);
    std::cout << "Address B:" << &B << " item B:" << &referenceFirstB << " VALUE:" << referenceFirstB << std::endl;

	//将Vector B 赋值给Vector A
    A = B;
	//获取Vector A 首元素引用，并输出内存地址，赋值后，实际测试结果是Vector A 与Vector B 首元素内存地址一样
	std::string &referenceFirstA1 = A.at(0);
    std::cout << "Address A1:" << &A << " item A1:" << &referenceFirstA1 << " VALUE:" << referenceFirstA1 << std::endl;
	
	//改变Vector A 首元素值
	A.at(0) = "ssss";
	
	//再次查看Vector A, Vector B 首元素内存地址，发现Vector B 首元素地址发生了改变
    std::cout << "Address A2:" << &A << " item A2:" << &(A.at(0)) << " VALUE:" << A.at(0) << std::endl;
	std::cout << "Address B0:" << &B << " item B0:" << &(B.at(0)) << " VALUE:" << B.at(0) << std::endl;
	
	
	/* 测试实际输出如下：
	leili2@leili2-VirtualBox:~/project/win_project/TestProgram/vector_test$ g++ main.cpp -o test
	leili2@leili2-VirtualBox:~/project/win_project/TestProgram/vector_test$ ./test 
	Address A:0x7ffed3d18850 item A:0x55e5bb0cfee0 VALUE:adsdf
	Address A1:0x7ffed3d18850 item A1:0x55e5bb0d0740 VALUE:ASSSS
	Address B:0x7ffed3d18870 item B:0x55e5bb0d0530 VALUE:ds
	Address A1:0x7ffed3d18850 item A1:0x55e5bb0d0740 VALUE:ds
	Address A2:0x7ffed3d18850 item A2:0x55e5bb0d0740 VALUE:ssss
	Address B0:0x7ffed3d18870 item B0:0x55e5bb0d0530 VALUE:ds
	leili2@leili2-VirtualBox:~/project/win_project/TestProgram/vector_test$
	*/
}

