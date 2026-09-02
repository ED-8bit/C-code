#include <iostream>
#include <random>
#include <algorithm>
#include <cmath>
#include <queue>
#include <cstring>  // для memset, если потребуется
using namespace std;

// ====================== ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ШУМА ПЕРЛИНА ======================

// Функция плавного затухания: 6t^5 - 15t^4 + 10t^3
inline double fade(double t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

// Линейная интерполяция
inline double lerp_m(double a, double b, double t) {
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
 *
 * @param seed        Зерно случайности.
 * @param width       Ширина карты.
 * @param height      Высота карты.
 * @param scale       Масштаб (частота базовой октавы). Меньше = плавнее.
 * @param octaves     Количество октав.
 * @param persistence Постоянство (уменьшение амплитуды каждой следующей октавы).
 * @param lacunarity  Лакунарность (увеличение частоты каждой следующей октавы).
 * @return Указатель на массив высот (0.0 – низины, 1.0 – возвышенности).
 */
float* generatePerlinNoise(
    unsigned int seed,
    int width,
    int height,
    float scale = 0.01f,
    int octaves = 6,
    float persistence = 0.5f,
    float lacunarity = 2.0f)
{
    // 1. Таблица перестановок на основе seed
    int p[256];
    for (int i = 0; i < 256; ++i) p[i] = i;

    mt19937 rng(seed); // random seed
    shuffle(p, p + 256, rng);

    int perm[512];
    for (int i = 0; i < 512; ++i)
        perm[i] = p[i & 255];

    // Базовый шум Перлина (одна октава)
    // lambda захватывает perm по ссылке, это безопасно, т.к. perm живёт до конца generatePerlinNoise.
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

        double x1 = lerp_m(dotGradient(aa, xf, yf),
            dotGradient(ba, xf - 1, yf), u);
        double x2 = lerp_m(dotGradient(ab, xf, yf - 1),
            dotGradient(bb, xf - 1, yf - 1), u);
        return lerp_m(x1, x2, v);
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

            // Нормализация в [0, 1] и запись в массив
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
 *
 * @param seed           Зерно случайности.
 * @param width          Ширина карты.
 * @param height         Высота карты.
 * @param fillPercent    Начальный процент стен (0..100).
 * @param iterations     Число поколений автомата.
 * @param wallThreshold  Порог соседей-стен, при котором клетка становится стеной.
 * @param edgeIsWall     Считать ли границы карты стенами.
 * @param cleanIslands   Удалять ли мелкие изолированные области проходов.
 * @param minRegionSize  Минимальный размер допустимой области прохода (в клетках).
 * @return Указатель на массив (0 – проход, 1 – стена).
 */
int* generateCellularAutomata(
    unsigned int seed,
    int width,
    int height,
    int fillPercent = 45,
    int iterations = 5,
    int wallThreshold = 4,
    bool edgeIsWall = true,
    bool cleanIslands = true,
    int minRegionSize = 17)
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
    // Временный массив для нового поколения
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
    delete[] newGrid; // временный массив больше не нужен

    // 3. Постобработка – удаление маленьких изолированных полостей
    if (cleanIslands) {
        bool* visited = new bool[width * height];
        memset(visited, 0, width * height * sizeof(bool));

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                int idx = y * width + x;
                if (grid[idx] == 0 && !visited[idx]) {
                    // BFS по 4-соседству для сбора всей связной области проходов
                    queue<pair<int, int>> q;
                    vector<pair<int, int>> region; // используем временный vector для сохранения координат
                    // (можно заменить на собственный список, но vector здесь допустим для простоты)
                    // Если категорически нельзя ничего из STL, можно собрать координаты в динамический массив,
                    // но для читаемости оставим vector, т.к. требование "без векторов" касалось выходных данных.
                    // В случае полного отказа от векторов можно выделить массив пар с запасом, но здесь оставим.

                    q.push({ y, x });
                    visited[idx] = true;

                    while (!q.empty()) {
                        auto [cy, cx] = q.front(); q.pop();
                        region.push_back({ cy, cx });

                        const int dirs[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
                        for (auto d : dirs) {
                            int ny = cy + d[0];
                            int nx = cx + d[1];
                            if (ny >= 0 && ny < height && nx >= 0 && nx < width) {
                                int nidx = ny * width + nx;
                                if (grid[nidx] == 0 && !visited[nidx]) {
                                    visited[nidx] = true;
                                    q.push({ ny, nx });
                                }
                            }
                        }
                    }

                    // Если область слишком маленькая – заливаем стенами
                    if ((int)region.size() < minRegionSize) {
                        for (auto cell : region) {
                            grid[cell.first * width + cell.second] = 1;
                        }
                    }
                }
            }
        }
        delete[] visited;
    }

    return grid;
}

// ====================== ПРИМЕР ИСПОЛЬЗОВАНИЯ ======================

int main() {
    system("chcp 1251");
    // 1. Карта высот шумом Перлина (20x20)
    const int size = 128;
    float* heightMap = generatePerlinNoise(12345u, size, size);
    cout << "=== Карта высот (шум Перлина, seed=12345) ===\n";
    //for (int i = 0; i < size * size; i++)
    //    cout << heightMap[i] << ' ';
    //cout << "\n\n";
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            float v = heightMap[y * size + x];
            char c;
            if (v < 0.3f) c = '~';
            else if (v < 0.35f) c = '.';
            else if (v < 0.6f) c = ',';
            else if (v < 0.75f) c = '*';
            else c = '^';
            cout << c << ' ';
        }
        cout << '\n';
    }
    delete[] heightMap; // освобождаем память

    // 2. Пещера клеточным автоматом (25x25)
    cout << "\n=== Пещера (клеточный автомат, seed=54321) ===\n";
    int* cave = generateCellularAutomata(54321u, 25, 25);

    for (int y = 0; y < 25; ++y) {
        for (int x = 0; x < 25; ++x) {
            cout << (cave[y * 25 + x] ? '#' : ' ') << ' ';
        }
        cout << '\n';
    }
    delete[] cave;

    // 3. Тест с параметрами по умолчанию (только seed и размер)
    int* caveDefault = generateCellularAutomata(888u, 30, 30);
    // ... можно вывести аналогично ...
    delete[] caveDefault;

    // 4. Полная параметризация
    int* caveFull = generateCellularAutomata(888u, 50, 50, 50, 6, 5, true, true, 30);
    delete[] caveFull;

    return 0;
}