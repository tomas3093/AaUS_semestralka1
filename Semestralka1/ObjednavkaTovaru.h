#pragma once

#include "Datum.h"
#include "Zakaznik.h"
#include "EvidenciaZakaznikov.h"

/// <summary> Trieda reprezentujuca objednavku tovaru od zakaznika. </summary>
class ObjednavkaTovaru
{
public:
	/// <summary> Konstruktor. </summary>
	ObjednavkaTovaru();

	/// <summary> Konstruktor. </summary>
	ObjednavkaTovaru(Zakaznik* zakaznik, Tovar::Typ typTovaru, double mnozstvo,
		double jednotkovaPredajnaCena, Datum datumZaevidovania, Datum datumDorucenia, StavObjednavky stav);

	/// <summary> Destruktor. </summary>
	~ObjednavkaTovaru();

	Datum dajDatumZaevidovania() { return datumZaevidovania_; }
	Datum dajDatumDorucenia() { return datumDorucenia_; }
	Zakaznik * dajZakaznika() { return zakaznik_; }
	Tovar::Typ dajTypTovaru() { return typTovaru_; }
	double dajMnozstvo() { return mnozstvo_; }
	double dajJednotkovuPredajnuCenu() { return jednotkovaPredajnaCena_; }
	StavObjednavky dajStav() { return stav_; }

	bool zmenStav(StavObjednavky novyStav);

	/// <summary> Zapise biofarmara do suboru. </summary>
	void zapisSa(ofstream * outFile);

	/// <summary> Nacita biofarmara zo suboru. </summary>
	void nacitajSa(ifstream * inFile, EvidenciaZakaznikov * zakaznici);

private:
	Datum datumZaevidovania_;
	Datum datumDorucenia_;
	Zakaznik * zakaznik_;
	Tovar::Typ typTovaru_;
	double mnozstvo_;
	double jednotkovaPredajnaCena_;
	StavObjednavky stav_;
};

inline ObjednavkaTovaru::ObjednavkaTovaru()
	:datumZaevidovania_(0), zakaznik_(nullptr),
typTovaru_(Tovar::Typ::ZEM_LUPIENKY), mnozstvo_(0), jednotkovaPredajnaCena_(0),
datumDorucenia_(0), stav_(StavObjednavky::ZRUSENA)
{
}

inline ObjednavkaTovaru::ObjednavkaTovaru(Zakaznik* zakaznik, Tovar::Typ typTovaru, double mnozstvo,
	double jednotkovaPredajnaCena, Datum datumZaevidovania, Datum datumDorucenia, StavObjednavky stav)
	:datumZaevidovania_(datumZaevidovania), zakaznik_(zakaznik),
	typTovaru_(typTovaru), mnozstvo_(mnozstvo), jednotkovaPredajnaCena_(jednotkovaPredajnaCena),
	datumDorucenia_(datumDorucenia), stav_(stav)
{
}


inline ObjednavkaTovaru::~ObjednavkaTovaru()
{
}

inline bool ObjednavkaTovaru::zmenStav(StavObjednavky novyStav)
{
	if (stav_ != novyStav)
	{
		stav_ = novyStav;
		return true;
	}
	return false;
}

inline void ObjednavkaTovaru::zapisSa(ofstream* outFile)
{
	*outFile << datumZaevidovania_ << endl;
	*outFile << datumDorucenia_ << endl;
	
	string nazovZakaznika = zakaznik_->dajNazov();
	*outFile << nazovZakaznika << endl;
	
	*outFile << Tovar::toNumber(typTovaru_) << endl;
	*outFile << mnozstvo_ << endl;
	*outFile << jednotkovaPredajnaCena_ << endl;
	*outFile << stavObjednavkytoNumber(stav_) << endl;
}

inline void ObjednavkaTovaru::nacitajSa(ifstream* inFile, EvidenciaZakaznikov * zakaznici)
{
	int datum;
	*inFile >> datum;
	datumZaevidovania_ = datum;
	*inFile >> datum;
	datumDorucenia_ = datum;

	string nazovZakaznika;
	*inFile >> nazovZakaznika;
	zakaznik_ = zakaznici->dajZakaznika(nazovZakaznika);

	int tovar;
	*inFile >> tovar;
	typTovaru_ = Tovar::toTyp(tovar);

	*inFile >> mnozstvo_;
	*inFile >> jednotkovaPredajnaCena_;

	int stavObjednavky;
	*inFile >> stavObjednavky;
	stav_ = stavObjednavkytoStav(stavObjednavky);
}
