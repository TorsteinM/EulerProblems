// Euler.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <map>
#include <set>
#include <algorithm>
#include <array>
#include <string>
#include <numeric>
#include <math.h>
#include <bitset>
#include <ppl.h>

using namespace std;

using UInt = unsigned long long;
using Int = long long;




struct Utils {
	static UInt distFactors(UInt a, vector<UInt> p) {
		UInt factors = 0;
		UInt ind = a / log(a);  //Prime Number theorem pi(x) < x / log (x).
		while (a > 1 && ind > 0) {
			if (a%p[--ind] == 0) {
				//	cout << "Factor " << p[ind] << " found." << endl;
				factors++;
				while (a%p[ind] == 0) {
					a /= p[ind];
				}
			}
		}
		return factors;
	}
	static UInt fact(UInt n) {
		if (n == 1)
			return 1;
		else
			return n*fact(n - 1);
	}
	static UInt gcd_rec(UInt a, UInt b) {
		if (b == 0) { 
			return a; 
		}
		else {
			return gcd(b, a % b);
		}
	}
	static UInt gcd(UInt a, UInt b) {
		while (b != 0) {
			auto t = b;
			b = a % b;
			a = t;
		}
		return a;
	}
	static double quickLen(UInt a, UInt b) {
		if (b > a) {
			return 0.947543636290784*(double)b + 0.392485425091961*(double)a;
		}
		else {
			return 0.947543636290784*(double)a + 0.392485425091961*(double)b;
		}
	}
	struct Sieve {

		// Sieve of Erastothenes
		// Constructor creates a vector of primes up to and including N.
		// The set which stores if the numbers are prime is kept to enable further growth and batching.
		// TH

		vector<UInt> primes;
		map<UInt, bool> primeMap;
		UInt curMax = 2;
		Sieve(){}
		Sieve(UInt N) {
			populate(N);
		}
		void populate(UInt N) {
			//populates the sieve from curMax to N. First pass starts at curMax=2.
			for (auto p : primes) {
				for (UInt i = curMax / p; i <= N / p; i++) {
					primeMap[i*p] = false;
				}
			}
			for (UInt i = curMax; i <= N; i++) {
				if (primeMap.count(i) < 1) {
					primeMap[i] = true;
					primes.push_back(i);
					for (int j = 2; j <= N / i; j++) {
						primeMap[i*j] = false;
					}
				}
			}
			curMax = N;
		}
	};
	struct Fib {

		// Fibonacci calculator

		// Produces the fibonacci number k with recursion
		// The calculated numbers are stored in a for easy lookup.

		map<UInt, UInt> Mem;
		Fib() {
			Mem[0] = 0;
			Mem[1] = 1;
		}
		UInt FibK(int k) {
			if (Mem.count(k) > 0) return Mem[k];
			else {
				Mem[k] = FibK(k - 1) + FibK(k - 2);
				return Mem[k];
			}
		}
	};
	static bool Triangle(UInt N) {
		// is inverse function an integer
		double test = (sqrt(8 * N + 1) - 1) / 2;
		return test == (int)test;
	}
	static bool Pentagonal(UInt N) {
		// is inverse function an integer
		double test = (sqrt(1 + 24 * N) + 1.0) / 6.0;
		return test == (int)test;
	}
	static UInt phi(UInt N, Sieve s) {
		// Base case
		if (N < 2)
			return 0;

		// Lehmer's conjecture
		if (s.primeMap[N])
			return N - 1;

		// Even number?
		if (N & 1 == 0) {
			UInt m = N >> 1;
			return !(m & 1) ? phi(m, s) << 1 : phi(m, s);
		}

		// For all primes ...
		for (std::vector<UInt>::iterator p = s.primes.begin();
			p != s.primes.end() && *p <= N;
			++p)
		{
			UInt m = *p;
			if (N % m) continue;

			// phi is multiplicative
			UInt o = N / m;
			UInt d = Utils::gcd(m, o);
			return d == 1 ? phi(m, s)*phi(o, s) : phi(m, s)*phi(o, s)*d / phi(d, s);
		}
	}
	
