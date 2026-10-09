// 任意进制互转 (2~36)，支持整数与小数
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <stdexcept>

const std::string DIGITS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// 单个字符 -> 数值
int digitVal(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
    if (c >= 'a' && c <= 'z') return c - 'a' + 10;
    return -1;
}

// 判断一个数字数组是否全为 0
static bool allZero(const std::vector<int>& v) {
    for (int x : v)
        if (x != 0) return false;
    return true;
}

std::string convert(std::string s, int fromBase, int toBase, int maxFrac = 30) {
    if (fromBase < 2 || fromBase > 36)
        throw std::invalid_argument("源进制需在 2~36 之间");
    if (toBase < 2 || toBase > 36)
        throw std::invalid_argument("目标进制需在 2~36 之间");

    // ---------- 清理输入 ----------
    std::string t;
    for (char c : s) {
        if (c == '_' || std::isspace(static_cast<unsigned char>(c))) continue;
        t += static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    }
    s = t;
    if (s.empty()) throw std::invalid_argument("请输入数值");

    bool neg = false;
    if (s[0] == '+' || s[0] == '-') {
        neg = (s[0] == '-');
        s = s.substr(1);
    }
    if (s.empty()) throw std::invalid_argument("请输入数值");

    size_t dot = s.find('.');
    if (dot != std::string::npos && s.find('.', dot + 1) != std::string::npos)
        throw std::invalid_argument("小数点过多");

    std::string intStr  = (dot == std::string::npos) ? s : s.substr(0, dot);
    std::string fracStr = (dot == std::string::npos) ? "" : s.substr(dot + 1);
    if (intStr.empty()) intStr = "0";

    // ---------- 解析整数部分 ----------
    std::vector<int> intDigits;
    for (char c : intStr) {
        int d = digitVal(c);
        if (d < 0 || d >= fromBase)
            throw std::invalid_argument("字符 '" + std::string(1, c) +
                                        "' 不是合法的 " + std::to_string(fromBase) + " 进制数字");
        intDigits.push_back(d);
    }

    // ---------- 整数部分：反复除以目标进制 ----------
    std::vector<int> outInt;
    if (allZero(intDigits)) {
        outInt.push_back(0);
    } else {
        while (!allZero(intDigits)) {
            int rem = 0;                       // 余数
            for (size_t i = 0; i < intDigits.size(); ++i) {
                int cur = rem * fromBase + intDigits[i];
                intDigits[i] = cur / toBase;   // 商的这一位
                rem = cur % toBase;            // 借给下一位
            }
            outInt.push_back(rem);             // 余数即目标进制的一位
        }
        std::reverse(outInt.begin(), outInt.end());
    }

    // ---------- 解析小数部分 ----------
    std::vector<int> fracDigits;
    for (char c : fracStr) {
        int d = digitVal(c);
        if (d < 0 || d >= fromBase)
            throw std::invalid_argument("字符 '" + std::string(1, c) +
                                        "' 不是合法的 " + std::to_string(fromBase) + " 进制数字");
        fracDigits.push_back(d);
    }

    // ---------- 小数部分：反复乘以目标进制 ----------
    std::vector<int> outFrac;
    for (int step = 0; step < maxFrac; ++step) {
        if (allZero(fracDigits)) break;
        int carry = 0;
        for (int j = static_cast<int>(fracDigits.size()) - 1; j >= 0; --j) {
            int cur = fracDigits[j] * toBase + carry;
            fracDigits[j] = cur % fromBase;    // 保留在源进制下
            carry = cur / fromBase;            // 向高位进位
        }
        outFrac.push_back(carry);              // 最终进位 = 目标进制的一位
    }
    // 去掉小数末尾多余的 0
    while (!outFrac.empty() && outFrac.back() == 0) outFrac.pop_back();

    // ---------- 拼装结果 ----------
    bool isZero = (outInt.size() == 1 && outInt[0] == 0 && outFrac.empty());
    std::string res;
    if (neg && !isZero) res += '-';
    for (int d : outInt) res += DIGITS[d];
    if (!outFrac.empty()) {
        res += '.';
        for (int d : outFrac) res += DIGITS[d];
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cout << "任意进制互转 (2~36)\n";
    std::cout << "请依次输入：源进制 目标进制 数值\n";
    std::cout << "例如：7 17 1234.56\n> ";

    int fromBase, toBase;
    std::string num;
    if (!(std::cin >> fromBase >> toBase >> num)) {
        std::cerr << "输入格式错误\n";
        return 1;
    }

    try {
        std::string res = convert(num, fromBase, toBase);
        std::cout << fromBase << " 进制 " << num
                  << " = " << toBase << " 进制 " << res << "\n";
    } catch (const std::exception& e) {
        std::cerr << "错误: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
