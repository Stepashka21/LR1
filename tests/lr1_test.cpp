#include <lib/lr1.h>
#include <gtest/gtest.h>
#include <vector>
#include <utility>
#include <iostream>
#include <fstream>
#include <random>

using namespace std;

// Подробнее https://google.github.io/googletest/reference/testing.html

// Тестовый класс
class CountAndSumTest : public ::testing::Test {
protected:

    void printErrors(pair<vector<pair<int, int>>, vector<string>> result) {
        cout << "\nErrors: \n";
        for (const auto& error : result.second) {
            cout << error << "\n";
        }
    }

    void writeNumbersToFile(const vector<int>& numbers) {
        
ofstream outputFile("../resources/numbers.txt"); // Открываем файл для записи
        for (int n : numbers)
            outputFile << n << endl;
        outputFile.close();
    }

    void writeNumbersToFile2(const vector<int>& numbers, string path) {

        ofstream outputFile(path); // Открываем файл для записи
        for (int n : numbers)
            outputFile << n << endl;
        outputFile.close();
    }

    vector<int>  randomNumber(int count) {
        vector<int> numbers;
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dist(-1000, 1000); // диапазон случайных чисел от 1 до 100
        // Заполняем вектор случайными числами
        for (int i = 0; i < count; ++i)
            numbers.push_back(dist(gen)); 
        return numbers;
    }

    vector<int>  getNimberFromFile(string path) {
        ifstream inputFile(path); // открываем файл для чтения
        vector<int> numbers;
        int num;
        while (inputFile >> num) 
            numbers.push_back(num);
        return numbers;
    }

    vector<pair<int, int>> parsePair(string path) {
        ifstream inputFile(path);
        vector<pair<int, int>> pairs;
        string line;
        while (getline(inputFile, line)) {
            istringstream iss(line);
            char discard; // для пропуска '{' и ',' между числами
            int num1, num2;
            iss >> discard >> num1 >> discard;
            iss >> num2 >> discard >> discard; // дополнительный discard для пропуска '}'
            pairs.emplace_back(num1, num2);
        }
        return pairs;
    }

    bool isNumber(const string& s) {
        for (char c : s) 
            if (!isdigit(c)) 
                return false;
        return true;
    }

    vector<string> parseBigNumber() {
        ifstream file("../resources/bignumber.txt");
        vector<string> errors;
        string str;
        while (file >> str) {
            if (isNumber(str)) {
                stringstream ss(str);
                double number;
                ss >> number;
                if (number > 2147483647 || number < -2147483647) 
                    errors.push_back("  " + str + "\n");
            }
        }
        file.close();
        return errors;
    }

    void writePairFromFile(pair<vector<pair<int, int>>, vector<string>> result, string path) {
        ofstream outputFile(path);
        for (const auto& pair : result.first)
            outputFile << "{" << pair.first << ", " << pair.second << "}" << endl;
        outputFile.close();
    }
};


// Пример теста 1 (вектор arr пустой)
TEST_F(CountAndSumTest, ArrEmpty) {
    vector<int> arr = { };
    pair<vector<pair<int, int>>, vector<string>> result;
    result = find_pairs(arr);
    vector<pair<int, int>> tmp = {  };
    EXPECT_EQ(result.first, tmp);
    printErrors(result);
}


// Пример теста 2 (вектор arr длинной > 1024)
TEST_F(CountAndSumTest, ArrSize) {
    vector<int> arr = { };
    for (int i = 0; i < 1025; ++i)
        arr.push_back(i);

    pair<vector<pair<int, int>>, vector<string>> result;
    result = find_pairs(arr);
    vector<pair<int, int>> tmp = {  };
    EXPECT_EQ(result.first, tmp);
    printErrors(result);
}

// Пример теста 3(вектор arr, который содержит 1 элемент)
TEST_F(CountAndSumTest, ArrWith1Element) {
    vector<int> arr = { 0 };

    pair<vector<pair<int, int>>, vector<string>> result;
    result = find_pairs(arr);
    vector<pair<int, int>> tmp = {};
    EXPECT_EQ(result.first, tmp);
    printErrors(result);
}