	/* Function to calculate (base^exponent)%modulus */
	static Int modular_pow(Int base, Int exponent, Int modulus){
		/* initialize result */
		long long int result = 1;

		while (exponent > 0)
		{
			/* if y is odd, multiply base with result */
			if (exponent & 1)
				result = (result * base) % modulus;

			/* exponent = exponent/2 */
			exponent = exponent >> 1;

			/* base = base * base */
			base = (base * base) % modulus;
		}
		return result;
	}
	static Int Rho(Int n) {
		// a^(p-1) equiv. 1 (mod p)
		// gcd(a^L - 1 mod N,N) = p*r
		// Evaluate a^(k!) for k=1,2,3... (to some practical limit)
		// 
		//
		//

		/* initialize random seed */
		srand(time(NULL));

		/* no prime divisor for 1 */
		if (n == 1) return n;

		/* even number means one of the divisors is 2 */
		if (n % 2 == 0) return 2;

		/* we will pick from the range [2, N) */
		Int x = (rand() % (n - 2)) + 2;
		Int y = x;
		
		/* the constant in f(x).
		* Algorithm can be re-run with a different c
		* if it throws failure for a composite. */
		Int c = (rand() % (n - 1)) + 1;

		/* Initialize candidate divisor (or result) */
		Int d = 1;

		while (d == 1)
		{
			/* Tortoise Move: x(i+1) = f(x(i)) */
			x = (modular_pow(x, 2, n) + c + n) % n;

			/* Hare Move: y(i+1) = f(f(y(i))) */
			y = (modular_pow(y, 2, n) + c + n) % n;
			y = (modular_pow(y, 2, n) + c + n) % n;

			/* check gcd of |x-y| and n */
			d = gcd(abs((x - y)), n);

			/* retry if the algorithm fails to find prime factor
			* with chosen x and c */
			if (d == n) return Rho(n);
		}

		return d;
	}
	
	struct MillerRabin {
		Int knownPrimesLimit = 1000;
		map<UInt, bool> _knownPrimes = { { 0, false }, { 1, false }};
		set<UInt> _primeSet;
		
		/*Constructor for the object*/
		MillerRabin() {
			populateKnown();
		}
		
		/*Routine for populating known primes, using a sieve*/
		void populateKnown() {
			for (UInt i = 2; i <= knownPrimesLimit; i++) {
				if (_knownPrimes.count(i) < 1) {
					_knownPrimes[i] = true;
					_primeSet.insert(i);
					for (int j = 2; j <= knownPrimesLimit / i; j++) {
						_knownPrimes[i*j] = false;
					}
				}
			}
		}
		
		/*Modular exponentiation*/
		Int pow_mod(Int x, Int y, Int z) {
			Int number = 1;
			while (y)
			{
				if (y & 1)
					number = number * x % z;
				y >>= 1;
				x = (unsigned long)x * x % z;
			}
			return number;
		}
		
		/*Composite test, returns True if it definitely is not a prime.*/
		bool _try_composite(Int a, Int d, Int n, Int s) {
			if (modular_pow(a, d, n) == 1)
				return false;
			for (Int i = 0; i < s; i++)
				if (modular_pow(a, pow(2, i) * d, n) == n - 1)
					return false;
			return true; //# n  is definitely composite
		}

