#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>
#include "partdist.hpp"
using namespace std;

//to compile: g++ partdist.cpp Lmunkres.cpp BipartiteGraph.cpp Hungarian.cpp -o partdist


/***************GLOBAL VARIABLES*****************/


/***************SUBROUTINES*****************/
//convert the string defining the partition from the command line into a vector containing the same.
vector<int> strtovec(std::string foo)
{
	//replace the commas with spaces in partitions
	std::replace(foo.begin(), foo.end(), ',', ' ');

	//stream foo into vector 'result' using iterators and back inserter trick
	std::vector<int> result;
	std::istringstream inputStream(foo);
	std::copy(std::istream_iterator<int>(inputStream),
          std::istream_iterator<int>(),
          std::back_inserter(result));

	return result;
}

//change a partition that starts at >1 to a partition that starts at 0
//then make all class values consecutive, i.e. 0,1,2,3, not 0,1,3,4, so that the vector.size()
//is the same as max_element() + 1
vector<int> zeroInd(vector<int> gen)
{
	int correctionfactor;
	vector<int> genZ;

	int amin = ( *min_element(gen.begin(),gen.end()) );
	correctionfactor = (0 - amin);
	
	//zero index the class values 
	for (unsigned int i=0;i<gen.size();i++)
	{
		genZ.push_back( gen[i]+correctionfactor );
	}
	
	//test whether values are consecutive
	vector<int> genZSort = genZ;
	sort( genZSort.begin(), genZSort.end() ); //sort copy of vector genZ

	vector<int> genZUniq = genZSort;
	genZUniq.erase( unique( genZUniq.begin(), genZUniq.end() ), genZUniq.end() ); //reduce to unique values
	
	int amax = ( *max_element(genZUniq.begin(), genZUniq.end()) ); //get the maximum value of the zero indexed vector

	vector<int> translateVec = genZ;  //holds zeroed partition with consecutive values
	if ( (amax + 1) != genZUniq.size() ) //if largest value +1 does not equal vector size, they can't be consecutive
	{
		//clear out genZ values from translateVec
		translateVec.clear();
		for (unsigned int i=0;i<genZ.size();i++)
		{
			for (unsigned int j=0;j<genZUniq.size();j++)
			{
				if (genZ[i] == genZUniq[j]) 
				{
					translateVec.push_back(j);
					break;
				}
			}
		
		}		
	
	}
	
	return translateVec;
}

//normalize pairwise partition distance matrix using maximum partition distance possible
//uses formulas for maximum "transfer distance" from Charon et al. 2006, Journal of Classification 23:103
double normpd(vector<pair<int, int> > pqmatrix, int n, int cost)
{
	int envmax, genmax;
	double p, q, c, pdmax;
		
	//determine p and q
	envmax = pqmatrix[0].first;
	genmax = pqmatrix[0].second;
	
	if (envmax < genmax)
	{
		p = double(envmax);
		q = double(genmax);
	}
	else
	{
		p = double(genmax);
		q = double(envmax);
	}

	//calculate max possible partition distance, 3 cases
	if (n <= (p + q - 2)) 
	{
		pdmax = ( (2 * n) - p - q); 
		//cout << "case 1, pdmax=" << pdmax << endl;
	}											 
	else if ( ((p + q - 1) <= n) && (n <= ((p - 1) * q)) )
	{
		pdmax = ( n - (ceil ((n + q - p) / q)) );
		//cout << "case 2, pdmax=" << pdmax << endl;
	}
	else if ( ((p - 1) * q) < n  )
	{
		pdmax = ( n - (ceil (n / q)) );
		//cout << "case 3, pdmax=" << pdmax << "n/q=" << n/q <<endl;
	}
	else 
	{
		cout << "Conditions for normalizing the partition distance not met.  Quitting...\n";
		return EXIT_FAILURE;
	}
	
	cout << "pdmax=" << pdmax << "\n";
	
	//normalize the pd
	c = ( cost / pdmax );
						

	return c;

}

/***************MAIN*****************/
int main( int argc, char* argv[] )

