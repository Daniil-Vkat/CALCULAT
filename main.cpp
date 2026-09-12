#include <iostream>
#include <string>
#include <limits>
 
// Статус вместо магических чисел
enum class Status {
    Ok,
    DivisionByZero,
    UnknownOperation,
    BadArgumentCount,
    InvalidNumber,
    Overflow,
    NegativeExponent,
    NegativeFactorial
};
 
struct Task {
    long long value1 = 0;
    char operation = '\0';
    long long value2 = 0;
    Status status = Status::Ok;
    long long result = 0;
};
 
 
// ---------- Операции ----------
 
Status addition(long long a, long long b, long long& out) {
    long long r;
    if (__builtin_add_overflow(a, b, &r)) return Status::Overflow;
    out = r;
    return Status::Ok;
}
 
Status subtraction(long long a, long long b, long long& out) {
    long long r;
    if (__builtin_sub_overflow(a, b, &r)) return Status::Overflow;
    out = r;
    return Status::Ok;
}
 
Status multiplication(long long a, long long b, long long& out) {
    long long r;
    if (__builtin_mul_overflow(a, b, &r)) return Status::Overflow;
    out = r;
    return Status::Ok;
}
 
Status division(long long a, long long b, long long& out) {
    if (b == 0) return Status::DivisionByZero;
    if (a == std::numeric_limits<long long>::min() && b == -1) return Status::Overflow;
    out = a / b;
    return Status::Ok;
}
 
Status power(long long a, long long b, long long& out) {
    if (b < 0) return Status::NegativeExponent;
    long long c = 1;
    for (long long i = 0; i < b; ++i) {
        if (__builtin_mul_overflow(c, a, &c)) return Status::Overflow;
    }
    out = c;
    return Status::Ok;
}
 
Status factorial(long long n, long long& out) {
    if (n < 0) return Status::NegativeFactorial;
    long long r = 1;
    for (long long i = 2; i <= n; ++i) {
        if (__builtin_mul_overflow(r, i, &r)) return Status::Overflow;
    }
    out = r;
    return Status::Ok;
}
 
// ---------- Парсинг ----------
 
bool parseNumber(const std::string& s, long long& out) {
    try {
        size_t pos = 0;
        long long v = std::stoll(s, &pos);
        if (pos != s.size()) return false;
        out = v;
        return true;
    } catch (...) {
        return false;
    }
}
 
bool parse(int argc, char** argv, Task& task) {
    if (argc != 4) {
        task.status = Status::BadArgumentCount;
        return false;
    }
    if (!parseNumber(argv[1], task.value1)) {
        task.status = Status::InvalidNumber;
        return false;
    }
    if (argv[2][0] == '\0') {
        task.status = Status::UnknownOperation;
        return false;
    }
    task.operation = argv[2][0];
    if (!parseNumber(argv[3], task.value2)) {
        task.status = Status::InvalidNumber;
        return false;
    }
    return true;
}
 
// ---------- Вычисление ----------
 
void calculate(Task& task) {
    switch (task.operation) {
        case '+': task.status = addition(task.value1, task.value2, task.result); break;
        case '-': task.status = subtraction(task.value1, task.value2, task.result); break;
        case '*': task.status = multiplication(task.value1, task.value2, task.result); break;
        case '/': task.status = division(task.value1, task.value2, task.result); break;
        case '^': task.status = power(task.value1, task.value2, task.result); break;
        case '!': task.status = factorial(task.value1, task.result); break;
        default: task.status = Status::UnknownOperation;
    }
}
 
// ---------- Вывод ----------
 
void output(const Task& task) {
    switch (task.status) {
        case Status::Ok:
            if (task.operation == '!')
                std::cout << task.value1 << "! = " << task.result << '\n';
            else
                std::cout << task.value1 << ' ' << task.operation << ' '
                          << task.value2 << " = " << task.result << '\n';
            break;
        case Status::DivisionByZero:
            std::cout << "Error! Division by zero!\n"; break;
        case Status::UnknownOperation:
            std::cout << "Error! Unknown operation!\n"; break;
        case Status::BadArgumentCount:
            std::cout << "Error! Usage: <num1> <op> <num2>\n"; break;
        case Status::InvalidNumber:
            std::cout << "Error! Invalid number!\n"; break;
        case Status::Overflow:
            std::cout << "Error! Overflow!\n"; break;
        case Status::NegativeExponent:
            std::cout << "Error! Negative exponent is not supported!\n"; break;
        case Status::NegativeFactorial:
            std::cout << "Error! Factorial of a negative number is undefined!\n"; break;
    }
}
 
// ---------- Запуск ----------
 
void run(int argc, char** argv) {
    Task task;
    if (parse(argc, argv, task)) {
        calculate(task);
    }
    output(task);
}
 
int main(int argc, char** argv) {
    run(argc, argv);
    return 0;
}