		/*Main function for determining if N is prime*/
		bool isPrime(Int N) {
			int _precisionHighN = 16;
			/*Do a lookup if N is low enough*/
			if (N < knownPrimesLimit) return _knownPrimes[N];
			
			/*Test for composition with known primes*/
			for (auto p : _primeSet) if (N%p == 0) return false;

			/*Initialize the composite checker*/
			auto d = N - 1;
			auto s = 0LL;
			while (d % 2==0) {
				d = d >> 1;
				s++;
			}
			if (N < 1373653) {
				if (_try_composite(2, d, N, s)) return false;
				if (_try_composite(3, d, N, s)) return false;
				//if (_try_composite(5, d, N, s)) return false;
				//if (_try_composite(7, d, N, s)) return false;
				return true;
			}
			if (N < 25326001) {
				if (_try_composite(2, d, N, s)) return false;
				if (_try_composite(3, d, N, s)) return false;
				if (_try_composite(5, d, N, s)) return false;
				//if (_try_composite(7, d, N, s)) return false;
				return true;
			}
			if (N < 118670087467) {
				if (N == 3215031751)return false;
				if (_try_composite(2, d, N, s)) return false;
				if (_try_composite(3, d, N, s)) return false;
				if (_try_composite(5, d, N, s)) return false;
				if (_try_composite(7, d, N, s)) return false;
				if (_try_composite(11, d, N, s)) return false;
				return true;
			}
			if (N < 2152302898747) {
				if (_try_composite(2, d, N, s)) return false;
				if (_try_composite(3, d, N, s)) return false;
				if (_try_composite(5, d, N, s)) return false;
				if (_try_composite(7, d, N, s)) return false;
				if (_try_composite(11, d, N, s)) return false;
				return true;
			}
			if (N < 3474749660383) {
				if (_try_composite(2, d, N, s)) return false;
				if (_try_composite(3, d, N, s)) return false;
				if (_try_composite(5, d, N, s)) return false;
				if (_try_composite(7, d, N, s)) return false;
				if (_try_composite(11, d, N, s)) return false;
				if (_try_composite(13, d, N, s)) return false;
				return true;
			}
			if (N < 341550071728321) {
				if (_try_composite(2, d, N, s)) return false;
				if (_try_composite(3, d, N, s)) return false;
				if (_try_composite(5, d, N, s)) return false;
				if (_try_composite(7, d, N, s)) return false;
				if (_try_composite(11, d, N, s)) return false;
				if (_try_composite(13, d, N, s)) return false;
				if (_try_composite(17, d, N, s)) return false;
				return true;
			}
			auto it = _primeSet.begin();
			for (auto i = 0; i < _precisionHighN; i++, it++)
				if (_try_composite(*it, d, N, s)) return false;
			return true;
		}
	};
};

class Problem1 {
public:
	Problem1() {
		solve(1000);
	}

	void solve(int N) {
		int result=0;
		for (int i = 1; i < N; i++) {
			if (i % 3==0 || i% 5==0) {
				result += i;
			}
		}
		cout << "The result is: " << result << endl;
	}
};

class Problem2 {

public:
	Problem2() {
		solve(4000000);
	}

	void solve(UInt N) {
		Utils::Fib fib;
		UInt Sum = 0;
		int i = 1;
		while (Sum < N) {
			UInt cur = fib.FibK(i);
			if (cur % 2 == 0)Sum += cur;
			i++;
		}
		cout << "Sum accumulated to " << Sum << endl;
	}

	

};

class Problem3 {
	// The sieve seems to be working nice, but the sqr(N) limit for it is a huge overkill. 
	// Maybe batch some primes and shrink the number with them until the highest emerges might be quickest.(Implemented batching for the sieve).
public:
	Problem3() {
		void solve();
	}
	void solve() {
		UInt num = 600851475143;
		UInt batch = 100;
		Utils::Sieve s(batch);

		UInt CurrRes = 3;
		while(num>1){
			for (auto p : s.primes) {
				while (num%p == 0) {
					CurrRes = p;
					num /= p;
				}
			}
			s.primes.clear();
			s.populate(s.curMax+batch);
			
		}
		cout << "Highest prime found: " << CurrRes << endl;
	}

};

class Problem5 {

public:
	void solve() {
		UInt res = 1;
		Utils::Sieve s(20);
		for (auto p : s.primes) {
			res *= p;
		}
		cout << "Result: " << 20*res << endl;
	}
};

class Problem7 {

public:
	static void solve() {
		UInt batch = 1000;
		Utils::Sieve s(batch);
		while (s.primes.size() < 10001) {
			s.populate(s.curMax + batch);
		}
		cout << "10001th prime is: " << s.primes[10000] << endl;
	}
};

class Problem9 {

};

class Problem43 {
	/*
		Sub string divisibility
	*/

	array<int,10> nums = { 0,1,2,3,4,5,6,7,8,9 };
	array<int, 7> divs = { 2,3,5,7,11,13,17 };

