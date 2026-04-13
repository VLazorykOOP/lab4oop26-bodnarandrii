#include <iostream>
#include <string>
#include <new> // Для обробки помилок пам'ятi

using namespace std;

class VectorInt {
private:
    int* data;
    int size;
    int codeError; // 0 - ОК, 1 - вихiд за межi, 2 - мало пам'ятi, 3 - дiлення на 0
    static int count;

public:
    VectorInt() : size(1), codeError(0) { 
        try { data = new int[1]{0}; } catch(bad_alloc&) { codeError = 2; data = nullptr; }
        count++; 
    }
    VectorInt(int s) : size(s > 0 ? s : 1), codeError(0) {
        try { data = new int[size]; for(int i=0; i<size; i++) data[i] = 0; } 
        catch(bad_alloc&) { codeError = 2; data = nullptr; }
        count++;
    }
    VectorInt(int s, int initVal) : size(s > 0 ? s : 1), codeError(0) {
        try { data = new int[size]; for(int i=0; i<size; i++) data[i] = initVal; } 
        catch(bad_alloc&) { codeError = 2; data = nullptr; }
        count++;
    }
    VectorInt(const VectorInt& other) : size(other.size), codeError(other.codeError) {
        try { data = new int[size]; for(int i=0; i<size; i++) data[i] = other.data[i]; } 
        catch(bad_alloc&) { codeError = 2; data = nullptr; }
        count++;
    }
    ~VectorInt() { if(data) delete[] data; count--; }

    static int getCount() { return count; }
    int getError() { return codeError; }

    VectorInt& operator++() { for(int i=0; i<size; i++) data[i]++; return *this; } 
    VectorInt operator++(int) { VectorInt temp(*this); ++(*this); return temp; } 
    VectorInt& operator--() { for(int i=0; i<size; i++) data[i]--; return *this; } 
    VectorInt operator--(int) { VectorInt temp(*this); --(*this); return temp; } 
    bool operator!() { return size != 0; } 
    VectorInt operator~() { VectorInt temp(size); for(int i=0; i<size; i++) temp.data[i] = ~data[i]; return temp; } 
    VectorInt operator-() { VectorInt temp(size); for(int i=0; i<size; i++) temp.data[i] = -data[i]; return temp; } 

    VectorInt& operator=(const VectorInt& other) {
        if (this != &other) {
            delete[] data; size = other.size; codeError = other.codeError;
            data = new int[size]; for(int i=0; i<size; i++) data[i] = other.data[i];
        }
        return *this;
    }
    VectorInt& operator+=(const VectorInt& other) {
        int m = min(size, other.size); for(int i=0; i<m; i++) data[i] += other.data[i]; return *this;
    }
    VectorInt& operator-=(const VectorInt& other) {
        int m = min(size, other.size); for(int i=0; i<m; i++) data[i] -= other.data[i]; return *this;
    }
    VectorInt& operator*=(int val) { for(int i=0; i<size; i++) data[i] *= val; return *this; }
    VectorInt& operator/=(int val) { 
        if(val==0) { codeError = 3; return *this; } 
        for(int i=0; i<size; i++) data[i] /= val; return *this; 
    }
    VectorInt& operator%=(int val) { 
        if(val==0) { codeError = 3; return *this; } 
        for(int i=0; i<size; i++) data[i] %= val; return *this; 
    }
    VectorInt& operator|=(const VectorInt& other) {
        int m = min(size, other.size); for(int i=0; i<m; i++) data[i] |= other.data[i]; return *this;
    }
    VectorInt& operator^=(const VectorInt& other) {
        int m = min(size, other.size); for(int i=0; i<m; i++) data[i] ^= other.data[i]; return *this;
    }
    VectorInt& operator&=(const VectorInt& other) {
        int m = min(size, other.size); for(int i=0; i<m; i++) data[i] &= other.data[i]; return *this;
    }

    VectorInt operator+(const VectorInt& other) { VectorInt temp(*this); temp += other; return temp; }
    VectorInt operator-(const VectorInt& other) { VectorInt temp(*this); temp -= other; return temp; }
    VectorInt operator*(int val) { VectorInt temp(*this); temp *= val; return temp; }
    VectorInt operator/(int val) { VectorInt temp(*this); temp /= val; return temp; }
    VectorInt operator%(int val) { VectorInt temp(*this); temp %= val; return temp; }
    VectorInt operator|(const VectorInt& other) { VectorInt temp(*this); temp |= other; return temp; }
    VectorInt operator^(const VectorInt& other) { VectorInt temp(*this); temp ^= other; return temp; }
    VectorInt operator&(const VectorInt& other) { VectorInt temp(*this); temp &= other; return temp; }

    bool operator==(const VectorInt& other) {
        if (size != other.size) return false;
        for (int i = 0; i < size; i++) if (data[i] != other.data[i]) return false;
        return true;
    }
    bool operator!=(const VectorInt& other) { return !(*this == other); }
    bool operator>(const VectorInt& other) {
        int s1 = 0, s2 = 0;
        for(int i=0; i<size; i++) s1 += data[i];
        for(int i=0; i<other.size; i++) s2 += other.data[i];
        return s1 > s2;
    }
    bool operator<(const VectorInt& other) { return !(*this > other) && *this != other; }
    bool operator>=(const VectorInt& other) { return *this > other || *this == other; }
    bool operator<=(const VectorInt& other) { return *this < other || *this == other; }

