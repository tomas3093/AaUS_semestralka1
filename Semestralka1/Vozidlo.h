#pragma once
#include "types.h"
#include "Datum.h"

// Parametre jednotlivych typov vozidiel
const int VOZIDLO_TYP_ZEM_HRANOLKY_NOSNOST = 5000;		// Kg
const int VOZIDLO_TYP_ZEM_LUPIENKY_NOSNOST = 2000;		// Kg
const int VOZIDLO_TYP_ZEM_HRANOLKY_NAKLADY_DEN = 100;	// Eur
const int VOZIDLO_TYP_ZEM_LUPIENKY_NAKLADY_DEN = 70;	// Eur

/// <summary> Trieda reprezentujuca vozidlo na rozvoz tovaru. </summary>
class Vozidlo
{
public:
	/// <summary> Konstruktor. </summary>
	Vozidlo();

	/// <summary> Konstruktor. </summary>
	Vozidlo(string spz, Tovar::Typ typTovaru, size_t datumZaradenia);

	/// <summary> Konstruktor. </summary>
	Vozidlo(string spz, Tovar::Typ typTovaru, size_t datumZaradenia, size_t prevadzkoveNaklady);

	/// <summary> Destruktor. </summary>
	~Vozidlo();

	/// <summary> Zvysi prevadzkove naklady vozidla o zadanu hodnotu. </summary>
	void zvysPrevadzkoveNaklady(size_t nakladyNaZvysenie) { prevadzkoveNaklady_ += nakladyNaZvysenie; }

	string dajSpz() { return spz_; }
	Tovar::Typ dajTyp() { return typTovaru_; }
	size_t dajPrevadzkoveNaklady() { return prevadzkoveNaklady_; }
	Datum dajDatumZaradenia() { return datumZaradenia_; }
	size_t dajNosnostVozidla();
	size_t dajJednotkoveNaklady();

	/// <summary> Zapise vozidlo do suboru. </summary>
	void zapisSa(ofstream * outFile);

	/// <summary> Nacita vozidlo zo suboru. </summary>
	void nacitajSa(ifstream * inFile);

private:
	/// <summary> Nazov vozidla - SPZ </summary>
	string spz_;

	/// <summary> Typ vozidla. </summary>
	Tovar::Typ typTovaru_;

	/// <summary> Celkove naklady na prevadzku vozidla. </summary>
	size_t prevadzkoveNaklady_;

	/// <summary> Datum zaradenia do evidencie. </summary>
	size_t datumZaradenia_;
};


inline Vozidlo::Vozidlo()
	:spz_(""), typTovaru_(Tovar::Typ::ZEM_LUPIENKY), prevadzkoveNaklady_(0), datumZaradenia_(0)
{
}

inline Vozidlo::Vozidlo(string spz, Tovar::Typ typTovaru, size_t datumZaradenia)
	:spz_(spz), typTovaru_(typTovaru), prevadzkoveNaklady_(0), datumZaradenia_(datumZaradenia)
{
}

inline Vozidlo::Vozidlo(string spz, Tovar::Typ typTovaru, size_t datumZaradenia, size_t prevadzkoveNaklady)
	: spz_(spz), typTovaru_(typTovaru), datumZaradenia_(datumZaradenia), prevadzkoveNaklady_(prevadzkoveNaklady)
{
}

inline Vozidlo::~Vozidlo()
{
}

inline size_t Vozidlo::dajNosnostVozidla()
{
	switch (typTovaru_)
	{
	case Tovar::Typ::ZEM_LUPIENKY:
		return VOZIDLO_TYP_ZEM_LUPIENKY_NOSNOST;
	case Tovar::Typ::ZEM_HRANOLKY:
		return VOZIDLO_TYP_ZEM_HRANOLKY_NOSNOST;
	}
	return 0;
}

inline size_t Vozidlo::dajJednotkoveNaklady()
{
	switch (typTovaru_)
	{
	case Tovar::Typ::ZEM_LUPIENKY:
		return VOZIDLO_TYP_ZEM_LUPIENKY_NAKLADY_DEN;
	case Tovar::Typ::ZEM_HRANOLKY:
		return VOZIDLO_TYP_ZEM_HRANOLKY_NAKLADY_DEN;
	}
	return SIZE_MAX;
}

inline void Vozidlo::zapisSa(ofstream* outFile)
{
	*outFile << spz_ << endl;
	*outFile << Tovar::toNumber(typTovaru_) << endl;
	*outFile << prevadzkoveNaklady_ << endl;
	*outFile << datumZaradenia_ << endl;
}

inline void Vozidlo::nacitajSa(ifstream* inFile)
{
	*inFile >> spz_;

	size_t typ;
	*inFile >> typ;
	typTovaru_ = Tovar::toTyp(typ);

	*inFile >> prevadzkoveNaklady_;
	*inFile >> datumZaradenia_;
}

