#include <iostream>
#include <ctime>
#include <chrono>
#include <fstream>
#include <locale>
#include <thread>
#include <mutex>
#define TEST_LEN1 5000
#define TEST_LEN2 15000
#define TEST_LEN3 30000
#define TEST_LEN4 50000
#define FUNC_COUNT 4
using namespace std;

int* test_mass = new(nothrow) int[50000];


void BubbleSort(int n)
{
    int* A = new(nothrow) int[n];   
    if (!A)
    {
        std::cout << "Ошибка выделения памяти\n";
        return;
    }
    
    int count_side = 0, count_main = 0;
    int i, j, x;
    int memory = 3 * sizeof(int);
    for ( i = 0; i < n; ++i)
        A[i] = test_mass[i];
    mutex first_thread;
    auto start_time = chrono::high_resolution_clock::now();
    for (i = 1; i < n; i++)
    {
        count_side++;
        for (j = n - 1; j >= i; j--)
        {
            count_main++;
            count_side++;
            if (A[j - 1] > A[j])
            {
                x = A[j - 1];
                A[j - 1] = A[j];    
                A[j] = x;
            }
        }
        count_side++;
    }
    count_side++;
    auto end_time = chrono::high_resolution_clock::now();
    first_thread.lock();
    std::cout << "               Сортировка методом пузырька\n";
    std::cout << "Неупорядоченный массив\n";
    std::cout << "Amount of memory - " << memory << " bites" << endl;
    std::cout << "execution time in milliseconds " << n << " elemets: " << chrono::duration_cast<chrono::milliseconds>(end_time.time_since_epoch() - start_time.time_since_epoch()).count() << endl;
    std::cout << "Main operations amount - " << count_main << " Side operations amount - " << count_side << endl;
    first_thread.unlock();

    
    count_side = count_main = 0;
    start_time = chrono::high_resolution_clock::now();
    for (i = 1; i < n; i++)
    {
        count_side++;
        for (j = n - 1; j >= i; j--)
        {
            count_main++;
            count_side++;
            if (A[j - 1] > A[j])
            {
                x = A[j - 1];
                A[j - 1] = A[j];
                A[j] = x;
            }
        }
        count_side++;
    }
    count_side++;
    end_time = chrono::high_resolution_clock::now();
    first_thread.lock();
    std::cout << "Упорядоченный массив\n";
    std::cout << "Amount of memory - " << memory << " bites" << endl;
    std::cout << "execution time in milliseconds " << n << " elemets: " << chrono::duration_cast<chrono::milliseconds>(end_time.time_since_epoch() - start_time.time_since_epoch()).count() << endl;
    std::cout << "Main operations amount - " << count_main << " Side operations amount - " << count_side << endl;
    first_thread.unlock();

    for (i = 0; i < n / 2; i++)
    {
        x = A[n - i - 1];
        A[n - i - 1] = A[i];
        A[i] = x;
    }

    
    count_side = count_main = 0;
    start_time = chrono::high_resolution_clock::now();
    for (i = 1; i < n; i++)
    {
        count_side++;
        for (j = n - 1; j >= i; j--)
        {
            count_main++;
            count_side++;
            if (A[j - 1] > A[j])
            {
                x = A[j - 1];
                A[j - 1] = A[j];
                A[j] = x;
            }
        }
        count_side++;
    }
    count_side++;
    end_time = chrono::high_resolution_clock::now();
    first_thread.lock();
    std::cout << "Обратно упорядоченный массив\n";
    std::cout << "Amount of memory - " << memory << " bites" << endl;
    std::cout << "execution time in milliseconds " << n << " elemets: " << chrono::duration_cast<chrono::milliseconds>(end_time.time_since_epoch() - start_time.time_since_epoch()).count() << endl;
    std::cout << "Main operations amount - " << count_main << " Side operations amount - " << count_side << endl;
    first_thread.unlock();
    delete[] A;
}

