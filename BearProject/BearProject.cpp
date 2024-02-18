// BearProject.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
/*
Implement a simple ATM controller
Write code for a simple ATM. It doesn't need any UI (either graphical or console), but a controller should be implemented and tested.



Requirements
At least the following flow should be implemented:
Insert Card => PIN number => Select Account => See Balance/Deposit/Withdraw
For simplification, there are only 1 dollar bills in this world, no cents. Thus account balance can be represented in integer.
Your code doesn't need to integrate with a real bank system, but keep in mind that we may want to integrate it with a real bank system in the future. It doesn't have to integrate with a real cash bin in the ATM, but keep in mind that we'd want to integrate with that in the future. And even if we integrate it with them, we'd like to test our code. Implementing bank integration and ATM hardware like cash bin and card reader is not a scope of this task, but testing the controller part (not including bank system, cash bin etc) is within the scope.

A bank API wouldn't give the ATM the PIN number, but it can tell you if the PIN number is correct or not.
Based on your work, another engineer should be able to implement the user interface. You don't need to implement any REST API, RPC, network communication etc, but just functions/classes/methods, etc.
You can simplify some complex real world problems if you think it's not worth illustrating in the project.

How to submit
Please upload the code for this project to GitHub or anywhere, and post a link to your repository below. 
Please attach the instruction to clone your project, build and run tests in README.md file in the root directory of the repository. 
Please attach the test code(or Test Case), too.
*/

#include <iostream>

int main()
{
    std::cout << "Hello World!\n";
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
