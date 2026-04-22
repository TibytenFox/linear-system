# Лабораторная работа №1 по линейной алгебре: Сравнение методов решения СЛАУ
## Математические формулы для методов решения СЛАУ

### 1. Метод Гаусса (прямой ход)

Исключение элементов под главной диагональю:

$$
\text{factor} = \frac{a_{ji}^{(k)}}{a_{ii}^{(k)}}, \quad j = i+1, \dots, n
$$

$$
a_{jk}^{(k+1)} = a_{jk}^{(k)} - \text{factor} \cdot a_{ik}^{(k)}, \quad k = i, \dots, n
$$

$$
b_j^{(k+1)} = b_j^{(k)} - \text{factor} \cdot b_i^{(k)}
$$

### 2. Метод Гаусса (обратный ход)

$$
x_i = \frac{b_i - \sum_{j=i+1}^{n} a_{ij} x_j}{a_{ii}}, \quad i = n, n-1, \dots, 1
$$

### 3. LU-разложение (Doolittle)

$$
L_{ii} = 1
$$

$$
U_{ik} = a_{ik} - \sum_{j=1}^{i-1} L_{ij} U_{jk}, \quad k \ge i
$$

$$
L_{ki} = \frac{a_{ki} - \sum_{j=1}^{i-1} L_{kj} U_{ji}}{U_{ii}}, \quad k > i
$$

### 4. Решение систем через LU-разложение

Прямая подстановка для $Ly = b$:

$$
y_i = b_i - \sum_{j=1}^{i-1} L_{ij} y_j, \quad i = 1, \dots, n
$$

Обратная подстановка для $Ux = y$:

$$
x_i = \frac{y_i - \sum_{j=i+1}^{n} U_{ij} x_j}{U_{ii}}, \quad i = n, \dots, 1
$$

### 5. Относительная погрешность

$$
\varepsilon = \frac{\|x_{\text{выч}} - x_{\text{точ}}\|_2}{\|x_{\text{точ}}\|_2}
$$

где $\|v\|_2 = \sqrt{\sum_{i=1}^{n} v_i^2}$

### 6. Невязка

$$
r = \|A x_{\text{выч}} - b\|_2
$$

### 7. Матрица Гильберта

$$
H_{ij} = \frac{1}{i + j - 1}, \quad i,j = 1, \dots, n
$$

### 8. Генерация случайных чисел

Равномерное распределение на $[ \text{MIN}, \text{MAX} ]$:

$$
x = \text{MIN} + \text{rand}() \cdot (\text{MAX} - \text{MIN})
$$

где $\text{rand}() \in [0,1)$ — псевдослучайное число.
## Установка и использование
1) Скачать файлы
```sh
git clone https://github.com/TibytenFox/linear-system
cd linear-system
```
2) Собрать программу
```sh
make
```
3) Запустить программу
```sh
make run
```
4) Собрать программу для тестов
```sh
make test
```
5) Запустить программу для тестов
```sh
make testing
```
6) Очистка от файлов (опционально)
```sh
make clear
```

## Таблица сравнения времени работы алгоритмов

| Название метода | Количество тестов | Размер матрицы | Время работы (секунды) |
|-----------------------------------------|-------------------|----------------|------------------------|
| **Одиночные тесты** | | | |
| Gauss Elimination | 1 | 100 | 0.008207 |
| Gauss Elimination with Pivoting | 1 | 100 | 0.006813 |
| LU Decomposition + Solve | 1 | 100 | 0.004931 |
| Gauss Elimination | 1 | 200 | 0.026548 |
| Gauss Elimination with Pivoting | 1 | 200 | 0.020096 |
| LU Decomposition + Solve | 1 | 200 | 0.016344 |
| Gauss Elimination | 1 | 500 | 0.243378 |
| Gauss Elimination with Pivoting | 1 | 500 | 0.249762 |
| LU Decomposition + Solve | 1 | 500 | 0.228975 |
| Gauss Elimination | 1 | 1000 | 1.978982 |
| Gauss Elimination with Pivoting | 1 | 1000 | 2.022824 |
| LU Decomposition + Solve | 1 | 1000 | 1.795089 |
| **Множественные тесты (фикс. размер 500)** | | | |
| Gauss Elimination | 1 | 500 | 0.273361 |
| Gauss Elimination with Pivoting | 1 | 500 | 0.255541 |
| LU Decomposition + Solve | 1 | 500 | 0.227603 |
| Gauss Elimination | 10 | 500 | 2.527327 |
| Gauss Elimination with Pivoting | 10 | 500 | 2.559800 |
| LU Decomposition + Solve | 10 | 500 | 0.235638 |
| Gauss Elimination | 100 | 500 | 25.396032 |
| Gauss Elimination with Pivoting | 100 | 500 | 25.949781 |
| LU Decomposition + Solve | 100 | 500 | 0.316898 |

  
## Относительная погрешность и невязка

| Название метода | Размер матрицы | Относительная погрешность | Невязка |
|-----------------------------------------|----------------|---------------------------|------------------|
| **Размер 5** | | | |
| Gauss Elimination | 5 | 2.738580e-13 | 2.220446e-16 |
| Gauss Elimination with Pivoting | 5 | 2.738580e-13 | 2.220446e-16 |
| LU Decomposition + Solve | 5 | 1.145471e-11 | 4.965068e-16 |
| **Размер 10** | | | |
| Gauss Elimination | 10 | 1.960091e-04 | 5.768888e-16 |
| Gauss Elimination with Pivoting | 10 | 1.960091e-04 | 5.768888e-16 |
| LU Decomposition + Solve | 10 | 2.244783e-04 | 7.850462e-16 |
| **Размер 15** | | | |
| Gauss Elimination | 15 | 5.673623e+00 | 9.550500e-16 |
| Gauss Elimination with Pivoting | 15 | 5.673623e+00 | 9.550500e-16 |
| LU Decomposition + Solve | 15 | 1.574429e+01 | 9.222205e-16 |