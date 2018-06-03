#pragma once

/// <summary> Trieda reprezentujuca datum. </summary>
class Datum
{
public:
	/// <summary> Konstruktor. </summary>
	Datum(int pociatocnyCas);

	/// <summary> Destruktor. </summary>
	~Datum();

	/// <summary> Vrati cas. </summary>
	size_t dajCas() { return cas_; }

	/// <summary> Zvysi datum o 1 den. </summary>
	void zvysDen() { cas_++; }

	operator size_t() {
		return cas_;
	}

private:
	/// <summary> Cas reprezentovany ako cele kladne cislo. </summary>
	size_t cas_;
};


inline Datum::Datum(int pociatocnyCas)
{
	cas_ = pociatocnyCas > 1 ? pociatocnyCas : 1;
}

inline Datum::~Datum()
{
}