void BubbleSort1(int n)
{
    int* A = new(nothrow) int[n];
    if (!A)
    {
        std::cout << "Ошибка выделения памяти\n";
        return;
    }
    
    int count_side = 0, count_main = 0;
    int i, j, x, flag = 1;
    int memory = 3 * sizeof(int);
    for (i = 0; i < n; ++i)
        A[i] = test_mass[i];
    mutex first_thread;
    auto start_time = chrono::high_resolution_clock::now();
    for (i = 1; flag; i++)
    {
        count_side++;
        flag = 0; /*признак упорядоченной последовательности*/
        for (j = n - 1; j >= i; j--)
        {
            count_side++;
            count_main++;
            if (A[j - 1] > A[j])
            {
                x = A[j - 1];
                A[j - 1] = A[j];
                A[j] = x;
                flag = 1; /*была перестановка, значит, еще не все*/
            }
        }
        count_side++;
    }
    count_side++;
    auto end_time = chrono::high_resolution_clock::now();
    first_thread.lock();
    std::cout << "               Сортировка методом пузырька c фиксацией факта обмена\n";
    std::cout << "Неупорядоченный массив\n";
    std::cout << "Amount of memory - " << memory << " bites" << endl;
    std::cout << "execution time in milliseconds " << n << " elemets: " << chrono::duration_cast<chrono::milliseconds>(end_time.time_since_epoch() - start_time.time_since_epoch()).count() << endl;
    std::cout << "Main operations amount - " << count_main << " Side operations amount - " << count_side << endl;
    first_thread.unlock();

    
    count_side = count_main = 0;
    start_time = chrono::high_resolution_clock::now();
    for (i = 1; flag; i++)
    {
        count_side++;
        flag = 0; /*признак упорядоченной последовательности*/
        for (j = n - 1; j >= i; j--)
        {
            count_side++;
            count_main++;
            if (A[j - 1] > A[j])
            {
                x = A[j - 1];
                A[j - 1] = A[j];
                A[j] = x;
                flag = 1; /*была перестановка, значит, еще не все*/
            }
        }
        count_side++;
    }
    count_side++;
    end_time = chrono::high_resolution_clock::now();
    first_thread.lock();
    std::cout << "Упорядоченный массив\n";
    std::cout << "Amount of memory - " << memory << " bites" << endl;
    std::cout << "execution time in milliseconds " << n << " elemets: " << chrono::duration_cast<chrono::milliseconds>(end_time.time_since_epoch() - start_time.time_since_epoch()).count() << endl;
    std::cout << "Main operations amount - " << count_main << " Side operations amount - " << count_side << endl;
    first_thread.unlock();

    for (i = 0; i < n / 2; i++)
    {
        x = A[n - i - 1];
        A[n - i - 1] = A[i];
        A[i] = x;
    }

    
    count_side = count_main = 0;
    start_time = chrono::high_resolution_clock::now();
    for (i = 1; flag; i++)
    {
        count_side++;
        flag = 0; /*признак упорядоченной последовательности*/
        for (j = n - 1; j >= i; j--)
        {
            count_side++;
            count_main++;
            if (A[j - 1] > A[j])
            {
                x = A[j - 1];
                A[j - 1] = A[j];
                A[j] = x;
                flag = 1; /*была перестановка, значит, еще не все*/
            }
        }
        count_side++;
    }
    count_side++;
    end_time = chrono::high_resolution_clock::now();
    first_thread.lock();
    std::cout << "Обратно упорядоченный массив\n";
    std::cout << "Amount of memory - " << memory << " bites" << endl;
    std::cout << "execution time in milliseconds " << n << " elemets: " << chrono::duration_cast<chrono::milliseconds>(end_time.time_since_epoch() - start_time.time_since_epoch()).count() << endl;
    std::cout << "Main operations amount - " << count_main << " Side operations amount - " << count_side << endl;
    first_thread.unlock();
    delete[] A;
}