    int& operator[](int index) {
        if (index < 0 || index >= size) {
            codeError = 1; 
            return data[size - 1]; 
        }
        codeError = 0;
        return data[index];
    }
    void operator()(int val) { for(int i=0; i<size; i++) data[i] = val; } 
    
    void* operator new(size_t size) { return ::operator new(size); }
    void operator delete(void* p) { ::operator delete(p); }

    friend ostream& operator<<(ostream& os, const VectorInt& v) {
        os << "[ "; for (int i = 0; i < v.size; i++) os << v.data[i] << " "; os << "]"; return os;
    }
    friend istream& operator>>(istream& is, VectorInt& v) {
        for (int i = 0; i < v.size; i++) is >> v.data[i]; return is;
    }
};

int VectorInt::count = 0;

class NumberDictionary {
private:
    int* numbers;        
    string* words;       
    int size;            
    int codeError;       

    string numberToWord(int n) {
        if (n == 100) return "sto";
        string ones[] = {"", "odyn", "dva", "try", "chotyry", "p'yat", "shist", "sim", "visim", "dev'yat"};
        string teens[] = {"desyat", "odynadtsyat", "dvanadtsyat", "trynadtsyat", "chotyrnadtsyat", "p'yatnadtsyat", "shistnadtsyat", "simnadtsyat", "visimnadtsyat", "dev'yatnadtsyat"};
        string tens[] = {"", "", "dvadtsyat", "trydtsyat", "sorok", "p'yatdesyat", "shistdesyat", "simdesyat", "visimdesyat", "dev'yanosto"};

        if (n < 10) return ones[n];
        if (n < 20) return teens[n - 10];
        string res = tens[n / 10];
        if (n % 10 != 0) res += " " + ones[n % 10];
        return res;
    }

public:
    NumberDictionary() {
        size = 100; numbers = new int[size]; words = new string[size]; codeError = 0;
        for (int i = 0; i < size; i++) { numbers[i] = i + 1; words[i] = numberToWord(i + 1); }
    }
    ~NumberDictionary() { delete[] numbers; delete[] words; }

    string operator[](int key) {
        codeError = 0;
        for (int i = 0; i < size; i++) if (numbers[i] == key) return words[i];
        codeError = 1; 
        return "Error: no such number!";
    }
    string operator()(int key) { return (*this)[key]; }
    int getError() { return codeError; }

    friend ostream& operator<<(ostream& os, const NumberDictionary& dict) {
        os << "Dictionary:\n";
        for (int i = 0; i < 3; i++) os << dict.numbers[i] << " - " << dict.words[i] << "\n";
        os << "...\n";
        for (int i = 97; i < 100; i++) os << dict.numbers[i] << " - " << dict.words[i] << "\n";
        return os;
    }
};


void testTask1() {
    cout << "\n--- Running Task 1.1 ---\n";
    
    int size1, val1, size2, val2;

    // Введення першого вектора
    cout << "Enter size for Vector 1: ";
    cin >> size1;
    cout << "Enter value to fill Vector 1: ";
    cin >> val1;
    VectorInt v1(size1, val1);

    // Введення другого вектора
    cout << "Enter size for Vector 2: ";
    cin >> size2;
    cout << "Enter value to fill Vector 2: ";
    cin >> val2;
    VectorInt v2(size2, val2);

    // Вектор для результатів 
    int maxSize = (size1 > size2) ? size1 : size2;
    VectorInt v3(maxSize, 0);  
    
    cout << "\nv1 = " << v1 << "\nv2 = " << v2 << endl;
    
    // Комплексний вираз
    cout << "Calculating expression: v3 = (v1 + v2) * 2 - (-v2)" << endl;
    v3 = (v1 + v2) * 2 - (-v2);
    cout << "Result: v3 = " << v3 << endl;

    // Додаткові оператори
    v3 /= 2;
    cout << "After v3 /= 2: " << v3 << endl;

    v3(7); 
    cout << "After calling v3(7) [filling with sevens]: " << v3 << endl;

    cout << "Total vectors in memory: " << VectorInt::getCount() << endl;
}

void testTask2() {
    cout << "\n--- Running Task 2.1 ---\n";
    NumberDictionary dict;
    
    cout << "Dictionary successfully created!\n";
    cout << dict; 
    
    int num;
    cout << "\nEnter a number from 1 to 100: ";
    cin >> num;

    cout << "Result via dict[num]: " << dict[num] << endl;

    if (dict.getError() != 0) {
        cout << "Caught an error! CodeError: " << dict.getError() << endl;
    }
}

int main() {
    int choice = -1;

    while (choice != 0) {
        cout << "    MAIN MENU    \n";
        cout << "1. Task 1.1 \n";
        cout << "2. Task 2.1 \n";
        cout << "0. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1) {
            testTask1(); // Виклик окремої функції для 1 завдання
        } 
        else if (choice == 2) {
            testTask2(); // Виклик окремої функції для 2 завдання
        } 
        else if (choice != 0) {
            cout << "Invalid choice! Try again.\n";
        }
    }

    cout << "Program terminated.\n";
    return 0;
}