#include <iostream>
#include <random>
#include <algorithm>
#include <cmath>
#include <cstring>   // memset
#include <Windows.h>

using namespace std;

// ====================== ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ШУМА ПЕРЛИНА ======================

// Функция плавного затухания: 6t^5 - 15t^4 + 10t^3
inline double fade(double t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

// Линейная интерполяция (переименована, чтобы избежать конфликта с std::lerp в C++20)
inline double lerp_val(double a, double b, double t) {
    return a + t * (b - a);
}

// Восемь градиентных векторов для 2D шума
static const int grad2[8][2] = {
    { 1,  1}, {-1,  1}, { 1, -1}, {-1, -1},
    { 1,  0}, {-1,  0}, { 0,  1}, { 0, -1}
};

// Скалярное произведение градиента по хэшу
double dotGradient(int hash, double x, double y) {
    int index = hash & 7; // 0..7
    return grad2[index][0] * x + grad2[index][1] * y;
}

// ====================== ГЕНЕРАЦИЯ ШУМОМ ПЕРЛИНА ======================

/**
 * Генерирует карту высот мультиоктавным шумом Перлина.
 * Возвращает плоский массив float размера width * height.
 * Вызывающий код должен освободить память (delete[]).
 */
float* generatePerlinNoise(
    unsigned int seed,
    int width,
    int height,
    float scale = 0.008f,
    int octaves = 7,
    float persistence = 0.52f,
    float lacunarity = 2.0f)
{
    // 1. Таблица перестановок на основе seed
    int p[256];
    for (int i = 0; i < 256; ++i) p[i] = i;

    mt19937 rng(seed);
    shuffle(p, p + 256, rng);

    int perm[512];
    for (int i = 0; i < 512; ++i)
        perm[i] = p[i & 255];

    // Базовый шум Перлина (одна октава)
    auto noise = [&perm](double x, double y) -> double {
        int X = (int)floor(x) & 255;
        int Y = (int)floor(y) & 255;
        double xf = x - floor(x);
        double yf = y - floor(y);

        double u = fade(xf);
        double v = fade(yf);

        int aa = perm[perm[X] + Y];
        int ab = perm[perm[X] + Y + 1];
        int ba = perm[perm[X + 1] + Y];
        int bb = perm[perm[X + 1] + Y + 1];

        double x1 = lerp_val(dotGradient(aa, xf, yf),
            dotGradient(ba, xf - 1, yf), u);
        double x2 = lerp_val(dotGradient(ab, xf, yf - 1),
            dotGradient(bb, xf - 1, yf - 1), u);
        return lerp_val(x1, x2, v);
        };

    // 2. Выделяем память под плоскую карту высот
    float* map = new float[width * height];

    // 3. Заполняем мультиоктавным шумом
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            double x = col * scale;
            double y = row * scale;

            double amplitude = 1.0;
            double frequency = 1.0;
            double noiseValue = 0.0;
            double maxValue = 0.0;

            for (int i = 0; i < octaves; ++i) {
                noiseValue += amplitude * noise(x * frequency, y * frequency);
                maxValue += amplitude;
                frequency *= lacunarity;
                amplitude *= persistence;
            }

            map[row * width + col] = static_cast<float>(noiseValue / maxValue);
        }
    }
    return map;
}

// ====================== ГЕНЕРАЦИЯ КЛЕТОЧНЫМ АВТОМАТОМ ======================

/**
 * Генерирует карту пещеры клеточным автоматом.
 * Возвращает плоский массив int размера width * height.
 * Вызывающий код должен освободить память (delete[]).
 */