void BubbleSort2(int n)
{
    int* A = new(nothrow) int[n];
    if (!A)
    {
        std::cout << "Ошибка выделения памяти\n";
        return;
    }
    
    int count_side = 0, count_main = 0;
    int i = 1, j, x, k;
    int memory = 3 * sizeof(int);
    for (i = 0; i < n; ++i)
        A[i] = test_mass[i];
    mutex first_thread;
    auto start_time = chrono::high_resolution_clock::now();
    memory = 4 * sizeof(int);
    i = 1;
    do
    {
        count_side++;
        k = 0; /*признак отсутствия обменов*/
        for (j = n - 1; j >= i; j--)
        {
            count_side++;
            count_main++;
            if (A[j - 1] > A[j])
            {
                x = A[j - 1];
                A[j - 1] = A[j];
                A[j] = x;
                k = j; /*запоминаем место последнего обмена*/
            }
        }
        count_side++;
        i = k; /*запоминаем место последнего обмена как левую границу*/
    } while (k);
    auto end_time = chrono::high_resolution_clock::now();
    first_thread.lock();
    std::cout << "               Сортировка методом пузырька с фиксацией места обмена\n";
    std::cout << "Неупорядоченный массив\n";
    std::cout << "Amount of memory - " << memory << " bites" << endl;
    std::cout << "execution time in milliseconds " << n << " elemets: " << chrono::duration_cast<chrono::milliseconds>(end_time.time_since_epoch() - start_time.time_since_epoch()).count() << endl;
    std::cout << "Main operations amount - " << count_main << " Side operations amount - " << count_side << endl;
    first_thread.unlock();

    
    count_side = count_main = 0;
    start_time = chrono::high_resolution_clock::now();
    i = 1;
    do
    {
        count_side++;
        k = 0; /*признак отсутствия обменов*/
        for (j = n - 1; j >= i; j--)
        {
            count_side++;
            count_main++;
            if (A[j - 1] > A[j])
            {
                x = A[j - 1];
                A[j - 1] = A[j];
                A[j] = x;
                k = j; /*запоминаем место последнего обмена*/
            }
        }
        count_side++;
        i = k; /*запоминаем место последнего обмена как левую границу*/
    } while (k);
    end_time = chrono::high_resolution_clock::now();
    first_thread.lock();
    std::cout << "Упорядоченный массив\n";
    std::cout << "Amount of memory - " << memory << " bites" << endl;
    std::cout << "execution time in milliseconds " << n << " elemets: " << chrono::duration_cast<chrono::milliseconds>(end_time.time_since_epoch() - start_time.time_since_epoch()).count() << endl;
    std::cout << "Main operations amount - " << count_main << " Side operations amount - " << count_side << endl;
    first_thread.unlock();

    for (i = 0; i < n / 2; i++)
    {
        x = A[n - i - 1];
        A[n - i - 1] = A[i];
        A[i] = x;
    }

    
    count_side = count_main = 0;
    start_time = chrono::high_resolution_clock::now();
    i = 1;
    do
    {
        count_side++;
        k = 0; /*признак отсутствия обменов*/
        for (j = n - 1; j >= i; j--)
        {
            count_side++;
            count_main++;
            if (A[j - 1] > A[j])
            {
                x = A[j - 1];
                A[j - 1] = A[j];
                A[j] = x;
                k = j; /*запоминаем место последнего обмена*/
            }
        }
        count_side++;
        i = k; /*запоминаем место последнего обмена как левую границу*/
    } while (k);
    end_time = chrono::high_resolution_clock::now();
    first_thread.lock();
    std::cout << "Обратно упорядоченный массив\n";
    std::cout << "Amount of memory - " << memory << " bites" << endl;
    std::cout << "execution time in milliseconds " << n << " elemets: " << chrono::duration_cast<chrono::milliseconds>(end_time.time_since_epoch() - start_time.time_since_epoch()).count() << endl;
    std::cout << "Main operations amount - " << count_main << " Side operations amount - " << count_side << endl;
    first_thread.unlock();
    delete[] A;
}

