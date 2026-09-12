#pragma once
#include <climits>
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
    if (a == LLONG_MIN && b == -1) return Status::Overflow;
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
 
