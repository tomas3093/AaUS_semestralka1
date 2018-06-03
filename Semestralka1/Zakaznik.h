#pragma once

#include "types.h"

/// <summary> Trieda reprezentujuca zakaznika firmy. </summary>
class Zakaznik
{
public:
	/// <summary> Konstruktor. </summary>
	Zakaznik();

	/// <summary> Konstruktor. </summary>
	Zakaznik(string nazov, size_t region);

	/// <summary> Destruktor. </summary>
	~Zakaznik();

	string dajNazov() { return nazov_; }
	size_t dajRegion() { return region_; }

	/// <summary> Zapise biofarmara do suboru. </summary>
	void zapisSa(ofstream * outFile);

	/// <summary> Nacita biofarmara zo suboru. </summary>
	void nacitajSa(ifstream * inFile);

private:
	/// <summary> Nazov zakaznika. </summary>
	string nazov_;

	/// <summary> Adresa zakaznika - cislo regionu. </summary>
	size_t region_;
};


inline Zakaznik::Zakaznik()
	:nazov_(""), region_(-1)
{
}

inline Zakaznik::Zakaznik(string nazov, size_t region)
	:nazov_(nazov), region_(region)
{
}


inline Zakaznik::~Zakaznik()
{
}

inline void Zakaznik::zapisSa(ofstream* outFile)
{
	*outFile << nazov_ << endl;
	*outFile << region_ << endl;
}

inline void Zakaznik::nacitajSa(ifstream* inFile)
{
	*inFile >> nazov_;
	*inFile >> region_;
}
