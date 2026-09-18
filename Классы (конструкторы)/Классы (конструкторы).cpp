#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>

using namespace std;

class TextFile {
private:
    fstream file;
    string filename;
public:
    TextFile(string name) : filename(name) {
        file.open(filename, ios::in | ios::out | ios::app);
        if (!file.is_open()) {
            cerr << "Не удалось открыть файл " << filename << '\n';
        }
        else {
            cout << "Файл " << filename << " создан/открыт\n";
        }
    }

    ~TextFile() {
        if (file.is_open()) {
            file.close();
            if (remove(filename.c_str()) == 0) {
                cout << "Файл " << filename << " удален\n";
            }
        }
    }

    void WriteLine(string text);
    void PrintContents();
};

void TextFile::WriteLine(string text) {
    if (file.is_open()) {
        file.clear(); 
        file << text << '\n';
    }
    else {
        cerr << "Ошибка. Файл закрыт, запись невозможна\n";
    }
}
void TextFile::PrintContents() {
    if (!file.is_open()) {
        cerr << "Ошибка. Файл закрыт.\n";
        return;
    }
    file.clear();
    file.seekg(0, ios::beg);

    string line;
    cout << "Содержимое файла " << filename << ":\n";
    while (getline(file, line)) {
        cout << line << '\n';
    }
}

class myvector {
private:
    int len;
    int* v;
public:
    myvector(int length) : len(length) {
        v = new int[len];
        for (int i = 0; i < len; ++i) v[i] = 0;
    }

    myvector(const myvector& copy) : len(copy.len) {
        v = new int[len];
        for (int i = 0; i < len; ++i) v[i] = copy.v[i];
    }

    ~myvector() { delete[] v; }

    int getLen() const { return len; }

    void enterINT(int num) {
        for (int i = 0; i < len; ++i) {
            if (v[i] == 0) {
                v[i] = num;
                return;
            }
        }
        cout << "Ввод невозможен. Массив заполнен\n";
    }

    int DotProduct(const myvector& other) const {
        int minLen = (len < other.len) ? len : other.len;
        int sum = 0;
        for (int i = 0; i < minLen; ++i) {
            sum += v[i] * other.v[i];
        }
        return sum;
    }

    int Sum() const {
        int sum = 0;
        for (int i = 0; i < len; ++i) sum += v[i];
        return sum;
    }

    myvector MultiplyByScalar(int k) const {
        myvector copy(*this);
        for (int i = 0; i < copy.len; ++i) {
            copy.v[i] *= k;
        }
        return copy;
    }

    void print() const {
        cout << "[ ";
        for (int i = 0; i < len; ++i) cout << v[i] << " ";
        cout << "]\n";
    }
};
class tiger {
private:
    string name;
    int weight;
    string color;
public:
    tiger() : name(""), weight(0), color("") {}
    tiger(string n, int w = 225, string c = "") : name(n), weight(w), color(c) {}
    ~tiger() {}

    tiger& setname(string NewName) { name = NewName; return *this; }
    tiger& setweight(int NewWeight) { weight = NewWeight; return *this; }
    tiger& setcolor(string NewColor) { color = NewColor; return *this; }

    string getname() const { return name; }
    int getweight() const { return weight; }
    string getcolor() const { return color; }

    void print() const {
        if (name != "" || weight != 0 || color != "") {
            if (name != "") cout << "Кличка: " << name << " ";
            if (weight != 0) cout << "Вес: " << weight << " ";
            if (color != "") cout << "Цвет: " << color << " ";
            cout << '\n';
        }
        else {
            cout << "Ошибка данные пусты\n";
        }
    }
};

bool less(const tiger& a, const tiger& b) {
    return a.getweight() < b.getweight();
}

class Song {
private:
    string name;
    string singer;
    int seconds;
public:
    Song(string n = "", string s = "", int sec = 0) : name(n), singer(s), seconds(sec) {}
    ~Song() {}

    void setname(string NewName) { name = NewName; }
    void setsinger(string NewSinger) { singer = NewSinger; }
    void setseconds(int NewSeconds) { seconds = NewSeconds; }

    string getname() const { return name; }
    string getsinger() const { return singer; }
    int getseconds() const { return seconds; }

    void printInfo() const {
        if (name != "" || singer != "" || seconds != 0) {
            if (name != "") cout << "Название: " << name << " ";
            if (singer != "") cout << "Исполнитель: " << singer << " ";
            if (seconds != 0) cout << "Длительность: " << seconds << " ";
            cout << '\n';
        }
        else {
            cout << "Ошибка данные пусты\n";
        }
    }
};

class Playlist {
private:
    int capacity;
    int count;
    Song* songs;
public:
    Playlist(int cap) : capacity(cap), count(0) {
        songs = new Song[capacity];
    }

    Playlist(const Playlist& copy) : capacity(copy.capacity), count(copy.count) {
        songs = new Song[capacity];
        for (int i = 0; i < capacity; ++i) {
            songs[i] = copy.songs[i];
        }
    }

    ~Playlist() { delete[] songs; }

    void AddSong(const Song& s) {
        if (count < capacity) {
            songs[count] = s;
            cout << "Песня: " << s.getname() << " добавлена в плейлист\n";
            ++count;
        }
        else {
            cout << "Плейлист заполнен\n";
        }
    }

    int TotalDuration() const {
        int sum = 0;
        for (int i = 0; i < count; ++i) {
            sum += songs[i].getseconds();
        }
        return sum;
    }

    void PrintAll() const {
        if (count == 0) {
            cout << "Плейлист пуст\n";
            return;
        }
        for (int i = 0; i < count; ++i) {
            songs[i].printInfo();
        }
    }
};

int main() {
    system("chcp 1251");
    system("cls");


    cout << "\n";
    {
        TextFile myFile("test.txt");
        myFile.WriteLine("Привет, мир!");
        myFile.WriteLine("Это TextFile на C++.");
        myFile.PrintContents();
    }

    cout << "\n\n";
    tiger T1, T2("Kuzya");
    T1.setname("Murzik").setcolor("light").setweight(200);
    T1.print();

    T2.print();
    T2.setname("Tigr");

    if (::less(T2, T1))
        T2.print();
    else
        T1.print();

    cout << "\n\n";
    myvector v1(5), v2(5);
    v1.enterINT(1);
    v1.enterINT(2);
    v1.enterINT(3);

    v2.enterINT(4);
    v2.enterINT(5);
    v2.enterINT(6);

    cout << "v1: "; v1.print();
    cout << "v2: "; v2.print();

    cout << "Скалярное произведение: " << v1.DotProduct(v2) << '\n';
    cout << "Сумма v1: " << v1.Sum() << '\n';

    myvector v3 = v1.MultiplyByScalar(3);
    cout << "v1 * 3: "; v3.print();

    cout << "\n\n";
    Song s1("Песня 1", "Исполнитель 1", 180);
    Song s2("Песня 2", "Исполнитель 2", 210);
    Song s3("Песня 3", "Исполнитель 3", 240);

    Playlist playlist(5);
    playlist.AddSong(s1);
    playlist.AddSong(s2);
    playlist.AddSong(s3);

    cout << "Содержимое плейлиста:\n";
    playlist.PrintAll();
    cout << "Общая длительность: " << playlist.TotalDuration() << " секунд\n";

    return 0;
}