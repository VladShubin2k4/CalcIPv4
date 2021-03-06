#include <iostream>
using namespace std;

int transfer(int byte, short radix) {
    int res = 0, k = 1;
    for (int i = 0; byte != 0; ++i) { res += (byte % radix) * k; k *= 10; byte /= radix; }
    return res;
}

int formout(int out) {
    int radix = 0, tmp = out;
    while (tmp > 0) { tmp /= 10; ++radix; }
    for (int i = radix; i < 8; ++i) cout << 0;
    return out;
}

int fastpow(int a, int n) {
    int res = 1;
    while (n) {
        if (n % 2) res *= a;
        a *= a;
        n >>= 1;
    }
    return res;
}

void Info(int* byte) {
    cout << "In BIN(2): ";
    for (short i = 0; i < 4; ++i) { cout << formout(transfer(byte[i], 2)); if (i != 3) cout << "."; }
    cout.unsetf(ios::dec); cout.setf(ios::hex);
    cout << "\nIn HEX(16): ";
    for (short i = 0; i < 4; ++i) { cout << byte[i]; if (i != 3) cout << "."; }
    cout.unsetf(ios::hex); cout.setf(ios::oct);
    cout << "\nIn OCT(8): ";
    for (short i = 0; i < 4; ++i) { cout << byte[i]; if (i != 3) cout << "."; }
    cout.unsetf(ios::oct); cout.setf(ios::dec);
}

void CIDR(int* byte) {
    short cidr, ip[32] = {};
    cin >> cidr;
    for (short i = 0; i < 4; ++i) {
        for (short j = i * 8; j < 8 * (i + 1); ++j) {
            int octet = transfer(byte[i], 2) % fastpow(10, 8 - (j % 8)), div = fastpow(10, 7 - (j % 8));
            ip[j] = octet / div;
        }
    }
    cout << "\n\nNet ID = ";
    for (short i = 0; i < cidr; ++i) {
        if (i % 8 == 0 && i != 0) cout << '.';
        cout << ip[i];
    }
    cout << "\nHost ID = ";
    for (short i = cidr; i < 32; ++i) {
        if (i % 8 == 0) cout << '.';
        cout << ip[i];
    }
    cout << "\n";
}

void ClassOfIP(int* byte) {
    if (byte[0] < 128) {
        if (byte[0] == 10 && byte[0] <= 126 && byte[1] < 256 && byte[2] < 256 && byte[3] < 256) cout << "\n!Common adress!\n";
        else cout << "\nUnic adress\n";
        cout << "\nA class:\n\tNet ID = " << formout(transfer(byte[0], 2)) << "\n";
        cout << "\tHost ID = ";
        for (short i = 1; i < 4; ++i) {
            cout << formout(transfer(byte[i], 2));
            if (i != 3) cout << ".";
        }
    }
    else if (byte[0] < 192) {
        if (byte[0] == 172 && byte[1] < 32 && byte[1]>15 && byte[2] < 256 && byte[3] < 256) cout << "\n!Common adress!\n";
        else cout << "\nUnic adress\n";
        cout << "\nB class:\n\tNet ID = " << formout(transfer(byte[0], 2)) << "." << formout(transfer(byte[1], 2)) << "\n";
        cout << "\tHost ID = " << formout(transfer(byte[2], 2)) << "." << formout(transfer(byte[3], 2));
    }
    else if (byte[0] < 224) {
        if (byte[0] == 192 && byte[1] == 168 && byte[2] < 256 && byte[3] < 256) cout << "\n!Common adress!\n";
        else cout << "\nUnic adress\n";
        cout << "\nC class:\n\tNet ID = ";
        for (short i = 0; i < 3; ++i) {
            cout << formout(transfer(byte[i], 2));
            if (i != 2) cout << ".";
        }
        cout << "\n\tHost ID = " << formout(transfer(byte[3], 2));
    }
    else cout << "\tD/E class";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    int byte[4];
    char dot, cmd = '0';
    for (short i = 0; i < 4; ++i) { cin >> byte[i]; if (i != 3) cin >> dot; }
    Info(byte);
    cin >> cmd;
    if (cmd == '/') CIDR(byte);
    else ClassOfIP(byte);
    cin.get(); cin.get();
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
