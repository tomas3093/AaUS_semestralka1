#pragma once
#include "UdajePolotovar.h"

/// <summary> Trieda reprezentuje mnozstvo daneho polotovaru. </summary>
class MnozstvoPolotovaru
{
public:
	MnozstvoPolotovaru();
	MnozstvoPolotovaru(Polotovar::Typ typPolotovaru, double mnozstvo);
	~MnozstvoPolotovaru();

	Polotovar::Typ dajTypPolotovaru() { return typPolotovaru_; }
	double dajMnozstvo() { return mnozstvo_; }

	/// <summary> Zmeni aktualne mnozstvo zasoby o zadane mnozstvo. Ak by bolo 
	///vysledne mnozstvo zaporne, tak nastavi nulove mnozstvo. </summary>
	void zmenMnozstvo(double kolko);

	/// <summary> Zapise biofarmara do suboru. </summary>
	void zapisSa(ofstream * outFile);

	/// <summary> Nacita biofarmara zo suboru. </summary>
	void nacitajSa(ifstream * inFile);

private:
	Polotovar::Typ typPolotovaru_;
	double mnozstvo_;
};


inline MnozstvoPolotovaru::MnozstvoPolotovaru()
	:typPolotovaru_(Polotovar::Typ::OCHUCOVADLA), mnozstvo_(0)
{
}

inline MnozstvoPolotovaru::MnozstvoPolotovaru(Polotovar::Typ typPolotovaru, double mnozstvo)
	:typPolotovaru_(typPolotovaru), mnozstvo_(mnozstvo)
{
}


inline MnozstvoPolotovaru::~MnozstvoPolotovaru()
{
}

inline void MnozstvoPolotovaru::zmenMnozstvo(double kolko)
{
	if (mnozstvo_ + kolko <= 0)
	{
		mnozstvo_ = 0;
	}
	else
	{
		mnozstvo_ += kolko;
	}
}

inline void MnozstvoPolotovaru::zapisSa(ofstream* outFile)
{
	*outFile << Polotovar::toNumber(typPolotovaru_) << endl;
	*outFile << mnozstvo_ << endl;
}

inline void MnozstvoPolotovaru::nacitajSa(ifstream* inFile)
{
	int typPolotovaru;
	*inFile >> typPolotovaru;
	typPolotovaru_ = Polotovar::toTyp(typPolotovaru);

	*inFile >> mnozstvo_;
}
