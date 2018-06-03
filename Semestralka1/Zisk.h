#pragma once

/// <summary> Trieda reprezentuje naklady a prijmy firmy za dany den. </summary>
class Zisk
{
public:
	/// <summary> Konstruktor. </summary>
	Zisk();

	/// <summary> Konstruktor. </summary>
	Zisk(double cenaObjednavokTovaru, double cenaObjednavokPolotovarov, double prevadzkoveNakladyVozidiel);

	/// <summary> Destruktor. </summary>
	~Zisk();

	double dajCenuObjednavokTovaru() { return cenaObjednavokTovaru_; }
	double dajCenuObjednavokPolotovarov() { return cenaObjednavokPolotovarov_; }
	double dajPrevadzkoveNakladyVozidiel() { return prevadzkoveNakladyVozidiel_; }
	double dajZisk() { return cenaObjednavokTovaru_ - cenaObjednavokPolotovarov_ - prevadzkoveNakladyVozidiel_; }

	/// <summary> Zapise zisk do suboru. </summary>
	void zapisSa(ofstream * outFile);

	/// <summary> Nacita zisk zo suboru. </summary>
	void nacitajSa(ifstream * inFile);

private:
	/// <summary> Celkova cena zrealizovanych objednavok, ktore mali konkretny datum dorucenia. </summary>
	double cenaObjednavokTovaru_;

	/// <summary> Celkova cena, ktora bola v konkretny datum zaplatena biofarmarom za objednane polotovary. </summary>
	double cenaObjednavokPolotovarov_;

	/// <summary> Celkove prevadzkove naklady vozidiel v konkretny datum. </summary>
	double prevadzkoveNakladyVozidiel_;
};


inline Zisk::Zisk()
	:cenaObjednavokTovaru_(0), cenaObjednavokPolotovarov_(0), prevadzkoveNakladyVozidiel_(0)
{
}

inline Zisk::Zisk(double cenaObjednavokTovaru, double cenaObjednavokPolotovarov,
	double prevadzkoveNakladyVozidiel)
	: cenaObjednavokTovaru_(cenaObjednavokTovaru), cenaObjednavokPolotovarov_(cenaObjednavokPolotovarov),
	prevadzkoveNakladyVozidiel_(prevadzkoveNakladyVozidiel)
{
}


inline Zisk::~Zisk()
{
}

inline void Zisk::zapisSa(ofstream* outFile)
{
	*outFile << cenaObjednavokTovaru_ << endl;
	*outFile << cenaObjednavokPolotovarov_ << endl;
	*outFile << prevadzkoveNakladyVozidiel_ << endl;
}

inline void Zisk::nacitajSa(ifstream* inFile)
{
	*inFile >> cenaObjednavokTovaru_;
	*inFile >> cenaObjednavokPolotovarov_;
	*inFile >> prevadzkoveNakladyVozidiel_;
}