void ShakerSort(int n)
{
    int* A = new(nothrow) int[n];
    if (!A)
    {
        std::cout << "Ошибка выделения памяти\n";
        return;
    }

    int count_side = 0, count_main = 0;
    int i = 1, j, x, k, left, right;
    int memory = 5 * sizeof(int);
    for (i = 0; i < n; ++i)
        A[i] = test_mass[i];
    mutex first_thread;
    auto start_time = chrono::high_resolution_clock::now();
    k = n - 1, left = 1, right = n - 1;
    do
    {
        for (j = right; j >= left; j--) /*сначала просматриваем справа налево*/
        {
            count_side++;
            count_main++;
            if (A[j - 1] > A[j])
            {
                x = A[j - 1];
                A[j - 1] = A[j];
                A[j] = x;
                k = j;
            }
        }
        count_side++;
        left = k + 1;
        for (j = left; j <= right; j++) /*а теперь просматриваем слева направо*/
        {
            count_side++;
            count_main++;
            if (A[j - 1] > A[j])
            {
                x = A[j - 1];
                A[j - 1] = A[j];
                A[j] = x;
                k = j;
            }
        }
        count_side++;
        right = k - 1;
        count_side++;
    } while (left <= right); /*и так до тех пор, пока есть что просматривать*/
    auto end_time = chrono::high_resolution_clock::now();
    first_thread.lock();
    std::cout << "               Сортировка методом шейкера\n";
    std::cout << "Неупорядоченный массив\n";
    std::cout << "Amount of memory - " << memory << " bites" << endl;
    std::cout << "execution time in milliseconds " << n << " elemets: " << chrono::duration_cast<chrono::milliseconds>(end_time.time_since_epoch() - start_time.time_since_epoch()).count() << endl;
    std::cout << "Main operations amount - " << count_main << " Side operations amount - " << count_side << endl;
    first_thread.unlock();

    
    count_side = count_main = 0;
    start_time = chrono::high_resolution_clock::now();
    k = n - 1, left = 1, right = n - 1;
    do
    {
        for (j = right; j >= left; j--) /*сначала просматриваем справа налево*/
        {
            count_side++;
            count_main++;
            if (A[j - 1] > A[j])
            {
                x = A[j - 1];
                A[j - 1] = A[j];
                A[j] = x;
                k = j;
            }
        }
        count_side++;
        left = k + 1;
        for (j = left; j <= right; j++) /*а теперь просматриваем слева направо*/
        {
            count_side++;
            count_main++;
            if (A[j - 1] > A[j])
            {
                x = A[j - 1];
                A[j - 1] = A[j];
                A[j] = x;
                k = j;
            }
        }
        count_side++;
        right = k - 1;
        count_side++;
    } while (left <= right); /*и так до тех пор, пока есть что просматривать*/
    end_time = chrono::high_resolution_clock::now();
    first_thread.lock();
    std::cout << "Упорядоченный массив\n";
    std::cout << "Amount of memory - " << memory << " bites" << endl;
    std::cout << "execution time in milliseconds " << n << " elemets: " << chrono::duration_cast<chrono::milliseconds>(end_time.time_since_epoch() - start_time.time_since_epoch()).count() << endl;
    std::cout << "Main operations amount - " << count_main << " Side operations amount - " << count_side << endl;
    first_thread.unlock();

    for (i = 0; i < n / 2; i++)
    {
        x = A[n - i - 1];
        A[n - i - 1] = A[i];
        A[i] = x;
    }

    
    count_side = count_main = 0;
    start_time = chrono::high_resolution_clock::now();
    k = n - 1, left = 1, right = n - 1;
    do
    {
        for (j = right; j >= left; j--) /*сначала просматриваем справа налево*/
        {
            count_side++;
            count_main++;
            if (A[j - 1] > A[j])
            {
                x = A[j - 1];
                A[j - 1] = A[j];
                A[j] = x;
                k = j;
            }
        }
        count_side++;
        left = k + 1;
        for (j = left; j <= right; j++) /*а теперь просматриваем слева направо*/
        {
            count_side++;
            count_main++;
            if (A[j - 1] > A[j])
            {
                x = A[j - 1];
                A[j - 1] = A[j];
                A[j] = x;
                k = j;
            }
        }
        count_side++;
        right = k - 1;
        count_side++;
    } while (left <= right); /*и так до тех пор, пока есть что просматривать*/
    end_time = chrono::high_resolution_clock::now();
    first_thread.lock();
    std::cout << "Обратно упорядоченный массив\n";
    std::cout << "Amount of memory - " << memory << " bites" << endl;
    std::cout << "execution time in milliseconds " << n << " elemets: " << chrono::duration_cast<chrono::milliseconds>(end_time.time_since_epoch() - start_time.time_since_epoch()).count() << endl;
    std::cout << "Main operations amount - " << count_main << " Side operations amount - " << count_side << endl;
    first_thread.unlock();
    delete[] A;
}

