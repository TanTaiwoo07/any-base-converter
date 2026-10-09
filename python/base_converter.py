# -*- coding: utf-8 -*-
"""任意进制互转 (2~36)，支持整数与小数"""

DIGITS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"


def digit_val(ch: str, base: int) -> int:
    """把单个字符转成数值，非法字符抛异常"""
    d = DIGITS.find(ch.upper())
    if d < 0 or d >= base:
        raise ValueError(f'字符 "{ch}" 不是合法的 {base} 进制数字')
    return d


def convert(s: str, from_base: int, to_base: int, max_frac: int = 30) -> str:
    """把 s 从 from_base 进制转成 to_base 进制（小数最多保留 max_frac 位）"""
    if not (2 <= from_base <= 36):
        raise ValueError("源进制需在 2~36 之间")
    if not (2 <= to_base <= 36):
        raise ValueError("目标进制需在 2~36 之间")

    # 清理：去空白、下划线，统一大写
    s = "".join(ch for ch in s if not ch.isspace() and ch != "_").upper()
    if not s:
        raise ValueError("请输入数值")

    neg = s.startswith("-")
    if s[0] in "+-":
        s = s[1:]
    if not s:
        raise ValueError("请输入数值")

    if s.count(".") > 1:
        raise ValueError("小数点过多")

    int_str, _, frac_str = s.partition(".")
    int_str = int_str or "0"

    # ---------- 整数部分：源进制 -> 十进制大整数 -> 目标进制 ----------
    val = 0
    for ch in int_str:
        val = val * from_base + digit_val(ch, from_base)

    if val == 0:
        out_int = "0"
    else:
        buf = []
        while val:
            val, r = divmod(val, to_base)
            buf.append(DIGITS[r])
        out_int = "".join(reversed(buf))

    # ---------- 小数部分：num/den 分数形式，反复乘目标进制 ----------
    num, den = 0, 1
    for ch in frac_str:
        num = num * from_base + digit_val(ch, from_base)
        den *= from_base

    out_frac = []
    for _ in range(max_frac):
        if num == 0:
            break
        num *= to_base
        d, num = divmod(num, den)
        out_frac.append(DIGITS[d])

    # 去掉小数末尾多余的 0
    while out_frac and out_frac[-1] == "0":
        out_frac.pop()

    res = ("-" if neg else "") + out_int
    if out_frac:
        res += "." + "".join(out_frac)
    if res == "-0":
        res = "0"
    return res


def main():
    print("任意进制互转 (2~36)")
    try:
        from_base = int(input("源进制: ").strip())
        to_base = int(input("目标进制: ").strip())
        num = input("数值: ").strip()
        result = convert(num, from_base, to_base)
        print(f"{from_base} 进制 {num} = {to_base} 进制 {result}")
    except Exception as e:
        print("错误:", e)


if __name__ == "__main__":
    main()
