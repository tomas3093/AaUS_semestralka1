#pragma once
#include "Datum.h"
#include "BioFarmar.h"
#include "EvidenciaBioFarmarov.h"

/// <summary> Trieda reprezentujuca objednavku polotovaru od dodavatela. </summary>
class ObjednavkaPolotovaru
{
public:
	/// <summary> Konstruktor. </summary>
	ObjednavkaPolotovaru();

	/// <summary> Konstruktor. </summary>
	ObjednavkaPolotovaru(Datum datumObjednania, BioFarmar * dodavatel, Polotovar::Typ typPolotovaru, 
	double mnozstvo, double jednotkovaNakupnaCena);

	/// <summary> Destruktor. </summary>
	~ObjednavkaPolotovaru();

	Datum dajDatumObjednania() { return datumObjednania_; }
	BioFarmar * dajDodavatela() { return dodavatel_; }
	Polotovar::Typ dajTypPolotovaru() { return typPolotovaru_; }
	double dajMnozstvo() { return mnozstvo_; }
	double dajJednotkovuNakupnuCenu() { return jednotkovaNakupnaCena_; }

	/// <summary> Zapise objednavku do suboru. </summary>
	void zapisSa(ofstream * outFile);

	/// <summary> Nacita objednavku zo suboru. </summary>
	void nacitajSa(ifstream * inFile, EvidenciaBioFarmarov * biofarmari);

private:
	Datum datumObjednania_;
	BioFarmar * dodavatel_;
	Polotovar::Typ typPolotovaru_;
	double mnozstvo_;
	double jednotkovaNakupnaCena_;
};


inline ObjednavkaPolotovaru::ObjednavkaPolotovaru()
	:datumObjednania_(0), dodavatel_(nullptr), typPolotovaru_(Polotovar::Typ::OCHUCOVADLA), mnozstvo_(0),
	jednotkovaNakupnaCena_(0)
{
}

inline ObjednavkaPolotovaru::ObjednavkaPolotovaru(Datum datumObjednania, BioFarmar * dodavatel, 
	Polotovar::Typ typPolotovaru, double mnozstvo, double jednotkovaNakupnaCena)
	:datumObjednania_(datumObjednania), dodavatel_(dodavatel), typPolotovaru_(typPolotovaru), mnozstvo_(mnozstvo),
	jednotkovaNakupnaCena_(jednotkovaNakupnaCena)
{
}


inline ObjednavkaPolotovaru::~ObjednavkaPolotovaru()
{
}

inline void ObjednavkaPolotovaru::zapisSa(ofstream* outFile)
{
	*outFile << datumObjednania_ << endl;

	string nazovBioFarmara = dodavatel_->dajNazov();
	*outFile << nazovBioFarmara << endl;

	*outFile << Polotovar::toNumber(typPolotovaru_) << endl;
	*outFile << mnozstvo_ << endl;
	*outFile << jednotkovaNakupnaCena_ << endl;
}

inline void ObjednavkaPolotovaru::nacitajSa(ifstream* inFile, EvidenciaBioFarmarov * biofarmari)
{
	int datum;
	*inFile >> datum;
	datumObjednania_ = datum;

	string nazovBioFarmara;
	*inFile >> nazovBioFarmara;
	dodavatel_ = biofarmari->dajFarmara(nazovBioFarmara);

	int typPolotovaru;
	*inFile >> typPolotovaru;
	typPolotovaru_ = Polotovar::toTyp(typPolotovaru);

	*inFile >> mnozstvo_;
	*inFile >> jednotkovaNakupnaCena_;
}
