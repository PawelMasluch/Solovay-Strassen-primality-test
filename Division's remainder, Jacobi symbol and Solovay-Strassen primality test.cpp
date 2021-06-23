#include<iostream>
#include<ctime>


using namespace std;


typedef long long LL;


#define REP(i,a,b) for(LL i=a; i<=b; ++i)


// a mod b, where a - any integer, b - any non-zero integer
LL mod(LL a, LL b)
{
	return ( a >= 0 )  ?  ( a - ( ( a / abs(b) ) * abs(b) ) )  :  ( a + ( ( ( abs(a) + abs(b) - 1 ) / abs(b) ) * abs(b) ) )  ;
}


// a*b (mod m).
// Assumptions: a,b >= 0, m > 0
LL multiplyModulo(LL a, LL b, LL m){
	
	a %= m;
	b %= m;
	
	LL res = 0;
	
	while ( b > 0 ){
		if( b % 2 == 1 ){
			res = ( res + a ) % m;
		}
		
		a = ( a+a ) % m;
		
		b /= 2;
	}
	
	return res % m;
}


// a^k (mod m).
// Assumptions: k >= 0, a,m > 0
LL fastPowerModulo(LL a, LL k, LL m){
	
	a %= m;
	
	LL res = 1;
	
	while ( k > 0 ){
		if( k % 2 == 1 ){
			res = multiplyModulo(res, a, m);
		}
		
		a = multiplyModulo(a, a, m);
		
		k /= 2;
	}
	
	return res % m; 
}


// Jacobi symbol (a/n).
// n - any integer(!)
// k - positive odd integer(!)

// Source:
// https://en.wikipedia.org/wiki/Jacobi_symbol
int Jacobi(LL n, LL k){
	
	n = mod( n, k );
	int r;
	int t = 1;
	
	while( n != 0 ){
		while( mod(n, 2) == 0 ){
			n /= 2;
			r = mod(k, 8);
			
			if( r == 3  ||  r == 5 ){
				t = -t;
			}
		}
		
		swap( n, k );
		
		if( mod(n, 4) == 3  && mod(k, 4) == 3 ){
			t = -t;	
		}
		
		n = mod( n, k );
	}
	
	if( k == 1 ){
		return t;
	}
	else{
		return 0;
	}
}



// Solovay-Strassen primality test + additional cases.
// 0 <= n <= 4*10^18 - an integer to be checked
// numberOfTests - number of tests (by default: numberOfTests = 50)
bool isPrimeSolovayStrassen(LL n, int numberOfTests=50){
			
			/* Additional cases. */
			
			if( n == 0 || n == 1 ) {
				return false;
			}
			
			if( n == 2 ){
				return true;
			}
			
			if( n % 2 == 0  &&  n > 2 ){
				return false;
			}
			
			
			// ---------------------------------
			
			
			/* A main part of the algorithm - Solovay-Strassen primality test. */
			
			// Sources:
			// https://pl.wikipedia.org/wiki/Test_pierwszo%C5%9Bci_Solovaya-Strassena
			
			srand( time(NULL) );
			
			//cout << "\nn=" << n << endl;
			
			REP(i,1,numberOfTests){ // for each test
				//cout << endl << "Test nr " << i << endl;
				
				LL a = 2 + rand() % (n-2); // a in {2, ..., n-1}
				//cout << "a=" << a << endl;
				
				int x = Jacobi(a,n);
				//cout << "x=Jacobi(a,n)=" << x << endl;
				
				if( x == 0  ||  fastPowerModulo(a, (n-1)/2, n) != mod(x,n) ){
					//cout << "Dla testu nr " << i << " zwrocono falsz\n";
					return false; // n - composite
				}
			}
			
			return true; // n - probably prime
		}



int main(){
	
	// Testy symbolu Jacobiego
	REP(a,0,10){
		REP(n,1,5){
			cout << "(" << a << "/" << 2*n-1 << ")" << "= " << Jacobi(a,2*n-1) << endl;
		}
		cout << endl;
	}
	cout << endl << endl;
	
	
	// Testy metody Solovay'a-Strassena
	REP(n,0,100){
		if( isPrimeSolovayStrassen(n) == true ){
			std::cout << "Liczba " << n << " jest prawdopodobnie pierwsza\n";
		}
		else{
			std::cout << "Liczba " << n << " nie jest pierwsza\n";
		}
	}
	
	
	return 0;	
}