int* generateCellularAutomata(
    unsigned int seed,
    int width,
    int height,
    int fillPercent = 60,
    int iterations = 4,
    int wallThreshold = 5,
    bool edgeIsWall = true,
    bool cleanIslands = true,
    int minRegionSize = 20)
{
    mt19937 rng(seed);
    uniform_int_distribution<int> dist(0, 99);

    // 1. Выделяем память под карту и заполняем случайным шумом
    int* grid = new int[width * height];
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            grid[y * width + x] = (dist(rng) < fillPercent) ? 1 : 0;
        }
    }

    // 2. Итеративное сглаживание (клеточный автомат)
    int* newGrid = new int[width * height];

    for (int iter = 0; iter < iterations; ++iter) {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                int wallCount = 0;

                // Окрестность Мура 3x3
                for (int dy = -1; dy <= 1; ++dy) {
                    for (int dx = -1; dx <= 1; ++dx) {
                        if (dx == 0 && dy == 0) continue;

                        int nx = x + dx;
                        int ny = y + dy;

                        if (nx < 0 || nx >= width || ny < 0 || ny >= height) {
                            if (edgeIsWall) ++wallCount;
                        }
                        else if (grid[ny * width + nx] == 1) {
                            ++wallCount;
                        }
                    }
                }

                newGrid[y * width + x] = (wallCount >= wallThreshold) ? 1 : 0;
            }
        }

        // Копируем новое состояние обратно в grid
        for (int i = 0; i < width * height; ++i) {
            grid[i] = newGrid[i];
        }
    }
    delete[] newGrid;

    // 3. Постобработка – удаление маленьких изолированных полостей
    if (cleanIslands) {
        bool* visited = new bool[width * height];
        memset(visited, 0, width * height * sizeof(bool));

        // Простая структура для хранения пар координат (без std::vector)
        struct IntPair { int x, y; };
        struct RegionQueue {
            IntPair* data;
            int head, tail, capacity;
            RegionQueue(int cap) : head(0), tail(0), capacity(cap) {
                data = new IntPair[cap];
            }
            ~RegionQueue() { delete[] data; }
            void push(int x, int y) {
                data[tail] = { x, y };
                tail = (tail + 1) % capacity;
            }
            IntPair pop() {
                IntPair p = data[head];
                head = (head + 1) % capacity;
                return p;
            }
            bool empty() const { return head == tail; }
            int size() const { return (tail - head + capacity) % capacity; }
        };

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                int idx = y * width + x;
                if (grid[idx] == 0 && !visited[idx]) {
                    // BFS для сбора связной области проходов
                    RegionQueue q(width * height);
                    q.push(x, y);
                    visited[idx] = true;

                    while (!q.empty()) {
                        IntPair p = q.pop();
                        int cy = p.y, cx = p.x;

                        // 4-соседство
                        const int dx[4] = { -1, 1, 0, 0 };
                        const int dy[4] = { 0, 0, -1, 1 };
                        for (int d = 0; d < 4; ++d) {
                            int nx = cx + dx[d];
                            int ny = cy + dy[d];
                            if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                                int nidx = ny * width + nx;
                                if (grid[nidx] == 0 && !visited[nidx]) {
                                    visited[nidx] = true;
                                    q.push(nx, ny);
                                }
                            }
                        }
                    }

                    // Если область слишком маленькая – замуровываем её стенами
                    if (q.size() < minRegionSize) {
                        // Вся область лежит в очереди; извлекаем и ставим стены
                        while (!q.empty()) {
                            IntPair p = q.pop();
                            grid[p.y * width + p.x] = 1;
                        }
                    }
                    // Если размер в норме, просто игнорируем (очередь уничтожится после блока)
                }
            }
        }
        delete[] visited;
    }

    return grid;
}

// ====================== ПРИМЕР ИСПОЛЬЗОВАНИЯ ======================

int main() 
{
    srand(time(0));
    do
    {
        system("cls");
        int seed1, seed2;
        seed1 = rand();
        seed2 = rand();
        system("chcp 1251");
        // 1. Карта высот шумом Перлина (1024x1024)
        const int size = 256;
        float* heightMap = generatePerlinNoise(seed1, size, size + 1.5 * size);

        cout << "=== Карта высот (шум Перлина, random seed) ===\n";
        for (int y = 0; y < size; ++y) {
            for (int x = 0; x < size; ++x) {
                float v = heightMap[y * size + x];
                char c;
                if (v < 0.025f) c = 'W';
                else if (v < 0.05f) c = 'O';
                else if (v < 0.1f) c = '|';
                else if (v < 0.2f) c = '*';
                else if (v < 0.3f) c = '^';
                else c = ' '; 
                cout << c << ' ';
            }
            cout << '\n';
        }
        delete[] heightMap;

        // 2. Пещера клеточным автоматом (25x25)
        cout << "\n=== Пещера (клеточный автомат, random seed) ===\n";
        int* cave = generateCellularAutomata(seed2, 256, 256);

        for (int y = 0; y < 256; ++y) {
            for (int x = 0; x < 256; ++x) {
                cout << (cave[y * 256 + x] ? '#' : ' ') << ' ';
            }
            cout << '\n';
        }
        delete[] cave;
/*
        // 3. Тест с параметрами по умолчанию (только seed и размер)
        int* caveDefault = generateCellularAutomata(777u, 30, 30);
        delete[] caveDefault;

        // 4. Полная параметризация
        int* caveFull = generateCellularAutomata(888u, 50, 50, 50, 6, 5, true, true, 30);
        delete[] caveFull;*/
        Sleep(2000);
    } while (false);
    

    return 0;
}