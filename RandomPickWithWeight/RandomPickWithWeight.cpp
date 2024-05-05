// RandomPickWithWeight.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// you are given a 0-indexed arrat of positive integers where w[i] describes the weight of the ith index
/*
Implement the function pickIndex() which randomly picks an integer in the range 0, w.lenght -1 inclusive and returns it.
The probability of returning an index i is w[i]/sum[w]

Example

if w = [1,3]

the probability of picking 

index 0 (1) is: 1/(1+3) = 1/4 = 0.25
index 1 (3) is 3/4 = 0.75
Note that the higher the weight the higher probability has to be chosen

Keyword: weights

if w = [1, 3, 2, 4]
        0  1  2  3

index 0 weights 1
index 1 weights 3

1. sum the weights = 10
2. obtain the probabilities p = [.1, .3, .2, .4] ( w[i]/sum )
...
   the probabilities are ranges:
   0.0 -> 0.1, 0.1 -> 0.3, 0.4 -> 0.6, 0.6 -> 1.0
   p = [0.1, 0.4, 0.6, 1.0]
3. obtain a random number
4 if the random number falls within the previous and next p[i] choose that element

Binary search
Target = 0.5
obtain the mid = left + (right - left)/2
mid = 0 + (3 - 0) / 2 = 1.5 = 1
element mid (1) is p[1] = 0.4 -> Its less than target.

increment mid ; mid = mid + 1
mid = 2

element mid(2) = 0.6

0.6 > 0.5 = GOOD

index = 2 

*********
*/

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>

#include <cstdlib>
#include <ctime>

using namespace std;

class Solution
{
	vector<double> m_p{};
	vector<int> m_w;
	double m_sum{};
	int pickIndex() // time complexity O(logN)
	{
		auto target = ((double)rand() / (RAND_MAX));
		cout << " random target " << target << " ";
		auto left = 0;
		auto right = m_w.size() - 1;

		while (left < right)
		{
			auto mid = left + (right - left) / 2;
			if (target > m_p[mid])
			{
				left = mid + 1;
			}
			else
				right = mid;
		}
		cout << " index chosen " << left << " element chosen " << m_p[left];
		return left;
	}
public:
	int pickIndex(const vector<int>& w) // time complexity O(n)
	{
		m_w = w;
		// 1. Sum weights
		for (auto& elem : m_w)
		{
			m_sum += double(elem);
		}
		m_p.resize(m_w.size());
		// 2. obtain probabilities
		m_p[0] = m_w[0] / m_sum;
		for (size_t i = 1; i < m_w.size(); i++)
		{
			m_p[i] = m_p[i - 1] + (m_w[i]/m_sum);
		}
		for (auto elem: m_p)
		{
			cout << elem << "\t";
		}
		cout << endl;
		// 3. and 4. generate random number and search
		auto elemeChosen = pickIndex();
		cout << "  elem chosen " << m_w[elemeChosen];
		return elemeChosen;
	}
};

int main()
{

	std::srand(std::time(nullptr)); // use current time as seed for random generator

	Solution sol;
	{
		vector<int> vec{1, 3, 2, 4};
		std::cout << "Random index on " << '\n';
		for (auto elem: vec)
		{
			cout << elem << "\t";
		}
		cout << endl;
		cout << " is " << sol.pickIndex(vec);
		//string tst = "fo(o(bar)ba)z)";
		//auto res = sol.validString(tst);
		//std::cout << "\nTest string " << tst << " result " << res;
	}
	return 0;
}