//int partdist( vector<int> env, vector<int> gen )
//int partdist( vector<int> env, vector<int> gen, ofstream& outf, vector<pair<int, int> >& pqmatrix )
{
	//extract the partitions from the command line
	const char* e = argv[1];
	const char* g = argv[2];
	
	//convert to string
	std::string ein(e);
	std::string gin(g);

	cout << "ein>" << ein << "<\n";
	cout << "gin>" << gin << "<\n";
	
	//load the space-delimited string into a vector<int>
	std::vector<int> gen = strtovec(gin);
	std::vector<int> env = strtovec(ein);
	
	//test whether the partitions hold the same number of values. if not, quit, because it
	//makes no sense to calculate pd in this case
	if (gen.size() != env.size())
	{
		cout << "ERROR: Partitions do not hold the same number of elements. Quitting...\n";
		return EXIT_FAILURE;
	}	

	cout << "env.size()>" << env.size() << "<\n";
	for (unsigned int i=0; i<env.size(); ++i) {cout << env[i] << " : ";}
	cout << "\n";

	cout << "gen.size()>" << gen.size() << "<\n";
	for (unsigned int i=0; i<gen.size(); ++i) {cout << gen[i] << " : ";}
	cout << "\n";
	
	//zero index partition coding in env, gen.  make values consecutive.
	vector<int> genZ, envZ;
	genZ = zeroInd(gen);
	envZ = zeroInd(env);

	vector<int> a = envZ;
	vector<int> b = genZ;
	
	
	cout << "env  ";
	for (unsigned int k=0;k<a.size();k++) cout << a[k];
	cout << endl << "gen  ";
	for (unsigned int k=0;k<b.size();k++) cout << b[k];
	cout << endl;
	
		
	//identify largest cluster number in either partition (this is the maximum number of clusters, minus one, because partition is now zero-indexed)
	int maxP;
	int amax = ( *max_element(a.begin(),a.end()) ); //get maximum value of vectors a, b.  must * (dereference) to get value instead of iterator
	int bmax = ( *max_element(b.begin(),b.end()) ); 
	if (amax >= bmax) maxP = amax;
	else maxP = bmax;
	
	//test whether both partitions have only one cluster defined in them. quit if so, because
	//it doesn't make sense to compute the pd in this case.
	if (maxP == 0)
	{
		cout << "ERROR: Both partitions have only one cluster. Quitting...\n";
		return EXIT_FAILURE;
	}
 
	//convert single string partition coding to multiple string binary coding
	vector<vector<int> > A(maxP+1);
	vector<vector<int> > B(maxP+1);
	
	for (unsigned int j=0; j<(maxP+1); j++)
	{
		for (unsigned int i=0; i<a.size(); i++)
		{
			if (a[i] == j) 
			{
				A[j].push_back(1);
				//cout << "a[i]=" << a[i] << "   1	" << A[j][i] << "\n";
			}
			else 
			{
				A[j].push_back(0);
				//cout << "a[i]=" << a[i] << "   0	" << A[j][i] << "\n";
			}
				
			if (b[i] == j) 
			{
				B[j].push_back(1);
				//cout << "b[i]=" << b[i] << "   0	" << B[j][i] << "\n";
			}
			else 
			{
				B[j].push_back(0);
				//cout << "b[i]=" << b[i] << "   0	" << B[j][i] << "\n";
			}
		}
	}
	
	//get Bbar, the complement (inverse) of B
	vector<vector<int> > Bbar(maxP+1);
	for (unsigned int i=0;i<Bbar.size();i++)
	{
		for (unsigned int j=0;j<a.size();j++)
		{
			if (B[i][j] == 0) Bbar[i].push_back(1);
			else Bbar[i].push_back(0);
		}
	}
	
	//get the intersection of A and Bbar
	//vector<vector<vector<int> > > intx(maxP+1, maxP+1); //3D vector
	vector<vector<vector<int> > > intx(maxP+1, vector<vector<int> >(maxP+1)); //3D vector
	for (unsigned int i=0;i<A.size();i++)
	{
		for (unsigned int j=0;j<Bbar.size();j++)
		{
			for (unsigned int k=0;k<a.size();k++)
			{
				if (A[i][k] == Bbar[j][k] && A[i][k] == 1) 
				{
					intx[i][j].push_back(1);
				}
				else intx[i][j].push_back(0);
			}
		}
	}
	
	//sum the values in the intersection of A and Bbar
	int m;
	vector<vector<int> > sumx(maxP+1);
	for (unsigned int i=0;i<A.size();i++)
	{
		for (unsigned int j=0;j<Bbar.size();j++)
		{
			m=0;
			for (unsigned int k=0;k<a.size();k++)
			{
				if (intx[i][j][k] == 1) m++;	
			}
			sumx[i].push_back(m);
		}
	}

	//Solve the minimum weighted assignment problem using Liu's program which
	//uses the bipartite graph approach to Kuhn-Munkres algorithm
	int cost;
	cost = Lmunkres(sumx);
	//cost = Lmunkres(sumx, outf);
		
	cout << "pd=" << cost << "\n";
	
	//normalize the partition distance to the maximum value possible given the partitions
	//add paired max number of subsets to pqmatrix 
	vector<pair<int, int> > pqmatrix;
	pqmatrix.push_back( make_pair(amax+1, bmax+1) );
	int n = gen.size(); //n is the number of samples in the partition
	//calculate the max number of partitions, then normalize the pd
	double npd = normpd(pqmatrix, n, cost);
	
	cout << "npd=" << npd << "\n";




	return 0;
}
