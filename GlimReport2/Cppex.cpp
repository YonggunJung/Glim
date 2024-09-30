// Cppex.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::cout << "Hello World!\n";
}

using namespace std;

int 양꼬치1(int n, int k) {
    int answer = 0;
    answer += n * 12000;
    int s = n / 10;
    k = k - s;
    answer += k * 2000;
    return answer;
}

int 접두사인지_확인하기2(string my_string, string is_prefix) {
    int answer = 0;
    if (my_string.substr(is_prefix.size()) == is_prefix)
        answer = 1;
    return answer;
}

vector<int> 순서_바꾸기3(vector<int> num_list, int n) {
    vector<int> answer(num_list.begin(), num_list.begin() + n);
    answer.insert(answer.begin(), num_list.begin() + n, num_list.end());
    return answer;
}

int 더_크게_합치기4(int a, int b) {
    
    int answer = max(stoi(to_string(a)), stoi(to_string(b)));
    return answer;
}

int 이차원_배열_대각선_순회하기5(vector<vector<int>> board, int k) {
    int answer = 0;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (i + j <= k)
                answer += board[i][j];
        }
    }
    return answer;
}

vector<int> 배열_조각하기6(vector<int> arr, vector<int> query) {
    vector<int> answer(arr);
    for (int i = 0; i < query.size(); i++) {
        if (i % 2 == 0)
            answer.erase(answer.begin() + query[i] + 1, answer.end());
        else
            answer.erase(answer.begin(), answer.begin() + query[i]);
    }
    return answer;
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