	UInt add() {
		UInt res = 0;
		UInt pot = 9;
		for (auto i : nums) res += i*pow(10, pot--);
		return res;
	}
	bool checkCurPerm() {
		if ((nums[1] * 100 + nums[2] * 10 + nums[3]) % divs[0] == 0)
			if ((nums[2] * 100 + nums[3] * 10 + nums[4]) % divs[1] == 0)
				if ((nums[3] * 100 + nums[4] * 10 + nums[5]) % divs[2] == 0)
					if ((nums[4] * 100 + nums[5] * 10 + nums[6]) % divs[3] == 0)
						if ((nums[5] * 100 + nums[6] * 10 + nums[7]) % divs[4] == 0)
							if ((nums[6] * 100 + nums[7] * 10 + nums[8]) % divs[5] == 0)
								if ((nums[7] * 100 + nums[8] * 10 + nums[9]) % divs[6] == 0)
									return true;
		return false;

	}

public:
	UInt solve() {
		UInt result = 0;
		for (int n = 1; n < Utils::fact(10); n++) {
			next_permutation(nums.begin(), nums.end());
			if (checkCurPerm()) result += add();
		}
		return result;
	}


};

class Problem44 {
public:
	bool isPent(UInt num) {
		// inverse function. Should give integer value for pentagon numbers
		double test = (sqrt(1 + 24 * num) + 1.0) / 6.0;
		return test == (int)test;
	}
	bool solve() {
		for (UInt N1 = 1;true;N1++) {
			UInt P1 = (3 * N1 * N1 - N1) / 2;
			for (UInt N2 = 1; N2 < N1; N2++) {
				UInt P2 = (3 * N2 * N2 - N2) / 2;
				if (isPent( P1 - P2) &&isPent(P1 + P2)) {
					cout << "Found a pair, P1: " << P1 << " P2: " << P2 << ". Their difference is: " << P1-P2 << "." << endl;
					return true;
				}
			}

		}
	}

};

class Problem45 {
	/*
		find the next triangle that is also pentagol and hexagonal.
		- assuming the reverse holds and try to calculate hexagonal numbers to find next.
	*/

public:
	static UInt solve() {
		UInt n = 143;
		while (true) {
			n++;
			UInt cand = n*(2*n - 1);
			if (Utils::Pentagonal(cand) && Utils::Triangle(cand)) {
				return cand;
			}
		}

	}
	
};

class Problem46 {
	Utils::Sieve s;
public:
	UInt solve() {
		s.populate(10000);
		for (UInt i = 33; true; i += 2) {
			if (s.primeMap[i]) continue;
			if (!conjecture(i)) return i;
		}
	}
	bool conjecture(UInt n) {
		int idx = -1;
		while (s.primes[++idx] < n) {
			double test = sqrt((n - s.primes[idx]) / 2);
			if (test == (int)test) return true;
		}
		return false;
	}
};

class Problem47 {
	/*
		First 4 consecutive numbers with 4 distinct factors.
	*/
public:

	static UInt solve() {
		
		Utils::Sieve s(130000);
		int streak = 0;
		const int consec = 4;
		UInt i = 10;
		UInt current;
		while (streak < consec) {
			if (Utils::distFactors(i++, s.primes)>=4) {
				streak++;
			}
			else {
				streak = 0;
				current = i;
			}
		}
		return current;



	}

};

class Problem49 {
	/*
		Find prime permutation that are arithmetically spaced.
		1000<primes<9999

		p1->p1+d->p1+2d

		0<d<5000

		1st intuition:
		start with a prime>1000. find all permutations that are prime. check for arithmetic progression.

		2nd intuition:
		when finding all primes, can throw current candidate if a lower prime permutation is found.
	*/

public:
	// 1789 1879 1987 8179 8719 8971 9187 9781 9817 9871
	
	void check_arith(set<UInt> set) {
		for (auto p : set) {
			for (UInt d = 1; d < 4000; d++) {
				if (set.count(p + d))
					if (set.count(p + 2 * d)){
						cout << "Reached 2 at " << p << " with d: " << d << endl;
						cout << p << p + d << p + 2 * d << endl;
					}
			}
		}
	}
	void Solve() {
		Utils::Sieve s(10000);
		
		//puts all primes into a vector
		vector<UInt> primes;
		for (UInt i = 1000; i < 10000; i++)
			if (s.primeMap[i])
				primes.push_back(i);
		
		for (auto p : primes) {
			set<UInt> candidates;
			candidates.insert(p);

			auto cand = to_string(p);
			for (int i = 1; i < 24; i++) {
				next_permutation(cand.begin(), cand.end());
				if (s.primeMap[stoi(cand)]) {
					candidates.insert(stoi(cand));
				}
			}
			if (p == *candidates.begin() && candidates.size()>2)
				check_arith(candidates);
		}
	}

	
};