int receive_data(string name_file, int* test, int length)
{
    char c;
    int flag = 0, number = 0, i = 0, j = 0;
    ifstream in(name_file);
    if (!in.is_open())
    {
        std::cout << "Ошибка открытия файла\n";
        return 0;
    }
    while ((c = in.get()))
    {
        if ((c >= '0' && c <= '9'))
        {
            flag = 1;
            number *= 10;
            number += c - 48;
        }
        if (flag == 1 && !(c >= '0' && c <= '9'))
        {
            test[j++] = number;
            if (j == length) break;
            number = 0;
            flag = 0;
        }
    }
    in.close();
    return 1;
}

int receive_repeatkeys(string name_file, int* test, int length, int count_keys)
{
    char c;
    int flag = 0, number = 0, j = 0, temp = 0;
    ifstream in(name_file);
    if (!in.is_open())
    {
        std::cout << "Ошибка открытия файла\n";
        return 0;
    }

    while ((c = in.get()))
    {
        if ((c >= '0' && c <= '9'))
        {
            flag = 1;
            number *= 10;
            number += c - 48;
        }
        if (flag == 1 && !(c >= '0' && c <= '9'))
        {
            break;
        }
    }
    temp = number;
    count_keys = int(length / count_keys);
    flag = number = 0;
    while ((c = in.get()))
    {
        if ((c >= '0' && c <= '9'))
        {
            flag = 1;
            number *= 10;
            number += c - 48;
        }
        if (flag == 1 && !(c >= '0' && c <= '9'))
        {
            if (j % count_keys == 0)
                test[j++] = temp;
            if (j == length) break;
            test[j++] = number;
            if (j == length) break;
            number = 0;
            flag = 0;
        }
    }
    in.close();
    return 1;
}

int main()
{
    setlocale(0, "rus");

    int* main_count[FUNC_COUNT * 4];
    for (int i = 0; i < FUNC_COUNT * 4; ++i)
        main_count[i] = new int[3];
    int* side_count[FUNC_COUNT * 4];
    for (int i = 0; i < FUNC_COUNT * 4; ++i)
        side_count[i] = new int[3];
    int memory[FUNC_COUNT];

    if (!test_mass)
    {
        cout << "Ошибка выделения памяти\n";
        return -1;
    }
    if (!receive_data("test_numbers.txt", test_mass, TEST_LEN4))/*считываем данные и одновременно проверяем на наличие
                                                                                                    ошибок во время считывания*/
    {
        return -1;
    }
    int count_keys[] = { 10, 100, 500, 1000 };
    void (*sorts[FUNC_COUNT]) (int) = { BubbleSort, BubbleSort1, BubbleSort2, ShakerSort };
    int test_mas_lengths[] = { TEST_LEN1, TEST_LEN2, TEST_LEN3, TEST_LEN4 };
    int i = 0, x, * test[FUNC_COUNT], z = 0;
    string names_test[] = { "Сортировка пузырьком", "Сортировка пузырьком с фиксацией факта обмена",
                        "Сортировка пузырьком с фиксацией места обмена", "Шейкерная сортировка" };
    
    std::thread th1(sorts[0], test_mas_lengths[0]);
    std::thread th2(sorts[0], test_mas_lengths[1]);
    std::thread th3(sorts[0], test_mas_lengths[2]);
    std::thread th4(sorts[0], test_mas_lengths[3]);

    std::thread th5(sorts[1], test_mas_lengths[0]);
    std::thread th6(sorts[1], test_mas_lengths[1]);
    std::thread th7(sorts[1], test_mas_lengths[2]);
    std::thread th8(sorts[1], test_mas_lengths[3]);

    std::thread th9(sorts[2], test_mas_lengths[0]);
    std::thread th10(sorts[2], test_mas_lengths[1]);
    std::thread th11(sorts[2], test_mas_lengths[2]);
    std::thread th12(sorts[2], test_mas_lengths[3]);

    std::thread th13(sorts[3], test_mas_lengths[0]);
    std::thread th14(sorts[3], test_mas_lengths[1]);
    std::thread th15(sorts[3], test_mas_lengths[2]);
    std::thread th16(sorts[3], test_mas_lengths[3]);

    th1.join();
    th2.join();
    th3.join();
    th4.join();
    th5.join();
    th6.join();
    th7.join();
    th8.join();
    th9.join();
    th10.join();
    th11.join();
    th12.join();
    th13.join();
    th14.join();
    th15.join();
    th16.join();


    delete[] test_mass;
    return 0;
}