// Пример теста 4(вектор arr содержит макс значение int32)
TEST_F(CountAndSumTest, ArrWithMaxInt32) {
    vector<int> arr = getNimberFromFile("../resources/plusmaxint32.txt");
    pair<vector<pair<int, int>>, vector<string>> result;
    result = find_pairs(arr);
    vector<pair<int, int>> tmp = parsePair("../resources/pairplusmaxint32.txt");
    EXPECT_EQ(result.first, tmp);
    printErrors(result);
}

// Пример теста 5(вектор arr содержит мин значение int32)
TEST_F(CountAndSumTest, ArrWithMinInt32) {
    vector<int> arr = getNimberFromFile("../resources/minusmaxint32.txt");

    pair<vector<pair<int, int>>, vector<string>> result;
    result = find_pairs(arr);
    vector<pair<int, int>> tmp = parsePair("../resources/pairminusmaxint32.txt");
    EXPECT_EQ(result.first, tmp);
    printErrors(result);
}

// Пример теста 6 (вектор arr содержит число, которое не делится на 5 без остатка)
TEST_F(CountAndSumTest, ArrWithNoPairsNoShare5) {
    vector<int> arr = getNimberFromFile("../resources/noshare5.txt");
    pair<vector<pair<int, int>>, vector<string>> result;
    result = find_pairs(arr);
    vector<pair<int, int>> tmp = {  };
    EXPECT_EQ(result.first, tmp);
    printErrors(result);
}

// Пример теста 7 (вектор arr размером 50)
TEST_F(CountAndSumTest, ArrWithSize50) {
    vector<int> arr = getNimberFromFile("../resources/randnum.txt");
    //writeNumbersToFile2(arr, "../resources/randnum.txt");
    pair<vector<pair<int, int>>, vector<string>> result;
    result = find_pairs(arr);
    vector<pair<int, int>> tmp = parsePair("../resources/pairrandnum.txt");
    EXPECT_EQ(result.first, tmp);
    printErrors(result);
}

// Пример теста 8 (вектор arr размером 1024)
TEST_F(CountAndSumTest, ArrWithSize1024) {
    vector<int> arr = getNimberFromFile("../resources/1024.txt");
    pair<vector<pair<int, int>>, vector<string>> result;
    result = find_pairs(arr);
    vector<pair<int, int>> tmp = parsePair("../resources/pair1024.txt");
    EXPECT_EQ(result.first, tmp);
    printErrors(result);
}

// Пример теста 9 (вектор arr не содержит ключевых элементов)
TEST_F(CountAndSumTest, ArrWithNoKeyElement) {
    vector<int> arr = getNimberFromFile("../resources/nokeyelement.txt");
    pair<vector<pair<int, int>>, vector<string>> result;
    result = find_pairs(arr);
    vector<pair<int, int>> tmp = {  };
    EXPECT_EQ(result.first, tmp);
    printErrors(result);
}

// Пример теста 10 (вектор arr содержит ключевой элемент в начале)
TEST_F(CountAndSumTest, ArrWithStartKeyElement) {
    vector<int> arr = getNimberFromFile("../resources/startkeyelement.txt");
    pair<vector<pair<int, int>>, vector<string>> result;
    result = find_pairs(arr);
    vector<pair<int, int>> tmp = parsePair("../resources/pairstartkeyelement.txt");
    //vector<pair<int, int>> tmp = {  };
    EXPECT_EQ(result.first, tmp);
    printErrors(result);
}

// Пример теста 11 (вектор arr содержит ключевой элемент в середине)
TEST_F(CountAndSumTest, ArrWithMidKeyElement) {
    vector<int> arr = getNimberFromFile("../resources/midkeyelement.txt");
    pair<vector<pair<int, int>>, vector<string>> result;
    result = find_pairs(arr);
    vector<pair<int, int>> tmp = parsePair("../resources/pairmidkeyelement.txt");
    //vector<pair<int, int>> tmp = {  };
    EXPECT_EQ(result.first, tmp);
    printErrors(result);
}

// Пример теста 12 (вектор arr содержит ключевой элемент в конце)
TEST_F(CountAndSumTest, ArrWithEndKeyElement) {
    vector<int> arr = getNimberFromFile("../resources/endkeyelement.txt");
    pair<vector<pair<int, int>>, vector<string>> result;
    result = find_pairs(arr);
    vector<pair<int, int>> tmp = parsePair("../resources/pairendkeyelement.txt");
    //vector<pair<int, int>> tmp = {  };
    EXPECT_EQ(result.first, tmp);
    printErrors(result);
}


