#ifndef CONFIG_HPP 
#define CONFIG_HPP
#include <sstream>
#include <string>
#include <cstdlib>
using namespace std;
static const unsigned int WIDTH = 800; 
static const unsigned int HEIGHT = 600; 
static const unsigned int BPP = 32; 
static bool cargada=false;
static bool cargada2=false;
struct Puntajes{int puntaje=0; char nombre[11]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};};
template <typename T>
string ToString(T val){
	stringstream stream;
	stream << val;
	return stream.str();
}
#endif // CONFIG_HPP 
	