template<UInt MAX>
class Problem50 {
	/* 
	
	Consecutive prime sum:
	-Which prime below 1M can be written as the sum of most consecutive primes.

	-
	
	1st intuition:
	start at beginning of table. Sum until > 1M. Record which is the longest result that ends in a prime. 
	Use this to work through whole table of primes.
	
	2nd intuition, work backwards:
	Start at beginnning. Sum all primes from this until > 1M.
	Remove primes from sum until it is a prime.
	
	3rd intuition, limitation:
	Assume the sequence end is below a limit relative to max sum. 
	Below 100, 6 primes with average 7. Below 1000,20 primes with average 50. 
	Assuming approx. 500 primes with 2000 average. Populating list with primes below 10000.

	*/
public:

	UInt Solve() {
		Utils::Sieve mySieve(MAX);
		UInt curLen = 0;
		UInt curSum = 0;
		for (auto seqStart = mySieve.primes.begin(); seqStart < mySieve.primes.end()-curLen; seqStart++) {
			auto curPrime = seqStart;
			auto sum = *curPrime;

			while ( sum < MAX) {
				curPrime++;
				sum += *curPrime;
			}
			while (!mySieve.primeMap[sum]) {
				sum -= *curPrime;
				curPrime--;
			}
			auto length = (UInt)(curPrime - seqStart) + 1;
			if (length > curLen) {
				curLen = length;
				curSum = sum;
				//cout << "Found a new max sum: " << sum << endl;
			}
		}
		return curSum;
	}
	
	

};

class Problem51 {
	/* Prime Digit Replacements - How many primes by replacing part of number by same digit.
	
	1st intuition:
	Need to test all non-trivial cases. D = roof(log(N)) digits. sum(binom(D,k)) from k=1 to k=D-1 non-trivial replacement patterns.

	2nd iniution:
	Make a mask for the number of replacements and permute it? Straight permutation of masks into a container will make duplicates for 2+ replacement patterns.
	Make a permutation set, that won't carry the duplicates? These sets would be general and can be made once for each D.

	Assuming the right replacement pattern, which is basicly the solution, is unique. So, we can make one big set of permutations, or some vector of sets that divides on digit length. Depends on what makes the logic work best.

	A set for each digit length makes sense i think. x denotes replacement, o denotes leave as is.

	3rd intuition:
	Moving away from the idea of permutating masks, instead i'll just recursively make all the different masks.

	Giving up for now. Runs endlessly for some reason i can't find. Maybe revisit this later.
	*/

	struct Res{
		UInt best;
		UInt prime;

		Res(UInt b, UInt p) {
			best = b;
			prime = p;
		}
			
	};
	
	Res branch(UInt level, UInt Mask, UInt D, Utils::Sieve s) {
		if (level > 0) {
			Mask *= 10;
			Res br1 = branch(level - 1, Mask, D, s);
			Res br2 = branch(level - 1, Mask+1, D, s);
			if (br1.best > br2.best)
				return br1;
			else
				return br2;
		}
		else{
			if (Mask == 0) {
				
				return Res(1,1);
			}
			
			Res best = Res(1, 1);
			string strMask = to_string(Mask);
			while (strMask.size() < D)strMask = '0' + strMask;
			UInt amount = strMask.find('1');
			UInt limit = pow(10, D - amount);
			for (int num = 1;num<limit; num++) {
				
				UInt base = 9*Mask;
				for (int ind = 0; ind < D; ind++) {
					if (strMask[D-1-ind] == '0') {
						base += num % 10 * (UInt)pow(10, ind);
						num /= 10;
					}
				}

				int nPrimes = 0;
				vector<UInt> primes;
				for (int i = 0; i < 10; i++) {
					
					if (s.primeMap[base]) {
						nPrimes++;
						primes.push_back(base);
					}
					base -= Mask;
				}

				if (nPrimes > best.best) {
					best.best = nPrimes;
					best.prime = primes[nPrimes-1];
					if (best.best > 3) {
						cout << "Result of " << best.best << " with " << best.prime << " being the lowest prime." << endl;
					}
				}
			}
			return best;
		}
	}


public:

	void Solve() {
		Utils::Sieve s(200000);
		Res MaxRes = Res(1,1);

		Res curres = branch(2, 0, 2, s);
		if (curres.best > MaxRes.best) {
			MaxRes = curres;
			cout << "New best: " << MaxRes.best << " primes, with " << MaxRes.prime << " as lowest prime." << endl;
		}			
	}
};
class Problem53 {
	/* Combinatoric selections.

	1st Intuition:
	N rows , times 1/2 N elements, times N * 1/4 * N * 1/4 N for each C. Also the problem of >50! becoming really large. Not even going to try brute force.
	
	Only have to find what element is the first to exceed 1M

	2nd intuition:
	Work from the side in a growing way. Each step seems to be dividing by position and multiplying by base-position+1.

	*/

public:
	UInt Solve() {

		UInt nCk, base, pos;
		bool running = false;
		UInt res = 0;
		for (int i = 23; i <= 100; i++) {			
			nCk = base = i;
			pos = 2;
			running = true;
			while (pos <= i - pos && running) {
				nCk = nCk*(--base) / (++pos-1);
				if (nCk > pow(10, 6)) {
					res+= i + 1 - (2 * (pos - 1));
					running = false;
				}
			}		
		}
		return res;
	}

};
class Problem54 {

	enum rank{high,pair,twoPair,triple,straight,flush,house,quad,s_flush,r_flush};
	class hand {
		rank r;
		vector<int> level;
	};

	hand eval(string s) {
		hand res;
		if (s[2] == s[5] && s[2] == s[8] && s[2] == s[11]) {
		}
	}

};

class Problem69 {
private:
	Utils::Sieve s;
public:
	UInt Solve(UInt Max) {

	}


};

class Problem604 {
private:
	/*	1398582231100 - The result the original solve gave me after 12 hours.
		1398582231101 - The actual number. Which i suspected would be the case when it finished the number would be missing a small amount from the ideal.
		2145000 -		The largest delX candidate i wrote to screen.

		The other solutions posted at project forum use a technique called euler's totient function, which I try and to implement in solve2. 
		
	*/
	// Utils::Sieve s;
public:

	static UInt solve(UInt N) {
		// Finding the number of lattice points a strictly convex path can cross in a NxN square.
		// Initializing with the subsolution of a 1x1 square which have the trivial solution of two lattice points.
		
		// The routince works by adding all the unique angles that can be composed by a certain length of squares.
		// Imagine a triangle made by a piece of thread across a nail, the slope can be altered by sliding the thread.
		// The same way the routine tests which slopes can be produced with a certain length and add if the uniqueness test using the gcd holds.
		// 
		// Euler's totient function should give these unique triangles by default.


		UInt cumulX = 1;	// 
		UInt cumulY = 1;	// 
		UInt lattice = 2;	// the number of lattices accumulated
		UInt fails = 0;
		UInt limit = 3;
		UInt stride;


		for (UInt sum = 3;; sum++) {
			//if (sum % 1000 == 0) {
			//	cout << "Reached " << sum << ". Estimated: " <<100*(double)cumulX/(double)N<< "% progression." << endl;
			//}
			if (sum % 2 == 0) {
				stride = 2;
			}
			else stride = 1;
			
			for (UInt j = 1; j <= sum / 2; j+=stride) {
				if (Utils::gcd(sum - j, j) == 1) {
					if (cumulX + (sum - j) <= N && cumulY + j <= N) {
						cumulX += (sum - j);
						cumulY += j;
						lattice++;
					}
					else {
						if (++fails > limit) return lattice;
					}
					if (cumulX + j< N && cumulY + (sum - j) < N) {
						cumulX += j;
						cumulY += (sum - j);
						lattice++;
					}
					else {
						if (++fails > limit) return lattice;
					}
				}
			}
		}
	}
	static UInt solve2(UInt N) {
		cout << "Solving for N  = " << N << endl;
		cout << "Populating sieve..." << endl;
		Utils::Sieve s(2500000);
		cout << "Sieve populated. Finding solution..." << endl;
		
		UInt lattice = 2;	// the number of lattices accumulated
		UInt len = 1;
		for (UInt candidate=3; ;candidate++) {
			auto phi = Utils::phi(candidate, s);
			if(phi * candidate + len <= N ){
				lattice += phi;
				len += phi/2 * candidate;
			}
			else {
				while (len + candidate/2 <= N) {
					lattice++;
					len += candidate/2;
				}
				return lattice;
			}
		}
	}

};