// Пример теста 13 (вектор arr содержит число > 2147483647)
TEST_F(CountAndSumTest, ArrWithMoreThenInt32) {
    vector<string> errors = parseBigNumber();
    vector<int> arr;
    vector<pair<int, int>> tmp;
    string path = "../resources/bignumber.txt";
    if (errors.size() != 0) {
        arr = {};
        pair<vector<pair<int, int>>, vector<string>> result;
        result = find_pairs(arr);
        tmp = {  };
        EXPECT_EQ(result.first, tmp);
        for (const auto& error : errors) {
            cout << error << "\n";
        }
    }
}

// Пример теста 14 (вектор arr содержит число < -2147483647)
TEST_F(CountAndSumTest, ArrWithMoreThanMinusInt32) {
    vector<string> errors = parseBigNumber();
    vector<int> arr;
    vector<pair<int, int>> tmp;
    string path = "../resources/bignumber2.txt";
    if (errors.size() != 0) {
        arr = {};
        pair<vector<pair<int, int>>, vector<string>> result;
        result = find_pairs(arr);
        tmp = {  };
        EXPECT_EQ(result.first, tmp);
        for (const auto& error : errors) {
            cout << error << "\n";
        }
    }
}


// Пример теста 15 (вектор arr содержит число, которое делится на 5 без остатка)
TEST_F(CountAndSumTest, ArrWithShare5) {
    vector<int> arr = getNimberFromFile("../resources/share5.txt");
    pair<vector<pair<int, int>>, vector<string>> result;
    result = find_pairs(arr);
    vector<pair<int, int>> tmp = parsePair("../resources/pairshare5.txt");
    //vector<pair<int, int>> tmp = {  };
    EXPECT_EQ(result.first, tmp);
    printErrors(result);
}

// Пример теста 16 (вектор arr длинной 200)
TEST_F(CountAndSumTest, ArrWith200) {
    vector<int> arr = getNimberFromFile("../resources/200.txt");
    writeNumbersToFile2(arr, "../resources/200.txt");
    pair<vector<pair<int, int>>, vector<string>> result;
    result = find_pairs(arr);
    vector<pair<int, int>> tmp = parsePair("../resources/pair200.txt");
    EXPECT_EQ(result.first, tmp);
    printErrors(result);
}

// Пример теста 17 (вектор arr длинной 500)
TEST_F(CountAndSumTest, ArrWith500) {
    vector<int> arr = getNimberFromFile("../resources/500.txt");
    writeNumbersToFile2(arr, "../resources/500.txt");
    pair<vector<pair<int, int>>, vector<string>> result;
    result = find_pairs(arr);
    vector<pair<int, int>> tmp = parsePair("../resources/pair500.txt");
    EXPECT_EQ(result.first, tmp);
    printErrors(result);
}

// Пример теста 18 (вектор arr длинной 700)
TEST_F(CountAndSumTest, ArrWith700) {
    vector<int> arr = getNimberFromFile("../resources/700.txt");
    writeNumbersToFile2(arr, "../resources/700.txt");
    pair<vector<pair<int, int>>, vector<string>> result;
    result = find_pairs(arr);
    vector<pair<int, int>> tmp = parsePair("../resources/pair700.txt");
    EXPECT_EQ(result.first, tmp);
    printErrors(result);
}

// Пример теста 19 (вектор arr длинной 900)
TEST_F(CountAndSumTest, ArrWith900) {
    vector<int> arr = getNimberFromFile("../resources/900.txt");
    writeNumbersToFile2(arr, "../resources/900.txt");
    pair<vector<pair<int, int>>, vector<string>> result;
    result = find_pairs(arr);
    vector<pair<int, int>> tmp = parsePair("../resources/pair900.txt");
    EXPECT_EQ(result.first, tmp);
    printErrors(result);
}

// Пример теста 20 (вектор arr длинной 1100)
TEST_F(CountAndSumTest, ArrWith1100) {
    vector<int> arr = getNimberFromFile("../resources/1100.txt");
    writeNumbersToFile2(arr, "../resources/1100.txt");
    pair<vector<pair<int, int>>, vector<string>> result;
    result = find_pairs(arr);
    vector<pair<int, int>> tmp = parsePair("../resources/pair1100.txt");
    EXPECT_EQ(result.first, tmp);
    printErrors(result);
}