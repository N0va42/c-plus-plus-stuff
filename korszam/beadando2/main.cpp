#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>

using namespace std;

struct Polinom
{
    std::vector<double> coeffs; // polinom eggyüthatóink vektorban tárolva
                                // pl.: {1, 2, 3} -> 1 + 2x + 3x^2

    Polinom(const std::vector<double>& coeffs) : coeffs(coeffs) {} // konstruktor

    Polinom operator+(const Polinom& p2) // polinomok összeadása
    {
        std::vector<double> result(std::max(coeffs.size(), p2.coeffs.size())); // az eredményvektor inicializálása

        for (int i = 0; i < coeffs.size(); i++) result[i] += coeffs[i];

        for (int i = 0; i < p2.coeffs.size(); i++) result[i] += p2.coeffs[i];

        return {result};
    }

    Polinom operator-(const Polinom& p2) // polinomok kivonása
    {
        std::vector<double> result(std::max(coeffs.size(), p2.coeffs.size()));

        for (int i = 0; i < coeffs.size(); i++) result[i] += coeffs[i];

        for (int i = 0; i < p2.coeffs.size(); i++) result[i] -= p2.coeffs[i];

        return {result};
    }

    Polinom operator*(const Polinom& p2) // polinomok szorzása
    {
        std::vector<double> result(coeffs.size() + p2.coeffs.size() - 1);

        for (int i = 0; i < coeffs.size(); i++)

            for (int j = 0; j < p2.coeffs.size(); j++)

                result[i + j] += coeffs[i] * p2.coeffs[j];

        return {result};
    }

    Polinom derivative() // polinom deriváltja
    {
        if (coeffs.size() < 2) return {{0}}; // az eredményvektor inicializálása, ha a polinom nulladfokú akkor autómatikusan 0

        std::vector<double> result(coeffs.size() - 1);

        for (int i = 1; i < coeffs.size(); i++) result[i - 1] = coeffs[i] * i;

        return {result};
    }

    Polinom integral()
    {
        if (coeffs[0] == 0 && coeffs.size() == 1) return {{'C'}};
        else if (coeffs.size() == 1) return {{coeffs[0]}};

        std::vector<double> result(coeffs.size() + 1);

        for (int i = 0; i < coeffs.size(); i++) result[i+1] = coeffs[i]/(i+1);

        return {result};
    }
};


void askForInput(std::vector<double>& polinom)
{
    cout << "Polinóm együtthatói (vesszővel elválasztva): ";
    string input;
    getline(cin, input);
    stringstream ss(input);
    double coeff;
    while (ss >> coeff)
    {
        polinom.push_back(coeff);
        if (ss.peek() == ',')
            ss.ignore();
    }
}

int main()
{
    std::vector<double> input1;
    askForInput(input1);
    Polinom p1(input1);

    std::vector<double> input2;
    askForInput(input2);
    Polinom p2(input2);
    
    // Test addition
    Polinom p3 = p1 + p2;
    cout << "p1 + p2 = ";
    for (double coeff : p3.coeffs) cout << coeff << " ";
    cout << endl;

    // Test subtraction
    Polinom p4 = p1 - p2;
    cout << "p1 - p2 = ";
    for (double coeff : p4.coeffs) cout << coeff << " ";
    cout << endl;

    // Test multiplication
    Polinom p5 = p1 * p2;
    cout << "p1 * p2 = ";
    for (double coeff : p5.coeffs) cout << coeff << " ";
    cout << endl;

    // Test derivative
    Polinom p6 = p1.derivative();
    cout << "derivative of p1 = ";
    for (double coeff : p6.coeffs) cout << coeff << " ";
    cout << endl;

    // Test derivative
    Polinom p7 = p2.derivative();
    cout << "derivative of p2 = ";
    for (double coeff : p7.coeffs) cout << coeff << " ";
    cout << endl;

    // Test integral
    Polinom p8 = p1.integral();
    cout << "integral of p1 = ";
    for (double coeff : p8.coeffs) cout << coeff << " ";
    cout << endl;

    // Test integral
    Polinom p9 = p2.integral();
    cout << "integral of p2 = ";
    for (double coeff : p9.coeffs) cout << coeff << " ";
    cout << endl;

    return 0;
}