class Problem621 {
private:
	UInt N = 17526000000000ULL;
	
public:

	double inverse(UInt num) {
		// reverse triangular number calculation.
		return (sqrt(8 * num + 1) - 1) / 2;
	}
	bool isTriangular(UInt num) {
		// inverse function
		auto inv = sqrt(8 * num + 1);

		// return true if fractional part == 0
		double intpart;
		return modf(inv, &intpart) == 0.0;
	}
	UInt getAmount(UInt Tx) {
		// Function for finding the amount of triangular number triplets that sum to N given Tx.
		// 
		// NB! Currently stripped for logic for discerning (Tx + 2 * Ty = N) variants, 
		// since N from Euler problem does not contain these and approach is currently based on brute force.
		UInt amount = 0;
		auto remainder = N - Tx;

		// check if Tz is triangular for every Ty, while Ty <= remainder. 
		for (UInt y = 0, Ty = 0; Ty <= remainder / 2; Ty += ++y) {
			auto Tz = remainder - Ty;

			// Skip Tz > Tx to avoid duplicates through symmetry(and sloppy work with boundaries).
			if (Tz > Tx)continue;
			
			// if inverse test passes, then add the 6 permutations of the 3 Triangular numbers.
			if (isTriangular(Tz)) amount += 6;
		}
		return amount;
	}

	UInt Solve_mthread() {
		
		//boundaries such that Tx >= Tz + Ty and Tx <= N
		auto start = (UInt)ceil(inverse(N / 3));
		auto Tn = start*(start + 1) / 2;
		
		//Populate Tx vector with triangular numbers.
		auto Tx = vector<UInt>();
		for (UInt x = start; Tn <= N; Tn += ++x)	Tx.push_back(Tn);

		//create the result vector, a place where parallel_transform can safely dump the results from getAmount.
		vector<int> results(Tx.size());
		concurrency::parallel_transform(Tx.begin(), Tx.end(), results.begin(), [&](UInt tx) { return getAmount(tx); });
		
		//return the sum of the result vector.
		return accumulate(results.begin(),results.end(),(UInt)0);
	}
};

class Problem622 {
private:
	UInt num = 1152921504606846976ULL;
	UInt blocks = 1024ULL;
	UInt end = 1073741824ULL;
	UInt blockSize = end / blocks;
	UInt twos[6] = { 63, 1023, 4095, 32767, 1048575, 1073741823 };
public:
	UInt getQuadCandidates(UInt start) {
			UInt res = 0;
			for (auto NUM = start; NUM < start + blockSize; NUM += 2) {
				if (num % (NUM - 1) == 1) {
					if (twos[0] % (NUM - 1) == 1) continue;
					if (twos[1] % (NUM - 1) == 1) continue;
					if (twos[2] % (NUM - 1) == 1) continue;
					if (twos[3] % (NUM - 1) == 1) continue;
					if (twos[4] % (NUM - 1) == 1) continue;
					if (twos[5] % (NUM - 1) == 1) continue;
					res += NUM;
				}
			}
		return res;
	}
	UInt Solve() {
		auto NxQ = vector<UInt>();
		
		auto blockSize = end / blocks;
		for (UInt Nx = 30; Nx <= end; Nx += blockSize)	NxQ.push_back(Nx);
		//cout << NxQ.size() << endl<<endl;
		vector<UInt> results(NxQ.size());
		concurrency::parallel_transform(NxQ.begin(), NxQ.end(), results.begin(), [&](UInt NxQ) { return getQuadCandidates(NxQ); });
		
		return accumulate(results.begin(), results.end(), (UInt)0);
	}
};

int main(int argc, char *argv[])
{
	
	auto start = chrono::steady_clock::now();
	Problem622 p622;
	auto result = p622.Solve();
	auto end = chrono::steady_clock::now();
	cout << "Execution took: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << "ns, or " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms." << endl;
	cout << "Solution is: " << result << endl;


	return 0;
}

